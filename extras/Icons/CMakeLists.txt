find_package (CMakeRC CONFIG REQUIRED)
# include (public/images/CMakeLists.txt)
if (NOT DEFINED CMakeRC_DIR)
    find_package (CMakeRC)
	if (NOT DEFINED CMakeRC_DIR)
		message (FATAL_ERROR "Cannot find CMakeRC?")
		return ()
	endif ()
endif ()

set (STONEYDSP_ICONS_PNG_WIDE "")
list (APPEND STONEYDSP_ICONS_PNG_WIDE
	public/images/w_icon__1024x768.png
	public/images/w_icon__196x128.png
	public/images/w_icon__384x256.png
	public/images/w_icon__768x512.png
)

cmrc_add_resource_library (Icons

	ALIAS StoneyDSP::Icons
	NAMESPACE StoneyDSP::Icons
	WHENCE public/images
	PREFIX StoneyDSP/Icons

    # SOURCES
	public/images/favicon.ico
	${STONEYDSP_ICONS_PNG_WIDE}
)

set (STONEYDSP_ICONS_PNG "")
list (APPEND STONEYDSP_ICONS_PNG
	public/images/favicon/android-chrome-192x192.png
	public/images/favicon/android-chrome-512x512.png
	public/images/favicon/android-icon-144x144.png
	public/images/favicon/android-icon-192x192.png
	public/images/favicon/android-icon-36x36.png
	public/images/favicon/android-icon-48x48.png
	public/images/favicon/android-icon-72x72.png
	public/images/favicon/android-icon-96x96.png
	public/images/favicon/favicon-144x144.png
	public/images/favicon/favicon-168x168.png
	public/images/favicon/favicon-256x256.png
	public/images/favicon/favicon-32x32.png
	public/images/favicon/favicon-48x48.png
	public/images/favicon/favicon-512x512.png
	public/images/favicon/favicon-64x64.png
	public/images/favicon/favicon-96x96.png
	public/images/favicon/ms-icon-150x150.png
	public/images/favicon/ms-icon-310x310.png
	public/images/favicon/ms-icon-70x70.png
)
cmrc_add_resources (Icons

	WHENCE public/images/favicon
	PREFIX StoneyDSP/Icons

	${STONEYDSP_ICONS_PNG}
)

set (STONEYDSP_ICONS_ICO "")
list (APPEND STONEYDSP_ICONS_ICO
	public/images/favicon/favicon__144x144.ico
	public/images/favicon/favicon__168x168.ico
	public/images/favicon/favicon__256x256.ico
	public/images/favicon/favicon__32x32.ico
	public/images/favicon/favicon__48x48.ico
	public/images/favicon/favicon__64x64.ico
	public/images/favicon/favicon__96x96.ico
)
cmrc_add_resources (Icons

	WHENCE public/images/favicon
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
