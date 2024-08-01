# Copyright 2024, Trail of Bits, Inc. All rights reserved.

add_gap_test(test-gap-sarif
    definitions.cpp
)

target_link_libraries(test-gap-sarif
    PUBLIC
        gap-sarif
)