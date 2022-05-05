// Copyright (c) 2021-present, Trail of Bits, Inc.

#include <compare> // for operator<, strong_ordering
#include <doctest/doctest.h>
#include <gap/core/strong_type.hpp> // for strong_type

namespace gap::test
{
    struct int_tag {};
    using tagged_int = gap::strong_type< int, int_tag >;

    static_assert(tagged_int(1) < tagged_int(2));
    static_assert(tagged_int(1) == tagged_int(1));
    static_assert(tagged_int(2) > tagged_int(0));

    TEST_CASE("tagged int") {
        tagged_int a(1), b(1);
        CHECK(a == b);
    }

    struct simple_tag {};
    struct empty_struct {
        friend constexpr auto operator<=>(const empty_struct&, const empty_struct&) = default;
    };

    using tagged_struct = gap::strong_type< empty_struct, simple_tag >;

    static_assert(tagged_struct() == tagged_struct());

    struct string_tag {};
    using tagged_string = gap::strong_type< std::string, string_tag >;

    TEST_CASE("tagged string") {
        tagged_string a1("a"), a2("a");
        CHECK(a1 == a2);
    }

} // namespace gap::test
