project(Pulse)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

# Policy to address @foo@ variable expansion
set(_VERSION_MAJOR 1)
set(_VERSION_MINOR 0)
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

# Build the core libraries as shared or static (DataModel, CDM, Engine)
set(BUILD_SHARED_LIBS OFF)

message(STATUS "Looking for modules here : ${CMAKE_PREFIX_PATH}")
set(CMAKE_CXX_STANDARD_LIBRARIES "" CACHE TYPE INTERNAL FORCE)
set(CMAKE_C_STANDARD_LIBRARIES "" CACHE TYPE INTERNAL FORCE)

find_package(Dirent REQUIRED)
find_package(Eigen3 REQUIRED)
# The outer build does some custom installing of dependent libraries
# Instead of using find_package, I will make sure things are where expected
if(NOT protobuf_DIR)
  set(protobuf_DIR ${CMAKE_BINARY_DIR}/..//protobuf/src/protobuf)
  set(protobuf_Header ${protobuf_DIR}/src/google/protobuf/package_info.h)
  # Proto headers should have been installed here by the outer build
  if(NOT EXISTS ${protobuf_Header})
    message(FATAL_ERROR "I cannot find protobuf header, ${protobuf_Header}, make sure you make the install target of the super build")
  endif()
endif()

# Log4cpp src should have been download to somewhere
if(NOT log4cpp_DIR)
  # It should be here if the outer build ran
  set(log4cpp_DIR ${CMAKE_BINARY_DIR}/../log4cpp/src/log4cpp)
  set(log4cpp_HEADER ${log4cpp_DIR}/include/log4cpp/Category.hh)
  if(NOT EXISTS ${log4cpp_HEADER})
    message(FATAL_ERROR "I cannot find log4cpp header, ${log4cpp_HEADER}, make sure you make the install target of the super build")
  endif()
endif()
if(NOT LOG4CPP_INCLUDE_DIR)
  set(LOG4CPP_INCLUDE_DIR ${log4cpp_DIR}/include)
endif()

list(APPEND CMAKE_PREFIX_PATH ${eigen_INSTALL})
list(APPEND CMAKE_PREFIX_PATH ${dirent_INSTALL})
list(APPEND CMAKE_PREFIX_PATH ${protobuf_INSTALL})
list(APPEND CMAKE_PREFIX_PATH ${log4cpp_INSTALL})

set(SCHEMA_SRC "${CMAKE_SOURCE_DIR}/schema")
set(SCHEMA_DST "${CMAKE_BINARY_DIR}/schema")

set(protobuf_BUILD_TESTS OFF CACHE TYPE INTERNAL FORCE)
set(protobuf_BUILD_EXAMPLES OFF CACHE TYPE INTERNAL FORCE)
add_subdirectory("${protobuf_DIR}/cmake" "${protobuf_DIR}-build" EXCLUDE_FROM_ALL)  
set_target_properties(HowToDriver libprotobuf-lite libprotoc protoc PROPERTIES EXCLUDE_FROM_ALL 1 EXCLUDE_FROM_DEFAULT_BUILD 1)
add_subdirectory(${log4cpp_DIR} ${log4cpp_DIR}-build)
add_subdirectory(schema)
add_subdirectory(cdm)
add_subdirectory(engine)
add_subdirectory(test)
add_subdirectory(sdk)
add_subdirectory(verification)
include(${CMAKE_CURRENT_SOURCE_DIR}/PulseJNI.cmake)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_target_properties (libprotobuf libprotobuf-lite libprotoc protoc js_embed PROPERTIES FOLDER protobufs)


file(COPY ${CMAKE_SOURCE_DIR}/bin DESTINATION ${CMAKE_INSTALL_PREFIX})
configure_file(${CMAKE_SOURCE_DIR}/bin/run.cmake.in ${CMAKE_INSTALL_PREFIX}/bin/run.cmake @ONLY)
configure_file(${CMAKE_SOURCE_DIR}/bin/run.config.in ${CMAKE_INSTALL_PREFIX}/bin/run.config @ONLY)
configure_file(${CMAKE_SOURCE_DIR}/docs/Doxygen/full.doxy.in ${CMAKE_INSTALL_PREFIX}/bin/docs/full.doxy @ONLY)

# Install the proto libs to the right locations
if(WIN32)
  if(BUILD_SHARED_LIBS)
    install(FILES "${protobuf_DIR}-build/Release/libprotobuf.dll"
      CONFIGURATIONS Release DESTINATION ${INSTALL_BIN}/release${EX_CONFIG})  
    install(FILES "${protobuf_DIR}-build/Debug/libprotobufd.dll"
      CONFIGURATIONS Debug DESTINATION ${INSTALL_BIN}/debug${EX_CONFIG})
    install(FILES "${protobuf_DIR}-build/RelWithDebInfo/libprotobuf.dll"
      CONFIGURATIONS RelWithDebInfo DESTINATION ${INSTALL_BIN}/relwithdebinfo${EX_CONFIG})
  endif()

  install(FILES "${protobuf_DIR}-build/Release/libprotobuf.lib"
    CONFIGURATIONS Release DESTINATION ${INSTALL_LIB}/release${EX_CONFIG})
  install(FILES "${protobuf_DIR}-build/Debug/libprotobufd.lib"
    CONFIGURATIONS Debug DESTINATION ${INSTALL_LIB}/debug${EX_CONFIG})
  install(FILES "${protobuf_DIR}-build/RelWithDebInfo/libprotobuf.lib"
    CONFIGURATIONS RelWithDebInfo DESTINATION ${INSTALL_LIB}/relwithdebinfo${EX_CONFIG})
else()
  if(BUILD_SHARED_LIBS)
    install(FILES ${protobuf_INSTALL}/bin/libprotobuf.so
      CONFIGURATIONS Release DESTINATION ${INSTALL_BIN}/release${EX_CONFIG})  
    install(FILES ${protobuf_INSTALL}/bin/libprotobufd.so
      CONFIGURATIONS Debug DESTINATION ${INSTALL_BIN}/debug${EX_CONFIG})
    install(FILES ${protobuf_INSTALL}/bin/libprotobuf.so
      CONFIGURATIONS RelWithDebInfo DESTINATION ${INSTALL_BIN}/relwithdebinfo${EX_CONFIG})
  endif()

  install(FILES ${xerces_INSTALL}/lib/libprotobuf.lib
    CONFIGURATIONS Release DESTINATION ${INSTALL_LIB}/release${EX_CONFIG})
  install(FILES ${xerces_INSTALL}/lib/libprotobufd.lib
    CONFIGURATIONS Debug DESTINATION ${INSTALL_LIB}/debug${EX_CONFIG})
  install(FILES ${xerces_INSTALL}/lib/libprotobuf.lib
    CONFIGURATIONS RelWithDebInfo DESTINATION ${INSTALL_LIB}/relwithdebinfo${EX_CONFIG})  
endif()

# Pulse Testing
enable_testing()
add_test(NAME runCDMUnitTests
  COMMAND ${CMAKE_COMMAND} -DTYPE:STRING=CDMUnitTests -P ${CMAKE_BINARY_DIR}/install/bin/run.cmake
  WORKING_DIRECTORY ${INSTALL_BIN})
add_test(NAME runBGEUnitTests
  COMMAND ${CMAKE_COMMAND} -DTYPE:STRING=EngineUnitTests -P ${CMAKE_BINARY_DIR}/install/bin/run.cmake
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
