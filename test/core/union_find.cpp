// Copyright (c) 2022-present, Trail of Bits, Inc.

#include <doctest/doctest.h>
#include <gap/core/union_find.hpp>
#include <vector>

namespace gap::test
{
    using union_type = gap::union_type;
    TEST_CASE("union-find-size-constructor") {
        constexpr int size = 5;
        union_find uf(size);

        auto zero = union_type(0u);
        CHECK(uf.parent(zero) == zero);
        CHECK(uf.rank(zero) == rank_type(0u));
    }

} // namespace gap::test
