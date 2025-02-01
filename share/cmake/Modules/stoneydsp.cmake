#[===============================[Include Guard]===============================]
include_guard(GLOBAL)

set(_version 0.0.0)

if(COMMAND stoneydsp_add_core)
    if(NOT DEFINED _stoneydsp_core_script_version OR NOT(_version STREQUAL _stoneydsp_core_script_version))
        message(WARNING "More than one 'stoneydsp.cmake' version has been included in this project.")
    endif()

    # 'stoneydsp.cmake' has already been included! Don't do anything
    return()
endif()

set(_stoneydsp_script_version "${_version}" CACHE INTERNAL "Current 'stoneydsp.cmake' version. Used for checking for conflicts")

set(_stoneydsp_script_file "${CMAKE_CURRENT_LIST_FILE}" CACHE INTERNAL "Path to current 'stoneydsp.cmake' script")

#[=============================================================================[
Internal helper
]=============================================================================] #
function(_stoneydsp_trim_newlines input)
    string(REGEX REPLACE "[\r\n\"]" "" input "${input}")
    set(input "${input}" PARENT_SCOPE)
endfunction()

#[=============================================================================[
Internal helper (borrowed from CMakeRC).
]=============================================================================]
function(_stoneydsp_normalize_path var)
    set(path "${${var}}")
    file(TO_CMAKE_PATH "${path}" path)

    while(path MATCHES "//")
        string(REPLACE "//" "/" path "${path}")
    endwhile()

    string(REGEX REPLACE "/+$" "" path "${path}")
    set("${var}" "${path}" PARENT_SCOPE)
endfunction()

#[=============================================================================[
Internal helper (borrowed from CMakeRC).
]=============================================================================]
function(stoneydsp_add_directories)
    file(RELATIVE_PATH STONEYDSP_INCLUDE_DIR "${STONEYDSP_DIR}" "${STONEYDSP_DIR}/include")
    file(RELATIVE_PATH STONEYDSP_SRC_DIR "${STONEYDSP_DIR}" "${STONEYDSP_DIR}/src")
    file(RELATIVE_PATH STONEYDSP_TEST_DIR "${STONEYDSP_DIR}" "${STONEYDSP_DIR}/test")
    file(RELATIVE_PATH STONEYDSP_DATA_DIR "${STONEYDSP_DIR}" "${STONEYDSP_DIR}/share")
    set(STONEYDSP_INCLUDE_DIR "${STONEYDSP_INCLUDE_DIR}" PARENT_SCOPE)
    set(STONEYDSP_SRC_DIR "${STONEYDSP_SRC_DIR}" PARENT_SCOPE)
    set(STONEYDSP_TEST_DIR "${STONEYDSP_TEST_DIR}" PARENT_SCOPE)
    set(STONEYDSP_DATA_DIR "${STONEYDSP_DATA_DIR}" PARENT_SCOPE)
endfunction()

#[==================================[Cleanup]==================================]
unset(_version)
