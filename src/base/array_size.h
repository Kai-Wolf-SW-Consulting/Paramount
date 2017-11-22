// Copyright (c) 2017, Kai Wolf. All rights reserved.
// Use of this source code is governed by a personal license that can be
// found in the LICENSE file in the top directory.

#ifndef PARAMOUNT_ARRAY_SIZE_H
#define PARAMOUNT_ARRAY_SIZE_H

#include <cstddef>

namespace pmt {
namespace base {
namespace internal {

/// The arraysize(arr) macro returns the number of elements in array.
/// The expression is a compile-time constant, and therefore can be used in
/// defining new arrays, for example. If you use arraysize on a pointer by
/// mistake, you will get a compile-time error, since *foo and foo[] are
/// two different things.
template <typename T, std::size_t N>
char (&ArraySizeHelper(T (&array)[N]))[N];

#define arraysize(arr) (sizeof(::pmt::base::internal::ArraySizeHelper(arr)))
} // namespace internal

/// Used to explicitly mark the return value of a function as unused.
template <typename T>
inline void ignore_result(const T& /*unused*/) {}
} // namespace base
} // namespace pmt

#endif // PARAMOUNT_ARRAY_SIZE_H
