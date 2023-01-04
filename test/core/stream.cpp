// Copyright (c) 2022-present, Trail of Bits, Inc.
#include "gap/core/generator.hpp"

#include <iterator>
#include <optional>
#include <utility>
#ifdef GAP_ENABLE_COROUTINES

    #include <doctest/doctest.h>
    #include <gap/core/stream.hpp>
    #include <vector>

namespace gap::test
{
    TEST_CASE("map vector") {
        const std::vector< int > vec{ 1, 2, 3, 4, 5, 6 };
        auto gen = gap::stream::map(
            [](int x) { return std::make_pair(x, x * 2); }, gap::stream::stream(vec));
        for (auto [a, b] : gen) {
            CHECK_EQ(2 * a, b);
        }

        gen = gap::stream::map(
            [](int x) { return std::make_pair(x, x * 2); },
            gap::stream::stream(std::vector< int >{ 1, 2, 3, 4, 5, 6 }));
        for (auto [a, b] : gen) {
            CHECK_EQ(2 * a, b);
        }
    }

    TEST_CASE("filter vector") {
        const std::vector< int > vec{ 1, 2, 3, 4, 5, 6 };
        auto gen = gap::stream::filter([](int x) { return x % 2; }, gap::stream::stream(vec));
        for (auto x : gen) {
            CHECK(x % 2);
        }

        auto new_gen = gap::stream::filter(
            [](int x) { return x % 2; },
            gap::stream::stream(std::vector< int >{ 1, 2, 3, 4, 5, 6 }));
        for (auto x : new_gen) {
            CHECK(x % 2);
        }
    }

    TEST_CASE("flatmap generator") {
        const std::vector< int > vec{ 1, 2, 3 };
        auto gen = gap::stream::flat_map(
            [](int x) -> gap::generator< int > {
                for (int i = 0; i < x; ++i) {
                    co_yield x;
                }
            },
            gap::stream::stream(vec));
        int count = 0;
        for (auto elem : gen) {
            (void) elem;
            ++count;
        }
        CHECK_EQ(count, 6);
    }

} // namespace gap::test

#endif // GAP_ENABLE_COROUTINES
