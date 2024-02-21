cmake_minimum_required (VERSION 3.22...3.28 FATAL_ERROR)

if (DEFINED VCPKG_ROOT)
    # global install...
    set (CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE FILEPATH "" FORCE)
elseif (EXISTS "${CMAKE_CURRENT_LIST_DIR}/ext/microsoft/vcpkg/scripts/buildsystems/vcpkg.cmake")
    # submodule...
    set (CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_LIST_DIR}/ext/microsoft/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE FILEPATH "" FORCE)
endif ()

list (APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/share/cmake/Modules")


option (BUILD_TESTS "Build tests" ON)

# IDE support
set (JUCE_ENABLE_MODULE_SOURCE_GROUPS ON)
set_property(GLOBAL PROPERTY USE_FOLDERS YES)

project (
    StoneyDSP
    # VERSION 1.0.0
    DESCRIPTION ""
    HOMEPAGE_URL "https://stoneydsp.com"
    LANGUAGES C;CXX
)

include (CMakePackageConfigHelpers)
include (GetGitRef)
include (WriteVersionFile)

stoneydsp_get_git_ref ()

set (STONEYDSP_VERSION_MAJOR 1                                                  CACHE STRING "First version number component of the ``PROJECT_VERSION`` variable as set by the ``project()`` command." FORCE)
set (STONEYDSP_VERSION_MINOR 0                                                  CACHE STRING "Second version number component of the ``PROJECT_VERSION`` variable as set by the ``project()`` command." FORCE)
set (STONEYDSP_VERSION_PATCH 0                                                  CACHE STRING "Third version number component of the ``PROJECT_VERSION`` variable as set by the ``project()`` command." FORCE)
set (STONEYDSP_VERSION_TWEAK "${STONEYDSP_GIT_COMMIT_REF}"                      CACHE STRING "Fourth version number component of the ``PROJECT_VERSION`` variable as set by the ``project()`` command." FORCE)

set (STONEYDSP_VERSION ${STONEYDSP_VERSION_MAJOR}.${STONEYDSP_VERSION_MINOR}.${STONEYDSP_VERSION_PATCH} CACHE STRING "StoneyDSP Version Number." FORCE)

stoneydsp_write_version_file ()

string (TOLOWER "${PROJECT_NAME}" PROJECT_NAME_LOWER)
string (TOUPPER "${PROJECT_NAME}" PROJECT_NAME_UPPER)


if (PROJECT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
endif ()
if (StoneyDSP_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
endif ()

set (StoneyDSP_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/include/StoneyDSP")

set (STONEYDSP_SHARED_HEADERS "")
list (APPEND STONEYDSP_SHARED_HEADERS
    "version.h"
    "StoneyDSP.h"
    "resources.h"
)
set (STONEYDSP_SHARED_SOURCES "")
list (APPEND STONEYDSP_SHARED_SOURCES
    "resources.cpp"
    "shared.cpp"
)

add_library (Shared SHARED)
add_library (StoneyDSP::shared ALIAS Shared)
# directories
target_include_directories (Shared
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include/StoneyDSP>
    $<INSTALL_INTERFACE:include/StoneyDSP>
)
# files
foreach (STONEYDSP_SHARED_HEADER IN LISTS STONEYDSP_SHARED_HEADERS)
    configure_file (
        "include/StoneyDSP/${STONEYDSP_SHARED_HEADER}" # SRC_DIR
        "include/StoneyDSP/${STONEYDSP_SHARED_HEADER}" # BIN_DIR
		@ONLY
    )
    target_sources (Shared
        PUBLIC
        FILE_SET stoneydsp_Shared_PUBLIC_HEADERS
        TYPE HEADERS
        BASE_DIRS
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include/StoneyDSP>
        $<INSTALL_INTERFACE:include/StoneyDSP>
        FILES
        # include/pacman/common/ini.h
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include/StoneyDSP/${STONEYDSP_SHARED_HEADER}>
        $<INSTALL_INTERFACE:include/StoneyDSP/${STONEYDSP_SHARED_HEADER}>
    )
endforeach ()
foreach (STONEYDSP_SHARED_SOURCE IN LISTS STONEYDSP_SHARED_SOURCES)
    target_sources (Shared
        PRIVATE
        "src/StoneyDSP/${STONEYDSP_SHARED_SOURCE}"
    )
endforeach ()
# properties
set_target_properties (Shared
  PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib"
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin"
  PDB_OUTPUT_DIRECTORY     "${CMAKE_CURRENT_BINARY_DIR}/bin"
  POSITION_INDEPENDENT_CODE ON
)

find_package (OpenSSL REQUIRED)
target_link_libraries (Shared PRIVATE OpenSSL::SSL OpenSSL::Crypto)

find_package (CURL CONFIG REQUIRED)
target_link_libraries (Shared PRIVATE CURL::libcurl)

find_package (CMakeRC CONFIG REQUIRED)
# Create a CMakeRC library
# See https://github.com/vector-of-bool/cmrc/blob/master/README.md#usage
cmrc_add_resource_library (Resources
	ALIAS StoneyDSP::Resources
	NAMESPACE StoneyDSP::Resources
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
  POSITION_INDEPENDENT_CODE ON
)

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




# if (EXISTS "${CMAKE_CURRENT_LIST_DIR}/ext/juce-framework/JUCE/CMakeLists.txt")
if (FALSE)
    # if JUCE is a submodule...
    add_subdirectory (JUCE)
else ()
    # if JUCE is installed globally...
    find_package (JUCE CONFIG REQUIRED)
endif ()

#[==[
juce provides the following common CMake targets:

find_package(JUCE CONFIG REQUIRED)
target_link_libraries(main PRIVATE
    juce::juce_core
    juce::juce_audio_basics
    juce::juce_events
    juce::juce_audio_devices
    juce::juce_graphics
    juce::juce_gui_basics
    juce::juce_gui_extra
    juce::juce_opengl
    juce::juce_analytics
    juce::juce_audio_formats
    juce::juce_audio_plugin_client
    juce::juce_audio_processors
    juce::juce_audio_utils
    juce::juce_box2d
    juce::juce_cryptography
    juce::juce_data_structures
    juce::juce_dsp
    juce::juce_osc
    juce::juce_product_unlocking
    juce::juce_video

    juce::juce_recommended_config_flags
    juce::juce_recommended_lto_flags
    juce::juce_recommended_warning_flags
)

]==]#

target_link_libraries (Shared
    PRIVATE
    juce::juce_core
    juce::juce_audio_basics
    juce::juce_events
    juce::juce_audio_devices
    PUBLIC
    juce::juce_recommended_warning_flags
    juce::juce_recommended_config_flags
    juce::juce_recommended_lto_flags
)
target_compile_definitions (Shared PUBLIC DONT_SET_USING_JUCE_NAMESPACE)

target_link_libraries (Shared
    PRIVATE
    StoneyDSP::Resources
    StoneyDSP::Icons
)

juce_add_module(
    # StoneyDSP::stoneydsp_core
    modules/stoneydsp_core
    ALIAS_NAMESPACE StoneyDSP
    INSTALL_PATH "include/StoneyDSP-${STONEYDSP_VERSION}/modules"
)
juce_add_module(
    # StoneyDSP::stoneydsp_audio
    modules/stoneydsp_audio
    ALIAS_NAMESPACE StoneyDSP
    INSTALL_PATH "include/StoneyDSP-${STONEYDSP_VERSION}/modules"
)
juce_add_module(
    # StoneyDSP::stoneydsp_graphics
    modules/stoneydsp_graphics
    ALIAS_NAMESPACE StoneyDSP
    INSTALL_PATH "include/StoneyDSP-${STONEYDSP_VERSION}/modules"
)

add_library (StoneyDSP INTERFACE)
add_library (StoneyDSP::StoneyDSP ALIAS StoneyDSP)
target_link_libraries (StoneyDSP
    INTERFACE
    StoneyDSP::stoneydsp_core
    StoneyDSP::stoneydsp_audio
    StoneyDSP::stoneydsp_graphics
)

add_executable (Main "src/main.cpp")
target_link_libraries (Main PRIVATE StoneyDSP::StoneyDSP)
set_target_properties (Main
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin"
    PDB_OUTPUT_DIRECTORY     "${CMAKE_CURRENT_BINARY_DIR}/bin"
    # POSITION_INDEPENDENT_CODE ON
)

set (STONEYDSP_MODULES "")
list (APPEND STONEYDSP_MODULES
    stoneydsp_core
    stoneydsp_audio
    stoneydsp_graphics
)

# export (
#     TARGETS ${STONEYDSP_MODULES}
#     FILE ${CMAKE_BINARY_DIR}/share/cmake/StoneyDSPTargets.cmake
#     NAMESPACE StoneyDSP::
# )

# install(
#     EXPORT StoneyDSPTargets
#     FILE StoneyDSPTargets.cmake
#     NAMESPACE StoneyDSP::
#     DESTINATION lib/cmake/StoneyDSP
# )

# install(TARGETS ${STONEYDSP_MODULES}
#     EXPORT StoneyDSPTargets
#     LIBRARY DESTINATION  "${CMAKE_INSTALL_LIBDIR}"
#     ARCHIVE DESTINATION  "${CMAKE_INSTALL_LIBDIR}"
#     RUNTIME DESTINATION  "${CMAKE_INSTALL_BINDIR}"
#     INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
# )

file (WRITE "${StoneyDSP_BINARY_DIR}/StoneyDSPConfig.cmake.in" [[
@PACKAGE_INIT@

include(CMakeFindDependencyMacro)
if(@USE_CURL@)
	find_dependency(libcurl @CURL_VERSION_MAJOR@)
endif()
if(@USE_OPENSSL@)
	find_dependency(OpenSSL @OPENSSL_VERSION_MAJOR@)
endif()
if(@USE_ZLIB@)
	find_dependency(ZLIB @ZLIB_VERSION_MAJOR@)
endif()

include("${CMAKE_CURRENT_LIST_DIR}/@TARGETS_EXPORT_NAME@.cmake")
check_required_components("@PROJECT_NAME@")

# Alias for either shared or static library
if(NOT TARGET ${PROJECT_NAME}::Shared)
	add_library(${PROJECT_NAME}::Shared ALIAS ${PROJECT_NAME}::${LIB_SELECTED})
endif()
]])

# create cmake config file
configure_package_config_file (
    ${PROJECT_BINARY_DIR}/StoneyDSPConfig.cmake.in
    ${PROJECT_BINARY_DIR}/share/cmake/StoneyDSPConfig.cmake
  INSTALL_DESTINATION
    ${CMAKE_INSTALL_LIBDIR}/cmake/StoneyDSP
)

# generate the version file for the cmake config file
write_basic_package_version_file (
	${PROJECT_BINARY_DIR}/share/cmake/StoneyDSPConfigVersion.cmake
	VERSION ${STONEYDSP_VERSION}
	COMPATIBILITY AnyNewerVersion
)

if(BUILD_TESTS AND (StoneyDSP_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR))
    enable_testing()
    # if(NOT MSVC)
    #     add_compile_options(-Wall -Wextra)
    # endif()
    # add_subdirectory(tests)
endif()

if (StoneyDSP_IS_INSTALLABLE)
    include (GNUInstallDirs)
    set (StoneyDSP_INCLUDE_DIR "${CMAKE_INSTALL_INCLUDEDIR}/StoneyDSP" CACHE PATH "StoneyDSP include directory." FORCE)
endif ()
