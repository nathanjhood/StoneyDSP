include (GetGitRef)

if (NOT DEFINED STONEYDSP_GIT_COMMIT_REF)
    stoneydsp_get_git_ref ()
endif ()

#[=============================================================================[
Provides:

    STONEYDSP_VERSION_FILE

]=============================================================================]#
macro (stoneydsp_write_version_file)
    set(STONEYDSP_VERSION_FILE "${StoneyDSP_SOURCE_DIR}/VERSION")
    file(WRITE "${STONEYDSP_VERSION_FILE}.tmp" "${STONEYDSP_VERSION_MAJOR}.${STONEYDSP_VERSION_MINOR}.${STONEYDSP_VERSION_PATCH}.${STONEYDSP_VERSION_TWEAK}\n")

    #Copy the file only if it has changed.
    execute_process(COMMAND ${CMAKE_COMMAND} -E copy_if_different "${STONEYDSP_VERSION_FILE}.tmp" "${STONEYDSP_VERSION_FILE}")
    file(REMOVE "${STONEYDSP_VERSION_FILE}.tmp")
endmacro ()
