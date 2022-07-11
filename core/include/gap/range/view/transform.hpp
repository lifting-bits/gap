// Copyright (c) 2022-present, Trail of Bits, Inc.

#pragma once

namespace gap::range::view
{

    namespace detail
    {
        template< typename R, typename F >
        struct iter_transform_view : view_adaptor< iter_transform_view< R, F >, R > {};
    } // namespace detail

} // namespace gap::range::view
