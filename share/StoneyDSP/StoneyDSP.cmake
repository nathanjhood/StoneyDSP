#[=============================================================================[
  StoneyDSP.cmake
  Copyright (C) 2024 Nathan J. Hood
  MIT License
  See: https://github.com/StoneyDSP/StoneyDSP
]=============================================================================]#

#[=============================================================================[
Check whether we have already been included (borrowed from CMakeRC)
]=============================================================================]#
set(_stoneydsp_cmake_version 1.0.0)

cmake_minimum_required(VERSION 3.15)
cmake_policy(VERSION 3.15)
include(CMakeParseArguments)
include(GNUInstallDirs)
include(CMakeDependentOption)

if(COMMAND stoneydsp_add_sources)
    if(NOT DEFINED _STONEYDSP_VERSION OR NOT (_stoneydsp_cmake_version STREQUAL _STONEYDSP_VERSION))
        message(WARNING "More than one 'StoneyDSP.cmake' version has been included in this project.")
    endif()
    # StoneyDSP.cmake has already been included! Don't do anything
    return()
endif()

set(_STONEYDSP_VERSION "${_stoneydsp_cmake_version}" CACHE INTERNAL "Current 'StoneyDSP.cmake' version. Used for checking for conflicts")
set(_STONEYDSP_SCRIPT  "${CMAKE_CURRENT_LIST_FILE}"  CACHE INTERNAL "Path to current 'StoneyDSP.cmake' script")

if(NOT DEFINED _STONEYDSP_JUCE_VERSION)
    set(_STONEYDSP_JUCE_VERSION 7.0.10 CACHE INTERNAL "Current 'StoneyDSP.cmake' JUCE version.")
endif()

message (STATUS "\n-- StoneyDSP.cmake v${_STONEYDSP_VERSION}")

#[=============================================================================[
 FUNCTIONS & MACROS
]=============================================================================]#

#[=============================================================================[
Calls ```find_package(JUCE ${VERSION} CONFIG REQUIRED)```.
]=============================================================================]#
macro(stoneydsp_find_juce _stoneydsp_juce_version)
    # Do some validation...
    find_package (JUCE ${_stoneydsp_juce_version} CONFIG REQUIRED)
endmacro()

#[=============================================================================[
Internal helper (borrowed from CMakeRC).
]=============================================================================]#
function(_stoneydsp_normalize_path var)
    set(path "${${var}}")
    file(TO_CMAKE_PATH "${path}" path)
    while(path MATCHES "//")
        string(REPLACE "//" "/" path "${path}")
    endwhile()
    string(REGEX REPLACE "/+$" "" path "${path}")
    set("${var}" "${path}" PARENT_SCOPE)
endfunction()

#[=============================================================================[
 DEPENDENCIES
]=============================================================================]#

# if (EXISTS "${CMAKE_CURRENT_LIST_DIR}/ext/juce-framework/JUCE/CMakeLists.txt")
if (TRUE)
    stoneydsp_find_juce(${_STONEYDSP_JUCE_VERSION})
endif ()

#[=============================================================================[
 MODULES
]=============================================================================]#

juce_add_module(
    # StoneyDSP::stoneydsp_core
    "${STONEYDSP_DIR}/modules/stoneydsp_core"
    ALIAS_NAMESPACE StoneyDSP
    INSTALL_PATH "include/StoneyDSP-${STONEYDSP_VERSION}/modules"
)
juce_add_module(
    # StoneyDSP::stoneydsp_audio
    "${STONEYDSP_DIR}/modules/stoneydsp_audio"
    ALIAS_NAMESPACE StoneyDSP
    INSTALL_PATH "include/StoneyDSP-${STONEYDSP_VERSION}/modules"
)
juce_add_module(
    # StoneyDSP::stoneydsp_graphics
    "${STONEYDSP_DIR}/modules/stoneydsp_graphics"
    ALIAS_NAMESPACE StoneyDSP
    INSTALL_PATH "include/StoneyDSP-${STONEYDSP_VERSION}/modules"
)
juce_add_module(
    # StoneyDSP::stoneydsp_web
    "${STONEYDSP_DIR}/modules/stoneydsp_web"
    ALIAS_NAMESPACE StoneyDSP
    INSTALL_PATH "include/StoneyDSP-${STONEYDSP_VERSION}/modules"
)

#[=============================================================================[
 CLEANUP
]=============================================================================]#

unset(_stoneydsp_cmake_version)
