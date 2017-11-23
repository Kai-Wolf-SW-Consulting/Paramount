// Copyright (c) 2017, Kai Wolf. All rights reserved.
// Use of this source code is governed by a personal license that can be
// found in the LICENSE file in the top directory.

#ifndef PARAMOUNT_MACROS_H
#define PARAMOUNT_MACROS_H

#include <memory>

/// Inside the declaration of a class will make it unassignable
#define DISALLOW_ASSIGN(TypeName) void operator=(const TypeName&) = delete

/// Inside the declaration of a class will make it uncopyable and unassignable
#if __cplusplus < 201103L
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
    TypeName(const TypeName&);             \
    void operator=(const TypeName&)
#else
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
    TypeName(const TypeName&) = delete;    \
    TypeName& operator=(const TypeName&) = delete;
#endif

/// Inside the declaration of a class will make it un-default constructible
#define DISALLOW_DEFAULT_CTOR(TypeName) TypeName() = delete

#define DISALLOW_IMPLICIT_CONSTRUCTOR(TypeName) \
    TypeName() = delete;                        \
    DISALLOW_COPY_AND_ASSIGN(TypeName)

/// Verify an expression during compile-time
#undef COMPILE_ASSERT
#define COMPILE_ASSERT(expr, msg) static_assert(expr, #msg)

/// Give branch indication hints to the (GCC) compiler: whether the if
/// condition is likely to be true or false
#undef LIKELY
#undef UNLIKELY
#if defined(__GNUC__) && __GNUC__ >= 4
#  define LIKELY(x) (__builtin_expect((x), 1))
#  define UNLIKELY(x) (__builtin_expect((x), 0))
#else
#  define LIKELY(x) (x)
#  define UNLIKELY(x) (x)
#endif

/// Determine host os system
#if defined(_WIN32)
#  define OS_WINDOWS 1
#  define __func__ __FUNCTION__
#elif defined(__APPLE__)
#  define OS_MACOSX 1
#elif defined(__FreeBSD__)
#  define OS_FREEBSD 1
#elif defined(__linux__)
#  define OS_LINUX 1
#endif

/// determine used compiler
#if defined(__clang__)
#  define COMPILER_CLANG
#elif defined(_MSC_VER)
#  define COMPILER_MSVC
#elif defined(__GNUC__)
#  define COMPILER_GCC
#endif

/// Concatenate symbols s1 and s2
#define CONCATENATE_IMPL(s1, s2) s1##s2
#define CONCATENATE(s1, s2) CONCATENATE_IMPL(s1, s2)

#ifdef __COUNTER__
#  define ANONYMOUS_VARIABLE(str) CONCATENATE(str, __COUNTER__)
#else
#  define ANONYMOUS_VARIABLE(str) CONCATENATE(str, __LINE__)
#endif

#endif // PARAMOUNT_MACROS_H
