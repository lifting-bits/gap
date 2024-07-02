# Copyright (c) 2021-present, Trail of Bits, Inc. All rights reserved.

add_headers(core GAP_CORE_HEADERS
	bigint.hpp
	common.hpp
	concepts.hpp
	config.hpp
	coroutine.hpp
	crtp.hpp
	dense_map.hpp
	generator.hpp
	hash.hpp
	memoize.hpp
	optional.hpp
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

add_gap_library(gap-core "${GAP_CORE_HEADERS}")
