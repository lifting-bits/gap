// Copyright (c) 2022-present, Trail of Bits, Inc.

#include <doctest/doctest.h>
#include <gap/core/concepts.hpp>
#include <gap/core/hash.hpp>

#include <unordered_set>

namespace gap::test
{
    static_assert(hashable< int >);
    static_assert(hashable< const int & >);
    static_assert(hashable< int && >);

    TEST_CASE("std hash") {
        CHECK_EQ(gap::hash<int>{}(0), gap::hash<int>{}(0));
        CHECK_EQ(gap::hash<float>{}(+0.0f), gap::hash<float>{}(-0.0f));
    }

    TEST_CASE("std const hash") {
        const int v = 0;
        CHECK_EQ(gap::hash<int>{}(v), gap::hash<int>{}(0));
    }

    static_assert(gap::supports_hash_value< std::tuple< int > >);

    TEST_CASE("tuple hash") {
        using point = std::tuple< int, int, int >;
        CHECK_EQ(gap::hash<point>{}(point{0, 0, 0}), gap::hash<point>{}(point{0, 0, 0}));
    }

    TEST_CASE("tuple hash key") {
        using point = std::tuple< int, int, int >;
        (void)gap::hash< point >{};
        std::unordered_set< point, gap::hash< point > > set;

        set.insert(point{0, 0, 0});
        set.insert(point{0, 0, 1});
        set.insert(point{0, 0, 0});
        CHECK_EQ(set.size(), 2);
    }

} // namespace gap::test
