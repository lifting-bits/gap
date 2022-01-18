// Copyright (c) 2022-present, Trail of Bits, Inc.

#include <array>
#include <doctest/doctest.h>
#include <gap/core/concepts.hpp>
#include <vector>

namespace gap::test
{
    struct dummy {};
    enum dummy_enum : int
    {
    };

    static_assert(integral< int >);
    static_assert(integral< dummy > == false);
    static_assert(integral< dummy_enum > == false);
    static_assert(integral< float > == false);
    static_assert(integral< const int >);
    static_assert(integral< bool >);

    static_assert(arithmetic< int >);
    static_assert(arithmetic< dummy > == false);
    static_assert(arithmetic< dummy_enum > == false);
    static_assert(arithmetic< float >);
    static_assert(arithmetic< const double >);
    static_assert(arithmetic< const int >);
    static_assert(arithmetic< bool >);

    static_assert(floating< int > == false);
    static_assert(floating< dummy > == false);
    static_assert(floating< dummy_enum > == false);
    static_assert(floating< float >);
    static_assert(floating< const double >);
    static_assert(floating< const int > == false);
    static_assert(floating< bool > == false);

} // namespace gap::test
