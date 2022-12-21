// Copyright (c) 2022-present, Trail of Bits, Inc.

#pragma once

#ifdef GAP_ENABLE_COROUTINES

    #include "gap/core/generator.hpp"

    #include <optional>

namespace gap
{
    namespace functional
    {
        auto stream(auto&& cont) -> gap::generator< decltype(*cont.begin()) > {
            for (auto&& elem : cont) {
                co_yield std::forward< decltype(elem) >(elem);
            }
        }

        template< typename T >
        gap::generator< T > stream(gap::generator< T > gen) {
            return gen;
        }

        template< typename T >
        auto stream(const std::optional< T >& cont) -> gap::generator< T > {
            if (cont.has_value()) {
                auto value = cont.value();
                co_yield value;
            }
        }

        template< typename TFunc, typename TSource >
        auto map(TFunc&& f, TSource&& source)
            -> gap::generator< decltype(f(*stream(source).begin())) > {
            for (auto&& elem : stream(std::forward< decltype(source) >(source))) {
                co_yield f(std::forward< decltype(elem) >(elem));
            }
        }

        template< typename TPred, typename TSource >
        auto filter(TPred&& pred, TSource&& source) -> decltype(stream(source)) {
            for (auto&& elem : stream(std::forward< decltype(source) >(source))) {
                if (pred(std::forward< decltype(elem) >(elem))) {
                    co_yield std::forward< decltype(elem) >(elem);
                }
            }
        }

        template< typename TFunc, typename TSource >
        auto flat_map(TFunc&& f, TSource&& source) -> decltype(stream(f(*stream(source).begin()))) {
            for (auto&& elem : stream(std::forward< decltype(source) >(source))) {
                for (auto&& sub_elem : stream(f(std::forward< decltype(elem) >(elem)))) {
                    co_yield std::forward< decltype(sub_elem) >(sub_elem);
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
