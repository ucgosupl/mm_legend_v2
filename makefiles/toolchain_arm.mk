################################################################################
# File:     toolchain_arm.mk
# Author:   GAndaLF
# Brief:    Variables for ARM toolchain.
################################################################################

TOOLCHAIN := arm-none-eabi-

CC := $(TOOLCHAIN)gcc
CXX := $(TOOLCHAIN)g++
AS := $(TOOLCHAIN)gcc -x assembler-with-cpp
OBJCOPY := $(TOOLCHAIN)objcopy
OBJDUMP := $(TOOLCHAIN)objdump
SIZE := $(TOOLCHAIN)size