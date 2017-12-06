if(NOT MSVC)
  return()
endif()


set( PULSE_BUILD_CLR "ON" CACHE BOOL "Build the CLR interface" )


add_library(PulseCLR SHARED engine/clr/PulseEngine.h
                            engine/clr/PulseEngine.cpp)

target_include_directories(PulseCLR PRIVATE ${CMAKE_BINARY_DIR}/schema/cpp/)
target_include_directories(PulseCLR PRIVATE ${CMAKE_BINARY_DIR}/schema/cpp/bind/)
target_include_directories(PulseCLR PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/engine/cpp)
target_include_directories(PulseCLR PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/cdm/cpp)
target_include_directories(PulseCLR PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/test/engine/cpp)
target_include_directories(PulseCLR PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/test/cdm/cpp)
target_include_directories(PulseCLR PRIVATE ${EIGEN3_INCLUDE_DIR})
target_include_directories(PulseCLR PRIVATE ${LOG4CPP_INCLUDE_DIR})
target_include_directories(PulseCLR PRIVATE ${PROTOBUF_INCLUDE_DIR})

set(PulseCLR_FLAGS "/clr /EHa")
string( REPLACE "/RTC1" "" CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG} )
set_target_properties(PulseCLR PROPERTIES COMPILE_FLAGS "${PulseCLR_FLAGS}" PREFIX "")
message(STATUS "PulseCLR COMPILE_FLAGS : ${CMAKE_CXX_FLAGS_DEBUG}")

target_link_libraries(PulseCLR PulseEngine)

add_custom_command(TARGET PulseCLR POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E make_directory ${INSTALL_BIN}/${CONFIGURATION}${EX_CONFIG}
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:PulseCLR> ${INSTALL_BIN}/${CONFIGURATION}${EX_CONFIG})

                   
if(PULSE_BUILD_CLR)
  install(TARGETS PulseCLR 
          RUNTIME CONFIGURATIONS Release DESTINATION ${INSTALL_BIN}/release${EX_CONFIG}
          LIBRARY CONFIGURATIONS Release DESTINATION ${INSTALL_LIB}/release${EX_CONFIG}
          ARCHIVE CONFIGURATIONS Release DESTINATION ${INSTALL_LIB}/release${EX_CONFIG})
  install(TARGETS PulseCLR 
          RUNTIME CONFIGURATIONS Debug DESTINATION ${INSTALL_BIN}/debug${EX_CONFIG}
          LIBRARY CONFIGURATIONS Debug DESTINATION ${INSTALL_LIB}/debug${EX_CONFIG}
          ARCHIVE CONFIGURATIONS Debug DESTINATION ${INSTALL_LIB}/debug${EX_CONFIG})
  install(TARGETS PulseCLR 
          RUNTIME CONFIGURATIONS RelWithDebInfo DESTINATION ${INSTALL_BIN}/relwithdebinfo${EX_CONFIG}
          LIBRARY CONFIGURATIONS RelWithDebInfo DESTINATION ${INSTALL_LIB}/relwithdebinfo${EX_CONFIG}
          ARCHIVE CONFIGURATIONS RelWithDebInfo DESTINATION ${INSTALL_LIB}/relwithdebinfo${EX_CONFIG})
else()
  set_target_properties(PulseCLR PROPERTIES EXCLUDE_FROM_ALL 1 EXCLUDE_FROM_DEFAULT_BUILD 1)
endif()