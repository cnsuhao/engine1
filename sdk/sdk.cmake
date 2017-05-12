project(BioGearsSDK)


file(GLOB SRC_FILES
  "howto/cpp/*.h"
  "howto/cpp/*.cpp"
)
source_group("" FILES ${SRC_FILES})
set(SOURCE ${SRC_FILES})
add_executable(HowToDriver EXCLUDE_FROM_ALL ${SOURCE})

# Preprocessor Definitions and Include Paths
set(FLAGS)
target_include_directories(HowToDriver PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(HowToDriver PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/cdm)
set_target_properties(HowToDriver PROPERTIES COMPILE_FLAGS "${FLAGS}" PREFIX "")
# Dependent Libraries
if(MSVC)
  set(D_LIB_FILES
    lib/debug${EX_CONFIG}/BioGearsEngine.lib
    lib/debug${EX_CONFIG}/CommonDataModel.lib
    lib/debug${EX_CONFIG}/DataModelBindings.lib
    lib/debug${EX_CONFIG}/log4cpp.lib
    lib/debug${EX_CONFIG}/xerces-c.lib
  )
  set(O_LIB_FILES
    lib/release${EX_CONFIG}/BioGearsEngine.lib
    lib/release${EX_CONFIG}/CommonDataModel.lib
    lib/release${EX_CONFIG}/DataModelBindings.lib
    lib/release${EX_CONFIG}/log4cpp.lib
    lib/release${EX_CONFIG}/xerces-c.lib
  )
elseif(UNIX)  
  set(D_LIB_FILES
    "lib/debug${EX_CONFIG}/BioGearsEngine.so"
    "lib/debug${EX_CONFIG}/CommonDataModel.so"
    "lib/debug${EX_CONFIG}/DataModelBindings.so"
    "lib/debug${EX_CONFIG}/log4cpp.so"
    "lib/debug${EX_CONFIG}/xerces-c.so"
  )
  set(O_LIB_FILES
    "lib/release${EX_CONFIG}/BioGearsEngine.so"
    "lib/release${EX_CONFIG}/CommonDataModel.so"
    "lib/release${EX_CONFIG}/DataModelBindings.so"
    "lib/release${EX_CONFIG}/log4cpp.so"
    "lib/release${EX_CONFIG}/xerces-c.so"
  )
else()
  set(D_LIB_FILES
    lib/debug/BioGearsEngine.lib
    lib/debug/CommonDataModel.lib
    lib/debug/DataModelBindings.lib
    lib/debug/log4cpp.lib
    lib/debug/xerces-c.lib
  )
  set(O_LIB_FILES
    lib/release/BioGearsEngine.lib
    lib/release/CommonDataModel.lib
    lib/release/DataModelBindings.lib
    lib/release/log4cpp.lib
    lib/release/xerces-c.lib
  )
endif()

foreach(file ${D_LIB_FILES})
	target_link_libraries(HowToDriver debug ${file})
endforeach()
foreach(file ${O_LIB_FILES})
	target_link_libraries(HowToDriver optimized ${file})
endforeach()
