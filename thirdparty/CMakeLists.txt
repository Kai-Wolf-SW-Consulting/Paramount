# Copyright (c) 2017, Kai Wolf. All rights reserved.
# Use of this source code is governed by a personal license that can be
# found in the LICENSE file in the top directory.

add_library(thirdparty::catch INTERFACE IMPORTED GLOBAL)
set_target_properties(thirdparty::catch PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/catch)
