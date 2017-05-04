cmake_minimum_required(VERSION 3.2)

project(BioGears_SuperBuild)

# Policy to address @foo@ variable expansion
if(POLICY CMP0053)
  cmake_policy(SET CMP0053 NEW)
endif()

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

set(INSTALL_BIN ${CMAKE_SOURCE_DIR}/bin)
set(INSTALL_SDK_INC ${CMAKE_SOURCE_DIR}/sdk)
set(INSTALL_SDK_LIB ${CMAKE_SOURCE_DIR}/sdk/lib)
file(MAKE_DIRECTORY "${INSTALL_BIN}/debug${EX_CONFIG}")
file(MAKE_DIRECTORY "${INSTALL_BIN}/release${EX_CONFIG}")
file(MAKE_DIRECTORY "${INSTALL_BIN}/relwithdebinfo${EX_CONFIG}")

if(UNIX AND NOT APPLE)
  set(LINUX TRUE)
endif()

set (SUPERBUILD ON CACHE BOOL "Initial pull and build of all dependent libraries/executables")
if(SUPERBUILD)
  include(SuperBuild.cmake)
  return()
else()
  include(BioGears.cmake)
endif()
