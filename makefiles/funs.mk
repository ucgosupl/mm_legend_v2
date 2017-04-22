################################################################################
# File:     funs.mk
# Author:   GAndaLF
# Brief:    Makefile script containing custom functions used by many makefiles.
################################################################################

# Function for searching folders recursively for given pattern
rwildcard=$(wildcard $(addsuffix $2, $1))\
$(foreach d,$(wildcard $(addsuffix *, $1)),$(call rwildcard,$d/,$2))