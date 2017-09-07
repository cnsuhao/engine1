if(NOT MSVC)
  return()
endif()


add_library(PulseCSharp SHARED engine/csharp/PulseEngine.h
                               engine/csharp/PulseEngine.cpp)

target_include_directories(PulseCSharp PRIVATE ${CMAKE_BINARY_DIR}/schema/cpp/)
target_include_directories(PulseCSharp PRIVATE ${CMAKE_BINARY_DIR}/schema/cpp/bind/)
target_include_directories(PulseCSharp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/engine/cpp)
target_include_directories(PulseCSharp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/cdm/cpp)
target_include_directories(PulseCSharp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/test/engine/cpp)
target_include_directories(PulseCSharp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/test/cdm/cpp)
target_include_directories(PulseCSharp PRIVATE ${EIGEN3_INCLUDE_DIR})
target_include_directories(PulseCSharp PRIVATE ${LOG4CPP_INCLUDE_DIR})
target_include_directories(PulseCSharp PRIVATE ${PROTOBUF_INCLUDE_DIR})

set(PulseCSharp_FLAGS "/clr /EHa")
set_target_properties(PulseCSharp PROPERTIES COMPILE_FLAGS "${PulseCSharp_FLAGS}" PREFIX "")

target_link_libraries(PulseCSharp PulseEngine)

add_custom_command(TARGET PulseCSharp POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E make_directory ${INSTALL_BIN}/${CONFIGURATION}${EX_CONFIG}
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:PulseCSharp> ${INSTALL_BIN}/${CONFIGURATION}${EX_CONFIG})

  install(TARGETS PulseJNI 
          RUNTIME CONFIGURATIONS Release DESTINATION ${INSTALL_BIN}/release${EX_CONFIG}
          LIBRARY CONFIGURATIONS Release DESTINATION ${INSTALL_BIN}/release${EX_CONFIG})
  install(TARGETS PulseJNI 
          RUNTIME CONFIGURATIONS Debug DESTINATION ${INSTALL_BIN}/debug${EX_CONFIG}
          LIBRARY CONFIGURATIONS Debug DESTINATION ${INSTALL_BIN}/debug${EX_CONFIG})
  install(TARGETS PulseJNI 
          RUNTIME CONFIGURATIONS RelWithDebInfo DESTINATION ${INSTALL_BIN}/relwithdebinfo${EX_CONFIG}
          LIBRARY CONFIGURATIONS RelWithDebInfo DESTINATION ${INSTALL_BIN}/relwithdebinfo${EX_CONFIG})

