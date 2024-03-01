// Copyright (c) 2021-present, Trail of Bits, Inc.

///////////////////////////////////////////////////////////////////////////////
// Copyright (c) Lewis Baker
// Licenced under MIT license. See LICENSE.txt for details.
///////////////////////////////////////////////////////////////////////////////
// This file is a modified version of cppcoro/test/sync_wait.cpp from
// the cppcoro project. The original file is licenced under the MIT license and
// the original license is included above.
///////////////////////////////////////////////////////////////////////////////

#ifdef GAP_ENABLE_COROUTINES

    #include <doctest/doctest.h>
    #include <gap/coro/sync_wait.hpp>

    #include <gap/core/config.hpp>
    #include <gap/core/on_scope_exit.hpp>

    #include <gap/coro/task.hpp>
    #include <gap/coro/shared_task.hpp>

    #include <string>
    #include <type_traits>

using namespace gap::coro;

namespace gap::test
{
    TEST_SUITE_BEGIN("sync_wait");

    static_assert(std::is_same<
        decltype(gap::coro::sync_wait(std::declval<gap::coro::task<std::string>>())),
        std::string&&>::value);
    static_assert(std::is_same<
        decltype(gap::coro::sync_wait(std::declval<gap::coro::task<std::string>&>())),
        std::string&>::value);

    TEST_CASE("sync_wait(task<T>)")
    {
        auto makeTask = []() -> gap::coro::task<std::string>
        {
            co_return "foo";
        };

        auto task = makeTask();
        CHECK(gap::coro::sync_wait(task) == "foo");

        CHECK(gap::coro::sync_wait(makeTask()) == "foo");
    }

    TEST_CASE("sync_wait(shared_task<T>)")
    {
        auto makeTask = []() -> gap::coro::shared_task<std::string>
        {
            co_return "foo";
        };

        auto task = makeTask();

        CHECK(gap::coro::sync_wait(task) == "foo");
        CHECK(gap::coro::sync_wait(makeTask()) == "foo");
    }

    TEST_SUITE_END();

} // namespace gap::test
#endif