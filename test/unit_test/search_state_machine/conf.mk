################################################################################
# File:     conf.mk
# Author:   GAndaLF
# Brief:    Makefile configuration script for unit_test_search_state_machine target.
#
# This file contains configuration variables for unit_test_search_state_machine target.
# After setting these variables, actual build script is called.
################################################################################

# Name for output binary hex, bin files
TARGET_NAME := search_state_machine

# Folder containing compilation result files
OUT_DIR := out/

# Defines passed as compiler arguments
GLOBAL_DEFS := \
UNIT_TEST=1 \

###############################################################################
# Paths for code under test

# Paths to header files (.h).
INC_DIRS := \
. \
../../../src/code \
../../../src/hw \
../common \
../mock_templates \

# Paths for source files (.c) and (.S)
# In these paths files are searched recursively in subfolders.
SRC_DIRS := \

# Additional source files (.c)
C_SRC_FILES := \
../../../src/code/search/search_state_machine.c \

#
###############################################################################

###############################################################################
# Paths for test code

# Dot . shouldn't be followed by slash /, because include paths wouldn't be
# found.
TEST_INC_DIRS := \
. \
../cpputest/include \

# Dot . should be followed by slash /, otherwise files from upper folder are
# also taken.
TEST_SRC_DIRS := \
./ \

TEST_SRC_FILES := \

#
###############################################################################

###############################################################################
# Static library defines

# Path to precompiled libraries (.a).
LIB_DIRS := \
../cpputest/out/lib

# Precompiled libraries used.
# Here we provide only the name of the library. File name also contains lib
# prefix and .a extension. For example for math library we provide here only
# the name "m", but actual file name is "libm.a".
LIBS := \
cpputest

include ../build.mk