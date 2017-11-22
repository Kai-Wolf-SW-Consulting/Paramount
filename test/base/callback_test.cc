// Copyright (c) 2017, Kai Wolf. All rights reserved.
// Use of this source code is governed by a personal license that can be
// found in the LICENSE file in the top directory.

#include "base/callback.h"
#include <catch.hpp>
#include <string>

namespace {
int value = 0;

int FreeFunctionWithReturnParam() {
    value += 17;
    return value;
}
} // namespace

TEST_CASE("Callback with free function", "[callback_test]") {
    auto cb = pmt::MakeCallback(&FreeFunctionWithReturnParam);
    REQUIRE(value == 0);
    REQUIRE(cb->run() == 17);
}

TEST_CASE("Check for onetime callback", "[callback_test]") {
    auto cb = pmt::MakeCallback(&FreeFunctionWithReturnParam);
    REQUIRE_FALSE(cb->isRepeatable());
}

TEST_CASE("Check for multitime callback", "[callback_test]") {
    auto cb = pmt::MakePermanentCallback(&FreeFunctionWithReturnParam);
    REQUIRE(cb->isRepeatable());
}
