project(BioGears)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
MACRO(install_headers SRC_DIR DEST)
  file(GLOB_RECURSE HEADER_LIST 
    ${SRC_DIR}/*.h 
    ${SRC_DIR}/*.hxx
    ${SRC_DIR}/*.inl)
  foreach(HEADER ${HEADER_LIST})
    #message(STATUS "Header at ${HEADER}")
    STRING(REPLACE ${SRC_DIR}/ "" REL_DIR ${HEADER})
    #message(STATUS "Relative Path ${REL_DIR}")  
    set(FULL_LOC ${INSTALL_INC}/include/${DEST}/${REL_DIR})
    #message(STATUS "File should goto ${FULL_LOC}")
    get_filename_component(DEST_DIR ${FULL_LOC} PATH) 
    #message(STATUS "Going to ${DEST_DIR}")
    install(FILES ${HEADER} DESTINATION ${DEST_DIR})
  endforeach()    

ENDMACRO(install_headers)

# Policy to address @foo@ variable expansion
set(BioGears_VERSION_MAJOR 6)
set(BioGears_VERSION_MINOR 2)
set(BioGears_VERSION_PATCH 0)
set(BioGears_VERSION "${BioGears_VERSION_MAJOR}.${BioGears_VERSION_MINOR}.${BioGears_VERSION_PATCH}")

set(CMAKE_CONFIGURATION_TYPES Debug Release RelWithDebInfo CACHE TYPE INTERNAL FORCE )
if(MSVC)  
  set(CMAKE_CXX_FLAGS_DEBUG "/D_DEBUG /MDd /Zi /Ob2 /Oi /Od /RTC1" CACHE TYPE INTERNAL FORCE)
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
find_package(XercesC 3.1.0 REQUIRED)
find_package(XSD REQUIRED)

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
file(GLOB_RECURSE JAVA_FILES 
  "${CMAKE_SOURCE_DIR}/schema/java/*.java"
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

# BioGears Testing
enable_testing()
add_test(NAME runCDMUnitTests
  COMMAND ${CMAKE_COMMAND} -DTYPE:STRING=CDMUnitTests -P ${CMAKE_SOURCE_DIR}/cmake/Scripts.cmake
  WORKING_DIRECTORY ${INSTALL_BIN})
add_test(NAME runBGEUnitTests
  COMMAND ${CMAKE_COMMAND} -DTYPE:STRING=BGEUnitTests -P ${CMAKE_SOURCE_DIR}/cmake/Scripts.cmake
  WORKING_DIRECTORY ${INSTALL_BIN})
add_test(NAME runSystemValidation
  COMMAND ${CMAKE_COMMAND} -DTYPE:STRING=SystemValidation -P ${CMAKE_SOURCE_DIR}/cmake/Scripts.cmake
  WORKING_DIRECTORY ${INSTALL_BIN})
add_test(NAME runPatientValidation
  COMMAND ${CMAKE_COMMAND} -DTYPE:STRING=PatientValidation -P ${CMAKE_SOURCE_DIR}/cmake/Scripts.cmake
  WORKING_DIRECTORY ${INSTALL_BIN})
add_test(NAME runVerification
  COMMAND ${CMAKE_COMMAND} -DTYPE:STRING=VerificationScenarios -P ${CMAKE_SOURCE_DIR}/cmake/Scripts.cmake
  WORKING_DIRECTORY ${INSTALL_BIN})
add_test(NAME runDrugValidation
  COMMAND ${CMAKE_COMMAND} -DTYPE:STRING=ValidationDrugs -P ${CMAKE_SOURCE_DIR}/cmake/Scripts.cmake
  WORKING_DIRECTORY ${INSTALL_BIN})
add_test(NAME runLongVerification
  COMMAND ${CMAKE_COMMAND} -DTYPE:STRING=LongVerificationScenarios -P ${CMAKE_SOURCE_DIR}/cmake/Scripts.cmake
  WORKING_DIRECTORY ${INSTALL_BIN})
# TODO Make Doc generation a test too!
