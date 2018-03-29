###############################################################################
#
# Script file for building unit tests on PC. This script is universal for every
# PC test. Each tests contains conf.mk file containing test specific defines.
#
###############################################################################

all : \
map \
map_update \
map_validate \
mazetool \
vbat \
wall_detection \
template \

clean : \
clear_testlog \
map_clean \
map_update_clean \
mazetool_clean \
vbat_clean \
wall_detection_clean \
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

map : cpputest
	@make -C map -f conf.mk

map_clean : cpputest_clean
	@make -C map -f conf.mk clean

map_update : cpputest
	@make -C map_update -f conf.mk

map_update_clean : cpputest_clean
	@make -C map_update -f conf.mk clean

map_validate : cpputest
	@make -C map_validate -f conf.mk

map_validate_clean : cpputest_clean
	@make -C map_validate -f conf.mk clean
	
mazetool : cpputest
	@make -C mazetool -f conf.mk

mazetool_clean : cpputest_clean
	@make -C mazetool -f conf.mk clean

vbat : cpputest
	@make -C vbat -f conf.mk

vbat_clean : cpputest_clean
	@make -C vbat -f conf.mk clean

wall_detection : cpputest
	@make -C wall_detection -f conf.mk

wall_detection_clean : cpputest_clean
	@make -C wall_detection -f conf.mk clean


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
.PHONY: map map_clean
.PHONY: map_update map_update_clean
.PHONY: map_validate map_validate_clean
.PHONY: mazetool mazetool_clean
.PHONY: vbat vbat_clean
.PHONY: wall_detection wall_detection_clean
.PHONY: template template_clean