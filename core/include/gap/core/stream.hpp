// Copyright (c) 2022-present, Trail of Bits, Inc.

#pragma once

#ifdef GAP_ENABLE_COROUTINES

    #include "gap/core/concepts.hpp"
    #include "gap/core/generator.hpp"

    #include <optional>

namespace gap
{
    namespace stream
    {
        template< typename T >
        requires iterable< T >
        auto stream(T&& cont) -> gap::generator< decltype(*cont.begin()) > {
            for (auto&& elem : cont) {
                co_yield std::forward< decltype(elem) >(elem);
            }
        }

        template< typename T >
        requires std::convertible_to< T, bool > && dereferenceable< T >
        auto stream(T&& cont) -> gap::generator< decltype(*cont) > {
            if (cont) {
                co_yield std::forward< decltype(*cont) >(*cont);
            }
        }

        template< typename TFunc, typename TInput >
        auto map(TFunc&& f, gap::generator< TInput > source)
            -> gap::generator< decltype(f(*source.begin())) > {
            for (auto&& elem : source) {
                co_yield f(std::forward< decltype(elem) >(elem));
            }
        }

        template< typename TPred, typename TElem >
        gap::generator< TElem > filter(TPred&& pred, gap::generator< TElem > source) {
            for (auto&& elem : source) {
                if (pred(std::forward< decltype(elem) >(elem))) {
                    co_yield std::forward< decltype(elem) >(elem);
                }
            }
        }

        template< typename TFunc, typename TElem >
        auto flat_map(TFunc&& f, gap::generator< TElem > source)
            -> gap::generator< decltype(*(f(*source.begin()).begin())) > {
            for (auto&& elem : source) {
                for (auto&& sub_elem : f(source)) {
                    co_yield std::forward< decltype(sub_elem) >(sub_elem);
                }
            }
        }
    } // namespace stream
} // namespace gap

#endif
