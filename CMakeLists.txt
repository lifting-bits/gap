# Copyright 2021-present, Trail of Bits, Inc. All rights reserved.

cmake_minimum_required(VERSION 3.22)

# Fix behavior of CMAKE_CXX_STANDARD when targeting macOS.
if (POLICY CMP0025)
  cmake_policy(SET CMP0025 NEW)
endif ()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

project(
  gap
  LANGUAGES C CXX
  VERSION 0.0.0
  DESCRIPTION "A utility library to bridge llvm and mlir gaps"
  HOMEPAGE_URL "https://github.com/lifting-bits/gap"
)

# Globally set the required C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

include(GNUInstallDirs)

# check if gap is being used directly or via add_subdirectory,
# but allow overriding
if(NOT DEFINED GAP_MASTER_PROJECT)
    if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
        set(GAP_MASTER_PROJECT ON)
    else()
        set(GAP_MASTER_PROJECT OFF)
    endif()
endif()

include(project_settings)
include(utils)

# adds header paths of library to list named var
function(add_headers lib var)
  set(headers ${${var}})
  foreach (header ${ARGN})
    set(headers ${headers} ${CMAKE_CURRENT_SOURCE_DIR}/include/gap/${lib}/${header})
  endforeach()
  set(${var} ${headers} PARENT_SCOPE)
endfunction()

# adds source paths of library to list named var
function(add_sources lib var)
  set(sources ${${var}})
  foreach (source ${ARGN})
    set(sources ${sources} ${CMAKE_CURRENT_SOURCE_DIR}/src/${source})
  endforeach()
  set(${var} ${sources} PARENT_SCOPE)
endfunction()

#
# CCACHE
#
find_program(CCACHE_PROGRAM ccache)
if (CCACHE_PROGRAM)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif ()

#
# GAP build settings
#
add_library(gap-settings INTERFACE)
add_library(gap::gap-settings ALIAS gap-settings)

option(GAP_ENABLE_WARNINGS "Enable extended warnings" ON)

if(GAP_ENABLE_WARNINGS)
  include(compiler_warnings)
  set_project_warnings(gap-settings)
endif()

target_include_directories(gap-settings
  INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# sanitizer options if supported by compiler
include(sanitizers)
enable_sanitizers(gap-settings)

# allow for static analysis options
include(static_analyzers)

option(GAP_ENABLE_COROUTINES "Enable coroutines" ON)

if (${GAP_ENABLE_COROUTINES})
  find_package(Coroutines COMPONENTS Experimental Final REQUIRED)
  target_compile_definitions(gap-settings INTERFACE GAP_ENABLE_COROUTINES)
  target_link_libraries(gap-settings INTERFACE std::coroutines)
endif()

#
# Core GAP libraries
#

add_subdirectory(core)
add_subdirectory(coro)
add_subdirectory(graph)

option(GAP_ENABLE_SARIF "Enable SARIF support" 
  $<IN_LIST:sarif,VCPKG_MANIFEST_FEATURES>
)

if (${GAP_ENABLE_SARIF})
  add_subdirectory(sarif)
endif()

option(GAP_ENABLE_MLIR "Enable MLIR support" OFF)

if (${GAP_ENABLE_MLIR})
  find_package(MLIR REQUIRED CONFIG)
  list(APPEND CMAKE_MODULE_PATH "${MLIR_CMAKE_DIR}")
  include(AddMLIR)

  add_subdirectory(mlir)
endif()

set(GAP_HEADERS
  ${GAP_CORE_HEADERS}
  ${GAP_CORO_HEADERS}
)

add_library(gap INTERFACE)
add_library(gap::gap ALIAS gap)

target_link_libraries(gap
  INTERFACE
    gap-core
    gap-coro
    gap-settings
)

set_target_properties(gap PROPERTIES PUBLIC_HEADER "${GAP_HEADERS}")

#
# testing support
#
option(GAP_ENABLE_TESTING "Enable GAP Test Builds" ON)

if (GAP_ENABLE_TESTING)
  include(CTest)
  enable_testing()
  add_subdirectory(test)
endif ()

#
# instalation support
#

option(GAP_INSTALL "Generate the install target." ${GAP_MASTER_PROJECT})

set_property(
  TARGET gap PROPERTY POSITION_INDEPENDENT_CODE ON
)

set_target_properties(${PROJECT_NAME}
  PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION ${PROJECT_VERSION_MAJOR}
)

if (GAP_INSTALL)
  set(GAP_CMAKE_INSTALL_DIR ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME} CACHE PATH "Path where CMake utilities will be installed")

  set(GAP_INSTALL_TARGETS gap gap-core gap-coro gap-settings)
  set(GAP_EXPORT_NAME gapTargets)

  install_gap_target(gap core)
  install_gap_target(gap-core core)
  install_gap_target(gap-settings core)
  install_gap_target(gap-coro coro)
  install_gap_target(gap-graph graph)

  if (${GAP_ENABLE_SARIF})
    install_gap_target(gap-sarif sarif)
  endif()

  if (${GAP_ENABLE_MLIR})
    install_gap_target(gap-mlir mlir)
  endif()

  #
  # packaging support
  #

  set(CPACK_PACKAGE_VENDOR "Trail of Bits")
  set(CPACK_PACKAGE_DESCRIPTION_SUMMARY
    "A utility library to bridge llvm and mlir gaps."
  )
  set(CPACK_PACKAGE_VERSION_MAJOR ${CMAKE_PROJECT_VERSION_MAJOR})
  set(CPACK_PACKAGE_VERSION_MINOR ${CMAKE_PROJECT_VERSION_MINOR})
  set(CPACK_PACKAGE_VERSION_PATCH ${CMAKE_PROJECT_VERSION_PATCH})
  set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
  set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")

  include(CPack)

  set(GAP_CONFIG_NAME "${PROJECT_NAME}Config")
  set(GAP_PACKAGE_CONFIG_FILE "${GAP_CONFIG_NAME}.cmake")
  set(GAP_PACKAGE_CONFIG_VERSION_FILE "${GAP_CONFIG_NAME}Version.cmake")

  include(CMakePackageConfigHelpers)

  configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/${GAP_CONFIG_NAME}.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/${GAP_PACKAGE_CONFIG_FILE}"
    INSTALL_DESTINATION ${GAP_CMAKE_INSTALL_DIR}
  )

  write_basic_package_version_file(
    ${GAP_PACKAGE_CONFIG_VERSION_FILE}
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY SameMajorVersion
  )

  install(FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindCoroutines.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${GAP_PACKAGE_CONFIG_FILE}"
    "${CMAKE_CURRENT_BINARY_DIR}/${GAP_PACKAGE_CONFIG_VERSION_FILE}"
    DESTINATION ${GAP_CMAKE_INSTALL_DIR}
  )

  install(FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/compiler_warnings.cmake"
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/sanitizers.cmake"
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/static_analyzers.cmake"
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/project_settings.cmake"
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/prevent_in_source_builds.cmake"
    DESTINATION ${GAP_CMAKE_INSTALL_DIR}
  )

endif()
