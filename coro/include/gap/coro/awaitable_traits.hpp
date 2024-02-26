// Copyright (c) 2024, Trail of Bits, Inc.

#pragma once

#ifdef GAP_ENABLE_COROUTINES

namespace gap::coro
{
    template< typename T >
    struct is_coroutine_handle : std::false_type {};

    template< typename promise_t >
    struct is_coroutine_handle< gap::coroutine_handle< promise_t > > : std::true_type {};

    template< typename T >
    constexpr bool is_coroutine_handle_v = is_coroutine_handle< T >::value;

    template< typename T >
    concept await_suspend_return_type =
        std::is_void_v< T > || std::is_same_v< bool, T > || is_coroutine_handle_v< T >;

    template< typename T >
    concept awaiter = requires {
        { std::declval< T >().await_ready() } -> std::same_as< bool >;
        { std::declval< T >().await_suspend(std::declval< gap::coroutine_handle<> >()) } -> await_suspend_return_type;
        { std::declval< T >().await_resume() };
    };

    template< typename T, typename R >
    concept awaiter_of = awaiter< T > && requires {
        { std::declval< T >().await_resume() } -> std::convertible_to< R >;
    };

    template< typename T >
    concept has_member_co_await = requires(T&& t) {
        { static_cast< T&& >(t).operator co_await() } -> awaiter;
    };

    template< typename T >
    concept has_free_co_await = requires(T&& t) {
        { operator co_await(static_cast< T&& >(t)) } -> awaiter;
    };

    template< typename T >
    concept awaitable = awaiter< T > || has_member_co_await< T > || has_free_co_await< T >;

    template< typename T >
    requires has_member_co_await< T >
    decltype(auto) get_awaiter(T &&t) noexcept(noexcept(static_cast< T&& >(t).operator co_await())) {
        return static_cast< T&& >(t).operator co_await();
    }

    template< typename T >
    requires has_free_co_await< T >
    decltype(auto) get_awaiter(T &&t) noexcept(noexcept(operator co_await(static_cast< T&& >(t)))) {
        return operator co_await(static_cast< T&& >(t));
    }

    template< typename T >
    requires awaiter< T > &&(!has_member_co_await< T > && !has_free_co_await< T >)
    T&& get_awaiter(T &&t) noexcept {
        return static_cast< T&& >(t);
    }

    template< awaitable T >
    using awaiter_type_t = decltype(get_awaiter(std::declval< T >()));

    template< awaitable T >
    using await_result_t = decltype(std::declval< awaiter_type_t< T >& >().await_resume());

} // namespace gap::coro

#endif