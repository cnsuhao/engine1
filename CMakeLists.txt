cmake_minimum_required(VERSION 3.7)
# Using SOURCE_SUBDIR which was first in 3.7

set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install CACHE PATH "Install location")

project(SuperBuild)

# Policy to address @foo@ variable expansion
if(POLICY CMP0053)
  cmake_policy(SET CMP0053 NEW)
endif()

MACRO(install_headers SRC_DIR DEST)
  file(GLOB_RECURSE HEADER_LIST 
    ${SRC_DIR}/*.h 
    ${SRC_DIR}/*.hxx
    ${SRC_DIR}/*.inl)
  foreach(HEADER ${HEADER_LIST})
    #message(STATUS "Header at ${HEADER}")
    STRING(REPLACE ${SRC_DIR}/ "" REL_DIR ${HEADER})
    #message(STATUS "Relative Path ${REL_DIR}")  
    set(FULL_LOC ${CMAKE_INSTALL_PREFIX}/include/${DEST}/${REL_DIR})
    #message(STATUS "File should goto ${FULL_LOC}")
    get_filename_component(DEST_DIR ${FULL_LOC} PATH) 
    #message(STATUS "Going to ${DEST_DIR}")
    install(FILES ${HEADER} DESTINATION ${DEST_DIR})
  endforeach()    
ENDMACRO(install_headers)

if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
  message( STATUS "64 bits compiler detected" )    
  set( EX_CONFIG "" )
  set(FIND_LIBRARY_USE_LIB64_PATHS ON)
else( CMAKE_SIZEOF_VOID_P EQUAL 8 ) 
  message( STATUS "32 bits compiler detected" )
  set( EX_CONFIG "32" )
  set(FIND_LIBRARY_USE_LIB64_PATHS OFF)
endif( CMAKE_SIZEOF_VOID_P EQUAL 8 )

SET(CONFIGURATION)
if(WIN32)
  set(CONFIGURATION ${CMAKE_CFG_INTDIR})
else()
  # Set a default build type if none was specified
  if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to 'Release' as none was specified.")
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
  endif()
  set(CONFIGURATION ${CMAKE_BUILD_TYPE})
endif()
string(TOLOWER ${CONFIGURATION} CONFIGURATION)
message(STATUS "Installing to ${CMAKE_INSTALL_PREFIX}")
set(INSTALL_BIN ${CMAKE_INSTALL_PREFIX}/bin)
set(INSTALL_LIB ${CMAKE_INSTALL_PREFIX}/lib)
file(MAKE_DIRECTORY "${INSTALL_BIN}/debug${EX_CONFIG}")
file(MAKE_DIRECTORY "${INSTALL_BIN}/release${EX_CONFIG}")
file(MAKE_DIRECTORY "${INSTALL_BIN}/relwithdebinfo${EX_CONFIG}")

if(UNIX AND NOT APPLE)
  set(LINUX TRUE)
endif()

set (SUPERBUILD ON CACHE BOOL "Initial pull and build of all dependent libraries/executables")
set (PULSE_DOWNLOAD_BASELINES OFF CACHE BOOL "Download all V&V Scenarios and their baseline result files")
if(SUPERBUILD)
  include(SuperBuild.cmake)
else()
  include(Pulse.cmake)
endif()
