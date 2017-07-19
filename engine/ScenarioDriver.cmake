# Files in the project
add_executable(ScenarioDriver cpp/BioGearsScenarioDriver.cpp
                                  cpp/BioGearsScenarioDriver.h
                                  cpp/Verification.cpp
                                  cpp/Verification.h)

set_target_properties(ScenarioDriver PROPERTIES COMPILE_FLAGS -pthread LINK_FLAGS -pthread)

# Preprocessor Definitions and Include Paths
target_include_directories(ScenarioDriver PRIVATE ${CMAKE_BINARY_DIR}/schema/cpp)
target_include_directories(ScenarioDriver PRIVATE ${CMAKE_BINARY_DIR}/schema/cpp/bind)
target_include_directories(ScenarioDriver PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/cpp)
target_include_directories(ScenarioDriver PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../cdm/cpp)
target_include_directories(ScenarioDriver PRIVATE ${EIGEN3_INCLUDE_DIR})
target_include_directories(ScenarioDriver PRIVATE ${LOG4CPP_INCLUDE_DIR})
target_include_directories(ScenarioDriver PRIVATE ${PROTOBUF_INCLUDE_DIR})

# Dependent Libraries
target_link_libraries(ScenarioDriver BioGearsEngine)
# Generate cxx/hxx files from xsd
# Copy to the bin

IF(UNIX)
    SET(CMAKE_INSTLL_RPATH "${CMAKE_INSTALL_RPATH}:\$ORIGIN")
ENDIF()

add_custom_command(TARGET ScenarioDriver POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E make_directory ${INSTALL_BIN}/${CONFIGURATION}${EX_CONFIG}
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:ScenarioDriver> ${INSTALL_BIN}/${CONFIGURATION}${EX_CONFIG})
install(TARGETS ScenarioDriver 
        RUNTIME CONFIGURATIONS Release DESTINATION ${INSTALL_BIN}/release${EX_CONFIG})
install(TARGETS ScenarioDriver 
        RUNTIME CONFIGURATIONS Debug DESTINATION ${INSTALL_BIN}/debug${EX_CONFIG})
install(TARGETS ScenarioDriver 
        RUNTIME CONFIGURATIONS RelWithDebInfo DESTINATION ${INSTALL_BIN}/relwithdebinfo${EX_CONFIG})
