// Copyright (c) 2017, Kai Wolf. All rights reserved.
// Use of this source code is governed by a personal license that can be
// found in the LICENSE file in the top directory.

#include "base/environment.h"
#include <catch.hpp>

TEST_CASE("Get environment variable", "[environment_test]") {
    std::string env_value;
    // We assume that every host system has a non-empty PATH
    REQUIRE(pmt::base::GetEnvVar("PATH", &env_value));
    REQUIRE_FALSE(env_value.empty());
}

TEST_CASE("Has environment variable", "[environment_test]") {
    // We assume that every system has a non-empty PATH
    REQUIRE(pmt::base::HasEnvVar("PATH"));
}

TEST_CASE("Set environment variable", "[environment_test]") {
    CHECK(pmt::base::SetEnvVar("FOO", "foo"));
    REQUIRE(pmt::base::HasEnvVar("FOO"));

    std::string value;
    REQUIRE(pmt::base::GetEnvVar("FOO", &value));
    REQUIRE(value == "foo");
}

TEST_CASE("Unset environemnt variable", "[environment_test]") {
    CHECK(pmt::base::SetEnvVar("FOO", "foo"));
    REQUIRE(pmt::base::HasEnvVar("FOO"));

    REQUIRE(pmt::base::UnsetEnvVar("FOO"));
    REQUIRE_FALSE(pmt::base::HasEnvVar("FOO"));
}
