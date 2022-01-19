// Copyright (c) 2022-present, Trail of Bits, Inc.

#include <array>
#include <doctest/doctest.h>
#include <gap/core/benchmark.hpp>
#include <vector>

namespace gap::test
{
    namespace bench = gap::bench;

    static_assert(bench::sum(std::array{ 1, 2, 3 }) == 6);

    static_assert(bench::mean(std::array{ 1, 2, 3 }) == 2);
    static_assert(bench::mean(std::array{ 2, 4, 4, 4, 5, 5, 7, 9 }) == 5);
    static_assert(bench::standard_deviation(std::array{ 2, 4, 4, 4, 5, 5, 7, 9 }) == 4);

} // namespace gap::test
