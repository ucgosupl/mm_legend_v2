################################################################################
# File:     Makefile
# Author:   GAndaLF
# Brief:    Makefile script containing all hw test targets.
################################################################################

all : \
template \
hbridge \
logger \

clean : \
template_clean \
hbridge_clean \
logger_clean \

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

logger :
	@make -C logger -f conf.mk

logger_clean :
	@make -C logger -f conf.mk clean
	
#
################################################################################

.PHONY: all clean

.PHONY: template template_clean
.PHONY: hbridge hbridge_clean
.PHONY: logger logger_clean