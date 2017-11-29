# Copyright (c) 2017, Kai Wolf. All rights reserved.
# Use of this source code is governed by a personal license that can be
# found in the LICENSE file in the top directory.

# Extracts the latest git commit revision
# Usage:
#   include(GetGitCommit)
#   get_git_revision(GIT_BRANCH GIT_COMMIT)
function(get_git_revision branch commit)
  set(GIT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/.git)
  if(NOT IS_DIRECTORY ${GIT_DIR})
    message(WARNING "Could not determine git checkout")
    return()
  elseif(NOT EXISTS ${GIT_DIR}/HEAD)
    message(WARNING "Could not find git HEAD")
    return()
  endif()

  set(GIT_DATA ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/git_data)
  file(MAKE_DIRECTORY ${GIT_DATA})

  # Retrieve branch name and git commit id
  configure_file(${GIT_DIR}/HEAD ${GIT_DATA}/HEAD COPYONLY)
  file(READ ${GIT_DATA}/HEAD HEAD_CONTENTS LIMIT 1024)
  string(STRIP "${HEAD_CONTENTS}" HEAD_CONTENTS)

  if(HEAD_CONTENTS MATCHES "ref")
    string(REPLACE "ref: " "" HEAD_REF "${HEAD_CONTENTS}")
    if(EXISTS ${GIT_DIR}/${HEAD_REF})
      configure_file(${GIT_DIR}/${HEAD_REF} ${GIT_DATA}/head_ref COPYONLY)
    else()
      configure_file(${GIT_DIR}/packed-refs ${GIT_DATA}/packed_refs COPYONLY)
      file(READ ${GIT_DATA}/packed_refs PACKED_REFS)
      if(${PACKED_REFS} MATCHES "([0-9a-z]*) ${HEAD_REF}")
        set(HEAD_HASH "${CMAKE_MATCH_1}")
      endif()
    endif()
  else()
    configure_file(${GIT_DIR}/HEAD ${GIT_DATA}/head_ref COPYONLY)
  endif()

  if(NOT HEAD_HASH)
    file(READ ${GIT_DATA}/head_ref HEAD_HASH LIMIT 1024)
    string(STRIP "${HEAD_HASH}" HEAD_HASH)
  endif()

  set(${branch} ${HEAD_REF} PARENT_SCOPE)
  set(${commit} ${HEAD_HASH} PARENT_SCOPE)
endfunction()
