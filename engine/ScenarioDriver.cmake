# Files in the project
add_executable(PulseScenarioDriver cpp/PulseScenarioDriver.cpp
                                   cpp/PulseScenarioDriver.h)

#set_target_properties(PulseScenarioDriver PROPERTIES COMPILE_FLAGS -pthread LINK_FLAGS -pthread)

# Preprocessor Definitions and Include Paths
target_include_directories(PulseScenarioDriver PRIVATE ${CMAKE_BINARY_DIR}/schema/cpp)
target_include_directories(PulseScenarioDriver PRIVATE ${CMAKE_BINARY_DIR}/schema/cpp/bind)
target_include_directories(PulseScenarioDriver PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/cpp)
target_include_directories(PulseScenarioDriver PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../cdm/cpp)
target_include_directories(PulseScenarioDriver PRIVATE ${EIGEN3_INCLUDE_DIR})
target_include_directories(PulseScenarioDriver PRIVATE ${LOG4CPP_INCLUDE_DIR})
target_include_directories(PulseScenarioDriver PRIVATE ${PROTOBUF_INCLUDE_DIR})

# Dependent Libraries
target_link_libraries(PulseScenarioDriver PulseEngine)

IF(UNIX)
    SET(CMAKE_INSTLL_RPATH "${CMAKE_INSTALL_RPATH}:\$ORIGIN")
ENDIF()

add_custom_command(TARGET PulseScenarioDriver POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E make_directory ${INSTALL_BIN}/${CONFIGURATION}${EX_CONFIG}
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:PulseScenarioDriver> ${INSTALL_BIN}/${CONFIGURATION}${EX_CONFIG})

install(TARGETS PulseScenarioDriver 
        RUNTIME CONFIGURATIONS Release DESTINATION ${INSTALL_BIN}/release${EX_CONFIG})
install(TARGETS PulseScenarioDriver 
        RUNTIME CONFIGURATIONS Debug DESTINATION ${INSTALL_BIN}/debug${EX_CONFIG})
install(TARGETS PulseScenarioDriver 
        RUNTIME CONFIGURATIONS RelWithDebInfo DESTINATION ${INSTALL_BIN}/relwithdebinfo${EX_CONFIG})
