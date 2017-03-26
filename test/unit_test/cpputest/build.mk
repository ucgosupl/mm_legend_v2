################################################################################
#
# Script for compiling CppUTest framework on PC. As a result static library
# libcpputest.a is created.
#
################################################################################

include ../../../makefiles/toolchain_pc.mk
include ../../../makefiles/platform.mk

################################################################################
# File paths defines

C_EXT := c
C_SRC := $(wildcard $(addsuffix /*.$(C_EXT), $(SRC_DIRS)))
OBJS := $(addprefix $(OUT_DIR), $(patsubst %.$(C_EXT),%.o,$(notdir $(C_SRC))))

CPP_EXT := cpp
CPP_SRC := $(wildcard $(addsuffix /*.$(CPP_EXT), $(SRC_DIRS)))
OBJS += $(addprefix $(OUT_DIR), $(patsubst %.$(CPP_EXT),%.o,$(notdir $(CPP_SRC))))

VPATH := $(sort $(INC_DIRS) $(SRC_DIRS))

#
################################################################################

################################################################################
# Compiler and linker defines

# Currently no special flags for CppUTest compilation
C_FLAGS := -std=gnu89 -O0 -g
C_INC_FLAGS := $(patsubst %, -I%, $(INC_DIRS))
C_FLAGS += $(C_INC_FLAGS)

# Currently no special flags for CppUTest compilation
CPP_FLAGS := -std=gnu++11 -O0 -g
CPP_INC_FLAGS := $(patsubst %, -I%, $(INC_DIRS))
CPP_FLAGS += $(CPP_INC_FLAGS)

#
################################################################################

################################################################################
# Targets

all: out_dir $(OUT_DIR)lib/lib$(TARGET_NAME).a

$(OUT_DIR)lib/lib$(TARGET_NAME).a : $(OBJS)
	$(ECHO) 'Making static lib: $@'
	$(AR) -rcs $@ $^
	$(ECHO) ' '

$(OUT_DIR)%.o : %.$(CPP_EXT)
	$(ECHO) 'Compiling file: $<'
	$(CPP) -c $(CPP_FLAGS) $< -o $@
	$(ECHO) ' '
	
$(OUT_DIR)%.o : %.$(C_EXT)
	$(ECHO) 'Compiling file: $<'
	$(CC) -c $(C_FLAGS) $< -o $@
	$(ECHO) ' '
	
out_dir :
	$(MKDIR) $(subst /,,$(OUT_DIR))
	$(MKDIR) $(OUT_DIR)lib

clean :
	$(RM) $(subst /,,$(OUT_DIR))
	$(RM) $(OUT_DIR)lib