#[=============================================================================[
This file is part of the StoneyDSP library.
Copyright (c) 2024 - StoneyDSP
Home: https://www.stoneydsp.com
Source: https://github.com/StoneyDSP/StoneyDSP

StoneyDSP is an open source library subject to open-source licensing.

By using StoneyDSP, you agree to the terms of the StoneyDSP End-User License
Agreement and also the StoneyDSP Privacy Policy.

End User License Agreement: www.stoneydsp.com/LICENSE
Privacy Policy: www.stoneydsp.com/privacy-policy

By using StoneyDSP, you must also agree to the terms of both the JUCE 7 End-User
License Agreement and JUCE Privacy Policy.

End User License Agreement: www.juce.com/juce-7-licence
Privacy Policy: www.juce.com/juce-privacy-policy

Or: You may also use this code under the terms of the GPL v3 (see
www.gnu.org/licenses).

STONEYDSP IS PROVIDED "AS IS" WITHOUT ANY WARRANTY, AND ALL WARRANTIES, WHETHER
EXPRESSED OR IMPLIED, INCLUDING MERCHANTABILITY AND FITNESS FOR PURPOSE, ARE
DISCLAIMED.
]=============================================================================]#

cmake_minimum_required (VERSION 3.22...3.28 FATAL_ERROR)

if (DEFINED ENV{VCPKG_ROOT} AND (NOT DEFINED CMAKE_TOOLCHAIN_FILE))
    set (VCPKG_ROOT $ENV{VCPKG_ROOT} CACHE FILEPATH "Path to vcpkg toolchain." FORCE)
    set (CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE FILEPATH "vcpkg toolchain file." FORCE)
endif ()

# if (DEFINED ENV{STONEYDSP_CI})
#     include ("${CMAKE_CURRENT_LIST_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")
# endif ()

list (APPEND CMAKE_MODULE_PATH
    "${CMAKE_CURRENT_LIST_DIR}/share/cmake/Modules"
)

message (STATUS "StoneyDSP CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")
message (STATUS "StoneyDSP CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")
message (STATUS "StoneyDSP CMAKE_TOOLCHAIN_FILE: ${CMAKE_TOOLCHAIN_FILE}")

# The default build type must be set before project()
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR AND NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

if (NOT DEFINED JUCE_VERSION)
    find_package (JUCE CONFIG REQUIRED)
endif ()

project (
    StoneyDSP
    VERSION 0.0.1
    DESCRIPTION "The StoneyDSP library for JUCE."
    HOMEPAGE_URL "https://github.com/StoneyDSP/StoneyDSP/blob/production/README.md"
    LANGUAGES C;CXX
)

message (STATUS "StoneyDSP CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")
execute_process (COMMAND ${CMAKE_COMMAND} -E cat ${CMAKE_BINARY_DIR}/*)
message (STATUS "StoneyDSP CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}/vcpkg_installed")
execute_process (COMMAND ${CMAKE_COMMAND} -E cat ${CMAKE_BINARY_DIR}/vcpkg_installed/*)
message (STATUS "StoneyDSP CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}/vcpkg_installed/${VCPKG_TARGET_TRIPLET}")
execute_process (COMMAND ${CMAKE_COMMAND} -E cat ${CMAKE_BINARY_DIR}/vcpkg_installed/${VCPKG_TARGET_TRIPLET}/*)


include (CMakeDependentOption)
include (GetGitRef)
include (WriteVersionFile)

stoneydsp_get_git_ref ()

set (StoneyDSP_VERSION_TWEAK "${STONEYDSP_GIT_COMMIT_REF}"                      CACHE STRING "Fourth version number component of the ``PROJECT_VERSION`` variable as set by the ``project()`` command." FORCE)

stoneydsp_write_version_file ()

set_property(GLOBAL PROPERTY USE_FOLDERS YES)

set (STONEYDSP_MODULES_DIR "${StoneyDSP_SOURCE_DIR}/modules" CACHE INTERNAL "The path to StoneyDSP modules")

# This option will disable most of the helper functions and tools. This option exists to
# facilitate existing CMake builds which handle things like bundle creation, icons, plists, and
# binary data independently of JUCE. This option is not recommended - use at your own risk!

option(STONEYDSP_MODULES_ONLY "Only configure the StoneyDSP modules" OFF)

include(extras/Build/CMake/StoneyDSPModuleSupport.cmake)

# This option controls whether dummy targets are added to the build, where these targets contain all
# of the source files for each JUCE module. If you're planning to use an IDE and want to be able to
# browse all of JUCE's source files, this may be useful. However, it will increase the size of
# generated IDE projects and might slow down configuration a bit. If you enable this, you should
# probably also add `set_property(GLOBAL PROPERTY USE_FOLDERS YES)` to your top level CMakeLists,
# otherwise the module sources will be added directly to the top level of the project, instead of in
# a nice 'Modules' subfolder.

cmake_dependent_option(STONEYDSP_ENABLE_MODULE_SOURCE_GROUPS
    "Show all module sources in IDE projects" OFF
    "NOT STONEYDSP_MODULES_ONLY" OFF
)

add_subdirectory(modules)

if(STONEYDSP_MODULES_ONLY)
    return()
endif()

set_directory_properties (PROPERTIES
    StoneyDSP_COMPANY_NAME       "StoneyDSP"
    StoneyDSP_COMPANY_WEBSITE    "https://stoneydsp.com"
    StoneyDSP_COMPANY_EMAIL      "nathanjhood@googlemail.com"
    StoneyDSP_COMPANY_COPYRIGHT  "Copyright (c) 2024 - Nathan J. Hood"
)

add_subdirectory(extras/Build)

option(STONEYDSP_BUILD_EXTRAS "Add build targets for the other StoneyDSP tools" OFF)

if(STONEYDSP_BUILD_EXTRAS)
    add_subdirectory(extras)
endif()

option(STONEYDSP_BUILD_EXAMPLES "Add build targets for the StoneyDSP example projects" OFF)

if(STONEYDSP_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# ==================================================================================================
# Test configuration

option (STONEYDSP_BUILD_TESTS "Build tests" ON)
if(STONEYDSP_BUILD_TESTS AND (StoneyDSP_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR))
    enable_testing()
    # if(NOT MSVC)
    #     add_compile_options(-Wall -Wextra)
    # endif()
    # add_subdirectory(tests)
endif()

# ==================================================================================================
# Install configuration

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${StoneyDSP_BINARY_DIR}/StoneyDSPConfigVersion.cmake"
    VERSION ${StoneyDSP_VERSION}
    COMPATIBILITY ExactVersion
)

set(STONEYDSP_INSTALL_DESTINATION "lib/cmake/StoneyDSP-v${StoneyDSP_VERSION}" CACHE STRING "The location, relative to the install prefix, where the StoneyDSP config file will be installed")

set(STONEYDSP_MODULE_PATH "include/StoneyDSP-v${StoneyDSP_VERSION}/modules")
set(STONEYDSP_UTILS_INSTALL_DIR "${STONEYDSP_INSTALL_DESTINATION}")
# set(JUCEAIDE_PATH "${JUCE_TOOL_INSTALL_DIR}/${JUCE_JUCEAIDE_NAME}")
set(STONEYDSP_STONEYHELPER_PATH "${STONEYDSP_TOOL_INSTALL_DIR}/${STONEYDSP_STONEYHELPER_NAME}")

configure_package_config_file(
    "${STONEYDSP_CMAKE_UTILS_DIR}/StoneyDSPConfig.cmake.in"
    "${StoneyDSP_BINARY_DIR}/StoneyDSPConfig.cmake"
    PATH_VARS STONEYDSP_UTILS_INSTALL_DIR STONEYDSP_MODULE_PATH STONEYDSP_STONEYHELPER_PATH
    INSTALL_DESTINATION "${STONEYDSP_INSTALL_DESTINATION}"
)

set(STONEYDSP_MODULE_PATH "${STONEYDSP_MODULES_DIR}")
set(STONEYDSP_UTILS_INSTALL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/extras/Build/CMake")
# get_target_property(JUCEAIDE_PATH juceaide IMPORTED_LOCATION)
get_target_property(STONEYDSP_STONEYHELPER_PATH stoneyhelper IMPORTED_LOCATION)
configure_package_config_file(
    "${STONEYDSP_CMAKE_UTILS_DIR}/StoneyDSPConfig.cmake.in"
    "${StoneyDSP_BINARY_DIR}/StoneyDSPExportConfig.cmake"
    PATH_VARS STONEYDSP_UTILS_INSTALL_DIR STONEYDSP_STONEYHELPER_PATH STONEYDSP_MODULE_PATH # JUCEAIDE_PATH
    INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
    INSTALL_DESTINATION "${CMAKE_CURRENT_BINARY_DIR}"
)

install(FILES
    "${StoneyDSP_BINARY_DIR}/StoneyDSPConfigVersion.cmake"
    "${StoneyDSP_BINARY_DIR}/StoneyDSPConfig.cmake"
    "${STONEYDSP_CMAKE_UTILS_DIR}/CMakeRC.cmake"
    "${STONEYDSP_CMAKE_UTILS_DIR}/JoinPaths.cmake"
    DESTINATION "${STONEYDSP_INSTALL_DESTINATION}"
)

# offer a basic/messy CPack

# set(CPACK_PACKAGE_CHECKSUM "${PROJECT_VERSION_TWEAK}") # git rev-parse is a good idea for this...
set(CPACK_PACKAGE_VENDOR "StoneyDSP")
set(CPACK_PACKAGE_NAME              "${PROJECT_NAME}-${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}-JUCE_${JUCE_VERSION}")
set(CPACK_PACKAGE_FILE_NAME         "${PROJECT_NAME}-${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}-JUCE_${JUCE_VERSION}") # Multi-platform CMake API distribution
set(CPACK_SOURCE_PACKAGE_FILE_NAME  "${PROJECT_NAME}-${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}-Source") # No system spec as this is un-compiled source file distribution (i.e., the Javascript API)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${PROJECT_DESCRIPTION})
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_VERSION_PATCH})
set(CPACK_PACKAGE_VERSION_TWEAK ${PROJECT_VERSION_VERSION_TWEAK})
set(CPACK_RESOURCE_FILE_LICENSE ${PROJECT_SOURCE_DIR}/LICENSE)
set(CPACK_RESOURCE_FILE_README  ${PROJECT_SOURCE_DIR}/README.md)
set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY ON)
set(CPACK_COMPONENT_INCLUDE_TOPLEVEL_DIRECTORY ON)
set(CPACK_SOURCE_GENERATOR "TGZ;ZIP") # Check out CPack's 'NSIS' installer for Win32, and the others!
set(CPACK_SOURCE_IGNORE_FILES
    _CPack_Packages
    /*.zip
    /*.tar
    /*.tar.*
    /.env*
    /.git/*
    /.bak
    /.cmake
    /.github
    /.vs
    /.vscode
    /.cache
    /.config
    /.local
    /dist
    /_layouts
    /doc
    /docs
    #/bin
    #/lib
    /usr
    /out
    #/build
    /Release
    /Debug
    /MinSizeRel
    /RelWithDebInfo
    /downloads
    /packages
    /installed
    /install
    /node_modules
    /vcpkg
    /vcpkg_installed
    /.*build.*
    /package-lock.json
    /yarn.lock
    /\\\\.DS_Store
)
include(CPack)
