cmake_minimum_required(VERSION 3.2)

set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install CACHE PATH "Install location")

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

set(CMAKE_CONFIGURATION_TYPES Debug Release RelWithDebInfo CACHE TYPE INTERNAL FORCE )
if(MSVC)  
  set(CMAKE_CXX_FLAGS_DEBUG "/D_DEBUG /MDd /Zi /Ob2 /Oi /Od /RTC1" CACHE TYPE INTERNAL FORCE)
endif()

if(MINGW)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -Wl,--kill-at -std=gnu++0x")#turn on C++11
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--kill-at")
endif()

if(APPLE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++11 -stdlib=libc++")
endif()

if(UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++11")
  set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_RPATH}:\$ORIGIN")
endif()

include(sdk.cmake)
