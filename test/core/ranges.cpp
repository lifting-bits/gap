// Copyright (c) 2022-present, Trail of Bits, Inc.

#include <doctest/doctest.h>

#include <gap/core/ranges.hpp>

#include <array>
#include <vector>
#include <list>
#include <ranges>

namespace gap::test
{
    namespace gr = gap::ranges;

    struct dummy {};

    static_assert(gr::range< std::vector< int > >);
    static_assert(gr::range< std::vector< dummy > >);
    static_assert(gr::range< std::array< int, 10 > >);
    static_assert(gr::range< int > == false);

    static_assert(gr::arithmetic_range< std::vector< int > >);
    static_assert(gr::arithmetic_range< std::vector< float > >);
    static_assert(gr::arithmetic_range< std::vector< dummy > > == false);


    static_assert(std::is_same_v< gr::range_value_t< std::vector< int > >, int >);
    static_assert(std::is_same_v< gr::range_value_t< std::vector< int* > >, int* >);
    static_assert(std::is_same_v<
        gr::range_value_t< std::vector< int > >, std::vector< int >::value_type
    >);

    static_assert(std::is_same_v<
        gr::range_value_t< std::vector< dummy > >, std::vector< dummy >::value_type
    >);

    TEST_SUITE("ranges") {
        TEST_CASE("to vector") {
            std::vector< int > v = {1, 2, 3, 4, 5};
            auto v2 = v | gr::to< std::vector >;
            CHECK(v == v2);
        }

        TEST_CASE("to list") {
            std::vector< int > v = {1, 2, 3, 4, 5};
            auto l = v | gr::to< std::list >;

            CHECK(std::equal(v.begin(), v.end(), l.begin(), l.end()));
        }

        TEST_CASE("to with filter") {
            std::vector< int > v = {1, 2, 3, 4, 5};
            auto v2 = v | std::views::filter([] (int x) { return x % 2 == 0; })
                        | gr::to< std::vector >;
            CHECK(v2 == std::vector{2, 4});
        }
    }

} // namespace gap::test
