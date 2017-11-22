// Copyright (c) 2017, Kai Wolf. All rights reserved.
// Use of this source code is governed by a personal license that can be
// found in the LICENSE file in the top directory.

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

TEST_CASE(
    "Check intrinsics"
    "[sanity_check]") {
    // we hope that true is true
    REQUIRE(true);

    // these values should be equal
    REQUIRE(1 + 1 == 2);

    int x[] = {1, 2, 3};
    int y[] = {1, 2, 3};
    for (int i = 0; i < 3; ++i) {
        REQUIRE(x[i] == y[i]);
    }

    double a = 1.51;
    double b = 1.52;
    REQUIRE(a != b);
}
