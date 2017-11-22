// Copyright (c) 2017, Kai Wolf. All rights reserved.
// Use of this source code is governed by a personal license that can be
// found in the LICENSE file in the top directory.

#include "base/unique_copy.h"
#include <catch.hpp>
#include <iostream>
#include <sstream>

TEST_CASE("Print only unique elements", "[unique_copy_test]") {
    // Redirect standard output
    std::stringstream buffer;
    std::streambuf *sbuf = std::cout.rdbuf();
    std::cout.rdbuf(buffer.rdbuf());

    std::stringstream sin{"1 1 2 3 3 3 4 5"};
    unique_copy(std::istream_iterator<int>{sin}, std::istream_iterator<int>{},
                std::ostream_iterator<int>{std::cout, " "},
                std::equal_to<int>{});

    // Cleanup
    std::cout.rdbuf(sbuf);

    REQUIRE(buffer.str() == "1 2 3 4 5 ");
}
