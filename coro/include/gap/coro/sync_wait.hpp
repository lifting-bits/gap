// Copyright (c) 2024, Trail of Bits, Inc.

///////////////////////////////////////////////////////////////////////////////
// Copyright (c) Lewis Baker
// Licenced under MIT license. See LICENSE.txt for details.
///////////////////////////////////////////////////////////////////////////////
// This file is a modified version of cppcoro/sync_wait.hpp from the cppcoro
// project. The original file is licenced under the MIT license and the original
// license is included above.
///////////////////////////////////////////////////////////////////////////////

#pragma once

#ifdef GAP_ENABLE_COROUTINES

    #include <gap/coro/awaitable_traits.hpp>
    #include <gap/coro/coroutine.hpp>
    #include <gap/coro/manual_reset_event.hpp>

    #include <semaphore>
    #include <cassert>

namespace gap::coro
{
    template< typename result_t >
    struct sync_wait_task;

    template< typename result_t >
    struct sync_wait_task_promise {
        using coroutine_handle = gap::coroutine_handle< sync_wait_task_promise >;

        sync_wait_task_promise() noexcept = default;

        void start(manual_reset_event &event) noexcept {
            m_event = &event;
            coroutine_handle::from_promise(*this).resume();
        }

        auto get_return_object() noexcept {
            return coroutine_handle::from_promise(*this);
        }

        gap::suspend_always initial_suspend() noexcept {
            return {};
        }

        auto final_suspend() noexcept {
            struct final_awaiter {
                bool await_ready() const noexcept {
                    return false;
                }

                void await_suspend(coroutine_handle coroutine) noexcept {
                    coroutine.promise().m_event->set();
                }

                void await_resume() const noexcept {}
            };

            return final_awaiter{};
        }

        auto yield_value(result_t &&value) noexcept {
            m_result = std::addressof(value);
            return final_suspend();
        }

        void return_void() noexcept {
            assert(false);
        }

        void unhandled_exception() noexcept {
            m_exception = std::current_exception();
        }

        result_t &&result() {
            if (m_exception) {
                std::rethrow_exception(m_exception);
            }

            return static_cast< result_t&& >(*m_result);
        }
        private:
        manual_reset_event *m_event = nullptr;
        std::remove_reference_t< result_t > *m_result = nullptr;
        std::exception_ptr m_exception;
    };

    template<>
    struct sync_wait_task_promise< void >
    {
        using coroutine_handle = gap::coroutine_handle< sync_wait_task_promise >;

        sync_wait_task_promise() noexcept = default;

        void start(manual_reset_event &event) noexcept {
            m_event = &event;
            coroutine_handle::from_promise(*this).resume();
        }

        auto get_return_object() noexcept {
            return coroutine_handle::from_promise(*this);
        }

        gap::suspend_always initial_suspend() noexcept {
            return {};
        }

        auto final_suspend() noexcept {
            struct final_awaiter {
                bool await_ready() const noexcept {
                    return false;
                }

                void await_suspend(coroutine_handle coroutine) noexcept {
                    coroutine.promise().m_event->set();
                }

                void await_resume() const noexcept {}
            };

            return final_awaiter{};
        }

        void return_void() noexcept {}

        void unhandled_exception() noexcept {
            m_exception = std::current_exception();
        }

        void result() {
            if (m_exception) {
                std::rethrow_exception(m_exception);
            }
        }

      private:
        manual_reset_event *m_event = nullptr;
        std::exception_ptr m_exception;
    };

    template< typename result_t >
    struct sync_wait_task final
    {
        using promise_type = sync_wait_task_promise< result_t >;
        using coroutine_handle = gap::coroutine_handle< promise_type >;

        sync_wait_task(coroutine_handle coroutine) noexcept
            : m_coroutine(coroutine)
        {}

        sync_wait_task(sync_wait_task const &other) = delete;
        sync_wait_task(sync_wait_task &&other) noexcept
            : m_coroutine(std::exchange(other.m_coroutine, coroutine_handle{}))
        {}

        sync_wait_task &operator=(sync_wait_task const &other) = delete;
        sync_wait_task &operator=(sync_wait_task &&other) noexcept {
            m_coroutine = std::exchange(other.m_coroutine, coroutine_handle{});
            return *this;
        }

        void start(manual_reset_event &event) noexcept {
            m_coroutine.promise().start(event);
        }

        decltype(auto) result() {
            return m_coroutine.promise().result();
        }
      private:
        coroutine_handle m_coroutine;
    };

    template< awaitable awaitable_t, typename result_t = await_result_t< awaitable_t&& > >
    requires (not std::is_void_v< result_t >)
    sync_wait_task< result_t > make_sync_wait_task(awaitable_t &&awaitable) {
        co_yield co_await std::forward< awaitable_t >(awaitable);
    }

    template< awaitable awaitable_t, typename result_t = await_result_t< awaitable_t&& > >
    requires std::is_void_v< result_t >
    sync_wait_task< void > make_sync_wait_task(awaitable_t &&awaitable) {
        co_await std::forward< awaitable_t >(awaitable);
    }

    template< awaitable awaitable_t >
    auto sync_wait(awaitable_t &&awaitable) -> await_result_t< awaitable_t > {
        auto task = make_sync_wait_task(std::forward< awaitable_t >(awaitable));
        manual_reset_event event;
        task.start(event);
        event.wait();
        return task.result();
    }
} // namespace gap::coro

#endif