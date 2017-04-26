# Files in the project 
file(GLOB CDM_FILES "cdm/cpp/*.h" "cdm/cpp/*.cpp")
# Does not belong in this project
list(REMOVE_ITEM CDM_FILES ${CMAKE_CURRENT_SOURCE_DIR}/cdm/cpp/CommonDataModelJNI.cpp)
list(REMOVE_ITEM CDM_FILES ${CMAKE_CURRENT_SOURCE_DIR}/cdm/cpp/stdafx.cpp)#PreCompiled Header Generator, will add later
source_group("" FILES ${CDM_FILES})
set(SOURCE ${CDM_FILES})
# Circuit
file(GLOB CIRCUIT_FILES "cdm/cpp/circuit/*.h" "cdm/cpp/circuit/*.cpp" "cdm/cpp/circuit/*.inl")
source_group("Circuit" FILES ${CIRCUIT_FILES})
list(APPEND SOURCE ${CIRCUIT_FILES})  
# Circuit/Electrical
file(GLOB CIRCUIT_ELECTRICAL_FILES "cdm/cpp/circuit/electrical/*.h" "cdm/cpp/circuit/electrical/*.cpp" "cdm/cpp/circuit/electrical/*.inl")
source_group("Circuit\\Electrical" FILES ${CIRCUIT_ELECTRICAL_FILES})
list(APPEND SOURCE ${CIRCUIT_ELECTRICAL_FILES}) 
# Circuit/Fluid
file(GLOB CIRCUIT_FLUID_FILES "cdm/cpp/circuit/fluid/*.h" "cdm/cpp/circuit/fluid/*.cpp" "cdm/cpp/circuit/fluid/*.inl")
source_group("Circuit\\Fluid" FILES ${CIRCUIT_FLUID_FILES})
list(APPEND SOURCE ${CIRCUIT_FLUID_FILES}) 
# Circuit/Thermal
file(GLOB CIRCUIT_THERMAL_FILES "cdm/cpp/circuit/thermal/*.h" "cdm/cpp/circuit/thermal/*.cpp" "cdm/cpp/circuit/thermal/*.inl")
source_group("Circuit\\Thermal" FILES ${CIRCUIT_THERMAL_FILES})
list(APPEND SOURCE ${CIRCUIT_THERMAL_FILES}) 
# Compartment
file(GLOB COMPARTMENT_FILES "cdm/cpp/compartment/*.h" "cdm/cpp/compartment/*.cpp" "cdm/cpp/compartment/*.inl")
source_group("Compartment" FILES ${COMPARTMENT_FILES})
list(APPEND SOURCE ${COMPARTMENT_FILES}) 
# Compartment/Fluid
file(GLOB COMPARTMENT_FLUID_FILES "cdm/cpp/compartment/fluid/*.h" "cdm/cpp/compartment/fluid/*.cpp" "cdm/cpp/compartment/fluid/*.inl")
source_group("Compartment\\Fluid" FILES ${COMPARTMENT_FLUID_FILES})
list(APPEND SOURCE ${COMPARTMENT_FLUID_FILES}) 
# Compartment/Thermal
file(GLOB COMPARTMENT_THERMAL_FILES "cdm/cpp/compartment/thermal/*.h" "cdm/cpp/compartment/thermal/*.cpp" "cdm/cpp/compartment/thermal/*.inl")
source_group("Compartment\\Thermal" FILES ${COMPARTMENT_THERMAL_FILES})
list(APPEND SOURCE ${COMPARTMENT_THERMAL_FILES}) 
# Compartment/Tissue
file(GLOB COMPARTMENT_TISSUE_FILES "cdm/cpp/compartment/tissue/*.h" "cdm/cpp/compartment/tissue/*.cpp" "cdm/cpp/compartment/tissue/*.inl")
source_group("Compartment\\Tissue" FILES ${COMPARTMENT_TISSUE_FILES})
list(APPEND SOURCE ${COMPARTMENT_TISSUE_FILES}) 
# Compartment/Managers
file(GLOB COMPARTMENT_MANAGERS_FILES "cdm/cpp/compartment/managers/*.h" "cdm/cpp/compartment/managers/*.cpp")
source_group("Compartment\\Managers" FILES ${COMPARTMENT_MANAGERS_FILES})
list(APPEND SOURCE ${COMPARTMENT_MANAGERS_FILES}) 
# Substance Quantity
file(GLOB SUBSTANCE_QUANTITY_FILES "cdm/cpp/compartment/substances/*.h" "cdm/cpp/compartment/substances/*.cpp" "cdm/cpp/compartment/substances/*.inl")
source_group("Compartment\\Substances" FILES ${SUBSTANCE_QUANTITY_FILES})
list(APPEND SOURCE ${SUBSTANCE_QUANTITY_FILES}) 
# Patient
file(GLOB PATIENT_FILES "cdm/cpp/patient/*.h" "cdm/cpp/patient/*.cpp")
source_group("Patient" FILES ${PATIENT_FILES})
file(GLOB PATIENT_ACTION_FILES "cdm/cpp/patient/actions/*.h" "cdm/cpp/patient/actions/*.cpp")
source_group("Patient\\Actions" FILES ${PATIENT_ACTION_FILES})
file(GLOB PATIENT_ASSESSMENT_FILES "cdm/cpp/patient/assessments/*.h" "cdm/cpp/patient/assessments/*.cpp")
source_group("Patient\\Assessments" FILES ${PATIENT_ASSESSMENT_FILES})
file(GLOB PATIENT_CONDITIONS_FILES "cdm/cpp/patient/conditions/*.h" "cdm/cpp/patient/conditions/*.cpp")
source_group("Patient\\Conditions" FILES ${PATIENT_CONDITIONS_FILES})
list(APPEND SOURCE ${PATIENT_FILES}) 
list(APPEND SOURCE ${PATIENT_ACTION_FILES}) 
list(APPEND SOURCE ${PATIENT_ASSESSMENT_FILES}) 
list(APPEND SOURCE ${PATIENT_CONDITIONS_FILES}) 
# Properties
file(GLOB PROPERTY_FILES "cdm/cpp/properties/*.h" "cdm/cpp/properties/*.cpp" "cdm/cpp/properties/*.inl")
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
file(GLOB SCENARIO_FILES "cdm/cpp/scenario/*.h" "cdm/cpp/scenario/*.cpp")
source_group("Scenario" FILES ${SCENARIO_FILES})
list(APPEND SOURCE ${SCENARIO_FILES}) 
file(GLOB SCENARIO_DATA_REQUEST_FILES "cdm/cpp/scenario/requests/*.h" "cdm/cpp/scenario/requests/*.cpp")
source_group("Scenario\\Data Requests" FILES ${SCENARIO_DATA_REQUEST_FILES})
list(APPEND SOURCE ${SCENARIO_DATA_REQUEST_FILES}) 
# Engine
file(GLOB ENGINE_FILES "cdm/cpp/engine/*.h" "cdm/cpp/engine/*.cpp")
source_group("Engine" FILES ${ENGINE_FILES})
list(APPEND SOURCE ${ENGINE_FILES})    
# Substance
file(GLOB SUBSTANCE_FILES "cdm/cpp/substance/*.h" "cdm/cpp/substance/*.cpp" "cdm/cpp/substance/*.inl")
source_group("Substance" FILES ${SUBSTANCE_FILES})
list(APPEND SOURCE ${SUBSTANCE_FILES})
# System
file(GLOB SYSTEM_FILES "cdm/cpp/system/*.h" "cdm/cpp/system/*.cpp")
source_group("System" FILES ${SYSTEM_FILES})
list(APPEND SOURCE ${SYSTEM_FILES}) 
# System\Environment
file(GLOB ENVIRONMENT_FILES "cdm/cpp/system/environment/*.h" "cdm/cpp/system/environment/*.cpp")
source_group("System\\Environment" FILES ${ENVIRONMENT_FILES})
list(APPEND SOURCE ${ENVIRONMENT_FILES}) 
file(GLOB ENVIRONMENT_ACTION_FILES "cdm/cpp/system/environment/actions/*.h" "cdm/cpp/system/environment/actions/*.cpp")
source_group("System\\Environment\\Actions" FILES ${ENVIRONMENT_ACTION_FILES})
list(APPEND SOURCE ${ENVIRONMENT_ACTION_FILES}) 
file(GLOB ENVIRONMENT_CONDITION_FILES "cdm/cpp/system/environment/conditions/*.h" "cdm/cpp/system/environment/conditions/*.cpp")
source_group("System\\Environment\\Conditions" FILES ${ENVIRONMENT_CONDITION_FILES})
list(APPEND SOURCE ${ENVIRONMENT_CONDITION_FILES}) 
# System\Equipment
file(GLOB ANESTHESIA_FILES "cdm/cpp/system/equipment/Anesthesia/*.h" "cdm/cpp/system/equipment/Anesthesia/*.cpp")
source_group("System\\Equipment\\Anesthesia" FILES ${ANESTHESIA_FILES})
file(GLOB ANESTHESIA_ACTION_FILES "cdm/cpp/system/equipment/Anesthesia/actions/*.h" "cdm/cpp/system/equipment/Anesthesia/actions/*.cpp")
source_group("System\\Equipment\\Anesthesia\\Actions" FILES ${ANESTHESIA_ACTION_FILES})
file(GLOB ECG_FILES "cdm/cpp/system/equipment/ElectroCardioGram/*.h" "cdm/cpp/system/equipment/ElectroCardioGram/*.cpp")
source_group("System\\Equipment\\ECG" FILES ${ECG_FILES})
file(GLOB INHALER_FILES "cdm/cpp/system/equipment/Inhaler/*.h" "cdm/cpp/system/equipment/Inhaler/*.cpp")
source_group("System\\Equipment\\Inhaler" FILES ${INHALER_FILES})
file(GLOB INHALER_ACTION_FILES "cdm/cpp/system/equipment/Inhaler/actions/*.h" "cdm/cpp/system/equipment/Inhaler/actions/*.cpp")
source_group("System\\Equipment\\Inhaler\\Actions" FILES ${INHALER_ACTION_FILES})

list(APPEND SOURCE ${ANESTHESIA_FILES}) 
list(APPEND SOURCE ${ANESTHESIA_ACTION_FILES}) 
list(APPEND SOURCE ${ECG_FILES}) 
list(APPEND SOURCE ${INHALER_FILES}) 
list(APPEND SOURCE ${INHALER_ACTION_FILES}) 
list(APPEND SOURCE ${MECHANICAL_VENTILATOR_FILES}) 
list(APPEND SOURCE ${MECHANICAL_VENTILATOR_ACTION_FILES}) 
# System\Physiology
file(GLOB PHYSIOLOGY_FILES "cdm/cpp/system/physiology/*.h" "cdm/cpp/system/physiology/*.cpp")
source_group("System\\Physiology" FILES ${PHYSIOLOGY_FILES})
list(APPEND SOURCE ${PHYSIOLOGY_FILES}) 
# Utils
file(GLOB UTILS_FILES "cdm/cpp/utils/*.h" "cdm/cpp/utils/*.cpp")
source_group("Utils" FILES ${UTILS_FILES})
file(GLOB UTILS_TESTING_FILES "cdm/cpp/utils/testing/*.h" "cdm/cpp/utils/testing/*.cpp")
source_group("Utils\\Testing" FILES ${UTILS_TESTING_FILES})
# Utils\UnitConversion
file(GLOB UTILS_UCE_FILES "cdm/cpp/utils/unitconversion/*.h" "cdm/cpp/utils/unitconversion/*.cpp")
list(REMOVE_ITEM UTILS_UCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/cdm/cpp/utils/unitconversion/UnitConversionDriver.cpp)
source_group("Utils\\UnitConversion" FILES ${UTILS_UCE_FILES})
# Utils\TaskRunner
file(GLOB UTILS_TASKRUNNER_FILES "cdm/cpp/utils/TaskRunner/*.h" "cdm/cpp/utils/TaskRunner/*.cpp")
source_group("Utils\\TaskRunner" FILES ${UTILS_TASKRUNNER_FILES})
list(APPEND SOURCE ${UTILS_TASKRUNNER_FILES}) 
#file(GLOB UTILS_XPSTL_FILES "cdm/cpp/utils/xpstl/*.h" "cdm/cpp/utils/xpstl/*.cpp")
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
set(CDM_FLAGS "${CDM_FLAGS} -D COMMONDATAMODEL_EXPORTS")
set(CDM_FLAGS "${CDM_FLAGS} -D UNICODE")
set(CDM_FLAGS "${CDM_FLAGS} -D _UNICODE")
if(MSVC)  
  set(CDM_FLAGS "${CDM_FLAGS} -Zm215")
  if(EX_PLATFORM EQUAL 64)
    #Make sure to prepend a space
    set(CDM_FLAGS  "${CDM_FLAGS}  /bigobj")
  endif()
  
endif(MSVC)
target_include_directories(CommonDataModel PRIVATE "cdm/cpp")
target_include_directories(CommonDataModel PRIVATE "schema/cpp")
target_include_directories(CommonDataModel PRIVATE ${xsd_DIR}/libxsd)
target_include_directories(CommonDataModel PRIVATE ${xerces_DIR}/include/)
target_include_directories(CommonDataModel PRIVATE ${eigen_DIR}/include/)
target_include_directories(CommonDataModel PRIVATE ${log4cpp_DIR}/include/)
if(WIN32)
  target_include_directories(CommonDataModel PRIVATE ${dirent_DIR}/include)
endif()

set_target_properties(CommonDataModel PROPERTIES COMPILE_FLAGS "${CDM_FLAGS}" PREFIX "")
if(APPLE)
    set_target_properties(CommonDataModel PROPERTIES MACOSX_RPATH ON)
endif()
