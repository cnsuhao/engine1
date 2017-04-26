# Files in the project 

include(cmake/GenerateCDMBindings.cmake)

file(GLOB BIND_FILES
    "schema/cpp/bind/*.hxx"
    "schema/cpp/bind/*.cxx"
)
if(MSVC)
  FILE(GLOB_RECURSE MIN_BIND_FILES
    "schema/cpp/bind/min/*.hxx"
    "schema/cpp/bind/min/*.cxx"
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
add_library(DataModelBindings ${SOURCE})
# Preprocessor Definitions and Include Paths
target_include_directories(DataModelBindings PRIVATE ./schema/cpp/bind)
target_include_directories(DataModelBindings PRIVATE ${xsd_DIR}/libxsd)
target_include_directories(DataModelBindings PRIVATE ${xerces_DIR}/include/)
set(FLAGS)
list(APPEND FLAGS " -DXML_LIBRARY")
set_target_properties(DataModelBindings PROPERTIES COMPILE_FLAGS "${FLAGS}" PREFIX "")

if(APPLE)
    set_target_properties(DataModelBindings PROPERTIES MACOSX_RPATH ON)
endif()

