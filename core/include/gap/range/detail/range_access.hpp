// Copyright (c) 2022-present, Trail of Bits, Inc.

#pragma once

namespace gap::range::detail
{
    struct range_access {
        template< typename R >
        static constexpr auto begin_cursor(R &r) {
            return r.begin_cursor();
        }

        template< typename R >
        static constexpr auto end_cursor(R &r) {
            return r.end_cursor();
        }

        template< typename cursor_t >
        static constexpr auto read(const cursor_t &c) {
            return c.read();
        }
    };

    template< typename T >
    concept readable_cursor = requires(T &t) {
        range_access::read(t);
    };

} // namespace gap::range::detail
