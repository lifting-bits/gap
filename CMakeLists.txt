# Copyright 2021-present, Trail of Bits, Inc. All rights reserved.

cmake_minimum_required(VERSION 3.20)

# Fix behavior of CMAKE_CXX_STANDARD when targeting macOS.
if (POLICY CMP0025)
  cmake_policy(SET CMP0025 NEW)
endif ()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(vcpkg_setup)

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

# heck if gap is being used directly or via add_subdirectory,
# but allow overriding
if(NOT DEFINED GAP_MASTER_PROJECT)
    if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
        set(GAP_MASTER_PROJECT ON)
    else()
        set(GAP_MASTER_PROJECT OFF)
    endif()
endif()

include(project_settings)

# adds header paths of library to list named var
function(add_headers lib var)
  set(headers ${${var}})
  foreach (header ${ARGN})
    set(headers ${headers} ${CMAKE_CURRENT_SOURCE_DIR}/include/gap/${lib}/${header})
  endforeach()
  set(${var} ${headers} PARENT_SCOPE)
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

include(compiler_warnings)
set_project_warnings(gap-settings)

target_include_directories(gap-settings
  INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# sanitizer options if supported by compiler
include(sanitizers)
enable_sanitizers(gap-settings)

# allow for static analysis options
include(static_analyzers)

#
# Core GAP libraries
#

add_subdirectory(core)

set(GAP_HEADERS
  ${GAP_CORE_HEADERS}
)

add_library(gap INTERFACE)
target_link_libraries(gap
  INTERFACE
    gap-core
    gap-settings
)

target_include_directories(gap
  INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

set_target_properties(gap PROPERTIES PUBLIC_HEADER "${GAP_HEADERS}")

add_library(gap::gap ALIAS gap)

#
# testing support
#
option(ENABLE_TESTING "Enable Test Builds" ON)

if (ENABLE_TESTING)
  enable_testing()
  add_subdirectory(test)
endif ()

#
# instalation support
#

option(GAP_INSTALL "Generate the install target." ${GAP_MASTER_PROJECT})

if (GAP_INSTALL)
  set(GAP_CMAKE_INSTALL_DIR ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})
  set(GAP_SCRIPTS_INSTALL_DIR ${CMAKE_INSTALL_LIBDIR}/scripts/)

  set(GAP_INSTALL_TARGETS gap gap-core gap-settings)
  set(GAP_EXPORT_NAME GapTargets)

  install(TARGETS ${GAP_INSTALL_TARGETS}
    EXPORT ${GAP_EXPORT_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/gap/core
  )

  install(EXPORT ${GAP_EXPORT_NAME}
    FILE ${GAP_EXPORT_NAME}.cmake
    NAMESPACE gap::
    DESTINATION ${GAP_CMAKE_INSTALL_DIR}
  )

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

  set(GAP_CONFIG_NAME "GapConfig")
  set(GAP_PACKAGE_CONFIG_FILE "${GAP_CONFIG_NAME}.cmake")
  set(GAP_PACKAGE_CONFIG_VERSION_FILE "${GAP_CONFIG_NAME}Version.cmake")

  include(CMakePackageConfigHelpers)

  configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/${GAP_CONFIG_NAME}.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/${GAP_PACKAGE_CONFIG_FILE}"
    INSTALL_DESTINATION ${GAP_CMAKE_INSTALL_DIR}
    NO_CHECK_REQUIRED_COMPONENTS_MACRO
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
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/vcpkg_setup.cmake"
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/vcpkg_setup.cmake"
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/sanitizers.cmake"
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/static_analyzers.cmake"
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/project_settings.cmake"
    DESTINATION ${GAP_SCRIPTS_INSTALL_DIR}
  )

endif()
