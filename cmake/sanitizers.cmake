# Copyright (c) 2021-present, Trail of Bits, Inc. All rights reserved.

# add sanitizer options for a targer
function (enable_sanitizers target)

  if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    option(ENABLE_COVERAGE "Enable coverage reporting for gcc/clang" FALSE)

    if (ENABLE_COVERAGE)
      target_compile_options(${target} INTERFACE --coverage -O0 -g)
      target_link_libraries(${target} INTERFACE --coverage)
    endif ()

    set(sanitizers "")

    option(ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" OFF)
    if (ENABLE_SANITIZER_ADDRESS)
      list(APPEND sanitizers "address")
    endif ()

    option(ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)
    if (ENABLE_SANITIZER_MEMORY)
      list(APPEND sanitizers "memory")
    endif ()

    option(ENABLE_SANITIZER_UNDEFINED_BEHAVIOR "Enable undefined behavior sanitizer" OFF)
    if (ENABLE_SANITIZER_UNDEFINED_BEHAVIOR)
      list(APPEND sanitizers "undefined")
    endif ()

    option(ENABLE_SANITIZER_THREAD "Enable thread sanitizer" OFF)
    if (ENABLE_SANITIZER_THREAD)
      list(APPEND sanitizers "thread")
    endif ()

    list(JOIN sanitizers "," list_of_sanitizers)

  endif ()

  if (list_of_sanitizers)
    if (NOT "${list_of_sanitizers}" STREQUAL "")
      target_compile_options(${target} INTERFACE -fsanitize=${list_of_sanitizers})
      target_link_libraries(${target} INTERFACE -fsanitize=${list_of_sanitizers})
    endif ()
  endif ()

endfunction ()
