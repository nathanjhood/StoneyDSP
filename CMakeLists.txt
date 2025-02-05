cmake_minimum_required(VERSION 3.23...3.31 FATAL_ERROR)

# Constants - write to cache!
set(STONEYDSP_SLUG "stoneydsp" CACHE STRING "" FORCE)
set(STONEYDSP_BRAND "stoneydsp" CACHE STRING "" FORCE)

# Temporary - no cache!
set(STONEYDSP_DIR "${CMAKE_CURRENT_LIST_DIR}")

# Include StoneyDSP CMake Modules
list(APPEND CMAKE_MODULE_PATH "${STONEYDSP_DIR}/share/cmake/Modules")
message(STATUS "CMake Module Path: ${CMAKE_MODULE_PATH}")

# Add directory structure
include(GNUInstallDirs)
include(stoneydsp)
include(stoneydsp-version-helpers)
stoneydsp_add_directories()
stoneydsp_git_versions()

# Begin project
project(STONEYDSP
    VERSION "0.0.${STONEYDSP_GIT_COMMIT_COUNT}.${STONEYDSP_GIT_REF_HEAD_SHORT}"
    DESCRIPTION "The StoneyDSP Audio Library."
    HOMEPAGE_URL "https://github.com/StoneyDSP/StoneyDSP"
    LANGUAGES C CXX
)

set(STONEYDSP_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}" CACHE STRING "" FORCE)
set(STONEYDSP_VERSION_MINOR "${PROJECT_VERSION_MINOR}" CACHE STRING "" FORCE)
set(STONEYDSP_VERSION_PATCH "${PROJECT_VERSION_PATCH}" CACHE STRING "" FORCE)
set(STONEYDSP_VERSION_TWEAK "${PROJECT_VERSION_TWEAK}" CACHE STRING "" FORCE)
set(STONEYDSP_VERSION "${PROJECT_VERSION}" CACHE STRING "" FORCE)
stoneydsp_update_version_file()

option(STONEYDSP_EXPERIMENTAL "Use '-DSTONEYDSP_EXPERIMENTAL=ON|OFF' when configuring to toggle this option." OFF)
option(STONEYDSP_BUILD_DOCS "Use '-DSTONEYDSP_BUILD_DOCS=ON|OFF' when configuring to toggle this option." OFF)
option(STONEYDSP_BUILD_CORE "Use '-DSTONEYDSP_BUILD_CORE=ON|OFF' when configuring to toggle this option." ON)
cmake_dependent_option(STONEYDSP_BUILD_SIMD "Use '-DSTONEYDSP_BUILD_SIMD=ON|OFF' when configuring to toggle this option." OFF "STONEYDSP_BUILD_CORE" OFF)
cmake_dependent_option(STONEYDSP_BUILD_TEST "Use '-DSTONEYDSP_BUILD_TEST=ON|OFF' when configuring to toggle this option." OFF "STONEYDSP_IS_TOP_LEVEL;STONEYDSP_BUILD_CORE" OFF)

include(CMakeDependentOption)

#[==============================[stoneydsp::core]==============================]
if(STONEYDSP_BUILD_CORE)
    include(stoneydsp-core)
    stoneydsp_add_core()
endif()

#[===========================[stoneydsp::stoneydsp]===========================]
# 'always-on' target: libstoneydsp
stoneydsp_add_stoneydsp()

#[==============================[stoneydsp::test]==============================]
if(STONEYDSP_BUILD_TEST)
    find_package(Catch2 REQUIRED 3.7.1)
    include(stoneydsp-test)
    stoneydsp_add_test()
endif()

#[===================================[CTest]===================================]
if(STONEYDSP_BUILD_TEST)
    enable_testing()
    include(CTest)
    include(Catch)

    set(CMAKE_CATCH_DISCOVER_TESTS_DISCOVERY_MODE PRE_TEST)
    catch_discover_tests(${STONEYDSP_TEST_TARGET_NAME})
endif()

#[===================================[CPack]===================================]
set(CPACK_PACKAGE_VENDOR "StoneyDSP")
set(CPACK_PACKAGE_VERSION_MAJOR "${STONEYDSP_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${STONEYDSP_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${STONEYDSP_VERSION_PATCH}")
set(CPACK_GENERATOR "ZIP")
set(CPACK_SOURCE_GENERATOR "ZIP")
include(CPack)
