# Copyright 2021-present, Trail of Bits, Inc. All rights reserved.

find_package(doctest CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

set(GAP_TEST_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}" CACHE INTERNAL "GAP test source directory")

function(add_gap_test name)
  add_executable(${name} ${GAP_TEST_SOURCE_DIR}/main.cpp ${ARGN})
  target_compile_features(${name} PRIVATE cxx_std_20)
  target_link_libraries(${name}
    PRIVATE
      gap-settings
      gap-core

      doctest::doctest
      spdlog::spdlog
  )

  target_include_directories(${name}
    PUBLIC
      ${DOCTEST_INCLUDE_DIR}
    PRIVATE
      $<BUILD_INTERFACE:${GAP_TEST_SOURCE_DIR}>
  )

  add_test(
    NAME ${name}
    COMMAND "$<TARGET_FILE:${name}>"
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
  )
endfunction()

add_subdirectory(core)
add_subdirectory(coro)
add_subdirectory(graph)
add_subdirectory(sarif)

if (${GAP_ENABLE_MLIR})
  add_subdirectory(mlir)
endif()
