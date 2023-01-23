// Copyright (c) 2022-present, Trail of Bits, Inc.

#pragma once

#include <gap/core/concepts.hpp>
#include <iterator>
#include <numeric>

namespace gap::ranges
{
    template< typename R >
    concept range = requires(R&& r) {
        typename std::decay_t< R >::value_type;
        std::begin(r);
        std::end(r);
    };

    template< range R >
    constexpr auto size(R&& r) {
        return std::size(r);
    }

    template< typename R >
    concept sized_range = range< R > && requires(R&& r) { ranges::size(r); };

    template< typename R >
    concept arithmetic_range = range< R > && arithmetic< typename R::value_type >;

    template< typename R, typename V >
    concept value_range = range< R > && convertible_to< typename R::value_type, V >;

    constexpr auto accumulate(range auto r, auto init) {
        return std::accumulate(r.begin(), r.end(), init);
    }

    constexpr auto accumulate(range auto r, auto init, auto bop) {
        return std::accumulate(r.begin(), r.end(), init, bop);
    }

    template< range R >
    using iterator_t = decltype(std::begin(std::declval< R& >()));

    template< range R >
    using range_value_t = std::iter_value_t< iterator_t< R > >;

} // namespace gap::ranges
