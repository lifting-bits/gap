// Copyright (c) 2022-present, Trail of Bits, Inc.

#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#include <gap/core/concepts.hpp>

namespace gap {

    template< std::size_t N, unsigned_integral T = std::uint64_t >
    struct big_int : std::array< T, N > {};

} // namespace gap
