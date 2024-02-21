cmake_minimum_required (VERSION 3.15...3.28 FATAL_ERROR)

if (NOT DEFINED CMakeRC_DIR)
    find_package (CMakeRC)
	if (NOT DEFINED CMakeRC_DIR)
		message (FATAL_ERROR "Cannot find CMakeRC?")
		return ()
	endif ()
endif ()

set (STONEYDSP_ICONS_PNG_WIDE "")
list (APPEND STONEYDSP_ICONS_PNG_WIDE
    w_icon__196x128.png
	w_icon__384x256.png
	w_icon__768x512.png
	w_icon__1024x768.png
)

cmrc_add_resource_library (Icons
	ALIAS StoneyDSP::Icons
	NAMESPACE StoneyDSP::Icons
	PREFIX StoneyDSP/Icons

    # SOURCES
	favicon.ico
	${STONEYDSP_ICONS_PNG_WIDE}
)

set (STONEYDSP_ICONS_PNG "")
list (APPEND STONEYDSP_ICONS_PNG
	favicon/android-chrome-192x192.png
	favicon/android-chrome-512x512.png
	favicon/android-icon-144x144.png
	favicon/android-icon-192x192.png
	favicon/android-icon-36x36.png
	favicon/android-icon-48x48.png
	favicon/android-icon-72x72.png
	favicon/android-icon-96x96.png
	favicon/favicon-144x144.png
	favicon/favicon-168x168.png
	favicon/favicon-256x256.png
	favicon/favicon-32x32.png
	favicon/favicon-48x48.png
	favicon/favicon-512x512.png
	favicon/favicon-64x64.png
	favicon/favicon-96x96.png
	favicon/ms-icon-150x150.png
	favicon/ms-icon-310x310.png
	favicon/ms-icon-70x70.png
)
cmrc_add_resources (Icons
	WHENCE favicon
	PREFIX StoneyDSP/Icons
	${STONEYDSP_ICONS_PNG}
)

set (STONEYDSP_ICONS_ICO "")
list (APPEND STONEYDSP_ICONS_ICO
	favicon/favicon__144x144.ico
	favicon/favicon__168x168.ico
	favicon/favicon__256x256.ico
	favicon/favicon__32x32.ico
	favicon/favicon__48x48.ico
	favicon/favicon__64x64.ico
	favicon/favicon__96x96.ico
)
cmrc_add_resources (Icons
    WHENCE favicon
	PREFIX StoneyDSP/Icons
	${STONEYDSP_ICONS_ICO}
)

set_target_properties (Icons
  PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib"
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin"
  PDB_OUTPUT_DIRECTORY     "${CMAKE_CURRENT_BINARY_DIR}/bin"
  POSITION_INDEPENDENT_CODE ON
)
