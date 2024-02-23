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

# Create a CMakeRC library
# See https://github.com/vector-of-bool/cmrc/blob/master/README.md#usage

find_package (CMakeRC CONFIG REQUIRED)
# include (public/images/CMakeLists.txt)
if (NOT DEFINED CMakeRC_DIR)
    find_package (CMakeRC)
	if (NOT DEFINED CMakeRC_DIR)
		message (FATAL_ERROR "Cannot find CMakeRC?")
		return ()
	endif ()
endif ()

cmrc_add_resource_library (Resources
	ALIAS StoneyDSP::Resources
	NAMESPACE StoneyDSP::Resources
)

cmrc_add_resources (Resources
    # Resources to compile...
    "LICENSE"
    "VERSION"
)

set_target_properties (Resources
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin"
    PDB_OUTPUT_DIRECTORY     "${CMAKE_CURRENT_BINARY_DIR}/bin"
)

if (UNIX)
    set_target_properties (Resources
        PROPERTIES
        POSITION_INDEPENDENT_CODE ON
    )
endif ()
