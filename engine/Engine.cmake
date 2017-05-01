# Files in the project (Relative to this CMAKE file)
file(GLOB BIOGEARS_FILES
  "cpp/*.h"
  "cpp/*.cpp"
)
list(REMOVE_ITEM BIOGEARS_FILES ${CMAKE_CURRENT_SOURCE_DIR}/cpp/BioGearsEngineJNI.h)
list(REMOVE_ITEM BIOGEARS_FILES ${CMAKE_CURRENT_SOURCE_DIR}/cpp/BioGearsEngineJNI.cpp)
list(REMOVE_ITEM BIOGEARS_FILES ${CMAKE_CURRENT_SOURCE_DIR}/cpp/BioGearsScenarioDriver.cpp)
list(REMOVE_ITEM BIOGEARS_FILES ${CMAKE_CURRENT_SOURCE_DIR}/cpp/BioGearsScenarioDriver.h)
list(REMOVE_ITEM BIOGEARS_FILES ${CMAKE_CURRENT_SOURCE_DIR}/cpp/Verification.cpp)
list(REMOVE_ITEM BIOGEARS_FILES ${CMAKE_CURRENT_SOURCE_DIR}/cpp/Verification.h)
list(REMOVE_ITEM BIOGEARS_FILES ${CMAKE_CURRENT_SOURCE_DIR}/cpp/stdafx.cpp)#PreCompiled Header Generator, will add later
set(SOURCE ${BIOGEARS_FILES})
file(GLOB BIOGEARS_CONTROLLER_FILES
  "cpp/Controller/*.h"
  "cpp/Controller/*.cpp"
)
list(APPEND SOURCE ${BIOGEARS_CONTROLLER_FILES})
file(GLOB BIOGEARS_SCENARIO_FILES
  "cpp/Controller/Scenario/*.h"
  "cpp/Controller/Scenario/*.cpp"
)
list(APPEND SOURCE ${BIOGEARS_SCENARIO_FILES})
file(GLOB BIOGEARS_EQUIPMENT_FILES
  "cpp/Equipment/*.h"
  "cpp/Equipment/*.cpp"
)
list(APPEND SOURCE ${BIOGEARS_EQUIPMENT_FILES})
file(GLOB BIOGEARS_SYSTEMS_FILES
  "cpp/Systems/*.h"
  "cpp/Systems/*.cpp"
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

target_include_directories(BioGearsEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/cpp)
target_include_directories(BioGearsEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../cdm/cpp)
target_include_directories(BioGearsEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../schema/cpp)
target_include_directories(BioGearsEngine PRIVATE ${EIGEN3_INCLUDE_DIR})
target_include_directories(BioGearsEngine PRIVATE ${LOG4CPP_INCLUDE_DIR})
target_include_directories(BioGearsEngine PRIVATE ${XercesC_INCLUDE_DIR})
target_include_directories(BioGearsEngine PRIVATE ${XSD_INCLUDE_DIR})

set_target_properties(BioGearsEngine PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(BioGearsEngine PROPERTIES COMPILE_FLAGS "${ENG_FLAGS}"  PREFIX "")

if(APPLE)
    set_target_properties(BioGearsEngine PROPERTIES MACOSX_RPATH ON)
endif()

# Dependent Libraries
target_link_libraries(BioGearsEngine CommonDataModel)

add_custom_command(TARGET BioGearsEngine POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:BioGearsEngine> ${INSTALL_BIN}/${CONFIGURATION}${EX_CONFIG})
install(TARGETS BioGearsEngine 
        RUNTIME CONFIGURATIONS Release DESTINATION ${INSTALL_BIN}/release${EX_CONFIG}
        LIBRARY CONFIGURATIONS Release DESTINATION ${INSTALL_LIB}/release${EX_CONFIG}
        ARCHIVE CONFIGURATIONS Release DESTINATION ${INSTALL_LIB}/release${EX_CONFIG})
install(TARGETS BioGearsEngine 
        RUNTIME CONFIGURATIONS Debug DESTINATION ${INSTALL_BIN}/debug${EX_CONFIG}
        LIBRARY CONFIGURATIONS Debug DESTINATION ${INSTALL_LIB}/debug${EX_CONFIG}
        ARCHIVE CONFIGURATIONS Debug DESTINATION ${INSTALL_LIB}/debug${EX_CONFIG})
install(TARGETS BioGearsEngine 
        RUNTIME CONFIGURATIONS RelWithDebInfo DESTINATION ${INSTALL_BIN}/relwithdebinfo${EX_CONFIG}
        LIBRARY CONFIGURATIONS RelWithDebInfo DESTINATION ${INSTALL_LIB}/relwithdebinfo${EX_CONFIG}
        ARCHIVE CONFIGURATIONS RelWithDebInfo DESTINATION ${INSTALL_LIB}/relwithdebinfo${EX_CONFIG})
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/cpp/BioGearsPhysiologyEngine.h DESTINATION ${INSTALL_INC}/include)