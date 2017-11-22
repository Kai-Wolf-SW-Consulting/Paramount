// Copyright (c) 2017, Kai Wolf. All rights reserved.
// Use of this source code is governed by a personal license that can be
// found in the LICENSE file in the top directory.

#ifndef PARAMOUNT_UNIQUE_COPY_H
#define PARAMOUNT_UNIQUE_COPY_H

namespace pmt {
namespace base {

template <class InIter, class OutIter, class Fn, class _Tp>
OutIter UniqueCopy(InIter first, InIter last, OutIter result, Fn binary_pred,
                    _Tp*) {
    _Tp value = *first;
    *result   = value;
    while (++first != last)
        if (!binary_pred(value, *first)) {
            value     = *first;
            *++result = value;
        }
    return ++result;
}

} // namespace base
} // namespace pmt

#endif // PARAMOUNT_UNIQUE_COPY_H
