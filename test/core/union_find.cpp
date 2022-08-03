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
        CHECK_EQ(uf.parent(zero), zero);
        CHECK_EQ(uf.rank(zero), rank_type(0u));
    }

    TEST_CASE("resizable-union-find") {
        resizable_union_find uf(0);

        auto a = uf.make_new_set();
        auto b = uf.make_new_set();
        CHECK_EQ(uf.size(), 2);

        CHECK_NE(uf.parent(a), uf.parent(b));

        uf.merge(uf.parent(a), uf.parent(b));
        CHECK_EQ(uf.parent(a), uf.parent(b));
    }

} // namespace gap::test
