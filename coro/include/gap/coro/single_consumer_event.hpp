// Copyright (c) 2024, Trail of Bits, Inc.

///////////////////////////////////////////////////////////////////////////////
// Copyright (c) Lewis Baker
// Licenced under MIT license. See LICENSE.txt for details.
///////////////////////////////////////////////////////////////////////////////
// This file is a modified version of cppcoro/single_consumer_event.hpp from the
// cppcoro project. The original file is licenced under the MIT license and the
// original license is included above.
///////////////////////////////////////////////////////////////////////////////

#pragma once

#ifdef GAP_ENABLE_COROUTINES

    #include <gap/coro/coroutine.hpp>
    #include <gap/coro/awaitable_traits.hpp>

    #include <atomic>
    #include <concepts>
    #include <type_traits>
    #include <utility>

namespace gap::coro
{
    // A manual-reset event that supports only a single awaiting
	// coroutine at a time. See cppcoro for more details.

    struct single_consumer_event
    {
        enum class state_kind { notset, set, waiting };

        single_consumer_event(bool initially_set = false) noexcept
            : m_state(initially_set ? state_kind::set : state_kind::notset)
        {}

        bool is_set() const noexcept {
            return m_state.load(std::memory_order_acquire) == state_kind::set;
        }

        void set() noexcept {
            if (m_state.exchange(state_kind::set, std::memory_order_acq_rel) == state_kind::waiting) {
                m_awaiter.resume();
            }
        }

        void reset() noexcept {
            state_kind old = state_kind::set;
            m_state.compare_exchange_strong(old, state_kind::notset, std::memory_order_relaxed);
        }

        auto operator co_await() noexcept {
            struct awaiter {
                single_consumer_event &m_event;

                bool await_ready() const noexcept {
                    return m_event.is_set();
                }

                bool await_suspend(gap::coroutine_handle<> handle) noexcept {
                    m_event.m_awaiter = handle;
                    state_kind old = state_kind::notset;
                    return m_event.m_state.compare_exchange_strong(
                        old, state_kind::waiting,
                        std::memory_order_release,
                        std::memory_order_acquire
                    );
                }

                void await_resume() const noexcept {}
            };

            return awaiter{ *this };
        }
      private:
        std::atomic< state_kind > m_state = state_kind::notset;
        gap::coroutine_handle<> m_awaiter = nullptr;
    };

} // namespace gap::coro

#endif