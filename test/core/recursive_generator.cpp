// Copyright (c) 2021-present, Trail of Bits, Inc.

#ifdef GAP_ENABLE_COROUTINES

    #include <doctest/doctest.h>
    #include <gap/core/recursive_generator.hpp>

namespace gap::test
{
    TEST_CASE("empty recursive generator") {
        recursive_generator< std::uint32_t > ints;
        CHECK(ints.begin() == ints.end());
    }

    TEST_CASE("non-recursive use of recursive_generator") {
        auto f = []() -> recursive_generator< float > {
            co_yield 1.0f;
            co_yield 2.0f;
        };

        auto gen  = f();
        auto iter = gen.begin();
        CHECK_EQ(*iter, 1.0f);
        ++iter;
        CHECK_EQ(*iter, 2.0f);
        ++iter;
        CHECK_EQ(iter, gen.end());
    }

    TEST_CASE("throw before first yield") {
        class test_exception : public std::exception {};

        auto f = []() -> recursive_generator< std::uint32_t > {
            throw test_exception{};
            co_return;
        };

        auto gen = f();
        CHECK_THROWS_AS(gen.begin(), test_exception);
    }

    TEST_CASE("generator doesn't start executing until begin is called") {
        bool reachedA = false;
        bool reachedB = false;
        bool reachedC = false;
        auto f        = [&]() -> recursive_generator< std::uint32_t > {
            reachedA = true;
            co_yield 1;
            reachedB = true;
            co_yield 2;
            reachedC = true;
        };

        auto gen = f();
        CHECK(!reachedA);
        auto iter = gen.begin();
        CHECK(reachedA);
        CHECK(!reachedB);
        CHECK_EQ(*iter, 1u);
        ++iter;
        CHECK(reachedB);
        CHECK(!reachedC);
        CHECK_EQ(*iter, 2u);
        ++iter;
        CHECK(reachedC);
        CHECK_EQ(iter, gen.end());
    }

    TEST_CASE("simple recursive yield") {
        auto f = [](std::uint32_t n, auto& f) -> recursive_generator< const std::uint32_t > {
            co_yield n;
            if (n > 0) {
                co_yield f(n - 1, f);
                co_yield n;
            }
        };

        auto f2 = [&f](std::uint32_t n) { return f(n, f); };

        {
            auto gen  = f2(1);
            auto iter = gen.begin();
            CHECK_EQ(*iter, 1u);
            ++iter;
            CHECK_EQ(*iter, 0u);
            ++iter;
            CHECK_EQ(*iter, 1u);
            ++iter;
            CHECK_EQ(iter, gen.end());
        }

        {
            auto gen  = f2(2);
            auto iter = gen.begin();
            CHECK_EQ(*iter, 2u);
            ++iter;
            CHECK_EQ(*iter, 1u);
            ++iter;
            CHECK_EQ(*iter, 0u);
            ++iter;
            CHECK_EQ(*iter, 1u);
            ++iter;
            CHECK_EQ(*iter, 2u);
            ++iter;
            CHECK_EQ(iter, gen.end());
        }
    }

    TEST_CASE("nested yield that yields nothing") {
        auto f = []() -> recursive_generator< std::uint32_t > { co_return; };

        auto g = [&f]() -> recursive_generator< std::uint32_t > {
            co_yield 1;
            co_yield f();
            co_yield 2;
        };

        auto gen  = g();
        auto iter = gen.begin();
        CHECK_EQ(*iter, 1u);
        ++iter;
        CHECK_EQ(*iter, 2u);
        ++iter;
        CHECK_EQ(iter, gen.end());
    }

} // namespace gap::test

#endif // GAP_ENABLE_COROUTINES
