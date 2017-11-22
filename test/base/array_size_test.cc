// Copyright (c) 2017, Kai Wolf. All rights reserved.
// Use of this source code is governed by a personal license that can be
// found in the LICENSE file in the top directory.

#include "base/array_size.h"
#include <catch.hpp>

TEST_CASE("Get compile-time array size", "[array_size_test]") {
    int foobar[] = {2, 3, 5, 7, 9, 11};
    int size = arraysize(foobar);
    REQUIRE(size == 6);
}
