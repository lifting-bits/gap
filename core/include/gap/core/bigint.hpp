// Copyright (c) 2022-present, Trail of Bits, Inc.

#pragma once

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <gap/core/concepts.hpp>
#include <vector>
#include <limits>
#include <span>
#include <string>
#include <utility>

namespace gap
{

    //
    // This class is a compatible tiny llvm::APInt port.
    // It allows for efficient storage and formating of
    // unsigned bitvectors of dynamic size.
    //
    // This representation does not support arithmetic, yet.
    //
    struct [[nodiscard]] bigint {
        using word_type = std::uint64_t;
        using half_type = std::uint32_t;

        explicit constexpr bigint()
            : bits(bits_per_word())
        {
            storage.value = 0;
        }

        explicit constexpr bigint(unsigned num_of_bits)
            : bigint(num_of_bits, 0u)
        {}

        constexpr bigint(unsigned num_of_bits, const bigint &other)
            : bigint(num_of_bits, other.as_span())
        {}

        constexpr bigint(unsigned num_of_bits, gap::unsigned_integral auto value)
            : bits(num_of_bits)
        {
            if (is_single_word()) {
                storage.value = word_type(value);
            } else {
                initialize_multiword(value);
            }

            clear_unused_bits();
        }

        constexpr bigint(unsigned num_of_bits, std::span< const word_type > buff)
            : bits(num_of_bits)
        {
            if (is_single_word()) {
                storage.value = buff[0];
            } else {
                storage.buffer = new word_type[get_num_words()]();

                auto words = std::min(buff.size(), std::size_t(get_num_words()));
                std::copy_n(buff.begin(), words, storage.buffer);
            }

            clear_unused_bits();
        }

        constexpr bigint(unsigned num_of_bits, std::string_view str, std::uint8_t radix)
            : bits(num_of_bits)
        {
            assert(!str.empty() && "invalid string");
            assert((radix == 10 || radix == 8 || radix == 16 || radix == 2 || radix == 36) && "unsupported radix");
            assert(str.front() != '-' && "unsupported negative numbers");

            if (is_single_word()) {
                storage.value = 0;
            } else {
                initialize_multiword(0u);
            }

            // Figure out if we can shift instead of multiply
            unsigned shift = (radix == 16 ? 4 : radix == 8 ? 3 : radix == 2 ? 1 : 0);
            for (auto c : str) {
                auto digit = get_digit(c, radix);
                assert(digit < radix && "invalid digit for radix");

                // Shift or multiply the value by the radix
                if (str.size() > 1) {
                    if (shift) {
                        *this <<= shift;
                    } else {
                        *this *= radix;
                    }
                }

                // Add in the digit we just interpreted
                *this += digit;
            }
        }

        constexpr bigint(const bigint &other)
            : bigint(other.bits, other.as_span())
        {}

        constexpr bigint(bigint &&other)
            : bits(other.bits), storage(other.storage)
        {}

        constexpr bigint &operator=(const bigint &other) {
            if (is_single_word() && other.is_single_word()) {
                storage.value = other.storage.value;
                bits = other.bits;
                return *this;
            }

            return copy_assign_multiword(other);
        }

        constexpr bigint &operator=(bigint &&other) {
            if (this == &other) {
                return *this;
            }

            if (!is_single_word()) {
                delete storage.buffer;
            }

            bits = other.bits;
            storage = other.storage;

            return *this;
        }

        constexpr ~bigint() {
            if (!is_single_word()) {
                delete[] storage.buffer;
            }
        }

        void clear() {
            bits = 0;
            storage.value = 0;
        }

        static constexpr unsigned get_digit(char c, std::uint8_t radix) {
            auto digit = unsigned(c);
            if (radix == 16 || radix == 36) {
                if (unsigned r = digit - '0'; r <= 9)
                    return r;
                if (unsigned r = digit - 'A'; r <= radix - 11U)
                    return r + 10;
                if (unsigned r = digit - 'a'; r <= radix - 11U)
                    return r + 10;
                radix = 10;
            }

            if (unsigned r = digit - '0'; r < radix)
                return r;
            return -1U;
        }

        template< gap::unsigned_integral value_type >
        constexpr void initialize_multiword(value_type value) {
            storage.buffer    = new word_type[get_num_words()]();
            storage.buffer[0] = word_type(value);
        }

        constexpr void initialize_multiword(const bigint &other) {
            storage.buffer = new word_type[get_num_words()];
            std::copy_n(other.storage.buffer, get_num_words(), storage.buffer);
        }

        constexpr bigint &copy_assign_multiword(const bigint &other) {
            if (this == &other)
                return *this;

            // Adjust the bit width and handle allocations as necessary.
            reallocate(other.bits);

            if (is_single_word()) {
                storage.value = other.storage.value;
            } else {
                auto buff = other.as_span();
                std::copy(buff.begin(), buff.end(), storage.buffer);
            }

            return *this;
        }

        constexpr void reallocate(unsigned new_bitwidth) {
            if (get_num_words() == get_num_words(new_bitwidth)) {
                bits = new_bitwidth;
                return;
            }

            if (!is_single_word())
                delete [] storage.buffer;

            bits = new_bitwidth;

            if (!is_single_word()) {
                storage.buffer = new word_type[get_num_words()];
            }
        }

        static constexpr unsigned bits_per_word() { return sizeof(word_type) * 8; }

        constexpr unsigned last_word_bits() const {
            return ((bits - 1) % bits_per_word()) + 1;
        }

        constexpr unsigned bits_per_word(unsigned index) const {
            if (index == get_num_words() - 1)
                return last_word_bits();
            return bits_per_word();
        }

        constexpr bool is_single_word() const { return bits <= bits_per_word(); }

        static constexpr unsigned get_num_words(unsigned bw) {
            return (bw + bits_per_word() - 1) / bits_per_word();
        }

        constexpr unsigned get_num_words() const { return get_num_words(bits); }

        constexpr word_type &last_word() {
            if (is_single_word())
                return storage.value;
            return storage.buffer[get_num_words() - 1];
        }

        constexpr bigint &clear_unused_bits() {
            const auto mask
                = std::numeric_limits< word_type >::max() >> (bits_per_word() - last_word_bits());
            last_word() &= mask;
            return *this;
        }

        constexpr bool operator==(const bigint &other) const {
            if (bits != other.bits)
                return false;
            if (is_single_word())
                return storage.value == other.storage.value;
            return std::equal(
                storage.buffer, storage.buffer + get_num_words(), other.storage.buffer);
        }

        constexpr bool ult(word_type other) {
            return (is_single_word() || active_bits() <= 64) && first_word() < other;
        }

        constexpr bool operator!() const { return is_zero(); }

        constexpr bool is_zero() const {
            if (is_single_word())
                return storage.value == 0;
            return count_leading_zeros() == bits;
        }

        constexpr operator bool() const { return !is_zero(); }

        static constexpr unsigned count_leading_zeros(unsigned bits, word_type word) {
            if (!word)
                return bits;

            unsigned count = 0;
            for (unsigned shift = bits_per_word() >> 1; shift; shift >>= 1) {
                if (word_type tmp = word >> shift) {
                    word = tmp;
                } else {
                    count |= shift;
                }
            }

            return bits - (bits_per_word() - count);
        }

        constexpr unsigned count_leading_zeros_slow() const {
            unsigned count = 0;
            for (unsigned i = 0; i < get_num_words(); ++i) {
                auto index = get_num_words() - i - 1;
                auto value = storage.buffer[index];
                if (value == 0) {
                    count += bits_per_word(index);
                } else {
                    count += count_leading_zeros(bits_per_word(index), value);
                    break;
                }
            }

            return std::min(count, bits);
        }

        constexpr unsigned count_leading_zeros() const {
            if (is_single_word())
                return count_leading_zeros(bits, storage.value);
            return count_leading_zeros_slow();
        }

        constexpr unsigned active_bits() const {
            return bits - count_leading_zeros();
        }

        constexpr bigint zext(unsigned width) const {
            assert(width >= bits && "invalid zext");

            if (width <= bits_per_word())
                return bigint(width, storage.value);

            if (width == bits)
                return *this;

            return bigint(width, *this);
        }

        constexpr word_type first_word() const {
            if (is_single_word())
                return storage.value;
            assert(active_bits() <= bits_per_word() && "too many active bits");
            return storage.buffer[0];
        }

        constexpr bigint& operator+=(std::uint64_t value) {
            if (is_single_word()) {
                storage.value += value;
            } else {
                add_to_multiword(as_span(), value);
            }

            return clear_unused_bits();
        }

        // returns carry of addition
        static constexpr word_type add_to_multiword(std::span< word_type > words, std::uint64_t value) {
            for (auto &word : words) {
                word += value;
                if (word >= value)
                    return 0;
                value = 1; // carry 1 to next word
            }

            return 1;
        }

        constexpr bigint& operator*=(std::uint64_t value) {
            if (is_single_word()) {
                storage.value *= value;
            } else {
                multiply_multiword(as_span(), value);
            }

            return clear_unused_bits();
        }

        static constexpr inline word_type low_bit_mask(unsigned bw) {
            assert(bw != 0 && bw <= bits_per_word());
            return ~word_type(0) >> (bits_per_word() - bw);
        }

        static constexpr inline word_type low_half(word_type word) {
            return word & low_bit_mask(bits_per_word() / 2);
        }

        static constexpr inline word_type high_half(word_type word) {
            return word >> (bits_per_word() / 2);
        }

        static constexpr void multiply_multiword(std::span< word_type > words, std::uint64_t multiplier) {
            word_type carry = 0;
            for (auto &word : words) {
                word_type src = word;
                word_type low, high;
                if (multiplier == 0 || src == 0) {
                    low  = carry;
                    high = 0;
                } else {
                    low  = low_half(word) * low_half(multiplier);
                    high = high_half(word) * high_half(multiplier);

                    auto multiply_mid = [&] (auto lhs_half, auto rhs_half) {
                        word_type mid = lhs_half * rhs_half;
                        high += high_half(mid);

                        mid <<= bits_per_word() / 2;
                        if (low + mid < low)
                            high++;
                        low += mid;
                    };

                    multiply_mid(low_half(word), high_half(multiplier));
                    multiply_mid(high_half(word), low_half(multiplier));

                    if (low + carry < low)
                        high++;
                    low += carry;
                }

                word  = low;
                carry = high;
            }
        }

        constexpr bigint& operator<<=(unsigned shift) {
            assert(shift <= bits && "invalid shift");
            if (is_single_word()) {
                storage.value <<= shift;
            } else {
                shift_left_multiword(as_span(), shift);
            }
            return clear_unused_bits();
        }

        static constexpr void shift_left_multiword(std::span< word_type > words, unsigned shift) {
            if (!shift)
                return;

            const auto word_shift = std::min(shift / bits_per_word(), unsigned(words.size()));
            const auto bit_shift  = shift % bits_per_word();

            if (bit_shift == 0) {
                // fastpath for moving by whole words
                std::shift_right(words.begin(), words.end(), word_shift);
            } else {
                for (auto i = words.size() - 1; i >= word_shift; --i) {
                    words[i] = words[i - word_shift] << bit_shift;
                    if (i > word_shift) {
                        words[i] |= words[i - word_shift - 1] >> (bits_per_word() - bit_shift);
                    }

                    if (i == 0) break;
                }
            }

            // fill in the remainder zeros
            auto zeros = words.subspan(0, word_shift);
            std::fill(zeros.begin(), zeros.end(), word_type(0));
        }

        constexpr bigint lshr(unsigned shift) const {
            bigint other(*this);
            return other.lshr_inplace(shift);
        }

        constexpr bigint& lshr_inplace(unsigned shift) {
            assert(shift <= bits && "invalid shift");
            if (is_single_word()) {
                storage.value >>= shift;
            } else {
                shift_right_multiword(as_span(), shift);
            }
            return clear_unused_bits();
        }

        static constexpr void shift_right_multiword(std::span< word_type > words, unsigned shift) {
            if (!shift)
                return;

            const auto word_shift = std::min(shift / bits_per_word(), unsigned(words.size()));
            const auto bit_shift  = shift % bits_per_word();

            const auto words_to_move = words.size() - word_shift;

            if (bit_shift == 0) {
                // fastpath for moving by whole words
                std::shift_left(words.begin(), words.end(), int(words_to_move));
            } else {
                for (unsigned i = 0; i < words_to_move; ++i) {
                    words[i] = words[i - word_shift] >> bit_shift;
                    if (i + 1 != words_to_move) {
                        words[i] |= words[i + word_shift + 1] << (bits_per_word() - bit_shift);
                    }
                }
            }

            // fill in the remainder zeros
            auto zeros = words.subspan(words_to_move);
            std::fill(zeros.begin(), zeros.end(), word_type(0));
        }

        static constexpr inline half_type high_half_32(word_type value) {
            return static_cast< half_type >(value >> 32);
        }

        static constexpr inline half_type low_half_32(word_type value) {
            return static_cast< half_type >(value);
        }

        static constexpr inline std::uint64_t combine(std::uint32_t hi, std::uint32_t lo) {
            return (std::uint64_t(hi) << 32) | std::uint64_t(lo);
        }

        constexpr std::pair< bigint, word_type > udivrem(word_type divisor) {
            assert(divisor != 0 && "division by zero");

            if (is_single_word()) {
                auto quot = storage.value / divisor;
                auto rem  = storage.value % divisor;
                return {{ bits, quot }, rem};
            }

            auto words = get_num_words();

            if (words == 0) {
                return {{bits, 0u}, 0};
            }

            if (divisor == 1) {
                return {*this, 0};
            }

            if (this->ult(divisor)) {
                return {{bits, 0u}, first_word()};
            }

            if (*this == divisor) {
                return {{bits, 1u}, 0};
            }

            // TODO the slow division
            return {{bits, 0u}, 0};
        }

        constexpr std::span< const word_type > as_span() const {
            if (is_single_word())
                return std::span(&storage.value, 1);
            return std::span(storage.buffer, get_num_words());
        }

        constexpr std::span< word_type > as_span() {
            if (is_single_word())
                return std::span(&storage.value, 1);
            return std::span(storage.buffer, get_num_words());
        }

        std::string string_prefix(unsigned radix) const {
            switch (radix) {
                case 2:  return "0b";
                case 8:  return "0";
                case 16: return "0x";
                default:
                    return "";
            }
        }

        std::string to_string(unsigned radix, bool with_prefix = true) const {
            assert((radix == 10 || radix == 8 || radix == 16 || radix == 2 || radix == 36) && "unsupported radix");
            auto prefix = with_prefix ? string_prefix(radix) : "";

            if (is_zero()) {
                return prefix + '0';
            }

            constexpr auto digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

            if (is_single_word()) {
                std::string buff;
                auto value = storage.value;
                while (value) {
                    buff += digits[value % radix];
                    value /= radix;
                }

                std::reverse(buff.begin(), buff.end());
                return prefix + buff;
            }

            bigint tmp(*this);
            std::string buff;

            // For the 2, 8 and 16 bit cases, we can just shift instead of divide
            // because the number of bits per digit (1, 3 and 4 respectively) divides
            // equally. We just shift until the value is zero.
            if (radix == 2 || radix == 8 || radix == 16) {
                // Just shift tmp right for each digit width until it becomes zero
                unsigned shift = (radix == 16 ? 4 : (radix == 8 ? 3 : 1));
                unsigned mask = radix - 1;

                while (tmp) {
                    buff += digits[unsigned(*tmp.raw()) & mask];
                    tmp.lshr_inplace(shift);
                }
            } else {
                assert(false && "not implemented");
                // while (tmp) {
                //     auto [res, rem] = tmp.udivrem(radix);
                //     assert(rem < radix && "divide failed");
                //     *(reverse_buff++) = char(digits[rem]);
                //     tmp = res;
                // }
            }

            std::reverse(buff.begin(), buff.end());
            return prefix + buff;
        }

        const word_type *raw() const {
            if (is_single_word())
                return &storage.value;
            return storage.buffer;
        }

        unsigned bits;

        union {
            word_type value;
            word_type *buffer;
        } storage;
    };

} // namespace gap
