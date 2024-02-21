# Copyright 2024, Trail of Bits, Inc. All rights reserved.

add_gap_test(test-gap-graph
    graph.cpp
)

target_link_libraries(test-gap-graph
    PUBLIC
        gap-graph
)