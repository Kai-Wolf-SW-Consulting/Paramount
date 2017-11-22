// Copyright (c) 2017, Kai Wolf. All rights reserved.
// Use of this source code is governed by a personal license that can be
// found in the LICENSE file in the top directory.

#ifndef PARAMOUNT_CHECK_H
#define PARAMOUNT_CHECK_H

#include "base/logging.h"
#include "base/macros.h"
#include <cstdlib>
#include <ostream>

namespace pmt {
namespace base {
namespace internal {

class CheckHandler {
  public:
    CheckHandler(const char *check, const char *file, const char *func,
                 int line)
        : log_(GetErrorLoggingInstance()) {
        log_ << file << ":" << line << ": " << func << ": Check `" << check
             << "' failed. ";
    }

    std::ostream &GetLog() {
        return log_;
    }

    ~CheckHandler() {
        log_ << std::endl;
        std::abort();
    }

    CheckHandler &operator=(const CheckHandler &) = delete;
    CheckHandler(const CheckHandler &)            = delete;
    CheckHandler()                                = delete;

  private:
    std::ostream &log_;
};

} // namespace internal
} // namespace base
} // namespace pmt

#ifndef NDEBUG
#define CHECK(b)                                                       \
    ((b) ? ::pmt::base::internal::GetNullLoggingInstance()             \
         : ::pmt::base::internal::CheckHandler(#b, __FILE__, __func__, \
                                               __LINE__)               \
               .GetLog())
#else
#define CHECK(b) ::pmt::base::internal::GetNullLoggingInstance()
#endif

// Always-on checking
#define CHECK_LT(x, y) CHECK((x) < (y))
#define CHECK_GT(x, y) CHECK((x) > (y))
#define CHECK_LE(x, y) CHECK((x) <= (y))
#define CHECK_GE(x, y) CHECK((x) >= (y))
#define CHECK_EQ(x, y) CHECK((x) == (y))
#define CHECK_NE(x, y) CHECK((x) != (y))
#define CHECK_NOTNULL(x) CHECK((x) != nullptr)

// Debug-only checking.
#ifndef NDEBUG
#  define DCHECK(condition) CHECK(condition)
#  define DCHECK_EQ(val1, val2) CHECK_EQ(val1, val2)
#  define DCHECK_NE(val1, val2) CHECK_NE(val1, val2)
#  define DCHECK_LE(val1, val2) CHECK_LE(val1, val2)
#  define DCHECK_LT(val1, val2) CHECK_LT(val1, val2)
#  define DCHECK_GE(val1, val2) CHECK_GE(val1, val2)
#  define DCHECK_GT(val1, val2) CHECK_GT(val1, val2)
#else
// Note: We define the macros below such that in NDEBUG mode, values used only
// in DCHECKs aren't considered unused. The compiler requires that DCHECK
// && statements end in a semicolon and DCHECK(...) << "foo" compiles.
#define DCHECK(condition) \
    while (false)         \
    CHECK(condition)
#define DCHECK_EQ(val1, val2) \
    while (false)             \
    CHECK_EQ(val1, val2)
#define DCHECK_NE(val1, val2) \
    while (false)             \
    CHECK_NE(val1, val2)
#define DCHECK_LE(val1, val2) \
    while (false)             \
    CHECK_LE(val1, val2)
#define DCHECK_LT(val1, val2) \
    while (false)             \
    CHECK_LT(val1, val2)
#define DCHECK_GE(val1, val2) \
    while (false)             \
    CHECK_GE(val1, val2)
#define DCHECK_GT(val1, val2) \
    while (false)             \
    CHECK_GT(val1, val2)
#endif

#endif // PARAMOUNT_CHECK_H
