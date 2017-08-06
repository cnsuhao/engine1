source_group("" FILES cpp/PulseEngineJNI.h
                      cpp/PulseEngineJNI.cpp)

add_library(PulseEngineJNI SHARED cpp/PulseEngineJNI.h
                                     cpp/PulseEngineJNI.cpp)
find_package(JNI REQUIRED)
target_include_directories(PulseEngineJNI PRIVATE ${JNI_INCLUDE_DIRS})
target_include_directories(PulseEngineJNI PRIVATE ${CMAKE_BINARY_DIR}/schema/cpp/)
target_include_directories(PulseEngineJNI PRIVATE ${CMAKE_BINARY_DIR}/schema/cpp/bind/)
target_include_directories(PulseEngineJNI PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/cpp)
target_include_directories(PulseEngineJNI PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../cdm/cpp)
target_include_directories(PulseEngineJNI PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../test/engine/cpp)
target_include_directories(PulseEngineJNI PRIVATE ${EIGEN3_INCLUDE_DIR})
target_include_directories(PulseEngineJNI PRIVATE ${LOG4CPP_INCLUDE_DIR})
target_include_directories(PulseEngineJNI PRIVATE ${PROTOBUF_INCLUDE_DIR})

set(PulseEngineJNI_FLAGS)
set_target_properties(PulseEngineJNI PROPERTIES COMPILE_FLAGS "${PulseEngineJNI_FLAGS}" PREFIX "")

if(APPLE)
    set_target_properties(CommonDataModelJNI PROPERTIES MACOSX_RPATH ON)
endif()

target_link_libraries(PulseEngineJNI PulseEngineUnitTests)

add_custom_command(TARGET PulseEngineJNI POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E make_directory ${INSTALL_BIN}/${CONFIGURATION}${EX_CONFIG}
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:PulseEngineJNI> ${INSTALL_BIN}/${CONFIGURATION}${EX_CONFIG})
if(WIN32)# Copy dll files to the bin
  install(TARGETS PulseEngineJNI 
          RUNTIME CONFIGURATIONS Release DESTINATION ${INSTALL_BIN}/release${EX_CONFIG}
          LIBRARY CONFIGURATIONS Release DESTINATION ${INSTALL_BIN}/release${EX_CONFIG})
  install(TARGETS PulseEngineJNI 
          RUNTIME CONFIGURATIONS Debug DESTINATION ${INSTALL_BIN}/debug${EX_CONFIG}
          LIBRARY CONFIGURATIONS Debug DESTINATION ${INSTALL_BIN}/debug${EX_CONFIG})
  install(TARGETS PulseEngineJNI 
          RUNTIME CONFIGURATIONS RelWithDebInfo DESTINATION ${INSTALL_BIN}/relwithdebinfo${EX_CONFIG}
          LIBRARY CONFIGURATIONS RelWithDebInfo DESTINATION ${INSTALL_BIN}/relwithdebinfo${EX_CONFIG})
else()# Copy so files to the bin
  install(TARGETS PulseEngineJNI 
          LIBRARY CONFIGURATIONS Release DESTINATION ${INSTALL_BIN}/release${EX_CONFIG})
  install(TARGETS PulseEngineJNI 
          LIBRARY CONFIGURATIONS Debug DESTINATION ${INSTALL_BIN}/debug${EX_CONFIG})
  install(TARGETS PulseEngineJNI 
          LIBRARY CONFIGURATIONS RelWithDebInfo DESTINATION ${INSTALL_BIN}/relwithdebinfo${EX_CONFIG})
endif()
