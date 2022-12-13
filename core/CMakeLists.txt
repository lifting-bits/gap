# Copyright (c) 2021-present, Trail of Bits, Inc. All rights reserved.

add_headers(core GAP_CORE_HEADERS
	bigint.hpp
	common.hpp
	concepts.hpp
	config.hpp
	coroutine.hpp
	dense_map.hpp
	graph.hpp
	generator.hpp
	hash.hpp
	memoize.hpp
	overloads.hpp
	parser.hpp
	pointer.hpp
	ranges.hpp
	recursive_generator.hpp
	source_location.hpp
	strong_type.hpp
	fixed_string.hpp
	type_traits.hpp
	union_find.hpp
)

add_library(gap-core INTERFACE)

add_library(gap::gap-core ALIAS gap-core)

target_compile_features(gap-core INTERFACE cxx_std_20)

target_include_directories(gap-core
	INTERFACE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

set_target_properties(gap-core PROPERTIES PUBLIC_HEADER "${GAP_CORE_HEADERS}")

target_link_libraries(gap-core INTERFACE gap-settings)
