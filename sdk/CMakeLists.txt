cmake_minimum_required(VERSION 3.2)

project(BioGearsSDK)

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
  set(CONFIGURATION ${CMAKE_BUILD_TYPE})
endif()
string(TOLOWER ${CONFIGURATION} CONFIGURATION)

if(UNIX AND NOT APPLE)
  set(LINUX TRUE)
endif()

set(CMAKE_CONFIGURATION_TYPES Debug Release CACHE TYPE INTERNAL FORCE )

if(MSVC)
  set(CMAKE_CXX_FLAGS_DEBUG "/D_DEBUG /MDd /Zi /Ob2 /Oi /Od /RTC1" CACHE TYPE INTERNAL FORCE)
endif()

if(MINGW)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")#turn on C++11
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

file(GLOB SRC_FILES
  "howto/cpp/*.h"
  "howto/cpp/*.cpp"
)
source_group("" FILES ${SRC_FILES})
set(SOURCE ${SRC_FILES})
add_executable(HowToDriver ${SOURCE})

# Preprocessor Definitions and Include Paths
set(FLAGS)
target_include_directories(HowToDriver PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(HowToDriver PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/cdm)
set_target_properties(HowToDriver PROPERTIES COMPILE_FLAGS "${FLAGS}" PREFIX "")
# Dependent Libraries
if(MSVC)
  file(GLOB D_LIB_FILES
    "lib/debug${EX_CONFIG}/BioGearsEngine.lib"
    "lib/debug${EX_CONFIG}/CommonDataModel.lib"
    "lib/debug${EX_CONFIG}/DataModelBindings.lib"
    "lib/debug${EX_CONFIG}/log4cpp.lib"
    "lib/debug${EX_CONFIG}/xerces-c.lib"
  )
  file(GLOB O_LIB_FILES
    "lib/release${EX_CONFIG}/BioGearsEngine.lib"
    "lib/release${EX_CONFIG}/CommonDataModel.lib"
    "lib/release${EX_CONFIG}/DataModelBindings.lib"
    "lib/release${EX_CONFIG}/log4cpp.lib"
    "lib/release${EX_CONFIG}/xerces-c.lib"
  )
else(UNIX)  
  file(GLOB D_LIB_FILES
    "lib/debug${EX_CONFIG}/BioGearsEngine.so"
    "lib/debug${EX_CONFIG}/CommonDataModel.so"
    "lib/debug${EX_CONFIG}/DataModelBindings.so"
    "lib/debug${EX_CONFIG}/log4cpp.so"
    "lib/debug${EX_CONFIG}/xerces-c.so"
  )
  file(GLOB O_LIB_FILES
    "lib/release${EX_CONFIG}/BioGearsEngine.so"
    "lib/release${EX_CONFIG}/CommonDataModel.so"
    "lib/release${EX_CONFIG}/DataModelBindings.so"
    "lib/release${EX_CONFIG}/log4cpp.so"
    "lib/release${EX_CONFIG}/xerces-c.so"
  )
else()
  file(GLOB D_LIB_FILES
    "lib/debug/BioGearsEngine.lib"
    "lib/debug/CommonDataModel.lib"
    "lib/debug/DataModelBindings.lib"
    "lib/debug/log4cpp.lib"
    "lib/debug/xerces-c.lib"
  )
  file(GLOB O_LIB_FILES
    "lib/release/BioGearsEngine.lib"
    "lib/release/CommonDataModel.lib"
    "lib/release/DataModelBindings.lib"
    "lib/release/log4cpp.lib"
    "lib/release/xerces-c.lib"
  )
endif()

foreach(file ${D_LIB_FILES})
	target_link_libraries(HowToDriver debug ${file})
endforeach()
foreach(file ${O_LIB_FILES})
	target_link_libraries(HowToDriver optimized ${file})
endforeach()
