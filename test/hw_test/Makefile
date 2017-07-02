################################################################################
# File:     Makefile
# Author:   GAndaLF
# Brief:    Makefile script containing all hw test targets.
################################################################################

all : \
template \
hbridge \

clean : \
template_clean \
hbridge_clean \

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

#
################################################################################

.PHONY: all clean

.PHONY: template template_clean
.PHONY: hbridge hbridge_clean