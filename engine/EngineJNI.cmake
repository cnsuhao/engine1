source_group("" FILES cpp/BioGearsEngineJNI.h
                      cpp/BioGearsEngineJNI.cpp)

add_library(BioGearsEngineJNI SHARED cpp/BioGearsEngineJNI.h
                                     cpp/BioGearsEngineJNI.cpp)
find_package(JNI REQUIRED)
target_include_directories(BioGearsEngineJNI PRIVATE ${JNI_INCLUDE_DIRS})
target_include_directories(BioGearsEngineJNI PRIVATE ${CMAKE_BINARY_DIR}/schema/cpp/)
target_include_directories(BioGearsEngineJNI PRIVATE ${CMAKE_BINARY_DIR}/schema/cpp/bind/)
target_include_directories(BioGearsEngineJNI PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/cpp)
target_include_directories(BioGearsEngineJNI PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../cdm/cpp)
target_include_directories(BioGearsEngineJNI PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../test/engine/cpp)
target_include_directories(BioGearsEngineJNI PRIVATE ${EIGEN3_INCLUDE_DIR})
target_include_directories(BioGearsEngineJNI PRIVATE ${LOG4CPP_INCLUDE_DIR})
target_include_directories(BioGearsEngineJNI PRIVATE ${PROTOBUF_INCLUDE_DIR})

set(BioGearsEngineJNI_FLAGS)
set_target_properties(BioGearsEngineJNI PROPERTIES COMPILE_FLAGS "${BioGearsEngineJNI_FLAGS}" PREFIX "")

if(APPLE)
    set_target_properties(CommonDataModelJNI PROPERTIES MACOSX_RPATH ON)
endif()

target_link_libraries(BioGearsEngineJNI BioGearsEngineUnitTests)

add_custom_command(TARGET BioGearsEngineJNI POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E make_directory ${INSTALL_BIN}/${CONFIGURATION}${EX_CONFIG}
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:BioGearsEngineJNI> ${INSTALL_BIN}/${CONFIGURATION}${EX_CONFIG})
if(WIN32)# Copy dll files to the bin
  install(TARGETS BioGearsEngineJNI 
          RUNTIME CONFIGURATIONS Release DESTINATION ${INSTALL_BIN}/release${EX_CONFIG}
          LIBRARY CONFIGURATIONS Release DESTINATION ${INSTALL_BIN}/release${EX_CONFIG})
  install(TARGETS BioGearsEngineJNI 
          RUNTIME CONFIGURATIONS Debug DESTINATION ${INSTALL_BIN}/debug${EX_CONFIG}
          LIBRARY CONFIGURATIONS Debug DESTINATION ${INSTALL_BIN}/debug${EX_CONFIG})
  install(TARGETS BioGearsEngineJNI 
          RUNTIME CONFIGURATIONS RelWithDebInfo DESTINATION ${INSTALL_BIN}/relwithdebinfo${EX_CONFIG}
          LIBRARY CONFIGURATIONS RelWithDebInfo DESTINATION ${INSTALL_BIN}/relwithdebinfo${EX_CONFIG})
else()# Copy so files to the bin
  install(TARGETS BioGearsEngineJNI 
          LIBRARY CONFIGURATIONS Release DESTINATION ${INSTALL_BIN}/release${EX_CONFIG})
  install(TARGETS BioGearsEngineJNI 
          LIBRARY CONFIGURATIONS Debug DESTINATION ${INSTALL_BIN}/debug${EX_CONFIG})
  install(TARGETS BioGearsEngineJNI 
          LIBRARY CONFIGURATIONS RelWithDebInfo DESTINATION ${INSTALL_BIN}/relwithdebinfo${EX_CONFIG})
endif()
