// Copyright (c) 2022-present, Trail of Bits, Inc.

#ifdef GAP_ENABLE_COROUTINES

    #include <doctest/doctest.h>
    #include <gap/core/generator.hpp>
    #include <gap/core/graph.hpp>
    #include <memory>
    #include <vector>

namespace gap::test
{
    namespace concepts
    {
        struct node_t {
            using node_pointer = std::shared_ptr< node_t >;
            using child_type   = node_pointer;

            generator< child_type > children() const;
        };

        static_assert(graph::node_like< node_t >);

        struct broken_node {
            generator< int > children();
        };

        static_assert(not graph::node_like< broken_node >);

        struct edge_t {
            using node_type    = node_t;
            using node_pointer = node_type::node_pointer;

            node_pointer source() const { return src; }
            node_pointer target() const { return dst; }

          private:
            node_pointer src, dst;
        };

        static_assert(graph::edge_like< edge_t >);

        struct graph_t {
            using node_type    = node_t;
            using edge_type    = edge_t;
            using node_pointer = node_type::node_pointer;

            generator< node_pointer > nodes() const;
            generator< edge_type > edges() const;
        };

        static_assert(graph::graph_like< graph_t >);
    } // namespace concepts

    //
    // test graph
    //
    struct node_t {
        using node_pointer = std::shared_ptr< node_t >;
        using child_type   = node_pointer;

        explicit node_t(char value)
            : value(value) {}

        generator< child_type > children() const {
            for (auto ch : _children)
                co_yield ch;
        }

        char value;

        std::vector< child_type > _children;
    };

    static_assert(graph::node_like< node_t >);

    template< graph::node_like node_t_ >
    struct edge_t {
        using node_type    = node_t_;
        using node_pointer = typename node_type::node_pointer;

        node_pointer source() const { return _src; }
        node_pointer target() const { return _dst; }

        node_pointer _src, _dst;
    };

    static_assert(graph::edge_like< edge_t< node_t > >);

    struct graph_t {
        using node_type = node_t;
        using edge_type = edge_t< node_t >;

        using node_pointer = node_type::node_pointer;

        generator< node_pointer > nodes() const {
            for (auto ch : _nodes)
                co_yield ch;
        }

        generator< edge_type > edges() const {
            for (auto node : _nodes) {
                for (auto child : node->children()) {
                    co_yield edge_type{ node, child };
                }
            }
        }

        std::vector< node_pointer > _nodes;
    };

    static_assert(graph::graph_like< graph_t >);

    using node_ptr = node_t::node_pointer;

    TEST_CASE("DFS") {
        graph_t g{
            {std::make_shared< node_t >('A'),
             std::make_shared< node_t >('B'),
             std::make_shared< node_t >('C'),
             std::make_shared< node_t >('D'),
             std::make_shared< node_t >('E')}
        };

        auto &nodes = g._nodes;

        nodes[0]->_children = { nodes[1], nodes[2] };
        nodes[1]->_children = { nodes[3] };
        nodes[2]->_children = { nodes[3] };
        nodes[3]->_children = { nodes[0] };

        constexpr auto yield_on_close = graph::yield_node::on_close;

        SUBCASE("DFS from single root") {
            std::vector topo = { 'D', 'B', 'C', 'A' };
            auto expected    = std::begin(topo);
            for (auto n : graph::dfs< yield_on_close >(nodes[0])) {
                CHECK(n->value == *(expected++));
            }
        }

        SUBCASE("DFS over full graph") {
            std::vector topo = { 'D', 'B', 'C', 'A', 'E' };
            auto expected    = std::begin(topo);
            for (auto n : graph::dfs< yield_on_close >(g)) {
                CHECK(n->value == *(expected++));
            }
        }

        SUBCASE("toposort from single root") {
            std::vector topo = { 'D', 'B', 'C', 'A' };
            auto expected    = std::begin(topo);
            for (auto n : graph::toposort(nodes[0])) {
                CHECK(n->value == *(expected++));
            }
        }
    }

} // namespace gap::test

#endif // GAP_ENABLE_COROUTINES
