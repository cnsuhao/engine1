# Files in the project
add_executable(BioGearsScenarioDriver cpp/BioGearsScenarioDriver.cpp
                                      cpp/BioGearsScenarioDriver.h
                                      cpp/Verification.cpp
                                      cpp/Verification.h)

set_target_properties(BioGearsScenarioDriver PROPERTIES COMPILE_FLAGS -pthread LINK_FLAGS -pthread)

# Preprocessor Definitions and Include Paths
target_include_directories(BioGearsScenarioDriver PRIVATE ${CMAKE_BINARY_DIR}/schema/cpp)
target_include_directories(BioGearsScenarioDriver PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/cpp)
target_include_directories(BioGearsScenarioDriver PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../cdm/cpp)
target_include_directories(BioGearsScenarioDriver PRIVATE ${EIGEN3_INCLUDE_DIR})
target_include_directories(BioGearsScenarioDriver PRIVATE ${LOG4CPP_INCLUDE_DIR})
target_include_directories(BioGearsScenarioDriver PRIVATE ${XercesC_INCLUDE_DIR})
target_include_directories(BioGearsScenarioDriver PRIVATE ${XSD_INCLUDE_DIR})

# Dependent Libraries
target_link_libraries(BioGearsScenarioDriver BioGearsEngine)
# Generate cxx/hxx files from xsd
# Copy to the bin

IF(UNIX)
    SET(CMAKE_INSTLL_RPATH "${CMAKE_INSTALL_RPATH}:\$ORIGIN")
ENDIF()

add_custom_command(TARGET BioGearsScenarioDriver POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E make_directory ${INSTALL_BIN}/${CONFIGURATION}${EX_CONFIG}
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:BioGearsScenarioDriver> ${INSTALL_BIN}/${CONFIGURATION}${EX_CONFIG})
install(TARGETS BioGearsScenarioDriver 
        RUNTIME CONFIGURATIONS Release DESTINATION ${INSTALL_BIN}/release${EX_CONFIG})
install(TARGETS BioGearsScenarioDriver 
        RUNTIME CONFIGURATIONS Debug DESTINATION ${INSTALL_BIN}/debug${EX_CONFIG})
install(TARGETS BioGearsScenarioDriver 
        RUNTIME CONFIGURATIONS RelWithDebInfo DESTINATION ${INSTALL_BIN}/relwithdebinfo${EX_CONFIG})
