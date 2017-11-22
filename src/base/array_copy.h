// Copyright (c) 2017, Kai Wolf. All rights reserved.
// Use of this source code is governed by a personal license that can be
// found in the LICENSE file in the top directory.

#ifndef PARAMOUNT_ARRAY_COPY_H
#define PARAMOUNT_ARRAY_COPY_H

#include <cstddef>
#include <cstring>
#include <iostream>
#include <type_traits>

namespace pmt {
namespace base {

template <typename T, std::size_t n>
inline void ArrayCopy(T (&dst)[n], T (&src)[n]) {
    static_assert(std::is_trivially_copy_assignable<T>::value,
                  "element type has non-trivial copy assignment");
    std::memcpy(dst, src, sizeof(T) * n);
}

template <typename T, std::size_t m, std::size_t n>
inline void ArrayCopy(T (&dst)[m], T (&src)[n]) {
    static_assert(m >= n, "destination too small");
    for (std::size_t idx = 0; idx < n; ++idx) {
        dst[idx] = src[idx];
    }
}

} // namespace base
} // namespace pmt

#endif // PARAMOUNT_ARRAY_COPY_H
