// Copyright (c) 2022-present, Trail of Bits, Inc.

#pragma once

#include <gap/core/ranges.hpp>
#include <numeric>

namespace gap::bench
{
    template< typename R >
    concept sample = gap::ranges::arithmetic_range< R >;

    template< sample S >
    using sample_type = typename S::value_type;

    constexpr double sum(sample auto s) { return gap::ranges::accumulate(s, 0); }

    constexpr double mean(sample auto s) { return sum(s) / ssize(s); }

    constexpr double standard_deviation(sample auto s) {
        double avg     = mean(s);
        auto deviation = [avg](double acc, auto val) { return acc + (avg - val) * (avg - val); };
        return gap::ranges::accumulate(s, 0l, deviation) / ssize(s);
    }

} // namespace gap::bench
