// Copyright (c) 2022-present, Trail of Bits, Inc.

#pragma once

namespace gap::range::view
{
    struct view_base {};

    enum cardinality : std::ptrdiff_t
    {
        infinite = -3,
        unknown = -2,
        finite = -1
    };

    template< cardinality >
    struct basic_view : view_base {};

} // namespace gap::range::view
