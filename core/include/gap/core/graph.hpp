// Copyright 2022-present, Trail of Bits, Inc.

#pragma once

#ifdef GAP_ENABLE_COROUTINES

    #include <gap/core/generator.hpp>
    #include <gap/core/ranges.hpp>

    #include <ranges>
    #include <unordered_set>

namespace gap::graph
{
    //
    // node concepts
    //
    template< typename node_type >
    concept node_like = requires(node_type n) {
        { n.children() } -> ranges::value_range< typename node_type::node_pointer >;
    };

    //
    // edge concepts
    //
    template< typename edge_type >
    concept edge_like = requires(edge_type&& e) {
        node_like< typename edge_type::node_type >;

        { e.source() } -> std::same_as< typename edge_type::node_pointer >;
        { e.target() } -> std::same_as< typename edge_type::node_pointer >;
    };

    //
    // graph concepts
    //
    template< typename graph_type >
    concept graph_like = requires(graph_type&& g) {
        node_like< typename graph_type::node_type >;
        edge_like< typename graph_type::edge_type >;

        { g.nodes() } -> ranges::value_range< typename graph_type::node_pointer >;
        { g.edges() } -> ranges::value_range< typename graph_type::edge_type >;
    };

        { g.nodes() } -> nodes_range;
        { g.edges() } -> edges_range;
    };

} // namespace gap::graph

#endif // GAP_ENABLE_COROUTINES
