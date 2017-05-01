# Scripts to assist developers
# Mostly these are calling the test suite driver and validator classes in Java

find_package(Java REQUIRED)
include(UseJava)
if(_JAVA_HOME)
  # Overwrite Java if the env variable is set
  
  message(STATUS "Using JAVA_HOME as my Java executable (set to : ${_JAVA_HOME})")
  set(Java_JAVA_EXECUTABLE ${_JAVA_HOME}/bin/java)
endif()
#  You tell me what JDK/JRE you want to use
#set(Java_JAVA_EXECUTABLE "/the_jdk_I_want/bin/java)

set(JAVA_CLASSPATH BioGears.jar;
        ../jar/jcommon-1.0.16.jar;
        ../jar/jdom-2.0.2.jar;
        ../jar/jfreechart-1.0.13.jar;
        ../jar/guava-11.0.2.jar;
        ../jar/log4j-1.2.17.jar;
        ../jar/poi-3.13-20150929.jar;
        ../jar/poi-ooxml-3.13-20150929.jar;
        ../jar/poi-ooxml-schemas-3.13-20150929.jar;
        ../jar/pdfbox-2.0.0-RC3.jar;
        ../jar/reflections-0.9.9-RC1-uberjar.jar;
        ../jar/xmlbeans-2.6.0.jar;
        ../jar/zip4j-1.3.1.jar)

if(TYPE STREQUAL "SystemValidation")
  execute_process(COMMAND "${Java_JAVA_EXECUTABLE}" -Xmx900m -classpath "${JAVA_CLASSPATH}" mil.tatrc.physiology.testing.TestDriver ../test/config/ValidationSystems.config)
  execute_process(COMMAND "${Java_JAVA_EXECUTABLE}" -Xmx900m -classpath "${JAVA_CLASSPATH}" mil.tatrc.physiology.testing.validation.SystemValidation)
elseif(TYPE STREQUAL "PatientValidation")
  execute_process(COMMAND "${Java_JAVA_EXECUTABLE}" -Xmx900m -classpath "${JAVA_CLASSPATH}" mil.tatrc.physiology.testing.TestDriver ../test/config/ValidationPatients.config)
  execute_process(COMMAND "${Java_JAVA_EXECUTABLE}" -Xmx900m -classpath "${JAVA_CLASSPATH}" mil.tatrc.physiology.testing.validation.PatientValidation)
elseif(TYPE STREQUAL "GenData")
  execute_process(COMMAND "${Java_JAVA_EXECUTABLE}" -Xmx900m -classpath "${JAVA_CLASSPATH}" mil.tatrc.physiology.biogears.dataset.DataSetReader)
elseif(TYPE STREQUAL "GenStates")
  execute_process(COMMAND "${Java_JAVA_EXECUTABLE}" -Xmx900m -classpath "${JAVA_CLASSPATH}" mil.tatrc.physiology.testing.TestDriver ../test/config/InitialPatientStates.config)
else()
  execute_process(COMMAND "${Java_JAVA_EXECUTABLE}" -Xmx900m -classpath "${JAVA_CLASSPATH}" mil.tatrc.physiology.testing.TestDriver ../test/config/${TYPE}.config)
endif()
