# Files in the project (Relative to this CMAKE file)
file(GLOB BIOGEARS_FILES
  "engine/cpp/*.h"
  "engine/cpp/*.cpp"
)
list(REMOVE_ITEM BIOGEARS_FILES ${CMAKE_CURRENT_SOURCE_DIR}/engine/cpp/BioGearsEngineJNI.h)
list(REMOVE_ITEM BIOGEARS_FILES ${CMAKE_CURRENT_SOURCE_DIR}/engine/cpp/BioGearsEngineJNI.cpp)
list(REMOVE_ITEM BIOGEARS_FILES ${CMAKE_CURRENT_SOURCE_DIR}/engine/cpp/BioGearsScenarioDriver.cpp)
list(REMOVE_ITEM BIOGEARS_FILES ${CMAKE_CURRENT_SOURCE_DIR}/engine/cpp/BioGearsScenarioDriver.h)
list(REMOVE_ITEM BIOGEARS_FILES ${CMAKE_CURRENT_SOURCE_DIR}/engine/cpp/Verification.cpp)
list(REMOVE_ITEM BIOGEARS_FILES ${CMAKE_CURRENT_SOURCE_DIR}/engine/cpp/Verification.h)
list(REMOVE_ITEM BIOGEARS_FILES ${CMAKE_CURRENT_SOURCE_DIR}/engine/cpp/stdafx.cpp)#PreCompiled Header Generator, will add later
set(SOURCE ${BIOGEARS_FILES})
file(GLOB BIOGEARS_CONTROLLER_FILES
  "engine/cpp/Controller/*.h"
  "engine/cpp/Controller/*.cpp"
)
list(APPEND SOURCE ${BIOGEARS_CONTROLLER_FILES})
file(GLOB BIOGEARS_SCENARIO_FILES
  "engine/cpp/Controller/Scenario/*.h"
  "engine/cpp/Controller/Scenario/*.cpp"
)
list(APPEND SOURCE ${BIOGEARS_SCENARIO_FILES})
file(GLOB BIOGEARS_EQUIPMENT_FILES
  "engine/cpp/Equipment/*.h"
  "engine/cpp/Equipment/*.cpp"
)
list(APPEND SOURCE ${BIOGEARS_EQUIPMENT_FILES})
file(GLOB BIOGEARS_SYSTEMS_FILES
  "engine/cpp/Systems/*.h"
  "engine/cpp/Systems/*.cpp"
)
list(APPEND SOURCE ${BIOGEARS_SYSTEMS_FILES})
# Set up Filters
source_group("" FILES ${BIOGEARS_FILES})
source_group("Controller" FILES ${BIOGEARS_CONTROLLER_FILES})
source_group("Controller\\Scenario" FILES ${BIOGEARS_SCENARIO_FILES})
source_group("Equipment" FILES ${BIOGEARS_EQUIPMENT_FILES})
source_group("Systems" FILES ${BIOGEARS_SYSTEMS_FILES})

# The DLL we are building
add_library(BioGearsEngine SHARED ${SOURCE})
# Preprocessor Definitions and Include Paths
set(ENG_FLAGS)
set(ENG_FLAGS "${ENG_FLAGS} -D BIOGEARS_EXPORT")
set(ENG_FLAGS "${ENG_FLAGS} -D UNICODE")
set(ENG_FLAGS "${ENG_FLAGS} -D _UNICODE")
if(MSVC)  
  set(ENG_FLAGS "${ENG_FLAGS} -Zm120")
endif(MSVC)

target_include_directories(BioGearsEngine PRIVATE "engine/cpp")
target_include_directories(BioGearsEngine PRIVATE "cdm/cpp")
target_include_directories(BioGearsEngine PRIVATE "schema/cpp")
target_include_directories(BioGearsEngine PRIVATE ${xsd_DIR}/libxsd)
target_include_directories(BioGearsEngine PRIVATE ${xerces_DIR}/include/)
target_include_directories(BioGearsEngine PRIVATE ${eigen_DIR}/include/)
target_include_directories(BioGearsEngine PRIVATE ${log4cpp_DIR}/include/)
if(WIN32)
  target_include_directories(BioGearsEngine PRIVATE ${dirent_DIR}/include)
endif()

set_target_properties(BioGearsEngine PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(BioGearsEngine PROPERTIES COMPILE_FLAGS "${ENG_FLAGS}"  PREFIX "")

if(APPLE)
    set_target_properties(BioGearsEngine PROPERTIES MACOSX_RPATH ON)
endif()

# Dependent Libraries
target_link_libraries(BioGearsEngine CommonDataModel)
target_link_libraries(BioGearsEngine DataModelBindings)
target_link_libraries(BioGearsEngine ${log4cpp_DIR}/lib/log4cpp.lib)
target_link_libraries(BioGearsEngine ${xerces_DIR}/lib/xerces-c.lib)
