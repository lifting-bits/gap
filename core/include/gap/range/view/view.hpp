// Copyright (c) 2022-present, Trail of Bits, Inc.

#pragma once

#include <gap/core/concepts.hpp>
#include <gap/range/view/base.hpp>

namespace gap::range::view
{
    struct view_closure_base {};

    template< typename fn_t >
    struct view_closure : view_closure_base, fn_t {};

} // namespace gap::range::view
