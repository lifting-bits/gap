// Copyright (c) 2021-present, Trail of Bits, Inc.

///////////////////////////////////////////////////////////////////////////////
// Copyright (c) Lewis Baker
// Licenced under MIT license. See LICENSE.txt for details.
///////////////////////////////////////////////////////////////////////////////
// This file is a modified version of cppcoro/test/shared_task.cpp from
// the cppcoro project. The original file is licenced under the MIT license and
// the original license is included above.
///////////////////////////////////////////////////////////////////////////////


#ifdef GAP_ENABLE_COROUTINES

    #include <doctest/doctest.h>
    #include <gap/coro/shared_task.hpp>
    #include <gap/coro/task.hpp>
    #include <gap/coro/sync_wait.hpp>
    #include <gap/coro/when_all_ready.hpp>
    #include <gap/coro/single_consumer_event.hpp>
    #include <gap/coro/fmap.hpp>

    #include <ostream>
    #include <string>

    #include "counted.hpp"

using namespace gap::coro;

namespace gap::test
{
    TEST_SUITE_BEGIN("shared_task");

    TEST_CASE("coroutine doesn't start executing until awaited")
    {
        bool startedExecuting = false;
        auto f = [&]() -> gap::coro::shared_task<>
        {
            startedExecuting = true;
            co_return;
        };

        auto t = f();

        CHECK(!t.is_ready());
        CHECK(!startedExecuting);

        gap::coro::sync_wait([](gap::coro::shared_task<> o) -> gap::coro::task<>
        {
            co_await o;
        }(t));

        CHECK(t.is_ready());
        CHECK(startedExecuting);
    }

    TEST_CASE("result is destroyed when last reference is destroyed")
    {
        counted::reset_counts();

        {
            auto t = []() -> gap::coro::shared_task<counted>
            {
                co_return counted{};
            }();

            CHECK(counted::active_count() == 0);

            gap::coro::sync_wait(t);

            CHECK(counted::active_count() == 1);
        }

        CHECK(counted::active_count() == 0);
    }

    TEST_CASE("multiple awaiters")
    {
        gap::coro::single_consumer_event event;
        bool startedExecution = false;
        auto produce = [&]() -> gap::coro::shared_task<int>
        {
            startedExecution = true;
            co_await event;
            co_return 1;
        };

        auto consume = [](gap::coro::shared_task<int> t) -> gap::coro::task<>
        {
            int result = co_await t;
            CHECK(result == 1);
        };

        auto sharedTask = produce();

        gap::coro::sync_wait(gap::coro::when_all_ready(
            consume(sharedTask),
            consume(sharedTask),
            consume(sharedTask),
            [&]() -> gap::coro::task<>
            {
                event.set();
                CHECK(sharedTask.is_ready());
                co_return;
            }()));

        CHECK(sharedTask.is_ready());
    }

    TEST_CASE("waiting on shared_task in loop doesn't cause stack-overflow")
    {
        // This test checks that awaiting a shared_task that completes
        // synchronously doesn't recursively resume the awaiter inside the
        // call to start executing the task. If it were to do this then we'd
        // expect that this test would result in failure due to stack-overflow.

        auto completesSynchronously = []() -> gap::coro::shared_task<int>
        {
            co_return 1;
        };

        gap::coro::sync_wait([&]() -> gap::coro::task<>
        {
            int result = 0;
            for (int i = 0; i < 1'000'000; ++i)
            {
                result += co_await completesSynchronously();
            }
            CHECK(result == 1'000'000);
        }());
    }

    TEST_CASE("make_shared_task")
    {
        bool startedExecution = false;

        auto f = [&]() -> gap::coro::task<std::string>
        {
            startedExecution = false;
            co_return "test";
        };

        auto t = f();

        gap::coro::shared_task<std::string> sharedT =
            gap::coro::make_shared_task(std::move(t));

        CHECK(!sharedT.is_ready());
        CHECK(!startedExecution);

        auto consume = [](gap::coro::shared_task<std::string> o) -> gap::coro::task<>
        {
            auto x = co_await std::move(o);
            CHECK(x == "test");
        };

        gap::coro::sync_wait(gap::coro::when_all_ready(
            consume(sharedT),
            consume(sharedT)));
    }

    TEST_CASE("make_shared_task of void"
        * doctest::description{ "Tests that workaround for 'co_return <void-expr>' bug is operational if required" })
    {
        bool startedExecution = false;

        auto f = [&]() -> gap::coro::task<>
        {
            startedExecution = true;
            co_return;
        };

        auto t = f();

        gap::coro::shared_task<> sharedT = gap::coro::make_shared_task(std::move(t));

        CHECK(!sharedT.is_ready());
        CHECK(!startedExecution);

        auto consume = [](gap::coro::shared_task<> o) -> gap::coro::task<>
        {
            co_await o;
        };

        auto c1 = consume(sharedT);
        gap::coro::sync_wait(c1);

        CHECK(startedExecution);

        auto c2 = consume(sharedT);
        gap::coro::sync_wait(c2);

        CHECK(c1.is_ready());
        CHECK(c2.is_ready());
    }

    TEST_CASE("shared_task<void> fmap operator")
    {
        gap::coro::single_consumer_event event;
        int value = 0;

        auto setNumber = [&]() -> gap::coro::shared_task<>
        {
            co_await event;
            value = 123;
        };

        gap::coro::sync_wait(gap::coro::when_all_ready(
            [&]() -> gap::coro::task<>
        {
            auto numericStringTask =
                setNumber()
                | gap::coro::fmap([&]() { return std::to_string(value); });

            auto result = co_await numericStringTask;
            CHECK(result == "123");
        }(),
            [&]() -> gap::coro::task<>
        {
            CHECK(value == 0);
            event.set();
            CHECK(value == 123);
            co_return;
        }()));
    }

    TEST_CASE("shared_task<T> fmap operator")
    {
        gap::coro::single_consumer_event event;

        auto getNumber = [&]() -> gap::coro::shared_task<int>
        {
            co_await event;
            co_return 123;
        };

        gap::coro::sync_wait(gap::coro::when_all_ready(
            [&]() -> gap::coro::task<>
        {
            auto numericStringTask =
                getNumber()
                | gap::coro::fmap([](int x) { return std::to_string(x); });
            auto result = co_await numericStringTask;
            CHECK(result == "123");
        }(),
            [&]() -> gap::coro::task<>
        {
            event.set();
            co_return;
        }()));
    }

    TEST_SUITE_END();
} // namespace gap::test

#endif