// Copyright (c) 2021-present, Trail of Bits, Inc.

#ifdef GAP_ENABLE_COROUTINES

    #include <doctest/doctest.h>
    #include <gap/core/generator.hpp>

    #include <vector>
    #include <gap/core/ranges.hpp>

namespace gap::test
{
    generator< int > iota() {
        int value = 0;
        while (true) {
            co_yield value++;
        }
    }

    TEST_CASE("tagged int") {
        int i = 0;
        for (int v : iota()) {
            CHECK_EQ(i++, v);
            if (i == 5)
                break;
        }
    }

    template< gap::ranges::range R >
    auto from_range(R &&rng) -> range_generator< R > {
        for (auto v : rng) {
            co_yield v;
        }
    }

    TEST_CASE("range generator") {
        std::vector< int > t{1, 2, 3};
        auto g = from_range(t);
        auto b = from_range(g);
    }

} // namespace gap::test

#endif // GAP_ENABLE_COROUTINES
