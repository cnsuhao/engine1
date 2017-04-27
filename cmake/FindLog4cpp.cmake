# - Try to find Log4cpp lib
#
#
# Once done this will define
#
#  LOG4CPP_FOUND - system has log4cpp lib
#  LOG4CPP_INCLUDE_DIR - the log4cpp include directory
#  LOG4CPP_LIBRARIES - the log4cpp libraries

set(LOG4CPP_FOUND FALSE)

find_path(LOG4CPP_INCLUDE_DIR log4cpp/Category.hh
  PATHS
  ${CMAKE_INSTALL_PREFIX}/include
  PATH_SUFFIXES log4cpp
)

find_library(LOG4CPP_LIBRARIES
  NAMES log4cpp
  PATHS 
  ${CMAKE_INSTALL_PREFIX}/lib
  PATH_SUFFIXES log4cpp
)

if (LOG4CPP_INCLUDE_DIR AND LOG4CPP_LIBRARIES)
  set(LOG4CPP_FOUND TRUE)
  mark_as_advanced(LOG4CPP_LIBRARIES LOG4CPP_INCLUDE_DIR)
elseif()
  message(FATAL_ERROR "Could NOT find LOG4CPP library")
endif()

