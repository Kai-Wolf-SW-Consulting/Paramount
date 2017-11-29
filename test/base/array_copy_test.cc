// Copyright (c) 2017, Kai Wolf. All rights reserved.
// Use of this source code is governed by a personal license that can be
// found in the LICENSE file in the top directory.

#include <pmt/array_copy.h>
#include <catch.hpp>

#include <iostream>

TEST_CASE("Copy element-wise into equal sized arrays", "[array_copy_test]") {
    int a[] = {17, 23, 42};
    int b[3];
    pmt::ArrayCopy(b, a);

    for (int idx = 0; idx < 3; idx++)
        REQUIRE(a[idx] == b[idx]);
}
