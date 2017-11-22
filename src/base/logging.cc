// Copyright (c) 2017, Kai Wolf. All rights reserved.
// Use of this source code is governed by a personal license that can be
// found in the LICENSE file in the top directory.

#include "base/logging.h"
#include <iostream>

namespace pmt {
namespace base {
namespace internal {
inline int& LoggingLevelImpl() {
    static int level = 0;
    return level;
}

void SetLoggingLevel(int value) {
    LoggingLevelImpl() = value;
}

int GetLoggingLevel() {
    return LoggingLevelImpl();
}

class NullLoggingBuffer : public std::streambuf {
  public:
    int overflow(int c) override {
        return c;
    }
};

std::ostream& GetNullLoggingInstance() {
    static NullLoggingBuffer log_buffer;
    static std::ostream null_logger(&log_buffer);
    return null_logger;
}

std::ostream& GetErrorLoggingInstance() {
    return std::clog;
}
} // namespace internal
} // namespace base
} // namespace pmt
