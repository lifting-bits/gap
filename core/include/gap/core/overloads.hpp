/*
 * Copyright (c) 2022 Trail of Bits, Inc.
 */

#pragma once

namespace gap
{

    // helper for variant visitor
    template< class... Ts >
    struct overloaded : Ts... {
        using Ts::operator()...;
    };
    template< class... Ts >
    overloaded(Ts...) -> overloaded< Ts... >;

} // namespace gap
