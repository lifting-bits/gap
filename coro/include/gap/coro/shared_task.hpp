// Copyright (c) 2024, Trail of Bits, Inc.

///////////////////////////////////////////////////////////////////////////////
// Copyright (c) Lewis Baker
// Licenced under MIT license. See LICENSE.txt for details.
///////////////////////////////////////////////////////////////////////////////
// This file is a modified version of gap/shared_task.hpp from the gap
// project. The original file is licenced under the MIT license and the original
// license is included above.
///////////////////////////////////////////////////////////////////////////////

#pragma once

#ifdef GAP_ENABLE_COROUTINES

    #include <gap/core/config.hpp>
    #include <gap/core/type_traits.hpp>
    #include <gap/coro/coroutine.hpp>
    #include <gap/coro/awaitable_traits.hpp>
    #include <gap/coro/broken_promise.hpp>
    #include <gap/coro/task.hpp>

    #include <atomic>
    #include <exception>
    #include <utility>
    #include <type_traits>

namespace gap::coro
{
    template< typename T >
    struct shared_task;

    namespace detail {

        struct shared_task_waiter {
            gap::coroutine_handle<> m_continuation;
            shared_task_waiter* m_next;
        };

        struct shared_task_promise_base {
            friend struct final_awaiter;

            struct final_awaiter {

                bool await_ready() const noexcept {
                    return false;
                }

                template< typename promise_t >
                void await_suspend(gap::coroutine_handle< promise_t > handle) noexcept {
                    shared_task_promise_base& promise = handle.promise();

                    // Exchange operation needs to be 'release' so that subsequent awaiters have
					// visibility of the result. Also needs to be 'acquire' so we have visibility
					// of writes to the waiters list.
					void* const value_ready_value = &promise;
					void* waiters = promise.m_waiters.exchange(value_ready_value, std::memory_order_acq_rel);
					if (waiters != nullptr)
					{
						shared_task_waiter* waiter = static_cast<shared_task_waiter*>(waiters);
						while (waiter->m_next != nullptr)
						{
							// Read the m_next pointer before resuming the coroutine
							// since resuming the coroutine may destroy the shared_task_waiter value.
							auto* next = waiter->m_next;
							waiter->m_continuation.resume();
							waiter = next;
						}

						// Resume last waiter in tail position to allow it to potentially
						// be compiled as a tail-call.
						waiter->m_continuation.resume();
					}
                }

                void await_resume() noexcept {}
            };

            shared_task_promise_base() noexcept
                : m_ref_count(1)
                , m_waiters(&this->m_waiters)
                , m_exception(nullptr)
            {}

            gap::suspend_always initial_suspend() noexcept {
                return {};
            }

            final_awaiter final_suspend() noexcept {
                return {};
            }

            void unhandled_exception() noexcept {
                m_exception = std::current_exception();
            }

            bool is_ready() const noexcept {
                const void* const value_ready_value = this;
                return m_waiters.load(std::memory_order_acquire) == value_ready_value;
            }

            void add_ref() noexcept {
                m_ref_count.fetch_add(1, std::memory_order_relaxed);
            }

            /// Decrement the reference count.
            ///
            /// \return
            /// true if successfully detached, false if this was the last
            /// reference to the coroutine, in which case the caller must
            /// call destroy() on the coroutine handle.
            bool try_detach() noexcept {
                return m_ref_count.fetch_sub(1, std::memory_order_acq_rel) != 1;
            }

            /// Try to enqueue a waiter to the list of waiters.
            ///
            /// \param waiter
            /// Pointer to the state from the waiter object.
            /// Must have waiter->m_coroutine member populated with the coroutine
            /// handle of the awaiting coroutine.
            ///
            /// \param coroutine
            /// Coroutine handle for this promise object.
            ///
            /// \return
            /// true if the waiter was successfully queued, in which case
            /// waiter->m_coroutine will be resumed when the task completes.
            /// false if the coroutine was already completed and the awaiting
            /// coroutine can continue without suspending.
            bool try_await(shared_task_waiter* waiter, gap::coroutine_handle<> coroutine) {
                void* const value_ready_value = this;
                void* const not_started_value = &this->m_waiters;
                constexpr void* started_no_waiters_value = static_cast<shared_task_waiter*>(nullptr);

                // NOTE: If the coroutine is not yet started then the first waiter
                // will start the coroutine before enqueuing itself up to the list
                // of suspended waiters waiting for completion. We split this into
                // two steps to allow the first awaiter to return without suspending.
                // This avoids recursively resuming the first waiter inside the call to
                // coroutine.resume() in the case that the coroutine completes
                // synchronously, which could otherwise lead to stack-overflow if
                // the awaiting coroutine awaited many synchronously-completing
                // tasks in a row.

                // Start the coroutine if not already started.
                void* old_waiters = m_waiters.load(std::memory_order_acquire);
                if (old_waiters == not_started_value &&
                    m_waiters.compare_exchange_strong(
                    old_waiters,
                    started_no_waiters_value,
                    std::memory_order_relaxed))
                {
                    // Start the task executing.
                    coroutine.resume();
                    old_waiters = m_waiters.load(std::memory_order_acquire);
                }

                // Enqueue the waiter into the list of waiting coroutines.
                do
                {
                    if (old_waiters == value_ready_value)
                    {
                        // Coroutine already completed, don't suspend.
                        return false;
                    }

                    waiter->m_next = static_cast<shared_task_waiter*>(old_waiters);
                } while (!m_waiters.compare_exchange_weak(
                    old_waiters,
                    static_cast<void*>(waiter),
                    std::memory_order_release,
                    std::memory_order_acquire)
                );

                return true;
            }

            protected:

            bool completed_with_unhandled_exception() {
                return m_exception != nullptr;
            }

            void rethrow_if_unhandled_exception() {
                if (m_exception != nullptr) {
                    std::rethrow_exception(m_exception);
                }
            }

            private:
            std::atomic< std::uint32_t > m_ref_count;
            // Value is either
            // - nullptr          - indicates started, no waiters
            // - this             - indicates value is ready
            // - &this->m_waiters - indicates coroutine not started
            // - other            - pointer to head item in linked-list of waiters.
            //                      values are of type 'gap::shared_task_waiter'.
            //                      indicates that the coroutine has been started.
            std::atomic< void* > m_waiters;

            std::exception_ptr m_exception;
        };

        template< typename T >
        struct shared_task_promise : shared_task_promise_base {
            shared_task_promise() noexcept = default;

            ~shared_task_promise() {
                if (this->is_ready() && !this->completed_with_unhandled_exception()) {
                    reinterpret_cast< T* >(m_value_storage)->~T();
                }
            }

            shared_task< T > get_return_object() noexcept;

            template< typename value_t >
            requires std::is_convertible_v< value_t&&, T >
            void return_value(value_t&& value)
            noexcept(std::is_nothrow_constructible_v< T, value_t&& >) {
                new (&m_value_storage) T(std::forward< value_t >(value));
            }

            T& result() {
                this->rethrow_if_unhandled_exception();
                return *reinterpret_cast< T* >(m_value_storage);
            }

          private:
            // Not using std::aligned_storage here due to bug in MSVC 2015 Update 2
			// that means it doesn't work for types with alignof(T) > 8.
			// See MS-Connect bug #2658635.
			alignas(T) char m_value_storage[sizeof(T)];
        };

        template<>
        struct shared_task_promise< void > : shared_task_promise_base {
            shared_task_promise() noexcept = default;

            shared_task< void > get_return_object() noexcept;

            void return_void() noexcept {
                // no-op
            }

            void result() {
                this->rethrow_if_unhandled_exception();
            }
        };

        template< typename T >
        struct shared_task_promise< T& > : shared_task_promise_base {
            shared_task_promise() noexcept = default;

            shared_task< T& > get_return_object() noexcept;

            void return_value(T& value) noexcept {
                m_value = std::addressof(value);
            }

            T& result() {
                this->rethrow_if_unhandled_exception();
                return *m_value;
            }

          private:
            T* m_value;
        };
    } // namespace detail

    template< typename T = void >
    struct [[nodiscard]] shared_task
    {
        using promise_type = detail::shared_task_promise< T >;
        using value_type = T;

      private:
        struct awaitable_base
        {
            gap::coroutine_handle< promise_type > m_coroutine;
            detail::shared_task_waiter m_waiter;

            awaitable_base(gap::coroutine_handle< promise_type > coroutine) noexcept
                : m_coroutine(coroutine)
            {}

            bool await_ready() const noexcept {
                return !m_coroutine || m_coroutine.promise().is_ready();
            }

            bool await_suspend(gap::coroutine_handle<> awaiter) noexcept {
                m_waiter.m_continuation = awaiter;
                return m_coroutine.promise().try_await(&m_waiter, m_coroutine);
            }
        };

      public:

        shared_task() noexcept = default;

        explicit shared_task(gap::coroutine_handle< promise_type > coroutine) noexcept
            : m_coroutine(coroutine)
        {
            // Don't increment the ref-count here since it has already been
			// initialised to 2 (one for shared_task and one for coroutine)
			// in the shared_task_promise constructor.
        }

        shared_task(shared_task&& other) noexcept
            : m_coroutine(other.m_coroutine)
        {
            other.m_coroutine = nullptr;
        }

        shared_task(const shared_task& other) noexcept
            : m_coroutine(other.m_coroutine)
        {
            if (m_coroutine) {
                m_coroutine.promise().add_ref();
            }
        }

        ~shared_task() { destroy(); }

        shared_task& operator=(shared_task&& other) noexcept {
            if (this != &other) {
                destroy();
                m_coroutine = other.m_coroutine;
                other.m_coroutine = nullptr;
            }

            return *this;
        }

        shared_task& operator=(const shared_task& other) noexcept {
            if (m_coroutine != other.m_coroutine) {
                destroy();
                m_coroutine = other.m_coroutine;
                if (m_coroutine) {
                    m_coroutine.promise().add_ref();
                }
            }

            return *this;
        }

        void swap(shared_task& other) noexcept {
            std::swap(m_coroutine, other.m_coroutine);
        }

        /// \brief
		/// Query if the task result is complete.
		///
		/// Awaiting a task that is ready will not block.
		bool is_ready() const noexcept {
			return !m_coroutine || m_coroutine.promise().is_ready();
		}

        auto operator co_await() const & noexcept {
            struct awaitable : awaitable_base {
                using awaitable_base::awaitable_base;

                decltype(auto) await_resume() {
                    if (!this->m_coroutine) {
                        throw gap::coro::broken_promise{};
                    }

                    return this->m_coroutine.promise().result();
                }
            };

            return awaitable{ m_coroutine };
        }

        /// \brief
		/// Returns an awaitable that will await completion of the task without
		/// attempting to retrieve the result.
		auto when_ready() const noexcept {
			struct awaitable : awaitable_base
			{
				using awaitable_base::awaitable_base;

				void await_resume() const noexcept {}
			};

			return awaitable{ m_coroutine };
		}

      private:

        template< typename U >
		friend bool operator==(const shared_task<U>&, const shared_task<U>&) noexcept;


        void destroy() {
            if (m_coroutine) {
                if (!m_coroutine.promise().try_detach()) {
                    m_coroutine.destroy();
                }
            }
        }

        gap::coroutine_handle< promise_type > m_coroutine = nullptr;
    };

    template< typename T >
	bool operator==(const shared_task<T>& lhs, const shared_task<T>& rhs) noexcept {
		return lhs.m_coroutine == rhs.m_coroutine;
	}

	template< typename T >
	bool operator!=(const shared_task<T>& lhs, const shared_task<T>& rhs) noexcept {
		return !(lhs == rhs);
	}

    template<typename T>
	void swap(shared_task<T>& a, shared_task<T>& b) noexcept {
		a.swap(b);
	}

    namespace detail {

        template< typename T >
        shared_task<T> shared_task_promise<T>::get_return_object() noexcept
		{
			return shared_task<T>{
				gap::coroutine_handle<shared_task_promise>::from_promise(*this)
			};
		}

		template< typename T >
		shared_task<T&> shared_task_promise<T&>::get_return_object() noexcept
		{
			return shared_task<T&>{
				gap::coroutine_handle<shared_task_promise>::from_promise(*this)
			};
		}

		inline shared_task<void> shared_task_promise<void>::get_return_object() noexcept
		{
			return shared_task<void>{
				gap::coroutine_handle<shared_task_promise>::from_promise(*this)
			};
		}

    } // namespace detail

    template< awaitable awaitable_t >
    auto make_shared_task(awaitable_t&& awaitable)
        -> shared_task< std::remove_reference_t< await_result_t< awaitable_t > > >
    {
        co_return co_await static_cast< awaitable_t&& >(awaitable);
    }

} // namespace gap::coro

#endif