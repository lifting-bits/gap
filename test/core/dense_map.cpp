// Copyright (c) 2022-present, Trail of Bits, Inc.

#include <doctest/doctest.h>
#include <gap/core/dense_map.hpp>

namespace gap::test
{
    TEST_SUITE("dense map") {
        TEST_CASE("basic") {
            dense_map< unsigned, char > map;

            CHECK(map.full());
            CHECK(map.empty());

            map[3] = 'c';
            map[1] = 'a';

            CHECK(map.contains(1));
            CHECK(map[1] == 'a');

            CHECK(map.contains(3));
            CHECK(map[3] == 'c');

            CHECK(!map.contains(2));

            CHECK(map.size() == 4);

            CHECK(!map.full());

            map[0] = 'd';
            map[2] = 'e';
            CHECK(map.full());
        }

        TEST_CASE("default value") {
            dense_map< unsigned, int > nums;

            nums[1] = 0;
            CHECK(!nums.contains(1));
            nums[1] = -1;
            CHECK(nums.contains(1));
            CHECK(nums[1] == -1);
        }

        TEST_CASE("iterators") {
            dense_map< unsigned, int > map;

            map[3] = 3;
            map[1] = 1;

            SUBCASE("begin") {
                auto it = map.begin();
                CHECK(it->first == 0);
                CHECK(it->second == int());
            }

            SUBCASE("end") {
                auto it = --map.end();
                CHECK(it->first == 3);
                CHECK(it->second == 3);
            }
        }

        TEST_CASE("comparison") {
            dense_map< unsigned, char > a;
            a[1] = 'a';
            dense_map< unsigned, char > b;
            b[1] = 'b';

            CHECK(a != b);

            dense_map< unsigned, char > c;
            c[1] = 'a';

            CHECK(a == c);
        }
    } // test suite dense map
} // namespace gap::test
