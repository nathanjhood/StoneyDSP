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

# Include deps
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

ifdef BUILD_TYPE
	PRESET_CONFIG := $(BUILD_TYPE)
else
	ifdef DEBUG
		PRESET_CONFIG := debug
	else
		PRESET_CONFIG := release
	endif
endif

ifdef VERBOSE
	PRESET_VERBOSE := -verbose
endif

PRESET ?= $(PRESET_ARCH)-$(PRESET_OS)-$(PRESET_CONFIG)$(PRESET_VERBOSE)
