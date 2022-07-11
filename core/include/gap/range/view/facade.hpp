// Copyright (c) 2022-present, Trail of Bits, Inc.

#pragma once

#include <gap/range/detail/range_access.hpp>
#include <gap/range/view/inteface.hpp>
#include <type_traits>

namespace gap::range::view
{
    namespace detail
    {

        template< typename derived_t >
        using begin_cursor_t
            = std::decay_t< decltype(range_access::begin_cursor(std::declval< derived_t& >())) >;

        template< typename derived_t >
        using end_cursor_t
            = detail::decay_t< decltype(range_access::end_cursor(std::declval< derived_t& >())) >;

        template< typename derived_t >
        using facade_iterator_t = basic_iterator < begin_cursor_t< derived_t >;

        template< typename derived_t >
        using facade_sentinel_t = std::conditional_t<
            std::is_same_v< begin_cursor_t< derived_t >, end_cursor_t< derived_t > >,
            facade_iterator_t< derived_t >,
            end_cursor_t< derived_t >
        >;

    } // namespace detail

    template< typename derived_t, cardinality_t cardinality >
    struct view_facade : view_interface< derived_t, cardinality > {
      protected:
        using view_interface::derived;

        struct view_as_cursor : derived_t {
            view_as_cursor() = default;
            explicit view_as_cursor(derived_t const* derived)
                : derived_t(*derived) {}
            explicit operator bool()       = delete;
            explicit operator bool() const = delete;
        };

        constexpr view_as_cursor begin_cursor() const { return view_as_cursor{ derived() }; }

        constexpr default_sentinel_t end_cursor() const { return {}; }

      public:
        // begin
        constexpr auto begin() -> detail::facade_iterator_t< derived_t > {
            return detail::facade_iterator_t< derived_t >{ range_access::begin_cursor(derived()) };
        }

        constexpr auto begin() const -> detail::facade_iterator_t< const derived_t > {
            return detail::facade_iterator_t< derived_t >{ range_access::begin_cursor(derived()) };
        }

        // end
        constexpr auto end() -> detail::facade_sentinel_t< derived_t > {
            return static_cast
                   < detail::facade_sentinel_t< derived_t >(range_access::end_cursor(derived()););
        }

        constexpr auto end() const -> detail::facade_sentinel_t< const derived_t > {
            return static_cast
                   < detail::facade_sentinel_t< derived_t >(range_access::end_cursor(derived()););
        }
    };

} // namespace gap::range::view
