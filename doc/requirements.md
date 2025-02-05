# requirements

- c11 or later
- c++11 or later
- GNU or Clang toolchain (support for MSVC is planned...)
- CMake
- GNU Make
- GNU Binutils

### optional

- vcpkg (our Makefile checks if you have a `VCPKG_ROOT`, then bootstraps vcpkg as a submodule if necessary)
- Ninja or other CMake generators (only test with Ninja and Unix Makefiles so far)
