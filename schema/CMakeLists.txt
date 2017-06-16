# Files in the project 

set(SCHEMA_SRC "${CMAKE_SOURCE_DIR}/schema")
set(SCHEMA_DST "${CMAKE_BINARY_DIR}/schema")
include(${CMAKE_CURRENT_SOURCE_DIR}/GenerateCDMBindings.cmake)

file(GLOB_RECURSE BIND_FILES
  "${SCHEMA_DST}/cpp/bind/*.h"
  "${SCHEMA_DST}/cpp/bind/*.cc"
)
source_group("" FILES ${BIND_FILES})
set(SOURCE ${BIND_FILES})

if(NOT SOURCE)
  list(APPEND SOURCE "Error_No_Bindings_Created")
endif()

# The DLL we are building
add_library(DataModelBindings SHARED ${SOURCE})
# Preprocessor Definitions and Include Paths
target_include_directories(DataModelBindings PRIVATE ${CMAKE_BINARY_DIR}/schema/cpp/bind)
target_include_directories(DataModelBindings PRIVATE ${PROTOBUF_INCLUDE_DIR})
message(STATUS "PROTOBUF_INCLUDE_DIR ${PROTOBUF_INCLUDE_DIR}")
set(FLAGS)
list(APPEND FLAGS " -DXML_LIBRARY")
set_target_properties(DataModelBindings PROPERTIES COMPILE_FLAGS "${FLAGS}" PREFIX "")

if(APPLE)
    set_target_properties(DataModelBindings PROPERTIES MACOSX_RPATH ON)
endif()
target_link_libraries(DataModelBindings libprotobuf)
if(MSVC)
  target_link_libraries(DataModelBindings ws2_32.lib)
  target_link_libraries(DataModelBindings advapi32.lib)
endif()
add_custom_command(TARGET DataModelBindings POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E make_directory ${INSTALL_BIN}/${CONFIGURATION}${EX_CONFIG}
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:DataModelBindings> ${INSTALL_BIN}/${CONFIGURATION}${EX_CONFIG}
                   COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/proto ${INSTALL_BIN}/proto)
if(WIN32)# Copy dll files to the bin
  install(TARGETS DataModelBindings 
          RUNTIME CONFIGURATIONS Release DESTINATION ${INSTALL_BIN}/release${EX_CONFIG}
          LIBRARY CONFIGURATIONS Release DESTINATION ${INSTALL_BIN}/release${EX_CONFIG})
  install(TARGETS DataModelBindings 
          RUNTIME CONFIGURATIONS Debug DESTINATION ${INSTALL_BIN}/debug${EX_CONFIG}
          LIBRARY CONFIGURATIONS Debug DESTINATION ${INSTALL_BIN}/debug${EX_CONFIG})
  install(TARGETS DataModelBindings 
          RUNTIME CONFIGURATIONS RelWithDebInfo DESTINATION ${INSTALL_BIN}/relwithdebinfo${EX_CONFIG}
          LIBRARY CONFIGURATIONS RelWithDebInfo DESTINATION ${INSTALL_BIN}/relwithdebinfo${EX_CONFIG})
else()# Copy so files to the bin
  install(TARGETS DataModelBindings 
          LIBRARY CONFIGURATIONS Release DESTINATION ${INSTALL_BIN}/release${EX_CONFIG})
  install(TARGETS DataModelBindings 
          LIBRARY CONFIGURATIONS Debug DESTINATION ${INSTALL_BIN}/debug${EX_CONFIG})
  install(TARGETS DataModelBindings 
          LIBRARY CONFIGURATIONS RelWithDebInfo DESTINATION ${INSTALL_BIN}/relwithdebinfo${EX_CONFIG})
endif()
# Copy lib/so files to the sdk/lib
install(TARGETS DataModelBindings         
        LIBRARY CONFIGURATIONS Release DESTINATION ${INSTALL_LIB}/release${EX_CONFIG}
        ARCHIVE CONFIGURATIONS Release DESTINATION ${INSTALL_LIB}/release${EX_CONFIG})
install(TARGETS DataModelBindings 
        LIBRARY CONFIGURATIONS Debug DESTINATION ${INSTALL_LIB}/debug${EX_CONFIG}
        ARCHIVE CONFIGURATIONS Debug DESTINATION ${INSTALL_LIB}/debug${EX_CONFIG})
install(TARGETS DataModelBindings  
        LIBRARY CONFIGURATIONS RelWithDebInfo DESTINATION ${INSTALL_LIB}/relwithdebinfo${EX_CONFIG}
        ARCHIVE CONFIGURATIONS RelWithDebInfo DESTINATION ${INSTALL_LIB}/relwithdebinfo${EX_CONFIG})
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/proto DESTINATION ${INSTALL_BIN})
install_headers("${CMAKE_BINARY_DIR}/schema/cpp/bind" "bind")
