# Copyright (c) 2021-present, Trail of Bits, Inc. All rights reserved.
set(GAP_CORE_DIR src/core)

add_library(gap-core STATIC ${GAP_CORE_DIR}/source_location.cpp)

target_compile_features(gap-core PRIVATE cxx_std_20)

target_include_directories(
	gap-core PUBLIC $<INSTALL_INTERFACE:include> ${CMAKE_CURRENT_SOURCE_DIR}/include
)

find_package(Coroutines COMPONENTS Experimental Final REQUIRED)

target_link_libraries(gap-core
	INTERFACE
		gap_settings
	PRIVATE
		std::coroutines
)

add_library(gap::core ALIAS gap-core)
