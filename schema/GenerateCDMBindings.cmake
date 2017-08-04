
set(from "${SCHEMA_SRC}/proto")
set(to   "${SCHEMA_DST}")
set(BINDER "${SCHEMA_DST}/../../protobuf/install/bin/protoc")

message(STATUS ${from})
message(STATUS ${to})

message(STATUS "Generating Schema Bindings" )
message(STATUS "Using : ${BINDER}")

file(GLOB_RECURSE _FILES "${from}/*.proto")

set(cpp_bindings_DIR "${to}/cpp")
file(MAKE_DIRECTORY "${cpp_bindings_DIR}/bind")
file(GLOB_RECURSE _OLD_CPP_FILES "${cpp_bindings_DIR}/*.*")
if(_OLD_CPP_FILES)
  file(REMOVE ${_OLD_CPP_FILES})
endif() 
foreach(f ${_FILES})
  message(STATUS "Binding file ${f}")
  execute_process(COMMAND ${BINDER} --proto_path=${from}
                                    --cpp_out=${cpp_bindings_DIR}/bind
                                    # or 
                                    #--cpp_out=dllexport_decl=CDM_BINDINGS_EXPORT:${cpp_bindings_DIR}/bind
                                    ${f})
endforeach()
message(STATUS "cpp bindings are here : ${cpp_bindings_DIR}" )


#Generate the java descriptor file
execute_process(COMMAND ${BINDER} --proto_path=${SCHEMA_DST}/../../protobuf/src/protobuf/src/
                                  --java_out=${SCHEMA_DST}/../../protobuf/src/protobuf/java/core/src/main/java/
                                    ${SCHEMA_DST}/../../protobuf/src/protobuf/src/google/protobuf/descriptor.proto)
execute_process(COMMAND ${BINDER} --proto_path=${SCHEMA_DST}/../../protobuf/src/protobuf/src/
                                  --java_out=${SCHEMA_DST}/../../protobuf/src/protobuf/java/core/src/main/java/
                                    ${SCHEMA_DST}/../../protobuf/src/protobuf/src/google/protobuf/any.proto)
set(java_bindings_DIR "${to}/java")
file(MAKE_DIRECTORY "${java_bindings_DIR}")
file(GLOB_RECURSE _OLD_FILES "${java_bindings_DIR}/*.*")
if(_OLD_FILES)
  file(REMOVE ${_OLD_FILES})
endif()
file(MAKE_DIRECTORY "${java_bindings_DIR}/build")
file(GLOB_RECURSE _OLD_FILES "${java_bindings_DIR}/build/*.*")
if(_OLD_FILES)
  file(REMOVE ${_OLD_FILES})
endif()
foreach(f ${_FILES})
  message(STATUS "Binding file ${f}")
  execute_process(COMMAND ${BINDER} --proto_path=${from}
                                    --java_out=${java_bindings_DIR}
                                    ${f})
endforeach()
message(STATUS "java bindings are here : ${java_bindings_DIR}" )
