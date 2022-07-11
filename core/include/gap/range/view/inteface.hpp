// Copyright (c) 2022-present, Trail of Bits, Inc.

#pragma once

#include <gap/core/concepts.hpp>
#include <gap/range/view/base.hpp>

namespace gap::range::view
{
    template< typename derived_t, cardinality_t cardinality /* = finite*/ >
    struct view_interface : basic_view< cardinality_t > {
      protected:
        constexpr derived_t &derived() noexcept {
            static_assert(derived_from< derived_t, view_interface >);
            return static_cast< derived_t & >(*this);
        }

        constexpr derived_t const &derived() const noexcept {
            static_assert(derived_from< derived_t, view_interface >);
            return static_cast< derived_t const & >(*this);
        }

      public:
        view_interface()                                  = default;
        view_interface(view_interface &&)                 = default;
        view_interface(view_interface const &)            = default;
        view_interface &operator=(view_interface &&)      = default;
        view_interface &operator=(view_interface const &) = default;

        // empty

        // size

        // front

        // back

        // operator []

        // data()

        // at()

        // operator<<
    };

} // namespace gap::range::view
