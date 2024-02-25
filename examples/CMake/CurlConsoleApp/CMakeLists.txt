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

cmake_minimum_required(VERSION 3.22)

project(CURL_CONSOLE_APP_EXAMPLE VERSION 0.0.1)

if (NOT DEFINED CURL_VERSION_MAJOR)
    find_package (CURL REQUIRED)
endif ()

# Uncomment this if not being built as a StoneyDSP example sub-project
# find_package(JUCE CONFIG REQUIRED)

juce_add_console_app (
    CurlConsoleAppExample
     # The name of the final executable, which can differ from the target name
    PRODUCT_NAME "Console App with cURL Example"
    NEEDS_CURL TRUE
)

configure_file (
    "include/CurlConsoleApp/main.h"
    "include/CurlConsoleApp/main.h"
)
target_include_directories (CurlConsoleAppExample
    PUBLIC
        $<BUILD_INTERFACE:${CURL_CONSOLE_APP_EXAMPLE_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

juce_generate_juce_header (CurlConsoleAppExample)

target_sources (CurlConsoleAppExample
    PRIVATE
        src/CurlConsoleApp/main.cpp
)

target_compile_definitions (CurlConsoleAppExample
    PRIVATE
        # JUCE_WEB_BROWSER would be on by default, but you might not need them.
        # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the
        # `juce_add_console_app` call
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=1
)

# juce_add_binary_data(ConsoleAppData SOURCES ...)

target_link_libraries (CurlConsoleAppExample
    PRIVATE
        # ConsoleAppData            # If you'd created a binary data target, you'd link to it here
        juce::juce_core
        StoneyDSP::stoneydsp_core
        StoneyDSP::stoneydsp_web
        CURL::libcurl
    PUBLIC
        juce::juce_recommended_warning_flags
        juce::juce_recommended_config_flags
        # juce::juce_recommended_lto_flags
)
