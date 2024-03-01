// Copyright (c) 2024, Trail of Bits, Inc.

///////////////////////////////////////////////////////////////////////////////
// Copyright (c) Lewis Baker
// Licenced under MIT license. See LICENSE.txt for details.
///////////////////////////////////////////////////////////////////////////////
// This file is a modified version of cppcoro/on_scope_exit.hpp from the cppcoro
// project. The original file is licenced under the MIT license and the original
// license is included above.
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <type_traits>
#include <exception>

namespace gap
{
	template< typename func_t >
	struct scoped_lambda
	{
		scoped_lambda(func_t&& func)
			: m_func(std::forward<func_t>(func))
			, m_cancelled(false)
		{}

		scoped_lambda(const scoped_lambda& other) = delete;

		scoped_lambda(scoped_lambda&& other)
			: m_func(std::forward<func_t>(other.m_func))
			, m_cancelled(other.m_cancelled)
		{
			other.cancel();
		}

		~scoped_lambda()
		{
			if (!m_cancelled) {
				m_func();
			}
		}

		void cancel() noexcept {
			m_cancelled = true;
		}

		void call_now() noexcept(noexcept(std::declval<func_t>()())) {
			m_cancelled = true;
			m_func();
		}

	private:

		func_t m_func;
		bool m_cancelled;

	};

	/// A scoped lambda that executes the lambda when the object destructs
	/// but only if exiting due to an exception (call_on_failure = true) or
	/// only if not exiting due to an exception (call_on_failure = false).
	template< typename func_t, bool call_on_failure >
	struct conditional_scoped_lambda
	{
		conditional_scoped_lambda(func_t&& func)
			: m_func(std::forward<func_t>(func))
			, m_uncaught_exception_count(std::uncaught_exceptions())
			, m_cancelled(false)
		{}

		conditional_scoped_lambda(const conditional_scoped_lambda& other) = delete;

		conditional_scoped_lambda(conditional_scoped_lambda&& other)
			noexcept(std::is_nothrow_move_constructible_v<func_t>)
			: m_func(std::forward<func_t>(other.m_func))
			, m_uncaught_exception_count(other.m_uncaught_exception_count)
			, m_cancelled(other.m_cancelled)
		{
			other.cancel();
		}

		~conditional_scoped_lambda() noexcept(call_on_failure || noexcept(std::declval<func_t>()()))
		{
			if (!m_cancelled && (is_unwinding_due_to_exception() == call_on_failure)) {
				m_func();
			}
		}

		void cancel() noexcept {
			m_cancelled = true;
		}

	private:

		bool is_unwinding_due_to_exception() const noexcept {
			return std::uncaught_exceptions() > m_uncaught_exception_count;
		}

		func_t m_func;
		int m_uncaught_exception_count;
		bool m_cancelled;

	};

	/// Returns an object that calls the provided func_ttion when it goes out
	/// of scope either normally or due to an uncaught exception unwinding
	/// the stack.
	///
	/// \param func
	/// The function to call when the scope exits.
	/// The function must be noexcept.
	template< typename func_t >
	auto on_scope_exit(func_t&& func) {
		return scoped_lambda<func_t>{ std::forward<func_t>(func) };
	}

	/// Returns an object that calls the provided func_ttion when it goes out
	/// of scope due to an uncaught exception unwinding the stack.
	///
	/// \param func
	/// The function to be called if unwinding due to an exception.
	/// The function must be noexcept.
	template< typename func_t >
	auto on_scope_failure(func_t&& func) {
		return conditional_scoped_lambda<func_t, true>{ std::forward<func_t>(func) };
	}

	/// Returns an object that calls the provided func_ttion when it goes out
	/// of scope via normal execution (ie. not unwinding due to an exception).
	///
	/// \param func
	/// The function to call if the scope exits normally.
	/// The function does not necessarily need to be noexcept.
	template<typename func_t>
	auto on_scope_success(func_t&& func) {
		return conditional_scoped_lambda<func_t, false>{ std::forward<func_t>(func) };
	}

} // namespace gap