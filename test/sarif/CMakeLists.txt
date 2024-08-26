# Copyright 2024, Trail of Bits, Inc. All rights reserved.

if (GAP_ENABLE_SARIF)
    add_gap_test(test-gap-sarif
        sarif.cpp
    )

    target_link_libraries(test-gap-sarif
        PUBLIC
            gap-sarif
    )
endif()