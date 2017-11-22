// Copyright (c) 2017, Kai Wolf. All rights reserved.
// Use of this source code is governed by a personal license that can be
// found in the LICENSE file in the top directory.

// Constrain read/write access for (memory-mapped) hw registers
//
// HW vendors often define register addresses via simple macros. This may lead
// to runtime bugs, since there is no way to check for register which are only
// read- or writable.
// According to Scott Meyers, Effective C++ book one should prefer
// compile-time and link-time errors to runtime errors. Furthermore, interfaces
// should be easy to use correctly and hard to use incorrectly.

#ifndef PARAMOUNT_RW_PROTECTED_H
#define PARAMOUNT_RW_PROTECTED_H

#include <cstdint>

namespace pmt {
namespace base {

template <typename t>
class WriteOnly {
  public:
    WriteOnly() = default;
    WriteOnly(const t &val) : val_(val) {}
    // returns void instead of reference to self in order to forbid read access
    void operator=(const t &val) {
        val_ = val;
    }
    WriteOnly(const WriteOnly &) = delete;
    WriteOnly &operator=(const WriteOnly &) = delete;

  private:
    t val_;
};

template <typename t>
class ReadOnly {
  public:
    ReadOnly() = default;
    ReadOnly(const t &val) : val_(val) {}
    operator const t &() const {
        return val_;
    }
    const t *operator&() const {
        return &val_;
    }
    ReadOnly(const ReadOnly &) = delete;
    ReadOnly &operator=(const ReadOnly &) = delete;

  private:
    t val_;
};

} // namespace base
} // namespace pmt

#endif // PARAMOUNT_RW_PROTECTED_H
