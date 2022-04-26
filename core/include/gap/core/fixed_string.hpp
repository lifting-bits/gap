/*
 * Copyright (c) 2021 Trail of Bits, Inc.
 */

#pragma once

#include <algorithm>

namespace gap
{
    // Class 'fixed_string' implements a static string that can
    // be passed as a non type template parameter.

    namespace detail
    {
        template< std::size_t size >
        using const_char_array = const char (&)[size + 1];
    } // namespace detail

    template< std::size_t size >
    struct fixed_string {
        using value_type  = char;
        using container_t = std::array< value_type, size >;

        using reference       = value_type &;
        using const_reference = const value_type &;
        using pointer         = value_type *;
        using const_pointer   = const value_type *;
        using iterator        = typename container_t::iterator;
        using const_iterator  = typename container_t::const_iterator;

        using const_char_array = detail::const_char_array< size >;

        constexpr fixed_string() = default;

        explicit constexpr fixed_string(const_char_array arr) noexcept {
            std::copy(arr, std::next(arr, size), _data.begin());
        }

        constexpr fixed_string(const fixed_string &other) = default;
        constexpr fixed_string(fixed_string &&other)      = default;

        constexpr fixed_string &operator=(const fixed_string &other) = default;
        constexpr fixed_string &operator=(fixed_string &&other) = default;

        constexpr iterator begin() noexcept { return _data.begin(); }
        constexpr const_iterator begin() const noexcept { return _data.begin(); }

        constexpr iterator end() noexcept { return _data.end(); }
        constexpr const_iterator end() const noexcept { return _data.end(); }

        constexpr reference front() noexcept { return _data.front(); }
        constexpr const_reference front() const noexcept { return _data.front(); }

        constexpr reference back() noexcept { return _data.back(); }
        constexpr const_reference back() const noexcept { return _data.back(); }

        constexpr std::size_t size() const noexcept { return _data.size(); }
        constexpr bool empty() const noexcept { return _data.empty(); }

        constexpr bool contains(char c) const noexcept {
            return std::find(begin(), end(), c) != end();
        }

        constexpr reference operator[](std::size_t idx) noexcept { return _data[idx]; }
        constexpr const_reference operator[](std::size_t idx) const noexcept { return _data[idx]; }

        constexpr operator std::basic_string_view< char >() const noexcept {
            return std::basic_string_view< char >{ _data.begin(), _data.size() };
        }

        constexpr const_char_array c_str() const { return _data.data(); }

        template< std::size_t from >
        constexpr auto substr() const noexcept {
            fixed_string< size - from > result{};
            std::copy(std::next(begin(), from), end(), result.begin());
            return result;
        }

        constexpr auto operator<=>(const fixed_string &other) const = default;

        template< typename ostream >
        friend ostream &operator<<(ostream &os, const fixed_string &s) {
            return os << static_cast< std::string_view >(s);
        }

      private:
        container_t _data;
    }

    template< std::size_t N, std::size_t M >
    constexpr auto operator+(const fixed_string< N > &a, const fixed_string< M > &b) {
        fixed_string< N + M > result{};
        std::copy(a.begin(), a.end(), result.begin());
        std::copy(b.begin(), b.end(), std::next(result.begin(), N));
        return result;
    }

    template< std::size_t N, std::size_t M >
    requires(N != M) constexpr bool operator==(
        const fixed_string< N > &a, const fixed_string< M > &b) {
        return false;
    }

    template< std::size_t size >
    fixed_string(detail::const_char_array< size >) -> fixed_string< size - 1 >;

    template< std::size_t size >
    fixed_string(fixed_string< size >) -> fixed_string< size >;

    namespace
    { // compile-time tests
        static inline void tests() {
            static_assert(fixed_string("abc").size() == 3);
            static_assert(fixed_string("abc").back() == 'c');
            static_assert(fixed_string("abc")[1] == 'b');

            static_assert(fixed_string("a") + fixed_string("b") == fixed_string("ab"));
            static_assert(fixed_string("a") != fixed_string("aa"));
        }
    } // namespace

} // namespace gap
