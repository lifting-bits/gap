// Copyright (c) 2024, Trail of Bits, Inc.

///////////////////////////////////////////////////////////////////////////////
// Copyright (c) Lewis Baker
// Licenced under MIT license. See LICENSE.txt for details.
///////////////////////////////////////////////////////////////////////////////
// This file is a modified version of cppcoro/async_manual_reset_event.hpp from
// the cppcoro project. The original file is licenced under the MIT license and
// the original license is included above.
///////////////////////////////////////////////////////////////////////////////

#pragma once

#ifdef GAP_ENABLE_COROUTINES

    #include <gap/coro/coroutine.hpp>

    #include <stdexcept>
    #include <atomic>

namespace gap::coro
{
    struct async_manual_reset_event_operation;

    struct async_manual_reset_event
    {
        async_manual_reset_event(bool initially_set = false) noexcept;

        ~async_manual_reset_event() noexcept;

        async_manual_reset_event_operation operator co_await() const noexcept;

        bool is_set() const noexcept;

    	void set() noexcept;

        void reset() noexcept;
      private:
        friend struct async_manual_reset_event_operation;

        // This variable has 3 states:
		// - this    - The state is 'set'.
		// - nullptr - The state is 'not set' with no waiters.
		// - other   - The state is 'not set'.
		//             Points to an 'async_manual_reset_event_operation' that is
		//             the head of a linked-list of waiters.
		mutable std::atomic<void*> m_state;
    };

    struct async_manual_reset_event_operation
    {
        explicit async_manual_reset_event_operation(const async_manual_reset_event& event) noexcept;

        bool await_ready() const noexcept;
		bool await_suspend(gap::coroutine_handle<> awaiter) noexcept;
		void await_resume() const noexcept {}

      private:
        friend struct async_manual_reset_event;

        const async_manual_reset_event& m_event;
        async_manual_reset_event_operation* m_next;
        gap::coroutine_handle<> m_awaiter;
    };

} // namespace gap::coro

#endif