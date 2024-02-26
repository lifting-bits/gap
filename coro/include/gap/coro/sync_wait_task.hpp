// Copyright (c) 2024, Trail of Bits, Inc.

#pragma once

#ifdef GAP_ENABLE_COROUTINES

    #include "gap/coro/awaitable_traits.hpp"
    #include "gap/coro/manual_reset_event.hpp"

namespace gap::coro
{
    template< typename result_t >
    struct sync_wait_task;

    namespace detail
    {
        template< typename result_t >
        struct sync_wait_task_promise final {
            using coroutine_handle = gap::coroutine_handle< sync_wait_task_promise >;
            using reference_type   = std::add_rvalue_reference_t< result_t >;

            sync_wait_task_promise() noexcept = default;

            void start(manual_reset_event &event) noexcept {
                m_event = &event;
                coroutine_handle::from_promise(*this).resume();
            }

            auto get_return_object() noexcept { return coroutine_handle::from_promise(*this); }

            gap::suspend_always initial_suspend() const noexcept { return {}; }

            auto final_suspend() const noexcept {
                struct final_awaiter {
                    bool await_ready() const noexcept { return false; }

                    void await_suspend(coroutine_handle coroutine) noexcept {
                        coroutine.promise().m_event->set();
                    }

                    void await_resume() const noexcept {}
                };

                return final_awaiter{};
            }

            auto yield_value(reference_type value) noexcept {
                m_result = std::addressof(value);
                return final_suspend();
            }

            void return_void() noexcept {
                // The coroutine should have either yielded a value or thrown
                // an exception in which case it should have bypassed return_void().
                assert(false);
            }

            void unhandled_exception() noexcept { m_exception = std::current_exception(); }

            reference_type result() {
                if (m_exception) {
                    std::rethrow_exception(m_exception);
                }

                assert(m_result);
                return static_cast< reference_type >(*m_result);
            }

          private:
            manual_reset_event *m_event = nullptr;
            std::remove_reference_t< result_t > m_result;
            std::exception_ptr m_exception;
        };

        template<>
        struct sync_wait_task_promise< void > final {
            using coroutine_handle = gap::coroutine_handle< sync_wait_task_promise >;

            sync_wait_task_promise() noexcept = default;

            void start(manual_reset_event &event) noexcept {
                m_event = &event;
                coroutine_handle::from_promise(*this).resume();
            }

            auto get_return_object() noexcept { return coroutine_handle::from_promise(*this); }

            gap::suspend_always initial_suspend() const noexcept { return {}; }

            auto final_suspend() const noexcept {
                struct final_awaiter {
                    bool await_ready() const noexcept { return false; }

                    void await_suspend(coroutine_handle coroutine) noexcept {
                        coroutine.promise().m_event->set();
                    }

                    void await_resume() const noexcept {}
                };

                return final_awaiter{};
            }

            void return_void() noexcept {}

            void unhandled_exception() noexcept { m_exception = std::current_exception(); }

            void result() {
                if (m_exception) {
                    std::rethrow_exception(m_exception);
                }
            }

          private:
            manual_reset_event *m_event = nullptr;
            std::exception_ptr m_exception;
        };
    } // namespace detail

    template< typename result_t >
    struct sync_wait_task final {
        using promise_type     = detail::sync_wait_task_promise< result_t >;
        using coroutine_handle = gap::coroutine_handle< promise_type >;

        sync_wait_task(coroutine_handle coroutine) noexcept
            : m_coroutine(coroutine) {}

        sync_wait_task(const sync_wait_task &) = delete;
        sync_wait_task(sync_wait_task &&other) noexcept
            : m_coroutine(std::exchange(other.m_coroutine, {})) {}

        ~sync_wait_task() {
            if (m_coroutine) {
                m_coroutine.destroy();
            }
        }

        sync_wait_task &operator=(const sync_wait_task &) = delete;
        sync_wait_task &operator=(sync_wait_task &&other) {
            if (this != std::addressof(other)) {
                if (m_coroutine) {
                    m_coroutine.destroy();
                }

                m_coroutine = std::exchange(other.m_coroutine, {});
            }

            return *this;
        }

        void start(manual_reset_event &event) noexcept { m_coroutine.promise().start(event); }

        decltype(auto) result() { m_coroutine.promise().result(); }

        private:
        coroutine_handle m_coroutine;
    };

    template< awaitable awaitable_t >
        requires std::is_void_v< await_result_t< awaitable_t > >
    sync_wait_task< void > make_sync_wait_task(awaitable_t &&awaitable) {
        co_await std::forward< awaitable_t >(awaitable);
    }

    template< awaitable awaitable_t >
        requires ( not std::is_void_v< await_result_t< awaitable_t > > )
    sync_wait_task< await_result_t< awaitable_t > > make_sync_wait_task(awaitable_t &&awaitable) {
        co_yield co_await std::forward< awaitable_t >(awaitable);
    }

} // namespace gap::coro

#endif