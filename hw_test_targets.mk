###############################################################################
# File:     hw_test_targets.mk
# Author:   GAndaLF
# Brief:    Makefile containing all hw test targets.
###############################################################################

###############################################################################
# Build all unit tests

hw_test :
	@make -C test/hw_test all

hw_test_clean :
	@make -C test/hw_test clean

#
###############################################################################

###############################################################################
# Build HW test template

hw_test_template :
	@make -C test/hw_test template

hw_test_template_clean :
	@make -C test/hw_test template_clean

#
###############################################################################

###############################################################################
# HW test targets

#
###############################################################################

.PHONY: hw_test hw_test_clean
.PHONY: hw_test_template hw_test_template_clean