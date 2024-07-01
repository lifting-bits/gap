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

namespace gap::mlir
{
    auto regions(operation op) -> decltype(std::views::all(op->getRegions()));
    auto blocks(operation op) -> decltype(std::views::join(regions(op)));
    auto operations(operation op) -> decltype(std::views::join(blocks(op)));

} // namespace gap::mlir