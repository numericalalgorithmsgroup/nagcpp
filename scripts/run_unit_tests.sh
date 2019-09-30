#!/bin/bash -u
## run the unit tests

set +o nounset
## installation / working directories ...
SCRIPT_DIR="${BASH_SOURCE%/*}"
if [[ ! -d "$SCRIPT_DIR" ]]; then SCRIPT_DIR="$PWD"; fi
source "${SCRIPT_DIR}/set_installation_dir.sh"
## ... installation / working directories

usage()
{
  echo Usage: "$(basename "${0}") [-tpl <n>] [-uls <n>] [-cls <n>] [-rls <n>] [-valgrind] [-noclean] [installation directory] [working directory]"
  echo "Compile and run unit tests, also checks for unregistered tests"
  echo "installation directory defaults to: ${INSTALLATION_DIR}"
  echo "working directory defaults to: ./Temp/"
  if [ -z ${ENGINEHOME} ]
  then
    echo "ENGINEHOME variable is unset, which is what is used to get directory defaults"
  fi
  echo Switches:
  echo "  -tpl <n>,                         print level for the tests."
  echo "      --test-print-level <n>        (levels 0 to 4, see cxxunit_testing.hpp)"
  echo "  -uls <n>,                         log style for reporting unregistered test cases"
  echo "      --unregistered-log-style <n>  defaults to screen only (3)"
  echo "  -cls <n>,                         log style for reporting compilation output"
  echo "      --compile-log-style <n>       defaults to file only (2)"
  echo "  -rls <n>,                         log style for reporting output from running tests"
  echo "      --run-log-style <n>           defaults to screen and file (1)"
  echo "  all log styles are 0, 1, 2 or 3: 0 = no output, 1 = to screen and file"
  echo "    2 = file only, 3 = screen only"
  echo "  -valgrind                         if present, all tests are run via valgrind"
  echo "  -f / -makefile                    name of the makefile to use (defaults to makefile)"
  echo "  -noclean                          if specified then make clean is not run first"
}

TEST_PRINT_LEVEL=1

## named constants
SCREEN_AND_FILE=1
FILE_ONLY=2
SCREEN_ONLY=3
NO_OUTPUT=0

UNREGISTERED_LOG_STYLE=${SCREEN_ONLY}
COMPILE_LOG_STYLE=${FILE_ONLY}
RUN_LOG_STYLE=${SCREEN_AND_FILE}
VALGRIND=
MAKEFILE=${INSTALLATION_DIR}/scripts/makefile

run_clean=1
verbose=1

install_dir_set=0
working_dir_set=0
while test $# -gt 0
do
  case ${1} in
    -noclean | --noclean)
      run_clean=0
      ;;
    -tpl | --test-print-level)
      shift
      TEST_PRINT_LEVEL=${1}
      ;;
    -uls | --unregistered-log-style)
      shift
      UNREGISTERED_LOG_STYLE=${1}
      ;;
    -cls | --compile-log-style)
      shift
      COMPILE_LOG_STYLE=${1}
      ;;
    -rls | --run-log-style)
      shift
      RUN_LOG_STYLE=${1}
      ;;
    -valgrind | --valgrind)
      VALGRIND=valgrind
      ;;
    -f | --f | --makefile | -makefile)
      shift
      MAKEFILE=${1}
      ;;
    -h | --h | --help | -help)
      usage
      exit 0
      ;;
    -* | --*)
      usage
      echo Error: invalid switch "${1}" > /dev/stderr
      exit 1
      ;;
     *)
       if [ $install_dir_set = 0 ]
       then
         INSTALLATION_DIR=${1}
         install_dir_set=1
       elif [ $working_dir_set = 0 ]
       then
         WORKING_DIR=${1}
         working_dir_set=1
       else
         usage
         echo Error: too many directories specified
         exit 1
       fi
  esac
  shift
done
set -o nounset

if [ $working_dir_set = 0 ]
then
  WORKING_DIR=./Temp/
fi

if [[ ! -d ${INSTALLATION_DIR} ]]
then
  echo "directory does not exist: ${INSTALLATION_DIR}"
  exit 1
fi

## rest of directories ...
UNIT_TEST_DIR=${INSTALLATION_DIR}/tests/
## ... rest of directories

if [[ ! -d ${UNIT_TEST_DIR} ]]
then
  echo "directory does not exist: ${UNIT_TEST_DIR}"
  exit 1
fi

## log files
UNREGISTERED_LOG_FILE=ut_unregistered_tests.log
COMPILE_LOG_FILE=ut_compile.log
RUN_LOG_FILE=ut_run.log

LOGGER() {
  ## echos output of a temporary file to
  ## screen and / or a permanent file
  ## usage:
  ## LOGGER <temporary file> <log style> <log file>
  ## originally tried to write this so it could
  ## be used at the end of a pipe, but couldn't get it
  ## to work - so now temporary files are used

  if [ ${2} == ${SCREEN_AND_FILE} ]
  then
    if [ "$VALGRIND" != "" ]
    then
      ## strip out the valgrind information from the screen if
      ## also sending to a file
      cat ${1} | grep -v "^==[[:digit:]]*=="
    else
      cat ${1}
    fi
    mv ${1} ${3}
  elif [ ${2} == ${FILE_ONLY} ]
  then
    mv ${1} ${3}
  elif [ ${2} == ${SCREEN_ONLY} ]
  then
    cat ${1}
    CLEAN_LOG ${1}
  elif [ ${2} == ${NO_OUTPUT} ]
  then
    CLEAN_LOG ${1}
  else
    echo "INVALID STYLE IN LOGGER ${2}"
    exit 1
  fi

}

CLEAN_LOG() {
  ## remove a file
  ## usage:
  ## CLEAN_LOG <file>
  if [[ ${1} != *"*"* ]]
  then
    rm -f ${1}
  else
    echo "Not removing the specified log file it contains a wildcard"
    exit 1
  fi
}

## check for unregistered tests
tmpfile=$(mktemp _UT_TEMPORARY_UNREGISTERED.XXXXX)
CLEAN_LOG "${UNREGISTERED_LOG_FILE}"
for file in ${UNIT_TEST_DIR}/ut*.cpp
do
  registered_tests=$(grep REGISTER_TEST ${file} | grep -v "^//" | cut -d "(" -f 2- | cut -d "," -f 1)
  written_tests=$(grep "struct.*[[:space:]]*:[[:space:]]*\(public\)\?[[:space:]]*TestCase" ${file} | grep -v "^//" | cut -d ' ' -f 2- | cut -d : -f 1)

  unregistered_tests=$(echo ${registered_tests} ${written_tests} | xargs -n1 | sort | uniq -u)

  if [ "${unregistered_tests}" != "" ]
  then
    echo "Possibly unregistered tests in ${file}:" >> ${tmpfile}
    for test in ${unregistered_tests}
    do
      echo "  ${test}" >> ${tmpfile}
    done
    echo >> ${tmpfile}
  fi
done
LOGGER ${tmpfile} "${UNREGISTERED_LOG_STYLE}" "${UNREGISTERED_LOG_FILE}"

## compile the tests
if [ ${run_clean} == 1 ]
then
  make -f ${MAKEFILE} INSTALLATION_DIR="${INSTALLATION_DIR}" WORKING_DIR="${WORKING_DIR}" clean &> /dev/null
fi
CLEAN_LOG "${COMPILE_LOG_FILE}"
tmpfile=$(mktemp _UT_TEMPORARY_MAKE.XXXXX)
for file in ${UNIT_TEST_DIR}/ut*.cpp
do
  filename=$(basename $file | cut -d '.' -f 1)
  if [ ${verbose} != 0 ]
  then
    echo make -f ${MAKEFILE} INSTALLATION_DIR="${INSTALLATION_DIR}" WORKING_DIR="${WORKING_DIR}" ${filename}.exe
  fi
  make -f ${MAKEFILE} INSTALLATION_DIR="${INSTALLATION_DIR}" WORKING_DIR="${WORKING_DIR}" ${filename}.exe &>> ${tmpfile}
done
LOGGER ${tmpfile} "${COMPILE_LOG_STYLE}" "${COMPILE_LOG_FILE}"

## run the tests
failed=0

CLEAN_LOG "${RUN_LOG_FILE}"
tmpfile=$(mktemp _UT_TEMPORARY_RUN.XXXXX)
for file in ${UNIT_TEST_DIR}/ut*.cpp
do
  filename=$(basename $file | cut -d '.' -f 1)
  echo "Running ${filename}:" >> ${tmpfile}

  if [ -f ${WORKING_DIR}/${filename}.exe ]
  then
    $VALGRIND ${WORKING_DIR}/${filename}.exe -p ${TEST_PRINT_LEVEL} &>> ${tmpfile}
    if [ $? -gt 0 ]
    then
      failed=1
    fi
  else
    echo "* Overall Summary: FAILED" >> ${tmpfile}
    echo "   Test did not compile" >> ${tmpfile}
    failed=1
  fi
  echo >> ${tmpfile}
done

if [ ${failed} -gt 0 ]
then
  echo "At least one test FAILED (or failed to compile)" >> ${tmpfile}
else
  echo "All tests PASSED" >> ${tmpfile}
fi
LOGGER ${tmpfile} "${RUN_LOG_STYLE}" "${RUN_LOG_FILE}"
