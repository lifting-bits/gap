// Copyright (c) 2021-present, Trail of Bits, Inc.

///////////////////////////////////////////////////////////////////////////////
// Copyright (c) Lewis Baker
// Licenced under MIT license. See LICENSE.txt for details.
///////////////////////////////////////////////////////////////////////////////
// This file is a modified version of cppcoro/test/task.cpp from the cppcoro
// project. The original file is licenced under the MIT license and the original
// license is included above.
///////////////////////////////////////////////////////////////////////////////

#ifdef GAP_ENABLE_COROUTINES

    #include <doctest/doctest.h>
    #include <gap/coro/fmap.hpp>
    #include <gap/coro/single_consumer_event.hpp>
    #include <gap/coro/sync_wait.hpp>
    #include <gap/coro/task.hpp>
    #include <gap/coro/when_all_ready.hpp>

    #include "counted.hpp"

using namespace gap::coro;

namespace gap::test
{

    TEST_SUITE_BEGIN("task");

    TEST_CASE("task doesn't start until awaited") {
        bool started = false;
        auto func    = [&]() -> gap::coro::task<> {
            started = true;
            co_return;
        };

        gap::coro::sync_wait([&]() -> gap::coro::task<> {
            auto t = func();
            CHECK(!started);

            co_await t;

            CHECK(started);
        }());
    }

    TEST_CASE("awaiting task that completes asynchronously") {
        bool reached_before_event = false;
        bool reached_after_event  = false;
        gap::coro::single_consumer_event event;
        auto f = [&]() -> gap::coro::task<> {
            reached_before_event = true;
            co_await event;
            reached_after_event = true;
        };

        gap::coro::sync_wait([&]() -> gap::coro::task<> {
            auto t = f();

            CHECK(!reached_before_event);

            (void) co_await gap::coro::when_all_ready(
                [&]() -> gap::coro::task<> {
                    co_await t;
                    CHECK(reached_before_event);
                    CHECK(reached_after_event);
                }(),
                [&]() -> gap::coro::task<> {
                    CHECK(reached_before_event);
                    CHECK(!reached_after_event);
                    event.set();
                    CHECK(reached_after_event);
                    co_return;
                }());
        }());
    }

    TEST_CASE("destroying task that was never awaited destroys captured args") {
        counted::reset_counts();

        auto f = [](counted c) -> gap::coro::task< counted > { co_return c; };

        CHECK(counted::active_count() == 0);

        {
            auto t = f(counted{});
            CHECK(counted::active_count() == 1);
        }

        CHECK(counted::active_count() == 0);
    }

    TEST_CASE("task destructor destroys result") {
        counted::reset_counts();

        auto f = []() -> gap::coro::task< counted > { co_return counted{}; };

        {
            auto t = f();
            CHECK(counted::active_count() == 0);

            auto& result = gap::coro::sync_wait(t);

            CHECK(counted::active_count() == 1);
            CHECK(result.id == 0);
        }

        CHECK(counted::active_count() == 0);
    }

    TEST_CASE("task of reference type") {
        int value = 3;
        auto f    = [&]() -> gap::coro::task< int& > { co_return value; };

        gap::coro::sync_wait([&]() -> gap::coro::task<> {
            SUBCASE("awaiting rvalue task") {
                decltype(auto) result = co_await f();
                static_assert(
                    std::is_same< decltype(result), int& >::value,
                    "co_await r-value reference of task<int&> should result in an int&");
                CHECK(&result == &value);
            }

            SUBCASE("awaiting lvalue task") {
                auto t                = f();
                decltype(auto) result = co_await t;
                static_assert(
                    std::is_same< decltype(result), int& >::value,
                    "co_await l-value reference of task<int&> should result in an int&");
                CHECK(&result == &value);
            }
        }());
    }

    TEST_CASE("passing parameter by value to task coroutine calls move-constructor exactly once") {
        counted::reset_counts();

        auto f = [](counted) -> gap::coro::task<> { co_return; };

        counted c;

        CHECK(counted::active_count() == 1);
        CHECK(counted::default_construction_count == 1);
        CHECK(counted::copy_construction_count == 0);
        CHECK(counted::move_construction_count == 0);
        CHECK(counted::destruction_count == 0);

        {
            auto t = f(c);

            // Should have called copy-constructor to pass a copy of 'c' into f by value.
            CHECK(counted::copy_construction_count == 1);

            // Inside f it should have move-constructed parameter into coroutine frame variable
            // WARN_MESSAGE(counted::move_construction_count == 1,
            //	"Known bug in MSVC 2017.1, not critical if it performs multiple moves");

            // Active counts should be the instance 'c' and the instance captured in coroutine frame
            // of 't'.
            CHECK(counted::active_count() == 2);
        }

        CHECK(counted::active_count() == 1);
    }

    TEST_CASE("task<void> fmap pipe operator") {
        using gap::coro::fmap;

        gap::coro::single_consumer_event event;

        auto f = [&]() -> gap::coro::task<> {
            co_await event;
            co_return;
        };

        auto t = f() | fmap([] { return 123; });

        gap::coro::sync_wait(gap::coro::when_all_ready(
            [&]() -> gap::coro::task<> {
                auto result = co_await t;
                CHECK(result == 123); }(),
            [&]() -> gap::coro::task<> {
                event.set();
                co_return;
            }()));
    }

    TEST_CASE("task<int> fmap pipe operator") {
        using gap::coro::fmap;
        using gap::coro::make_task;
        using gap::coro::sync_wait;
        using gap::coro::task;

        auto one = [&]() -> task< int > { co_return 1; };

        SUBCASE("r-value fmap / r-value lambda") {
            auto t = one() | fmap([delta = 1](auto i) { return i + delta; });
            CHECK(sync_wait(t) == 2);
        }

        SUBCASE("r-value fmap / l-value lambda") {
            using namespace std::string_literals;

            auto t = [&] {
                auto f = [prefix = "pfx"s](int x) { return prefix + std::to_string(x); };

                // Want to make sure that the resulting awaitable has taken
                // a copy of the lambda passed to fmap().
                return one() | fmap(f);
            }();

            CHECK(sync_wait(t) == "pfx1");
        }

        SUBCASE("l-value fmap / r-value lambda") {
            using namespace std::string_literals;

            auto t = [&] {
                auto addprefix = fmap(
                    [prefix
                     = "a really really long prefix that prevents small string optimisation"s](
                        int x) { return prefix + std::to_string(x); });

                // Want to make sure that the resulting awaitable has taken
                // a copy of the lambda passed to fmap().
                return one() | addprefix;
            }();

            CHECK(
                sync_wait(t)
                == "a really really long prefix that prevents small string optimisation1");
        }

        SUBCASE("l-value fmap / l-value lambda") {
            using namespace std::string_literals;

            task< std::string > t;

            {
                auto lambda
                    = [prefix
                       = "a really really long prefix that prevents small string optimisation"s](
                          int x) { return prefix + std::to_string(x); };

                auto addprefix = fmap(lambda);

                // Want to make sure that the resulting task has taken
                // a copy of the lambda passed to fmap().
                t = make_task(one() | addprefix);
            }

            CHECK(!t.is_ready());

            CHECK(
                sync_wait(t)
                == "a really really long prefix that prevents small string optimisation1");
        }
    }

    TEST_CASE("chained fmap pipe operations") {
        using namespace std::string_literals;
        using gap::coro::sync_wait;
        using gap::coro::task;

        auto prepend = [](std::string s) {
            using gap::coro::fmap;
            return fmap([s = std::move(s)](const std::string& value) { return s + value; });
        };

        auto append = [](std::string s) {
            using gap::coro::fmap;
            return fmap([s = std::move(s)](const std::string& value) { return value + s; });
        };

        auto asyncString = [](std::string s) -> task< std::string > { co_return std::move(s); };

        auto t = asyncString("base"s) | prepend("pre_"s) | append("_post"s);

        CHECK(sync_wait(t) == "pre_base_post");
    }

    TEST_CASE("lots of synchronous completions doesn't result in stack-overflow") {
        auto completes_synchronously = []() -> gap::coro::task< int > { co_return 1; };

        auto run = [&]() -> gap::coro::task<> {
            int sum = 0;
            for (int i = 0; i < 1'000'000; ++i) {
                sum += co_await completes_synchronously();
            }
            CHECK(sum == 1'000'000);
        };

        gap::coro::sync_wait(run());
    }

    TEST_SUITE_END();

} // namespace gap::test

#endif // GAP_ENABLE_COROUTINES
