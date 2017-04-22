################################################################################
# File:     toolchain.mk
# Author:   GAndaLF
# Brief:    Variables for gcc toolchain for PC.
################################################################################

ifeq ($(TRAVIS), true)
CC := gcc-4.8
CPP := g++-4.8
AR := ar
else
CC := gcc
CPP := g++
AR := ar
endif