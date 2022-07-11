// Copyright (c) 2022-present, Trail of Bits, Inc.

#pragma once

#include <gap/core/concepts.hpp>
#include <iterator>
#include <numeric>

namespace gap::ranges
{
    template< typename R >
    concept range = requires(R&& r) {
        typename R::value_type;
        std::begin(r);
        std::end(r);
    };

    namespace detail {
        template< range R >
        constexpr auto size(R&& r) {
            return std::size(std::forward< R >(r));
        }
    } // namespace detail

    template< typename R >
    concept sized_range = range< R > && requires(R&& r) {
        detail::size(r);
    };

    template< typename R >
    concept arithmetic_range = range< R > && arithmetic< typename R::value_type >;

} // namespace gap::ranges
