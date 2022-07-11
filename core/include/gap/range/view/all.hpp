// Copyright (c) 2022-present, Trail of Bits, Inc.

#pragma once

namespace gap::range::view
{
    struct all_fn {
        /* TODO */
    };

    inline constexpr view_closure< all_fn > all;

    template< /* TODO view concept */ range_t >
    struct identity_adaptor : range_t {

    };
} // namespace gap::range::view
