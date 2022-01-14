# Copyright (c) 2021-present, Trail of Bits, Inc. All rights reserved.
add_library(gap-core
	src/source_location.cpp
)

target_compile_features(gap-core PRIVATE cxx_std_20)

target_include_directories(gap-core
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    	$<INSTALL_INTERFACE:include>
)

find_package(Coroutines COMPONENTS Experimental Final REQUIRED)

target_link_libraries(gap-core
	INTERFACE
		gap-settings
	PRIVATE
		std::coroutines
)

add_library(gap::core ALIAS gap-core)
