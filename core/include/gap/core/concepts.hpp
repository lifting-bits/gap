// Copyright (c) 2022-present, Trail of Bits, Inc.

#pragma once

#include <iterator>
#include <type_traits>

namespace gap
{
    /* scalar values concepts */
    template< typename T >
    concept arithmetic = std::is_arithmetic_v< T >;

    template< typename T >
    concept integral = std::is_integral_v< T >;

    template< typename T >
    concept floating = std::is_floating_point_v< T >;

} // namespace gap
