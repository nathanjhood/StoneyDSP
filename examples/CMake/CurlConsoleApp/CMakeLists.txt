cmake_minimum_required(VERSION 3.22)

project(CURL_CONSOLE_APP_EXAMPLE VERSION 0.0.1)

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
        $<BUILD_INTERFACE:${CURL_CONSOLE_APP_EXAMPLE_SOURCE_DIR}/include>
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
)

# juce_add_binary_data(ConsoleAppData SOURCES ...)

target_link_libraries (CurlConsoleAppExample
    PRIVATE
        # ConsoleAppData            # If you'd created a binary data target, you'd link to it here
        juce::juce_core
        StoneyDSP::stoneydsp_core
        StoneyDSP::stoneydsp_web
    PUBLIC
        juce::juce_recommended_warning_flags
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
)
