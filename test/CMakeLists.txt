# Copyright (c) 2017, Kai Wolf. All rights reserved.
# Use of this source code is governed by a personal license that can be
# found in the LICENSE file in the top directory.

set(TEST_SOURCES
  base/array_copy_test.cc
  base/array_size_test.cc
  base/callback_test.cc
  base/environment_test.cc
  base/for_each_argument_test.cc
  base/rw_protected_test.cc
  base/scope_guard_test.cc
  base/unique_copy_test.cc
  paramount_test.cc
)

set(TEST_EXE_NAME ${PROJECT_NAME}_test)
add_executable(${TEST_EXE_NAME} ${TEST_SOURCES})

set_target_properties(${TEST_EXE_NAME} PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS NO)

get_filename_component(PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
target_include_directories(${TEST_EXE_NAME}
  PRIVATE ${PARENT_DIR}/src) # include private implementation for testing

target_link_libraries(${TEST_EXE_NAME}
  PRIVATE pmt::Paramount thirdparty::catch)

add_test(NAME RunTests COMMAND $<TARGET_FILE:${TEST_EXE_NAME}>)
