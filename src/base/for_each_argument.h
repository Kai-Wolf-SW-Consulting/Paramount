// Copyright (c) 2017, Kai Wolf. All rights reserved.
// Use of this source code is governed by a personal license that can be
// found in the LICENSE file in the top directory.

#ifndef PARAMOUNT_FOR_EACH_ARGUMENT_H
#define PARAMOUNT_FOR_EACH_ARGUMENT_H

#include <iostream>
#include <utility>

namespace pmt {
namespace base {

template <class F, class... Args>
void ForEachArgument(F f, Args &&... args) {
    [](...) {}((f(std::forward<Args>(args)), 0)...);
}

template <class F, class... Args>
void ForEachArgumentInOrder(F f, Args &&... args) {
    (void) (int[]){(f(std::forward<Args>(args)), 0)...};
}

} // namespace base
} // namespace pmt

#endif // PARAMOUNT_FOR_EACH_ARGUMENT_H
