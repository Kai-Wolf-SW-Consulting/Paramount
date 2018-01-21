# Copyright (c) 2017, Kai Wolf. All rights reserved.
# Use of this source code is governed by a personal license that can be
# found in the LICENSE file in the top directory.

cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

project(Paramount VERSION 1.0 LANGUAGES CXX)
set(COMPANY    "Kai Wolf - SW Consulting")
set(COPYRIGHT  "Copyright (c) 2017, Kai Wolf. All rights reserved.")
set(IDENTIFIER "me.kai-wolf")

list(APPEND CMAKE_MODULE_PATH
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(ParamountUtils)

option(BUILD_TESTING "Build with tests" ON)
option(ENABLE_ADDRESS_SANITIZER "Build with address sanitizer" OFF)
check_sanitize_prerequisites(ENABLE_ADDRESS_SANITIZER)

option(ENABLE_THREAD_SANITIZER "Build with thread sanitizer" OFF)
check_sanitize_prerequisites(ENABLE_THREAD_SANITIZER)

option(ENABLE_UB_SANITIZER "Build with undefined behaviour sanitizer" OFF)
check_sanitize_prerequisites(ENABLE_UB_SANITIZER)

option(ENABLE_IWYU "Use include-what-you-use for checking includes" OFF)
if(ENABLE_IWYU)
  find_program(IWYU_EXE NAMES include-what-you-use iwyu
    DOC "Path to include-what-you-use executable")
  if(IWYU_EXE)
    message(STATUS "Found include-what-you-use: ${IWYU_EXE}")
    set(IWYU_OPTIONS
      ${IWYU_EXE} -Xiwyu --mapping_file=${CMAKE_CURRENT_SOURCE_DIR}/iwyu.imp)
  endif()
endif()

option(ENABLE_CLANG_TIDY "Build with clang-tidy enabled" OFF)
if(ENABLE_CLANG_TIDY)
  find_program(CLANG_TIDY_EXE NAMES clang-tidy
    DOC "Path to clang-tidy executable")
  if(CLANG_TIDY_EXE)
    message(STATUS "Found clang-tidy: ${CLANG_TIDY_EXE}")
  endif()
endif()

option(ENABLE_COVERAGE "Build with code coverage information" OFF)
if(ENABLE_COVERAGE)
  if(NOT CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR
     NOT CMAKE_SYSTEM_NAME STREQUAL "Linux" OR
     NOT CMAKE_BUILD_TYPE MATCHES "Debug")
    message(WARNING "ENABLE_COVERAGE is not supported for this configuration")
  endif()
endif()

find_package(Boost 1.60.0 EXACT REQUIRED COMPONENTS filesystem system thread)
find_package(Qt5 5.10.0 EXACT REQUIRED COMPONENTS Core Gui Widgets)
find_package(GTest 1.8.0 EXACT REQUIRED)

add_subdirectory(thirdparty)

set(SOURCES
  src/base/array_size.h
  src/base/callback.h
  src/base/callback_impl.h
  src/base/callback_types.h
  src/base/check.h
  src/base/cmdline_flags.cc
  src/base/cmdline_flags.h
  $<$<NOT:$<PLATFORM_ID:Windows>>:src/base/environment.cc>
  $<$<NOT:$<PLATFORM_ID:Windows>>:src/base/environment.h>
  src/base/generate_callback_impl.py
  src/base/integral_types.h
  src/base/logging.cc
  src/base/logging.h
  src/base/macros.h
  src/base/rw_protected.h
  src/base/scope_guard.h
  src/base/status.cc
  src/base/status.h)

add_library(${PROJECT_NAME} ${SOURCES})
add_library(pmt::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_compile_features(${PROJECT_NAME}
  PUBLIC cxx_std_14)

if(ENABLE_IWYU)
  set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_INCLUDE_WHAT_YOU_USE ${IWYU_OPTIONS})
endif()

if(ENABLE_CLANG_TIDY)
  set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_CLANG_TIDY ${CLANG_TIDY_EXE})
endif()

if(ENABLE_COVERAGE)
  target_compile_options(${PROJECT_NAME} PUBLIC
    -fprofile-arcs -ftest-coverage)
endif()

if(ENABLE_ADDRESS_SANITIZER)
  set(_ASAN_FLAGS -fno-omit-frame-pointer -fsanitize=address)
  target_compile_options(${PROJECT_NAME} PUBLIC ${_ASAN_FLAGS})
  target_link_libraries(${PROJECT_NAME} PUBLIC ${_ASAN_FLAGS})
endif()

if(ENABLE_THREAD_SANITIZER)
  set(_MSAN_FLAGS -fno-omit-frame-pointer -fsanitize=thread)
  target_compile_options(${PROJECT_NAME} PUBLIC ${_MSAN_FLAGS})
  target_link_libraries(${PROJECT_NAME} PUBLIC ${_MSAN_FLAGS})
endif()

if(ENABLE_UB_SANITIZER)
  set(_UB_FLAGS -fno-omit-frame-pointer -fsanitize=undefined)
  target_compile_options(${PROJECT_NAME} PUBLIC ${_UB_FLAGS})
  target_link_libraries(${PROJECT_NAME} PUBLIC ${_UB_FLAGS})
endif()

target_include_directories(${PROJECT_NAME}
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)

add_executable(main src/main.cc)
target_link_libraries(main Qt5::Widgets)

if(BUILD_TESTING)
  enable_testing()
  add_subdirectory(test)
endif()

# Export the package for use from the build tree
export(TARGETS ${PROJECT_NAME} NAMESPACE pmt:: FILE cmake/${PROJECT_NAME}Targets.cmake)
export(PACKAGE ${PROJECT_NAME})

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  cmake/${PROJECT_NAME}ConfigVersion.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion)

configure_package_config_file(
  cmake/${PROJECT_NAME}Config.cmake.in
  cmake/${PROJECT_NAME}Config.cmake
  INSTALL_DESTINATION lib/cmake/)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}Targets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  BUNDLE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/cmake/${PROJECT_NAME}Config.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/cmake/${PROJECT_NAME}ConfigVersion.cmake
  DESTINATION lib/cmake/)

install(EXPORT ${PROJECT_NAME}Targets
  NAMESPACE pmt:: DESTINATION lib/cmake/)
