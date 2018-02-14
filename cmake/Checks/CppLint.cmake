# Copyright (c) 2017, Kai Wolf. All rights reserved.
# Use of this source code is governed by a personal license that can be
# found in the LICENSE file in the top directory.

find_program(CPPLINT_EXE NAMES cpplint
  DOC "Path to cpplint executable")

if(CPPLINT_EXE)
  set(CMAKE_C_CPPLINT "${CPPLINT_EXE};--linelength=120")
  set(CMAKE_CXX_CPPLINT "${CPPLINT_EXE};--linelength=120")
else()
  message(WARNING "No cpplint executable found. Skipping checks...")
endif()
