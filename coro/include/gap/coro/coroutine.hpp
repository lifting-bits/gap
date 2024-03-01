// Copyright (c) 2024, Trail of Bits, Inc.

///////////////////////////////////////////////////////////////////////////////
// Copyright (c) Lewis Baker
// Licenced under MIT license. See LICENSE.txt for details.
///////////////////////////////////////////////////////////////////////////////
// This file is a modified version of cppcoro/coroutine.hpp from the cppcoro
// project. The original file is licenced under the MIT license and the original
// license is included above.
///////////////////////////////////////////////////////////////////////////////

#pragma once

#ifdef GAP_ENABLE_COROUTINES

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

#endif
