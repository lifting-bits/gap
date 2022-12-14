// Copyright (c) 2022-present, Trail of Bits, Inc.

#include <doctest/doctest.h>
#include <gap/core/optional.hpp>
#include <optional>

namespace gap::test
{
    struct optional_int {
        using value_type = int;

        constexpr optional_int() = default;
        constexpr optional_int(int v) : value(v), has_value(true) {}

        constexpr operator int() const noexcept { return value; }
        constexpr explicit operator bool() const noexcept { return has_value; }

        constexpr value_type& operator*() & noexcept { return value; }
        constexpr value_type operator*() const& noexcept { return value; }
        constexpr value_type operator*() && noexcept { return value; }
        constexpr value_type operator*() const&& noexcept { return value; }

        int value = 0;
        bool has_value = false;
    };

    static_assert( !std::is_pointer_v< optional_int > );
    static_assert( std::is_convertible_v< optional_int, bool > );

    static_assert( optional_like< std::optional< int > > );
    static_assert( optional_like< optional_adaptor< int* > > );
    static_assert( optional_like< optional_adaptor< optional_int > > );

    TEST_SUITE("std optional") {
        using maybe_integer = optional_wrapper< std::optional< int > >;

        template< typename T >
        constexpr bool constructible_from = std::is_constructible_v< maybe_integer, T >;
        static_assert(constructible_from< int >);
        static_assert(constructible_from< std::optional< int > >);
        static_assert(constructible_from< std::optional< short > >);
        static_assert(constructible_from< optional_wrapper< std::optional< int > > >);
        static_assert(constructible_from< optional_wrapper< std::optional< long > > >);

        static_assert(!constructible_from< std::string >);
        static_assert(!constructible_from< std::optional< std::string > >);
        static_assert(!constructible_from<
            optional_wrapper< std::optional< std::string > >
        >);

        TEST_CASE("create") {
            maybe_integer val;
            val = 10;
            CHECK_EQ(val, 10);
        }

        TEST_CASE("bool") {
            maybe_integer val = 10;
            CHECK(val);
            CHECK(val.has_value());

            const maybe_integer cval = val;
            CHECK(cval);
            CHECK(cval.has_value());

            maybe_integer none = std::nullopt;
            CHECK(!none);
            CHECK(!none.has_value());
        }

        TEST_CASE("value") {
            maybe_integer val = 10;
            CHECK_EQ(val.value(), 10);
            CHECK_EQ(*val, 10);
            CHECK_EQ(*std::move(val), 10);

            const auto cval = val;
            CHECK_EQ(cval.value(), 10);
            CHECK_EQ(*cval, 10);
            CHECK_EQ(*std::move(cval), 10);
        }

        TEST_CASE("value_or") {
            maybe_integer val = 10;
            CHECK_EQ(val.value_or(1), 10);
            CHECK_EQ(std::move(val).value_or(1), 10);

            const auto cval = val;
            CHECK_EQ(cval.value_or(1), 10);
            CHECK_EQ(std::move(cval).value_or(1), 10);

            maybe_integer none = std::nullopt;
            CHECK_EQ(none.value_or(1), 1);

            const auto cnone = none;
            CHECK_EQ(cnone.value_or(1), 1);
        }

        constexpr auto add = [] (auto v) -> maybe_integer {
            return v + 1;
        };

        TEST_CASE("and_then") {
            maybe_integer a = maybe_integer(9).and_then(add);
            CHECK_EQ(a.value(), 10);

            maybe_integer b = maybe_integer(9).and_then(add).and_then(add);
            CHECK_EQ(b.value(), 11);

            maybe_integer c = maybe_integer(1);
            auto d = std::move(c).and_then(add).and_then(add);
            CHECK_EQ(d.value(), 3);

            maybe_integer none = maybe_integer().and_then(add).and_then(add);
            CHECK(!none.has_value());
        }

        // struct A {};
        // struct B {};
        // struct C {};

        // TEST_CASE("transform") {
        //     using optional_a = optional_wrapper< std::optional< A > >;
        //     using optional_b = optional_wrapper< std::optional< B > >;

        //     auto a_to_b = [] (optional_a) -> B { return B{}; };
        //     auto b_to_c = [] (optional_b) -> C { return C{}; };

        //     optional_a a( A{} );
        //     auto res = a.transform(a_to_b).transform(b_to_c);
        // }

        TEST_CASE("or else") {
            maybe_integer a = 42;
            CHECK_EQ(a.or_else([] { return maybe_integer(13); }).value(), 42);

            maybe_integer none;
            CHECK_EQ(none.or_else([] { return maybe_integer(13); }).value(), 13);
        }
    }

    TEST_SUITE("pointer-like optional") {
        using maybe_integer_ptr = optional_wrapper< int* >;
        TEST_CASE("create") {
            int v = 10;
            maybe_integer_ptr ptr = &v;
            int *test_ptr = &v;
            CHECK_EQ(ptr, test_ptr);
        }

        TEST_CASE("bool") {
            int v = 10;
            maybe_integer_ptr val = &v;
            CHECK(val);
            CHECK(val.has_value());

            const maybe_integer_ptr cval = val;
            CHECK(cval);
            CHECK(cval.has_value());

            maybe_integer_ptr none = nullptr;
            CHECK(!none);
            CHECK(!none.has_value());
        }

        TEST_CASE("value") {
            int v = 10;
            maybe_integer_ptr val = &v;
            CHECK_EQ(val.value(), 10);
            CHECK_EQ(*val, 10);
            CHECK_EQ(std::move(val).value(), 10);

            const maybe_integer_ptr cval = val;
            CHECK_EQ(cval.value(), 10);
            CHECK_EQ(*cval, 10);
            CHECK_EQ(std::move(cval).value(), 10);
        }

        TEST_CASE("value_or") {
            int v = 10;
            maybe_integer_ptr val = &v;
            CHECK_EQ(val.value_or(1), 10);
            CHECK_EQ(std::move(val).value_or(1), 10);

            const auto cval = val;
            CHECK_EQ(cval.value_or(1), 10);
            CHECK_EQ(std::move(cval).value_or(1), 10);

            maybe_integer_ptr none = nullptr;
            CHECK_EQ(none.value_or(1), 1);
            CHECK_EQ(std::move(none).value_or(1), 1);

            const auto cnone = none;
            CHECK_EQ(cnone.value_or(1), 1);
            CHECK_EQ(std::move(cnone).value_or(1), 1);
        }

        constexpr auto add = [] (auto &&v) -> maybe_integer_ptr {
            v += 1;
            return &v;
        };

        TEST_CASE("and_then") {
            int v = 10;
            maybe_integer_ptr val = &v;

            auto a = val.and_then(add);
            CHECK_EQ(a.value(), 11);

            auto b = val.and_then(add).and_then(add);
            CHECK_EQ(b.value(), 13);

            int x = 1;
            auto c = maybe_integer_ptr(&x);
            auto d = std::move(c).and_then(add).and_then(add);
            CHECK_EQ(d.value(), 3);

            auto none = maybe_integer_ptr();
            auto e = none.and_then(add);
            CHECK(!e.has_value());
        }
    }

    TEST_SUITE("value-like optional") {
        using maybe_integer = optional_wrapper< optional_int >;
        TEST_CASE("create") {
            maybe_integer val = 10;
            CHECK_EQ(val, 10);
        }

        TEST_CASE("bool") {
            maybe_integer val = 10;
            CHECK(val);
            CHECK(val.has_value());

            const maybe_integer cval = val;
            CHECK(cval);
            CHECK(cval.has_value());

            maybe_integer none;
            CHECK(!none);
            CHECK(!none.has_value());
        }

        TEST_CASE("value") {
            maybe_integer val = 10;
            CHECK_EQ(val.value(), 10);
            CHECK_EQ(*val, 10);
            CHECK_EQ(*std::move(val), 10);

            const auto cval = val;
            CHECK_EQ(cval.value(), 10);
            CHECK_EQ(*cval, 10);
            CHECK_EQ(*std::move(cval), 10);
        }

        TEST_CASE("value_or") {
            maybe_integer val = 10;
            CHECK_EQ(val.value_or(1), 10);
            CHECK_EQ(std::move(val).value_or(1), 10);

            const auto cval = val;
            CHECK_EQ(cval.value_or(1), 10);
            CHECK_EQ(std::move(cval).value_or(1), 10);

            maybe_integer none;
            CHECK_EQ(none.value_or(1), 1);

            const auto cnone = none;
            CHECK_EQ(cnone.value_or(1), 1);
        }

        constexpr auto add = [] (auto v) -> maybe_integer {
            return v + 1;
        };

        TEST_CASE("and_then") {
            maybe_integer a = maybe_integer(9).and_then(add);
            CHECK_EQ(a.value(), 10);

            maybe_integer b = maybe_integer(9).and_then(add).and_then(add);
            CHECK_EQ(b.value(), 11);

            maybe_integer c = maybe_integer(1);
            auto d = std::move(c).and_then(add).and_then(add);
            CHECK_EQ(d.value(), 3);

            maybe_integer none = maybe_integer().and_then(add).and_then(add);
            CHECK(!none.has_value());
        }

        TEST_CASE("or else") {
            maybe_integer a = 42;
            CHECK_EQ(a.or_else([] { return maybe_integer(13); }).value(), 42);

            maybe_integer none;
            CHECK_EQ(none.or_else([] { return maybe_integer(13); }).value(), 13);
        }
    }

} // namespace gap::test
