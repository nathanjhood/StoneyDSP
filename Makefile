include ./arch.mk

# Compilers and tools
CC := cc
CXX := c++
CPP := cpp
LD := ld
GDB := gdb
OBJCOPY ?= objcopy

include ./flags.mk

# Directories
BUILD_DIR := build
INCLUDE_DIR := $(BUILD_DIR)/include
SRC_DIR := src
TEST_DIR := test

BUILD_SHARED ?= 1

# Library type
ifdef BUILD_SHARED
	LIB_EXT := so
	LIB_FLAGS += -shared
else
	LIB_EXT := a
	LIB_FLAGS +=
endif

# Source files
CORE_SRC := $(wildcard src/stoneydsp/core/core.cpp)
DSP_SRC := $(wildcard src/stoneydsp/dsp/dsp.cpp)
SIMD_SRC := $(wildcard src/stoneydsp/simd/simd.cpp)
LIB_SRC := $(wildcard src/stoneydsp/stoneydsp.cpp)

# Object files
CORE_OBJ := $(CORE_SRC:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/src/%.cpp.o)
DSP_OBJ := $(DSP_SRC:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/src/%.cpp.o)
SIMD_OBJ := $(SIMD_SRC:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/src/%.cpp.o)
LIB_OBJ := $(LIB_SRC:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/src/%.cpp.o)

# Feature flags
ifeq ($(STONEYDSP_BUILD_CORE), 1)
	SOURCES += $(CORE_SRC)
	OBJECTS += $(CORE_OBJ)
	FLAGS += -DSTONEYDSP_BUILD_CORE=$(STONEYDSP_BUILD_CORE)
endif
ifeq ($(STONEYDSP_BUILD_DSP), 1)
	SOURCES += $(DSP_SRC)
	OBJECTS += $(DSP_OBJ)
	FLAGS += -DSTONEYDSP_BUILD_DSP
endif
ifeq ($(STONEYDSP_BUILD_SIMD), 1)
	SOURCES += $(SIMD_SRC)
	OBJECTS += $(SIMD_OBJ)
	FLAGS += -DSTONEYDSP_BUILD_SIMD
endif

# Always include the library source
SOURCES += $(LIB_SRC)
OBJECTS += $(LIB_OBJ)
INCLUDES += -I$(INCLUDE_DIR)

# Test files
ifdef BUILD_TEST
	TEST_SRC := $(wildcard test/main.cpp test/catch2session.cpp)
	TEST_OBJ := $(TEST_SRC:$(TEST_DIR)/%.cpp=$(BUILD_DIR)/test/%.cpp.o)
	FLAGS += -DBUILD_TEST=$(BUILD_TEST)
	OBJECTS += $(TEST_OBJ)
	TEST_TARGET := $(BUILD_DIR)/test/main
endif

# Targets
.PHONY: all clean dep

all: dep libstoneydsp.$(LIB_EXT) $(TEST_TARGET)

include ./version.mk
include ./dep.mk
include ./presets.mk

# These are "main" Makefile targets which most Rack plugin devs expect...

# Dependencies
dep: reconfigure

# Distribution build
libstoneydsp.$(LIB_EXT): $(OBJECTS)
	$(CXX) $(LIB_FLAGS) -o $@ $^

# Test executable
ifdef BUILD_TEST
$(LIB_CATCH_PATH)/lib$(LIB_CATCH).a: $(VCPKG)
	$(VCPKG) install

$(TEST_TARGET): $(TEST_OBJ) libstoneydsp.$(LIB_EXT) $(LIB_CATCH_PATH)/lib$(LIB_CATCH).a
	$(CXX) $(LDFLAGS) -o $@ $^

run: $(TEST_TARGET)
	./$(TEST_TARGET) $(TEST_ARGS)
endif

# Pattern rules for other file extensions
$(BUILD_DIR)/src/%.cpp.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/src/%.cc.o: $(SRC_DIR)/%.cc
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/src/%.c.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/src/%.m.o: $(SRC_DIR)/%.m
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/src/%.mm.o: $(SRC_DIR)/%.mm
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

ifdef BUILD_TEST
# Pattern rules for test files
$(BUILD_DIR)/test/%.cpp.o: $(TEST_DIR)/%.cpp $(LIB_CATCH_PATH)/lib$(LIB_CATCH).a
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -I$(BUILD_DIR)/test -c $< -o $@ $(LIB_CATCH_PATH)/lib$(LIB_CATCH).a
endif

# build/%.bin.o: %
# 	@mkdir -p $(@D)
# ifdef ARCH_LIN
# 	$(OBJCOPY) -I binary -O elf64-x86-64 -B i386:x86-64 --rename-section .data=.rodata,alloc,load,readonly,data,contents $< $@
# endif
# ifdef ARCH_WIN
# 	$(OBJCOPY) -I binary -O pe-x86-64 -B i386:x86-64 --rename-section .data=.rodata,alloc,load,readonly,data,contents $< $@
# endif
# ifdef ARCH_MAC
# 	@# Apple makes this needlessly complicated, so just generate a C file with an array.
# 	xxd -i $< | $(CC) $(MAC_SDK_FLAGS) -c -o $@ -xc -
# endif

build/%.html: %.md
	markdown $< > $@

PREFIX ?= /usr/local

install: libstoneydsp.a
	@mkdir -p $(PREFIX)/lib
	@mkdir -p $(PREFIX)/include/stoneydsp
	@cp libstoneydsp.a $(PREFIX)/lib/
	@cp -r $(BUILD_DIR)/include/stoneydsp $(PREFIX)/include/
	@echo "StoneyDSP Library and headers installed to $(PREFIX)"


# Clean up build files
clean:
	rm -rvf libstoneydsp.$(LIB_EXT) $(TEST_TARGET) $(BUILD_DIR)/src/*.o $(BUILD_DIR)/test/*.o

# clean:
# 	rm -rvf $(BUILD_DIR)/*.o
# 	rm -rvf $(BUILD_DIR)/*.c.o
# 	rm -rvf $(BUILD_DIR)/*.cpp.o
# 	rm -rvf $(BUILD_DIR)/**/*.o
# 	rm -rvf $(BUILD_DIR)/**/*.c.o
# 	rm -rvf $(BUILD_DIR)/**/*.cpp.o
# 	rm -rvf $(BUILD_DIR)/**/**/*.o
# 	rm -rvf $(BUILD_DIR)/**/**/*.c.o
# 	rm -rvf $(BUILD_DIR)/**/**/*.cpp.o
# 	rm -rvf $(BUILD_DIR)/*.d
# 	rm -rvf $(BUILD_DIR)/*.c.d
# 	rm -rvf $(BUILD_DIR)/*.cpp.d
# 	rm -rvf $(BUILD_DIR)/**/*.d
# 	rm -rvf $(BUILD_DIR)/**/*.c.d
# 	rm -rvf $(BUILD_DIR)/**/*.cpp.d
# 	rm -rvf $(BUILD_DIR)/**/**/*.d
# 	rm -rvf $(BUILD_DIR)/**/**/*.c.d
# 	rm -rvf $(BUILD_DIR)/**/**/*.cpp.d
# 	rm -rvf $(TEST_OBJ_DIR)/*.o
# 	rm -rvf $(TEST_OBJ_DIR)/*.c.o
# 	rm -rvf $(TEST_OBJ_DIR)/*.cpp.o
# 	rm -rvf $(TEST_OBJ_DIR)/**/*.o
# 	rm -rvf $(TEST_OBJ_DIR)/**/*.c.o
# 	rm -rvf $(TEST_OBJ_DIR)/**/*.cpp.o
# 	rm -rvf $(TEST_OBJ_DIR)/**/**/*.o
# 	rm -rvf $(TEST_OBJ_DIR)/**/**/*.c.o
# 	rm -rvf $(TEST_OBJ_DIR)/**/**/*.cpp.o
# 	rm -rvf $(TEST_OBJ_DIR)/*.d
# 	rm -rvf $(TEST_OBJ_DIR)/*.c.d
# 	rm -rvf $(TEST_OBJ_DIR)/*.cpp.d
# 	rm -rvf $(TEST_OBJ_DIR)/**/*.d
# 	rm -rvf $(TEST_OBJ_DIR)/**/*.c.d
# 	rm -rvf $(TEST_OBJ_DIR)/**/*.cpp.d
# 	rm -rvf $(TEST_OBJ_DIR)/**/**/*.d
# 	rm -rvf $(TEST_OBJ_DIR)/**/**/*.c.d
# 	rm -rvf $(TEST_OBJ_DIR)/**/**/*.cpp.d
# 	rm -rvf $(OBJ_DIR)/MakeFiles
# 	rm -rvf $(TEST_TARGET)
