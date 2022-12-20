// Copyright (c) 2022-present, Trail of Bits, Inc.

#pragma once

#ifdef GAP_ENABLE_COROUTINES

    #include "gap/core/generator.hpp"

    #include <optional>

namespace gap
{
    namespace functional
    {
        template< typename TContainer >
        auto enumerate(const TContainer& cont) -> gap::generator< decltype(*cont.begin()) > {
            for (auto& elem : cont) {
                co_yield elem;
            }
        }

        template< typename T >
        gap::generator< T > enumerate(gap::generator< T > gen) {
            return gen;
        }

        template< typename T >
        auto enumerate(const std::optional< T >& cont) -> gap::generator< T > {
            if (cont.has_value()) {
                auto value = cont.value();
                co_yield value;
            }
        }

        template< typename TFunc, typename TSource >
        auto map(TFunc f, const TSource& source)
            -> gap::generator< decltype(f(*enumerate(source).begin())) > {
            for (auto& elem : enumerate(source)) {
                co_yield f(elem);
            }
        }

        template< typename TPred, typename TSource >
        auto filter(TPred pred, const TSource& source) -> decltype(enumerate(source)) {
            for (auto& elem : enumerate(source)) {
                if (pred(elem)) {
                    co_yield elem;
                }
            }
        }

        template< typename TFunc, typename TSource >
        auto flat_map(TFunc f, const TSource& source)
            -> decltype(enumerate(f(*enumerate(source).begin()))) {
            for (auto& elem : enumerate(source)) {
                for (auto& sub_elem : enumerate(f(elem))) {
                    co_yield sub_elem;
                }
            }
        }

        template< typename T, typename Inserter >
        Inserter insert_into(Inserter ins, gap::generator< T >& gen) {
            for (auto& value : gen) {
                *ins = value;
                ++ins;
            }
            return ins;
        }

        template< typename T, typename ItBegin, typename ItEnd >
        ItBegin insert_into(ItBegin begin, ItEnd end, gap::generator< T >& gen) {
            for (auto& value : gen) {
                if (begin == end) {
                    break;
                }

                *begin = value;
                ++begin;
            }
            return begin;
        }

    } // namespace functional
} // namespace gap

#endif
