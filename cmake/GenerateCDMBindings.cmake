
file(GLOB_RECURSE OLD_BINDING_FILES "schema/cpp/bind/*")
file(GLOB_RECURSE XSD_FILES "schema/xsd/*")
add_custom_target(GenerateBindings 
)
message( STATUS "Generating Schema Bindings" )
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

set(bindings_DIR "${CMAKE_CURRENT_SOURCE_DIR}/schema/cpp/bind")

foreach(f ${OLD_BINDING_FILES})
  file(REMOVE $f)
endforeach()
file(MAKE_DIRECTORY "${bindings_DIR}/min/cdm")
file(MAKE_DIRECTORY "${bindings_DIR}/min/biogears")
file(COPY "schema/cpp/custom-double/" 
     DESTINATION "${bindings_DIR}"
     FILES_MATCHING PATTERN "*.hxx" PATTERN "biogears-cdm.cxx")

#Generate normally, which is a file per type 
execute_process(COMMAND ${xsd_DIR}/bin/xsd cxx-tree 
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
                                           --export-symbol "__declspec(dllexport)"
                                           ${CMAKE_CURRENT_SOURCE_DIR}/schema/xsd/BioGearsDataModel.xsd
                WORKING_DIRECTORY "${bindings_DIR}/")
execute_process(COMMAND ${xsd_DIR}/bin/xsd cxx-tree 
                                           --std c++11 
                                           --generate-xml-schema
                                           --generate-polymorphic 
                                           --polymorphic-type-all 
                                           --generate-serialization 
                                           --generate-ostream 
                                           --generate-doxygen 
                                           --generate-default-ctor 
                                           --export-symbol "__declspec(dllexport)"
                                           ${bindings_DIR}/data-model-schema.xsd
                WORKING_DIRECTORY "${bindings_DIR}/")
#Generate cxx/hxx file for each xsd file (faster to build)
file(GLOB CDM_XSD "${CMAKE_CURRENT_SOURCE_DIR}/schema/xsd/cdm/*.xsd")
foreach(ITEM ${CDM_XSD})
  message(STATUS "Processing ${ITEM}")
  execute_process(COMMAND ${xsd_DIR}/bin/xsd cxx-tree 
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
                                             --export-symbol "__declspec(dllexport)"
                                             ${ITEM}
                  WORKING_DIRECTORY "${bindings_DIR}/min/cdm")
endforeach()
file(GLOB BGE_XSD "${CMAKE_CURRENT_SOURCE_DIR}/schema/xsd/biogears/*.xsd")
foreach(ITEM ${BGE_XSD})
  message(STATUS "Processing ${ITEM}")
  execute_process(COMMAND ${xsd_DIR}/bin/xsd cxx-tree 
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
                                             --export-symbol "__declspec(dllexport)"
                                             ${ITEM}
                  WORKING_DIRECTORY "${bindings_DIR}/min/biogears")
endforeach()

message(STATUS "bindings are here : ${bindings_DIR}" )