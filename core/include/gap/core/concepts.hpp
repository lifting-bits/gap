// Copyright (c) 2022-present, Trail of Bits, Inc.

#pragma once

#include <concepts>
#include <functional>
#include <iterator>
#include <ostream>
#include <type_traits>
#include <utility> // for forward

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

    template< typename F, typename... Args >
    concept invocable = requires(F&& f, Args&&... args) {
        std::invoke(std::forward< F >(f), std::forward< Args >(args)...);
    };

    /* operator concepts */
    template< typename T >
    concept incrementable = requires(T value) {
        ++value;
        value++;
    };

    template< typename T >
    concept decrementable = requires(T value) {
        --value;
        value--;
    };

    template< typename A, typename B >
    concept comparable = requires(const A& a, const B& b) {
        a == b;
    };

    template< typename From, typename To >
    concept convertible_to = std::is_convertible_v< From, To > && requires {
        static_cast< To >(std::declval< From >());
    };

    template< typename Derived, typename Base >
    concept derived_from =
        std::is_base_of_v< Base, Derived > &&
        std::is_convertible_v< const volatile Derived*, const volatile Base* >;

} // namespace gap
