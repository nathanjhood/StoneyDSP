include (GetGitRef)

if (NOT DEFINED git_revision)
  get_git_ref ()
endif ()

macro (write_version_header)

  set(_STONEYDSP_HEADER_FILE "${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/version.h")

  file(WRITE "${_STONEYDSP_HEADER_FILE}.tmp" "// ${PROJECT_NAME} v${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}.${git_revision}\n")
  file(APPEND "${_STONEYDSP_HEADER_FILE}.tmp" "// Version control info\n")
  file(APPEND "${_STONEYDSP_HEADER_FILE}.tmp" "\n")

  file(APPEND "${_STONEYDSP_HEADER_FILE}.tmp" "#ifndef ${PROJECT_NAME}_VERSION_H_\n")
  file(APPEND "${_STONEYDSP_HEADER_FILE}.tmp" "#define ${PROJECT_NAME}_VERSION_H_\n")
  file(APPEND "${_STONEYDSP_HEADER_FILE}.tmp" "\n")

  file(APPEND "${_STONEYDSP_HEADER_FILE}.tmp" "#define ${PROJECT_NAME}_VERSION_MAJOR \"${PROJECT_VERSION_MAJOR}\"\n")
  file(APPEND "${_STONEYDSP_HEADER_FILE}.tmp" "#define ${PROJECT_NAME}_VERSION_MINOR \"${PROJECT_VERSION_MINOR}\"\n")
  file(APPEND "${_STONEYDSP_HEADER_FILE}.tmp" "#define ${PROJECT_NAME}_VERSION_PATCH \"${PROJECT_VERSION_PATCH}\"\n")

  if(DEFINED git_revision)
      file(APPEND "${_STONEYDSP_HEADER_FILE}.tmp" "#define ${PROJECT_NAME}_VERSION_TWEAK \"${git_revision}\"\n")
      file(APPEND "${_STONEYDSP_HEADER_FILE}.tmp" "#define ${PROJECT_NAME}_VERSION \"${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}.${git_revision}\"\n")
  else()
      file(APPEND "${_STONEYDSP_HEADER_FILE}.tmp" "#undef ${PROJECT_NAME}_VERSION_TWEAK\n")
      file(APPEND "${_STONEYDSP_HEADER_FILE}.tmp" "#define ${PROJECT_NAME}_VERSION \"${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}\"\n")
  endif()

  if(git_url)
      file(APPEND "${_STONEYDSP_HEADER_FILE}.tmp" "#define ${PROJECT_NAME}_REPOSITORY \"${git_url}\"\n")
  else()
      file(APPEND "${_STONEYDSP_HEADER_FILE}.tmp" "#undef ${PROJECT_NAME}_REPOSITORY\n")
  endif()

  file(APPEND "${_STONEYDSP_HEADER_FILE}.tmp" "\n")
  file(APPEND "${_STONEYDSP_HEADER_FILE}.tmp" "#endif // ${PROJECT_NAME}_VERSION_H_\n")
  file(APPEND "${_STONEYDSP_HEADER_FILE}.tmp" "\n")

  #Copy the file only if it has changed.
  execute_process(COMMAND ${CMAKE_COMMAND} -E copy_if_different "${_STONEYDSP_HEADER_FILE}.tmp" "${_STONEYDSP_HEADER_FILE}")
  file(REMOVE "${_STONEYDSP_HEADER_FILE}.tmp")
endmacro ()
