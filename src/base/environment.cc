// Copyright (c) 2017, Kai Wolf. All rights reserved.
// Use of this source code is governed by a personal license that can be
// found in the LICENSE file in the top directory.

#include "base/environment.h"
#include <cstddef>
#include <cstdlib>

namespace pmt {
namespace base {

bool GetEnvVar(const std::string& var_name, std::string* result) {
    const char* env_value = getenv(var_name.data());
    if (env_value == nullptr) { return false; }

    // Note that the variable may be defined but empty
    if (result != nullptr) { *result = env_value; }

    return true;
}

bool HasEnvVar(const std::string& var_name) {
    return GetEnvVar(var_name, nullptr);
}

bool SetEnvVar(const std::string& var_name, const std::string& new_value) {
    // On success, zero is returned
    return setenv(var_name.data(), new_value.c_str(), 1) == 0;
}

bool UnsetEnvVar(const std::string& var_name) {
    // On success, zero is returned
    return unsetenv(var_name.data()) == 0;
}

} // namespace base
} // namespace pmt
