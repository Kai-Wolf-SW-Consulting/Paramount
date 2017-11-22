// Copyright (c) 2017, Kai Wolf. All rights reserved.
// Use of this source code is governed by a personal license that can be
// found in the LICENSE file in the top directory.

#include "base/for_each_argument.h"
#include <catch.hpp>
#include <sstream>

namespace {
void PrintFloat(float f) {
    std::cout << f << ",";
}
} // namespace

TEST_CASE("Execute fun for each argument", "[for_each_argument_test]") {
  // Redirect standard output
  std::stringstream buffer;
  std::streambuf *sbuf = std::cout.rdbuf();
  std::cout.rdbuf(buffer.rdbuf());

  pmt::base::ForEachArgumentInOrder(PrintFloat, 1.2f, 2.3f, 3.4f, 4.5f);

  // Cleanup
  std::cout.rdbuf(sbuf);

  REQUIRE(buffer.str() == "1.2,2.3,3.4,4.5,");
}
