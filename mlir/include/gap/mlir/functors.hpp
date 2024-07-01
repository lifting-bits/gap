// Copyright 2024, Trail of Bits, Inc.

#pragma once

namespace gap::mlir
{
    template< typename T >
    constexpr auto isa = []< typename U >(U &&u) {
        return ::mlir::isa< T >(std::forward< U >(u));
    };

    template< typename T >
    constexpr auto dyn_cast = []< typename U >(U &&u) {
        return ::mlir::dyn_cast< T >(std::forward< U >(u));
    };

    template< typename T >
    constexpr auto cast = []< typename U >(U &&u) {
        return ::mlir::cast< T >(std::forward< U >(u));
    };

} // namespace gap::mlir