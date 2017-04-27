cmake_minimum_required(VERSION 3.2)

project(BioGears)

# Policy to address @foo@ variable expansion
if(POLICY CMP0053)
  cmake_policy(SET CMP0053 NEW)
endif()

if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
  message( STATUS "64 bits compiler detected" )    
  set( EX_CONFIG "64" )
  set(FIND_LIBRARY_USE_LIB64_PATHS ON)
else( CMAKE_SIZEOF_VOID_P EQUAL 8 ) 
  message( STATUS "32 bits compiler detected" )
  set( EX_CONFIG "" )
  set(FIND_LIBRARY_USE_LIB64_PATHS OFF)
endif( CMAKE_SIZEOF_VOID_P EQUAL 8 )

SET(CONFIGURATION)
if(WIN32)
  set(CONFIGURATION ${CMAKE_CFG_INTDIR})
else()
  set(CONFIGURATION ${CMAKE_BUILD_TYPE})
endif()
string(TOLOWER ${CONFIGURATION} CONFIGURATION)

set(INSTALL_BIN ${CMAKE_SOURCE_DIR}/bin/)

## Pull and Compile dependencies
set (PULL_DEPENDENCIES false CACHE BOOL "Initial pull and build of all dependent libraries/executables")

if(PULL_DEPENDENCIES)
  include(cmake/ExternalDependencies.cmake)
elseif(NOT PULL_DEPENDENCIES)
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

  


  set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
  set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${CMAKE_BINARY_DIR}/dirent/install)  
  find_package(Dirent REQUIRED)
  set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${CMAKE_BINARY_DIR}/eigen/install)
  find_package(Eigen3 3.3.3 REQUIRED)
  set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${CMAKE_BINARY_DIR}/log4cpp/install)  
  find_package(Log4cpp REQUIRED)
  set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${CMAKE_BINARY_DIR}/xerces/install)  
  find_package(XercesC 3.1.0 REQUIRED)
  set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${CMAKE_BINARY_DIR}/xsd/install)  
  find_package(XSD REQUIRED)

  ADD_SUBDIRECTORY(schema)
  ADD_SUBDIRECTORY(cdm)
  ADD_SUBDIRECTORY(engine)
  #ADD_SUBDIRECTORY(test)
  
  # I should probably just make these a copy....error out if they are not there...
  file(GLOB DLIBS 
    ${CMAKE_BINARY_DIR}/log4cpp/install/bin/*.dll
    ${CMAKE_BINARY_DIR}/log4cpp/install/bin/*.so)
  install(FILES ${DLIBS}
    CONFIGURATIONS Release DESTINATION ${INSTALL_BIN}/release${EX_CONFIG})
  install(FILES ${DLIBS}
    CONFIGURATIONS Debug DESTINATION ${INSTALL_BIN}/debug${EX_CONFIG})
  install(FILES ${DLIBS}
    CONFIGURATIONS RelWithDeb DESTINATION ${INSTALL_BIN}/relwithdeb${EX_CONFIG})
    
  file(GLOB DLIBS 
    ${CMAKE_BINARY_DIR}/xerces/install/bin/*.dll
    ${CMAKE_BINARY_DIR}/xerces/install/bin/*.so)
  install(FILES ${DLIBS}
    CONFIGURATIONS Release DESTINATION ${INSTALL_BIN}/release${EX_CONFIG})
  install(FILES ${DLIBS}
    CONFIGURATIONS Debug DESTINATION ${INSTALL_BIN}/debug${EX_CONFIG})
  install(FILES ${DLIBS}
    CONFIGURATIONS RelWithDeb DESTINATION ${INSTALL_BIN}/relwithdeb${EX_CONFIG})    
  
endif()
