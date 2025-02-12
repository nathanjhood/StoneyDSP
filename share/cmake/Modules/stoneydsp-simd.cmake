#[===============================[Include Guard]===============================]
include_guard(GLOBAL)

set(_version 0.0.0)

if(COMMAND stoneydsp_add_simd)
    if(NOT DEFINED _stoneydsp_simd_script_version OR NOT(_version STREQUAL _stoneydsp_simd_script_version))
        message(WARNING "More than one 'stoneydsp-simd.cmake' version has been included in this project.")
    endif()

    # 'stoneydsp-simd.cmake' has already been included! Don't do anything
    return()
endif()

set(_stoneydsp_simd_script_version "${_version}" CACHE INTERNAL "Current 'stoneydsp-simd.cmake' version. Used for checking for conflicts")

set(_stoneydsp_simd_script_file "${CMAKE_CURRENT_LIST_FILE}" CACHE INTERNAL "Path to current 'stoneydsp-simd.cmake' script")

#[============================[stoneydsp_add_simd]============================]
cmake_dependent_option(STONEYDSP_SIMD_TARGET_INSTALL "Notes" ON "STONEYDSP_BUILD_SIMD" ON)
cmake_dependent_option(STONEYDSP_SIMD_TARGET_EXPORT "Notes" ON "STONEYDSP_BUILD_SIMD" ON)
include(CMakeDependentOption)

#[==[
Adds target: `stoneydsp::simd`
]==]
function(stoneydsp_add_simd)
    # Generate target properties
    set(STONEYDSP_SIMD_TARGET_NAME "simd")
    set(STONEYDSP_SIMD_VERSION_MAJOR "0")
    set(STONEYDSP_SIMD_VERSION_MINOR "0")
    set(STONEYDSP_SIMD_VERSION_BUILD "0")
    set(STONEYDSP_SIMD_VERSION "${STONEYDSP_SIMD_VERSION_MAJOR}.${STONEYDSP_SIMD_VERSION_MINOR}.${STONEYDSP_SIMD_VERSION_BUILD}")
    set(STONEYDSP_SIMD_HEADERS_FILESET_NAME "stoneydsp_SIMD_PUBLIC_HEADERS")

    # simd.h|cpp
    set(STONEYDSP_SIMD_H_FILE "${STONEYDSP_INCLUDE_DIR}/${STONEYDSP_SLUG}/${STONEYDSP_SIMD_TARGET_NAME}/${STONEYDSP_SIMD_TARGET_NAME}.h")
    set(STONEYDSP_SIMD_CPP_FILE "${STONEYDSP_SRC_DIR}/${STONEYDSP_SLUG}/${STONEYDSP_SIMD_TARGET_NAME}/${STONEYDSP_SIMD_TARGET_NAME}.cpp")

    # vector/vector.h
    set(STONEYDSP_SIMD_VECTOR_SUPPORT_H_FILE "${STONEYDSP_INCLUDE_DIR}/${STONEYDSP_SLUG}/${STONEYDSP_SIMD_TARGET_NAME}/vector/support.h")

    # List header files (public)
    set(STONEYDSP_SIMD_HEADER_FILES)
    list(APPEND STONEYDSP_SIMD_HEADER_FILES
        ${STONEYDSP_SIMD_H_FILE}
        ${STONEYDSP_SIMD_VECTOR_SUPPORT_H_FILE}
    )

    # List source files (private)
    set(STONEYDSP_SIMD_SOURCE_FILES)
    list(APPEND STONEYDSP_SIMD_SOURCE_FILES
        ${STONEYDSP_SIMD_CPP_FILE}
    )

    # List link libraries (private)
    set(STONEYDSP_SIMD_LINK_LIBRARIES_PRIVATE)
    list(APPEND STONEYDSP_SIMD_LINK_LIBRARIES_PRIVATE)

    # List link libraries (public)
    set(STONEYDSP_SIMD_LINK_LIBRARIES_PUBLIC)
    list(APPEND STONEYDSP_SIMD_LINK_LIBRARIES_PUBLIC)

    # List link libraries (interface)
    set(STONEYDSP_SIMD_LINK_LIBRARIES_INTERFACE)
    list(APPEND STONEYDSP_SIMD_LINK_LIBRARIES_INTERFACE)

    # List compile definitions (private)
    set(STONEYDSP_SIMD_COMPILE_DEFINITIONS_PRIVATE)
    list(APPEND STONEYDSP_SIMD_COMPILE_DEFINITIONS_PRIVATE)

    # List compile definitions (public)
    set(STONEYDSP_SIMD_COMPILE_DEFINITIONS_PUBLIC)
    list(APPEND STONEYDSP_SIMD_COMPILE_DEFINITIONS_PUBLIC
        "-DSTONEYDSP_BUILD_SIMD=1"
        "-DSTONEYDSP_SIMD_VERSION_MAJOR=${STONEYDSP_SIMD_VERSION_MAJOR}"
        "-DSTONEYDSP_SIMD_VERSION_MINOR=${STONEYDSP_SIMD_VERSION_MINOR}"
        "-DSTONEYDSP_SIMD_VERSION_BUILD=${STONEYDSP_SIMD_VERSION_BUILD}"
        "-DSTONEYDSP_SIMD_VERSION=${STONEYDSP_SIMD_VERSION}"
    )

    # List compile definitions (interface)
    set(STONEYDSP_SIMD_COMPILE_DEFINITIONS_INTERFACE)
    list(APPEND STONEYDSP_SIMD_COMPILE_DEFINITIONS_INTERFACE)

    # List compile options (interface)
    set(STONEYDSP_SIMD_COMPILE_OPTIONS_INTERFACE)
    list(APPEND STONEYDSP_SIMD_COMPILE_OPTIONS_INTERFACE)

    # List compile options (private)
    set(STONEYDSP_SIMD_COMPILE_OPTIONS_PRIVATE)
    list(APPEND STONEYDSP_SIMD_COMPILE_OPTIONS_PRIVATE)

    # List compile options (public)
    set(STONEYDSP_SIMD_COMPILE_OPTIONS_PUBLIC)
    list(APPEND STONEYDSP_SIMD_COMPILE_OPTIONS_PUBLIC)

    # List compile features (interface)
    set(STONEYDSP_SIMD_COMPILE_FEATURES_INTERFACE)
    list(APPEND STONEYDSP_SIMD_COMPILE_FEATURES_INTERFACE)

    # List compile features (private)
    set(STONEYDSP_SIMD_COMPILE_FEATURES_PRIVATE)
    list(APPEND STONEYDSP_SIMD_COMPILE_FEATURES_PRIVATE)

    # List compile features (public)
    set(STONEYDSP_SIMD_COMPILE_FEATURES_PUBLIC)
    list(APPEND STONEYDSP_SIMD_COMPILE_FEATURES_PUBLIC)

    add_library(${STONEYDSP_SIMD_TARGET_NAME} OBJECT)
    add_library(${STONEYDSP_SLUG}::${STONEYDSP_SIMD_TARGET_NAME} ALIAS ${STONEYDSP_SIMD_TARGET_NAME})
    add_library(${STONEYDSP_BRAND}::${STONEYDSP_SLUG}::${STONEYDSP_SIMD_TARGET_NAME} ALIAS ${STONEYDSP_SIMD_TARGET_NAME})

    set_target_properties(${STONEYDSP_SIMD_TARGET_NAME}
        PROPERTIES

        VERSION "${STONEYDSP_SIMD_VERSION}"
        SOVERSION "${STONEYDSP_SIMD_VERSION_MAJOR}"

        RUNTIME_OUTPUT_DIRECTORY "${STONEYDSP_BINARY_DIR}/bin"
        PDB_OUTPUT_DIRECTORY "${STONEYDSP_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${STONEYDSP_BINARY_DIR}/lib"
        ARCHIVE_OUTPUT_DIRECTORY "${STONEYDSP_BINARY_DIR}/lib"
    )

    foreach(STONEYDSP_SIMD_HEADER_FILE IN LISTS STONEYDSP_SIMD_HEADER_FILES)
        message(DEBUG "Target: ${STONEYDSP_SIMD_TARGET_NAME} - adding header: ${STONEYDSP_SIMD_HEADER_FILE}")
        configure_file("${STONEYDSP_SIMD_HEADER_FILE}" "${STONEYDSP_SIMD_HEADER_FILE}")
        target_sources(${STONEYDSP_SIMD_TARGET_NAME}
            PUBLIC
            FILE_SET ${STONEYDSP_SIMD_HEADERS_FILESET_NAME}
            TYPE HEADERS
            BASE_DIRS
            $<BUILD_INTERFACE:${STONEYDSP_DIR}/${STONEYDSP_INCLUDE_DIR}>
            $<INSTALL_INTERFACE:${STONEYDSP_INCLUDE_DIR}>
            FILES
            $<BUILD_INTERFACE:${STONEYDSP_DIR}/${STONEYDSP_SIMD_HEADER_FILE}>
            $<INSTALL_INTERFACE:${STONEYDSP_SIMD_HEADER_FILE}>
        )
        message(VERBOSE "Target: ${STONEYDSP_SIMD_TARGET_NAME} - added header: ${STONEYDSP_SIMD_HEADER_FILE}")
    endforeach(STONEYDSP_SIMD_HEADER_FILE IN LISTS STONEYDSP_SIMD_HEADER_FILES)

    foreach(STONEYDSP_SIMD_SOURCE_FILE IN LISTS STONEYDSP_SIMD_SOURCE_FILES)
        message(DEBUG "Target: ${STONEYDSP_SIMD_TARGET_NAME} - adding source: ${STONEYDSP_SIMD_SOURCE_FILE}")
        target_sources(${STONEYDSP_SIMD_TARGET_NAME}
            PRIVATE
            "${STONEYDSP_SIMD_SOURCE_FILE}"
        )
        message(VERBOSE "Target: ${STONEYDSP_SIMD_TARGET_NAME} - added source: ${STONEYDSP_SIMD_SOURCE_FILE}")
    endforeach(STONEYDSP_SIMD_SOURCE_FILE IN LISTS STONEYDSP_SIMD_SOURCE_FILES)

    find_path(SIMDE_INCLUDE_DIRS "simde/x86/sse4.2.h")
    target_include_directories(${STONEYDSP_SIMD_TARGET_NAME} PRIVATE ${SIMDE_INCLUDE_DIRS})

    if(STONEYDSP_SIMD_TARGET_INSTALL)
        # Generate export set
        install(TARGETS ${STONEYDSP_SIMD_TARGET_NAME}
            EXPORT ${STONEYDSP_SIMD_TARGET_NAME}Install
            COMPONENT ${STONEYDSP_SIMD_TARGET_NAME}
            LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
            RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
            ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
            INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
            FILE_SET ${STONEYDSP_SIMD_HEADERS_FILESET_NAME} DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
        )

        # Install export set
        install(EXPORT ${STONEYDSP_SIMD_TARGET_NAME}Install
            FILE "${STONEYDSP_SLUG}-${STONEYDSP_SIMD_TARGET_NAME}-targets.cmake"
            NAMESPACE ${STONEYDSP_BRAND}::${STONEYDSP_SLUG}::
            DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${STONEYDSP_BRAND}"
        )
    endif()

    if(STONEYDSP_SIMD_TARGET_EXPORT)
        # Generate export set
        export(
            SETUP ${STONEYDSP_SIMD_TARGET_NAME}Export
            TARGET ${STONEYDSP_SIMD_TARGET_NAME}
        )

        # Install export set
        export(
            EXPORT ${STONEYDSP_SIMD_TARGET_NAME}Export
            FILE "lib/cmake/${STONEYDSP_BRAND}/${STONEYDSP_SLUG}-${STONEYDSP_SIMD_TARGET_NAME}-targets.cmake"
            NAMESPACE ${STONEYDSP_BRAND}::${STONEYDSP_SLUG}::
        )
    endif()

    set(STONEYDSP_SIMD_TARGET_NAME ${STONEYDSP_SIMD_TARGET_NAME} PARENT_SCOPE)
endfunction()
