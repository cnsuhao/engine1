source_group("" FILES cpp/CommonDataModelJNI.cpp)

add_library(CommonDataModelJNI SHARED cpp/CommonDataModelJNI.cpp)

find_package(JNI REQUIRED)
target_include_directories(CommonDataModelJNI PRIVATE ${JNI_INCLUDE_DIRS})
target_include_directories(CommonDataModelJNI PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/cpp)
target_include_directories(CommonDataModelJNI PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../cdm/cpp)
target_include_directories(CommonDataModelJNI PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../schema/cpp/)
target_include_directories(CommonDataModelJNI PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../test/cdm/cpp)
target_include_directories(CommonDataModelJNI PRIVATE ${EIGEN3_INCLUDE_DIR})
target_include_directories(CommonDataModelJNI PRIVATE ${LOG4CPP_INCLUDE_DIR})
target_include_directories(CommonDataModelJNI PRIVATE ${XercesC_INCLUDE_DIR})
target_include_directories(CommonDataModelJNI PRIVATE ${XSD_INCLUDE_DIR})

set(CDM_JNI_FLAGS)
set_target_properties(CommonDataModelJNI PROPERTIES COMPILE_FLAGS "${CDM_JNI_FLAGS}" PREFIX "")      

if(APPLE)
    set_target_properties(CommonDataModelJNI PROPERTIES MACOSX_RPATH ON)
endif()

# Dependent Libraries
target_link_libraries(CommonDataModelJNI CommonDataModelUnitTests)

add_custom_command(TARGET CommonDataModelJNI POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:CommonDataModelJNI> ${INSTALL_BIN}/${CONFIGURATION}${EX_CONFIG})
install(TARGETS CommonDataModelJNI 
        RUNTIME CONFIGURATIONS Release DESTINATION ${INSTALL_BIN}/release${EX_CONFIG})
install(TARGETS CommonDataModelJNI 
        RUNTIME CONFIGURATIONS Debug DESTINATION ${INSTALL_BIN}/debug${EX_CONFIG})
install(TARGETS CommonDataModelJNI 
        RUNTIME CONFIGURATIONS RelWithDebInfo DESTINATION ${INSTALL_BIN}/relwithdebinfo${EX_CONFIG})
