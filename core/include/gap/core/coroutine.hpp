// Copyright (c) 2021-present, Trail of Bits, Inc.

#pragma once

#include "gap/core/config.hpp"

#ifdef GAP_COROHEADER_FOUND_AND_USABLE

    #include <coroutine>

namespace gap
{
    using std::coroutine_handle;
    using std::noop_coroutine;
    using std::suspend_always;
    using std::suspend_never;

} // namespace gap

#elif __has_include(<experimental/coroutine>)

    #include <experimental/coroutine>

namespace gap
{
    using std::experimental::coroutine_handle;
    using std::experimental::suspend_always;
    using std::experimental::suspend_never;

    #if GAP_COMPILER_SUPPORTS_SYMMETRIC_TRANSFER
    using std::experimental::noop_coroutine;
    #endif
} // namespace gap

#else
    #error gap requires a C++20 compiler with coroutine support
#endif
