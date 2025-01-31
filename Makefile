# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# # Allow only one "make -f Makefile2" at a time, but pass parallelism.
# .NOTPARALLEL:

# The shell in which to execute make rules.
SHELL = /bin/sh

include ./arch.mk

# Compilers and tools
CC := gcc
CXX := g++
CPP := cpp
LD := ld
GDB := gdb
OBJCOPY ?= objcopy
CMAKE := cmake

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
	BUILD_SHARED_FLAG := -shared
else
	LIB_EXT := a
	BUILD_SHARED_FLAG :=
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

# include ./presets.mk
CMAKE := cmake

reconfigure: submodules
	VCPKG_ROOT=$(VCPKG_ROOT) $(CMAKE) \
	--preset $(PRESET) \
	--fresh
.PHONY: reconfigure

configure: submodules
	VCPKG_ROOT=$(VCPKG_ROOT) $(CMAKE) \
	--preset $(PRESET)
.PHONY: configure

build: configure
	$(CMAKE) \
	--build $(PWD)/build \
	--preset $(PRESET)
.PHONY: build

test: build
	ctest \
	--test-dir $(PWD)/build \
	--preset $(PRESET)
.PHONY: test

package: test
	$(CMAKE) \
	--build $(PWD)/build \
	--target $@
.PHONY: package

package_source: test
	$(CMAKE) \
	--build $(PWD)/build \
	--target $@
.PHONY: package_source

workflow: $(VCPKG_ROOT)/vcpkg
	VCPKG_ROOT=$(VCPKG_ROOT) $(CMAKE) \
	--workflow \
	--preset $(PRESET) \
	--fresh
.PHONY: workflow

source: configure
	$(CMAKE) \
	--install $(PWD)/build \
	--prefix $(PWD)/dist \
	--component $@
.PHONY: source

# package: test
# 	$(CMAKE) \
#   --install $(PWD)/build \
# 	--prefix $(PWD)/install

# These are "main" Makefile targets which most Rack plugin devs expect...

# Dependencies
dep: reconfigure

# Distribution build
libstoneydsp.$(LIB_EXT): $(OBJECTS)
	$(CXX) $(BUILD_SHARED_FLAG) -o $@ $^

# Test executable
ifdef BUILD_TEST
$(LIB_CATCH_PATH)/lib$(LIB_CATCH).a: $(VCPKG)
	$(VCPKG) install

$(TEST_TARGET): $(TEST_OBJ) libstoneydsp.$(LIB_EXT) $(LIB_CATCH_PATH)/lib$(LIB_CATCH).a
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

run: $(TEST_TARGET)
	$(TEST_TARGET) $(TEST_ARGS)
.PHONY: run
endif

# Pattern rules for other file extensions
$(BUILD_DIR)/src/%.cpp.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -fPIC -c $< -o $@

$(BUILD_DIR)/src/%.cc.o: $(SRC_DIR)/%.cc
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -fPIC -c $< -o $@

$(BUILD_DIR)/src/%.c.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CXXFLAGS) $(INCLUDES) -fPIC -c $< -o $@

$(BUILD_DIR)/src/%.m.o: $(SRC_DIR)/%.m
	@mkdir -p $(dir $@)
	$(CC) $(CXXFLAGS) $(INCLUDES) -fPIC -c $< -o $@

$(BUILD_DIR)/src/%.mm.o: $(SRC_DIR)/%.mm
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -fPIC -c $< -o $@

ifdef BUILD_TEST
# Pattern rules for test files
$(BUILD_DIR)/test/%.cpp.o: $(TEST_DIR)/%.cpp $(LIB_CATCH_PATH)/lib$(LIB_CATCH).a
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -I$(BUILD_DIR)/test -fPIC -c $< -o $@
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

# Include the docs target
./build/docs/html: configure
	cd docs
	doxygen ./docs/Doxyfile
	cd $(PWD)

docs: $(PWD)/build/docs/html

.PHONY: docs

PREFIX ?= /usr/local

install: libstoneydsp.a
	@mkdir -p $(PREFIX)/lib
	@mkdir -p $(PREFIX)/include/stoneydsp
	@cp libstoneydsp.a $(PREFIX)/lib/
	@cp -r $(BUILD_DIR)/include/stoneydsp $(PREFIX)/include/
	@echo "StoneyDSP Library and headers installed to $(PREFIX)"


# Clean up build files
clean:
	rm -rvf libstoneydsp.$(LIB_EXT) $(TEST_TARGET) $(BUILD_DIR)/src $(BUILD_DIR)/test

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

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... install"
	@echo "... install/local"
	@echo "... install/strip"
	@echo "... list_install_components"
	@echo "... package"
	@echo "... package_source"
	@echo "... rebuild_cache"
	@echo "... catch2session"
	@echo "... core"
	@echo "... test"
	@echo "... src/stoneydsp/stoneydsp.o"
	@echo "... src/stoneydsp/stoneydsp.i"
	@echo "... src/stoneydsp/stoneydsp.s"
	@echo "... test/catch2session.o"
	@echo "... test/catch2session.i"
	@echo "... test/catch2session.s"
	@echo "... test/main.o"
	@echo "... test/main.i"
	@echo "... test/main.s"
.PHONY : help
