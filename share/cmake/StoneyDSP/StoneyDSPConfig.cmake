#[=============================================================================[
StoneyDSPConfig.cmake
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

####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was StoneyDSPConfig.cmake.in                    ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../../" ABSOLUTE)

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

macro(check_required_components _NAME)
  foreach(comp ${${_NAME}_FIND_COMPONENTS})
    if(NOT ${_NAME}_${comp}_FOUND)
      if(${_NAME}_FIND_REQUIRED_${comp})
        set(${_NAME}_FOUND FALSE)
      endif()
    endif()
  endforeach()
endmacro()

####################################################################################

include(CMakeFindDependencyMacro)

find_package (JUCE 7.0.10 CONFIG REQUIRED)

if(USE_CURL)
	find_dependency(libcurl ${CURL_VERSION_MAJOR})
endif()
if(USE_OPENSSL)
	find_dependency(OpenSSL ${OPENSSL_VERSION_MAJOR})
endif()
if(USE_ZLIB)
	find_dependency(ZLIB ${ZLIB_VERSION_MAJOR})
endif()

#include("${CMAKE_CURRENT_LIST_DIR}/StoneyDSPTargets.cmake")

check_required_components("StoneyDSP")

set_directory_properties (PROPERTIES
    STONEYDSP_COMPANY_NAME       "StoneyDSP"
    STONEYDSP_COMPANY_WEBSITE    "https://stoneydsp.com"
    STONEYDSP_COMPANY_EMAIL      "nathanjhood@googlemail.com"
    STONEYDSP_COMPANY_COPYRIGHT  "Copyright (c) 2024 - Nathan J. Hood"
)

set(STONEYDSP_MODULES_DIR "${PACKAGE_PREFIX_DIR}/include/StoneyDSP/v1.0.0/modules" CACHE INTERNAL "The path to StoneyDSP modules")

set(_stoneydsp_modules
    stoneydsp_audio
    stoneydsp_core
    stoneydsp_graphics
    stoneydsp_web
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
    juce_add_module("${PACKAGE_PREFIX_DIR}/include/StoneyDSP/1.0.0/modules/${_stoneydsp_module}" ALIAS_NAMESPACE StoneyDSP)
endforeach()

unset(_stoneydsp_modules)

# Alias for either shared or static library
if(NOT TARGET ${PROJECT_NAME}::Shared)
	add_library(${PROJECT_NAME}::Shared ALIAS ${PROJECT_NAME}::${LIB_SELECTED})
endif()
