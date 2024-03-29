// Copyright (c) 2024, Trail of Bits, Inc.

///////////////////////////////////////////////////////////////////////////////
// Copyright (c) Lewis Baker
// Licenced under MIT license. See LICENSE.txt for details.
///////////////////////////////////////////////////////////////////////////////
// This file is a modified version of cppcoro/task.hpp from the cppcoro
// project. The original file is licenced under the MIT license and the original
// license is included above.
///////////////////////////////////////////////////////////////////////////////

#pragma once

#ifdef GAP_ENABLE_COROUTINES

    #include "gap/coro/coroutine.hpp"
    #include "gap/coro/broken_promise.hpp"
    #include "gap/coro/awaitable_traits.hpp"

    #include <atomic>
    #include <cassert>
    #include <exception>
    #include <type_traits>
    #include <utility>
    #include <variant>

namespace gap::coro
{
    template< typename T = void >
    struct task;

    namespace detail
    {
        struct task_promise_base {
          private:
            friend struct final_awaitable;

            struct final_awaiter {
                constexpr bool await_ready() const noexcept { return false; }

            #if GAP_COMPILER_SUPPORTS_SYMMETRIC_TRANSFER
                template< typename promise_t >
                gap::coroutine_handle<> await_suspend(
                    gap::coroutine_handle< promise_t > coroutine) noexcept
                {
                    return coroutine.promise().m_continuation;
                }
            #else
                template< typename promise_t >
                GAP_NOINLINE
                void await_suspend(gap::coroutine_handle< promise_t > coroutine) noexcept {
                    task_promise_base& promise = coroutine.promise();
                    // Use 'release' memory semantics in case we finish before the
					// awaiter can suspend so that the awaiting thread sees our
					// writes to the resulting value.
					// Use 'acquire' memory semantics in case the caller registered
					// the continuation before we finished. Ensure we see their write
					// to m_continuation.
                    if (promise.m_state.exchange(true, std::memory_order_acq_rel)) {
                        promise.m_continuation.resume();
                    }
                }
            #endif

                void await_resume() const noexcept {}
            };

          public:
            task_promise_base() noexcept = default;

            gap::suspend_always initial_suspend() const noexcept { return {}; }
            final_awaiter final_suspend() const noexcept { return {}; }

        #if GAP_COMPILER_SUPPORTS_SYMMETRIC_TRANSFER
            void set_continuation(gap::coroutine_handle<> continuation) noexcept {
                m_continuation = continuation;
            }
        #else
            bool try_set_continuation(gap::coroutine_handle<> continuation) noexcept {
                m_continuation = continuation;
                return !m_state.exchange(true, std::memory_order_acq_rel);
            }
        #endif

          protected:
            #if !GAP_COMPILER_SUPPORTS_SYMMETRIC_TRANSFER
                // Initially false. Set to true when either a continuation is registered
                // or when the coroutine has run to completion. Whichever operation
                // successfully transitions from false->true got there first.
                std::atomic< bool > m_state = false;
            #endif
            gap::coroutine_handle<> m_continuation = nullptr;
        };

        template< typename T >
        struct task_promise final : task_promise_base {
            using result_type = std::variant< std::monostate, T, std::exception_ptr >;

            task_promise() noexcept = default;

            task< T > get_return_object() noexcept;

            void unhandled_exception() { m_result = std::current_exception(); }

            template< typename U >
                requires std::is_convertible_v< U&&, T >
            void return_value(U&& value)
                noexcept(std::is_nothrow_constructible_v<T, U&&>)
            {
                m_result.template emplace< T >(std::forward< U >(value));
            }

            T& result() & {
                if (std::holds_alternative< std::exception_ptr >(m_result)) {
                    std::rethrow_exception(std::get< std::exception_ptr >(m_result));
                }

                assert(std::holds_alternative< T >(m_result));
                return std::get< T >(m_result);
            }

            // HACK: Need to have co_await of task<int> return prvalue rather than
            // rvalue-reference to work around an issue with MSVC where returning
            // rvalue reference of a fundamental type from await_resume() will
            // cause the value to be copied to a temporary. This breaks the
            // sync_wait() implementation.
            // See https://github.com/lewissbaker/GAP/issues/40#issuecomment-326864107
            using rvalue_type
                = std::conditional_t< std::is_arithmetic_v< T > || std::is_pointer_v< T >, T, T&& >;

            rvalue_type result() && {
                if (std::holds_alternative< std::exception_ptr >(m_result)) {
                    std::rethrow_exception(std::get< std::exception_ptr >(m_result));
                }

                assert(std::holds_alternative< T >(m_result));
                return std::get< T >(std::move(m_result));
            }

          private:
            result_type m_result;
        };

        template<>
        struct task_promise< void > : task_promise_base {
            task_promise() noexcept = default;

            task< void > get_return_object() noexcept;

            void return_void() noexcept {}

            void result() {
                if (m_result) {
                    std::rethrow_exception(m_result);
                }
            }

            void unhandled_exception() { m_result = std::current_exception(); }

          private:
            std::exception_ptr m_result;
        };

        template< typename T >
        struct task_promise< T& > : task_promise_base {
            task_promise() noexcept = default;

            task< T& > get_return_object() noexcept;

            void return_value(T& value) noexcept { m_result = std::addressof(value); }

            T& result() {
                if (m_exception) {
                    std::rethrow_exception(m_exception);
                }

                assert(m_result);
                return *m_result;
            }

            void unhandled_exception() { m_exception = std::current_exception(); }

          private:
            T* m_result = nullptr;
            std::exception_ptr m_exception;
        };

        template< typename T >
        using promise_type = detail::task_promise< T >;

        template< typename T >
        using coroutine_handle = gap::coroutine_handle< promise_type< T > >;
    } // namespace detail

    template< typename T >
    struct [[nodiscard]] task {
        using promise_type     = detail::promise_type< T >;
        using coroutine_handle = detail::coroutine_handle< T >;

      private:
        struct awaitable_base {
            coroutine_handle m_coroutine;

            awaitable_base(coroutine_handle coroutine) noexcept
                : m_coroutine(coroutine) {}

            bool await_ready() const noexcept { return !m_coroutine || m_coroutine.done(); }

        #if GAP_COMPILER_SUPPORTS_SYMMETRIC_TRANSFER
            gap::coroutine_handle<> await_suspend(gap::coroutine_handle<> coroutine) noexcept {
                m_coroutine.promise().set_continuation(coroutine);
                return m_coroutine;
            }
        #else
            bool await_suspend(gap::coroutine_handle<> coroutine) noexcept {
                m_coroutine.resume();
                return m_coroutine.promise().try_set_continuation(coroutine);
            }
        #endif

        };

      public:
        task() noexcept = default;

        explicit task(coroutine_handle coroutine) noexcept
            : m_coroutine(coroutine)
        {}

        task(const task&) = delete;

        task(task&& other) noexcept
            : m_coroutine(std::exchange(other.m_coroutine, nullptr)) {}

        ~task() {
            if (m_coroutine) {
                m_coroutine.destroy();
            }
        }

        task& operator=(const task&) = delete;
        task& operator=(task&& other) noexcept {
            if (this != std::addressof(other)) {
                if (m_coroutine) {
                    m_coroutine.destroy();
                }

                m_coroutine = std::exchange(other.m_coroutine, nullptr);
            }

            return *this;
        }

        bool is_ready() const noexcept { return !m_coroutine || m_coroutine.done(); }

        auto operator co_await() const& noexcept {
            struct awaitable : awaitable_base {
                using awaitable_base::awaitable_base;

                decltype(auto) await_resume() {
                    if (!this->m_coroutine) {
                        throw broken_promise{};
                    }

                    return this->m_coroutine.promise().result();
                }
            };

            return awaitable{ m_coroutine };
        }

        auto operator co_await() const&& noexcept {
            struct awaitable : awaitable_base {
                using awaitable_base::awaitable_base;

                decltype(auto) await_resume() {
                    if (!this->m_coroutine) {
                        throw broken_promise{};
                    }

                    return std::move(this->m_coroutine.promise()).result();
                }
            };

            return awaitable{ m_coroutine };
        }

        // Returns an awaitable that will await completion of the task without
        // attempting to retrieve the result.
        auto when_ready() const noexcept {
            struct awaitable : awaitable_base {
                using awaitable_base::awaitable_base;
                void await_resume() const noexcept {}
            };

            return awaitable{ m_coroutine };
        }

      private:
        coroutine_handle m_coroutine = nullptr;
    };

    template< awaitable awaitable_t >
    auto make_task(awaitable_t awaitable)
        -> task< std::remove_reference_t< await_result_t< awaitable_t > > >
    {
        co_return co_await static_cast< awaitable_t&& >(awaitable);
    }

    namespace detail
    {
        template< typename T >
        task< T > task_promise< T >::get_return_object() noexcept {
            return task< T >{ gap::coroutine_handle< task_promise >::from_promise(*this) };
        }

        inline task< void > task_promise< void >::get_return_object() noexcept {
            return task< void >{ gap::coroutine_handle< task_promise >::from_promise(*this) };
        }

        template< typename T >
        task< T& > task_promise< T& >::get_return_object() noexcept {
            return task< T& >{ gap::coroutine_handle< task_promise >::from_promise(*this) };
        }
    } // namespace detail
} // namespace gap::coro

#endif