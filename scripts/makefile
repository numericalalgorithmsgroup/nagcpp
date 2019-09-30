## Use sh as the shell
SHELL = /bin/sh

## Clear out suffixes, not using any default rules
.SUFFIXES:

.PHONY: clean check_env all dumpy really_all

IS_WINDOWS := $(shell uname -a | grep -i "Microsoft\|CYGWIN" | wc -l)
IS_CYGWIN := $(shell uname -a | grep -i "CYGWIN" | wc -l)
## expecting PLATOS = LINUX or WINDOWS, we only
## use WINDOWS in if statements
ifeq ($(IS_WINDOWS),1)
  PLATOS="WINDOWS"
else
  PLATOS="LINUX"
endif

## installation / working directories ...
INSTALLATION_DIR ?= $(dir $(lastword $(MAKEFILE_LIST)))../
WORKING_DIR ?= ./Temp
## ... installation / working directories

## rest of directories ...
EXAMPLE_DIR := $(INSTALLATION_DIR)/examples
UNIT_TEST_DIR := $(INSTALLATION_DIR)/tests
HEADERS_DIR := $(INSTALLATION_DIR)/include
SCRIPTS_DIR := $(INSTALLATION_DIR)/scripts
OBJ_DIR := $(WORKING_DIR)/objects
EXE_DIR := $(WORKING_DIR)
## ... rest of directories

## extensions ...
EXE_EXT ?= .exe
CPP_EXT ?= .cpp
HPP_EXT ?= .hpp
ifeq ($(PLATOS),"WINDOWS")
  OBJ_EXT ?= .obj
else
  OBJ_EXT ?= .o
endif
## ... extensions

## compiler options ...
## it is assumed that on Linux the NAG supplied nagvars.sh has been run
## which sets NAGLIB_CXX, NAGLIB_CXXFLAGS, NAGLIB_INCLUDE and NAGLIB_LINK
NAMEOBJ := -o # comment to preserve trailing space
NAMEEXE := -o # comment to preserve trailing space

ifeq ($(PLATOS),"WINDOWS")
  ifeq ($(IS_CYGWIN),1)
    NAGLIB_CXX := $(SCRIPTS_DIR)/win_icl
  else
    NAGLIB_CXX := icl.exe
  endif
  NAGLIB_CXXFLAGS := /EHsc /MD /Qstd=c++11
  NAGLIB_LINK := nag_nag_MD.lib user32.lib
  NAMEOBJ := -Fo:
  NAMEEXE := -Fe:
else
  ADDITIONAL_CXXFLAGS += -std=c++11
endif

ifeq ($(debug_mode),1)
  ifeq ($(PLATOS),"WINDOWS")
    ADDITIONAL_CXXFLAGS +=  /Z7 /Od
  else
    ADDITIONAL_CXXFLAGS += -Wall -w3 -debug
    ## disable remark #869: parameter XXXX was never referenced
    ADDITIONAL_CXXFLAGS += -wd869
    ## disable remark #383: value copied to temporary, reference to temporary used
    ADDITIONAL_CXXFLAGS += -wd383
    ## disable remark #1418: external function definition with no prior declaration
    ADDITIONAL_CXXFLAGS += -wd1418
  endif
endif
## ... compiler options

EXAMPLE_SRC := $(notdir $(wildcard $(EXAMPLE_DIR)/*$(CPP_EXT)))
EXAMPLE_OBJ := $(addprefix $(OBJ_DIR)/, $(addsuffix $(OBJ_EXT), $(basename $(EXAMPLE_SRC))))
EXAMPLE_EXE := $(addprefix $(EXE_DIR)/, $(addsuffix $(EXE_EXT), $(notdir $(basename $(EXAMPLE_OBJ)))))

UNIT_TEST_SRC := $(notdir $(wildcard $(UNIT_TEST_DIR)/*$(CPP_EXT)))
UNIT_TEST_OBJ := $(addprefix $(OBJ_DIR)/, $(addsuffix $(OBJ_EXT), $(basename $(UNIT_TEST_SRC))))
UNIT_TEST_EXE := $(addprefix $(EXE_DIR)/, $(addsuffix $(EXE_EXT), $(notdir $(basename $(UNIT_TEST_OBJ)))))

ALL_OBJ := $(EXAMPLE_OBJ) $(UNIT_TEST_OBJ)
ALL_EXE := $(EXAMPLE_EXE) $(UNIT_TEST_EXE)

## List of directories that make can search for source files in
VPATH := $(EXAMPLE_DIR) : $(UNIT_TEST_DIR)

DRY_RUN ?= 0
ifeq ($(DRY_RUN),1)
  ECHO:=@echo
else
  ECHO:=
endif

clean:
	$(ECHO) @rm -fr $(OBJ_DIR) | cat
	$(ECHO) @rm -fr $(EXE_DIR) | cat

check_env:
ifeq ("${NAGLIB_CXX}", "")
	$(error NAGLIB_CXX is undefined, try running the nagvars.sh supplied with the library)
else
ifeq ($(shell which ${NAGLIB_CXX}),)
	$(error ${NAGLIB_CXX} is not in the path, try running compiler setup script (compilervars.sh?))
endif
endif

##	Rule to allow target to be specified without directory
$(notdir $(ALL_OBJ)) : %$(OBJ_EXT) : $(OBJ_DIR)/%$(OBJ_EXT)
$(notdir $(ALL_EXE)) : %$(EXE_EXT) : $(EXE_DIR)/%$(EXE_EXT)

$(ALL_OBJ) : $(OBJ_DIR)/%$(OBJ_EXT) : %$(CPP_EXT) check_env
	@mkdir -p $(OBJ_DIR)
	$(ECHO) ${NAGLIB_CXX} ${NAGLIB_CXXFLAGS} $(ADDITIONAL_CXXFLAGS) ${NAGLIB_INCLUDE} -I $(HEADERS_DIR) $< -c $(NAMEOBJ)$(OBJ_DIR)/$(@F)

$(ALL_EXE) : $(EXE_DIR)/%$(EXE_EXT) : $(OBJ_DIR)/%$(OBJ_EXT) check_env
	@mkdir -p $(EXE_DIR)
	$(ECHO) ${NAGLIB_CXX} ${NAGLIB_CXXFLAGS} $(ADDITIONAL_CXXFLAGS) ${NAGLIB_INCLUDE} $< ${NAGLIB_LINK} $(NAMEEXE)$(EXE_DIR)/$(@F)

BOOST_EXE=$(filter %boost.exe, $(ALL_EXE))
ALL_NO_THIRD_PARTY_EXE=$(filter-out $(BOOST_EXE), $(ALL_EXE))

all: $(ALL_NO_THIRD_PARTY_EXE)

really_all: $(ALL_EXE)

.DEFAULT:
	@echo "No target to make $(@)"
ifeq ("$(wildcard $(INSTALLATION_DIR)/*)","")
	$(error $(INSTALLATION_DIR) does not exist)
endif

dump:
	@echo "PLATOS              : $(PLATOS)"
	@echo "NAGLIB_CXX          : $(NAGLIB_CXX)"
	@echo "NAGLIB_CXXFLAGS     : $(NAGLIB_CXXFLAGS)"
	@echo "NAGLIB_LINK         : $(NAGLIB_LINK)"
	@echo "ADDITIONAL_CXXFLAGS : $(ADDITIONAL_CXXFLAGS)"
	@echo "INSTALLATION_DIR    : $(INSTALLATION_DIR)"
	@echo "EXAMPLE_SRC         : $(EXAMPLE_SRC)"
	@echo "EXAMPLE_EXE         : $(EXAMPLE_EXE)"
	@echo "UNIT_TEST_SRC       : $(UNIT_TEST_SRC)"
	@echo "UNIT_TEST_EXE       : $(UNIT_TEST_EXE)"
	@echo "all target          : $(ALL_NO_THIRD_PARTY_EXE)"
	@echo "really_all target   : $(ALL_EXE)"
	@echo "BOOST EXE           : $(BOOST_EXE)"
