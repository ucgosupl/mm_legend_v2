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


hw_test_hbridge :
	@make -C test/hw_test hbridge

hw_test_hbridge_clean :
	@make -C test/hw_test hbridge_clean


hw_test_logger :
	@make -C test/hw_test logger

hw_test_logger_clean :
	@make -C test/hw_test logger_clean


#
###############################################################################

.PHONY: hw_test hw_test_clean
.PHONY: hw_test_template hw_test_template_clean
.PHONY: hw_test_hbridge hw_test_hbridge_clean
.PHONY: hw_test_logger hw_test_logger_clean