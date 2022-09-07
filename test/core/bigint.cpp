// Copyright (c) 2022-present, Trail of Bits, Inc.

#include <array>
#include <doctest/doctest.h>
#include <gap/core/bigint.hpp>
#include <vector>

namespace gap::test
{
    static_assert(bigint(100, 5u) != bigint(50, 5u));
    static_assert(bigint(100, 5u) == bigint(100, 5u));

    static_assert(bigint(30, 0u).get_num_words() == 1);
    static_assert(bigint(30, 0u).bits_per_word() == 64);
    static_assert(bigint(30, 0u).count_leading_zeros() == 30);
    static_assert(bigint(30, 0u).zext(64).count_leading_zeros() == 64);

    static_assert(bigint(30, 1u).get_num_words() == 1);
    static_assert(bigint(30, 1u).bits_per_word() == 64);
    static_assert(bigint(30, 1u).count_leading_zeros() == 29);
    static_assert(bigint(30, 1u).zext(64).count_leading_zeros() == 63);

    static_assert(bigint(100, 0u).get_num_words() == 2);
    static_assert(bigint(100, 0u).bits_per_word() == 64);

TEST_SUITE("bigint") {

    TEST_CASE("value default init") {
        auto value = bigint();
        CHECK(!value);
        CHECK(!value.zext(64));
        CHECK(!value.zext(128));
    }

    TEST_CASE("count leading zeros") {
        auto small_zero = bigint(30, 0u);
        CHECK(small_zero.count_leading_zeros() == 30);
        CHECK(small_zero.zext(64).count_leading_zeros() == 64);
        CHECK(small_zero.zext(128).count_leading_zeros() == 128);
        CHECK(small_zero.zext(300).count_leading_zeros() == 300);

        auto small_one = bigint(30, 1u);
        CHECK(small_one.count_leading_zeros() == 29);
        CHECK(small_one.zext(128).count_leading_zeros() == 127);
        CHECK(small_one.zext(300).count_leading_zeros() == 299);

        auto big_zero = bigint(100, 0u);
        CHECK(big_zero.count_leading_zeros() == 100);
        CHECK(big_zero.zext(128).count_leading_zeros() == 128);
        CHECK(big_zero.zext(300).count_leading_zeros() == 300);

        auto big_one = bigint(100, 1u);
        CHECK(big_one.count_leading_zeros() == 99);
        CHECK(big_one.zext(128).count_leading_zeros() == 127);
        CHECK(big_one.zext(300).count_leading_zeros() == 299);

        auto i61 = bigint(61, 1u << 15);
        CHECK(45u == i61.count_leading_zeros());
        CHECK(16u == i61.active_bits());
        CHECK(static_cast< std::uint64_t >(1 << 15) == i61.first_word());
    }

    TEST_CASE("from string i32") {
        CHECK(bigint(32, 0u) == bigint(32,   "0", 2));
        CHECK(bigint(32, 1u) == bigint(32,   "1", 2));
        CHECK(bigint(32, 2u) == bigint(32,  "10", 2));
        CHECK(bigint(32, 3u) == bigint(32,  "11", 2));
        CHECK(bigint(32, 4u) == bigint(32, "100", 2));

        CHECK(bigint(32,  0u) == bigint(32,  "0", 8));
        CHECK(bigint(32,  1u) == bigint(32,  "1", 8));
        CHECK(bigint(32,  7u) == bigint(32,  "7", 8));
        CHECK(bigint(32,  8u) == bigint(32, "10", 8));
        CHECK(bigint(32, 15u) == bigint(32, "17", 8));
        CHECK(bigint(32, 16u) == bigint(32, "20", 8));

        CHECK(bigint(32,  0u) == bigint(32,  "0", 10));
        CHECK(bigint(32,  1u) == bigint(32,  "1", 10));
        CHECK(bigint(32,  9u) == bigint(32,  "9", 10));
        CHECK(bigint(32, 10u) == bigint(32, "10", 10));
        CHECK(bigint(32, 19u) == bigint(32, "19", 10));
        CHECK(bigint(32, 20u) == bigint(32, "20", 10));

        CHECK(bigint(32,  0u) == bigint(32,  "0", 16));
        CHECK(bigint(32,  1u) == bigint(32,  "1", 16));
        CHECK(bigint(32, 15u) == bigint(32,  "F", 16));
        CHECK(bigint(32, 16u) == bigint(32, "10", 16));
        CHECK(bigint(32, 31u) == bigint(32, "1F", 16));
        CHECK(bigint(32, 32u) == bigint(32, "20", 16));

        CHECK(bigint(32,  0u) == bigint(32,  "0", 36));
        CHECK(bigint(32,  1u) == bigint(32,  "1", 36));
        CHECK(bigint(32, 35u) == bigint(32,  "Z", 36));
        CHECK(bigint(32, 36u) == bigint(32, "10", 36));
        CHECK(bigint(32, 71u) == bigint(32, "1Z", 36));
        CHECK(bigint(32, 72u) == bigint(32, "20", 36));
    }

    TEST_CASE("from string i100") {
        CHECK(bigint(100, 0u) == bigint(100,   "0", 2));
        CHECK(bigint(100, 1u) == bigint(100,   "1", 2));
        CHECK(bigint(100, 2u) == bigint(100,  "10", 2));
        CHECK(bigint(100, 3u) == bigint(100,  "11", 2));
        CHECK(bigint(100, 4u) == bigint(100, "100", 2));

        CHECK(bigint(100,  0u) == bigint(100,  "0", 8));
        CHECK(bigint(100,  1u) == bigint(100,  "1", 8));
        CHECK(bigint(100,  7u) == bigint(100,  "7", 8));
        CHECK(bigint(100,  8u) == bigint(100, "10", 8));
        CHECK(bigint(100, 15u) == bigint(100, "17", 8));
        CHECK(bigint(100, 16u) == bigint(100, "20", 8));

        CHECK(bigint(100,  0u) == bigint(100,  "0", 10));
        CHECK(bigint(100,  1u) == bigint(100,  "1", 10));
        CHECK(bigint(100,  9u) == bigint(100,  "9", 10));
        CHECK(bigint(100, 10u) == bigint(100, "10", 10));
        CHECK(bigint(100, 19u) == bigint(100, "19", 10));
        CHECK(bigint(100, 20u) == bigint(100, "20", 10));

        CHECK(bigint(100,  0u) == bigint(100,  "0", 16));
        CHECK(bigint(100,  1u) == bigint(100,  "1", 16));
        CHECK(bigint(100, 15u) == bigint(100,  "F", 16));
        CHECK(bigint(100, 16u) == bigint(100, "10", 16));
        CHECK(bigint(100, 31u) == bigint(100, "1F", 16));
        CHECK(bigint(100, 32u) == bigint(100, "20", 16));

        CHECK(bigint(100,  0u) == bigint(100,  "0", 36));
        CHECK(bigint(100,  1u) == bigint(100,  "1", 36));
        CHECK(bigint(100, 35u) == bigint(100,  "Z", 36));
        CHECK(bigint(100, 36u) == bigint(100, "10", 36));
        CHECK(bigint(100, 71u) == bigint(100, "1Z", 36));
        CHECK(bigint(100, 72u) == bigint(100, "20", 36));
    }

    TEST_CASE("from string i256") {
        CHECK(bigint(256, 0u) == bigint(256,   "0", 2));
        CHECK(bigint(256, 1u) == bigint(256,   "1", 2));
        CHECK(bigint(256, 2u) == bigint(256,  "10", 2));
        CHECK(bigint(256, 3u) == bigint(256,  "11", 2));
        CHECK(bigint(256, 4u) == bigint(256, "100", 2));

        CHECK(bigint(256,  0u) == bigint(256,  "0", 8));
        CHECK(bigint(256,  1u) == bigint(256,  "1", 8));
        CHECK(bigint(256,  7u) == bigint(256,  "7", 8));
        CHECK(bigint(256,  8u) == bigint(256, "10", 8));
        CHECK(bigint(256, 15u) == bigint(256, "17", 8));
        CHECK(bigint(256, 16u) == bigint(256, "20", 8));

        CHECK(bigint(256,  0u) == bigint(256,  "0", 10));
        CHECK(bigint(256,  1u) == bigint(256,  "1", 10));
        CHECK(bigint(256,  9u) == bigint(256,  "9", 10));
        CHECK(bigint(256, 10u) == bigint(256, "10", 10));
        CHECK(bigint(256, 19u) == bigint(256, "19", 10));
        CHECK(bigint(256, 20u) == bigint(256, "20", 10));

        CHECK(bigint(256,  0u) == bigint(256,  "0", 16));
        CHECK(bigint(256,  1u) == bigint(256,  "1", 16));
        CHECK(bigint(256, 15u) == bigint(256,  "F", 16));
        CHECK(bigint(256, 16u) == bigint(256, "10", 16));
        CHECK(bigint(256, 31u) == bigint(256, "1F", 16));
        CHECK(bigint(256, 32u) == bigint(256, "20", 16));

        CHECK(bigint(256,  0u) == bigint(256,  "0", 36));
        CHECK(bigint(256,  1u) == bigint(256,  "1", 36));
        CHECK(bigint(256, 35u) == bigint(256,  "Z", 36));
        CHECK(bigint(256, 36u) == bigint(256, "10", 36));
        CHECK(bigint(256, 71u) == bigint(256, "1Z", 36));
        CHECK(bigint(256, 72u) == bigint(256, "20", 36));
    }

    TEST_CASE("to string") {
        CHECK(bigint(8, 0u).to_string(2)  == "0b0");
        CHECK(bigint(8, 0u).to_string(8)  == "00");
        CHECK(bigint(8, 0u).to_string(10u) == "0");
        CHECK(bigint(8, 0u).to_string(16) == "0x0");
        CHECK(bigint(8, 0u).to_string(2, false)  == "0");

        CHECK(bigint(8, 255u).to_string(2)  == "0b11111111");
        CHECK(bigint(8, 255u).to_string(8)  == "0377");
        CHECK(bigint(8, 255u).to_string(10u) == "255");
        CHECK(bigint(8, 255u).to_string(16) == "0xFF");
        CHECK(bigint(8, 255u).to_string(36) == "73");

        CHECK(bigint(100, 0u).to_string(2)  == "0b0");
        CHECK(bigint(100, 0u).to_string(8)  == "00");
        CHECK(bigint(100, 0u).to_string(10u) == "0");
        CHECK(bigint(100, 0u).to_string(16) == "0x0");
        CHECK(bigint(100, 0u).to_string(2, false)  == "0");

        CHECK(bigint(100, 255u).to_string(2)  == "0b11111111");
        CHECK(bigint(100, 255u).to_string(8)  == "0377");
        // CHECK(bigint(100, 255u).to_string(10u) == "255");
        CHECK(bigint(100, 255u).to_string(16) == "0xFF");
        // CHECK(bigint(100, 255u).to_string(36) == "73");

        CHECK(bigint(256, 0u).to_string(2)  == "0b0");
        CHECK(bigint(256, 0u).to_string(8)  == "00");
        CHECK(bigint(256, 0u).to_string(10u) == "0");
        CHECK(bigint(256, 0u).to_string(16) == "0x0");
        CHECK(bigint(256, 0u).to_string(2, false)  == "0");

        CHECK(bigint(256, 255u).to_string(2)  == "0b11111111");
        CHECK(bigint(256, 255u).to_string(8)  == "0377");
        // CHECK(bigint(256, 255u).to_string(10u) == "255");
        CHECK(bigint(256, 255u).to_string(16) == "0xFF");
        // CHECK(bigint(256, 255u).to_string(36) == "73");
    }

    TEST_CASE("big string conversions") {
        CHECK(bigint(256, "40000000000000000", 16).to_string(2)
            == "0b1000000000000000000000000000000000000000000000000000000000000000000"
        );

        CHECK(bigint(256, "40000000000000000", 16).to_string(8)
            == "010000000000000000000000"
        );

        // CHECK(bigint(256, "40000000000000000", 16).to_string(10)
        //     == "73786976294838206464"
        // );

        CHECK(bigint(256, "40000000000000000", 16).to_string(16)
            == "0x40000000000000000"
        );
    }

} // testsuite bigint
} // namespace gap::test
