###############################################################################
#
# Script file for building unit tests on PC. This script is universal for every
# PC test. Each tests contains conf.mk file containing test specific defines.
#
###############################################################################

include ../../../makefiles/toolchain_pc.mk
include ../../../makefiles/platform.mk
include ../../../makefiles/funs.mk

###############################################################################
# Files and paths defines

C_EXT := c
C_CODE_SRC := $(call rwildcard,$(SRC_DIRS),*.$(C_EXT)) $(C_SRC_FILES)
C_TEST_SRC := $(call rwildcard,$(TEST_SRC_DIRS),*.$(C_EXT)) $(TEST_SRC_FILES)

C_CODE_SRC := $(filter-out $(C_SRC_EXCLUDE), $(C_CODE_SRC))
C_TEST_SRC := $(filter-out $(C_SRC_EXCLUDE), $(C_TEST_SRC))

CPP_EXT := cpp
CPP_TEST_SRC := $(call rwildcard,$(TEST_SRC_DIRS),*.$(CPP_EXT)) $(CPP_TEST_SRC_FILES)
CPP_TEST_SRC := $(filter-out $(CPP_SRC_EXCLUDE), $(CPP_TEST_SRC))

CODE_OBJ := $(addprefix $(OUT_DIR)code/, $(sort $(notdir $(C_CODE_SRC:.$(C_EXT)=.o))))
TEST_OBJ := $(addprefix $(OUT_DIR)test/, $(sort $(notdir $(C_TEST_SRC:.$(C_EXT)=.o))))

TEST_OBJ += $(addprefix $(OUT_DIR)test/, $(sort $(notdir $(CPP_TEST_SRC:.$(CPP_EXT)=.o))))

OBJS := $(CODE_OBJ) $(TEST_OBJ)

DEPS := $(OBJS:.$.o=.d)

VPATH := $(sort $(dir $(C_TEST_SRC) $(C_CODE_SRC)) $(dir $(CPP_TEST_SRC)) $(TEST_INC_DIRS))
#
###############################################################################

###############################################################################
# Compiler and linker defines

# Code under tests is compiled with extended warning flags
C_FLAGS_CODE := -std=gnu89 -O0 -Wall -Wextra -Wstrict-prototypes -MMD
# Test files are compiled with only standard flags set
C_FLAGS_TEST := -std=gnu89 -O0 -Wall -MMD

CPP_FLAGS_TEST := -std=gnu++11 -O0 -Wall -MMD

# Include paths
INC_FLAGS_CODE := $(patsubst %, -I%, $(INC_DIRS))
INC_FLAGS_TEST := -I. $(patsubst %, -I%, $(TEST_INC_DIRS))

# Global defines
GLOBAL_DEFS_F = $(patsubst %, -D%, $(GLOBAL_DEFS))

# Compiler flags
C_FLAGS_CODE += $(GLOBAL_DEFS_F) $(INC_FLAGS_CODE) -g
C_FLAGS_TEST += $(GLOBAL_DEFS_F) $(INC_FLAGS_CODE) $(INC_FLAGS_TEST) -g
CPP_FLAGS_TEST += $(GLOBAL_DEFS_F) $(INC_FLAGS_CODE) $(INC_FLAGS_TEST) -g

# Linker flags
LD_FLAGS := -Wl,-Map=$(OUT_DIR)bin/$(TARGET_NAME).map -Wl,--gc-sections
LD_LIBS := -L$(LIB_DIRS) -l$(LIBS)

#
###############################################################################

###############################################################################
# Targets

all: init out_dir $(OUT_DIR)bin/$(TARGET_NAME) run

run:
	@rm -rf test_results.txt
	$(ECHO) 'Running tests for $(TARGET_NAME)'
	$(ECHO) ''
	$(ECHO) 'Date and time:'
	@date +'%y.%m.%d %H:%M:%S'
	$(ECHO) ''
	-$(OUT_DIR)bin/$(TARGET_NAME)
	$(ECHO) ''

# Creating resulting binary file
$(OUT_DIR)bin/$(TARGET_NAME) : $(TEST_OBJ) $(CODE_OBJ)
	@echo 'Linking target: $(OUT_DIR)bin/$(TARGET_NAME)'
	$(CPP) $(LD_FLAGS) $(TEST_OBJ) $(CODE_OBJ) $(LD_LIBS) -o $@
	@echo ''

# Pattern for test files compilation
$(OUT_DIR)test/%.o : %.$(CPP_EXT)
	@echo 'Compiling file: $<'
	$(CPP) -c $(CPP_FLAGS_TEST) $< -o $@
	@echo ''

# Pattern for code under test compilation
$(OUT_DIR)code/%.o : %.$(C_EXT)
	@echo 'Compiling file: $<'
	$(CC) -c $(C_FLAGS_CODE) $< -o $@
	@echo ''

# Pattern for test files compilation
$(OUT_DIR)test/%.o : %.$(C_EXT)
	@echo 'Compiling file: $<'
	$(CC) -c $(C_FLAGS_TEST) $< -o $@
	@echo ''

# header dependencies
-include $(DEPS)

out_dir :
	@mkdir -p $(OUT_DIR)bin
	@mkdir -p $(OUT_DIR)code
	@mkdir -p $(OUT_DIR)test

init :
	@echo ''
	@echo 'Building $(TARGET_NAME) PC unit tests:'
	@echo 'SRC files under test:'
	@echo $(C_CODE_SRC)
	@echo 'Test file sources:'
	@echo $(C_TEST_SRC)
	@echo 'Test file .cpp sources:'
	@echo $(CPP_TEST_SRC)
	@echo ''

clean:
	@rm -rf $(subst /,,$(OUT_DIR))
