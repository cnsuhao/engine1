# Files in the project
add_executable(BioGearsScenarioDriver engine/cpp/BioGearsScenarioDriver.cpp
                                      engine/cpp/BioGearsScenarioDriver.h
                                      engine/cpp/Verification.cpp
                                      engine/cpp/Verification.h)

set_target_properties(BioGearsScenarioDriver PROPERTIES COMPILE_FLAGS -pthread LINK_FLAGS -pthread)

# Preprocessor Definitions and Include Paths
target_include_directories(BioGearsScenarioDriver PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/cpp)
target_include_directories(BioGearsScenarioDriver PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../cdm/cpp)
target_include_directories(BioGearsScenarioDriver PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../schema/cpp)
target_include_directories(BioGearsScenarioDriver PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../lib/log4cpp/include)
target_include_directories(BioGearsScenarioDriver PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../lib/Eigen-3.3.1)
target_include_directories(BioGearsScenarioDriver PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../lib/${XERCES_VER}/src)
target_include_directories(BioGearsScenarioDriver PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../lib/${XSD_VER}/libxsd)

# Dependent Libraries
target_link_libraries(BioGearsScenarioDriver BioGearsEngine)
# Generate cxx/hxx files from xsd
# Copy to the bin

IF(UNIX)
    SET(CMAKE_INSTLL_RPATH "${CMAKE_INSTALL_RPATH}:\$ORIGIN")
ENDIF()

