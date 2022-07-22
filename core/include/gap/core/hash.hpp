// Copyright 2022-present, Trail of Bits, Inc.

#pragma once

#include <type_traits>

#include <gap/core/concepts.hpp>

namespace gap
{
    template< typename T >
    struct hash;

    //
    // hash_code serves to keep hash function state and pass it along
    //
    template< typename hash_code >
    concept hash_code_like =
        std::constructible_from< std::decay_t< hash_code >, std::size_t > &&
        std::convertible_to< std::decay_t< hash_code >, std::size_t >;

    struct hash_code {

        explicit constexpr hash_code(std::size_t state) : state(state) {}

        constexpr operator std::size_t() const { return state; }

        std::size_t state;
    };

    static_assert( hash_code_like< hash_code > );

    namespace detail
    {
        // generic hash_combine inspired by boost.hash implementation
        constexpr inline std::size_t hash_combine(std::size_t lhs, std::size_t rhs) {
            return hash_code(lhs ^ (rhs * 0x9e3779b9 + (lhs << 6) + (lhs >> 2)));
        }
    } // namespace detail

    inline hash_code operator%(hash_code &&lhs, hash_code &&rhs) {
        return hash_code{ detail::hash_combine(lhs.state, rhs.state) };
    }


    namespace detail
    {
        template< hash_code_like... args_t >
        constexpr hash_code hash_combine_impl(args_t&&... args) {
            return hash_code((std::forward< args_t >(args) % ...));
        }
    } // namespace detail

    template< hash_code_like... args_t >
    constexpr hash_code hash_combine(args_t&&... args) {
        return detail::hash_combine_impl(args...);
    }

    //
    // hash_value
    //
    template< hash_code_like H, typename T >
    constexpr inline H hash_value(H h, const T& val);

    template< hash_code_like H, hashable T >
    constexpr H hash_value(H /* h */, const T& v) {
        return H( std::hash< T >{}(v) );
    }

    template< typename T >
    concept supports_hash_value = requires(T v) {
        hash_value(std::declval< hash_code >(), v);
    };

    //
    // tuple hash_value
    //
    namespace detail
    {
        template< hash_code_like H, typename Tuple, size_t... Is >
        constexpr H hash_tuple(H code, Tuple&& t, std::index_sequence< Is... >) {
            return hash_combine(
                hash_value(code, std::get< Is >(std::forward< Tuple >(t)))...
            );
        }
    } // namespace detail

    template< hash_code_like H, typename... Ts >
    constexpr inline H hash_value(H code, const std::tuple< Ts... >& t) {
        return detail::hash_tuple(
            std::move(code), std::tuple< Ts... >(t),
            std::make_index_sequence< sizeof...(Ts) >()
        );
    }

    //
    // generic hash interface
    //
    template< typename T >
    struct hash {
        template< supports_hash_value U = T >
        requires (not hashable< U >)
        std::size_t operator()(const U& u) const {
            std::size_t state = 0;
            return static_cast< std::size_t >(
                hash_value(hash_code(state), u)
            );
        }

        template< hashable U = T >
        std::size_t operator()(const U& u) const {
            return std::hash< std::decay_t< U > >{}(u);
        }
    };

} // namespace gap
