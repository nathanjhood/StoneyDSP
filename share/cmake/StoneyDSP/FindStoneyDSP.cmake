#[=============================================================================[
  StoneyDSP.cmake
  Copyright (C) 2024 Nathan J. Hood
  MIT License
  See: https://github.com/StoneyDSP/StoneyDSP
]=============================================================================]#

#[=============================================================================[
Check whether we have already been included (borrowed from CMakeRC)
]=============================================================================]#
set(_stoneydsp_cmake_version 1.0.0)

cmake_minimum_required(VERSION 3.15)
cmake_policy(VERSION 3.15)
include(CMakeParseArguments)
include(CMakeDependentOption)

if(COMMAND stoneydsp_add_sources)
    if(NOT DEFINED _STONEYDSP_VERSION OR NOT (_stoneydsp_cmake_version STREQUAL _STONEYDSP_VERSION))
        message(WARNING "More than one 'StoneyDSP.cmake' version has been included in this project.")
    endif()
    # StoneyDSP.cmake has already been included! Don't do anything
    return()
endif()

set(_STONEYDSP_VERSION "${_stoneydsp_cmake_version}" CACHE INTERNAL "Current 'StoneyDSP.cmake' version. Used for checking for conflicts")
set(_STONEYDSP_SCRIPT  "${CMAKE_CURRENT_LIST_FILE}"  CACHE INTERNAL "Path to current 'StoneyDSP.cmake' script")

if(NOT DEFINED _STONEYDSP_JUCE_VERSION)
    set(_STONEYDSP_JUCE_VERSION 7.0.10 CACHE INTERNAL "Current 'StoneyDSP.cmake' JUCE version.")
endif()

message (STATUS "\n-- StoneyDSP.cmake v${_STONEYDSP_VERSION}")

#[=============================================================================[
 FUNCTIONS & MACROS
]=============================================================================]#

#[=============================================================================[
Calls ```find_package(JUCE ${VERSION} CONFIG REQUIRED)```.
]=============================================================================]#
macro(stoneydsp_find_juce _stoneydsp_juce_version)
    # Do some validation...
    # IDE support
    set (JUCE_ENABLE_MODULE_SOURCE_GROUPS ON)
    set_property(GLOBAL PROPERTY USE_FOLDERS YES)
    find_package (JUCE ${_stoneydsp_juce_version} CONFIG REQUIRED)
endmacro()

#[=============================================================================[
Internal helper (borrowed from CMakeRC).
]=============================================================================]#
function(_stoneydsp_normalize_path var)
    set(path "${${var}}")
    file(TO_CMAKE_PATH "${path}" path)
    while(path MATCHES "//")
        string(REPLACE "//" "/" path "${path}")
    endwhile()
    string(REGEX REPLACE "/+$" "" path "${path}")
    set("${var}" "${path}" PARENT_SCOPE)
endfunction()

#[=======================================================================[.rst:
FindStoneyDSP
-------------

Find StoneyDSP include dirs and modules

Use this module by invoking :command:`find_package` with the form:

.. code-block:: cmake

  find_package(StoneyDSP
    [version] [EXACT]      # Minimum or EXACT version e.g. 1.0.1
    [REQUIRED]             # Fail with error if StoneyDSP is not found
    [COMPONENTS <libs>...] # StoneyDSP modules by their canonical name
                           # e.g. "stoneydsp_audio" for "StoneyDSP::Filter"
    [OPTIONAL_COMPONENTS <libs>...]
                           # Optional StoneyDSP modules by their canonical name)
    )                      # e.g. "main" for "StoneyDSP::Main"

This module finds headers and requested component libraries OR a CMake
package configuration file provided by a "StoneyDSP CMake" build.  For the
latter case skip to the :ref:`StoneyDSP CMake` section below.

.. versionadded:: 1.0.1
  ``StoneyDSP`` CMake API component.

.. versionadded:: 1.0.0
  ``stoneydsp_core`` and ``stoneydsp_graphics`` components on all platforms.


Result Variables
^^^^^^^^^^^^^^^^

This module defines the following variables:

``StoneyDSP_FOUND``
  True if headers and requested libraries were found.

``StoneyDSP_INCLUDE_DIRS``
  StoneyDSP include directories.

``StoneyDSP_LIBRARY_DIRS``
  Link directories for StoneyDSP libraries.

``StoneyDSP_LIBRARIES``
  StoneyDSP component libraries to be linked.

``StoneyDSP_MODULE_DIRS``
  Link directories for StoneyDSP modules.

``StoneyDSP_MODULES``
  StoneyDSP component modules to be linked.

``StoneyDSP_<COMPONENT>_FOUND``
  True if component ``<COMPONENT>`` was found (``<COMPONENT>`` name is upper-case).

``StoneyDSP_<COMPONENT>_LIBRARY``
  Libraries to link for component ``<COMPONENT>`` (may include
  :command:`target_link_libraries` debug/optimized keywords).

``StoneyDSP_VERSION_MACRO``
  ``STONEYDSP_VERSION`` value from ``StoneyDSP/version.hpp``.

``StoneyDSP_VERSION_STRING``
  StoneyDSP version number in ``X.Y.Z`` format.

``StoneyDSP_VERSION``
  StoneyDSP version number in ``X.Y.Z`` format (same as ``StoneyDSP_VERSION_STRING``).

``StoneyDSP_LIB_VERSION``
  Version string appended to library filenames.

``StoneyDSP_VERSION_MAJOR``, ``StoneyDSP_MAJOR_VERSION``
  StoneyDSP major version number (``X`` in ``X.Y.Z``).

``StoneyDSP_VERSION_MINOR``, ``StoneyDSP_MINOR_VERSION``
  StoneyDSP minor version number (``Y`` in ``X.Y.Z``).

``StoneyDSP_VERSION_PATCH``, ``StoneyDSP_SUBMINOR_VERSION``
  StoneyDSP subminor version number (``Z`` in ``X.Y.Z``).

``StoneyDSP_VERSION_COUNT``
  Amount of version components (3).

Cache variables
^^^^^^^^^^^^^^^

Search results are saved persistently in CMake cache entries:

``StoneyDSP_INCLUDE_DIR``
  Directory containing StoneyDSP headers.

``StoneyDSP_LIBRARY_DIR_RELEASE``
  Directory containing release StoneyDSP libraries.

``StoneyDSP_LIBRARY_DIR_DEBUG``
  Directory containing debug StoneyDSP libraries.

``StoneyDSP_<COMPONENT>_LIBRARY_DEBUG``
  Component ``<COMPONENT>`` library debug variant.

``StoneyDSP_<COMPONENT>_LIBRARY_RELEASE``
  Component ``<COMPONENT>`` library release variant.

Hints
^^^^^

This module reads hints about search locations from variables:

``STONEYDSP_ROOT``, ``STONEYDSPROOT``
  Preferred installation prefix.

``STONEYDSP_INCLUDEDIR``
  Preferred include directory e.g. ``<prefix>/include``.

``STONEYDSP_LIBRARYDIR``
  Preferred library directory e.g. ``<prefix>/lib``.

``StoneyDSP_NO_SYSTEM_PATHS``
  Set to ``ON`` to disable searching in locations not
  specified by these hint variables. Default is ``OFF``.

``StoneyDSP_ADDITIONAL_VERSIONS``
  List of StoneyDSP versions not known to this module.
  (StoneyDSP install locations may contain the version).

Users may set these hints or results as ``CACHE`` entries.  Projects
should not read these entries directly but instead use the above
result variables.  Note that some hint names start in upper-case
``STONEYDSP``.  One may specify these as environment variables if they are
not specified as CMake variables or cache entries.

Imported Targets
^^^^^^^^^^^^^^^^

This module defines the following :prop_tgt:`IMPORTED` targets:

``StoneyDSP::stoneydsp``
  Target for header-only dependencies. (StoneyDSP include directory).

``StoneyDSP::headers``

``StoneyDSP::<component>``
  Target for specific component dependency (shared or static library);
  ``<component>`` name is lower-case.

Implicit dependencies such as ``StoneyDSP::foobar`` requiring
``StoneyDSP::foo`` will be automatically detected and satisfied, even
if foo is not specified when using :command:`find_package` and if
``StoneyDSP::foo`` is not added to :command:`target_link_libraries`.  If using
``StoneyDSP::Resources``, then ``CMakeRC::cmrc`` will also be added automatically.

It is important to note that the imported targets behave differently
than variables created by this module: multiple calls to
:command:`find_package(StoneyDSP)` in the same directory or sub-directories with
different options (e.g. static or shared) will not override the
values of the targets created by the first call.

Other Variables
^^^^^^^^^^^^^^^

StoneyDSP libraries come in many variants encoded in their file name.
Users or projects may tell this module which variant to find by
setting variables:

``StoneyDSP_USE_DEBUG_LIBS``

  Set to ``ON`` or ``OFF`` to specify whether to search and use the debug
  libraries.  Default is ``ON``.

``StoneyDSP_USE_RELEASE_LIBS``

  Set to ``ON`` or ``OFF`` to specify whether to search and use the release
  libraries.  Default is ``ON``.

``StoneyDSP_USE_DEBUG_RUNTIME``
  Set to ``ON`` or ``OFF`` to specify whether to use libraries linked to the
  MS debug C++ runtime ("g" tag).  Default is ``ON``.

Other variables one may set to control this module are:

``StoneyDSP_DEBUG``
  Set to ``ON`` to enable debug output from ``FindStoneyDSP``.
  Please enable this before filing any bug report.

``StoneyDSP_LIBRARY_DIR``
  Default value for ``StoneyDSP_LIBRARY_DIR_RELEASE`` and
  ``StoneyDSP_LIBRARY_DIR_DEBUG``.

Examples
^^^^^^^^

Find StoneyDSP headers and some (release only) libraries/modules:

.. code-block:: cmake

  set(StoneyDSP_USE_DEBUG_LIBS        OFF)  # ignore debug libs and
  set(StoneyDSP_USE_RELEASE_LIBS       ON)  # only find release libs
  find_package(StoneyDSP 1.0.1 COMPONENTS cli stoneydsp_core ...)
  if(StoneyDSP_FOUND)
    include_directories(${StoneyDSP_INCLUDE_DIRS})
    add_executable(foo foo.cc)
    target_link_libraries(foo ${StoneyDSP_LIBRARIES})
  endif()

.. _`StoneyDSP CMake`:

StoneyDSP CMake
^^^^^^^^^^^

If StoneyDSP was built using the stoneydsp-cmake project,
it provides a package configuration file for use with find_package's config mode.
This module looks for the package configuration file called
``StoneyDSPConfig.cmake`` or ``stoneydsp-config.cmake`` and stores the result in
``CACHE`` entry ``STONEYDSP_DIR``.  If found, the package configuration file is loaded
and this module returns with no further action.  See documentation of
the Boost CMake package configuration for details on what it provides.

Set ``StoneyDSP_NO_BOOST_CMAKE`` to ``ON``, to disable the search for stoneydsp-cmake.

]=======================================================================]#

#[=============================================================================[
 DEPENDENCIES
]=============================================================================]#

# if (EXISTS "${CMAKE_CURRENT_LIST_DIR}/ext/juce-framework/JUCE/CMakeLists.txt")
if (TRUE)
    stoneydsp_find_juce(${_STONEYDSP_JUCE_VERSION})
endif ()

#[=============================================================================[
 PATHS
]=============================================================================]#

set(STONEYDSP_MODULE_PATH "${StoneyDSP_SOURCE_DIR}/modules" CACHE PATH "")

#[=============================================================================[
 MODULES
]=============================================================================]#

juce_add_module(
    # StoneyDSP::stoneydsp_core
    "${STONEYDSP_MODULE_PATH}/stoneydsp_core"
    ALIAS_NAMESPACE StoneyDSP
    INSTALL_PATH "include/StoneyDSP/v${STONEYDSP_VERSION}/modules"
)
juce_add_module(
    # StoneyDSP::stoneydsp_audio
    "${STONEYDSP_MODULE_PATH}/stoneydsp_audio"
    ALIAS_NAMESPACE StoneyDSP
    INSTALL_PATH "include/StoneyDSP/v${STONEYDSP_VERSION}/modules"
)
juce_add_module(
    # StoneyDSP::stoneydsp_graphics
    "${STONEYDSP_MODULE_PATH}/stoneydsp_graphics"
    ALIAS_NAMESPACE StoneyDSP
    INSTALL_PATH "include/StoneyDSP/v${STONEYDSP_VERSION}/modules"
)
juce_add_module(
    # StoneyDSP::stoneydsp_web
    "${STONEYDSP_MODULE_PATH}/stoneydsp_web"
    ALIAS_NAMESPACE StoneyDSP
    INSTALL_PATH "include/StoneyDSP/v${STONEYDSP_VERSION}/modules"
)

#[=============================================================================[
 CLEANUP
]=============================================================================]#

unset(_stoneydsp_cmake_version)
