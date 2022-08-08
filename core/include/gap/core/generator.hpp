// Copyright (c) 2021-present, Trail of Bits, Inc.

#pragma once

#ifdef GAP_ENABLE_COROUTINES

    #include "gap/core/coroutine.hpp"

    #include <concepts>
    #include <cstddef>
    #include <exception>
    #include <iterator>
    #include <type_traits>
    #include <utility>

namespace gap
{
    template< typename T >
    struct generator;

    namespace detail
    {
        template< typename T >
        struct generator_promise_type {
            using value_type     = std::remove_reference_t< T >;
            using reference_type = std::conditional_t< std::is_reference_v< T >, T, T& >;
            using pointer_type   = value_type*;

            generator_promise_type() = default;

            generator< T > get_return_object() noexcept;

            constexpr gap::suspend_always initial_suspend() const noexcept { return {}; }
            constexpr gap::suspend_always final_suspend() const noexcept { return {}; }

            gap::suspend_always yield_value(std::remove_reference_t< T >& value) noexcept {
                _value = std::addressof(value);
                return {};
            }

            gap::suspend_always yield_value(std::remove_reference_t< T >&& value) noexcept {
                _value = std::addressof(value);
                return {};
            }

            void unhandled_exception() { _exception = std::current_exception(); }

            void return_void() {}

            reference_type value() const noexcept { return static_cast< reference_type >(*_value); }

            // Don't allow any use of 'co_await' inside the generator coroutine.
            template< typename U >
            gap::suspend_never await_transform(U&& value) = delete;

            void rethrow_if_exception() {
                if (_exception) {
                    std::rethrow_exception(_exception);
                }
            }

          private:
            pointer_type _value;
            std::exception_ptr _exception;
        };

        template< typename T >
        using promise_type = detail::generator_promise_type< T >;

        template< typename T >
        using coroutine_handle = gap::coroutine_handle< promise_type< T > >;

        struct generator_sentinel {};

        template< typename T >
        struct generator_iterator {
            using iterator_category = std::input_iterator_tag;
            using difference_type   = std::ptrdiff_t;
            using value_type        = typename promise_type< T >::value_type;
            using reference         = typename promise_type< T >::reference_type;
            using pointer           = typename promise_type< T >::pointer_type;

            generator_iterator() noexcept = default;

            explicit generator_iterator(coroutine_handle< T > coroutine) noexcept
                : _coroutine(coroutine) {}

            friend bool operator==(const generator_iterator& it, generator_sentinel) noexcept {
                return !it._coroutine || it._coroutine.done();
            }

            friend bool operator==(generator_sentinel s, const generator_iterator& it) noexcept {
                return (it == s);
            }

            friend bool operator!=(const generator_iterator& it, generator_sentinel s) noexcept {
                return !(it == s);
            }

            friend bool operator!=(generator_sentinel s, const generator_iterator& it) noexcept {
                return it != s;
            }

            generator_iterator& operator++() {
                _coroutine.resume();
                if (_coroutine.done()) {
                    _coroutine.promise().rethrow_if_exception();
                }

                return *this;
            }

            void operator++(int) { (void) operator++(); }

            reference operator*() const noexcept { return _coroutine.promise().value(); }

            pointer operator->() const noexcept { return std::addressof(operator*()); }

          private:
            coroutine_handle< T > _coroutine = nullptr;
        };

    } // namespace detail

    template< typename T >
    struct [[nodiscard]] generator {
        using iterator         = detail::generator_iterator< T >;
        using promise_type     = detail::promise_type< T >;
        using coroutine_handle = detail::coroutine_handle< T >;

        using value_type       = typename promise_type::reference_type;

        generator(generator&& other) noexcept
            : _coroutine(other._coroutine) {
            other._coroutine = nullptr;
        }

        generator(const generator& other) = delete;

        ~generator() {
            if (_coroutine) {
                _coroutine.destroy();
            }
        }

        generator& operator=(generator other) noexcept {
            swap(other);
            return *this;
        }

        iterator begin() {
            if (_coroutine) {
                _coroutine.resume();
                if (_coroutine.done()) {
                    _coroutine.promise().rethrow_if_exception();
                }
            }

            return iterator{ _coroutine };
        }

        detail::generator_sentinel end() noexcept { return {}; }

        void swap(generator& other) noexcept { std::swap(_coroutine, other._coroutine); }

      private:
        friend struct detail::generator_promise_type< T >;

        explicit generator(coroutine_handle coroutine)
            : _coroutine(coroutine) {}

        coroutine_handle _coroutine = nullptr;
    };

    namespace detail
    {
        template< typename T >
        generator< T > generator_promise_type< T >::get_return_object() noexcept {
            using coroutine_handle = detail::coroutine_handle< T >;
            return generator< T >{ coroutine_handle::from_promise(*this) };
        }
    } // namespace detail

} // namespace gap

#endif
