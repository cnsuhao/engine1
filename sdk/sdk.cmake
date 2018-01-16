project(PulseSDK)

# If you want to build your own CMake project for your code that uses Pulse
# Check out this wiki article to get started : 
# https://gitlab.kitware.com/physiology/engine/wikis/how-to-connect-to-pulse


file(GLOB SRC_FILES
  "howto/cpp/*.h"
  "howto/cpp/*.cpp"
)
source_group("" FILES ${SRC_FILES})
set(SOURCE ${SRC_FILES})
add_executable(HowToDriver ${SOURCE})

# Preprocessor Definitions and Include Paths
target_include_directories(HowToDriver PRIVATE ${CMAKE_BINARY_DIR}/schema/cpp)
target_include_directories(HowToDriver PRIVATE ${CMAKE_BINARY_DIR}/schema/cpp/bind)
target_include_directories(HowToDriver PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../engine/cpp)
target_include_directories(HowToDriver PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../cdm/cpp)
target_include_directories(HowToDriver PRIVATE ${EIGEN3_INCLUDE_DIR})
target_include_directories(HowToDriver PRIVATE ${LOG4CPP_INCLUDE_DIR})
target_include_directories(HowToDriver PRIVATE ${PROTOBUF_INCLUDE_DIR})

# Dependent Libraries
target_link_libraries(HowToDriver PulseEngine)


IF(UNIX)
    SET(CMAKE_INSTLL_RPATH "${CMAKE_INSTALL_RPATH}:\$ORIGIN")
ENDIF()

add_custom_command(TARGET HowToDriver POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E make_directory ${INSTALL_BIN}/${CONFIGURATION}${EX_CONFIG}
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:HowToDriver> ${INSTALL_BIN}/${CONFIGURATION}${EX_CONFIG})
