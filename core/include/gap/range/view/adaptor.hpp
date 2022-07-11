// Copyright (c) 2022-present, Trail of Bits, Inc.

#pragma once

#include <gap/range/view/facade.hpp>

namespace gap::range::view
{
    template< typename derived_t, typename base_range_t, cardinality_t cardinality >
    struct view_adaptor : view_facade< derived_t, cardinality > {
        view_adaptor() = default;
        view_adaptor(view_adaptor &&) = default;
        view_adaptor(view_adaptor const &) = default;
        view_adaptor & operator=(view_adaptor &&) = default;
        view_adaptor & operator=(view_adaptor const &) = default;

        constexpr explicit view_adaptor(base_range_t &&rng)
            : _rng(all(std::forward< base_range_t >(rng))) {}


        private:
            base_range_t _rng;
    };

} // namespace gap::range::view
