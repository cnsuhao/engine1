# Files in the project (Relative to this CMAKE file)
file(GLOB PULSE_TEST_FILES
  "engine/cpp/*.h"
  "engine/cpp/*.cpp"
)
set(SOURCE ${PULSE_TEST_FILES})
source_group("" FILES ${PULSE_TEST_FILES})
# The DLL we are building
add_library(PulseEngineUnitTests ${SOURCE})
# Preprocessor Definitions and Include Paths
target_include_directories(PulseEngineUnitTests PRIVATE ${CMAKE_BINARY_DIR}/schema/cpp)
target_include_directories(PulseEngineUnitTests PRIVATE ${CMAKE_BINARY_DIR}/schema/cpp/bind)
target_include_directories(PulseEngineUnitTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/cdm/cpp)
target_include_directories(PulseEngineUnitTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../cdm/cpp)
target_include_directories(PulseEngineUnitTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/engine/cpp)
target_include_directories(PulseEngineUnitTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../engine/cpp)
target_include_directories(PulseEngineUnitTests PRIVATE ${EIGEN3_INCLUDE_DIR})
target_include_directories(PulseEngineUnitTests PRIVATE ${LOG4CPP_INCLUDE_DIR})
target_include_directories(PulseEngineUnitTests PRIVATE ${PROTOBUF_INCLUDE_DIR})

set(ENGINE_TEST_FLAGS)
set(ENGINE_TEST_FLAGS "${ENGINE_TEST_FLAGS} -D UNICODE")
set(ENGINE_TEST_FLAGS "${ENGINE_TEST_FLAGS} -D _UNICODE")
if(${BUILD_SHARED_LIBS}) 
  set(ENGINE_TEST_FLAGS "${ENGINE_TEST_FLAGS} -D SHARED_ENGINE_TEST")
endif()
set_target_properties(PulseEngineUnitTests PROPERTIES COMPILE_FLAGS "${ENGINE_TEST_FLAGS}" PREFIX "")

IF(APPLE)
    set_target_properties(PulseEngineUnitTests PROPERTIES MACOSX_RPATH ON)
ENDIF()

# Dependent Libraries
target_link_libraries(PulseEngineUnitTests PulseEngine)

add_custom_command(TARGET PulseEngineUnitTests POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E make_directory ${INSTALL_BIN}/${CONFIGURATION}${EX_CONFIG}
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:PulseEngineUnitTests> ${INSTALL_BIN}/${CONFIGURATION}${EX_CONFIG})
if(${BUILD_SHARED_LIBS})
  if(WIN32)# Copy dll files to the bin
    install(TARGETS PulseEngineUnitTests 
            RUNTIME CONFIGURATIONS Release DESTINATION ${INSTALL_BIN}/release${EX_CONFIG}
            LIBRARY CONFIGURATIONS Release DESTINATION ${INSTALL_BIN}/release${EX_CONFIG})
    install(TARGETS PulseEngineUnitTests 
            RUNTIME CONFIGURATIONS Debug DESTINATION ${INSTALL_BIN}/debug${EX_CONFIG}
            LIBRARY CONFIGURATIONS Debug DESTINATION ${INSTALL_BIN}/debug${EX_CONFIG})
    install(TARGETS PulseEngineUnitTests 
            RUNTIME CONFIGURATIONS RelWithDebInfo DESTINATION ${INSTALL_BIN}/relwithdebinfo${EX_CONFIG}
            LIBRARY CONFIGURATIONS RelWithDebInfo DESTINATION ${INSTALL_BIN}/relwithdebinfo${EX_CONFIG})
  else()# Copy so files to the bin
    install(TARGETS PulseEngineUnitTests 
            LIBRARY CONFIGURATIONS Release DESTINATION ${INSTALL_BIN}/release${EX_CONFIG})
    install(TARGETS PulseEngineUnitTests 
            LIBRARY CONFIGURATIONS Debug DESTINATION ${INSTALL_BIN}/debug${EX_CONFIG})
    install(TARGETS PulseEngineUnitTests 
            LIBRARY CONFIGURATIONS RelWithDebInfo DESTINATION ${INSTALL_BIN}/relwithdebinfo${EX_CONFIG})
  endif()
endif()
