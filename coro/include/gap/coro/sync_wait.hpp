// Copyright (c) 2024, Trail of Bits, Inc.

#pragma once

#ifdef GAP_ENABLE_COROUTINES

#include <gap/coro/awaitable_traits.hpp>
#include <gap/coro/manual_reset_event.hpp>
#include <gap/coro/sync_wait_task.hpp>

namespace gap::coro
{
    namespace detail {

    }

    template< awaitable awaitable_t >
    decltype(auto) sync_wait(awaitable_t &&awaitable) {
        auto task = make_sync_wait_task(std::forward< awaitable_t >(awaitable));

        manual_reset_event event;
        task.start(event);
        event.wait();
        return task.result();
    }
} // namespace gap::coro

#endif