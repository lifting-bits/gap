// Copyright (c) 2021-present, Trail of Bits, Inc.

///////////////////////////////////////////////////////////////////////////////
// Copyright (c) Lewis Baker
// Licenced under MIT license. See LICENSE.txt for details.
///////////////////////////////////////////////////////////////////////////////
// This file is a modified version of cppcoro/test/generator.cpp from the
// cppcoro project. The original file is licenced under the MIT license and the
// original license is included above.
///////////////////////////////////////////////////////////////////////////////

#ifdef GAP_ENABLE_COROUTINES

    #include <doctest/doctest.h>
    #include <gap/coro/generator.hpp>

    #include <vector>
    #include <gap/core/ranges.hpp>

namespace gap::test
{
    generator< int > iota() {
        int value = 0;
        while (true) {
            co_yield value;
            ++value;
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

    generator< int > empty_generator() {
        return {};
    }

    TEST_CASE("empty generator") {
        auto v = empty_generator();
    }

} // namespace gap::test

#endif // GAP_ENABLE_COROUTINES
