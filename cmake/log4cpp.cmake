CMAKE_MINIMUM_REQUIRED(VERSION 2.8.12)

PROJECT(log4cpp)

# Policy to address @foo@ variable expansion
if(POLICY CMP0053)
  cmake_policy(SET CMP0053 NEW)
endif()

MESSAGE(STATUS "Using files from ${log4cpp_DIR}")
# Files in the project (Relative to this CMAKE file)
SET(log4cpp_DIR )
IF(log4cpp_DIR STREQUAL "")
  SET(log4cpp_DIR "${CMAKE_BINARY_DIR}/log4cpp/src/log4cpp/")
ENDIF()
	
FILE(GLOB SOURCE
    "${log4cpp_DIR}/*.hh"
    "${log4cpp_DIR}/src/*.cpp"
    "${log4cpp_DIR}/threading/*.hh"  
)

ADD_LIBRARY(log4cpp SHARED ${SOURCE})
TARGET_INCLUDE_DIRECTORIES(log4cpp PRIVATE ${log4cpp_DIR}/include)
# Preprocessor Definitions
IF (WIN32)
  SET(FLAGS)
  SET(FLAGS "${FLAGS} -D LOG4CPP_HAS_DLL")
  SET(FLAGS "${FLAGS} -D LOG4CPP_BUILD_DLL")
  SET(FLAGS "${FLAGS} -D _CRT_SECURE_NO_WARNINGS")
#  MESSAGE(${FLAGS})
  SET_TARGET_PROPERTIES(log4cpp PROPERTIES COMPILE_FLAGS "${FLAGS}" PREFIX "")
  TARGET_LINK_LIBRARIES(log4cpp ws2_32 advapi32)
#  SET_TARGET_PROPERTIES(log4cpp PROPERTIES LINK_FLAGS /NODEFAULTLIB:msvcrt )
ENDIF (WIN32)                            

IF(APPLE)
    SET_TARGET_PROPERTIES(log4cpp PROPERTIES MACOSX_RPATH ON)
ENDIF()

# Copy to the bin
SET(CONFIG_STRING)
IF(WIN32)
  SET(CONFIG_STRING ${CMAKE_CFG_INTDIR})
ELSE()
  STRING(TOLOWER ${CMAKE_BUILD_TYPE} CONFIG_STRING)
ENDIF()

ADD_CUSTOM_COMMAND(TARGET log4cpp POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_SOURCE_DIR}/../../bin/${CONFIG_STRING}${EX_CONFIG}
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:log4cpp> ${CMAKE_CURRENT_SOURCE_DIR}/../../bin/${CONFIG_STRING}${EX_CONFIG}
)           
