// Copyright (c) 2022-present, Trail of Bits, Inc.

#pragma once

#include <type_traits>

namespace gap::trait
{

    template< typename T >
    struct type_wrapper {
        template< typename U >
        friend constexpr bool operator==(type_wrapper, type_wrapper< U >) {
            return std::is_same_v< T, U >;
        }
    };

    template< typename T >
    inline constexpr auto type = type_wrapper< T >{};
    template< typename T >
    constexpr auto typeof(T &&) {
        return type< T >;
    }

    namespace
    {
        static_assert(type< int > == type< int >);
        static_assert(type< unsigned > != type< double >);

        template< typename T, typename U >
        constexpr bool check(T &&a, U &&b) {
            if constexpr (type< T > == type< U >) {
                static_assert(typeof(a) == typeof(b));
            } else {
                static_assert(typeof(a) != typeof(b));
            }
        }

        static_assert(check(1, 2));
        static_assert(check(1, 2.1));
        static_assert(check("hello", "world"));

    } // anonymous namespace

} // namespace gap::trait
