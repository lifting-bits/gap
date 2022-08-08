// Copyright 2022-present, Trail of Bits, Inc.

#pragma once

#include <type_traits>

#include <gap/core/concepts.hpp>
#include <gap/core/ranges.hpp>

#include <array>
#include <tuple>
#include <utility>

namespace gap
{
    template< typename T >
    struct hash;

    //
    // hash_code serves to keep hash function state and pass it along
    //
    struct hash_code {
        constexpr explicit hash_code(std::size_t s) : state(s) {}
        constexpr operator std::size_t() const { return state; }

        std::size_t state;
    };

    template< typename T >
    concept hash_code_like = convertible_to< T, hash_code >;

    namespace detail
    {
        // generic hash_combine inspired by boost.hash implementation
        constexpr hash_code hash_combine(std::size_t lhs, std::size_t rhs) {
            return hash_code(lhs ^ (rhs * 0x9e3779b9 + (lhs << 6) + (lhs >> 2)));
        }
    } // namespace detail

    constexpr hash_code operator%(const hash_code &lhs, const hash_code &rhs) {
        return hash_code{ detail::hash_combine(lhs.state, rhs.state) };
    }

    namespace detail
    {
        template< hash_code_like... args_t >
        constexpr hash_code hash_combine_impl(const args_t&... args) {
            return hash_code((args % ...));
        }

    } // namespace detail

    //
    // hash_value
    //
    template< typename T >
    constexpr hash_code hash_value(hash_code code, const T& val);


    //
    // hashing convenience helper functions
    //
    template< hash_code_like... args_t >
    constexpr hash_code hash_combine(const args_t&... args) {
        return detail::hash_combine_impl(args...);
    }

    template< ranges::range range_t >
    constexpr hash_code hash_combine_range(hash_code code, const range_t &range) {
        for (const auto &v : range)
            code = hash_combine(code, hash_value(code, v));
        return code;
    }

    template< ranges::range range_t >
    constexpr hash_code hash_sized_container(hash_code code, const range_t &range) {
        return hash_combine(
            hash_combine_range(code, range),
            hash_code(range.size())
        );
    }

    template< typename T, size_t N >
    constexpr hash_code hash_value(hash_code code, const std::array< T, N >& arr) {
        return hash_sized_container(code, arr);
    }

    template< hashable T >
    constexpr hash_code hash_value(hash_code h, const T& v) {
        return hash_combine(h, hash_code( std::hash< T >{}(v) ));
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
        template< typename Tuple, size_t... Is >
        constexpr hash_code hash_tuple(hash_code code, Tuple&& t, std::index_sequence< Is... >) {
            return hash_combine(
                hash_value(code, std::get< Is >(std::forward< Tuple >(t)))...
            );
        }
    } // namespace detail

    template< typename... Ts >
    constexpr hash_code hash_value(hash_code code, const std::tuple< Ts... >& t) {
        return detail::hash_tuple(
            code, std::tuple< Ts... >(t),
            std::make_index_sequence< sizeof...(Ts) >()
        );
    }

    template< typename T, typename U >
    constexpr hash_code hash_value(hash_code code, const std::pair< T, U >& p) {
        return hash_combine(code, hash_value(code, p.first), hash_value(code, p.second));
    }

    //
    // generic hash interface
    //
    template< typename T >
    struct hash {
        template< supports_hash_value U = T >
        requires (not hashable< U >)
        constexpr std::size_t operator()(const U& u) const {
            hash_code state{ 0 };
            return static_cast< std::size_t >(
                hash_value(hash_code(state), u)
            );
        }

        template< hashable U = T >
        constexpr std::size_t operator()(const U& u) const {
            return std::hash< std::decay_t< U > >{}(u);
        }
    };

} // namespace gap
