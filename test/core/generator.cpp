// Copyright (c) 2021-present, Trail of Bits, Inc.

#include <doctest/doctest.h>
#include <gap/core/generator.hpp>

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

} // namespace gap::test
