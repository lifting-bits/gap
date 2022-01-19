// Copyright (c) 2022-present, Trail of Bits, Inc.

#pragma once

#include <gap/core/concepts.hpp>
#include <iterator>

namespace gap::ranges
{
    template< typename R >
    concept range = requires(R&& r) {
        std::begin(r);
        std::end(r);
    };

    template< range R >
    constexpr auto size(R&& r) {
        return std::size(r);
    }

    template< class R >
    concept sized_range = range< R > && requires(R&& r) {
        ranges::size(r);
    };

} // namespace gap::ranges