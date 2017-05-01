# There are two ways I generate the bind code:
# - Per XSD type : These are in the cpp/ folder
# - Per XSD file : These are in the cpp/min folder
# There are fewer files in the min folder but they are much larger
# And in working witn MinGW, they generate obj files with redundent types in them
# When the linker tries to process them all, it runs out of memory
# MSVC does not have any issue with these large files, and it is much fast to build the min folder
# So for MSVC I am going to build the bind DLL with the min generated source to speed up build times
# Maybe one day I will figure out how to properly get a gcc compiler to digest the min folder as well
# I tried precompiled headers in MinGW but that did not really work as I expected..
# Shoot me an email if you have any ideas (aaron.bray@kitware.com)

message(STATUS "Generating Schema Bindings" )
message(STATUS "Using Code Synthesis XSD : ${XSD_EXECUTABLE}")
set(bindings_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cpp/bind")
file(GLOB_RECURSE OLD_BINDING_FILES "${bindings_DIR}/*")
file(GLOB_RECURSE XSD_FILES "xsd/*")

foreach(f ${OLD_BINDING_FILES})
  file(REMOVE $f)
endforeach()
file(MAKE_DIRECTORY "${bindings_DIR}/min/cdm")
file(MAKE_DIRECTORY "${bindings_DIR}/min/biogears")
file(COPY "cpp/custom-double/" 
     DESTINATION "${bindings_DIR}"
     FILES_MATCHING PATTERN "*.hxx" PATTERN "biogears-cdm.cxx")

if(WIN32)
  set(EXPORT_SYMBOL --export-symbol "__declspec(dllexport)")
elseif( CMAKE_COMPILER_IS_GNUCXX AND ${CMAKE_CXX_COMPILER_VERSION} VERSION_GREATER 4)
  set(EXPORT_SYMBOL --export-symbol "__attribute__ ((visibility (\"default\")))")
else()
  set(EXPORT_SYMBOL)
endif()

#Generate normally, which is a file per type 
execute_process(COMMAND ${XSD_EXECUTABLE} cxx-tree 
                                           --std c++11 
                                           --file-per-type
                                           --extern-xml-schema data-model-schema.xsd
                                           --cxx-prologue \#include\"biogears-cdm.hxx\"
                                           --generate-polymorphic 
                                           --polymorphic-type-all 
                                           --generate-serialization 
                                           --generate-ostream 
                                           --generate-doxygen 
                                           --generate-default-ctor 
                                           --custom-type "double=double"
                                           --custom-type "decimal=long double"
                                           --hxx-epilogue-file ${bindings_DIR}/xml-schema-epilogue.hxx
                                           ${EXPORT_SYMBOL}
                                           ${CMAKE_CURRENT_SOURCE_DIR}/xsd/BioGearsDataModel.xsd
                WORKING_DIRECTORY "${bindings_DIR}/")
execute_process(COMMAND ${XSD_EXECUTABLE} cxx-tree 
                                           --std c++11 
                                           --generate-xml-schema
                                           --generate-polymorphic 
                                           --polymorphic-type-all 
                                           --generate-serialization 
                                           --generate-ostream 
                                           --generate-doxygen 
                                           --generate-default-ctor 
                                           ${EXPORT_SYMBOL}
                                           ${bindings_DIR}/data-model-schema.xsd
                WORKING_DIRECTORY "${bindings_DIR}/")
#Generate cxx/hxx file for each xsd file (faster to build)
file(GLOB CDM_XSD "${CMAKE_CURRENT_SOURCE_DIR}/xsd/cdm/*.xsd")
foreach(ITEM ${CDM_XSD})
  message(STATUS "Processing ${ITEM}")
  execute_process(COMMAND ${XSD_EXECUTABLE} cxx-tree 
                                             --std c++11 
                                             --generate-polymorphic 
                                             --polymorphic-type-all 
                                             --generate-serialization 
                                             --generate-ostream 
                                             --generate-doxygen 
                                             --generate-default-ctor 
                                             --custom-type "double=double"
                                             --custom-type "decimal=long double"
                                             --hxx-epilogue-file ${bindings_DIR}/xml-schema-epilogue.hxx
                                             ${EXPORT_SYMBOL}
                                             ${ITEM}
                  WORKING_DIRECTORY "${bindings_DIR}/min/cdm")
endforeach()
file(GLOB BGE_XSD "${CMAKE_CURRENT_SOURCE_DIR}/xsd/biogears/*.xsd")
foreach(ITEM ${BGE_XSD})
  message(STATUS "Processing ${ITEM}")
  execute_process(COMMAND ${XSD_EXECUTABLE} cxx-tree 
                                             --std c++11 
                                             --generate-polymorphic 
                                             --polymorphic-type-all 
                                             --generate-serialization 
                                             --generate-ostream 
                                             --generate-doxygen 
                                             --generate-default-ctor 
                                             --custom-type "double=double"
                                             --custom-type "decimal=long double"
                                             --hxx-epilogue-file ${bindings_DIR}/xml-schema-epilogue.hxx
                                             ${EXPORT_SYMBOL}
                                             ${ITEM}
                  WORKING_DIRECTORY "${bindings_DIR}/min/biogears")
endforeach()

# Generating the Java bindings
find_program(Java_XJC_EXECUTABLE
    NAMES xjc
    HINTS ${_JAVA_HINTS}
    PATHS ${_JAVA_PATHS}
  )
  message(STATUS "Java XJC : ${Java_XJC_EXECUTABLE}")

file(REMOVE_RECURSE "${CMAKE_SOURCE_DIR}/schema/java")
file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/schema/java")
file(REMOVE_RECURSE "${CMAKE_SOURCE_DIR}/schema/build")
file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/schema/build")

execute_process(COMMAND ${Java_XJC_EXECUTABLE} -d ${CMAKE_SOURCE_DIR}/schema/java -p mil.tatrc.physiology.datamodel.bind ${CMAKE_SOURCE_DIR}/schema/xsd/BioGearsDataModel.xsd)

message(STATUS "bindings are here : ${bindings_DIR}" )
