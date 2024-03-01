// Copyright (c) 2024, Trail of Bits, Inc.

///////////////////////////////////////////////////////////////////////////////
// Copyright (c) Lewis Baker
// Licenced under MIT license. See LICENSE.txt for details.
///////////////////////////////////////////////////////////////////////////////
// This file is a modified version of cppcoro/broken_promise.hpp from
// the cppcoro project. The original file is licenced under the MIT license and
// the original license is included above.
///////////////////////////////////////////////////////////////////////////////

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