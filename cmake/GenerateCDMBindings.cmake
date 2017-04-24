MESSAGE( STATUS "Generating Schema Bindings" )
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

FILE(REMOVE_RECURSE "${CMAKE_BINARY_DIR}/bind/cpp/")
FILE(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/bind/cpp/")
FILE(COPY "${CMAKE_CURRENT_SOURCE_DIR}/schema/cpp/custom-double/" 
     DESTINATION "${CMAKE_BINARY_DIR}/bind/cpp"
	 FILES_MATCHING PATTERN "*.hxx" PATTERN "biogears-cdm.cxx")

#Generate normally, which is a file per type 
FILE(REMOVE_RECURSE "${CMAKE_BINARY_DIR}/bind/cpp/min")
FILE(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/bind/cpp/min/cdm")
FILE(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/bind/cpp/min/biogears")
EXECUTE_PROCESS(COMMAND ${xsd_DIR}/bin/xsd cxx-tree 
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
                                           --hxx-epilogue-file ${CMAKE_BINARY_DIR}/bind/cpp/xml-schema-epilogue.hxx
                                           --export-symbol "__declspec(dllexport)"
                                           ${CMAKE_CURRENT_SOURCE_DIR}/schema/xsd/BioGearsDataModel.xsd
                WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/bind/cpp/")
#Generate cxx/hxx file for each xsd file (faster to build)
FILE(GLOB CDM_XSD "${CMAKE_CURRENT_SOURCE_DIR}/schema/xsd/cdm/*.xsd")
FOREACH(ITEM ${CDM_XSD})
MESSAGE(STATUS ${ITEM})
EXECUTE_PROCESS(COMMAND ${xsd_DIR}/bin/xsd cxx-tree 
                                           --std c++11 
                                           --generate-polymorphic 
                                           --polymorphic-type-all 
                                           --generate-serialization 
                                           --generate-ostream 
                                           --generate-doxygen 
                                           --generate-default-ctor 
                                           --custom-type "double=double"
                                           --custom-type "decimal=long double"
                                           --hxx-epilogue-file ${CMAKE_BINARY_DIR}/bind/cpp/xml-schema-epilogue.hxx
                                           --export-symbol "__declspec(dllexport)"
                                           ${ITEM}
                WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/bind/cpp/min/cdm")
ENDFOREACH()
FILE(GLOB BGE_XSD "${CMAKE_CURRENT_SOURCE_DIR}/schema/xsd/biogears/*.xsd")
FOREACH(ITEM ${CDM_XSD})
EXECUTE_PROCESS(COMMAND ${xsd_DIR}/bin/xsd cxx-tree 
                                           --std c++11 
                                           --generate-polymorphic 
                                           --polymorphic-type-all 
                                           --generate-serialization 
                                           --generate-ostream 
                                           --generate-doxygen 
                                           --generate-default-ctor 
                                           --custom-type "double=double"
                                           --custom-type "decimal=long double"
                                           --hxx-epilogue-file ${CMAKE_BINARY_DIR}/bind/cpp/xml-schema-epilogue.hxx
                                           --export-symbol "__declspec(dllexport)"
                                           ${ITEM}
                WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/bind/cpp/min/biogears")
ENDFOREACH()

SET(bindings_DIR "${CMAKE_BINARY_DIR}/bind/cpp")
MESSAGE(STATUS "bindings are here : ${bindings_DIR}" )