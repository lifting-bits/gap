// Copyright (c) 2022-present, Trail of Bits, Inc.

#pragma once

#include <concepts>
#include <optional>
#include <type_traits>

#include <gap/core/concepts.hpp>
#include <gap/core/pointer.hpp>

namespace gap {

    //
    // optional concepts
    //
    template< typename T >
    concept optional_like = requires (T a) {
        { a.value() }     -> convertible_to< typename T::value_type >;
        { a.has_value() } -> convertible_to< bool >;
        { *a } -> convertible_to< typename T::value_type >;
    };

    //
    // optional-like wrapper details
    //
    namespace detail {

        template< typename T >
        struct value_like_optional_adaptor : T {
            using base = T;
            using base::base;

            using value_type = T;

            constexpr value_type* operator->() noexcept { return this; }
            constexpr const value_type* operator->() const noexcept { return this; }

            constexpr value_type& operator*() & noexcept { return *this; }
            constexpr const value_type& operator*() const& noexcept { return *this; }
            constexpr value_type&& operator*() && noexcept { return std::move(*this); }
            constexpr const value_type&& operator*() const&& noexcept { return std::move(*this); }
        };

        template< typename T >
        using optional_adaptor_base =
            std::conditional_t< std::is_pointer_v< T >,
                pointer_wrapper< T >,
                std::conditional_t< std::is_convertible_v< T, bool >,
                    value_like_optional_adaptor< T >,
                T >
        >;

    } // namespace detail

    //
    // optional-like wrapper
    //
    template< typename T >
    struct optional_adaptor : detail::optional_adaptor_base< T >
    {
        using base = detail::optional_adaptor_base< T >;
        using base::base;

        using value_type = typename base::value_type;

        static constexpr bool copy_constructible = std::is_copy_constructible_v< value_type >;
        static constexpr bool move_constructible = std::is_move_constructible_v< value_type >;

        constexpr bool has_value() const noexcept {
            return static_cast< bool >(*this);
        }

        constexpr value_type& value() & { return **this; }
        constexpr const value_type& value() const& { return **this; }
        constexpr value_type&& value() && { return std::move(**this); }
        constexpr const value_type&& value() const&& { return std::move(**this); }

        template< typename U >
            requires(copy_constructible && std::is_convertible_v< U&&, value_type >)
        constexpr value_type value_or( U&& default_value ) const& {
            return bool(*this) ? **this : static_cast< value_type >(std::forward<U>(default_value));
        }

        template< typename U >
            requires(move_constructible && std::is_convertible_v< U&&, value_type >)
        constexpr value_type value_or( U&& default_value ) && {
            return bool(*this) ? std::move(**this) : static_cast< value_type >(std::forward<U>(default_value));
        }
    };

    //
    // optional wrapper
    //
    namespace detail {
        template< typename T >
        using optional_wrapper_base = std::conditional_t<
            optional_like< T >, T, optional_adaptor< T >
        >;
    } // namespace detail

    template< typename base >
    struct optional_wrapper : detail::optional_wrapper_base< base >
    {
        using base_type  = detail::optional_wrapper_base< base >;
        using value_type = typename base_type::value_type;

        using base_type::base_type;
        using base_type::value;

        base& unwrap() & { return *this; }
        const base& unwrap() const& { return *this; }
        base&& unwrap() && { return std::move(*this); }
        const base&& unwrap() const&& { return std::move(*this); }
    };

} // namespace gap
