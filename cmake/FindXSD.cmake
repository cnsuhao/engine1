# - Try to find code synthesis xsd
#
#
# Once done this will define
#
#  XSD_FOUND - system has xsd
#  XSD_INCLUDE_DIR - the xsd include directory
#  XSD_EXECUTABLE - the xsd executable

set(XSD_FOUND FALSE)

find_path(XSD_INCLUDE_DIR xsd/cxx/config.hxx
  PATHS
  ${CMAKE_INSTALL_PREFIX}/include
  PATH_SUFFIXES libxsd
)

find_program(XSD_EXECUTABLE
  NAMES xsd
  PATHS 
  ${CMAKE_INSTALL_PREFIX}/bin
  PATH_SUFFIXES xsd
)

if (XSD_INCLUDE_DIR AND XSD_EXECUTABLE)
  set(XSD_FOUND TRUE)
  mark_as_advanced(XSD_EXECUTABLE XSD_INCLUDE_DIR)
elseif()
  message(FATAL_ERROR "Could NOT find XSD library")
endif()

