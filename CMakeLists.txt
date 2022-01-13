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

include(GNUInstallDirs)
install(TARGETS gap-core gap-settings
	EXPORT gap-core-export
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
		COMPONENT Gap_Runtime
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
		COMPONENT Gap_Runtime
		NAMELINK_COMPONENT Gap_Development
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
		COMPONENT Gap_Development
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT gap-core-export
	FILE GapTargets.cmake
  NAMESPACE gap::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/gap-core
)
