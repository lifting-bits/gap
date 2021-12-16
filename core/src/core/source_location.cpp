// Copyright (c) 2021-present, Trail of Bits, Inc.

#include "core/source_location.hpp"

namespace gap
{
    constexpr source_location source_location::current(
        file_name file, func_name function, unsigned line, unsigned column) noexcept {
        return source_location(file, function, line, column);
    }
} // namespace gap
