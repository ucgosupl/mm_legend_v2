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
# Build unit test targets

unit_test_map :
	@make -C test/unit_test map

unit_test_map_clean :
	@make -C test/unit_test map_clean

unit_test_map_update :
	@make -C test/unit_test map_update

unit_test_map_update_clean :
	@make -C test/unit_test map_update_clean

unit_test_map_validate :
	@make -C test/unit_test map_validate

unit_test_map_validate_clean :
	@make -C test/unit_test map_validate_clean

unit_test_mazetool :
	@make -C test/unit_test mazetool

unit_test_mazetool_clean :
	@make -C test/unit_test mazetool_clean

unit_test_vbat :
	@make -C test/unit_test vbat

unit_test_vbat_clean :
	@make -C test/unit_test vbat_clean

unit_test_wall_detection :
	@make -C test/unit_test wall_detection

unit_test_wall_detection_clean :
	@make -C test/unit_test wall_detection_clean

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
.PHONY: unit_test_map unit_test_map_clean
.PHONY: unit_test_map_update unit_test_map_update_clean
.PHONY: unit_test_map_validate unit_test_map_validate_clean
.PHONY: unit_test_mazetool unit_test_mazetool_clean
.PHONY: unit_test_vbat unit_test_vbat_clean
.PHONY: unit_test_wall_detection unit_test_wall_detection_clean
.PHONY: unit_test_template unit_test_template_clean
