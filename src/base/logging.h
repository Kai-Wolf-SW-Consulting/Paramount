// Copyright (c) 2017, Kai Wolf. All rights reserved.
// Use of this source code is governed by a personal license that can be
// found in the LICENSE file in the top directory.

#ifndef PARAMOUNT_LOGGING_H
#define PARAMOUNT_LOGGING_H

#include "base/macros.h"

#ifdef OS_WINDOWS
#undef ERROR
#endif
#include <ostream>

namespace pmt {
namespace base {

enum LogSeverity { FATAL, ERROR, WARNING, INFO };

namespace internal {
int GetLoggingLevel();
void SetLoggingLevel(int value);

std::ostream& GetNullLoggingInstance();
std::ostream& GetErrorLoggingInstance();

inline std::ostream& GetLoggingInstanceForLevel(int level) {
    if (level <= GetLoggingLevel()) { return GetErrorLoggingInstance(); }
    return GetNullLoggingInstance();
}
} // namespace internal
} // namespace base

#define LOGGING(x)                                        \
    (::pmt::base::internal::GetLoggingInstanceForLevel(x) \
     << "-- Paramount LOG(" << (x) << "): ")
} // namespace pmt

#endif // PARAMOUNT_LOGGING_H
