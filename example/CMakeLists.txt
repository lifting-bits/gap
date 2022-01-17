# Copyright 2022-present, Trail of Bits, Inc. All rights reserved.

cmake_minimum_required(VERSION 3.20)

project(gap-example LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

if (DEFINED ENV{GAP_INSTALL_DIR} AND NOT GAP_INSTALL_DIR)
    set(GAP_INSTALL_DIR $ENV{GAP_INSTALL_DIR})
endif ()

if (GAP_INSTALL_DIR)
    if (NOT EXISTS "${GAP_INSTALL_DIR}")
      message(FATAL_ERROR "GAP_INSTALL_DIR directory does not exist: '${GAP_INSTALL_DIR}'")
    endif ()
else ()
    message(FATAL_ERROR "Please define a path to GAP_INSTALL_DIR.")
endif ()

list(APPEND CMAKE_MODULE_PATH "${GAP_INSTALL_DIR}/lib/cmake/gap")

find_package(gap REQUIRED)
find_package(Coroutines COMPONENTS Experimental Final REQUIRED)

add_executable(coroutines-example
    coroutines-example.cpp
)

target_link_libraries(coroutines-example
    PRIVATE gap::gap-core
)
