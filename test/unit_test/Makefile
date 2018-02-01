###############################################################################
#
# Script file for building unit tests on PC. This script is universal for every
# PC test. Each tests contains conf.mk file containing test specific defines.
#
###############################################################################

all : \
vbat \
template \

clean : \
clear_testlog \
vbat_clean \
template_clean \

###############################################################################
# CppUTest target

cpputest :
	@make -C cpputest -f conf.mk

cpputest_clean :
	@make -C cpputest -f conf.mk clean

#
###############################################################################

###############################################################################
# Unit test targets

vbat : cpputest
	@make -C vbat -f conf.mk

vbat_clean : cpputest_clean
	@make -C vbat -f conf.mk clean

#
###############################################################################

###############################################################################
# Template unit test target

template : cpputest
	@make -C template -f conf.mk

template_clean : cpputest_clean
	@make -C template -f conf.mk clean

#
###############################################################################

###############################################################################
# Unit test targets

#
###############################################################################

clear_testlog :
	@rm -rf test_results.txt

.PHONY: all clean
.PHONY: clear_testlog
.PHONY: cpputest cpputest_clean
.PHONY: vbat vbat_clean
.PHONY: template template_clean