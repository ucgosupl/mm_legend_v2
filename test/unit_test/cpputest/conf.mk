################################################################################
# File:     conf.mk
# Author:   GAndaLF
# Brief:    Makefile configuration script for cpputest target.
#
# This file contains configuration variables for cpputest target.
# After setting these variables, actual build script is called.
################################################################################

TARGET_NAME := cpputest

# Output folder containing object files
OUT_DIR := out/

# Paths containing headers (.h)
INC_DIRS := \
include/ \

# Paths containing source (.c)
SRC_DIRS := \
src/CppUTest \
src/CppUTestExt \

include build.mk