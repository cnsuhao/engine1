# Files in the project (Relative to this CMAKE file)
source_group("" FILES driver/cpp/main.cpp)
# The DLL we are building
add_executable(UnitTestDriver driver/cpp/main.cpp)

set_target_properties(UnitTestDriver PROPERTIES COMPILE_FLAGS -pthread LINK_FLAGS -pthread)
target_include_directories(UnitTestDriver PRIVATE ${CMAKE_BINARY_DIR}/schema/cpp)
target_include_directories(UnitTestDriver PRIVATE ${CMAKE_BINARY_DIR}/schema/cpp/bind)
target_include_directories(UnitTestDriver PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/cdm/cpp)
target_include_directories(UnitTestDriver PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../cdm/cpp)
target_include_directories(UnitTestDriver PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/engine/cpp)
target_include_directories(UnitTestDriver PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../engine/cpp)
target_include_directories(UnitTestDriver PRIVATE ${EIGEN3_INCLUDE_DIR})
target_include_directories(UnitTestDriver PRIVATE ${LOG4CPP_INCLUDE_DIR})
target_include_directories(UnitTestDriver PRIVATE ${PROTOBUF_INCLUDE_DIR})
target_link_libraries(UnitTestDriver CommonDataModelUnitTests PulseEngineUnitTests)

add_custom_command(TARGET UnitTestDriver POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E make_directory ${INSTALL_BIN}/${CONFIGURATION}${EX_CONFIG}
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:UnitTestDriver> ${INSTALL_BIN}/${CONFIGURATION}${EX_CONFIG})
install(TARGETS UnitTestDriver 
        RUNTIME CONFIGURATIONS Release DESTINATION ${INSTALL_BIN}/release${EX_CONFIG})
install(TARGETS UnitTestDriver 
        RUNTIME CONFIGURATIONS Debug DESTINATION ${INSTALL_BIN}/debug${EX_CONFIG})
install(TARGETS UnitTestDriver 
        RUNTIME CONFIGURATIONS RelWithDebInfo DESTINATION ${INSTALL_BIN}/relwithdebinfo${EX_CONFIG})
