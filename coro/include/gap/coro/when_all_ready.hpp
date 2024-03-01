// Copyright (c) 2024, Trail of Bits, Inc.

///////////////////////////////////////////////////////////////////////////////
// Copyright (c) Lewis Baker
// Licenced under MIT license. See LICENSE.txt for details.
///////////////////////////////////////////////////////////////////////////////
// This file is a modified version of cppcoro/when_all_ready.hpp from the cppcoro
// project. The original file is licenced under the MIT license and the original
// license is included above.
///////////////////////////////////////////////////////////////////////////////

#pragma once

#ifdef GAP_ENABLE_COROUTINES

    #include <gap/core/type_traits.hpp>
    #include <gap/coro/awaitable_traits.hpp>
    #include <gap/coro/coroutine.hpp>

    #include <semaphore>
    #include <cassert>
    #include <vector>

namespace gap::coro
{
    namespace detail {
        struct void_type {};

        struct when_all_counter
        {
            when_all_counter(std::size_t count) noexcept : m_counter(count + 1) {}

            bool is_ready() const noexcept {
                // We consider this complete if we're asking whether it's ready
				// after a coroutine has already been registered.
				return static_cast<bool>(m_awaiting_coroutine);
            }

            bool try_await(gap::coroutine_handle<> waiting_coroutine) noexcept {
                m_awaiting_coroutine = waiting_coroutine;
                return m_counter.fetch_sub(1, std::memory_order_acq_rel) > 1;
            }

            void notify_awaitable_completed() noexcept {
                if (m_counter.fetch_sub(1, std::memory_order_acq_rel) == 1) {
                    m_awaiting_coroutine.resume();
                }
            }

          protected:
            std::atomic< std::size_t > m_counter = 0;
            gap::coroutine_handle<> m_awaiting_coroutine = nullptr;
        };


        template< typename task_container_t >
        struct when_all_ready_awaitable;

        template<>
        struct when_all_ready_awaitable< std::tuple<> > {
            constexpr when_all_ready_awaitable() noexcept = default;
            explicit constexpr when_all_ready_awaitable(std::tuple<>) noexcept {}

            constexpr bool await_ready() const noexcept { return true; }
            void await_suspend(gap::coroutine_handle<>) const noexcept {}
            std::tuple<> await_resume() const noexcept { return {}; }
        };

        template< typename... awaitables_t >
        struct when_all_ready_awaitable< std::tuple< awaitables_t... > > {
            explicit when_all_ready_awaitable(awaitables_t &&...awaitables)
                noexcept(std::conjunction_v<std::is_nothrow_move_constructible< awaitables_t >... >)
                : m_counter(sizeof...(awaitables_t))
                , m_awaitables(std::forward< awaitables_t >(awaitables)...)
            {}

            explicit when_all_ready_awaitable(std::tuple< awaitables_t... > &&awaitables)
                noexcept(std::is_nothrow_move_constructible_v< std::tuple< awaitables_t... > >)
                : m_counter(sizeof...(awaitables_t))
                , m_awaitables(std::move(awaitables))
            {}

            when_all_ready_awaitable(when_all_ready_awaitable &&other) noexcept
                : m_counter(sizeof...(awaitables_t))
                , m_awaitables(std::move(other.m_awaitables))
            {}

            auto operator co_await() & noexcept
            {
                struct awaiter
                {   awaiter(when_all_ready_awaitable &awaitable) noexcept
                        : m_awaitable(awaitable)
                    {}

                    bool await_ready() const noexcept {
                        return m_awaitable.is_ready();
                    }

                    bool await_suspend(gap::coroutine_handle<> awaiting_coroutine) noexcept {
                        return m_awaitable.try_await(awaiting_coroutine);
                    }

                    std::tuple< awaitables_t... >& await_resume() noexcept {
                        return m_awaitable.m_awaitables;
                    }

                  private:
                        when_all_ready_awaitable &m_awaitable;
                };

                return awaiter{ *this };
            }

            auto operator co_await() && noexcept {
                struct awaiter
                {
                    awaiter(when_all_ready_awaitable &awaitable) noexcept
                        : m_awaitable(awaitable)
                    {}

                    bool await_ready() const noexcept {
                        return m_awaitable.is_ready();
                    }

                    bool await_suspend(gap::coroutine_handle<> awaiting_coroutine) noexcept {
                        return m_awaitable.try_await(awaiting_coroutine);
                    }

                    std::tuple< awaitables_t... >&& await_resume() noexcept {
                        return std::move(m_awaitable.m_awaitables);
                    }

                  private:
                    when_all_ready_awaitable& m_awaitable;
                };

                return awaiter{ *this };
            }

          private:
            bool is_ready() const noexcept {
                return m_counter.is_ready();
            }

            bool try_await(gap::coroutine_handle<> awaiting_coroutine) noexcept {
                start_tasks(std::index_sequence_for< awaitables_t... >{});
                return m_counter.try_await(awaiting_coroutine);
            }

            template< std::size_t... idxs >
            void start_tasks(std::index_sequence< idxs... >) noexcept {
                (std::get< idxs >(m_awaitables).start(m_counter), ...);
            }

            when_all_counter m_counter;
            std::tuple< awaitables_t... > m_awaitables;
        };

        template< typename awaitables_container >
        struct when_all_ready_awaitable
        {
            explicit when_all_ready_awaitable(awaitables_container &&awaitables) noexcept
                : m_counter(awaitables.size())
                , m_awaitables(std::forward< awaitables_container >(awaitables))
            {}

            when_all_ready_awaitable(when_all_ready_awaitable &&other)
                noexcept(std::is_nothrow_move_constructible_v< awaitables_container >)
                : m_counter(other.m_awaitables.size())
                , m_awaitables(std::move(other.m_awaitables))
            {}

            when_all_ready_awaitable(when_all_ready_awaitable const &other) = delete;
            when_all_ready_awaitable &operator=(when_all_ready_awaitable &&other) = delete;

            auto operator co_await() & noexcept
            {
                struct awaiter
                {
                    awaiter(when_all_ready_awaitable &awaitable) noexcept
                        : m_awaitable(awaitable)
                    {}

                    bool await_ready() const noexcept {
                        return m_awaitable.is_ready();
                    }

                    bool await_suspend(gap::coroutine_handle<> awaiting_coroutine) noexcept {
                        return m_awaitable.try_await(awaiting_coroutine);
                    }

                    awaitables_container &await_resume() noexcept {
                        return m_awaitable.m_awaitables;
                    }

                  private:
                    when_all_ready_awaitable &m_awaitable;
                };

                return awaiter{ *this };
            }

            auto operator co_await() && noexcept
            {
                struct awaiter
                {
                    awaiter(when_all_ready_awaitable &awaitable) noexcept
                        : m_awaitable(awaitable)
                    {}

                    bool await_ready() const noexcept {
                        return m_awaitable.is_ready();
                    }

                    bool await_suspend(gap::coroutine_handle<> awaiting_coroutine) noexcept {
                        return m_awaitable.try_await(awaiting_coroutine);
                    }

                    awaitables_container &&await_resume() noexcept {
                        return std::move(m_awaitable.m_awaitables);
                    }

                  private:
                    when_all_ready_awaitable& m_awaitable;
                };

                return awaiter{ *this };
            }

          private:
            bool is_ready() const noexcept {
                return m_counter.is_ready();
            }

            bool try_await(gap::coroutine_handle<> awaiting_coroutine) noexcept {
                for (auto &&awaitable : m_awaitables) {
                    awaitable.start(m_counter);
                }

                return m_counter.try_await(awaiting_coroutine);
            }

            when_all_counter m_counter;
            awaitables_container m_awaitables;
        };

        template< typename result_t >
        struct when_all_task;

        template< typename result_t >
        struct when_all_task_promise final {
            using coroutine_handle = gap::coroutine_handle< when_all_task_promise >;

            when_all_task_promise() noexcept = default;

            auto get_return_object() noexcept {
                return coroutine_handle::from_promise(*this);
            }

            gap::suspend_always initial_suspend() const noexcept {
                return {};
            }

            auto final_suspend() const noexcept {
                struct final_awaiter_t {
                    bool await_ready() const noexcept { return false; }

                    void await_suspend(coroutine_handle coroutine) noexcept {
                        coroutine.promise().m_counter->notify_awaitable_completed();
                    }

                    void await_resume() const noexcept {}
                };

                return final_awaiter_t{};
            }

            void unhandled_exception() noexcept {
                m_exception = std::current_exception();
            }

            void return_void() noexcept {
                // We should have either suspended at co_yield point or an
                // exception was thrown before running off the end of the
                // coroutine.
				assert(false);
            }

            auto yield_value(result_t &&result) noexcept {
                m_result = std::addressof(result);
                return final_suspend();
            }

            void start(when_all_counter &counter) noexcept {
                m_counter = &counter;
                coroutine_handle::from_promise(*this).resume();
            }

            result_t&& result() && {
                rethrow_if_exception();
                return std::forward< result_t >(*m_result);
            }

            result_t& result() & {
                rethrow_if_exception();
                return *m_result;
            }

          private:

            void rethrow_if_exception() {
                if (m_exception) {
                    std::rethrow_exception(m_exception);
                }
            }

            when_all_counter* m_counter;
            std::exception_ptr m_exception;
            std::add_pointer_t< result_t > m_result;
        };

        template<>
        struct when_all_task_promise<void> final
        {
            using coroutine_handle = gap::coroutine_handle< when_all_task_promise >;

            when_all_task_promise() noexcept = default;

            auto get_return_object() noexcept {
                return coroutine_handle::from_promise(*this);
            }

            gap::suspend_always initial_suspend() const noexcept {
                return {};
            }

            auto final_suspend() const noexcept {
                struct final_awaiter_t {
                    bool await_ready() const noexcept { return false; }

                    void await_suspend(coroutine_handle coroutine) noexcept {
                        coroutine.promise().m_counter->notify_awaitable_completed();
                    }

                    void await_resume() const noexcept {}
                };

                return final_awaiter_t{};
            }

            void unhandled_exception() noexcept {
                m_exception = std::current_exception();
            }

            void return_void() noexcept {
                // We should have either suspended at co_yield point or an
                // exception was thrown before running off the end of the
                // coroutine.
            }

            void start(when_all_counter &counter) noexcept {
                m_counter = &counter;
                coroutine_handle::from_promise(*this).resume();
            }

            void result() {
                if (m_exception) {
                    std::rethrow_exception(m_exception);
                }
            }
          private:
            when_all_counter* m_counter;
            std::exception_ptr m_exception;
        };

        template< typename result_t >
        struct when_all_task final
        {
            using promise_type = when_all_task_promise< result_t >;
            using coroutine_handle = gap::coroutine_handle< promise_type >;

            when_all_task(coroutine_handle coroutine) noexcept
                : m_coroutine(coroutine)
            {}

            when_all_task(when_all_task const &other) = delete;
            when_all_task(when_all_task &&other) noexcept
                : m_coroutine(std::exchange(other.m_coroutine, coroutine_handle{}))
            {}

            when_all_task &operator=(when_all_task const &other) = delete;
            when_all_task &operator=(when_all_task &&other) {
                if (this != std::addressof(other)) {
                    if (m_coroutine) {
                        m_coroutine.destroy();
                    }

                    m_coroutine = std::exchange(other.m_coroutine, coroutine_handle{});
                }

                return *this;
            }

            ~when_all_task() {
                if (m_coroutine) {
                    m_coroutine.destroy();
                }
            }

            decltype(auto) result() & {
                return m_coroutine.promise().result();
            }

            decltype(auto) result() && {
                return std::move(m_coroutine.promise()).result();
            }

            decltype(auto) non_void_result() & {
                if constexpr (std::is_void_v< decltype(this->result()) >) {
                    return this->result();
                    return void_type{};
                } else {
                    return this->result();
                }
            }

            decltype(auto) non_void_result() && {
                if constexpr (std::is_void_v< decltype(this->result()) >) {
                    std::move(*this).result();
                    return void_type{};
                } else {
                    return std::move(*this).result();
                }
            }

          private:

            template< typename awaitable_container >
            friend struct when_all_ready_awaitable;

            void start(when_all_counter &counter) noexcept {
                m_coroutine.promise().start(counter);
            }

            coroutine_handle m_coroutine;
        };

        template< awaitable awaitable_t, typename result_t = await_result_t< awaitable_t&& > >
        requires (not std::is_void_v< result_t >)
        when_all_task< result_t > make_when_all_task(awaitable_t awaitable) {
            co_yield co_await static_cast< awaitable_t&& >(awaitable);
        }

        template< awaitable awaitable_t, typename result_t = await_result_t< awaitable_t&& > >
        requires std::is_void_v< result_t >
        when_all_task< void > make_when_all_task(awaitable_t awaitable) {
            co_await static_cast< awaitable_t&& >(awaitable);
        }

        template< awaitable awaitable_t, typename result_t = await_result_t< awaitable_t& > >
        requires (not std::is_void_v< result_t >)
        when_all_task< result_t > make_when_all_task(std::reference_wrapper< awaitable_t > awaitable) {
            co_yield co_await awaitable.get();
        }

        template< awaitable awaitable_t, typename result_t = await_result_t< awaitable_t& > >
        requires std::is_void_v< result_t >
        when_all_task< void > make_when_all_task(std::reference_wrapper< awaitable_t > awaitable) {
            co_await awaitable.get();
        }

    } // namespace detail

    template< awaitable... awaitable_t >
    GAP_FORCE_INLINE auto when_all_ready(awaitable_t &&...awaitables)
    {
        return detail::when_all_ready_awaitable< std::tuple<
            detail::when_all_task<
                await_result_t<
                    trait::unwrap_reference_t< std::remove_reference_t< awaitable_t > >
                >
            >...
        > >(
            std::make_tuple(
                detail::make_when_all_task(
                    std::forward< awaitable_t >(awaitables)
                )...
            )
        );
    }

    template<
        awaitable awaitable_t,
        typename result_t = await_result_t< std::remove_reference_t< awaitable_t > >
    >
    auto when_all_ready_vec(std::vector< awaitable_t > awaitables)
    {
        std::vector< detail::when_all_task< result_t > > tasks;
        tasks.reserve(awaitables.size());

        for (auto &awaitable : awaitables) {
            tasks.emplace_back(detail::make_when_all_task(std::move(awaitable)));
        }

        return detail::when_all_ready_awaitable< std::vector< detail::when_all_task< result_t > > >(
            std::move(tasks)
        );
    }

} // namespace gap::coro

#endif