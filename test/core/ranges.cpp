// Copyright (c) 2022-present, Trail of Bits, Inc.

#include <array>
#include <doctest/doctest.h>
#include <gap/core/ranges.hpp>
#include <vector>

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

} // namespace gap::test
