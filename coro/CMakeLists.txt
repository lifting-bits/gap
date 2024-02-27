# Copyright (c) 2024, Trail of Bits, Inc. All rights reserved.

add_headers(coro GAP_CORO_HEADERS
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

add_gap_library(gap-coro "${GAP_CORO_HEADERS}")

target_link_libraries(gap-coro INTERFACE gap-core)