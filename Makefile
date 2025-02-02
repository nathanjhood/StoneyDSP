############################################<<<-Part 1: Initialization and Setup

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# # Allow only one "make -f Makefile2" at a time, but pass parallelism.
# .NOTPARALLEL:

# The shell in which to execute make rules.
SHELL := /bin/sh
ECHO := echo

# Compilers and tools
CC := gcc
CXX := g++
CPP := $(CXX) -E
ASM := $(CXX) -S
AR := ar
LD ?= ld
GDB ?= gdb
OBJCOPY ?= objcopy
CMAKE := cmake
GIT := git
ZIP := ZIP
UNZIP := unzip
XXD := xxd
MD5SUM := md5sum
SHA1SUM := sha1sum
HASH_ALGORITHM ?= $(XXD)
PKG_CONFIG ?= pkg-config

# Get the directory of the Makefile
MAKEFILE_DIR := $(patsubst %/,%,$(dir $(realpath $(firstword $(MAKEFILE_LIST)))))

SOURCES :=
OBJECTS :=
INCLUDES :=

ifdef CROSS_COMPILE
	MACHINE := $(CROSS_COMPILE)
else
	MACHINE ?= $(shell $(CC) -dumpmachine)
endif

ifneq (,$(findstring x86_64-,$(MACHINE)))
	ARCH_X64 := 1
	ARCH_CPU := x64
else ifneq (,$(findstring arm64-,$(MACHINE)))
	ARCH_ARM64 := 1
	ARCH_CPU := arm64
else ifneq (,$(findstring aarch64-,$(MACHINE)))
	ARCH_ARM64 := 1
	ARCH_CPU := arm64
else
$(error Could not determine CPU architecture of $(MACHINE))
endif

ifneq (,$(findstring -darwin,$(MACHINE)))
	ARCH_MAC := 1
	ARCH_OS := mac
else ifneq (,$(findstring -mingw32,$(MACHINE)))
	ARCH_WIN := 1
	ARCH_OS := win
else ifneq (,$(findstring -linux,$(MACHINE)))
	ARCH_LIN := 1
	ARCH_OS := lin
else
$(error Could not determine operating system of $(MACHINE))
endif

ARCH_NAME = $(ARCH_OS)-$(ARCH_CPU)

ifdef ARCH_X64
	TRIPLET_ARCH := x64
	PRESET_ARCH := x64
endif

ifdef ARCH_ARM64
	TRIPLET_ARCH := arm64
	PRESET_ARCH := arm64
endif

ifdef ARCH_WIN
	TRIPLET_OS := mingw-dynamic
	PRESET_OS := windows
endif

ifdef ARCH_LIN
	TRIPLET_OS := linux
	PRESET_OS := linux
endif

ifdef ARCH_MAC
	TRIPLET_OS := osx
	PRESET_OS := osx
endif

# 1. Accepts a 'BUILD_TYPE=' argument when configuring (supports 'debug' or 'release')
# 2. Lookup the 'DEBUG' env var if no 'BUILD_TYPE=' was specified.
# 3. If 'DEBUG' was set, build in 'debug' mode; otherwise, defaults to 'release'.
# 4. Lookup the 'VERBOSE' env var; if set, append '-verbose' to the preset.
ifdef BUILD_TYPE
	PRESET_CONFIG := $(BUILD_TYPE)
else ifdef DEBUG
	PRESET_CONFIG := debug
else
	PRESET_CONFIG := release
endif

ifdef VERBOSE
	PRESET_VERBOSE := -verbose
endif

# The deduced CMake Preset name.
PRESET ?= $(PRESET_ARCH)-$(PRESET_OS)-$(PRESET_CONFIG)$(PRESET_VERBOSE)

# This target reports the automatically-selected CMake Preset to stdout.
preset:
	@echo $(PRESET)
.PHONY: preset

###################################<<<-Part 2: Standards, Flags, and Directories

# Standards
C_STANDARD ?= 14
CXX_STANDARD ?= 14

ifdef USE_GNU_EXTENSIONS
	C_DIALECT := gnu
	CXX_DIALECT := gnu
else
	C_DIALECT := c
	CXX_DIALECT := c++
endif

CFLAGS += -std=$(C_DIALECT)$(C_STANDARD)
CXXFLAGS += -std=$(CXX_DIALECT)$(CXX_STANDARD)

# Optional debugger symbols
ifdef DEBUG
	CPPFLAGS += -g
endif

# -O0: No optimization. This is the default level. It aims for the fastest compilation time and the best debugging experience.
# -O1: Basic optimization. Enables optimizations that do not involve a space-speed tradeoff.
# -O2: Further optimization. More optimizations are enabled that improve performance without significantly increasing the compilation time.
# -O3: Aggressive optimization. It enables more aggressive optimizations that may increase the compilation time but aim to maximize the performance of the generated code.
# -Os: Optimize for size. Enables all -O2 optimizations that do not typically increase code size and enables further optimizations to reduce code size.
# -Ofast: Disregards strict standards compliance for the sake of optimization. Enables all -O3 optimizations along with other aggressive optimizations.
OPTIMIZATION ?= -O0
CPPFLAGS += $(OPTIMIZATION)

# Warnings and errors
CPPFLAGS += -Wall
CPPFLAGS += -Wextra

ifdef DEBUG
	CPPFLAGS += -Wno-unused-parameter
	CPPFLAGS += -Werror
	CPPFLAGS += -pedantic
else ifdef VERBOSE
	CPPFLAGS += -Wno-unused-parameter
	CPPFLAGS += -Werror
	CPPFLAGS += -pedantic
endif

FLAGS += -fPIC

# FLAGS += -save-temps

# CPPFLAGS += -fmacro-prefix-map=$(BUILD_DIR)/include=include
# CPPFLAGS += -fmacro-prefix-map=$(BUILD_DIR)/src=src
# CPPFLAGS += -fmacro-prefix-map=$(BUILD_DIR)/test=test

#############################################<<<-Part 3: Source and Object Files

# Directories
BUILD_DIR := build
DOC_DIR := doc
SRC_DIR := src
TEST_DIR := test
INCLUDE_DIR := $(BUILD_DIR)/include

# Source files
CORE_SRCS := $(wildcard $(SRC_DIR)/stoneydsp/core/core.cpp)
DSP_SRCS := $(wildcard $(SRC_DIR)/stoneydsp/dsp/dsp.cpp)
SIMD_SRCS := $(wildcard $(SRC_DIR)/stoneydsp/simd/simd.cpp)
LIB_SRCS := $(wildcard $(SRC_DIR)/stoneydsp/stoneydsp.cpp)

# Object files
CORE_OBJS := $(CORE_SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/src/%.cpp.o)
DSP_OBJS := $(DSP_SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/src/%.cpp.o)
SIMD_OBJS := $(SIMD_SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/src/%.cpp.o)
LIB_OBJS := $(LIB_SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/src/%.cpp.o)

# Dep files
CORE_DEPS := $(CORE_OBJS:.o=.d)
DSP_DEPS := $(DSP_OBJS:.o=.d)
SIMD_DEPS := $(SIMD_OBJS:.o=.d)
LIB_DEPS := $(LIB_OBJS:.o=.d)

###########################################<<<-Part 4: Feature Flags and Targets

# Library type
BUILD_SHARED ?= 1
ifeq ($(BUILD_SHARED),1)
	DEFINES += -DSTONEYDSP_BUILD_SHARED=$(BUILD_SHARED)
	LIB_EXT := so
	BUILD_SHARED_FLAG := -shared
else
	LIB_EXT := a
	BUILD_SHARED_FLAG :=
endif

# TODO: The macro NDEBUG controls whether assert() statements are active or not.
ifdef DEBUG
	# DEFINES += -DDEBUG # consider Windows MSVC...
	DEFINES += -D_DEBUG
else
	DEFINES += -DNDEBUG
endif

# Feature flags
EXPERIMENTAL ?= 0
BUILD_CORE ?= 1
BUILD_DSP ?= 0
BUILD_SIMD ?= 0

# Always include the library source
SOURCES += $(LIB_SRCS)
OBJECTS += $(LIB_OBJS)
INCLUDES += -I$(INCLUDE_DIR)

ifeq ($(EXPERIMENTAL),1)
	DEFINES += -DSTONEYDSP_EXPERIMENTAL=$(EXPERIMENTAL)
endif
ifeq ($(BUILD_CORE),1)
	SOURCES += $(CORE_SRCS)
	OBJECTS += $(CORE_OBJS)
	DEPS := $(CORE_DEPS)
	DEFINES += -DSTONEYDSP_BUILD_CORE=$(BUILD_CORE)
endif
ifeq ($(BUILD_DSP),1)
	SOURCES += $(DSP_SRCS)
	OBJECTS += $(DSP_OBJS)
	DEPS := $(DSP_DEPS)
	DEFINES += -DSTONEYDSP_BUILD_DSP=$(BUILD_DSP)
endif
ifeq ($(BUILD_SIMD),1)
	SOURCES += $(SIMD_SRCS)
	OBJECTS += $(SIMD_OBJS)
	DEPS := $(SIMD_DEPS)
	DEFINES += -DSTONEYDSP_BUILD_SIMD=$(BUILD_SIMD)
endif

# Optional test objects
ifeq ($(BUILD_TEST),1)
	TEST_TARGET := $(BUILD_DIR)/test/main
	TEST_SRCS := $(wildcard test/catch2session.cpp)
	TEST_OBJS := $(TEST_SRCS:$(TEST_DIR)/%.cpp=$(BUILD_DIR)/test/%.cpp.o)
	TEST_DEPS := $(TEST_OBJS:.o=.d)
	DEFINES += -DSTONEYDSP_BUILD_TEST=$(BUILD_TEST)
endif

##################################<<<-Part 5: Dependencies and submodule targets

GIT_REF ?= $(strip $(shell $(GIT) rev-parse --short HEAD))

STONEYDSP_VERSION_MAJOR ?= 0
STONEYDSP_VERSION_MINOR ?= 0
STONEYDSP_VERSION_PATCH ?= $(strip $(shell $(GIT) rev-list HEAD | wc -l))
STONEYDSP_VERSION_TWEAK ?= $(strip $(shell $(ECHO) -n $(GIT_REF) | $(HASH_ALGORITHM) -p))
STONEYDSP_VERSION_BUILD ?= $(strip $(shell $(GIT) rev-parse --short HEAD))
STONEYDSP_VERSION ?= $(STONEYDSP_VERSION_MAJOR).$(STONEYDSP_VERSION_MINOR).$(STONEYDSP_VERSION_PATCH).$(STONEYDSP_VERSION_TWEAK)

DEFINES += -DSTONEYDSP_VERSION_MAJOR="$(STONEYDSP_VERSION_MAJOR)"
DEFINES += -DSTONEYDSP_VERSION_MINOR="$(STONEYDSP_VERSION_MINOR)"
DEFINES += -DSTONEYDSP_VERSION_PATCH="$(STONEYDSP_VERSION_PATCH)"
DEFINES += -DSTONEYDSP_VERSION_TWEAK="$(STONEYDSP_VERSION_TWEAK)"
DEFINES += -DSTONEYDSP_VERSION="$(STONEYDSP_VERSION)"

version-major:
	@echo $(STONEYDSP_VERSION_MAJOR)
.PHONY: version-major

version-minor:
	@echo $(STONEYDSP_VERSION_MINOR)
.PHONY: version-minor

version-patch:
	@echo $(STONEYDSP_VERSION_PATCH)
.PHONY: version-patch

version-tweak:
	@echo $(STONEYDSP_VERSION_TWEAK)
.PHONY: version-tweak

version-build:
	@echo $(STONEYDSP_VERSION_BUILD)
.PHONY: version-build

version:
	@echo $(STONEYDSP_VERSION)
.PHONY: version

version-package:
	@echo $(STONEYDSP_VERSION_MAJOR).$(STONEYDSP_VERSION_MINOR).$(STONEYDSP_VERSION_PATCH)-r$(STONEYDSP_VERSION_BUILD)
.PHONY: version-package

version-all: version-major version-minor version-patch version-tweak
	@echo $(STONEYDSP_VERSION)
	@echo $(STONEYDSP_VERSION_MAJOR).$(STONEYDSP_VERSION_MINOR).$(STONEYDSP_VERSION_PATCH)-r$(STONEYDSP_VERSION_BUILD)
.PHONY: version-all

./.git/modules:
	$(GIT) submodule update --init --recursive

./.git/modules/dep: ./.git/modules

# Fetch submodules
./.git/modules/dep/vcpkg: ./.git/modules/dep

# Bootstrap vcpkg
./dep/vcpkg/bootstrap-vcpkg.sh: ./.git/modules/dep/vcpkg
	$(GIT) submodule update --init --recursive

# Use vcpkg
./dep/vcpkg/vcpkg: ./dep/vcpkg/bootstrap-vcpkg.sh

# ./dep/vcpkg: ./.git/modules/dep/vcpkg

VCPKG_ROOT ?= ./dep/vcpkg
VCPKG := $(VCPKG_ROOT)/vcpkg

# PKG_CONFIG_PATH += build/vcpkg_installed/$(TRIPLET_ARCH)-$(TRIPLET_OS)/lib/pkgconfig

ifdef DEBUG
	LIB_CATCH := Catch2d
	LIB_CATCH_PATH := build/vcpkg_installed/$(TRIPLET_ARCH)-$(TRIPLET_OS)/debug/lib
	# PKG_CONFIG_PATH +=build/vcpkg_installed/$(TRIPLET_ARCH)-$(TRIPLET_OS)/debug/lib/pkgconfig
else
	LIB_CATCH := Catch2
	LIB_CATCH_PATH := build/vcpkg_installed/$(TRIPLET_ARCH)-$(TRIPLET_OS)/lib
	# PKG_CONFIG_PATH +=build/vcpkg_installed/$(TRIPLET_ARCH)-$(TRIPLET_OS)/lib/pkgconfig
endif

INCLUDES += -Ibuild/vcpkg_installed/$(TRIPLET_ARCH)-$(TRIPLET_OS)/include

ifdef BUILD_TEST
	LDFLAGS += -L$(LIB_CATCH_PATH)
	LDFLAGS += -l$(LIB_CATCH)
endif

###################################<<<-Part 6: CMake and workflow targets

reconfigure: ./dep/vcpkg/vcpkg
	VCPKG_ROOT=$(VCPKG_ROOT) $(CMAKE) \
	--preset $(PRESET) \
	--fresh
.PHONY: reconfigure

configure: ./dep/vcpkg/vcpkg
	VCPKG_ROOT=$(VCPKG_ROOT) $(CMAKE) \
	--preset $(PRESET)
.PHONY: configure

build: configure
	$(CMAKE) \
	--build $(PWD)/build \
	--preset $(PRESET)
.PHONY: build

test: build
	$(CTEST) \
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

workflow: ./dep/vcpkg/vcpkg
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

# # Dependencies
# dep: configure

# .PHONY: dep

############################################<<<-Libraries and executable targets

TARGET := $(BUILD_DIR)/lib/libstoneydsp.$(LIB_EXT)

# Distribution build
$(TARGET): $(OBJECTS)
	@mkdir -p $(dir $@)
	$(CXX) $(BUILD_SHARED_FLAG) $(CPPFLAGS) $(CXXFLAGS) $(FLAGS) $(DEFINES) $(INCLUDES) -o $@ $<

# Test executable
ifdef BUILD_TEST
$(LIB_CATCH_PATH)/lib$(LIB_CATCH).a: configure

catch2: $(LIB_CATCH_PATH)/lib$(LIB_CATCH).a

.PHONY: catch2

$(TEST_TARGET): $(TEST_OBJS) $(TARGET) $(LIB_CATCH_PATH)/lib$(LIB_CATCH).a
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(FLAGS) $(DEFINES) $(INCLUDES) $< $(OBJECTS) test/main.cpp $(LDFLAGS) -o $@

run: $(TEST_TARGET)
	$(TEST_TARGET) $(TEST_ARGS)

.PHONY: run
endif

##################################################<<<-Part 8: Patterns and rules

$(BUILD_DIR)/include: configure
	@echo "Configured CMake"

## <CC>

## '*.c' - Pre-Processor
$(BUILD_DIR)/src/%.c.i: $(SRC_DIR)/%.c $(BUILD_DIR)/include
	@mkdir -p $(dir $@)
	$(CPP) $(CFLAGS) $(CPPFLAGS) $(FLAGS) $(DEFINES) $(INCLUDES) -x c $< -o $@
## '*.c.s' - Assembler
$(BUILD_DIR)/src/%.c.s: $(BUILD_DIR)/src/%.c.i
	@mkdir -p $(dir $@)
	$(ASM) $(CFLAGS) $(CPPFLAGS) $(FLAGS) $(DEFINES) $(INCLUDES) -x c-cpp-output $< -o $@
## '*.c.o' - Compiler
$(BUILD_DIR)/src/%.c.o: $(BUILD_DIR)/src/%.c.s
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(FLAGS) $(DEFINES) $(INCLUDES) -x assembler $< -o $@
# ## '*.cpp.d' - Dependency tracking
# $(BUILD_DIR)/src/%.c.d: $(SRC_DIR)/%.c
# 	@mkdir -p $(dir $@)
# 	$(CC) $(CFLAGS) $(CPPFLAGS) $(FLAGS) $(DEFINES) $(INCLUDES) -x c -MM -MF $@ -MT $(@:.d=.o) $<
# -include $(DEPS)
## <CXX>

## '*.cpp.i' - Pre-Processor
$(BUILD_DIR)/src/%.cpp.i: $(SRC_DIR)/%.cpp $(BUILD_DIR)/include
	@mkdir -p $(dir $@)
	$(CPP) $(CXXFLAGS) $(CPPFLAGS) $(FLAGS) $(DEFINES) $(INCLUDES) -x c++ $< -o $@
## '*.cpp.s' - Assembler
$(BUILD_DIR)/src/%.cpp.s: $(BUILD_DIR)/src/%.cpp.i
	@mkdir -p $(dir $@)
	$(ASM) $(CXXFLAGS) $(CPPFLAGS) $(FLAGS) $(DEFINES) $(INCLUDES) -x c++-cpp-output $< -o $@
## '*.cpp.o' - Compiler
$(BUILD_DIR)/src/%.cpp.o: $(BUILD_DIR)/src/%.cpp.s
	@mkdir -p $(dir $@)
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $(FLAGS) $(DEFINES) $(INCLUDES) -x assembler-with-cpp $< -o $@
# ## '*.cpp.d' - Dependency tracking
# $(BUILD_DIR)/src/%.cpp.d: $(SRC_DIR)/%.cpp
# 	@mkdir -p $(dir $@)
# 	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(FLAGS) $(DEFINES) $(INCLUDES) -x c++ -MM -MF $@ -MT $(@:.d=.o) $<
# -include $(DEPS)

$(BUILD_DIR)/src/%.m.o: $(SRC_DIR)/%.m $(BUILD_DIR)/include
	@mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $(FLAGS) $(DEFINES) $(INCLUDES) $< -o $@


$(BUILD_DIR)/src/%.mm.o: $(SRC_DIR)/%.mm $(BUILD_DIR)/include
	@mkdir -p $(dir $@)
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $(FLAGS) $(DEFINES) $(INCLUDES) $< -o $@

ifdef BUILD_TEST
INCLUDES += -I$(BUILD_DIR)/test

# Pattern rules for test files
$(BUILD_DIR)/test/%.cpp.o: $(TEST_DIR)/%.cpp $(BUILD_DIR)/include
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(FLAGS) $(DEFINES) $(INCLUDES) -c $< -o $@

# # Test entry point depfiles
# $(BUILD_DIR)/test/%.cpp.d: $(TEST_DIR)/%.cpp
# 	@mkdir -p $(dir $@)
# 	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(FLAGS) $(DEFINES) $(INCLUDES) -x c++ -MM -MF $@ -MT $(@:.d=.o) $<
# -include $(TEST_DEPS)
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

##########################################<<<-Part 9: Packaging and distribution

PREFIX ?= /usr/local

install: $(TARGET)
	@mkdir -p $(PREFIX)/lib
	@mkdir -p $(PREFIX)/include/stoneydsp
	@cp $(TARGET) $(PREFIX)/lib/
	@cp -r $(BUILD_DIR)/include/stoneydsp $(PREFIX)/include/
	@echo "StoneyDSP Library and headers installed to $(PREFIX)"

$(BUILD_DIR)/%.html: %.md
	@mkdir -p $(dir $@)
	markdown $< > $@

# Include the doc target
$(BUILD_DIR)/doc/html: configure
	doxygen ./doc/Doxyfile

doc: $(BUILD_DIR)/doc/html
	@mkdir -p $(dir $@)
.PHONY: doc

#############################################<<<-Part 10: Clean, Help, and utils

# default target
all: $(TARGET) $(TEST_TARGET)

# Fetch submodules
submodules:
	$(GIT) submodule update --init --recursive
.PHONY: submodules

DEBUG_FLAGS := -g -O0
RELEASE_FLAGS := -O2

debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(TARGET)

.PHONY: debug

release: CFLAGS += $(RELEASE_FLAGS)
release: $(TARGET)

.PHONY: release

# Clean up build files
clean:
	@rm -rvf $(BUILD_DIR)/include $(BUILD_DIR)/src $(BUILD_DIR)/test $(TARGET) $(TEST_TARGET)

wipe: clean
	@rm -rvf $(BUILD_DIR)

# Help Target
help:
	@echo "The directory of the Makefile is: $(MAKEFILE_DIR)"
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... dep"
	@echo "... catch2"
	@echo "... submodules"
	@echo "... doc"
	@echo "... configure"
	@echo "... build"
	@echo "... test"
	@echo "... run"
	@echo "... install"
	@echo "... package"
	@echo "... package_source"
	@echo "... workflow"
	@echo "... clean"
	@echo "... version"
	@echo "... help"
.PHONY: help

.DEFAULT_TARGET: all
