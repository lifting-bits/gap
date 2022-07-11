// Copyright (c) 2022-present, Trail of Bits, Inc.

#pragma once


#include <gap/range/detail/range_access.hpp>

namespace gap::range
{
    namespace detail {

        template<typename cursor_t, bool is_readable /* = (bool) readable_cursor< cursor_t > */>
        struct iterator_associated_types_base_impl : /* TODO */ {
            /* TODO */
        };

        template< typename cursor_t >
        using iterator_associated_types_base
            = iterator_associated_types_base_impl< cursor_t, (bool) readable_cursor< cursor_t > >;
    } // namesapce detail

    template< typename cursor_t >
    struct basic_iterator {

    };

} // namespace gap::range
