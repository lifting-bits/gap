// Copyright 2022-present, Trail of Bits, Inc.

#pragma once

namespace gap
{
    struct no_property {};

    template< typename tag_t, typename value_t, typename base_t = no_property >
    struct property {
        using next_type  = base_t;
        using tag_type   = tag_t;
        using value_type = value_t;

        property(const value_t &value = {})
            : value(value) {}
        property(const value_t &value, const base_t &base)
            : value(value)
            , base(base) {}

        value_type value;
        next_type base;
    };

    template< typename map_t >
    concept property_map = requires {
        typename map_t::key_type;
        typename map_t::value_type;
        typename map_t::reference;
        typename map_t::category;
    };

    template< property_map map_t >
    struct default_property_map_traits {
        using key_type   = map_t::key_type;
        using value_type = map_t::value_type;
        using reference  = map_t::reference;
        using category   = map_t::category;
    };

    struct null_property_traits {};

    template< property_map map_t >
    struct property_traits : default_property_traits< map_t > {};

    template< typename other_t >
    struct property_traits : null_property_traits {};

    struct readable_property_map_tag {};

    struct writable_property_map_tag {};

    struct read_write_property_map_tag
        : readable_property_map_tag
        , writable_property_map_tag {};

    template< typename T >
    struct property_traits< T * > {
        using value_type = T;
        using reference  = value_type &;
        using key_type   = std::ptrdiff_t;
        using category   = read_write_property_map_tag;
    };

} // namespace gap
