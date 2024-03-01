# Copyright (c) 2024, Trail of Bits, Inc. All rights reserved.

add_headers(coro GAP_CORO_HEADERS
	async_manual_reset_event.hpp
	awaitable_traits.hpp
	broken_promise.hpp
	coroutine.hpp
	fmap.hpp
	generator.hpp
	manual_reset_event.hpp
	recursive_generator.hpp
	single_consumer_event.hpp
	sync_wait.hpp
	task.hpp
	when_all_ready.hpp
)

add_sources(coro GAP_CORO_SOURCES
	async_manual_reset_event.cpp
)

add_gap_static_library(gap-coro "${GAP_CORO_HEADERS}" "${GAP_CORO_SOURCES}")

target_link_libraries(gap-coro PUBLIC gap-core)