project(PulseSDK)


file(GLOB SRC_FILES
  "howto/cpp/*.h"
  "howto/cpp/*.cpp"
)

source_group("" FILES ${SRC_FILES})
set(SOURCE ${SRC_FILES})
add_executable(HowToDriver EXCLUDE_FROM_ALL ${SOURCE})

# Preprocessor Definitions and Include Paths
set(FLAGS)
target_include_directories(HowToDriver PRIVATE ${CMAKE_INSTALL_PREFIX}/include)
target_include_directories(HowToDriver PRIVATE ${CMAKE_INSTALL_PREFIX}/include/cdm)
target_include_directories(HowToDriver PRIVATE ${CMAKE_INSTALL_PREFIX}/include/bind)
set_target_properties(HowToDriver PROPERTIES COMPILE_FLAGS "${FLAGS}" PREFIX "")
# Dependent Libraries

if(WIN32)
  set(lib_ext "lib")
  set(log4cpp_prefix "")
else()
  set(lib_ext "a")
  set(log4cpp_prefix "lib")
endif()

set(D_LIB_FILES
  ${CMAKE_INSTALL_PREFIX}/lib/debug${EX_CONFIG}/PulseEngine.${lib_ext}
  ${CMAKE_INSTALL_PREFIX}/lib/debug${EX_CONFIG}/CommonDataModel.${lib_ext}
  ${CMAKE_INSTALL_PREFIX}/lib/debug${EX_CONFIG}/DataModelBindings.${lib_ext}
  ${CMAKE_INSTALL_PREFIX}/lib/debug${EX_CONFIG}/${log4cpp_prefix}log4cpp.${lib_ext}
  ${CMAKE_INSTALL_PREFIX}/lib/debug${EX_CONFIG}/libprotobufd.${lib_ext}
)
set(O_LIB_FILES
  ${CMAKE_INSTALL_PREFIX}/lib/release${EX_CONFIG}/PulseEngine.${lib_ext}
  ${CMAKE_INSTALL_PREFIX}/lib/release${EX_CONFIG}/CommonDataModel.${lib_ext}
  ${CMAKE_INSTALL_PREFIX}/lib/release${EX_CONFIG}/DataModelBindings.${lib_ext}
  ${CMAKE_INSTALL_PREFIX}/lib/release${EX_CONFIG}/${log4cpp_prefix}log4cpp.${lib_ext}
  ${CMAKE_INSTALL_PREFIX}/lib/release${EX_CONFIG}/libprotobuf.${lib_ext}
)


foreach(file ${D_LIB_FILES})
	target_link_libraries(HowToDriver debug ${file})
endforeach()
foreach(file ${O_LIB_FILES})
	target_link_libraries(HowToDriver optimized ${file})
endforeach()

add_custom_command(TARGET HowToDriver POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E make_directory ${INSTALL_BIN}/${CONFIGURATION}${EX_CONFIG}
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:HowToDriver> ${INSTALL_BIN}/${CONFIGURATION}${EX_CONFIG})
