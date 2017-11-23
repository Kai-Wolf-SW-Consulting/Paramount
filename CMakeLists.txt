# Copyright (c) 2017, Kai Wolf. All rights reserved.
# Use of this source code is governed by a personal license that can be
# found in the LICENSE file in the top directory.

cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

project(Paramount VERSION 0.1 LANGUAGES CXX)
set(COMPANY    "Kai Wolf - SW Consulting")
set(COPYRIGHT  "Copyright (c) 2017, Kai Wolf. All rights reserved.")
set(IDENTIFIER "me.kai-wolf")

option(ENABLE_TESTS "Build with tests" ON)

#find_package(Boost 1.60.0 COMPONENTS filesystem system thread)
add_subdirectory(thirdparty)

set(SOURCES
  src/base/array_copy.h
  src/base/array_size.h
  src/base/check.h
  src/base/cmdline_flags.cc
  src/base/cmdline_flags.h
  src/base/environment.cc
  src/base/environment.h
  src/base/integral_types.h
  src/base/logging.cc
  src/base/logging.h
  src/base/macros.h
  src/base/scope_guard.h
  src/base/status.cc
  src/base/status.h
  src/base/string_util.h
)

add_library(${PROJECT_NAME} ${SOURCES})
add_library(pmt::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES
  LINKER_LANGUAGE CXX
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS NO)

target_include_directories(${PROJECT_NAME}
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)

if(ENABLE_TESTS)
  enable_testing()
  add_subdirectory(test)
endif()

export(TARGETS ${PROJECT_NAME}
  NAMESPACE pmt:: FILE cmake/${PROJECT_NAME}Config.cmake)
export(PACKAGE ${PROJECT_NAME})

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}Targets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  BUNDLE  DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(DIRECTORY include DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

include(CMakePackageConfigHelpers)
write_basic_package_version_file(cmake/${PROJECT_NAME}ConfigVersion.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion)

