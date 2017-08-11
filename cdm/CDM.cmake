# Files in the project 
file(GLOB CDM_FILES "cpp/*.h" "cpp/*.cpp")
# Does not belong in this project
list(REMOVE_ITEM CDM_FILES ${CMAKE_CURRENT_SOURCE_DIR}/cpp/CommonDataModelJNI.cpp)
list(REMOVE_ITEM CDM_FILES ${CMAKE_CURRENT_SOURCE_DIR}/cpp/stdafx.cpp)#PreCompiled Header Generator, will add later
source_group("" FILES ${CDM_FILES})
set(SOURCE ${CDM_FILES})
# Circuit
file(GLOB CIRCUIT_FILES "cpp/circuit/*.h" "cpp/circuit/*.cpp" "cpp/circuit/*.inl")
source_group("Circuit" FILES ${CIRCUIT_FILES})
list(APPEND SOURCE ${CIRCUIT_FILES})  
# Circuit/Electrical
file(GLOB CIRCUIT_ELECTRICAL_FILES "cpp/circuit/electrical/*.h" "cpp/circuit/electrical/*.cpp" "cdm/cpp/circuit/electrical/*.inl")
source_group("Circuit\\Electrical" FILES ${CIRCUIT_ELECTRICAL_FILES})
list(APPEND SOURCE ${CIRCUIT_ELECTRICAL_FILES}) 
# Circuit/Fluid
file(GLOB CIRCUIT_FLUID_FILES "cpp/circuit/fluid/*.h" "cpp/circuit/fluid/*.cpp" "cpp/circuit/fluid/*.inl")
source_group("Circuit\\Fluid" FILES ${CIRCUIT_FLUID_FILES})
list(APPEND SOURCE ${CIRCUIT_FLUID_FILES}) 
# Circuit/Thermal
file(GLOB CIRCUIT_THERMAL_FILES "cpp/circuit/thermal/*.h" "cpp/circuit/thermal/*.cpp" "cpp/circuit/thermal/*.inl")
source_group("Circuit\\Thermal" FILES ${CIRCUIT_THERMAL_FILES})
list(APPEND SOURCE ${CIRCUIT_THERMAL_FILES}) 
# Compartment
file(GLOB COMPARTMENT_FILES "cpp/compartment/*.h" "cpp/compartment/*.cpp" "cpp/compartment/*.inl")
source_group("Compartment" FILES ${COMPARTMENT_FILES})
list(APPEND SOURCE ${COMPARTMENT_FILES}) 
# Compartment/Fluid
file(GLOB COMPARTMENT_FLUID_FILES "cpp/compartment/fluid/*.h" "cpp/compartment/fluid/*.cpp" "cpp/compartment/fluid/*.inl")
source_group("Compartment\\Fluid" FILES ${COMPARTMENT_FLUID_FILES})
list(APPEND SOURCE ${COMPARTMENT_FLUID_FILES}) 
# Compartment/Thermal
file(GLOB COMPARTMENT_THERMAL_FILES "cpp/compartment/thermal/*.h" "cpp/compartment/thermal/*.cpp" "cpp/compartment/thermal/*.inl")
source_group("Compartment\\Thermal" FILES ${COMPARTMENT_THERMAL_FILES})
list(APPEND SOURCE ${COMPARTMENT_THERMAL_FILES}) 
# Compartment/Tissue
file(GLOB COMPARTMENT_TISSUE_FILES "cpp/compartment/tissue/*.h" "cpp/compartment/tissue/*.cpp" "cpp/compartment/tissue/*.inl")
source_group("Compartment\\Tissue" FILES ${COMPARTMENT_TISSUE_FILES})
list(APPEND SOURCE ${COMPARTMENT_TISSUE_FILES}) 
# Compartment/Managers
file(GLOB COMPARTMENT_MANAGERS_FILES "cpp/compartment/managers/*.h" "cpp/compartment/managers/*.cpp")
source_group("Compartment\\Managers" FILES ${COMPARTMENT_MANAGERS_FILES})
list(APPEND SOURCE ${COMPARTMENT_MANAGERS_FILES}) 
# Substance Quantity
file(GLOB SUBSTANCE_QUANTITY_FILES "cpp/compartment/substances/*.h" "cpp/compartment/substances/*.cpp" "cpp/compartment/substances/*.inl")
source_group("Compartment\\Substances" FILES ${SUBSTANCE_QUANTITY_FILES})
list(APPEND SOURCE ${SUBSTANCE_QUANTITY_FILES}) 
# Patient
file(GLOB PATIENT_FILES "cpp/patient/*.h" "cpp/patient/*.cpp")
source_group("Patient" FILES ${PATIENT_FILES})
file(GLOB PATIENT_ACTION_FILES "cpp/patient/actions/*.h" "cpp/patient/actions/*.cpp")
source_group("Patient\\Actions" FILES ${PATIENT_ACTION_FILES})
file(GLOB PATIENT_ASSESSMENT_FILES "cpp/patient/assessments/*.h" "cpp/patient/assessments/*.cpp")
source_group("Patient\\Assessments" FILES ${PATIENT_ASSESSMENT_FILES})
file(GLOB PATIENT_CONDITIONS_FILES "cpp/patient/conditions/*.h" "cpp/patient/conditions/*.cpp")
source_group("Patient\\Conditions" FILES ${PATIENT_CONDITIONS_FILES})
list(APPEND SOURCE ${PATIENT_FILES}) 
list(APPEND SOURCE ${PATIENT_ACTION_FILES}) 
list(APPEND SOURCE ${PATIENT_ASSESSMENT_FILES}) 
list(APPEND SOURCE ${PATIENT_CONDITIONS_FILES}) 
# Properties
file(GLOB PROPERTY_FILES "cpp/properties/*.h" "cpp/properties/*.cpp" "cpp/properties/*.inl")
# Remove SEArray* files as arrays are not supported yet
foreach(f ${PROPERTY_FILES})  
  string(FIND ${f} "SEArray" idx)
  if(${idx} GREATER -1)
    list(REMOVE_ITEM PROPERTY_FILES ${f})
  endif()
endforeach()
source_group("Properties" FILES ${PROPERTY_FILES})
list(APPEND SOURCE ${PROPERTY_FILES}) 
# Scenario
file(GLOB SCENARIO_FILES "cpp/scenario/*.h" "cpp/scenario/*.cpp")
source_group("Scenario" FILES ${SCENARIO_FILES})
list(APPEND SOURCE ${SCENARIO_FILES}) 
# Engine
file(GLOB ENGINE_FILES "cpp/engine/*.h" "cpp/engine/*.cpp")
source_group("Engine" FILES ${ENGINE_FILES})
list(APPEND SOURCE ${ENGINE_FILES})    
# Substance
file(GLOB SUBSTANCE_FILES "cpp/substance/*.h" "cpp/substance/*.cpp" "cpp/substance/*.inl")
source_group("Substance" FILES ${SUBSTANCE_FILES})
list(APPEND SOURCE ${SUBSTANCE_FILES})
# System
file(GLOB SYSTEM_FILES "cpp/system/*.h" "cpp/system/*.cpp")
source_group("System" FILES ${SYSTEM_FILES})
list(APPEND SOURCE ${SYSTEM_FILES}) 
# System\Environment
file(GLOB ENVIRONMENT_FILES "cpp/system/environment/*.h" "cpp/system/environment/*.cpp")
source_group("System\\Environment" FILES ${ENVIRONMENT_FILES})
list(APPEND SOURCE ${ENVIRONMENT_FILES}) 
file(GLOB ENVIRONMENT_ACTION_FILES "cpp/system/environment/actions/*.h" "cpp/system/environment/actions/*.cpp")
source_group("System\\Environment\\Actions" FILES ${ENVIRONMENT_ACTION_FILES})
list(APPEND SOURCE ${ENVIRONMENT_ACTION_FILES}) 
file(GLOB ENVIRONMENT_CONDITION_FILES "cpp/system/environment/conditions/*.h" "cpp/system/environment/conditions/*.cpp")
source_group("System\\Environment\\Conditions" FILES ${ENVIRONMENT_CONDITION_FILES})
list(APPEND SOURCE ${ENVIRONMENT_CONDITION_FILES}) 
# System\Equipment
file(GLOB ANESTHESIA_FILES "cpp/system/equipment/Anesthesia/*.h" "cpp/system/equipment/Anesthesia/*.cpp")
source_group("System\\Equipment\\Anesthesia" FILES ${ANESTHESIA_FILES})
file(GLOB ANESTHESIA_ACTION_FILES "cpp/system/equipment/Anesthesia/actions/*.h" "cpp/system/equipment/Anesthesia/actions/*.cpp")
source_group("System\\Equipment\\Anesthesia\\Actions" FILES ${ANESTHESIA_ACTION_FILES})
file(GLOB ECG_FILES "cpp/system/equipment/ElectroCardioGram/*.h" "cpp/system/equipment/ElectroCardioGram/*.cpp")
source_group("System\\Equipment\\ECG" FILES ${ECG_FILES})
file(GLOB INHALER_FILES "cpp/system/equipment/Inhaler/*.h" "cpp/system/equipment/Inhaler/*.cpp")
source_group("System\\Equipment\\Inhaler" FILES ${INHALER_FILES})
file(GLOB INHALER_ACTION_FILES "cpp/system/equipment/Inhaler/actions/*.h" "cpp/system/equipment/Inhaler/actions/*.cpp")
source_group("System\\Equipment\\Inhaler\\Actions" FILES ${INHALER_ACTION_FILES})

list(APPEND SOURCE ${ANESTHESIA_FILES}) 
list(APPEND SOURCE ${ANESTHESIA_ACTION_FILES}) 
list(APPEND SOURCE ${ECG_FILES}) 
list(APPEND SOURCE ${INHALER_FILES}) 
list(APPEND SOURCE ${INHALER_ACTION_FILES}) 
list(APPEND SOURCE ${MECHANICAL_VENTILATOR_FILES}) 
list(APPEND SOURCE ${MECHANICAL_VENTILATOR_ACTION_FILES}) 
# System\Physiology
file(GLOB PHYSIOLOGY_FILES "cpp/system/physiology/*.h" "cpp/system/physiology/*.cpp")
source_group("System\\Physiology" FILES ${PHYSIOLOGY_FILES})
list(APPEND SOURCE ${PHYSIOLOGY_FILES}) 
# Utils
file(GLOB UTILS_FILES "cpp/utils/*.h" "cpp/utils/*.cpp")
source_group("Utils" FILES ${UTILS_FILES})
file(GLOB UTILS_TESTING_FILES "cpp/utils/testing/*.h" "cpp/utils/testing/*.cpp")
source_group("Utils\\Testing" FILES ${UTILS_TESTING_FILES})
# Utils\UnitConversion
file(GLOB UTILS_UCE_FILES "cpp/utils/unitconversion/*.h" "cpp/utils/unitconversion/*.cpp")
list(REMOVE_ITEM UTILS_UCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/cpp/utils/unitconversion/UnitConversionDriver.cpp)
source_group("Utils\\UnitConversion" FILES ${UTILS_UCE_FILES})
# Utils\TaskRunner
file(GLOB UTILS_TASKRUNNER_FILES "cpp/utils/TaskRunner/*.h" "cpp/utils/TaskRunner/*.cpp")
source_group("Utils\\TaskRunner" FILES ${UTILS_TASKRUNNER_FILES})
list(APPEND SOURCE ${UTILS_TASKRUNNER_FILES}) 
#file(GLOB UTILS_XPSTL_FILES "cpp/utils/xpstl/*.h" "cpp/utils/xpstl/*.cpp")
#source_group("Utils\\XPSTL" FILES ${UTILS_XPSTL_FILES})
list(APPEND SOURCE ${UTILS_FILES}) 
list(APPEND SOURCE ${UTILS_TESTING_FILES}) 
list(APPEND SOURCE ${UTILS_UCE_FILES}) 
#list(APPEND SOURCE ${UTILS_XPSTL_FILES}) 

# The DLL we are building
add_library(CommonDataModel ${SOURCE})
# Preprocessor Definitions and Include Paths
# Common Compile Flags
set(CDM_FLAGS)
set(CDM_FLAGS "${CDM_FLAGS} -D EIGEN_MPL2_ONLY")
set(CDM_FLAGS "${CDM_FLAGS} -D UNICODE")
set(CDM_FLAGS "${CDM_FLAGS} -D _UNICODE")
if(${BUILD_SHARED_LIBS}) 
  set(CDM_FLAGS "${CDM_FLAGS} -D SHARED_CDM")
endif()
if(MSVC)
  set(CDM_FLAGS "${CDM_FLAGS} -Zm215")
  if(EX_PLATFORM EQUAL 64)
    #Make sure to prepend a space
    set(CDM_FLAGS  "${CDM_FLAGS}  /bigobj")
  endif()
  
endif(MSVC)
target_include_directories(CommonDataModel PRIVATE ${CMAKE_BINARY_DIR}/schema/cpp/bind)
target_include_directories(CommonDataModel PRIVATE ${CMAKE_BINARY_DIR}/schema/cpp/)
target_include_directories(CommonDataModel PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/cpp)
target_include_directories(CommonDataModel PRIVATE ${EIGEN3_INCLUDE_DIR})
target_include_directories(CommonDataModel PRIVATE ${LOG4CPP_INCLUDE_DIR})
target_include_directories(CommonDataModel PRIVATE ${PROTOBUF_INCLUDE_DIR})
if(WIN32)
  target_include_directories(CommonDataModel PRIVATE ${DIRENT_INCLUDE_DIR})
endif()

set_target_properties(CommonDataModel PROPERTIES COMPILE_FLAGS "${CDM_FLAGS}" PREFIX "")
if(APPLE)
    set_target_properties(CommonDataModel PROPERTIES MACOSX_RPATH ON)
endif()
target_link_libraries(CommonDataModel DataModelBindings)
target_link_libraries(CommonDataModel log4cpp)

if(${BUILD_SHARED_LIBS})
  add_custom_command(TARGET CommonDataModel POST_BUILD
                     COMMAND ${CMAKE_COMMAND} -E make_directory ${INSTALL_BIN}/${CONFIGURATION}${EX_CONFIG}
                     COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:CommonDataModel> ${INSTALL_BIN}/${CONFIGURATION}${EX_CONFIG})

  if(WIN32)# Copy dll files to the bin
    install(TARGETS CommonDataModel 
            RUNTIME CONFIGURATIONS Release DESTINATION ${INSTALL_BIN}/release${EX_CONFIG}
            LIBRARY CONFIGURATIONS Release DESTINATION ${INSTALL_BIN}/release${EX_CONFIG})
    install(TARGETS CommonDataModel 
            RUNTIME CONFIGURATIONS Debug DESTINATION ${INSTALL_BIN}/debug${EX_CONFIG}
            LIBRARY CONFIGURATIONS Debug DESTINATION ${INSTALL_BIN}/debug${EX_CONFIG})
    install(TARGETS CommonDataModel 
            RUNTIME CONFIGURATIONS RelWithDebInfo DESTINATION ${INSTALL_BIN}/relwithdebinfo${EX_CONFIG}
            LIBRARY CONFIGURATIONS RelWithDebInfo DESTINATION ${INSTALL_BIN}/relwithdebinfo${EX_CONFIG})
  else()# Copy so files to the bin
    install(TARGETS CommonDataModel 
            LIBRARY CONFIGURATIONS Release DESTINATION ${INSTALL_BIN}/release${EX_CONFIG})
    install(TARGETS CommonDataModel 
            LIBRARY CONFIGURATIONS Debug DESTINATION ${INSTALL_BIN}/debug${EX_CONFIG})
    install(TARGETS CommonDataModel 
            LIBRARY CONFIGURATIONS RelWithDebInfo DESTINATION ${INSTALL_BIN}/relwithdebinfo${EX_CONFIG})
  endif()
endif()
# Copy lib/so files to the sdk/lib
install(TARGETS CommonDataModel         
        LIBRARY CONFIGURATIONS Release DESTINATION ${INSTALL_LIB}/release${EX_CONFIG}
        ARCHIVE CONFIGURATIONS Release DESTINATION ${INSTALL_LIB}/release${EX_CONFIG})
install(TARGETS CommonDataModel 
        LIBRARY CONFIGURATIONS Debug DESTINATION ${INSTALL_LIB}/debug${EX_CONFIG}
        ARCHIVE CONFIGURATIONS Debug DESTINATION ${INSTALL_LIB}/debug${EX_CONFIG})
install(TARGETS CommonDataModel  
        LIBRARY CONFIGURATIONS RelWithDebInfo DESTINATION ${INSTALL_LIB}/relwithdebinfo${EX_CONFIG}
        ARCHIVE CONFIGURATIONS RelWithDebInfo DESTINATION ${INSTALL_LIB}/relwithdebinfo${EX_CONFIG})
install_headers("${CMAKE_CURRENT_SOURCE_DIR}/cpp" "cdm")

