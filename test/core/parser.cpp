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
}
