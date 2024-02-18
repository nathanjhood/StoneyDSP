cmake_minimum_required (VERSION 3.22...3.28 FATAL_ERROR)

if (EXISTS "${CMAKE_CURRENT_LIST_DIR}/ext/microsoft/vcpkg/scripts/buildsystems/vcpkg.cmake")
    set (CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_LIST_DIR}/ext/microsoft/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE FILEPATH "" FORCE)
endif ()

list (APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/share/cmake/Modules")

include (GetGitRef)
include (WriteVersionFile)

get_git_ref ()
write_version_file ()

project (
    StoneyDSP
    # VERSION 1.0.0
    DESCRIPTION ""
    HOMEPAGE_URL "https://stoneydsp.com"
    LANGUAGES C;CXX
)

set (PROJECT_VERSION_MAJOR 1                  CACHE STRING "First version number component of the ``PROJECT_VERSION`` variable as set by the ``project()`` command." FORCE)
set (PROJECT_VERSION_MINOR 0                  CACHE STRING "Second version number component of the ``PROJECT_VERSION`` variable as set by the ``project()`` command." FORCE)
set (PROJECT_VERSION_PATCH 0                  CACHE STRING "Third version number component of the ``PROJECT_VERSION`` variable as set by the ``project()`` command." FORCE)
set (PROJECT_VERSION_TWEAK "${git_revision}"  CACHE STRING "Fourth version number component of the ``PROJECT_VERSION`` variable as set by the ``project()`` command." FORCE)

string (TOLOWER "${PROJECT_NAME}" PROJECT_NAME_LOWER)
string (TOUPPER "${PROJECT_NAME}" PROJECT_NAME_UPPER)

set (StoneyDSP_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/include/StoneyDSP")

set (STONEYDSP_SHARED_HEADERS "")
list (APPEND STONEYDSP_SHARED_HEADERS
    "version.h"
    "StoneyDSP.h"
    "resources.h"
)

foreach (STONEYDSP_SHARED_HEADER IN LISTS STONEYDSP_SHARED_HEADERS)
  configure_file (
      "include/StoneyDSP/${STONEYDSP_SHARED_HEADER}"
      "include/StoneyDSP/${STONEYDSP_SHARED_HEADER}"
  )
endforeach ()

add_library (shared SHARED)
add_library (StoneyDSP::shared ALIAS shared)
target_sources (shared
    PRIVATE
    "src/StoneyDSP/resources.cpp"
    "src/StoneyDSP/shared.cpp"
)
target_include_directories (shared
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include/StoneyDSP>
    $<INSTALL_INTERFACE:include/StoneyDSP>
)
set_target_properties (shared
  PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib"
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin"
  PDB_OUTPUT_DIRECTORY     "${CMAKE_CURRENT_BINARY_DIR}/bin"
  POSITION_INDEPENDENT_CODE ON
)


include (CMakeRC)
# Create a CMakeRC library
# See https://github.com/vector-of-bool/cmrc/blob/master/README.md#usage
cmrc_add_resource_library (resources
	ALIAS StoneyDSP::resources
	NAMESPACE StoneyDSP::resources
  # Resources to compile...
  "LICENSE"
  "VERSION"
)
set_target_properties (resources
  PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib"
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin"
  PDB_OUTPUT_DIRECTORY     "${CMAKE_CURRENT_BINARY_DIR}/bin"
  POSITION_INDEPENDENT_CODE ON
)

target_link_libraries (shared PRIVATE StoneyDSP::resources)

# if (EXISTS "${CMAKE_CURRENT_LIST_DIR}/ext/juce-framework/JUCE/CMakeLists.txt")
if (FALSE)
    # if JUCE is a submodule...
    add_subdirectory (JUCE)
else ()
    # if JUCE is installed globally...
    find_package (JUCE CONFIG REQUIRED)
endif ()

#[=============================================================================[
Create a static library that embeds the contents of the files passed as
arguments to this function. Adds a library target called <name> which can be
linked into other targets using target_link_libraries.

The HEADER_NAME argument is optional. If provided, the generated header will be
given the requested name, otherwise the generated header will be named
"BinaryData.h". In completely new projects, you should provide a unique name
here, so that projects containing more than one binary data target are able to
include the binary data headers without ambiguity.

The NAMESPACE argument is also optional. If not provided, the generated files
will use the default namespace BinaryData. Each of the files located at the
paths following SOURCES will be encoded and embedded in the resulting static
library. This library can be linked as normal using
target_link_libraries(<otherTarget> PRIVATE <name>), and the header can be
included using #include <BinaryData.h>.
]=============================================================================]#
juce_add_binary_data (binary_data
    # [HEADER_NAME ...]
    # [NAMESPACE ...]
    # NAMESPACE StoneyDSP
    SOURCES "VERSION"
)
set_target_properties (binary_data
  PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib"
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin"
  PDB_OUTPUT_DIRECTORY     "${CMAKE_CURRENT_BINARY_DIR}/bin"
  POSITION_INDEPENDENT_CODE ON
)
target_link_libraries (shared PRIVATE binary_data)

#[=============================================================================[
This is a target which can be linked to other targets using
target_link_libraries, in order to enable the recommended JUCE warnings when
building them.

This target just sets compiler and linker flags, and doesn't have any associated
libraries or include directories. When building plugins, it's probably desirable
to link this to the shared code target with PUBLIC visibility, so that all the
plugin wrappers inherit the same compile/link flags.
]=============================================================================]#
target_link_libraries (shared PUBLIC juce::juce_recommended_warning_flags)

#[=============================================================================[
This is a target which can be linked to other targets using
target_link_libraries, in order to enable the recommended JUCE optimisation and
debug flags.

This target just sets compiler and linker flags, and doesn't have any associated
libraries or include directories. When building plugins, it's probably desirable
to link this to the shared code target with PUBLIC visibility, so that all the
plugin wrappers inherit the same compile/link flags.
]=============================================================================]#
target_link_libraries (shared PUBLIC juce::juce_recommended_config_flags)

#[=============================================================================[
This is a target which can be linked to other targets using
target_link_libraries, in order to enable the recommended JUCE link time
optimisation settings.

This target just sets compiler and linker flags, and doesn't have any associated
libraries or include directories. When building plugins, it's probably desirable
to link this to the shared code target with PUBLIC visibility, so that all the
plugin wrappers inherit the same compile/link flags.
]=============================================================================]#
target_link_libraries (shared PUBLIC juce::juce_recommended_lto_flags)

if (BUILD_TESTS)
  enable_testing ()
endif ()

if (StoneyDSP_IS_INSTALLABLE)
    include (GNUInstallDirs)
    set (StoneyDSP_INCLUDE_DIR "${CMAKE_INSTALL_INCLUDEDIR}/StoneyDSP" CACHE PATH "StoneyDSP include directory." FORCE)
endif ()
