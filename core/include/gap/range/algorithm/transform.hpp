// Copyright (c) 2022-present, Trail of Bits, Inc.

#pragma once

#include <gap/ranges/algorithm/result_types.hpp>

namespace gap::ranges
{
    template< typename I, typename O >
    using unary_transform_result = in_out_result< I, O >;

    template< typename I1, typename I2, typename O >
    using binary_transform_result = in_in_out_result< I1, I2, O >;

    namespace detail
    {
        struct transform_fn {
            private:

            template <typename I, typename S, typename O, typename F, typename Proj>
            static constexpr unary_transform_result<I, O>
            unary_impl(I first, S last, O result, F& op, Proj& proj)
            {
                while (first != last) {
                    *result = nano::invoke(op, nano::invoke(proj, *first));
                    ++first;
                    ++result;
                }

                return {std::move(first), std::move(result)};
            }
        };
    } // namespace detail

} // namespace gap::ranges
