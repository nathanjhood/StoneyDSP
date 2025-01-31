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

# Targets
.PHONY: all clean dep

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

CFLAGS += -std=c$(C_STANDARD)
CXXFLAGS += -std=c++$(CXX_STANDARD)

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

CPPFLAGS += -MMD
CPPFLAGS += -MP

FLAGS += -fPIC

# Directories
BUILD_DIR := build
DOC_DIR := doc
SRC_DIR := src
TEST_DIR := test
INCLUDE_DIR := $(BUILD_DIR)/include

#############################################<<<-Part 3: Source and Object Files

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

ifeq ($(EXPERIMENTAL),1)
	DEFINES += -DSTONEYDSP_EXPERIMENTAL=$(EXPERIMENTAL)
endif
ifeq ($(BUILD_CORE),1)
	SOURCES += $(CORE_SRC)
	OBJECTS += $(CORE_OBJ)
	DEFINES += -DSTONEYDSP_BUILD_CORE=$(BUILD_CORE)
endif
ifeq ($(BUILD_DSP),1)
	SOURCES += $(DSP_SRC)
	OBJECTS += $(DSP_OBJ)
	DEFINES += -DSTONEYDSP_BUILD_DSP=$(BUILD_DSP)
endif
ifeq ($(BUILD_SIMD),1)
	SOURCES += $(SIMD_SRC)
	OBJECTS += $(SIMD_OBJ)
	DEFINES += -DSTONEYDSP_BUILD_SIMD=$(BUILD_SIMD)
endif
ifeq ($(BUILD_TEST),1)
	TEST_TARGET := $(BUILD_DIR)/test/main
	TEST_SRC := $(wildcard test/main.cpp test/catch2session.cpp)
	TEST_OBJ := $(TEST_SRC:$(TEST_DIR)/%.cpp=$(BUILD_DIR)/test/%.cpp.o)
	OBJECTS += $(TEST_OBJ)
	DEFINES += -DSTONEYDSP_BUILD_TEST=$(BUILD_TEST)
endif

# Always include the library source
SOURCES += $(LIB_SRC)
OBJECTS += $(LIB_OBJ)
INCLUDES += -I$(INCLUDE_DIR)

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


# Fetch submodules
submodules:
	$(shell $(GIT) submodule update --init --recursive)
.PHONY: submodules

# Fetch vcpkg
./dep/vcpkg: submodules

# Bootstrap vcpkg
./dep/vcpkg/bootstrap-vcpkg.sh: ./dep/vcpkg

# Use vcpkg
./dep/vcpkg/vcpkg: ./dep/vcpkg/bootstrap-vcpkg.sh

.PHONY: ./dep/vcpkg ./dep/vcpkg/bootstrap-vcpkg.sh ./dep/vcpkg/vcpkg

VCPKG_ROOT ?= ./dep/vcpkg
VCPKG := $(VCPKG_ROOT)/vcpkg

# PKG_CONFIG_PATH += build/vcpkg_installed/$(TRIPLET_ARCH)-$(TRIPLET_OS)/lib/pkgconfig

ifdef DEBUG
	LDFLAGS += -Lbuild/vcpkg_installed/$(TRIPLET_ARCH)-$(TRIPLET_OS)/lib/debug
	LIB_CATCH := Catch2d
	LIB_CATCH_PATH := build/vcpkg_installed/$(TRIPLET_ARCH)-$(TRIPLET_OS)/lib/debug
else
	LDFLAGS += -Lbuild/vcpkg_installed/$(TRIPLET_ARCH)-$(TRIPLET_OS)/lib
	LIB_CATCH := Catch2
	LIB_CATCH_PATH := build/vcpkg_installed/$(TRIPLET_ARCH)-$(TRIPLET_OS)/lib
endif

INCLUDES += -Ibuild/vcpkg_installed/$(TRIPLET_ARCH)-$(TRIPLET_OS)/include

ifdef BUILD_TEST
	LDFLAGS += -L$(LIB_CATCH_PATH)
	LDFLAGS += -lCatch2
endif

###################################<<<-Part 6: CMake and workflow targets

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

####################################<<<-Part 7: Libraries and executable targets

# Distribution build
libstoneydsp.$(LIB_EXT): $(OBJECTS)
	$(CXX) $(BUILD_SHARED_FLAG) -o $@ $^

# Test executable
ifdef BUILD_TEST
$(LIB_CATCH_PATH)/lib$(LIB_CATCH).a: dep
# .PHONY: $(LIB_CATCH_PATH)/lib$(LIB_CATCH).a

$(TEST_TARGET): $(TEST_OBJ) libstoneydsp.$(LIB_EXT) $(LIB_CATCH_PATH)/lib$(LIB_CATCH).a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(FLAGS) $(DEFINES) $^ $(LDFLAGS) -o $@

run: $(TEST_TARGET)
	$(TEST_TARGET) $(TEST_ARGS)
.PHONY: run
endif

##################################################<<<-Part 8: Patterns and rules

# Pattern rules for other file extensions
$(BUILD_DIR)/src/%.cpp.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(FLAGS) $(DEFINES) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/src/%.cc.o: $(SRC_DIR)/%.cc
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(FLAGS) $(DEFINES) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/src/%.c.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(FLAGS) $(DEFINES) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/src/%.m.o: $(SRC_DIR)/%.m
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(FLAGS) $(DEFINES) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/src/%.mm.o: $(SRC_DIR)/%.mm
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(FLAGS) $(DEFINES) $(INCLUDES) -c $< -o $@

ifdef BUILD_TEST
# Pattern rules for test files
$(BUILD_DIR)/test/%.cpp.o: $(TEST_DIR)/%.cpp $(LIB_CATCH_PATH)/lib$(LIB_CATCH).a
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(FLAGS) $(DEFINES) -I$(BUILD_DIR)/test $(INCLUDES) -c $< -o $@
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

##########################################<<<-Part 9: Packaging and distribution

PREFIX ?= /usr/local

install: libstoneydsp.a
	@mkdir -p $(PREFIX)/lib
	@mkdir -p $(PREFIX)/include/stoneydsp
	@cp libstoneydsp.a $(PREFIX)/lib/
	@cp -r $(BUILD_DIR)/include/stoneydsp $(PREFIX)/include/
	@echo "StoneyDSP Library and headers installed to $(PREFIX)"

#############################################<<<-Part 10: Clean, Help, and utils

# default target
all: dep libstoneydsp.$(LIB_EXT) $(TEST_TARGET)

.DEFAULT_TARGET: all

# Clean up build files
clean:
	rm -rvf libstoneydsp.$(LIB_EXT) $(TEST_TARGET) $(BUILD_DIR)/src $(BUILD_DIR)/test

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... dep"
	@echo "... run"
	@echo "... install"
	@echo "... package"
	@echo "... package_source"
.PHONY : help
