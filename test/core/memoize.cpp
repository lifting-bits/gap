// Copyright (c) 2022-present, Trail of Bits, Inc.

#include <doctest/doctest.h>
#include <gap/core/concepts.hpp>
#include <gap/core/memoize.hpp>

#include <iostream>

namespace gap::test
{
    void checks_addition(auto fn) {
        CHECK_EQ(fn(1, 2), 3);

        CHECK_EQ(fn.cache_size(), 1);
        CHECK( fn.cached(1, 2));
        CHECK(!fn.cached(2, 1));

        CHECK_EQ(fn(2, 1), 3);

        CHECK_EQ(fn.cache_size(), 2);
        CHECK(fn.cached(2, 1));
    }

    void checks_fib(auto fn) {
        CHECK_EQ(fn(1), 1);
        CHECK_EQ(fn.cache_size(), 1);
        CHECK(!fn.cached(0));

        CHECK_EQ(fn(5), 5);
        CHECK_EQ(fn.cache_size(), 6);
        CHECK(!fn.cached(6));

        CHECK_EQ(fn(10), 55);
        CHECK_EQ(fn.cache_size(), 11);
    }

    TEST_SUITE("memoization") {
        int free_function(int a, int b) { return a + b; }
        TEST_CASE("free-function") {
            auto fn = memoize(&free_function);
            checks_addition(fn);
        }

        TEST_CASE("lambda-move") {
            auto fn = memoize([](int a, int b) { return a + b; });
            checks_addition(fn);
        }

        TEST_CASE("lambda-ref") {
            auto add = [] (int a, int b) { return a + b; };
            auto fn = memoize(add);
            checks_addition(fn);
        }

        struct function_object {
            int operator() (int a, int b) const { return a + b; }
        };

        TEST_CASE("function object") {
            auto fn = memoize(function_object());
            checks_addition(fn);
        }

        struct poly_function_object {
            int operator() (int a, int b) const { return a + b; }
            double operator() (double a, double b) const { return a + b; }
        };

        TEST_CASE("function object") {
            auto fn = memoize<int(int, int)>(poly_function_object());
            checks_addition(fn);
        }

        auto fib = [] (auto &self, int n) -> int {
            if (n == 0) return 0;
            if (n == 1) return 1;
            return self(n - 1) + self(n - 2);
        };

        TEST_CASE("result-type-signature") {
            auto fn = recursive_memoize<int>(fib);
            checks_fib(fn);
        }

        TEST_CASE("explicit-signature") {
            auto fn = recursive_memoize<int(int)>(fib);
            checks_fib(fn);
        }

        TEST_CASE("count-calls") {
            unsigned calls = 0;
            auto fn = memoize([&calls](int a, int b) {
                return ++calls, a + b;
            });

            CHECK_EQ(fn(1, 2), 3);
            CHECK_EQ(fn(1, 2), 3);
            CHECK_EQ(fn(1, 2), 3);
            CHECK_EQ(calls, 1);
        }
    }

} // namespace gap::test
