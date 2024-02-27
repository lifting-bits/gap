// Copyright (c) 2024, Trail of Bits, Inc.

#pragma once

#ifdef GAP_ENABLE_COROUTINES

    #include <gap/coro/coroutine.hpp>
    #include <gap/coro/awaitable_traits.hpp>

    #include <concepts>
    #include <type_traits>
    #include <utility>

namespace gap::coro
{
    namespace detail
    {
        template< typename func_t, awaitable awaitable_t >
        struct fmap_awaiter {
            using awaiter_t = awaiter_type_t< awaitable_t&& >;

            fmap_awaiter(func_t &&func, awaitable_t &&awaitable)
                noexcept(
                    std::is_nothrow_move_constructible_v< func_t > &&
                    noexcept(get_awaiter(static_cast< awaitable_t&& >(awaitable)))
                )
                : m_func(static_cast< func_t&& >(func))
                , m_awaiter(get_awaiter(static_cast< awaitable_t&& >(awaitable)))
            {}

            decltype(auto) await_ready()
                noexcept(noexcept(static_cast< awaiter_t&& >(m_awaiter).await_ready()))
            {
                return static_cast<awaiter_t&&>(m_awaiter).await_ready();
            }

            template< typename promise_t >
            decltype(auto) await_suspend(gap::coroutine_handle< promise_t > coroutine)
                noexcept(noexcept(static_cast< awaiter_t&& >(m_awaiter).await_suspend(std::move(coroutine))))
            {
                return static_cast<awaiter_t&&>(m_awaiter).await_suspend(std::move(coroutine));
            }

            template< typename await_result = decltype(std::declval< awaiter_t >().await_resume()) >
            requires std::is_void_v< await_result >
            decltype(auto) await_resume()
                noexcept(noexcept(std::invoke(static_cast< func_t&& >(m_func))))
            {
                static_cast<awaiter_t&&>(m_awaiter).await_resume();
                return std::invoke(static_cast< func_t&& >(m_func));
            }

            template< typename await_result = decltype(std::declval< awaiter_t >().await_resume()) >
            requires (not std::is_void_v< await_result >)
            decltype(auto) await_resume()
                noexcept(noexcept(std::invoke(static_cast< func_t&& >(m_func), static_cast<awaiter_t&&>(m_awaiter).await_resume())))
            {
                return std::invoke(
                    static_cast< func_t&& >(m_func),
                    static_cast<awaiter_t&&>(m_awaiter).await_resume()
                );
            }
          private:
            func_t &&m_func;
            awaiter_t m_awaiter;
        };

        template< typename func_t, awaitable awaitable_t >
        struct fmap_awaitable
        {
            static_assert(!std::is_lvalue_reference_v< func_t >);
            static_assert(!std::is_lvalue_reference_v< awaitable_t >);

            template< typename func_arg_t, typename awaitable_arg_t >
            requires std::is_constructible_v< func_t, func_arg_t >
                  && std::is_constructible_v< awaitable_t, awaitable_arg_t >
            explicit fmap_awaitable(func_arg_t &&func, awaitable_arg_t &&awaitable)
                noexcept(
                    std::is_nothrow_constructible_v< func_t, func_arg_t > &&
                    std::is_nothrow_constructible_v< awaitable_t, awaitable_arg_t >
                )
                : m_func(static_cast< func_arg_t&& >(func))
                , m_awaitable(static_cast< awaitable_arg_t&& >(awaitable))
            {}

            auto operator co_await() const & {
                return fmap_awaiter< const func_t &, const awaitable_t & >(
                    m_func, m_awaitable
                );
            }

            auto operator co_await() && {
                return fmap_awaiter< func_t &&, awaitable_t && >(
                    static_cast< func_t&& >(m_func),
                    static_cast< awaitable_t&& >(m_awaitable)
                );
            }

            auto operator co_await() & {
                return fmap_awaiter< func_t &, awaitable_t & >(
                    m_func, m_awaitable
                );
            }
          private:
            func_t m_func;
            awaitable_t m_awaitable;
        };

    } // namespace detail

    template< typename func_t >
    struct fmap_transform
    {
        explicit fmap_transform(func_t &&func)
            noexcept(std::is_nothrow_move_constructible_v< func_t >)
            : m_func(std::forward< func_t >(func))
        {}

        func_t m_func;
    };

    template< typename func_t, awaitable awaitable_t >
    auto fmap(func_t &&func, awaitable_t &&awaitable)
    {
        return detail::fmap_awaitable<
            std::remove_cv_t< std::remove_reference_t< func_t > >,
            std::remove_cv_t< std::remove_reference_t< awaitable_t > >
        >(
            std::forward< func_t >(func),
            std::forward< awaitable_t >(awaitable)
        );
    }

    template< typename func_t >
    auto fmap(func_t &&func)
    {
        return fmap_transform< func_t >(
            std::forward< func_t >(func)
        );
    }

    template< typename value_t, typename func_t >
    decltype(auto) operator|(value_t &&value, fmap_transform< func_t > &&transform)
    {
        return fmap(
            std::forward< func_t >(transform.m_func),
            std::forward< value_t >(value)
        );
    }

    template< typename value_t, typename func_t >
    decltype(auto) operator|(value_t &&value, fmap_transform< func_t > &transform)
    {
        return fmap(
            transform.m_func,
            std::forward< value_t >(value)
        );
    }

    template< typename value_t, typename func_t >
    decltype(auto) operator|(value_t &&value, const fmap_transform< func_t > &transform)
    {
        return fmap(
            transform.m_func,
            std::forward< value_t >(value)
        );
    }

} // namespace gap::coro

#endif