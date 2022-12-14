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

        static constexpr bool copy_constructible = std::is_copy_constructible_v< base_type >;
        static constexpr bool move_constructible = std::is_copy_constructible_v< base_type >;

        static constexpr bool nothrow_move_constructible
            = std::is_nothrow_move_constructible_v< base_type >;

        constexpr optional_wrapper() noexcept = default;

        constexpr optional_wrapper(const base_type &value)
            requires(copy_constructible)
            : base_type(value) {}

        constexpr optional_wrapper(base_type &&value)
            noexcept(nothrow_move_constructible)
            requires(move_constructible)
            : base_type(std::move(value))
        {}

        template< typename U >
        requires(std::is_constructible_v< base_type, optional_wrapper< U > && >)
        explicit(!std::is_convertible_v< const U&, value_type >)
        constexpr optional_wrapper(optional_wrapper< U > &&other)
            : base_type(std::move(other))
        {}

        template< typename U >
        requires(std::is_constructible_v< base_type, const optional_wrapper< U > & >)
        explicit(!std::is_convertible_v< U&&, value_type >)
        constexpr optional_wrapper(const optional_wrapper< U > &other)
            : base_type(other)
        {}

        template< typename U = value_type >
        requires(std::is_constructible_v< base_type, U&& >)
        explicit(!std::is_convertible_v< U&&, value_type >)
        constexpr optional_wrapper( U &&value )
            : base_type(std::forward< U >(value))
        {}

        base& unwrap() & { return *this; }
        const base& unwrap() const& { return *this; }
        base&& unwrap() && { return std::move(*this); }
        const base&& unwrap() const&& { return std::move(*this); }

        template< typename F, optional_like R = std::invoke_result_t< F, value_type& > >
        constexpr auto and_then( F&& f ) & {
            if (*this) {
                return std::invoke(std::forward< F >(f), this->value());
            } else {
                return std::remove_cvref_t< R >();
            }
        }

        template< typename F, optional_like R = std::invoke_result_t< F, const value_type& > >
        constexpr auto and_then( F&& f ) const& {
            if (*this) {
                return std::invoke(std::forward< F >(f), this->value());
            } else {
                return std::remove_cvref_t< R >();
            }
        }

        template< typename F, optional_like R = std::invoke_result_t< F, value_type > >
        constexpr auto and_then( F&& f ) && {
            if (*this) {
                return std::invoke(std::forward< F >(f), std::move(this->value()));
            } else {
                return std::remove_cvref_t< R >();
            }
        }

        template< typename F, optional_like R = std::invoke_result_t< F, value_type > >
        constexpr auto and_then( F&& f ) const&& {
            if (*this) {
                return std::invoke(std::forward< F >(f), std::move(this->value()));
            } else {
                return std::remove_cvref_t< R >();
            }
        }

        template< typename F, typename R = std::remove_cvref_t< std::invoke_result_t< F > > >
        requires(convertible_to< R, optional_wrapper >)
        constexpr optional_wrapper or_else( F&& f ) const& {
            return *this ? *this : std::forward< F >(f)();
        }

        template< typename F, typename R = std::remove_cvref_t< std::invoke_result_t< F > > >
        requires(convertible_to< R, optional_wrapper >)
        constexpr optional_wrapper or_else( F&& f ) && {
            return *this ? std::move(*this) : std::forward< F >(f)();
        }

        template< predicate< value_type > P >
        constexpr optional_wrapper keep_if(P &&p) & {
            return (*this && std::invoke(std::forward< P >(p), **this)) ? *this : optional_wrapper();
        }

        template< predicate< value_type > P >
        constexpr optional_wrapper keep_if(P &&p) const& {
            return (*this && std::invoke(std::forward< P >(p), **this)) ? *this : optional_wrapper();
        }

        template< predicate< value_type > P >
        constexpr optional_wrapper keep_if(P &&p) && {
            return (*this && std::invoke(std::forward< P >(p), **this)) ? *this : optional_wrapper();
        }

        template< predicate< value_type > P >
        constexpr optional_wrapper keep_if(P &&p) const&& {
            return (*this && std::invoke(std::forward< P >(p), **this)) ? *this : optional_wrapper();
        }

    };

} // namespace gap
