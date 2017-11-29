# Copyright (c) 2017, Kai Wolf. All rights reserved.
# Use of this source code is governed by a personal license that can be
# found in the LICENSE file in the top directory.

# Checks if the given |san_option| is suitable for the current setup
# Usage:
#   include(ParamountUtils)
#   check_sanitize_prerequisites(ENABLE_ADDRESS_SANITIZER)
function(check_sanitize_prerequisites san_option)
  if(${san_option})
    if(NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang" AND
       NOT CMAKE_CXX_COMPILER_ID MATCHES "GNU")
      message(WARNING "${san_option} only works with Clang or GCC")
    elseif(NOT CMAKE_BUILD_TYPE MATCHES "Debug")
      message(WARNING "${san_option} only works for debug builds")
    endif()
  endif()
endfunction()
