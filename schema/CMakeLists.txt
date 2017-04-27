# Files in the project 

#include(${CMAKE_CURRENT_SOURCE_DIR}/GenerateCDMBindings.cmake)

file(GLOB BIND_FILES
    "cpp/bind/*.hxx"
    "cpp/bind/*.cxx"
)
if(MSVC)
  FILE(GLOB_RECURSE MIN_BIND_FILES
    "cpp/bind/min/*.hxx"
    "cpp/bind/min/*.cxx"
  )
  SOURCE_GROUP("" FILES ${MIN_BIND_FILES})
  SET(SOURCE ${MIN_BIND_FILES})
else(MSVC)
  SOURCE_GROUP("" FILES ${BIND_FILES})
  SET(SOURCE ${BIND_FILES})
endif(MSVC)

if(NOT SOURCE)
  list(APPEND SOURCE "Error_No_Bindings_Created") 
endif()

# The DLL we are building
add_library(DataModelBindings SHARED ${SOURCE})
# Preprocessor Definitions and Include Paths
target_include_directories(DataModelBindings PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/cpp/bind)
target_include_directories(DataModelBindings PRIVATE ${XercesC_INCLUDE_DIR})
target_include_directories(DataModelBindings PRIVATE ${XSD_INCLUDE_DIR})
set(FLAGS)
list(APPEND FLAGS " -DXML_LIBRARY")
set_target_properties(DataModelBindings PROPERTIES COMPILE_FLAGS "${FLAGS}" PREFIX "")

if(APPLE)
    set_target_properties(DataModelBindings PROPERTIES MACOSX_RPATH ON)
endif()
target_link_libraries(DataModelBindings ${XercesC_LIBRARIES})
if(MSVC)
  target_link_libraries(DataModelBindings ws2_32.lib)
  target_link_libraries(DataModelBindings advapi32.lib)
endif()
add_custom_command(TARGET DataModelBindings POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:DataModelBindings> ${INSTALL_BIN}/${CONFIGURATION}${EX_CONFIG})
install(TARGETS DataModelBindings 
        RUNTIME CONFIGURATIONS Release DESTINATION ${INSTALL_BIN}/release${EX_CONFIG})
install(TARGETS DataModelBindings 
        RUNTIME CONFIGURATIONS Debug DESTINATION ${INSTALL_BIN}/debug${EX_CONFIG})
install(TARGETS DataModelBindings 
        RUNTIME CONFIGURATIONS RelWithDebug DESTINATION ${INSTALL_BIN}/relwithdebug${EX_CONFIG})

add_custom_target(GenerateBindings)
add_custom_command(TARGET GenerateBindings PRE_BUILD 
  COMMAND cmake ${CMAKE_CURRENT_SOURCE_DIR} 
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

