GIT := git
ZIP := ZIP
UNZIP := unzip

include ./arch.mk

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

STONEYDSP_EXTERNAL_DEPS :=
STONEYDSP_EXTERNAL_DEPS += catch2

PKG_CONFIG_PATH += build/vcpkg_installed/$(TRIPLET_ARCH)-$(TRIPLET_OS)/lib/pkgconfig

ifdef DEBUG
	FLAGS += -Lbuild/vcpkg_installed/$(TRIPLET_ARCH)-$(TRIPLET_OS)/lib/debug
	LIB_CATCH := Catch2d
	LIB_CATCH_PATH := build/vcpkg_installed/$(TRIPLET_ARCH)-$(TRIPLET_OS)/lib/debug
else
	FLAGS += -Lbuild/vcpkg_installed/$(TRIPLET_ARCH)-$(TRIPLET_OS)/lib
	LIB_CATCH := Catch2
	LIB_CATCH_PATH := build/vcpkg_installed/$(TRIPLET_ARCH)-$(TRIPLET_OS)/lib
endif

CFLAGS += -Ibuild/vcpkg_installed/$(TRIPLET_ARCH)-$(TRIPLET_OS)/include
CXXFLAGS += -Ibuild/vcpkg_installed/$(TRIPLET_ARCH)-$(TRIPLET_OS)/include
CPPFLAGS += -Ibuild/vcpkg_installed/$(TRIPLET_ARCH)-$(TRIPLET_OS)/include

# ifdef STONEYDSP_BUILD_TEST
# 	LDFLAGS += -Ibuild/vcpkg_installed/$(TRIPLET_ARCH)-$(TRIPLET_OS)/include
# 	LDFLAGS += -Lbuild/vcpkg_installed/$(TRIPLET_ARCH)-$(TRIPLET_OS)/lib
# 	LDFLAGS += -lCatch2
# endif

# ifneq ($(strip $(shell PKG_CONFIG_PATH=$(PKG_CONFIG_PATH) pkg-config --cflags-only-I $(STONEYDSP_EXTERNAL_DEPS) 2>/dev/null)),)
# 	STONEYDSP_CFLAGS += -isystem $(strip $(shell PKG_CONFIG_PATH=$(PKG_CONFIG_PATH) pkg-config --cflags-only-I $(STONEYDSP_EXTERNAL_DEPS) 2>/dev/null))
# endif
# ifneq ($(strip $(shell PKG_CONFIG_PATH=$(PKG_CONFIG_PATH) pkg-config --cflags-only-other $(STONEYDSP_EXTERNAL_DEPS) 2>/dev/null)),)
# 	STONEYDSP_CFLAGS += -isystem $(strip $(shell PKG_CONFIG_PATH=$(PKG_CONFIG_PATH) pkg-config --cflags-only-other $(STONEYDSP_EXTERNAL_DEPS) 2>/dev/null))
# endif
# ifneq ($(strip $(shell PKG_CONFIG_PATH=$(PKG_CONFIG_PATH) pkg-config --cflags-only-I $(STONEYDSP_EXTERNAL_DEPS) 2>/dev/null)),)
# 	STONEYDSP_CXXFLAGS += -isystem $(strip $(shell PKG_CONFIG_PATH=$(PKG_CONFIG_PATH) pkg-config --cflags-only-I $(STONEYDSP_EXTERNAL_DEPS) 2>/dev/null))
# endif
# ifneq ($(strip $(shell PKG_CONFIG_PATH=$(PKG_CONFIG_PATH) pkg-config --cflags-only-other $(STONEYDSP_EXTERNAL_DEPS) 2>/dev/null)),)
# 	STONEYDSP_CXXFLAGS += -isystem $(strip $(shell PKG_CONFIG_PATH=$(PKG_CONFIG_PATH) pkg-config --cflags-only-other $(STONEYDSP_EXTERNAL_DEPS) 2>/dev/null))
# endif
# ifneq ($(strip $(shell PKG_CONFIG_PATH=$(PKG_CONFIG_PATH) pkg-config --cflags-only-I $(STONEYDSP_EXTERNAL_DEPS) 2>/dev/null)),)
# 	STONEYDSP_CPPFLAGS += -isystem $(strip $(shell PKG_CONFIG_PATH=$(PKG_CONFIG_PATH) pkg-config --cflags-only-I $(STONEYDSP_EXTERNAL_DEPS) 2>/dev/null))
# endif
# ifneq ($(strip $(shell PKG_CONFIG_PATH=$(PKG_CONFIG_PATH) pkg-config --cflags-only-other $(STONEYDSP_EXTERNAL_DEPS) 2>/dev/null)),)
# 	STONEYDSP_CPPFLAGS += -isystem $(strip $(shell PKG_CONFIG_PATH=$(PKG_CONFIG_PATH) pkg-config --cflags-only-other $(STONEYDSP_EXTERNAL_DEPS) 2>/dev/null))
# endif
# ifneq ($(strip $(shell PKG_CONFIG_PATH=$(PKG_CONFIG_PATH) pkg-config --libs-only-l $(STONEYDSP_EXTERNAL_DEPS) 2>/dev/null)),)
# 	STONEYDSP_LDFLAGS += -isystem $(strip $(shell PKG_CONFIG_PATH=$(PKG_CONFIG_PATH) pkg-config --libs-only-l $(STONEYDSP_EXTERNAL_DEPS) 2>/dev/null))
# endif
# ifneq ($(strip $(shell PKG_CONFIG_PATH=$(PKG_CONFIG_PATH) pkg-config --libs-only-L $(STONEYDSP_EXTERNAL_DEPS) 2>/dev/null)),)
# 	STONEYDSP_LDFLAGS += -isystem $(strip $(shell PKG_CONFIG_PATH=$(PKG_CONFIG_PATH) pkg-config --libs-only-L $(STONEYDSP_EXTERNAL_DEPS) 2>/dev/null))
# endif
# ifneq ($(strip $(shell PKG_CONFIG_PATH=$(PKG_CONFIG_PATH) pkg-config --libs-only-other $(STONEYDSP_EXTERNAL_DEPS) 2>/dev/null)),)
# 	STONEYDSP_LDFLAGS += -isystem $(strip $(shell PKG_CONFIG_PATH=$(PKG_CONFIG_PATH) pkg-config --libs-only-other $(STONEYDSP_EXTERNAL_DEPS) 2>/dev/null))
# endif
