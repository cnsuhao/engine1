# Files in the project 

  include(${CMAKE_CURRENT_SOURCE_DIR}/GenerateCDMBindings.cmake)

file(GLOB BIND_FILES
    "${CMAKE_BINARY_DIR}/schema/cpp/bind/*.hxx"
    "${CMAKE_BINARY_DIR}/schema/cpp/bind/*.cxx"
)
if(MSVC)
  FILE(GLOB_RECURSE MIN_BIND_FILES
    "${CMAKE_BINARY_DIR}/schema/cpp/bind/min/*.hxx"
    "${CMAKE_BINARY_DIR}/schema/cpp/bind/min/*.cxx"
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
target_include_directories(DataModelBindings PRIVATE ${CMAKE_BINARY_DIR}/schema/cpp/bind)
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
                   COMMAND ${CMAKE_COMMAND} -E make_directory ${INSTALL_BIN}/${CONFIGURATION}${EX_CONFIG}
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:DataModelBindings> ${INSTALL_BIN}/${CONFIGURATION}${EX_CONFIG}
                   COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/xsd ${INSTALL_BIN}/xsd)
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
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/xsd DESTINATION ${INSTALL_BIN})
install_headers("${CMAKE_BINARY_DIR}/schema/cpp/bind" "bind")
