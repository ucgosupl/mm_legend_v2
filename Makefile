################################################################################
# File:     Makefile
# Author:   GAndaLF
# Brief:    Main makefile for the whole project.
#
# This file contains definitions of all targets in the project. If target is
# not defined here, it is included from one of helper makefiles included.
################################################################################

################################################################################
# build all possible targets

all : \
unit_test \
hw_test \
main_program \

clean : \
unit_test_clean \
hw_test_clean \
main_program_clean \

#
################################################################################

################################################################################
# build main program for the target platform
main_program :
	@make -C src -f conf.mk

# cleaning of the files created during main program build
main_program_clean :
	@make -C src -f conf.mk clean

#
################################################################################

.PHONY: all clean

.PHONY: main_program main_program_clean

include unit_test_targets.mk
include hw_test_targets.mk