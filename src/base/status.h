// Copyright (c) 2017, Kai Wolf. All rights reserved.
// Use of this source code is governed by a personal license that can be
// found in the LICENSE file in the top directory.

#ifndef PARAMOUNT_STATUS_H
#define PARAMOUNT_STATUS_H

#include <string>
#include <utility>

namespace pmt {
namespace base {
namespace error {
enum Code { OK = 0 };
} // namespace error

/// Determines whether a call or a given object is error free.
/// Status objects may be used, whenever one inputs an object into a function
/// and wants to check, if the desired transformation could be applied
/// sucessfully.
class Status {
  public:
    Status() : code_(error::OK) {}
    Status(error::Code code, std::string msg)
        : code_(code), msg_(std::move(msg)) {}
    Status(const Status& status) = default;
    ~Status()                    = default;

    Status& operator=(const Status& status) = default;

    bool operator==(const Status& status) const {
        return code_ == status.code_ && msg_ == status.msg_;
    }

    bool ok() const {
        return code_ == error::OK;
    }

    const std::string& errorMessage() const {
        return msg_;
    }

    error::Code errorCode() const {
        return code_;
    }

    std::string toString() const;

  private:
    error::Code code_;
    std::string msg_;
};

} // namespace base
} // namespace pmt

#endif // PARAMOUNT_STATUS_H
