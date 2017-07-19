# Files in the project (Relative to this CMAKE file)
file(GLOB BIOGEARS_TEST_FILES
  "engine/cpp/*.h"
  "engine/cpp/*.cpp"
)
set(SOURCE ${BIOGEARS_TEST_FILES})
source_group("" FILES ${BIOGEARS_TEST_FILES})
# The DLL we are building
add_library(BioGearsEngineUnitTests SHARED ${SOURCE})
# Preprocessor Definitions and Include Paths
target_include_directories(BioGearsEngineUnitTests PRIVATE ${CMAKE_BINARY_DIR}/schema/cpp)
target_include_directories(BioGearsEngineUnitTests PRIVATE ${CMAKE_BINARY_DIR}/schema/cpp/bind)
target_include_directories(BioGearsEngineUnitTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/cdm/cpp)
target_include_directories(BioGearsEngineUnitTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../cdm/cpp)
target_include_directories(BioGearsEngineUnitTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/engine/cpp)
target_include_directories(BioGearsEngineUnitTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../engine/cpp)
target_include_directories(BioGearsEngineUnitTests PRIVATE ${EIGEN3_INCLUDE_DIR})
target_include_directories(BioGearsEngineUnitTests PRIVATE ${LOG4CPP_INCLUDE_DIR})
target_include_directories(BioGearsEngineUnitTests PRIVATE ${PROTOBUF_INCLUDE_DIR})

set(ENGINE_TEST_FLAGS)
set(ENGINE_TEST_FLAGS "${ENGINE_TEST_FLAGS} -D TEST_EXPORTS")
set(ENGINE_TEST_FLAGS "${ENGINE_TEST_FLAGS} -D UNICODE")
set(ENGINE_TEST_FLAGS "${ENGINE_TEST_FLAGS} -D _UNICODE")
set_target_properties(BioGearsEngineUnitTests PROPERTIES COMPILE_FLAGS "${ENGINE_TEST_FLAGS}" PREFIX "")

IF(APPLE)
    set_target_properties(BioGearsEngineUnitTests PROPERTIES MACOSX_RPATH ON)
ENDIF()

# Dependent Libraries
target_link_libraries(BioGearsEngineUnitTests BioGearsEngine)

add_custom_command(TARGET BioGearsEngineUnitTests POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E make_directory ${INSTALL_BIN}/${CONFIGURATION}${EX_CONFIG}
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:BioGearsEngineUnitTests> ${INSTALL_BIN}/${CONFIGURATION}${EX_CONFIG})
if(WIN32)# Copy dll files to the bin
  install(TARGETS BioGearsEngineUnitTests 
          RUNTIME CONFIGURATIONS Release DESTINATION ${INSTALL_BIN}/release${EX_CONFIG}
          LIBRARY CONFIGURATIONS Release DESTINATION ${INSTALL_BIN}/release${EX_CONFIG})
  install(TARGETS BioGearsEngineUnitTests 
          RUNTIME CONFIGURATIONS Debug DESTINATION ${INSTALL_BIN}/debug${EX_CONFIG}
          LIBRARY CONFIGURATIONS Debug DESTINATION ${INSTALL_BIN}/debug${EX_CONFIG})
  install(TARGETS BioGearsEngineUnitTests 
          RUNTIME CONFIGURATIONS RelWithDebInfo DESTINATION ${INSTALL_BIN}/relwithdebinfo${EX_CONFIG}
          LIBRARY CONFIGURATIONS RelWithDebInfo DESTINATION ${INSTALL_BIN}/relwithdebinfo${EX_CONFIG})
else()# Copy so files to the bin
  install(TARGETS BioGearsEngineUnitTests 
          LIBRARY CONFIGURATIONS Release DESTINATION ${INSTALL_BIN}/release${EX_CONFIG})
  install(TARGETS BioGearsEngineUnitTests 
          LIBRARY CONFIGURATIONS Debug DESTINATION ${INSTALL_BIN}/debug${EX_CONFIG})
  install(TARGETS BioGearsEngineUnitTests 
          LIBRARY CONFIGURATIONS RelWithDebInfo DESTINATION ${INSTALL_BIN}/relwithdebinfo${EX_CONFIG})
endif()
