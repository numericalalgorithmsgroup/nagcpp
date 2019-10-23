#!/bin/bash -u
## run the examples

set +o nounset
## installation / working directories ...
SCRIPT_DIR="${BASH_SOURCE%/*}"
if [[ ! -d "$SCRIPT_DIR" ]]; then SCRIPT_DIR="$PWD"; fi
source "${SCRIPT_DIR}/set_installation_dir.sh"
## ... installation / working directories

usage()
{
  echo Usage: "$(basename "${0}") [-valgrind] [-f makefile] [-k 0|1|2] [-noclean] [installation directory] [working directory]"
  echo "Compile and run examples"
  echo "installation directory defaults to: ${INSTALLATION_DIR}"
  echo "working directory defaults to: ./Temp/"
  if [ -z ${ENGINEHOME} ]
  then
    echo "ENGINEHOME variable is unset, which is what is used to get directory defaults"
  fi
  echo Switches:
  echo "  -valgrind                         if present, all tests are run via valgrind"
  echo "  -f / -makefile                    name of the makefile to use (defaults to makefile)"
  echo "  -k / -keep_work_files             if 0 work files are deleted, 1 (default) = kept on failure"
  echo "                                    2 = always kept (strictly speaking this is != 0 or 1 rather than 2)"
  echo "  -noclean                          if specified then make clean is not run first"
}

VALGRIND=
MAKEFILE=${INSTALLATION_DIR}/scripts/makefile

run_clean=1
keep_work_files=1
verbose=1

install_dir_set=0
working_dir_set=0
while test $# -gt 0
do
  case ${1} in
    -valgrind | --valgrind)
      VALGRIND=valgrind
      ;;
    -noclean | --noclean)
      run_clean=0
      ;;
    -f | --f | --makefile | -makefile)
      shift
      MAKEFILE=${1}
      ;;
    -k | --k | --keep_work_files | -keep_work_files)
      shift
      keep_work_files=${1}
      ;;
    -h | --h | --help | -help)
      usage
      exit 0
      ;;
    -* | --* )
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
EXAMPLE_DIR=${INSTALLATION_DIR}/examples/
EXAMPLE_RESULTS_DIR=${EXAMPLE_DIR}/baseresults/
EXAMPLE_DATA_DIR=${EXAMPLE_DIR}/data/
## ... rest of directories

if [[ ! -d ${EXAMPLE_DIR} ]]
then
  echo "directory does not exist: ${EXAMPLE_DIR}"
  exit 1
fi

## compile the examples
failed=0
make_failed=0
if [ ${run_clean} == 1 ]
then
  make -f ${MAKEFILE} INSTALLATION_DIR="${INSTALLATION_DIR}" WORKING_DIR="${WORKING_DIR}" clean &> /dev/null
fi
tmpfile=$(mktemp _EX_TEMPORARY_MAKE.XXXXX)
for file in ${EXAMPLE_DIR}/ex*.cpp
do
  filename=$(basename $file | cut -d '.' -f 1)
  if [ ${verbose} != 0 ]
  then
    echo make -f ${MAKEFILE} INSTALLATION_DIR="${INSTALLATION_DIR}" WORKING_DIR="${WORKING_DIR}" ${filename}.exe
  fi
  make -f ${MAKEFILE} INSTALLATION_DIR="${INSTALLATION_DIR}" WORKING_DIR="${WORKING_DIR}" ${filename}.exe &>> ${tmpfile}
  if [ $? -gt 0 ]
  then
    echo "ERROR: making ${filename}.exe failed"
    make_failed=1
    failed=1
  fi
done

differ=0
tmpdir=$(mktemp -d _EX_TEMPORARY_RESULTS.XXXXX)
for file in ${EXAMPLE_DIR}/ex*.cpp
do
  filename=$(basename $file | cut -d '.' -f 1)
  if [ -f ${WORKING_DIR}/${filename}.exe ]
  then
    $VALGRIND ${WORKING_DIR}/${filename}.exe > ${tmpdir}/${filename}.r
    this_differ=1
    match_res=
    ## loop over variant results files
    for resfile in ${EXAMPLE_RESULTS_DIR}/${filename}.r*
    do
      diff --strip-trailing-cr -q ${tmpdir}/${filename}.r ${resfile} > /dev/null
      if [ $? -eq 0 ]
      then
        this_differ=0
        match_res=${resfile}
      fi
    done
    if [ ${this_differ} == 1 ]
    then
      failed=1
      differ=1
      result="example differs"
    else
      result="example same ($(basename ${match_res}))"
    fi
  else
    result="example does not exist"
    differ=1
    failed=1
  fi
  echo "${filename}: ${result}"
done

echo
if [ $failed == 1 ]
then
  echo "At least one example FAILED (or failed to compile)"
else
  echo "All examples PASSED"
fi

if [[ ${keep_work_files} == 0 || (${failed} == 0 && ${keep_work_files} == 1) ]]
then
  \rm ${tmpfile}
  \rm -fr ${tmpdir}
else
  echo
  echo "Results files can be found in ${tmpdir}"
  echo "and make log file can be found in ${tmpfile}"
fi
