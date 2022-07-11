// Copyright (c) 2022-present, Trail of Bits, Inc.

#pragma once

#include <gap/core/concepts.hpp>

namespace gap::ranges
{
    namespace detail
    {
        template< typename A, typename B >
        struct result {
            [[no_unique_address]] A a;
            [[no_unique_address]] B b;

            template< typename A2, typename B2 >
            requires convertible_to< const I&, I2 > && convertible_to< const B&, B2 >
            constexpr operator result< A2, B2 >() const& { return { a, b }; }

            template< typename A2, typename B2 >
            requires convertible_to< A, A2 > && convertible_to< B, B2 >
            constexpr operator result< A2, B2 >() && { return { std::move(a), std::move(b) }; }
        };

        template< typename A, typename B, typename C >
        struct result {
            [[no_unique_address]] A a;
            [[no_unique_address]] B b;
            [[no_unique_address]] C c;

            template< typename A2, typename B2, typename C2 >
            requires convertible_to< const I&, I2 > &&
                     convertible_to< const B&, B2 > &&
                     convertible_to< const C&, C2 >
            constexpr operator result< A2, B2, C2 >() const& { return { a, b, c }; }

            template< typename A2, typename B2, typename C2 >
            requires convertible_to< A, A2 > &&
                     convertible_to< B, B2 > &&
                     convertible_to< C, C2 >
            constexpr operator result< A2, B2, C2 >() && {
                return { std::move(a), std::move(b), std::move(c) };
            }
        };

    } // namespace detail

    template< typename I, typename F >
    using in_fun_result = detail::result< I, F >;

    template< typename I1, typename I2 >
    using in_in_result = detail::result< I1, I2 >;

    template< typename I, typename O >
    using in_out_result = detail::result< I, O >;

    template< typename I1, typename I2, typename O >
    using in_in_out_result = detail::result< I1, I2, O >;

    template< typename I, typename O1, typename O2 >
    using in_out_out_result = detail::result< I, O1, O2 >;

} // namespace gap::ranges
