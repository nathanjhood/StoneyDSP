#[=============================================================================[
StoneyDSPConfigVersion.cmake
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

# This is a basic version file for the Config-mode of find_package().
# It is used by write_basic_package_version_file() as input file for configure_file()
# to create a version-file which can be installed along a config.cmake file.
#
# The created file sets PACKAGE_VERSION_EXACT if the current version string and
# the requested version string are exactly the same and it sets
# PACKAGE_VERSION_COMPATIBLE if the current version is equal to the requested version.
# The tweak version component is ignored.
# The variable CVF_VERSION must be set before calling configure_file().


if (PACKAGE_FIND_VERSION_RANGE)
  message(AUTHOR_WARNING
    "`find_package()` specify a version range but the version strategy "
    "(ExactVersion) of the module `${PACKAGE_FIND_NAME}` is incompatible "
    "with this request. Only the lower endpoint of the range will be used.")
endif()

set(PACKAGE_VERSION "1.0.0")

if("1.0.0" MATCHES "^([0-9]+)\\.([0-9]+)\\.([0-9]+)") # strip the tweak version
  set(CVF_VERSION_MAJOR "${CMAKE_MATCH_1}")
  set(CVF_VERSION_MINOR "${CMAKE_MATCH_2}")
  set(CVF_VERSION_PATCH "${CMAKE_MATCH_3}")

  if(NOT CVF_VERSION_MAJOR VERSION_EQUAL 0)
    string(REGEX REPLACE "^0+" "" CVF_VERSION_MAJOR "${CVF_VERSION_MAJOR}")
  endif()
  if(NOT CVF_VERSION_MINOR VERSION_EQUAL 0)
    string(REGEX REPLACE "^0+" "" CVF_VERSION_MINOR "${CVF_VERSION_MINOR}")
  endif()
  if(NOT CVF_VERSION_PATCH VERSION_EQUAL 0)
    string(REGEX REPLACE "^0+" "" CVF_VERSION_PATCH "${CVF_VERSION_PATCH}")
  endif()

  set(CVF_VERSION_NO_TWEAK "${CVF_VERSION_MAJOR}.${CVF_VERSION_MINOR}.${CVF_VERSION_PATCH}")
else()
  set(CVF_VERSION_NO_TWEAK "1.0.0")
endif()

if(PACKAGE_FIND_VERSION MATCHES "^([0-9]+)\\.([0-9]+)\\.([0-9]+)") # strip the tweak version
  set(REQUESTED_VERSION_MAJOR "${CMAKE_MATCH_1}")
  set(REQUESTED_VERSION_MINOR "${CMAKE_MATCH_2}")
  set(REQUESTED_VERSION_PATCH "${CMAKE_MATCH_3}")

  if(NOT REQUESTED_VERSION_MAJOR VERSION_EQUAL 0)
    string(REGEX REPLACE "^0+" "" REQUESTED_VERSION_MAJOR "${REQUESTED_VERSION_MAJOR}")
  endif()
  if(NOT REQUESTED_VERSION_MINOR VERSION_EQUAL 0)
    string(REGEX REPLACE "^0+" "" REQUESTED_VERSION_MINOR "${REQUESTED_VERSION_MINOR}")
  endif()
  if(NOT REQUESTED_VERSION_PATCH VERSION_EQUAL 0)
    string(REGEX REPLACE "^0+" "" REQUESTED_VERSION_PATCH "${REQUESTED_VERSION_PATCH}")
  endif()

  set(REQUESTED_VERSION_NO_TWEAK
      "${REQUESTED_VERSION_MAJOR}.${REQUESTED_VERSION_MINOR}.${REQUESTED_VERSION_PATCH}")
else()
  set(REQUESTED_VERSION_NO_TWEAK "${PACKAGE_FIND_VERSION}")
endif()

if(REQUESTED_VERSION_NO_TWEAK STREQUAL CVF_VERSION_NO_TWEAK)
  set(PACKAGE_VERSION_COMPATIBLE TRUE)
else()
  set(PACKAGE_VERSION_COMPATIBLE FALSE)
endif()

if(PACKAGE_FIND_VERSION STREQUAL PACKAGE_VERSION)
  set(PACKAGE_VERSION_EXACT TRUE)
endif()


# if the installed or the using project don't have CMAKE_SIZEOF_VOID_P set, ignore it:
if("${CMAKE_SIZEOF_VOID_P}" STREQUAL "" OR "8" STREQUAL "")
  return()
endif()

# check that the installed version has the same 32/64bit-ness as the one which is currently searching:
if(NOT CMAKE_SIZEOF_VOID_P STREQUAL "8")
  math(EXPR installedBits "8 * 8")
  set(PACKAGE_VERSION "${PACKAGE_VERSION} (${installedBits}bit)")
  set(PACKAGE_VERSION_UNSUITABLE TRUE)
endif()
