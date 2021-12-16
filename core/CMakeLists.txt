# Copyright (c) 2021-present, Trail of Bits, Inc. All rights reserved.
set(GAP_CORE_DIR src/core)

add_library(gap-core STATIC ${GAP_CORE_DIR}/source_location.cpp)

target_include_directories(
	gap-core PUBLIC $<INSTALL_INTERFACE:include> ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(gap-core INTERFACE gap_project_options gap_project_warnings)

add_library(gap::core ALIAS gap-core)
