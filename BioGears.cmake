cmake_minimum_required(VERSION 3.2)

project(BioGears)

# Policy to address @foo@ variable expansion
if(POLICY CMP0053)
  cmake_policy(SET CMP0053 NEW)
endif()

set(BioGears_VERSION_MAJOR 6)
set(BioGears_VERSION_MINOR 2)
set(BioGears_VERSION_PATCH 0)
set(BioGears_VERSION "${BioGears_VERSION_MAJOR}.${BioGears_VERSION_MINOR}.${BioGears_VERSION_PATCH}")



set(CMAKE_CONFIGURATION_TYPES Debug Release RelWithDebInfo CACHE TYPE INTERNAL FORCE )
if(MSVC)  
  set(CMAKE_CXX_FLAGS_DEBUG "/D_DEBUG /MDd /Zi /Ob2 /Oi /Od /RTC1" CACHE TYPE INTERNAL FORCE)
endif()

if(MINGW)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,--kill-at -std=gnu++0x")#turn on C++11
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--kill-at")
endif()

if(APPLE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")
endif()

if(CMAKE_GENERATOR STREQUAL "Unix Makefiles")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()
if(UNIX)
    set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_RPATH}:\$ORIGIN")
endif()

set(CMAKE_CXX_STANDARD_LIBRARIES "" CACHE TYPE INTERNAL FORCE)
set(CMAKE_C_STANDARD_LIBRARIES "" CACHE TYPE INTERNAL FORCE)

if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
  message( STATUS "64 bits compiler detected" )
  set( EX_PLATFORM 64 )
  set( EX_CONFIG "64" )
  set(FIND_LIBRARY_USE_LIB64_PATHS ON)
else( CMAKE_SIZEOF_VOID_P EQUAL 8 ) 
  message( STATUS "32 bits compiler detected" )
  set( EX_PLATFORM 32 )
  set( EX_CONFIG "" )
  set(FIND_LIBRARY_USE_LIB64_PATHS OFF)
endif( CMAKE_SIZEOF_VOID_P EQUAL 8 )


set(eigen_DIR ${CMAKE_BINARY_DIR}/eigen/install)
set(log4cpp_DIR ${CMAKE_BINARY_DIR}/log4cpp/install)
set(xsd_DIR ${CMAKE_BINARY_DIR}/xsd/install)
set(xerces_DIR ${CMAKE_BINARY_DIR}/xerces/install)
set(dirent_DIR ${CMAKE_BINARY_DIR}/dirent/install)

ADD_SUBDIRECTORY(schema)
ADD_SUBDIRECTORY(cdm)
ADD_SUBDIRECTORY(engine)
#ADD_SUBDIRECTORY(test)
