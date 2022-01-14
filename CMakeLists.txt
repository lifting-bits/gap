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

set(GAP_CMAKE_INSTALL_DIR ${CMAKE_INSTALL_LIBDIR}/cmake/gap)
install(TARGETS gap-core gap-settings
	EXPORT gap-export
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
		COMPONENT Gap_Runtime
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
		COMPONENT Gap_Runtime
		NAMELINK_COMPONENT Gap_Development
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
		COMPONENT Gap_Development
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT gap-export
	FILE GapTargets.cmake
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

configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/config.cmake.in
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
  "${CMAKE_CURRENT_BINARY_DIR}/${GAP_PACKAGE_CONFIG_FILE}"
  "${CMAKE_CURRENT_BINARY_DIR}/${GAP_PACKAGE_CONFIG_VERSION_FILE}"
  DESTINATION ${GAP_CMAKE_INSTALL_DIR}
)
