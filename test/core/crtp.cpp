// Copyright (c) 2022-present, Trail of Bits, Inc.

#include <array>
#include <doctest/doctest.h>
#include <gap/core/crtp.hpp>

namespace gap::test
{
    template< typename derived >
    struct base : gap::core::crtp< derived, base > {
        using gap::core::crtp< derived, base >::underlying;

        int foo() { return underlying().bar(); }
    };

    struct derived : base< derived > {
        int bar() { return 10; }
    };

    TEST_CASE("CRTP test") {
        derived d;
        CHECK(d.foo() == 10);
    }

} // namespace gap::test
