# Copyright 2022-present, Trail of Bits, Inc. All rights reserved.

add_executable(coroutines-example
    coroutines-example.cpp
)

target_link_libraries(coroutines-example
    PRIVATE gap-core
)
