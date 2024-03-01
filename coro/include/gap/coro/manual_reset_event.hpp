// Copyright (c) 2024, Trail of Bits, Inc.

///////////////////////////////////////////////////////////////////////////////
// Copyright (c) Lewis Baker
// Licenced under MIT license. See LICENSE.txt for details.
///////////////////////////////////////////////////////////////////////////////
// This file is a modified version of cppcoro/manual_reset_event.hpp from the
// cppcoro project. The original file is licenced under the MIT license and the
// original license is included above.
///////////////////////////////////////////////////////////////////////////////

#pragma once

#ifdef GAP_ENABLE_COROUTINES

#include <condition_variable>
#include <mutex>

namespace gap::coro
{
    struct manual_reset_event {
        void set() noexcept {
            std::lock_guard lock(m_mutex);
            m_is_set = true;
            m_cv.notify_all();
        }

        void reset() noexcept {
            std::lock_guard lock(m_mutex);
            m_is_set = false;
        }

        void wait() noexcept {
            std::unique_lock lock(m_mutex);
            m_cv.wait(lock, [this] { return m_is_set; });
        }

      private:
        std::mutex m_mutex;
        std::condition_variable m_cv;
        bool m_is_set = false;
    };

} // namespace gap::coro

#endif