include ./arch.mk

CMAKE := cmake

reconfigure: submodules
	VCPKG_ROOT=$(VCPKG_ROOT) $(CMAKE) \
	--preset $(PRESET) \
	--fresh

configure: submodules
	VCPKG_ROOT=$(VCPKG_ROOT) $(CMAKE) \
	--preset $(PRESET)

.PHONY: configure reconfigure

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

# Include the docs target
./build/docs/html: configure
	cd docs
	doxygen ./docs/Doxyfile
	cd $(PWD)

docs: $(PWD)/build/docs/html

.PHONY: docs

# These are "main" Makefile targets which most Rack plugin devs expect
dep: reconfigure

.PHONY: dep
