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
        auto lhs = gap::hash<point>{}(point{1, 2, 3});
        auto rhs = gap::hash<point>{}(point{1, 2, 3});
        CHECK_EQ(lhs, rhs);

        auto other = gap::hash<point>{}(point{3, 2, 1});
        CHECK_NE(lhs, other);
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

    static_assert(gap::supports_hash_value< std::tuple< int, std::tuple< int, int > > >);

    TEST_CASE("nested tuple hash") {
        using nested = std::tuple< int, std::tuple< int, int > >;
        std::unordered_set< nested, gap::hash< nested > > set;

        set.insert(nested{1,{0, 0}});
        set.insert(nested{1,{1, 0}});
        set.insert(nested{1,{0, 1}});
        CHECK_EQ(set.size(), 3);
    }

    TEST_CASE("pair hash") {
        using pair = std::pair< int, char >;

        auto lhs = gap::hash<pair>{}(pair{1, 'a'});
        auto rhs = gap::hash<pair>{}(pair{1, 'a'});
        CHECK_EQ(lhs, rhs);

        auto other = gap::hash<pair>{}(pair{1, 'b'});
        CHECK_NE(lhs, other);
    }

    TEST_CASE("hash array") {
        auto lhs = std::array{1, 2, 3};
        auto rhs = std::array{1, 2, 3};

        CHECK_EQ(
            gap::hash< decltype(lhs) >{}(lhs),
            gap::hash< decltype(rhs) >{}(rhs)
        );

        auto other = std::array{3, 2, 1};
        CHECK_NE(
            gap::hash< decltype(lhs) >{}(lhs),
            gap::hash< decltype(other) >{}(other)
        );

        auto one = std::array{1};
        auto ones = std::array{1, 1};

        CHECK_NE(
            gap::hash< decltype(one) >{}(one),
            gap::hash< decltype(ones) >{}(ones)
        );
    }

} // namespace gap::test
