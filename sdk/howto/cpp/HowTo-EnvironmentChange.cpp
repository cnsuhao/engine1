/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "EngineHowTo.h"

// Include the various types you will be using in your code
#include "system/environment/SEActiveConditioning.h"
#include "system/environment/actions/SEChangeEnvironmentConditions.h"
#include "system/environment/actions/SEThermalApplication.h"
#include "system/physiology/SEBloodChemistrySystem.h"
#include "system/physiology/SECardiovascularSystem.h"
#include "system/physiology/SEEnergySystem.h"
#include "system/physiology/SERespiratorySystem.h"
#include "substance/SESubstanceManager.h"
#include "substance/SESubstanceCompound.h"
#include "properties/SEScalar0To1.h"
#include "properties/SEScalarFrequency.h"
#include "properties/SEScalarHeatResistanceArea.h"
#include "properties/SEScalarLengthPerTime.h"
#include "properties/SEScalarMass.h"
#include "properties/SEScalarMassPerVolume.h"
#include "properties/SEScalarPressure.h"
#include "properties/SEScalarTemperature.h"
#include "properties/SEScalarTime.h"
#include "properties/SEScalarVolume.h"
#include "properties/SEScalarVolumePerTime.h"
#include "properties/SEScalarPower.h"
#include "properties/SEScalarFlowResistance.h"
#include "substance/SESubstanceFraction.h"
#include "engine/SEEngineTracker.h"
#include "compartment/SECompartmentManager.h"

#include "system/environment/conditions/SEInitialEnvironmentConditions.h"

//--------------------------------------------------------------------------------------------------
/// \brief
/// Usage for applying an Environment Change to the patient
///
/// \details
/// Refer to the SEEnvironmentChange class
/// Refer to the SEEnvironmentHeating class
//--------------------------------------------------------------------------------------------------
void HowToEnvironmentChange()
{
  // Create the engine and load the patient
  std::unique_ptr<PhysiologyEngine> pe = CreatePulseEngine("HowToEnvironmentChange.log");
  pe->GetLogger()->Info("HowToEnvironmentChange");
  /*
  // You have the option to change the enviornmental conditions of the patient 
  // with a condition or an action. By default the standard environment file is used
  // when stabilizing the patient, all initial states provided are with that environment.
  // You will need to initialize the engine to this condition
  // You could then save out your own state and use it in the future

  SEInitialEnvironment ienv(pe->GetSubstanceManager());
  ienv.SetConditionsFile("./environments/AnchorageDecember.pba");
  // You can set a file or the conditions object just like is shown below
  std::vector<const SECondition*> conditions;
  conditions.push_back(&ienv);

  if (!pe->InitializeEngine("StandardMale.pba", &conditions))
  {
    pe->GetLogger()->Error("Could not load initialize engine, check the error");
    return;
  }
  */
  
  if (!pe->LoadStateFile("./states/StandardMale@0s.pba"))
  {
    pe->GetLogger()->Error("Could not load state, check the error");
    return;
  }

  // Get some substances out we will use
  SESubstance* N2 = pe->GetSubstanceManager().GetSubstance("Nitrogen");
  SESubstance* O2 = pe->GetSubstanceManager().GetSubstance("Oxygen");
  SESubstance* CO2 = pe->GetSubstanceManager().GetSubstance("CarbonDioxide");

    // The tracker is responsible for advancing the engine time and outputting the data requests below at each time step
  HowToTracker tracker(*pe);

  // Create data requests for each value that should be written to the output log as the engine is executing
  // Physiology System Names are defined on the System Objects 
  // defined in the Physiology.xsd file
  pe->GetEngineTracker()->GetDataRequestManager().CreatePhysiologyDataRequest("HeartRate", FrequencyUnit::Per_min);
  pe->GetEngineTracker()->GetDataRequestManager().CreatePhysiologyDataRequest("CardiacOutput", VolumePerTimeUnit::mL_Per_min);
  pe->GetEngineTracker()->GetDataRequestManager().CreatePhysiologyDataRequest("MeanArterialPressure", PressureUnit::mmHg);
  pe->GetEngineTracker()->GetDataRequestManager().CreatePhysiologyDataRequest("SystolicArterialPressure", PressureUnit::mmHg);
  pe->GetEngineTracker()->GetDataRequestManager().CreatePhysiologyDataRequest("DiastolicArterialPressure", PressureUnit::mmHg);
  pe->GetEngineTracker()->GetDataRequestManager().CreatePhysiologyDataRequest("SkinTemperature", TemperatureUnit::C);
  pe->GetEngineTracker()->GetDataRequestManager().CreatePhysiologyDataRequest("CoreTemperature", TemperatureUnit::C);
  pe->GetEngineTracker()->GetDataRequestManager().CreatePhysiologyDataRequest("TotalMetabolicRate", PowerUnit::W);
  pe->GetEngineTracker()->GetDataRequestManager().CreatePhysiologyDataRequest("SystemicVascularResistance", FlowResistanceUnit::mmHg_s_Per_mL);

  pe->GetEngineTracker()->GetDataRequestManager().SetResultsFilename("HowToEnvironmentChange.txt");

  // Advance some time to get some resting data
  tracker.AdvanceModelTime(50);

  pe->GetLogger()->Info("The patient is nice and healthy");
  pe->GetLogger()->Info(std::stringstream() <<"Cardiac Output : " << pe->GetCardiovascularSystem()->GetCardiacOutput(VolumePerTimeUnit::mL_Per_min) << VolumePerTimeUnit::mL_Per_min);
  pe->GetLogger()->Info(std::stringstream() <<"Mean Arterial Pressure : " << pe->GetCardiovascularSystem()->GetMeanArterialPressure(PressureUnit::mmHg) << PressureUnit::mmHg);
  pe->GetLogger()->Info(std::stringstream() <<"Systolic Pressure : " << pe->GetCardiovascularSystem()->GetSystolicArterialPressure(PressureUnit::mmHg) << PressureUnit::mmHg);
  pe->GetLogger()->Info(std::stringstream() <<"Diastolic Pressure : " << pe->GetCardiovascularSystem()->GetDiastolicArterialPressure(PressureUnit::mmHg) << PressureUnit::mmHg);
  pe->GetLogger()->Info(std::stringstream() <<"Heart Rate : " << pe->GetCardiovascularSystem()->GetHeartRate(FrequencyUnit::Per_min) << "bpm");
  pe->GetLogger()->Info(std::stringstream() <<"Skin Temperature : " << pe->GetEnergySystem()->GetSkinTemperature(TemperatureUnit::C) << TemperatureUnit::C);
  pe->GetLogger()->Info(std::stringstream() <<"Core Temperature : " << pe->GetEnergySystem()->GetCoreTemperature(TemperatureUnit::C) << TemperatureUnit::C);
  pe->GetLogger()->Info(std::stringstream() <<"Total Metabolic Rate : " << pe->GetEnergySystem()->GetTotalMetabolicRate(PowerUnit::W) << PowerUnit::W);
  pe->GetLogger()->Info(std::stringstream() <<"Systemic Vascular Resistance : " << pe->GetCardiovascularSystem()->GetSystemicVascularResistance(FlowResistanceUnit::mmHg_s_Per_mL) << FlowResistanceUnit::mmHg_s_Per_mL);;

  // EnvironmentChange Starts - instantiate a EnvironmentChange action and have the engine process it
  // The patient is instantly submerged in 10 degree Celsius water. 
  // This causes an immediate drop in the skin temperature due to increased convective heat transfer from the skin surface. 
  // The core temperature follows the skin temperature, and the metabolic rate increases due to shivering.
  SEChangeEnvironmentConditions env(pe->GetSubstanceManager());
  SEEnvironmentalConditions& conditions = env.GetConditions();
  conditions.SetSurroundingType(cdm::EnvironmentData_eSurroundingType_Water);
  conditions.GetAirVelocity().SetValue(0, LengthPerTimeUnit::m_Per_s);
  conditions.GetAmbientTemperature().SetValue(10.0, TemperatureUnit::C);
  conditions.GetAtmosphericPressure().SetValue(760., PressureUnit::mmHg);
  conditions.GetClothingResistance().SetValue(0.01, HeatResistanceAreaUnit::clo);
  conditions.GetEmissivity().SetValue(0.0);
  conditions.GetMeanRadiantTemperature().SetValue(22.0, TemperatureUnit::C);
  conditions.GetRelativeHumidity().SetValue(1.0);
  conditions.GetRespirationAmbientTemperature().SetValue(22.0, TemperatureUnit::C);
  conditions.GetAmbientGas(*N2).GetFractionAmount().SetValue(0.7901);
  conditions.GetAmbientGas(*O2).GetFractionAmount().SetValue(0.2095);
  conditions.GetAmbientGas(*CO2).GetFractionAmount().SetValue(4.0E-4);
  pe->ProcessAction(env);
  tracker.AdvanceModelTime(30);

  pe->GetLogger()->Info(std::stringstream() <<"Cardiac Output : " << pe->GetCardiovascularSystem()->GetCardiacOutput(VolumePerTimeUnit::mL_Per_min) << VolumePerTimeUnit::mL_Per_min);
  pe->GetLogger()->Info(std::stringstream() <<"Mean Arterial Pressure : " << pe->GetCardiovascularSystem()->GetMeanArterialPressure(PressureUnit::mmHg) << PressureUnit::mmHg);
  pe->GetLogger()->Info(std::stringstream() <<"Systolic Pressure : " << pe->GetCardiovascularSystem()->GetSystolicArterialPressure(PressureUnit::mmHg) << PressureUnit::mmHg);
  pe->GetLogger()->Info(std::stringstream() <<"Diastolic Pressure : " << pe->GetCardiovascularSystem()->GetDiastolicArterialPressure(PressureUnit::mmHg) << PressureUnit::mmHg);
  pe->GetLogger()->Info(std::stringstream() <<"Heart Rate : " << pe->GetCardiovascularSystem()->GetHeartRate(FrequencyUnit::Per_min) << "bpm");
  pe->GetLogger()->Info(std::stringstream() <<"Skin Temperature : " << pe->GetEnergySystem()->GetSkinTemperature(TemperatureUnit::C) << TemperatureUnit::C);
  pe->GetLogger()->Info(std::stringstream() <<"Core Temperature : " << pe->GetEnergySystem()->GetCoreTemperature(TemperatureUnit::C) << TemperatureUnit::C);
  pe->GetLogger()->Info(std::stringstream() <<"Total Metabolic Rate : " << pe->GetEnergySystem()->GetTotalMetabolicRate(PowerUnit::W) << PowerUnit::W);
  pe->GetLogger()->Info(std::stringstream() <<"Systemic Vascular Resistance : " << pe->GetCardiovascularSystem()->GetSystemicVascularResistance(FlowResistanceUnit::mmHg_s_Per_mL) << FlowResistanceUnit::mmHg_s_Per_mL);;

  // The patient is removed from the water and returns to the normal environment. 
  // The skin temperature rises, leading to a subsequent rise in core temperature
  conditions.SetSurroundingType(cdm::EnvironmentData_eSurroundingType_Water);
  conditions.GetAirVelocity().SetValue(0.1, LengthPerTimeUnit::m_Per_s);
  conditions.GetAmbientTemperature().SetValue(22.0, TemperatureUnit::C);
  conditions.GetAtmosphericPressure().SetValue(760., PressureUnit::mmHg);
  conditions.GetClothingResistance().SetValue(0.01, HeatResistanceAreaUnit::clo);
  conditions.GetEmissivity().SetValue(0.95);
  conditions.GetMeanRadiantTemperature().SetValue(22.0, TemperatureUnit::C);
  conditions.GetRelativeHumidity().SetValue(0.6);
  conditions.GetRespirationAmbientTemperature().SetValue(19, TemperatureUnit::C);
  conditions.GetAmbientGas(*N2).GetFractionAmount().SetValue(0.7896);
  conditions.GetAmbientGas(*O2).GetFractionAmount().SetValue(0.21);
  conditions.GetAmbientGas(*CO2).GetFractionAmount().SetValue(4.0E-4);
  pe->ProcessAction(env);
  tracker.AdvanceModelTime(60);

  pe->GetLogger()->Info(std::stringstream() <<"Cardiac Output : " << pe->GetCardiovascularSystem()->GetCardiacOutput(VolumePerTimeUnit::mL_Per_min) << VolumePerTimeUnit::mL_Per_min);
  pe->GetLogger()->Info(std::stringstream() <<"Mean Arterial Pressure : " << pe->GetCardiovascularSystem()->GetMeanArterialPressure(PressureUnit::mmHg) << PressureUnit::mmHg);
  pe->GetLogger()->Info(std::stringstream() <<"Systolic Pressure : " << pe->GetCardiovascularSystem()->GetSystolicArterialPressure(PressureUnit::mmHg) << PressureUnit::mmHg);
  pe->GetLogger()->Info(std::stringstream() <<"Diastolic Pressure : " << pe->GetCardiovascularSystem()->GetDiastolicArterialPressure(PressureUnit::mmHg) << PressureUnit::mmHg);
  pe->GetLogger()->Info(std::stringstream() <<"Heart Rate : " << pe->GetCardiovascularSystem()->GetHeartRate(FrequencyUnit::Per_min) << "bpm");
  pe->GetLogger()->Info(std::stringstream() <<"Skin Temperature : " << pe->GetEnergySystem()->GetSkinTemperature(TemperatureUnit::C) << TemperatureUnit::C);
  pe->GetLogger()->Info(std::stringstream() <<"Core Temperature : " << pe->GetEnergySystem()->GetCoreTemperature(TemperatureUnit::C) << TemperatureUnit::C);
  pe->GetLogger()->Info(std::stringstream() <<"Total Metabolic Rate : " << pe->GetEnergySystem()->GetTotalMetabolicRate(PowerUnit::W) << PowerUnit::W);
  pe->GetLogger()->Info(std::stringstream() <<"Systemic Vascular Resistance : " << pe->GetCardiovascularSystem()->GetSystemicVascularResistance(FlowResistanceUnit::mmHg_s_Per_mL) << FlowResistanceUnit::mmHg_s_Per_mL);
  pe->GetLogger()->Info("");

  //The patient’s skin temperature continues to rise as they are actively heated at 340 btu/hr. Both core temperature and skin
    // temperature increase as a result of this.  The patient’s metabolic rate has returned to normal since shivering has ceased.
  SEThermalApplication heat;
  heat.GetActiveHeating().GetPower().SetValue(340, PowerUnit::BTU_Per_hr);
  pe->ProcessAction(heat);
  tracker.AdvanceModelTime(120);

  pe->GetLogger()->Info(std::stringstream() <<"Cardiac Output : " << pe->GetCardiovascularSystem()->GetCardiacOutput(VolumePerTimeUnit::mL_Per_min) << VolumePerTimeUnit::mL_Per_min);
  pe->GetLogger()->Info(std::stringstream() <<"Mean Arterial Pressure : " << pe->GetCardiovascularSystem()->GetMeanArterialPressure(PressureUnit::mmHg) << PressureUnit::mmHg);
  pe->GetLogger()->Info(std::stringstream() <<"Systolic Pressure : " << pe->GetCardiovascularSystem()->GetSystolicArterialPressure(PressureUnit::mmHg) << PressureUnit::mmHg);
  pe->GetLogger()->Info(std::stringstream() <<"Diastolic Pressure : " << pe->GetCardiovascularSystem()->GetDiastolicArterialPressure(PressureUnit::mmHg) << PressureUnit::mmHg);
  pe->GetLogger()->Info(std::stringstream() <<"Heart Rate : " << pe->GetCardiovascularSystem()->GetHeartRate(FrequencyUnit::Per_min) << "bpm");
  pe->GetLogger()->Info(std::stringstream() <<"Skin Temperature : " << pe->GetEnergySystem()->GetSkinTemperature(TemperatureUnit::C) << TemperatureUnit::C);
  pe->GetLogger()->Info(std::stringstream() <<"Core Temperature : " << pe->GetEnergySystem()->GetCoreTemperature(TemperatureUnit::C) << TemperatureUnit::C);
  pe->GetLogger()->Info(std::stringstream() <<"Total Metabolic Rate : " << pe->GetEnergySystem()->GetTotalMetabolicRate(PowerUnit::W) << PowerUnit::W);
  pe->GetLogger()->Info(std::stringstream() <<"Systemic Vascular Resistance : " << pe->GetCardiovascularSystem()->GetSystemicVascularResistance(FlowResistanceUnit::mmHg_s_Per_mL) << FlowResistanceUnit::mmHg_s_Per_mL);;
  pe->GetLogger()->Info("Finished");
}
