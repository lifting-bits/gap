// Copyright (c) 2022-present, Trail of Bits, Inc.

#pragma once

#include <concepts>
#include <iterator>
#include <ostream>
#include <type_traits>

namespace gap
{
    namespace detail
    {
        template< typename T >
        using with_ref = T&;
    } // namespace detail

    /* scalar values concepts */
    template< typename T >
    concept arithmetic = std::is_arithmetic_v< T >;

    template< typename T >
    concept integral = std::is_integral_v< T >;

    template< typename T >
    concept floating = std::is_floating_point_v< T >;

    /* value concepts */
    template< typename T >
    concept class_or_enum = std::is_class_v< T > || std::is_union_v< T > || std::is_enum_v< T >;

    template< typename R >
    inline constexpr bool is_array_like = std::is_array_v< std::remove_reference_t< R > >;

    template< typename R >
    inline constexpr bool is_class_like = class_or_enum< std::remove_reference_t< R > >;

    template< typename R >
    inline constexpr bool is_bounded_array_like
        = std::is_bounded_array_v< std::remove_reference_t< R > >;

    template< typename T >
    concept can_reference = requires {
        typename detail::with_ref< T >;
    };

    /* common concepts */
    template< typename T >
    concept printable = requires(std::ostream& os, T t) {
        { os << t } -> std::same_as< std::ostream& >;
    };

} // namespace gap
