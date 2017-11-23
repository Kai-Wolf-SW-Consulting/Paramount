// Copyright (c) 2017, Kai Wolf. All rights reserved.
// Use of this source code is governed by a personal license that can be
// found in the LICENSE file in the top directory.

#include "base/scope_guard.h"
#include <catch.hpp>

TEST_CASE("Execute scope guard after scope" "[scope_guard_test]") {
    using namespace pmt::base;
    int foo = 17;
    {
        SCOPE_EXIT { foo = 23; };
    }
    REQUIRE(foo == 23);
}

