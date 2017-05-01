project(BioGears)

# Policy to address @foo@ variable expansion
if(POLICY CMP0053)
  cmake_policy(SET CMP0053 NEW)
endif()

if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
  message( STATUS "64 bits compiler detected" )    
  set( EX_CONFIG "64" )
  set(FIND_LIBRARY_USE_LIB64_PATHS ON)
else( CMAKE_SIZEOF_VOID_P EQUAL 8 ) 
  message( STATUS "32 bits compiler detected" )
  set( EX_CONFIG "" )
  set(FIND_LIBRARY_USE_LIB64_PATHS OFF)
endif( CMAKE_SIZEOF_VOID_P EQUAL 8 )

SET(CONFIGURATION)
if(WIN32)
  set(CONFIGURATION ${CMAKE_CFG_INTDIR})
else()
  set(CONFIGURATION ${CMAKE_BUILD_TYPE})
endif()
string(TOLOWER ${CONFIGURATION} CONFIGURATION)

set(INSTALL_BIN ${CMAKE_SOURCE_DIR}/bin/)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)


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

if(CMAKE_GENERATOR STREQUAL "Unix Makefiles")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()
if(UNIX)
    set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_RPATH}:\$ORIGIN")
endif()

set(CMAKE_CXX_STANDARD_LIBRARIES "" CACHE TYPE INTERNAL FORCE)
set(CMAKE_C_STANDARD_LIBRARIES "" CACHE TYPE INTERNAL FORCE)

message(STATUS "Where I am looking for eigen : ${CMAKE_BINARY_DIR}/eigen/install")
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${CMAKE_BINARY_DIR}/dirent/install)  
find_package(Dirent REQUIRED)
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${CMAKE_BINARY_DIR}/eigen/install)
find_package(Eigen3 3.3.3 REQUIRED)
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${CMAKE_BINARY_DIR}/log4cpp/install)  
find_package(Log4cpp REQUIRED)
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${CMAKE_BINARY_DIR}/xerces/install)  
find_package(XercesC 3.1.0 REQUIRED)
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${CMAKE_BINARY_DIR}/xsd/install)  
find_package(XSD REQUIRED)

ADD_SUBDIRECTORY(schema)
ADD_SUBDIRECTORY(cdm)
ADD_SUBDIRECTORY(engine)
ADD_SUBDIRECTORY(test)

# I should probably just make these a copy....error out if they are not there...
file(GLOB DLIBS 
  ${CMAKE_BINARY_DIR}/log4cpp/install/bin/*.dll
  ${CMAKE_BINARY_DIR}/log4cpp/install/bin/*.so)
install(FILES ${DLIBS}
  CONFIGURATIONS Release DESTINATION ${INSTALL_BIN}/release${EX_CONFIG})
install(FILES ${DLIBS}
  CONFIGURATIONS Debug DESTINATION ${INSTALL_BIN}/debug${EX_CONFIG})
install(FILES ${DLIBS}
  CONFIGURATIONS RelWithDeb DESTINATION ${INSTALL_BIN}/relwithdeb${EX_CONFIG})

file(GLOB DLIBS 
  ${CMAKE_BINARY_DIR}/xerces/install/bin/*.dll
  ${CMAKE_BINARY_DIR}/xerces/install/bin/*.so)
install(FILES ${DLIBS}
  CONFIGURATIONS Release DESTINATION ${INSTALL_BIN}/release${EX_CONFIG})
install(FILES ${DLIBS}
  CONFIGURATIONS Debug DESTINATION ${INSTALL_BIN}/debug${EX_CONFIG})
install(FILES ${DLIBS}
  CONFIGURATIONS RelWithDeb DESTINATION ${INSTALL_BIN}/relwithdeb${EX_CONFIG})    
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
add_jar(BioGears ${JAVA_FILES}
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
get_target_property(_jarFile BioGears JAR_FILE)
add_custom_command(TARGET BioGears POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${_jarFile} ${INSTALL_BIN})
install_jar(BioGears ${INSTALL_BIN})

# BioGears Testing
enable_testing()
add_test(NAME genData
  COMMAND ${CMAKE_COMMAND} -DTYPE:STRING=GenData -P ${CMAKE_SOURCE_DIR}/cmake/Scripts.cmake
  WORKING_DIRECTORY ${INSTALL_BIN})
add_test(NAME genStates
  COMMAND ${CMAKE_COMMAND} -DTYPE:STRING=InitialPatientStates -P ${CMAKE_SOURCE_DIR}/cmake/Scripts.cmake
  WORKING_DIRECTORY ${INSTALL_BIN})
add_test(NAME runDebug
  COMMAND ${CMAKE_COMMAND} -DTYPE:STRING=DebugRun -P ${CMAKE_SOURCE_DIR}/cmake/Scripts.cmake
  WORKING_DIRECTORY ${INSTALL_BIN})
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

# TODO More Test Targets
# Rebasing
# mil.tatrc.physiology.utilities.testing.Rebase [from to (config|ALL)]
#
# Ploting
# mil.tatrc.physiology.utilities.csv.plots.PlotDriver
#
# Reconfigure the config file (in memory) so we can test serialization
# mil.tatrc.physiology.utilities.testing.Reconfiguration
