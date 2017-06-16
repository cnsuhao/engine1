project(Engine)

set(BUILD_SHARED_LIBS ON)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

# Policy to address @foo@ variable expansion
set(_VERSION_MAJOR 6)
set(_VERSION_MINOR 2)
set(_VERSION_PATCH 0)
set(_VERSION "${_VERSION_MAJOR}.${_VERSION_MINOR}.${_VERSION_PATCH}")

set(CMAKE_CONFIGURATION_TYPES Debug Release RelWithDebInfo CACHE TYPE INTERNAL FORCE )
if(MSVC)  
# use MT to link the runtime library statically so that MSVCR*.DLL is not required at runtime
  set(CMAKE_CXX_FLAGS_DEBUG "/D_DEBUG /MTd /Zi /Ob2 /Oi /Od /RTC1" CACHE TYPE INTERNAL FORCE)
  set(CMAKE_CXX_FLAGS_RELEASE "/MT" CACHE TYPE INTERNAL FORCE)
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/MTd" CACHE TYPE INTERNAL FORCE)
endif()

if(MINGW)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,--kill-at -std=gnu++0x")#turn on C++11
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--kill-at")
endif()

if(APPLE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")
endif()

if(UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
  set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_RPATH}:\$ORIGIN")
endif()

message(STATUS "Looking for modules here : ${CMAKE_PREFIX_PATH}")
set(CMAKE_CXX_STANDARD_LIBRARIES "" CACHE TYPE INTERNAL FORCE)
set(CMAKE_C_STANDARD_LIBRARIES "" CACHE TYPE INTERNAL FORCE)

find_package(Dirent REQUIRED)
find_package(Eigen3 3.3.3 REQUIRED)
find_package(ProtoBuf REQUIRED)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
if(MSVC)
  set(protobuf_BUILD_TESTS OFF CACHE TYPE INTERNAL FORCE)
  set(protobuf_BUILD_EXAMPLES OFF CACHE TYPE INTERNAL FORCE)
  add_subdirectory("${protobuf_DIR}/cmake" "${protobuf_DIR}-build")
  set_target_properties(libprotobuf-lite libprotoc protoc PROPERTIES EXCLUDE_FROM_ALL 1 EXCLUDE_FROM_DEFAULT_BUILD 1)
  set_target_properties (libprotobuf libprotobuf-lite libprotoc protoc js_embed PROPERTIES FOLDER protobufs)
endif()
add_subdirectory("${log4cpp_DIR}" "${log4cpp_DIR}-build")
add_subdirectory(schema)
add_subdirectory(cdm)
add_subdirectory(engine)
add_subdirectory(test)
add_subdirectory(sdk)


# TODO put a USE_JAVA option in (you would get no JNI, jar, and test suite, but maybe you just want the C++ SDK)
# Java Compiling
find_package(Java REQUIRED)
include(UseJava)
# Protobuf needs to auto generate some things needed to be used with Java

file(GLOB_RECURSE JAVA_FILES 
  "${CMAKE_BINARY_DIR}/schema/java/*.java"
  "${CMAKE_BINARY_DIR}/protobuf/src/protobuf/java/core/java/*.java"
  "${CMAKE_SOURCE_DIR}/cdm/java/*.java"
  "${CMAKE_SOURCE_DIR}/engine/java/*.java"
  "${CMAKE_SOURCE_DIR}/test/cdm/java/*.java"
  "${CMAKE_SOURCE_DIR}/test/engine/java/*.java"
  "${CMAKE_SOURCE_DIR}/test/driver/java/*.java")
add_jar(BioGearsJava ${JAVA_FILES}
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
    OUTPUT_NAME BioGears)
get_target_property(_jarFile BioGearsJava JAR_FILE)
add_custom_command(TARGET BioGearsJava POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${INSTALL_BIN}
    COMMAND ${CMAKE_COMMAND} -E copy ${_jarFile} ${INSTALL_BIN})
install_jar(BioGearsJava ${INSTALL_BIN})

install(DIRECTORY ${CMAKE_SOURCE_DIR}/bin DESTINATION ${CMAKE_INSTALL_PREFIX})
set(DATA_ROOT ${CMAKE_SOURCE_DIR})
configure_file(${CMAKE_SOURCE_DIR}/bin/run.cmake.in ${CMAKE_BINARY_DIR}/run.cmake @ONLY)
install(FILES ${CMAKE_BINARY_DIR}/run.cmake DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
configure_file(${CMAKE_SOURCE_DIR}/bin/run.config.in ${CMAKE_BINARY_DIR}/run.config @ONLY)
install(FILES ${CMAKE_BINARY_DIR}/run.config DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
# For documentation
configure_file(${CMAKE_SOURCE_DIR}/docs/Doxygen/full.doxy.in ${CMAKE_BINARY_DIR}/full.doxy @ONLY)
install(FILES ${CMAKE_BINARY_DIR}/full.doxy DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/docs)

# BioGears Testing
enable_testing()
add_test(NAME runCDMUnitTests
  COMMAND ${CMAKE_COMMAND} -DTYPE:STRING=CDMUnitTests -P ${CMAKE_BINARY_DIR}/install/bin/run.cmake
  WORKING_DIRECTORY ${INSTALL_BIN})
add_test(NAME runBGEUnitTests
  COMMAND ${CMAKE_COMMAND} -DTYPE:STRING=BGEUnitTests -P ${CMAKE_BINARY_DIR}/install/bin/run.cmake
  WORKING_DIRECTORY ${INSTALL_BIN})
add_test(NAME runSystemValidation
  COMMAND ${CMAKE_COMMAND} -DTYPE:STRING=SystemValidation -P ${CMAKE_BINARY_DIR}/install/bin/run.cmake
  WORKING_DIRECTORY ${INSTALL_BIN})
add_test(NAME runPatientValidation
  COMMAND ${CMAKE_COMMAND} -DTYPE:STRING=PatientValidation -P ${CMAKE_BINARY_DIR}/install/bin/run.cmake
  WORKING_DIRECTORY ${INSTALL_BIN})
add_test(NAME runVerification
  COMMAND ${CMAKE_COMMAND} -DTYPE:STRING=VerificationScenarios -P ${CMAKE_BINARY_DIR}/install/bin/run.cmake
  WORKING_DIRECTORY ${INSTALL_BIN})
add_test(NAME runDrugValidation
  COMMAND ${CMAKE_COMMAND} -DTYPE:STRING=ValidationDrugs -P ${CMAKE_BINARY_DIR}/install/bin/run.cmake
  WORKING_DIRECTORY ${INSTALL_BIN})
add_test(NAME runLongVerification
  COMMAND ${CMAKE_COMMAND} -DTYPE:STRING=LongVerificationScenarios -P ${CMAKE_BINARY_DIR}/install/bin/run.cmake
  WORKING_DIRECTORY ${INSTALL_BIN})
# TODO Make Doc generation a test too!
