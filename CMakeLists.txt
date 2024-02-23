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

# pick up vcpkg toolchain if around (otherwise, find packages locally)...
if (DEFINED ENV{VCPKG_ROOT})
    # global install...
    set (CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE FILEPATH "" FORCE)
elseif (EXISTS "${CMAKE_CURRENT_LIST_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")
    # submodule...
    set (CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_LIST_DIR}/ext/microsoft/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE FILEPATH "" FORCE)
elseif (EXISTS "${CMAKE_CURRENT_LIST_DIR}/ext/microsoft/vcpkg/scripts/buildsystems/vcpkg.cmake")
    # submodule...
    set (CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_LIST_DIR}/ext/microsoft/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE FILEPATH "" FORCE)
endif ()

list (APPEND CMAKE_MODULE_PATH
    "${CMAKE_CURRENT_LIST_DIR}/share/cmake/StoneyDSP"
    "${CMAKE_CURRENT_LIST_DIR}/share/cmake/Modules"
)

# The default build type must be set before project()
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR AND NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

if (NOT DEFINED StoneyDSP_SOURCE_DIR)
    set (StoneyDSP_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}")
endif ()

if (NOT DEFINED StoneyDSP_DIR)
    set (StoneyDSP_DIR "${CMAKE_CURRENT_LIST_DIR}/share/cmake/StoneyDSP")
endif ()

find_package (StoneyDSP 1.0.0 CONFIG REQUIRED)

project (
    StoneyDSP
    VERSION 1.0.0
    DESCRIPTION ""
    HOMEPAGE_URL "https://stoneydsp.com"
    LANGUAGES C;CXX
)

include (CMakeDependentOption)
include (GetGitRef)
include (WriteVersionFile)

stoneydsp_get_git_ref ()

set (StoneyDSP_VERSION_MAJOR 1                                                  CACHE STRING "First version number component of the ``PROJECT_VERSION`` variable as set by the ``project()`` command." FORCE)
set (StoneyDSP_VERSION_MINOR 0                                                  CACHE STRING "Second version number component of the ``PROJECT_VERSION`` variable as set by the ``project()`` command." FORCE)
set (StoneyDSP_VERSION_PATCH 0                                                  CACHE STRING "Third version number component of the ``PROJECT_VERSION`` variable as set by the ``project()`` command." FORCE)
set (StoneyDSP_VERSION_TWEAK "${STONEYDSP_GIT_COMMIT_REF}"                      CACHE STRING "Fourth version number component of the ``PROJECT_VERSION`` variable as set by the ``project()`` command." FORCE)

set (StoneyDSP_VERSION ${StoneyDSP_VERSION_MAJOR}.${StoneyDSP_VERSION_MINOR}.${StoneyDSP_VERSION_PATCH} CACHE STRING "StoneyDSP Version Number." FORCE)

stoneydsp_write_version_file ()

set_property(GLOBAL PROPERTY USE_FOLDERS YES)

set (STONEYDSP_MODULES_DIR "${StoneyDSP_SOURCE_DIR}/modules" CACHE INTERNAL "The path to StoneyDSP modules")

# This option will disable most of the helper functions and tools. This option exists to
# facilitate existing CMake builds which handle things like bundle creation, icons, plists, and
# binary data independently of JUCE. This option is not recommended - use at your own risk!

option(STONEYDSP_MODULES_ONLY "Only configure the StoneyDSP modules" OFF)

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

if(JUCE_MODULES_ONLY)
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

option (STONEYDSP_BUILD_TESTS "Build tests" ON)
if(STONEYDSP_BUILD_TESTS AND (StoneyDSP_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR))
    enable_testing()
    # if(NOT MSVC)
    #     add_compile_options(-Wall -Wextra)
    # endif()
    # add_subdirectory(tests)
endif()

if (StoneyDSP_IS_INSTALLABLE) # StoneyDSP_IS_INSTALLABLE
    set (StoneyDSP_MODULES "")
    list (APPEND StoneyDSP_MODULES
        stoneydsp_core
        stoneydsp_audio
        stoneydsp_graphics
        stoneydsp_web
    )

    file (WRITE "${StoneyDSP_BINARY_DIR}/StoneyDSPConfig.cmake.in" [[
@PACKAGE_INIT@

if(NOT TARGET StoneyDSP::CLI)
    add_executable(StoneyDSP::CLI IMPORTED)
    set_target_properties(StoneyDSP::CLI PROPERTIES
        IMPORTED_LOCATION "@PACKAGE_STONEYDSP_CLI_PATH@")
endif()

# include("${CMAKE_CURRENT_LIST_DIR}/@TARGETS_EXPORT_NAME@.cmake")
check_required_components("@PROJECT_NAME@")

set(STONEYDSP_MODULES_DIR "@PACKAGE_STONEYDSP_MODULE_PATH@" CACHE INTERNAL "The path to STONEYDSP modules")

include(CMakeFindDependencyMacro)

find_package (JUCE 7.0.10 CONFIG REQUIRED)

set(_stoneydsp_modules
    stoneydsp_audio
    stoneydsp_core
    stoneydsp_graphics
)

set(_targets_defined)
set(_targets_expected)

foreach(_stoneydsp_module IN LISTS _stoneydsp_modules)
    list(APPEND _targets_expected ${_stoneydsp_module} StoneyDSP::${_stoneydsp_modules})
    if(TARGET ${_stoneydsp_module})
        list(APPEND _targets_defined ${_stoneydsp_module})
    endif()

    if(TARGET StoneyDSP::${_stoneydsp_module})
        list(APPEND _targets_defined StoneyDSP::${_stoneydsp_module})
    endif()
endforeach()

if("${_targets_defined}" STREQUAL "${_targets_expected}")
    unset(_targets_defined)
    unset(_targets_expected)
    return()
endif()

if(NOT "${_targets_defined}" STREQUAL "")
    message(FATAL_ERROR "Some targets in this export set were already defined.")
endif()

unset(_targets_defined)
unset(_targets_expected)

foreach(_stoneydsp_module IN LISTS _stoneydsp_modules)
    juce_add_module("@PACKAGE_STONEYDSP_MODULE_PATH@/${_stoneydsp_module}" ALIAS_NAMESPACE StoneyDSP)
endforeach()

unset(_stoneydsp_modules)

# # Alias for either shared or static library
# if(NOT TARGET ${PROJECT_NAME}::Shared)
# 	add_library(${PROJECT_NAME}::Shared ALIAS ${PROJECT_NAME}::${LIB_SELECTED})
# endif()
]])

    include(CMakePackageConfigHelpers)
    write_basic_package_version_file(
        "${StoneyDSP_BINARY_DIR}/StoneyDSPConfigVersion.cmake"
        VERSION ${StoneyDSP_VERSION}
        COMPATIBILITY ExactVersion
    )

    set(STONEYDSP_INSTALL_DESTINATION "lib/cmake/StoneyDSP/${StoneyDSP_VERSION}" CACHE STRING "The location, relative to the install prefix, where the StoneyDSP config file will be installed")

    set(STONEYDSP_MODULE_PATH "include/StoneyDSP-${StoneyDSP_VERSION}/modules")
    set(STONEYDSP_UTILS_INSTALL_DIR "${STONEYDSP_INSTALL_DESTINATION}")
    # set(JUCEAIDE_PATH "${JUCE_TOOL_INSTALL_DIR}/${JUCE_JUCEAIDE_NAME}")

    configure_package_config_file(
        "${StoneyDSP_BINARY_DIR}/StoneyDSPConfig.cmake.in"
        "${StoneyDSP_BINARY_DIR}/StoneyDSPConfig.cmake"
        PATH_VARS STONEYDSP_UTILS_INSTALL_DIR STONEYDSP_MODULE_PATH # JUCEAIDE_PATH
        INSTALL_DESTINATION "${STONEYDSP_INSTALL_DESTINATION}"
    )

    set(STONEYDSP_MODULE_PATH "${STONEYDSP_MODULES_DIR}")
    set(STONEYDSP_UTILS_INSTALL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/share/cmake/StoneyDSP")
    # get_target_property(JUCEAIDE_PATH juceaide IMPORTED_LOCATION)
    configure_package_config_file(
        "${StoneyDSP_BINARY_DIR}/StoneyDSPConfig.cmake.in"
        "${StoneyDSP_BINARY_DIR}/StoneyDSPExportConfig.cmake"
        PATH_VARS STONEYDSP_UTILS_INSTALL_DIR STONEYDSP_MODULE_PATH # JUCEAIDE_PATH
        INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
        INSTALL_DESTINATION "${CMAKE_CURRENT_BINARY_DIR}"
    )

    install(FILES
        "${StoneyDSP_BINARY_DIR}/StoneyDSPConfigVersion.cmake"
        "${StoneyDSP_BINARY_DIR}/StoneyDSPConfig.cmake"
        DESTINATION "${STONEYDSP_INSTALL_DESTINATION}"
    )

    include (GNUInstallDirs)
    set (STONEYDSP_INCLUDE_DIR "${CMAKE_INSTALL_INCLUDEDIR}/StoneyDSP" CACHE PATH "StoneyDSP include directory." FORCE)
endif ()
