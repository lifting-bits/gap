// Copyright (c) 2024, Trail of Bits, Inc.

///////////////////////////////////////////////////////////////////////////////
// Copyright (c) Lewis Baker
// Licenced under MIT license. See LICENSE.txt for details.
///////////////////////////////////////////////////////////////////////////////
// This file is a modified version of cppcoro/recursive_generator.hpp from the
// cppcoro project. The original file is licenced under the MIT license and the
// original license is included above.
///////////////////////////////////////////////////////////////////////////////

#pragma once

#ifdef GAP_ENABLE_COROUTINES

    #include "gap/coro/coroutine.hpp"
    #include "gap/coro/generator.hpp"

    #include <cassert>
    #include <concepts>
    #include <cstddef>
    #include <exception>
    #include <iterator>
    #include <type_traits>
    #include <utility>

namespace gap
{
    template< typename T >
    struct recursive_generator;

    namespace detail
    {
        template< typename T >
        struct recursive_generator_promise_type final {
            using value_type     = std::remove_reference_t< T >;
            using reference_type = std::conditional_t< std::is_reference_v< T >, T, T& >;
            using pointer_type   = std::add_pointer_t< T >;
            using handle_type    = gap::coroutine_handle< recursive_generator_promise_type >;

            recursive_generator_promise_type() noexcept
                : _value(nullptr)
                , _exception(nullptr)
                , _root(this)
                , _parent_or_leaf(this) {}

            recursive_generator_promise_type(const recursive_generator_promise_type&) = delete;
            recursive_generator_promise_type(recursive_generator_promise_type&&)      = delete;

            auto get_return_object() noexcept { return recursive_generator< T >{ *this }; }

            gap::suspend_always initial_suspend() const noexcept { return {}; }
            gap::suspend_always final_suspend() const noexcept { return {}; }

            void unhandled_exception() noexcept { _exception = std::current_exception(); }

            void return_void() noexcept {}

            gap::suspend_always yield_value(std::remove_reference_t< T >& value) noexcept {
                _value = std::addressof(value);
                return {};
            }

            gap::suspend_always yield_value(std::remove_reference_t< T >&& value) noexcept {
                _value = std::addressof(value);
                return {};
            }

            auto yield_value(recursive_generator< T >&& generator) noexcept {
                return yield_value(generator);
            }

            auto yield_value(recursive_generator< T >& generator) noexcept {
                struct awaitable {
                    explicit awaitable(recursive_generator_promise_type* child_promise)
                        : _child_promise(child_promise) {}

                    bool await_ready() noexcept { return this->_child_promise == nullptr; }

                    void await_suspend(handle_type) noexcept {}

                    void await_resume() {
                        if (this->_child_promise != nullptr) {
                            this->_child_promise->rethrow_if_exception();
                        }
                    }

                  private:
                    recursive_generator_promise_type* _child_promise;
                };

                if (generator._promise != nullptr) {
                    _root->_parent_or_leaf              = generator._promise;
                    generator._promise->_root           = _root;
                    generator._promise->_parent_or_leaf = this;
                    generator._promise->resume();

                    if (!generator._promise->is_complete()) {
                        return awaitable{ generator._promise };
                    }

                    _root->_parent_or_leaf = this;
                }

                return awaitable{ nullptr };
            }

            // Don't allow any use of 'co_await' inside the recursive_generator coroutine.
            template< typename U >
            gap::suspend_never await_transform(U&& value) = delete;

            void destroy() noexcept { handle_type::from_promise(*this).destroy(); }

            void rethrow_if_exception() {
                if (_exception) {
                    std::rethrow_exception(_exception);
                }
            }

            bool is_complete() noexcept { return handle_type::from_promise(*this).done(); }

            reference_type value() noexcept {
                assert(this == _root);
                assert(!is_complete());
                return *(_parent_or_leaf->_value);
            }

            void pull() noexcept {
                assert(this == _root);
                assert(!_parent_or_leaf->is_complete());

                _parent_or_leaf->resume();

                while (_parent_or_leaf != this && _parent_or_leaf->is_complete()) {
                    _parent_or_leaf = _parent_or_leaf->_parent_or_leaf;
                    _parent_or_leaf->resume();
                }
            }

          private:
            void resume() noexcept { handle_type::from_promise(*this).resume(); }

            pointer_type _value;
            std::exception_ptr _exception;

            recursive_generator_promise_type* _root;

            // If this is the promise of the root generator then this field
            // is a pointer to the leaf promise.
            // For non-root generators this is a pointer to the parent promise.
            recursive_generator_promise_type* _parent_or_leaf;
        };
    } // namespace detail

    template< typename T >
    struct [[nodiscard]] recursive_generator {
        using promise_type = detail::recursive_generator_promise_type< T >;

        recursive_generator() noexcept
            : _promise(nullptr) {}

        explicit recursive_generator(promise_type& promise) noexcept
            : _promise(&promise) {}

        recursive_generator(recursive_generator&& other) noexcept
            : _promise(std::move(other._promise)) {
            other._promise = nullptr;
        }

        recursive_generator(const recursive_generator& other)            = delete;
        recursive_generator& operator=(const recursive_generator& other) = delete;

        ~recursive_generator() {
            if (_promise != nullptr) {
                _promise->destroy();
            }
        }

        recursive_generator& operator=(recursive_generator&& other) noexcept {
            if (this != &other) {
                if (_promise != nullptr) {
                    _promise->destroy();
                }

                _promise       = std::move(other._promise);
                other._promise = nullptr;
            }

            return *this;
        }

        struct iterator {
            using iterator_category = std::input_iterator_tag;
            using difference_type   = std::ptrdiff_t;
            using value_type        = typename promise_type::value_type;
            using reference         = typename promise_type::reference_type;
            using pointer           = typename promise_type::pointer_type;

            iterator() noexcept
                : _promise(nullptr) {}

            explicit iterator(promise_type* promise) noexcept
                : _promise(promise) {}

            bool operator==(const iterator& other) const noexcept {
                return _promise == other._promise;
            }

            bool operator!=(const iterator& other) const noexcept {
                return _promise != other._promise;
            }

            iterator& operator++() {
                assert(_promise != nullptr);
                assert(!_promise->is_complete());

                _promise->pull();
                if (_promise->is_complete()) {
                    auto* temp = _promise;
                    _promise   = nullptr;
                    temp->rethrow_if_exception();
                }

                return *this;
            }

            void operator++(int) { (void) operator++(); }

            reference operator*() const noexcept {
                assert(_promise != nullptr);
                return static_cast< reference >(_promise->value());
            }

            pointer operator->() const noexcept { return std::addressof(operator*()); }

          private:
            promise_type* _promise;
        };

        iterator begin() {
            if (_promise != nullptr) {
                _promise->pull();
                if (!_promise->is_complete()) {
                    return iterator(_promise);
                }

                _promise->rethrow_if_exception();
            }

            return iterator(nullptr);
        }

        iterator end() noexcept { return iterator(nullptr); }

        void swap(recursive_generator& other) noexcept { std::swap(_promise, other._promise); }

      private:
        friend promise_type;

        promise_type* _promise;
    };

    template< typename T >
    void swap(recursive_generator< T >& a, recursive_generator< T >& b) noexcept {
        a.swap(b);
    }

} // namespace gap

#endif