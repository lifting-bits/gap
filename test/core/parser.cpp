/*
 * Copyright (c) 2021, Trail of Bits, Inc.
 * All rights reserved.
 *
 * This source code is licensed in accordance with the terms specified in
 * the LICENSE file found in the root directory of this source tree.
 */

#include <chrono> // for literals
#include <doctest/doctest.h>
#include <gap/core/parser.hpp>
#include <gap/core/bigint.hpp>
#include <optional>    // for optional
#include <string_view> // for operator""sv

using namespace std::literals; // NOLINT
using namespace gap;           // NOLINT

TEST_SUITE("parser") {
    TEST_CASE("simple") {
        SUBCASE("char parser") {
            auto p = parser::char_parser('+')("+"sv);
            CHECK(p);
            CHECK_EQ(parser::result(p), '+');
        }

        SUBCASE("digit parser") {
            auto p = parser::digit_parser< int >()("7"sv);
            CHECK(p);
            CHECK_EQ(parser::result(p), 7);
        }

        SUBCASE("digit parser - radix") {
            CHECK(parser::digit_parser< int >(2)("0"sv));
            CHECK(parser::digit_parser< int >(2)("1"sv));
            CHECK(!parser::digit_parser< int >(2)("2"sv));
            CHECK(!parser::digit_parser< int >(2)("7"sv));

            CHECK(parser::digit_parser< int >(8)("7"sv));
            CHECK(!parser::digit_parser< int >(8)("8"sv));

            CHECK(parser::digit_parser< int >(16)("8"sv));
            CHECK(parser::digit_parser< int >(16)("F"sv));
            CHECK(!parser::digit_parser< int >(16)("G"sv));

            CHECK(!parser::nonzero_parser< int >(16)("0"sv));
            CHECK(!parser::nonzero_parser< int >(16)("G"sv));
        }

        SUBCASE("letter parser") {
            auto p = parser::letter_parser()("a"sv);
            CHECK(p);
            CHECK_EQ(parser::result(p), 'a');
        }

        SUBCASE("value parser") {
            constexpr auto p = parser::value_parser< int >()("123"sv);
            CHECK(p);
            CHECK_EQ(parser::result(p), 123);
        }
    }

    TEST_CASE("numbers") {
        SUBCASE("unsigned") {
            CHECK(parser::unsigned_number_parser< unsigned >()("123"sv));
            CHECK(!parser::unsigned_number_parser< unsigned >()("-123"sv));
        }

        SUBCASE("signed") {
            CHECK(parser::signed_number_parser< int >()("123"sv));
            CHECK(parser::signed_number_parser< int >()("-123"sv));
        }

        SUBCASE("radix 2") {
            constexpr auto p1 = parser::unsigned_number_parser< unsigned, 2 >();
            {
                auto result = p1("100"sv);
                CHECK(result);
                CHECK_EQ(parser::result(result), 4);
            }

            {
                auto result = p1("110"sv);
                CHECK(result);
                CHECK_EQ(parser::result(result), 6);
            }


            CHECK(!p1("3"sv));
            CHECK(!p1("2"sv));

            constexpr auto p2 = parser::unsigned_number_parser< unsigned >();
            {
                auto result = p2("0b100"sv);
                CHECK(result);
                CHECK_EQ(parser::result(result), 4);
            }

            {
                auto result = p2("0b110"sv);
                CHECK(result);
                CHECK_EQ(parser::result(result), 6);
            }

            {
                auto result = p2("0b0"sv);
                CHECK(result);
                CHECK_EQ(parser::result(result), 0);
            }
        }

        SUBCASE("radix 8") {
            constexpr auto p1 = parser::unsigned_number_parser< unsigned, 8 >();
            {
                auto result = p1("10"sv);
                CHECK(result);
                CHECK_EQ(parser::result(result), 8);
            }

            {
                auto result = p1("110"sv);
                CHECK(result);
                CHECK_EQ(parser::result(result), 72);
            }


            CHECK(!p1("8"sv));
            CHECK(!p1("9"sv));

            constexpr auto p2 = parser::unsigned_number_parser< unsigned >();
            {
                auto result = p2("07"sv);
                CHECK(result);
                CHECK_EQ(parser::result(result), 7);
            }

            {
                auto result = p2("011"sv);
                CHECK(result);
                CHECK_EQ(parser::result(result), 9);
            }

            {
                auto result = p2("00"sv);
                CHECK(result);
                CHECK_EQ(parser::result(result), 0);
            }
        }

        SUBCASE("radix 10") {
            constexpr auto p1 = parser::unsigned_number_parser< unsigned, 10 >();
            {
                auto result = p1("10"sv);
                CHECK(result);
                CHECK_EQ(parser::result(result), 10);
            }

            {
                auto result = p1("110"sv);
                CHECK(result);
                CHECK_EQ(parser::result(result), 110);
            }

            {
                auto result = p1("0"sv);
                CHECK(result);
                CHECK_EQ(parser::result(result), 0);
            }

            CHECK(!p1("A"sv));

            constexpr auto p2 = parser::unsigned_number_parser< unsigned >();
            {
                auto result = p2("15"sv);
                CHECK(result);
                CHECK_EQ(parser::result(result), 15);
            }

            {
                auto result = p2("0"sv);
                CHECK(result);
                CHECK_EQ(parser::result(result), 0);
            }
        }
        SUBCASE("radix 16") {
            constexpr auto p1 = parser::unsigned_number_parser< unsigned, 16 >();
            {
                auto result = p1("10"sv);
                CHECK(result);
                CHECK_EQ(parser::result(result), 16);
            }

            {
                auto result = p1("110"sv);
                CHECK(result);
                CHECK_EQ(parser::result(result), 272);
            }

            {
                auto result = p1("FF"sv);
                CHECK(result);
                CHECK_EQ(parser::result(result), 255);
            }

            CHECK(!p1("G"sv));

            constexpr auto p2 = parser::unsigned_number_parser< unsigned >();
            {
                auto result = p2("0xF"sv);
                CHECK(result);
                CHECK_EQ(parser::result(result), 15);
            }

            {
                auto result = p2("0xF0F"sv);
                CHECK(result);
                CHECK_EQ(parser::result(result), 3855);
            }

            {
                auto result = p2("0x0"sv);
                CHECK(result);
                CHECK_EQ(parser::result(result), 0);
            }
        }
    }

    TEST_CASE("bigint") {
        SUBCASE("radix 2") {
            constexpr auto p1 = parser::bigint_parser< 2 >();
            {
                auto result = p1("100:32"sv);
                CHECK(result);
                CHECK_EQ(parser::result(result).to_string(10), "4");
                CHECK_EQ(parser::result(result).bits, 32);
            }

            {
                auto result = p1("110:32"sv);
                CHECK(result);
                CHECK_EQ(parser::result(result).to_string(10), "6");
                CHECK_EQ(parser::result(result).bits, 32);
            }

            CHECK(!p1("3:32"sv));
            CHECK(!p1("2:32"sv));

            constexpr auto p2 = parser::bigint_parser();
            {
                auto result = p2("0b100:32"sv);
                CHECK(result);
                CHECK_EQ(parser::result(result).to_string(10), "4");
                CHECK_EQ(parser::result(result).bits, 32);
            }

            {
                auto result = p2("0b110:32"sv);
                CHECK(result);
                CHECK_EQ(parser::result(result).to_string(10), "6");
                CHECK_EQ(parser::result(result).bits, 32);
            }

            {
                auto result = p2("0b0:32"sv);
                CHECK(result);
                CHECK_EQ(parser::result(result).to_string(10), "0");
                CHECK_EQ(parser::result(result).bits, 32);
            }
        }

        SUBCASE("radix 8") {
            constexpr auto p1 = parser::bigint_parser< 8 >();
            {
                auto result = p1("10:64"sv);
                CHECK(result);
                CHECK_EQ(parser::result(result).to_string(10), "8");
                CHECK_EQ(parser::result(result).bits, 64);
            }

            {
                auto result = p1("110:64"sv);
                CHECK(result);
                CHECK_EQ(parser::result(result).to_string(10), "72");
                CHECK_EQ(parser::result(result).bits, 64);
            }


            CHECK(!p1("8:64"sv));
            CHECK(!p1("9:64"sv));

            constexpr auto p2 = parser::bigint_parser();
            {
                auto result = p2("07:64"sv);
                CHECK(result);
                CHECK_EQ(parser::result(result).to_string(10), "7");
                CHECK_EQ(parser::result(result).bits, 64);
            }

            {
                auto result = p2("011:64"sv);
                CHECK(result);
                CHECK_EQ(parser::result(result).to_string(10), "9");
                CHECK_EQ(parser::result(result).bits, 64);
            }

            {
                auto result = p2("00:64"sv);
                CHECK(result);
                CHECK_EQ(parser::result(result).to_string(10), "0");
                CHECK_EQ(parser::result(result).bits, 64);
            }
        }

        SUBCASE("radix 10") {
            constexpr auto p1 = parser::bigint_parser< 10 >();
            {
                auto result = p1("10:32"sv);
                CHECK(result);
                CHECK_EQ(parser::result(result).to_string(10), "10");
                CHECK_EQ(parser::result(result).bits, 32);
            }

            {
                auto result = p1("110:32"sv);
                CHECK(result);
                CHECK_EQ(parser::result(result).to_string(10), "110");
                CHECK_EQ(parser::result(result).bits, 32);
            }

            {
                auto result = p1("0:16"sv);
                CHECK(result);
                CHECK_EQ(parser::result(result).to_string(10), "0");
                CHECK_EQ(parser::result(result).bits, 16);
            }

            CHECK(!p1("A"sv));

            constexpr auto p2 = parser::bigint_parser();
            {
                auto result = p2("15:64"sv);
                CHECK(result);
                CHECK_EQ(parser::result(result).to_string(10), "15");
                CHECK_EQ(parser::result(result).bits, 64);
            }

            {
                auto result = p2("0:64"sv);
                CHECK(result);
                CHECK_EQ(parser::result(result).to_string(10), "0");
                CHECK_EQ(parser::result(result).bits, 64);
            }
        }

        SUBCASE("radix 16") {
            constexpr auto p1 = parser::bigint_parser< 16 >();
            {
                auto result = p1("10:64"sv);
                CHECK(result);
                CHECK_EQ(parser::result(result).to_string(10), "16");
                CHECK_EQ(parser::result(result).bits, 64);
            }

            {
                auto result = p1("110:64"sv);
                CHECK(result);
                CHECK_EQ(parser::result(result).to_string(10), "272");
                CHECK_EQ(parser::result(result).bits, 64);
            }

            {
                auto result = p1("FF:64"sv);
                CHECK(result);
                CHECK_EQ(parser::result(result).to_string(10), "255");
                CHECK_EQ(parser::result(result).bits, 64);
            }

            CHECK(!p1("G:64"sv));

            constexpr auto p2 = parser::bigint_parser();
            {
                auto result = p2("0xF:64"sv);
                CHECK(result);
                CHECK_EQ(parser::result(result).to_string(10), "15");
                CHECK_EQ(parser::result(result).bits, 64);
            }

            {
                auto result = p2("0xF0F:64"sv);
                CHECK(result);
                CHECK_EQ(parser::result(result).to_string(10), "3855");
                CHECK_EQ(parser::result(result).bits, 64);
            }

            {
                auto result = p2("0x0:64"sv);
                CHECK(result);
                CHECK_EQ(parser::result(result).to_string(10), "0");
                CHECK_EQ(parser::result(result).bits, 64);
            }
        }
    }
}
