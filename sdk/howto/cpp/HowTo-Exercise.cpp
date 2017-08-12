/**************************************************************************************
Copyright 2015 Applied Research Associates, Inc.
Licensed under the Apache License, Version 2.0 (the "License"); you may not use
this file except in compliance with the License. You may obtain a copy of the License
at:
http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software distributed under
the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License.
**************************************************************************************/

#include "EngineHowTo.h"

// Include the various types you will be using in your code
#include "patient/actions/SEExercise.h"
#include "system/physiology/SEBloodChemistrySystem.h"
#include "system/physiology/SECardiovascularSystem.h"
#include "system/physiology/SEEnergySystem.h"
#include "system/physiology/SERespiratorySystem.h"
#include "substance/SESubstanceManager.h"
#include "substance/SESubstanceCompound.h"
#include "properties/SEScalar0To1.h"
#include "properties/SEScalarFrequency.h"
#include "properties/SEScalarMass.h"
#include "properties/SEScalarMassPerVolume.h"
#include "properties/SEScalarPressure.h"
#include "properties/SEScalarTemperature.h"
#include "properties/SEScalarTime.h"
#include "properties/SEScalarVolume.h"
#include "properties/SEScalarVolumePerTime.h"
#include "properties/SEScalarPower.h"
#include "properties/SEScalar0To1.h"
#include "engine/SEEngineTracker.h"
#include "compartment/SECompartmentManager.h"

//--------------------------------------------------------------------------------------------------
/// \brief
/// Usage for applying an Exercise insult to the patient
///
/// \details
/// Refer to the SEExercise class
//--------------------------------------------------------------------------------------------------
void HowToExercise() 
{
  // Create the engine and load the patient
  std::unique_ptr<PhysiologyEngine> pe = CreatePulseEngine("HowToExercise.log");
  pe->GetLogger()->Info("HowToExercise");
  if (!pe->LoadState("./states/StandardMale@0s.pba"))
  {
    pe->GetLogger()->Error("Could not load state, check the error");
    return;
  }

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
  pe->GetEngineTracker()->GetDataRequestManager().CreatePhysiologyDataRequest("TotalMetabolicRate", PowerUnit::kcal_Per_day);
  pe->GetEngineTracker()->GetDataRequestManager().CreatePhysiologyDataRequest("CoreTemperature", TemperatureUnit::C);
  pe->GetEngineTracker()->GetDataRequestManager().CreatePhysiologyDataRequest("RespirationRate", FrequencyUnit::Per_min);
  pe->GetEngineTracker()->GetDataRequestManager().CreatePhysiologyDataRequest("AchievedExerciseLevel");
  pe->GetEngineTracker()->GetDataRequestManager().CreatePhysiologyDataRequest("FatigueLevel");
  pe->GetEngineTracker()->GetDataRequestManager().CreatePhysiologyDataRequest("TotalMetabolicRate", PowerUnit::W);
  pe->GetEngineTracker()->GetDataRequestManager().CreatePhysiologyDataRequest("TotalWorkRateLevel");
  
  pe->GetEngineTracker()->GetDataRequestManager().SetResultsFilename("HowToExercise.txt");

  // Advance some time to get some resting data
  tracker.AdvanceModelTime(20);
  
  pe->GetLogger()->Info("The patient is nice and healthy");
  pe->GetLogger()->Info(std::stringstream() <<"Cardiac Output : " << pe->GetCardiovascularSystem()->GetCardiacOutput(VolumePerTimeUnit::mL_Per_min) << VolumePerTimeUnit::mL_Per_min);
  pe->GetLogger()->Info(std::stringstream() <<"Mean Arterial Pressure : " << pe->GetCardiovascularSystem()->GetMeanArterialPressure(PressureUnit::mmHg) << PressureUnit::mmHg);
  pe->GetLogger()->Info(std::stringstream() <<"Systolic Pressure : " << pe->GetCardiovascularSystem()->GetSystolicArterialPressure(PressureUnit::mmHg) << PressureUnit::mmHg);
  pe->GetLogger()->Info(std::stringstream() <<"Diastolic Pressure : " << pe->GetCardiovascularSystem()->GetDiastolicArterialPressure(PressureUnit::mmHg) << PressureUnit::mmHg);
  pe->GetLogger()->Info(std::stringstream() <<"Heart Rate : " << pe->GetCardiovascularSystem()->GetHeartRate(FrequencyUnit::Per_min) << "bpm");
  pe->GetLogger()->Info(std::stringstream() <<"Total Metabolic Rate : " << pe->GetEnergySystem()->GetTotalMetabolicRate(PowerUnit::kcal_Per_day) << PowerUnit::kcal_Per_day);
  pe->GetLogger()->Info(std::stringstream() <<"Core Temperature : " << pe->GetEnergySystem()->GetCoreTemperature(TemperatureUnit::C) << TemperatureUnit::C);
  pe->GetLogger()->Info(std::stringstream() <<"RespirationRate : " << pe->GetRespiratorySystem()->GetRespirationRate(FrequencyUnit::Per_min) << "bpm");
  //pe->GetLogger()->Info(std::stringstream() <<"AchievedExerciseLevel : " << pe->GetEnergySystem()->GetAchievedExerciseLevel()); // This will be NaN as the patient is not doing any exercise
  //pe->GetLogger()->Info(std::stringstream() <<"FatigueLevel : " << pe->GetEnergySystem()->GetFatigueLevel()); // No fatigue either
  pe->GetLogger()->Info(std::stringstream() <<"TotalMetabolicRate : " << pe->GetEnergySystem()->GetTotalMetabolicRate(PowerUnit::W) << PowerUnit::W);//This will be at Basal Level
  pe->GetLogger()->Info(std::stringstream() <<"TotalWorkRateLevel : " << pe->GetEnergySystem()->GetTotalWorkRateLevel());; // Nothing here either as the patient is resting

  // Exercise Starts - instantiate an Exercise action and have the engine process it.
  // After initiating exercise the patient’s metabolic rate begins to increased. 
  // An intensity of 1.0 asks the patient to exercise at the maximum work rate capable by the patient (an output of ~1200W for a patient in relativly good shape).
  // The patient will not be able to sustain this pace for long... and will get fatigued
  // This leads to an increase in core temperature, cardiac output, respiration rate and tidal volume.
  // The increase in core temperature leads to an elevated sweat rate, which causes the patient’s skin temperature to drop due to evaporation. 
  SEExercise ex;
  ex.GetIntensity().SetValue(0.5);
  pe->ProcessAction(ex);
  tracker.AdvanceModelTime(30);

  pe->GetLogger()->Info(std::stringstream() <<"Cardiac Output : " << pe->GetCardiovascularSystem()->GetCardiacOutput(VolumePerTimeUnit::mL_Per_min) << VolumePerTimeUnit::mL_Per_min);
  pe->GetLogger()->Info(std::stringstream() <<"Mean Arterial Pressure : " << pe->GetCardiovascularSystem()->GetMeanArterialPressure(PressureUnit::mmHg) << PressureUnit::mmHg);
  pe->GetLogger()->Info(std::stringstream() <<"Systolic Pressure : " << pe->GetCardiovascularSystem()->GetSystolicArterialPressure(PressureUnit::mmHg) << PressureUnit::mmHg);
  pe->GetLogger()->Info(std::stringstream() <<"Diastolic Pressure : " << pe->GetCardiovascularSystem()->GetDiastolicArterialPressure(PressureUnit::mmHg) << PressureUnit::mmHg);
  pe->GetLogger()->Info(std::stringstream() <<"Heart Rate : " << pe->GetCardiovascularSystem()->GetHeartRate(FrequencyUnit::Per_min) << "bpm");
  pe->GetLogger()->Info(std::stringstream() <<"Total Metabolic Rate : " << pe->GetEnergySystem()->GetTotalMetabolicRate(PowerUnit::kcal_Per_day) << PowerUnit::kcal_Per_day);
  pe->GetLogger()->Info(std::stringstream() <<"Core Temperature : " << pe->GetEnergySystem()->GetCoreTemperature(TemperatureUnit::C) << TemperatureUnit::C);
  pe->GetLogger()->Info(std::stringstream() <<"RespirationRate : " << pe->GetRespiratorySystem()->GetRespirationRate(FrequencyUnit::Per_min) << "bpm");
  pe->GetLogger()->Info(std::stringstream() <<"AchievedExerciseLevel : " << pe->GetEnergySystem()->GetAchievedExerciseLevel()); // this is the fraction of what we asked for, 1.0 means we are doing what you asked for.
  pe->GetLogger()->Info(std::stringstream() <<"FatigueLevel : " << pe->GetEnergySystem()->GetFatigueLevel()); // Patient is very tired
  pe->GetLogger()->Info(std::stringstream() <<"TotalMetabolicRate : " << pe->GetEnergySystem()->GetTotalMetabolicRate(PowerUnit::W) << PowerUnit::W);// We are burning 
  pe->GetLogger()->Info(std::stringstream() <<"TotalWorkRateLevel : " << pe->GetEnergySystem()->GetTotalWorkRateLevel());; // How much work we are getting / the max work rate possible

  // Once exercise has ended, the patient is in a recovery period where the metabolic rate begins to return to its basal value. 
  // The cardiac output, respiration rate and tidal volume follow this recovery trend towards their normal values.
  ex.GetIntensity().SetValue(0);
  pe->ProcessAction(ex);
  
  // Advance some time while the medic gets the drugs ready
  tracker.AdvanceModelTime(30);

  pe->GetLogger()->Info(std::stringstream() <<"Cardiac Output : " << pe->GetCardiovascularSystem()->GetCardiacOutput(VolumePerTimeUnit::mL_Per_min) << VolumePerTimeUnit::mL_Per_min);
  pe->GetLogger()->Info(std::stringstream() <<"Mean Arterial Pressure : " << pe->GetCardiovascularSystem()->GetMeanArterialPressure(PressureUnit::mmHg) << PressureUnit::mmHg);
  pe->GetLogger()->Info(std::stringstream() <<"Systolic Pressure : " << pe->GetCardiovascularSystem()->GetSystolicArterialPressure(PressureUnit::mmHg) << PressureUnit::mmHg);
  pe->GetLogger()->Info(std::stringstream() <<"Diastolic Pressure : " << pe->GetCardiovascularSystem()->GetDiastolicArterialPressure(PressureUnit::mmHg) << PressureUnit::mmHg);
  pe->GetLogger()->Info(std::stringstream() <<"Heart Rate : " << pe->GetCardiovascularSystem()->GetHeartRate(FrequencyUnit::Per_min) << "bpm");
  pe->GetLogger()->Info(std::stringstream() <<"Total Metabolic Rate : " << pe->GetEnergySystem()->GetTotalMetabolicRate(PowerUnit::kcal_Per_day) << PowerUnit::kcal_Per_day);
  pe->GetLogger()->Info(std::stringstream() <<"Core Temperature : " << pe->GetEnergySystem()->GetCoreTemperature(TemperatureUnit::C) << TemperatureUnit::C);
  pe->GetLogger()->Info(std::stringstream() <<"RespirationRate : " << pe->GetRespiratorySystem()->GetRespirationRate(FrequencyUnit::Per_min) << "bpm");
  //pe->GetLogger()->Info(std::stringstream() <<"AchievedExerciseLevel : " << pe->GetEnergySystem()->GetAchievedExerciseLevel()); // This will be NaN as the patient is not doing any exercise
  //pe->GetLogger()->Info(std::stringstream() <<"FatigueLevel : " << pe->GetEnergySystem()->GetFatigueLevel()); // We are not working out but we are still fatigued
  pe->GetLogger()->Info(std::stringstream() <<"TotalMetabolicRate : " << pe->GetEnergySystem()->GetTotalMetabolicRate(PowerUnit::W) << PowerUnit::W);// We are still burning 
  pe->GetLogger()->Info(std::stringstream() <<"TotalWorkRateLevel : " << pe->GetEnergySystem()->GetTotalWorkRateLevel());; // How much work we are getting over the max work rate possible
  pe->GetLogger()->Info("Finished");
}
