# Copyright (c) 2024, Trail of Bits, Inc. All rights reserved.

add_headers(coro GAP_CORO_HEADERS
	awaitable_traits.hpp
	broken_promise.hpp
	coroutine.hpp
	generator.hpp
	manual_reset_event.hpp
	recursive_generator.hpp
	sync_wait.hpp
	sync_wait_task.hpp
	task.hpp
)

add_gap_library(gap-coro "${GAP_CORO_HEADERS}")

target_link_libraries(gap-coro INTERFACE gap-core)