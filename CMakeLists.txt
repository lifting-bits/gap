#
# Copyright (c) 2021-present, Trail of Bits, Inc.
# All rights reserved.
#
# This source code is licensed in accordance with the terms specified in
# the LICENSE file found in the root directory of this source tree.
#

cmake_minimum_required(VERSION 3.20)

# Fix behavior of CMAKE_CXX_STANDARD when targeting macOS.
if (POLICY CMP0025)
  cmake_policy(SET CMP0025 NEW)
endif ()

project(vast
    LANGUAGES C CXX
    VERSION 0.0.0
    DESCRIPTION "A utility library to bridge llvm and mlir gaps"
    HOMEPAGE_URL "https://github.com/lifting-bits/gap"
)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(GNUInstallDirs)

include(project_settings)

#
# CCACHE
#
find_program(CCACHE_PROGRAM ccache)
if (CCACHE_PROGRAM)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif()

#
# GAP build settings
#

add_library(gap_settings INTERFACE)

include(compiler_warnings)
set_project_warnings(gap_settings)

target_include_directories(gap_settings INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

# sanitizer options if supported by compiler
include(sanitizers)
enable_sanitizers(gap_settings)

# allow for static analysis options
include(static_analyzers)

#
# Core GAP libraries
#
add_subdirectory(core)

# test options
option(ENABLE_TESTING "Enable Test Builds" ON)

if (ENABLE_TESTING)
  enable_testing()
  add_subdirectory(test)
endif()
