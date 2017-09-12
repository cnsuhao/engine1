
find_package(Java REQUIRED)
include(UseJava)
# TODO put a USE_JAVA option in (you would get no JNI, jar, and test suite, but maybe you just want the C++ SDK)
# Java Compiling

add_library(PulseJNI SHARED cdm/cpp/CommonDataModelJNI.cpp
                            engine/cpp/PulseEngineJNI.h
                            engine/cpp/PulseEngineJNI.cpp)
find_package(JNI REQUIRED)
target_include_directories(PulseJNI PRIVATE ${JNI_INCLUDE_DIRS})
target_include_directories(PulseJNI PRIVATE ${CMAKE_BINARY_DIR}/schema/cpp/)
target_include_directories(PulseJNI PRIVATE ${CMAKE_BINARY_DIR}/schema/cpp/bind/)
target_include_directories(PulseJNI PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/engine/cpp)
target_include_directories(PulseJNI PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/cdm/cpp)
target_include_directories(PulseJNI PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/test/engine/cpp)
target_include_directories(PulseJNI PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/test/cdm/cpp)
target_include_directories(PulseJNI PRIVATE ${EIGEN3_INCLUDE_DIR})
target_include_directories(PulseJNI PRIVATE ${LOG4CPP_INCLUDE_DIR})
target_include_directories(PulseJNI PRIVATE ${PROTOBUF_INCLUDE_DIR})

set(PulseJNI_FLAGS)
set_target_properties(PulseJNI PROPERTIES COMPILE_FLAGS "${PulseJNI_FLAGS}" PREFIX "")

if(APPLE)
    set_target_properties(PulseJNI PROPERTIES MACOSX_RPATH ON)
endif()

target_link_libraries(PulseJNI PulseEngineUnitTests)
target_link_libraries(PulseJNI CommonDataModelUnitTests)

add_custom_command(TARGET PulseJNI POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E make_directory ${INSTALL_BIN}/${CONFIGURATION}${EX_CONFIG}
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:PulseJNI> ${INSTALL_BIN}/${CONFIGURATION}${EX_CONFIG})
if(WIN32)# Copy dll files to the bin
  install(TARGETS PulseJNI 
          RUNTIME CONFIGURATIONS Release DESTINATION ${INSTALL_BIN}/release${EX_CONFIG}
          LIBRARY CONFIGURATIONS Release DESTINATION ${INSTALL_LIB}/release${EX_CONFIG}
          ARCHIVE CONFIGURATIONS Release DESTINATION ${INSTALL_LIB}/release${EX_CONFIG})
  install(TARGETS PulseJNI 
          RUNTIME CONFIGURATIONS Debug DESTINATION ${INSTALL_BIN}/debug${EX_CONFIG}
          LIBRARY CONFIGURATIONS Debug DESTINATION ${INSTALL_LIB}/debug${EX_CONFIG}
          ARCHIVE CONFIGURATIONS Debug DESTINATION ${INSTALL_LIB}/debug${EX_CONFIG})
  install(TARGETS PulseJNI 
          RUNTIME CONFIGURATIONS RelWithDebInfo DESTINATION ${INSTALL_BIN}/relwithdebinfo${EX_CONFIG}
          LIBRARY CONFIGURATIONS RelWithDebInfo DESTINATION ${INSTALL_LIB}/relwithdebinfo${EX_CONFIG}
          ARCHIVE CONFIGURATIONS RelWithDebInfo DESTINATION ${INSTALL_LIB}/relwithdebinfo${EX_CONFIG})
else()# Copy so files to the bin
  install(TARGETS PulseJNI 
          LIBRARY CONFIGURATIONS Release DESTINATION ${INSTALL_BIN}/release${EX_CONFIG})
  install(TARGETS PulseJNI 
          LIBRARY CONFIGURATIONS Debug DESTINATION ${INSTALL_BIN}/debug${EX_CONFIG})
  install(TARGETS PulseJNI 
          LIBRARY CONFIGURATIONS RelWithDebInfo DESTINATION ${INSTALL_BIN}/relwithdebinfo${EX_CONFIG})
endif()


file(GLOB_RECURSE JAVA_FILES 
  "${CMAKE_BINARY_DIR}/schema/java/*.java"
  "${CMAKE_BINARY_DIR}/../protobuf/src/protobuf/java/core/src/main/java/*.java"
  "${CMAKE_SOURCE_DIR}/cdm/java/*.java"
  "${CMAKE_SOURCE_DIR}/engine/java/*.java"
  "${CMAKE_SOURCE_DIR}/test/cdm/java/*.java"
  "${CMAKE_SOURCE_DIR}/test/engine/java/*.java"
  "${CMAKE_SOURCE_DIR}/test/driver/java/*.java")
add_jar(PulseJava ${JAVA_FILES}
    INCLUDE_JARS 
      ${CMAKE_SOURCE_DIR}/jar/jcommon-1.0.16.jar
      ${CMAKE_SOURCE_DIR}/jar/jdom-2.0.2.jar
      ${CMAKE_SOURCE_DIR}/jar/jfreechart-1.0.13.jar
      ${CMAKE_SOURCE_DIR}/jar/guava-11.0.2.jar
      ${CMAKE_SOURCE_DIR}/jar/log4j-1.2.17.jar
      ${CMAKE_SOURCE_DIR}/jar/poi-3.13-20150929.jar
      ${CMAKE_SOURCE_DIR}/jar/poi-ooxml-3.13-20150929.jar
      ${CMAKE_SOURCE_DIR}/jar/poi-ooxml-schemas-3.13-20150929.jar
      ${CMAKE_SOURCE_DIR}/jar/pdfbox-2.0.0-RC3.jar
      ${CMAKE_SOURCE_DIR}/jar/reflections-0.9.9-RC1-uberjar.jar
      ${CMAKE_SOURCE_DIR}/jar/zip4j-1.3.1.jar
    OUTPUT_NAME Pulse)
get_target_property(_jarFile PulseJava JAR_FILE)
add_custom_command(TARGET PulseJava POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${INSTALL_BIN}
    COMMAND ${CMAKE_COMMAND} -E copy ${_jarFile} ${INSTALL_BIN})
install_jar(PulseJava ${INSTALL_BIN})
