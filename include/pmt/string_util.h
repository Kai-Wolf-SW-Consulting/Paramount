// Copyright (c) 2017, Kai Wolf. All rights reserved.
// Use of this source code is governed by a personal license that can be
// found in the LICENSE file in the top directory.

#ifndef PARAMOUNT_STRING_UTIL_H
#define PARAMOUNT_STRING_UTIL_H

#include <sstream>
#include <string>
#include <vector>

using StringList = std::vector<std::string>;

namespace pmt {

std::string Trim(const std::string& str) {
    auto first = str.find_first_not_of(' ');
    auto last  = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

StringList SplitString(const std::string& str, char delim) {
    StringList tokens;
    std::stringstream ss(str);

    std::string token;
    while (std::getline(ss, token, delim)) {
        if (!token.empty()) { tokens.push_back(Trim(token)); }
    }

    return tokens;
}

} // namespace pmt

#endif // PARAMOUNT_STRING_UTIL_H
