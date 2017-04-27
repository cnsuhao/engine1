# - Try to find dirent header
#
#
# Once done this will define
#
#  DIRENT_FOUND - system has dirent
#  DIRENT_INCLUDE_DIR - the dirent header directory

set(DIRENT_FOUND FALSE)

find_path(DIRENT_INCLUDE_DIR dirent.h
  PATHS
  ${CMAKE_INSTALL_PREFIX}/include
  PATH_SUFFIXES dirent
)


if (DIRENT_INCLUDE_DIR)
  set(DIRENT_FOUND TRUE)
  mark_as_advanced(DIRENT_INCLUDE_DIR)
elseif()
  message(FATAL_ERROR "Could NOT find dirent")
endif()

