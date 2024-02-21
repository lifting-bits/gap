# Copyright (c) 2021-present, Trail of Bits, Inc. All rights reserved.

add_headers(graph GAP_GRAPH_HEADERS
	graph.hpp
)

add_gap_library(gap-graph "${GAP_GRAPH_HEADERS}")

target_link_libraries(gap-graph INTERFACE gap-coro)