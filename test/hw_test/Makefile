################################################################################
# File:     Makefile
# Author:   GAndaLF
# Brief:    Makefile script containing all hw test targets.
################################################################################

all : \
template \
hbridge \
imu \
initial_states \
libfixmatrix \
logger \
motor_ident \
motor_linear \
position \
wall \

clean : \
template_clean \
hbridge_clean \
imu_clean \
initial_states_clean \
libfixmatrix_clean \
logger_clean \
motor_ident_clean \
motor_linear_clean \
position_clean \
wall_clean \

################################################################################
# Template HW test target

template :
	@make -C template -f conf.mk

template_clean :
	@make -C template -f conf.mk clean

#
################################################################################

################################################################################
# HW test targets

hbridge :
	@make -C hbridge -f conf.mk

hbridge_clean :
	@make -C hbridge -f conf.mk clean
	
imu :
	@make -C imu -f conf.mk

imu_clean :
	@make -C imu -f conf.mk clean

initial_states :
	@make -C initial_states -f conf.mk

initial_states_clean :
	@make -C initial_states -f conf.mk clean

libfixmatrix :
	@make -C libfixmatrix -f conf.mk

libfixmatrix_clean :
	@make -C libfixmatrix -f conf.mk clean
	
logger :
	@make -C logger -f conf.mk

logger_clean :
	@make -C logger -f conf.mk clean

motor_ident :
	@make -C motor_ident -f conf.mk

motor_ident_clean :
	@make -C motor_ident -f conf.mk clean

motor_linear :
	@make -C motor_linear -f conf.mk

motor_linear_clean :
	@make -C motor_linear -f conf.mk clean

position :
	@make -C position -f conf.mk

position_clean :
	@make -C position -f conf.mk clean

wall :
	@make -C wall -f conf.mk

wall_clean :
	@make -C wall -f conf.mk clean
			
#
################################################################################

.PHONY: all clean

.PHONY: template template_clean
.PHONY: hbridge hbridge_clean
.PHONY: imu imu_clean
.PHONY: initial_states initial_states_clean
.PHONY: libfixmatrix libfixmatrix_clean
.PHONY: logger logger_clean
.PHONY: motor_ident motor_ident_clean
.PHONY: motor_linear motor_linear_clean
.PHONY: position position_clean
.PHONY: wall wall_clean
