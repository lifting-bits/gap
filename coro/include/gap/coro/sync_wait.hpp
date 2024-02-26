// Copyright (c) 2024, Trail of Bits, Inc.

#pragma once

#ifdef GAP_ENABLE_COROUTINES

    #include <gap/coro/awaitable_traits.hpp>
    #include <gap/coro/coroutine.hpp>

    #include <semaphore>
    #include <cassert>

namespace gap::coro
{
    template< awaitable awaitable_t >
    auto sync_wait(awaitable_t &&awaitable) -> await_result_t< awaitable_t > {
        struct void_type {};

        using result_t = await_result_t< awaitable_t >;
        using storage_type = std::add_pointer_t<
            std::conditional_t<
                std::is_void_v< result_t >,
                void_type, result_t
            >
        >;
        using result_type = std::variant< std::monostate, storage_type, std::exception_ptr >;

        struct sync_wait_task {
            struct promise_type {
                using coroutine_handle = gap::coroutine_handle< promise_type >;

                sync_wait_task get_return_object() noexcept {
                    return sync_wait_task{ coroutine_handle::from_promise(*this) };
                }

                gap::suspend_always initial_suspend() const noexcept { return {}; }

                struct final_awaiter {
                    bool await_ready() const noexcept { return false; }

                    void await_suspend(coroutine_handle coroutine) noexcept {
                        // Now that coroutine has suspended we can signal the semaphore,
                        // unblocking the waiting thread. The other thread will then
                        // destroy this coroutine (which is safe because it is suspended).
                        coroutine.promise().m_semaphore.release();
                    }

                    void await_resume() const noexcept {}
                };

                final_awaiter final_suspend() const noexcept { return {}; }

                using non_void_return_type = std::conditional_t< std::is_void_v<result_t>, void_type, result_t >;

                final_awaiter yield_value(non_void_return_type value) requires (!std::is_void_v< result_t >) {
                    // Note that we just store the address here and then suspend
                    // and unblock the waiting thread which then copies/moves the
                    // result from this address directly to the return-value of
                    // sync_wait(). This avoids having to make an extra intermediate
                    // copy of the result value.
                    m_result.template emplace< storage_type >(std::addressof(value));
                    return {};
                }

                void return_void() noexcept {
                    m_result.template emplace< storage_type >();
                }

                void unhandled_exception() noexcept {
                    m_result.template emplace< std::exception_ptr >(std::current_exception());
                }

                std::binary_semaphore m_semaphore{0};
                result_type m_result;
            };

            using coroutine_handle = gap::coroutine_handle< promise_type >;

            explicit sync_wait_task(coroutine_handle coroutine) noexcept
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

            // The force-inline here is required to get the _sync_task coroutine
            // elided.  Otherwise the compiler doesn't know that this function
            // hasn't modified 'coro' member variable and so can't deduce that it's
            // always destroyed before sync_wait() returns.
            __attribute__((always_inline)) result_t run() {
                m_coroutine.resume();
                m_coroutine.promise().m_semaphore.acquire();
                auto& result = m_coroutine.promise().m_result;

                if (result.index() == 2) {
                    std::rethrow_exception(std::get< 2 >(result));
                }

                assert(result.index() == 1);

                if constexpr (std::is_void_v< result_t >) {
                    return;
                } else {
                    return static_cast< result_t&& >(*std::get< 1 >(result));
                }
            }

            private:
                coroutine_handle m_coroutine;
        };

        return [&] () -> sync_wait_task {
            if constexpr (std::is_void_v< result_t >) {
                co_await static_cast< awaitable_t&& >(awaitable);
            } else {
                // use co_yield instead of co_return so we suspend while the
                // potentially temporary result of co_await is still alive.
                co_yield co_await static_cast< awaitable_t&& >(awaitable);
            }
        }().run();
    }
} // namespace gap::coro

#endif