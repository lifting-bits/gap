#pragma once

#include <gap/mlir/common.hpp>

// Workaround to allow ABI breaking changes in join_view
#ifdef _LIBCPP_ENABLE_EXPERIMENTAL
    #define _LIBCPP_ENABLE_EXPERIMENTAL_WAS_DEFINED
#endif

#if _LIBCPP_VERSION
    #define _LIBCPP_ENABLE_EXPERIMENTAL
#endif

#include <ranges>

#ifndef _LIBCPP_ENABLE_EXPERIMENTAL_WAS_DEFINED
    #if _LIBCPP_VERSION
        #undef _LIBCPP_ENABLE_EXPERIMENTAL
    #endif
#endif

#include <gap/mlir/functors.hpp>

namespace gap::mlir::views
{
    static inline auto regions(operation op) -> decltype(auto) {
        auto regs = op->getRegions();
        return std::ranges::subrange{regs.begin(), regs.end()};
    }

    static inline auto blocks(operation op) -> decltype(auto) {
        return regions(op) | std::views::join;
    }

    static inline auto operations(operation op) -> decltype(auto) {
        return blocks(op) | std::views::join;
    }

    template< typename T >
    auto isa = std::views::filter(::gap::mlir::isa< T >);

    template< typename T >
    auto cast = std::views::transform(::gap::mlir::cast< T >);

    template< typename T >
    auto dyn_cast = std::views::transform(::gap::mlir::dyn_cast< T >);

    template< typename T >
    auto filter_cast = isa< T > | cast< T >;

} // namespace gap::mlir::views