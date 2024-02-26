// Copyright (c) 2024, Trail of Bits, Inc.

#pragma once

#ifdef GAP_ENABLE_COROUTINES

    #include <stdexcept>

namespace gap::coro
{
    // Exception thrown when you attempt to retrieve the result of
    // a task that has been detached from its promise/coroutine.
    struct broken_promise : std::logic_error {
        broken_promise() : std::logic_error("broken promise") {}
    };
} // namespace gap::coro

#endif