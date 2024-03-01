// Copyright (c) 2021-present, Trail of Bits, Inc.

#pragma once

// Compiler Detection

#if defined(_MSC_VER)
    #define GAP_COMPILER_MSVC _MSC_FULL_VER
#else
    #define GAP_COMPILER_MSVC 0
#endif

#if defined(__clang__)
    #define GAP_COMPILER_CLANG \
        (__clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__)
#else
    #define GAP_COMPILER_CLANG 0
#endif

#if defined(__GNUC__)
    #define GAP_COMPILER_GCC (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#else
    #define GAP_COMPILER_GCC 0
#endif

#if GAP_COMPILER_CLANG
    #if __clang_major__ >= 7
        #define GAP_COMPILER_SUPPORTS_SYMMETRIC_TRANSFER 1
    #endif
#endif
#ifndef GAP_COMPILER_SUPPORTS_SYMMETRIC_TRANSFER
    #define GAP_COMPILER_SUPPORTS_SYMMETRIC_TRANSFER 0
#endif

#if GAP_COMPILER_MSVC
    #if __has_include(<coroutine>)
        #include <yvals_core.h>
        #ifdef __cpp_lib_coroutine
            #define GAP_COROHEADER_FOUND_AND_USABLE
        #endif
    #endif
#else
    #if __has_include(<coroutine>)
        #define GAP_COROHEADER_FOUND_AND_USABLE
    #endif
#endif

#if GAP_COMPILER_MSVC
# define GAP_NOINLINE __declspec(noinline)
#elif GAP_COMPILER_CLANG || GAP_COMPILER_GCC
# define GAP_NOINLINE __attribute__((noinline))
#endif

#if GAP_COMPILER_MSVC
# define GAP_FORCE_INLINE __forceinline
#elif GAP_COMPILER_CLANG
# define GAP_FORCE_INLINE __attribute__((always_inline))
#else
# define GAP_FORCE_INLINE inline
#endif