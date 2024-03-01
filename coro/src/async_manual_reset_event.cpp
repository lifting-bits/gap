///////////////////////////////////////////////////////////////////////////////
// Copyright (c) Lewis Baker
// Licenced under MIT license. See LICENSE.txt for details.
///////////////////////////////////////////////////////////////////////////////

#include <gap/coro/async_manual_reset_event.hpp>

#include <gap/core/config.hpp>

#include <cassert>

namespace gap::coro {

    async_manual_reset_event::async_manual_reset_event(bool initially_set) noexcept
        : m_state(initially_set ? static_cast<void*>(this) : nullptr) {}

    async_manual_reset_event::~async_manual_reset_event() noexcept {
        assert(
            m_state.load(std::memory_order_relaxed) == nullptr ||
            m_state.load(std::memory_order_relaxed) == static_cast<void*>(this)
        );
    }

    bool async_manual_reset_event::is_set() const noexcept {
        return m_state.load(std::memory_order_acquire) == static_cast<const void*>(this);
    }

    async_manual_reset_event_operation async_manual_reset_event::operator co_await() const noexcept {
        return async_manual_reset_event_operation{ *this };
    }

    void async_manual_reset_event::set() noexcept {
        void* const set_state = static_cast<void*>(this);

        // Needs 'release' semantics so that prior writes are visible to event awaiters
        // that synchronise either via 'is_set()' or 'operator co_await()'.
        // Needs 'acquire' semantics in case there are any waiters so that we see
        // prior writes to the waiting coroutine's state and to the contents of
        // the queued async_manual_reset_event_operation objects.
        void* old_state = m_state.exchange(set_state, std::memory_order_acq_rel);
        if (old_state != set_state)
        {
            auto* current = static_cast<async_manual_reset_event_operation*>(old_state);
            while (current != nullptr)
            {
                auto* next = current->m_next;
                current->m_awaiter.resume();
                current = next;
            }
        }
    }

    void async_manual_reset_event::reset() noexcept {
        void* old_state = static_cast<void*>(this);
	    m_state.compare_exchange_strong(old_state, nullptr, std::memory_order_relaxed);
    }

    async_manual_reset_event_operation::async_manual_reset_event_operation(
        const async_manual_reset_event& event
    ) noexcept
        : m_event(event)
    {}

    bool async_manual_reset_event_operation::await_ready() const noexcept {
        return m_event.is_set();
    }

    bool async_manual_reset_event_operation::await_suspend(
        gap::coroutine_handle<> awaiter
    ) noexcept {
        m_awaiter = awaiter;

        const void* const set_state = static_cast<const void*>(&m_event);

        void* old_state = m_event.m_state.load(std::memory_order_acquire);
        do
        {
            if (old_state == set_state)
            {
                // State is now 'set' no need to suspend.
                return false;
            }

            m_next = static_cast<async_manual_reset_event_operation*>(old_state);
        } while (!m_event.m_state.compare_exchange_weak(
            old_state,
            static_cast<void*>(this),
            std::memory_order_release,
            std::memory_order_acquire)
        );

        // Successfully queued this waiter to the list.
        return true;
    }

} // namespace gap::coro