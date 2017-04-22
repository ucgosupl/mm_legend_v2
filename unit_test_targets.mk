###############################################################################
# File:     unit_test_targets.mk
# Author:   GAndaLF
# Brief:    Makefile containing all unit test targets.
###############################################################################

###############################################################################
# Build all unit tests

unit_test :
	@make -C test/unit_test all

unit_test_clean :
	@make -C test/unit_test clean

#
###############################################################################

###############################################################################
# Build unit test template

unit_test_template :
	@make -C test/unit_test template

unit_test_template_clean :
	@make -C test/unit_test template_clean

#
###############################################################################

###############################################################################
# Unit test targets

#
###############################################################################

.PHONY: unit_test unit_test_clean
.PHONY: unit_test_template unit_test_template_clean