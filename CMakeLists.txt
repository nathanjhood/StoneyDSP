cmake_minimum_required (VERSION 3.22...3.28 FATAL_ERROR)

project (
    StoneyDSP
    VERSION 1.0.0
    DESCRIPTION ""
    HOMEPAGE_URL "https://stoneydsp.com"
    LANGUAGES C;CXX
)

string (TOLOWER "${PROJECT_NAME}" PROJECT_NAME_LOWER)
string (TOUPPER "${PROJECT_NAME}" PROJECT_NAME_UPPER)

configure_file (
    "include/StoneyDSP/version.h"
    "include/StoneyDSP/version.h"
)

add_library (shared SHARED)
add_library (StoneyDSP::shared ALIAS shared)

target_sources (shared PRIVATE "src/StoneyDSP/shared.cpp")

target_include_directories (shared
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include/StoneyDSP>
    $<INSTALL_INTERFACE:include/StoneyDSP>
)

if (FALSE)
    # if JUCE is a submodule...
    add_subdirectory (JUCE)
else ()
    # if JUCE is installed globally...
    find_package (JUCE CONFIG REQUIRED)
endif ()

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
