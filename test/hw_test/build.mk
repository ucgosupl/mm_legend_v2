################################################################################
# File:     build.mk
# Author:   GAndaLF
# Brief:    Build script for STM32F4 used by hw tests.
################################################################################

include ../../../makefiles/toolchain_arm.mk
include ../../../makefiles/platform.mk
include ../../../makefiles/funs.mk

###############################################################################
# Files and paths definitions

# extensions of source C++, C and ASM files
CXX_EXT := cpp
C_EXT := c
ASM_EXT := S

# searching for source C"", C and ASM files in directories provided
CXX_SRCS := $(call rwildcard,$(SRC_DIRS),*.$(CXX_EXT))
C_SRCS := $(call rwildcard,$(SRC_DIRS),*.$(C_EXT))
ASM_SRCS := $(call rwildcard,$(SRC_DIRS),*.$(ASM_EXT))

# adding single files
CXX_SRCS += $(CXX_SRC_FILES)
C_SRCS += $(C_SRC_FILES)
ASM_SRCS += $(ASM_SRC_FILES)

# variable storing all possible paths where dependencies could be found
VPATH := $(sort $(dir $(CXX_SRCS) $(C_SRCS) $(ASM_SRCS)) $(INC_DIRS))

#
################################################################################

################################################################################
# Compiler and linker defines

# Compiler flags used for C and ASM files
CORE_FLAGS := -mcpu=cortex-m4 -mthumb

# Debug flag
CORE_FLAGS += -g

# Hardware float support
CORE_FLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16 -ffast-math

# Compiler flags specific for C++ files
# -std - C++ standard: c++98, gnu++98, c++11, gnu++11, c++14, gnu++14
# -fno-rtti - disable virtual class information used by dynamic_cast and typeid
# -fno-exceptions - disable exception handling
# fverbose-asm - additional comments for generated assembler code
CXX_FLAGS = -std=gnu++14 -O0 -g -fno-rtti -fno-exceptions -fverbose-asm

# Compiler flags specific for C files
# -std - C standard: c89, c99, gnu89,gnu99, iso9899:119409
# -O0 - optimization level: -O0, -O1, -O2, -O3, -Os
# fverbose-asm - additional comments for generated assembler code
C_FLAGS := -std=gnu89 -O0 -ffunction-sections -fdata-sections -fverbose-asm

# Warning flags for C++
# -Wall - standard warnings
# -Wextra - extended warnings
CXX_WARNINGS := -Wall -Wextra

# Warning flags for C
# -Wall - standard warnings
# -Wextra - extended warnings
# -Wstrict-prototypes - additional warnings for function prototypes
C_WARNINGS := -Wall -Wextra -Wstrict-prototypes

# Linker flags
# -Wl, -Map - map file to be created
# -T - file with linker script
# -g - debug flag
# -Wl,--gc-sections - unused function removal
LD_FLAGS := -Wl,-Map=$(OUT_DIR)bin/$(TARGET_NAME).map,--cref -T$(LD_SCRIPT) -g -Wl,--gc-sections

# Add global defines
GLOBAL_DEFS_F = $(patsubst %, -D%, $(GLOBAL_DEFS))
CORE_FLAGS += $(GLOBAL_DEFS_F)

# Add header paths
INC_DIRS_F = -I. $(patsubst %, -I%, $(INC_DIRS))

# Add static lib dirs
LIB_DIRS_F = $(patsubst %, -L%, $(LIB_DIRS))

# Add static libs
LIBS_F = $(patsubst %, -l%, $(LIBS))

# final flags for C++, C, ASM and linker
CXX_FLAGS += $(CORE_FLAGS) $(CXX_WARNINGS) $(INC_DIRS_F)
C_FLAGS += $(CORE_FLAGS) $(C_WARNINGS) $(INC_DIRS_F)
ASM_FLAGS := $(CORE_FLAGS) $(INC_DIRS_F)
LD_FLAGS += $(CORE_FLAGS) 
LD_LIBS = $(LIB_DIRS_F) $(LIBS_F)

#
################################################################################

################################################################################
# Defines for output files

ELF := $(OUT_DIR)bin/$(TARGET_NAME).elf
HEX := $(OUT_DIR)bin/$(TARGET_NAME).hex
BIN := $(OUT_DIR)bin/$(TARGET_NAME).bin
LSS := $(OUT_DIR)bin/$(TARGET_NAME).lss
DMP := $(OUT_DIR)bin/$(TARGET_NAME).dmp

CXX_OBJS := $(addprefix $(OUT_DIR), $(notdir $(CXX_SRCS:.$(CXX_EXT)=.o)))
C_OBJS := $(addprefix $(OUT_DIR), $(notdir $(C_SRCS:.$(C_EXT)=.o)))
ASM_OBJS := $(addprefix $(OUT_DIR), $(notdir $(ASM_SRCS:.$(ASM_EXT)=.o)))
OBJS := $(ASM_OBJS) $(C_OBJS) $(CXX_OBJS)

GENERATED := $(OBJS) $(ELF) $(HEX) $(BIN) $(LSS) $(DMP)

#
################################################################################

################################################################################
# Target list

all : make_out_dir $(ELF) $(LSS) $(DMP) $(HEX) $(BIN) print_size

# Binaries generation
$(HEX) : $(ELF)
	$(ECHO) 'Creating HEX image: $(HEX)'
	$(OBJCOPY) -O ihex $< $@
	$(ECHO) ' '

$(BIN) : $(ELF)
	$(ECHO) 'Creating binary image: $(BIN)'
	$(OBJCOPY) -O binary $< $@
	$(ECHO) ' '

# Memory dump
$(DMP) : $(ELF)
	$(ECHO) 'Creating memory dump: $(DMP)'
	$(OBJDUMP) -x --syms $< > $@
	$(ECHO) ' '

# Extended listing
$(LSS) : $(ELF)
	$(ECHO) 'Creating extended listing: $(LSS)'
	$(OBJDUMP) -S $< > $@
	$(ECHO) ' '

# Linking
$(ELF) : $(OBJS)
	$(ECHO) 'Linking target: $(ELF)'
ifneq ($(USE_CXX), 0)
	$(CXX) $(LD_FLAGS) $(OBJS) $(LD_LIBS) -o $@
else
	$(CC) $(LD_FLAGS) $(OBJS) $(LD_LIBS) -o $@
endif
	$(ECHO) ' '

# C++ files compilation
$(OUT_DIR)%.o : %.$(CXX_EXT)
	$(ECHO) 'Compiling file: $<'
	$(CXX) -c $(CXX_FLAGS) $< -o $@
	$(ECHO) ' '

# C files compilation
$(OUT_DIR)%.o : %.$(C_EXT)
	$(ECHO) 'Compiling file: $<'
	$(CC) -c $(C_FLAGS) $< -o $@
	$(ECHO) ' '

# ASM files compilation
$(OUT_DIR)%.o : %.$(ASM_EXT)
	$(ECHO) 'Assembling file: $<'
	$(AS) -c $(ASM_FLAGS) $< -o $@
	$(ECHO) ' '

make_out_dir :
	$(ECHO) $(OBJS)
	$(MKDIR) $(subst /,,$(OUT_DIR))
	$(MKDIR) $(OUT_DIR)bin
	
print_size :
	$(ECHO) 'Size of modules:'
	$(SIZE) -B -t --common $(OBJS) $(USER_OBJS)
	$(ECHO) ' '
	$(ECHO) 'Size of target .elf file:'
	$(SIZE) -B $(ELF)
	$(ECHO) ' '

clean:
	$(RM) $(subst /,,$(OUT_DIR))

# PHONY targets don't create output files with the same name as target
.PHONY: all clean print_size make_out_dir

#
################################################################################