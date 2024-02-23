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
