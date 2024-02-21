# Copyright (c) 2024, Trail of Bits, Inc. All rights reserved.

add_headers(coro GAP_CORO_HEADERS
	coroutine.hpp
	generator.hpp
	recursive_generator.hpp
)

add_gap_library(gap-coro "${GAP_CORO_HEADERS}")

target_link_libraries(gap-coro INTERFACE gap-core)