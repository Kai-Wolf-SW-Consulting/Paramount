# Copyright (c) 2017, Kai Wolf. All rights reserved.
# Use of this source code is governed by a personal license that can be
# found in the LICENSE file in the top directory.

# Enables clang-tidy checks from outside the project. Note that in order to
# enable those checks, you'll have to call cmake with the -C option, i.e.
#   $ cmake -C Checks/ClangTidy.cmake ..
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
find_program(CLANG_TIDY_EXE NAMES clang-tidy clang-tidy.exe
  DOC "Path to clang-tidy executable")

if(CLANG_TIDY_EXE)
  set(CMAKE_C_CLANG_TIDY "${CLANG_TIDY_EXE};-checks=*" CACHE STRING "")
  set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE};-checks=*" CACHE STRING "")
else()
  message(WARNING "No clang-tidy executable found. Skipping checks...")
endif()
