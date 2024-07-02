# Copyright 2024, Trail of Bits, Inc. All rights reserved.

add_gap_test(test-gap-core
    bigint.cpp
    benchmark.cpp
    crtp.cpp
    dense_map.cpp
    hash.cpp
    memoize.cpp
    optional.cpp
    parser.cpp
    ranges.cpp
    strong_type.cpp
    union_find.cpp
)

target_link_libraries(test-gap-core
    PUBLIC
        gap-core
)