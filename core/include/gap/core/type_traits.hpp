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
    constexpr auto type_of(T &&) {
        return type< T >;
    }

    namespace detail
    {
        template< typename T, typename enable_t = void >
        struct function_signature;

        template< typename T >
        struct function_signature< T, std::enable_if_t< std::is_class_v< std::remove_cvref_t< T > > > >
            : function_signature< decltype(&std::remove_cvref_t< T >::operator()) >
        {};

        template< typename T, typename result_t, typename... args_t >
        struct function_signature< result_t (T::*)(args_t...) > {
            using type = result_t(args_t...);
        };

        template< typename T, typename result_t, typename... args_t >
        struct function_signature< result_t (T::*)(args_t...) const > {
            using type = result_t(args_t...);
        };

        template< typename result_t, typename... args_t >
        struct function_signature< result_t(args_t...) > {
            using type = result_t(args_t...);
        };

        template< typename result_t, typename... args_t >
        struct function_signature< result_t (&)(args_t...) > {
            using type = result_t(args_t...);
        };

        template< typename result_t, typename... args_t >
         struct function_signature< result_t (*)(args_t...) > {
            using type = result_t(args_t...);
        };
    } // namespace detail

    template< typename T >
    using function_signature_t = typename detail::function_signature< T >::type;

    namespace detail
    {
        template< typename T >
        struct drop_first_arg;

        template< typename result_t, typename first_t, typename... args_t >
        struct drop_first_arg< result_t(first_t, args_t...) > {
            using type = result_t(args_t...);
        };

        struct dummy {};

        template< typename T, typename result_t = dummy, typename enable_t = void >
        struct recursive_function_signature;

        template< typename T, typename result_t >
        struct recursive_function_signature<
            T,
            result_t,
            std::enable_if_t< std::is_class_v< std::remove_cvref_t< T > > > >
        {
            using type = typename drop_first_arg< function_signature_t<
                decltype(&std::remove_cvref_t< T >::template operator()< result_t (*)(...) >) > >::type;
        };
    } // namespace detail

    template< typename... T >
    using recursive_function_signature_t = typename detail::recursive_function_signature< T... >::type;

    namespace
    {
        static_assert(type< int > == type< int >);
        static_assert(type< unsigned > != type< double >);

        template< typename T, typename U >
        constexpr bool check(T &&a, U &&b) {
            if constexpr (type< T > == type< U >) {
                return type_of(a) == type_of(b);
            } else {
                return type_of(a) != type_of(b);
            }
        }

        static_assert(check(1, 2));
        static_assert(check(1, 2.1));
        static_assert(check("hello", "world"));

    } // anonymous namespace

} // namespace gap::trait
