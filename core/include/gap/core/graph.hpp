// Copyright 2022-present, Trail of Bits, Inc.

#pragma once

#ifdef GAP_ENABLE_COROUTINES

    #include <gap/core/generator.hpp>
    #include <gap/core/ranges.hpp>

    #include <unordered_set>

namespace gap::graph
{
    //
    // node concepts
    //
    template< typename node_type >
    concept node_like = requires(node_type n) {
        { n.children() } -> ranges::value_range< typename node_type::child_type >;
    };

    //
    // edge concepts
    //
    template< typename edge_type >
    concept edge_like = requires(edge_type&& e) {
        node_like< typename edge_type::source_type >;
        node_like< typename edge_type::target_type >;

        { e.source() } -> std::same_as< typename edge_type::source_type >;
        { e.target() } -> std::same_as< typename edge_type::target_type >;
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

    enum class yield_node
    {
        never, on_open, on_close
    };

    template< typename node_pointer >
    using seen_set = std::unordered_set< node_pointer >;

    namespace detail
    {
        template< yield_node when, typename node_pointer >
        requires node_like< typename node_pointer::element_type >
        generator< node_pointer > dfs(node_pointer root, seen_set< node_pointer >& seen) {
            seen.insert(root);

            if constexpr (when == yield_node::on_open) {
                co_yield root;
            }

            for (auto child : root->children()) {
                if (!seen.count(child)) {
                    for (auto succ : dfs< when >(child, seen)) {
                        co_yield succ;
                    }
                }
            }

            if constexpr (when == yield_node::on_close) {
                co_yield root;
            };
        }

        template< yield_node when, typename node_pointer >
        requires node_like< typename node_pointer::element_type >
        generator< node_pointer > dfs(node_pointer root) {
            seen_set< node_pointer > seen;
            for (auto node : dfs< when >(root, seen)) {
                co_yield node;
            }
        }

    } // namespace detail

    template< yield_node when, graph_like graph_type, typename node_pointer = typename graph_type::node_pointer >
    generator< node_pointer > dfs(const graph_type &graph) {
        seen_set< node_pointer > seen;
        for (auto root : graph.nodes()) {
            if (!seen.count(root)) {
                for (auto node : detail::dfs< when >(root, seen)) {
                    co_yield node;
                }
            }
        }
    }

    template< yield_node when, typename node_pointer >
    requires node_like< typename node_pointer::element_type >
    generator< node_pointer > dfs(node_pointer root) {
        return detail::dfs< when >(root);
    }

    template< typename node_pointer >
    requires node_like< typename node_pointer::element_type >
    generator< node_pointer > toposort(node_pointer root) {
        return dfs< yield_node::on_close >(root);
    }

} // namespace gap::graph

#endif // GAP_ENABLE_COROUTINES
