// Copyright 2022-present, Trail of Bits, Inc.

#pragma once

#ifdef GAP_ENABLE_COROUTINES

    #include <gap/core/generator.hpp>
    #include <gap/core/ranges.hpp>
    #include <ranges>

namespace gap
{
    //
    // node concepts
    //
    template< typename N >
    concept node_like = requires(N&& n) {
        { n.children() } -> ranges::value_range< N >;
    };

    template< typename R >
    concept nodes_range
        = ranges::range< R > && node_like< std::remove_cvref_t< typename R::value_type > >;

    //
    // edge concepts
    //
    template< typename E >
    concept edge_like = requires(E&& e) {
        node_like< typename E::node_type >;

        { e.source() } -> node_like;
        { e.target() } -> node_like;
    };

    template< typename R >
    concept edges_range
        = ranges::range< R > && edge_like< std::remove_cvref_t< typename R::value_type > >;

    //
    // graph concepts
    //
    template< typename G >
    concept graph_like = requires(G&& g) {
        node_like< typename G::node_type >;
        edge_like< typename G::edge_type >;

        { g.nodes() } -> nodes_range;
        { g.edges() } -> edges_range;
    };

} // namespace gap

#endif // GAP_ENABLE_COROUTINES
