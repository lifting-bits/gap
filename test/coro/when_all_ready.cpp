// Copyright (c) 2021-present, Trail of Bits, Inc.

///////////////////////////////////////////////////////////////////////////////
// Copyright (c) Lewis Baker
// Licenced under MIT license. See LICENSE.txt for details.
///////////////////////////////////////////////////////////////////////////////
// This file is a modified version of cppcoro/test/when_all_ready.cpp from
// the cppcoro project. The original file is licenced under the MIT license and
// the original license is included above.
///////////////////////////////////////////////////////////////////////////////

#ifdef GAP_ENABLE_COROUTINES

    #include <doctest/doctest.h>
    #include <gap/coro/async_manual_reset_event.hpp>
    #include <gap/coro/shared_task.hpp>
    #include <gap/coro/sync_wait.hpp>
    #include <gap/coro/task.hpp>
    #include <gap/coro/when_all_ready.hpp>

using namespace gap::coro;

namespace gap::test
{
    TEST_SUITE_BEGIN("when_all_ready");

    template<template<typename T> class TASK, typename T>
    TASK<T> when_event_set_return(gap::coro::async_manual_reset_event& event, T value)
    {
        co_await event;
        co_return std::move(value);
    }

    TEST_CASE("when_all_ready() with no args")
    {
        [[maybe_unused]] std::tuple<> result = gap::coro::sync_wait(gap::coro::when_all_ready());
    }

    TEST_CASE("when_all_ready() with one task")
    {
        bool started = false;
        auto f = [&](gap::coro::async_manual_reset_event& event) -> gap::coro::task<>
        {
            started = true;
            co_await event;
        };

        gap::coro::async_manual_reset_event event;
        auto when_all_awaitable = gap::coro::when_all_ready(f(event));
        CHECK(!started);

        bool finished = false;
        gap::coro::sync_wait(gap::coro::when_all_ready(
            [&]() -> gap::coro::task<>
        {
            auto&[t] = co_await when_all_awaitable;
            finished = true;
            t.result();
        }(),
            [&]() -> gap::coro::task<>
        {
            CHECK(started);
            CHECK(!finished);
            event.set();
            CHECK(finished);
            co_return;
        }()));
    }

    TEST_CASE("when_all_ready() with multiple task")
    {
        auto make_task = [&](bool& started, gap::coro::async_manual_reset_event& event, int result) -> gap::coro::task<int>
        {
            started = true;
            co_await event;
            co_return result;
        };

        gap::coro::async_manual_reset_event event1;
        gap::coro::async_manual_reset_event event2;
        bool started1 = false;
        bool started2 = false;
        auto when_all_awaitable = gap::coro::when_all_ready(
            make_task(started1, event1, 1),
            make_task(started2, event2, 2));
        CHECK(!started1);
        CHECK(!started2);

        bool when_all_awaitable_finished = false;

        gap::coro::sync_wait(gap::coro::when_all_ready(
            [&]() -> gap::coro::task<>
        {
            auto[t1, t2] = co_await std::move(when_all_awaitable);
            when_all_awaitable_finished = true;
            CHECK(t1.result() == 1);
            CHECK(t2.result() == 2);
        }(),
            [&]() -> gap::coro::task<>
        {
            CHECK(started1);
            CHECK(started2);

            event2.set();

            CHECK(!when_all_awaitable_finished);

            event1.set();

            CHECK(when_all_awaitable_finished);

            co_return;
        }()));
    }

    TEST_CASE("when_all_ready() with all task types")
    {
        gap::coro::async_manual_reset_event event;
        auto t0 = when_event_set_return<gap::coro::task>(event, 1);
        auto t1 = when_event_set_return<gap::coro::shared_task>(event, 2);

        auto all_tasks = gap::coro::when_all_ready(std::move(t0), t1);

        gap::coro::sync_wait(gap::coro::when_all_ready(
            [&]() -> gap::coro::task<>
        {
            auto [r0, r1] = co_await std::move(all_tasks);

            CHECK(r0.result() == 1);
            CHECK(r1.result() == 2);
        }(),
            [&]() -> gap::coro::task<>
        {
            event.set();
            co_return;
        }()));
    }

    TEST_CASE("when_all_ready() with std::vector<task<T>>")
    {
        gap::coro::async_manual_reset_event event;

        std::uint32_t started_count = 0;
        std::uint32_t finished_count = 0;

        auto make_task = [&]() -> gap::coro::task<>
        {
            ++started_count;
            co_await event;
            ++finished_count;
        };

        std::vector<gap::coro::task<>> tasks;
        for (std::uint32_t i = 0; i < 10; ++i)
        {
            tasks.emplace_back(make_task());
        }

        auto all_tasks = gap::coro::when_all_ready_vec(std::move(tasks));

        // Shouldn't have started any tasks yet.
        CHECK(started_count == 0u);

        gap::coro::sync_wait(gap::coro::when_all_ready(
            [&]() -> gap::coro::task<>
        {
            auto result_tasks = co_await std::move(all_tasks);
            CHECK(result_tasks.size() == 10u);

            for (auto& t : result_tasks)
            {
                CHECK_NOTHROW(t.result());
            }
        }(),
            [&]() -> gap::coro::task<>
        {
            CHECK(started_count == 10u);
            CHECK(finished_count == 0u);

            event.set();

            CHECK(finished_count == 10u);

            co_return;
        }()));
    }

    TEST_CASE("when_all_ready() with std::vector<shared_task<T>>")
    {
        gap::coro::async_manual_reset_event event;

        std::uint32_t started_count = 0;
        std::uint32_t finished_count = 0;

        auto make_task = [&]() -> gap::coro::shared_task<>
        {
            ++started_count;
            co_await event;
            ++finished_count;
        };

        std::vector<gap::coro::shared_task<>> tasks;
        for (std::uint32_t i = 0; i < 10; ++i)
        {
            tasks.emplace_back(make_task());
        }

        auto all_tasks = gap::coro::when_all_ready_vec(std::move(tasks));

        // Shouldn't have started any tasks yet.
        CHECK(started_count == 0u);

        gap::coro::sync_wait(gap::coro::when_all_ready(
            [&]() -> gap::coro::task<>
        {
            auto resultTasks = co_await std::move(all_tasks);
            CHECK(resultTasks.size() == 10u);

            for (auto& t : resultTasks)
            {
                CHECK_NOTHROW(t.result());
            }
        }(),
            [&]() -> gap::coro::task<>
        {
            CHECK(started_count == 10u);
            CHECK(finished_count == 0u);

            event.set();

            CHECK(finished_count == 10u);

            co_return;
        }()));
    }

    TEST_CASE("when_all_ready() doesn't rethrow exceptions")
    {
        auto make_task = [](bool throwException) -> gap::coro::task<int>
        {
            if (throwException)
            {
                throw std::exception{};
            }
            else
            {
                co_return 123;
            }
        };

        gap::coro::sync_wait([&]() -> gap::coro::task<>
        {
            try
            {
                auto[t0, t1] = co_await gap::coro::when_all_ready(make_task(true), make_task(false));

                // You can obtain the exceptions by re-awaiting the returned tasks.
                CHECK_THROWS_AS(t0.result(), const std::exception&);
                CHECK(t1.result() == 123);
            }
            catch (...)
            {
                FAIL("Shouldn't throw");
            }
        }());
    }

    TEST_SUITE_END();

} // namespace gap::test

#endif // GAP_ENABLE_COROUTINES
