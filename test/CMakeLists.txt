# Copyright 2021-present, Trail of Bits, Inc. All rights reserved.

find_package(doctest CONFIG REQUIRED)

add_executable(test-gap
  main.cpp

  core/concepts.cpp
  core/benchmark.cpp
  core/generator.cpp
  core/parser.cpp
  core/ranges.cpp
  core/strong_type.cpp
  core/union_find.cpp
)

target_compile_features(test-gap PRIVATE cxx_std_20)

target_link_libraries(test-gap
  PRIVATE
    gap-settings
    gap-core
    doctest::doctest
)

target_include_directories(test-gap PUBLIC ${DOCTEST_INCLUDE_DIR})

add_test(
  NAME test-gap
  COMMAND "$<TARGET_FILE:test-gap>"
  WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
)
