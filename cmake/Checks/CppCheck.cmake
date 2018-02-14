# Copyright (c) 2017, Kai Wolf. All rights reserved.
# Use of this source code is governed by a personal license that can be
# found in the LICENSE file in the top directory.

find_program(CPPCHECK_EXE NAMES cppcheck cppcheck.exe
  DOC "Path to cppcheck executable")

if(CPPCHECK_EXE)
  set(CMAKE_C_CPPCHECK "${CPPCHECK_EXE};--std=c++11")
  set(CMAKE_CXX_CPPCHECK "${CPPCHECK_EXE};--std=c++11")
else()
  message(WARNING "No cppcheck executable found. Skipping checks...")
endif()
