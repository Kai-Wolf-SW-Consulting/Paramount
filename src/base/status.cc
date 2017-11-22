// Copyright (c) 2017, Kai Wolf. All rights reserved.
// Use of this source code is governed by a personal license that can be
// found in the LICENSE file in the top directory.

#include "base/status.h"

namespace pmt {
namespace base {

#define CASE(code) \
    case error::code: return #code

static std::string StatusCodeToString(error::Code code) {
    switch (code) {
        CASE(OK);
        default:
            std::string result("Error #");
            result.append(std::to_string(code));
            return result;
    }
}
#undef CASE

std::string Status::toString() const {
    auto result = StatusCodeToString(code_);
    if (!msg_.empty()) {
        result.append(": ");
        result.append(msg_);
    }

    return result;
}
} // namespace base
} // namespace pmt
