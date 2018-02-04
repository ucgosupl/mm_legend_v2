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

hw_test_imu :
	@make -C test/hw_test imu

hw_test_imu_clean :
	@make -C test/hw_test imu_clean
	
hw_test_initial_states :
	@make -C test/hw_test initial_states

hw_test_initial_states_clean :
	@make -C test/hw_test initial_states_clean
	
hw_test_libfixmatrix :
	@make -C test/hw_test libfixmatrix

hw_test_libfixmatrix_clean :
	@make -C test/hw_test libfixmatrix_clean

hw_test_logger :
	@make -C test/hw_test logger

hw_test_logger_clean :
	@make -C test/hw_test logger_clean

hw_test_motor_ident :
	@make -C test/hw_test motor_ident

hw_test_motor_ident_clean :
	@make -C test/hw_test motor_ident_clean

hw_test_motor_linear :
	@make -C test/hw_test motor_linear

hw_test_motor_linear_clean :
	@make -C test/hw_test motor_linear_clean

hw_test_position :
	@make -C test/hw_test position

hw_test_position_clean :
	@make -C test/hw_test position_clean

hw_test_wall :
	@make -C test/hw_test wall

hw_test_wall_clean :
	@make -C test/hw_test wall_clean
	
#
###############################################################################

.PHONY: hw_test hw_test_clean
.PHONY: hw_test_template hw_test_template_clean
.PHONY: hw_test_hbridge hw_test_hbridge_clean
.PHONY: hw_test_imu hw_test_imu_clean
.PHONY: hw_test_initial_states hw_test_initial_states_clean
.PHONY: hw_test_libfixmatrix hw_test_libfixmatrix_clean
.PHONY: hw_test_logger hw_test_logger_clean
.PHONY: hw_test_motor_ident hw_test_motor_ident_clean
.PHONY: hw_test_motor_linear hw_test_motor_linear_clean
.PHONY: hw_test_position hw_test_position_clean
.PHONY: hw_test_wall hw_test_wall_clean
