# - Try to find PROTOBUF lib
#
#
# Once done this will define
#
#  PROTOBUF_FOUND - system has PROTOBUF lib
#  PROTOBUF_INCLUDE_DIR - the PROTOBUF include directory
#  PROTOBUF_LIBRARIES - the PROTOBUF libraries

set(PROTOBUF_FOUND FALSE)

find_path(PROTOBUF_INCLUDE_DIR google/protobuf/wrappers.pb.h
  PATHS
  ${CMAKE_INSTALL_PREFIX}/include
)

find_library(PROTOBUF_LIBRARIES
  NAMES libprotobuf
  PATHS 
  ${CMAKE_INSTALL_PREFIX}/lib
  PATH_SUFFIXES libprotobuf
)

if (PROTOBUF_INCLUDE_DIR AND PROTOBUF_LIBRARIES)
  set(PROTOBUF_FOUND TRUE)
  mark_as_advanced(PROTOBUF_LIBRARIES PROTOBUF_INCLUDE_DIR)
  message(STATUS "Found PROTOBUF headers at : ${PROTOBUF_INCLUDE_DIR}")
  message(STATUS "Found PROTOBUF libraries at : ${PROTOBUF_LIBRARIES}")
else()
  message(FATAL_ERROR "Could NOT find PROTOBUF library")
endif()

