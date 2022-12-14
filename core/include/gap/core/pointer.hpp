// Copyright (c) 2022-present, Trail of Bits, Inc.

#pragma once

namespace gap {

    template< typename T >
    struct pointer_wrapper
    {
        static_assert( std::is_pointer_v< T > );

        using pointer_type = T;
        using value_type = std::remove_pointer_t< pointer_type >;

        pointer_type _ptr = nullptr;

        constexpr pointer_wrapper() noexcept = default;
        constexpr pointer_wrapper( pointer_type v ) noexcept : _ptr( v ) {}

        constexpr pointer_type operator->() const noexcept { return _ptr; }
        constexpr value_type& operator*() const noexcept { return *_ptr; }

        constexpr explicit operator bool() const noexcept {
            return static_cast< bool >( _ptr );
        }

        constexpr bool operator!() const noexcept {
            return !static_cast< bool >( *this );
        }

        constexpr pointer_type& ptr() noexcept { return _ptr; }
        constexpr const pointer_type& ptr() const noexcept { return _ptr; }

        constexpr auto operator<=>(const pointer_wrapper &other) const noexcept = default;

        template< typename stream >
        friend auto operator<<( stream &o, const pointer_wrapper< T > &p )
            -> decltype( o << std::declval< void * >() )
        {
            return o << p._ptr;
        }
    };

} // namespace gap
