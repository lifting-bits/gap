# Copyright 2024, Trail of Bits, Inc. All rights reserved.

add_gap_test(test-gap-coro
    counted.cpp
    generator.cpp
    recursive_generator.cpp
    shared_task.cpp
    task.cpp
    when_all_ready.cpp
)

target_link_libraries(test-gap-coro
    PUBLIC
        gap-coro
)