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
#include "patient/actions/SEHemorrhage.h"
#include "patient/actions/SESubstanceCompoundInfusion.h"
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
#include "engine/SEEngineTracker.h"
#include "compartment/SECompartmentManager.h"

//--------------------------------------------------------------------------------------------------
/// \brief
/// Usage for applying a Hemorrhage insult to the patient
///
/// \details
/// Refer to the SEHemorrhage class
/// Refer to the SESubstanceManager class
/// Refer to the SESubstanceIVFluids class for applying an IV to the patient
//--------------------------------------------------------------------------------------------------
void HowToHemorrhage() 
{
  // Create the engine and load the patient
  std::unique_ptr<PhysiologyEngine> pe = CreatePulseEngine("HowToHemorrhage.log");
  pe->GetLogger()->Info("HowToHemorrhage");
  if (!pe->LoadStateFile("./states/StandardMale@0s.pba"))
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
  pe->GetEngineTracker()->GetDataRequestManager().CreatePhysiologyDataRequest("BloodVolume", VolumeUnit::mL);
  pe->GetEngineTracker()->GetDataRequestManager().CreatePhysiologyDataRequest("CardiacOutput", VolumePerTimeUnit::mL_Per_min);
  pe->GetEngineTracker()->GetDataRequestManager().CreatePhysiologyDataRequest("MeanArterialPressure", PressureUnit::mmHg);
  pe->GetEngineTracker()->GetDataRequestManager().CreatePhysiologyDataRequest("SystolicArterialPressure", PressureUnit::mmHg);
  pe->GetEngineTracker()->GetDataRequestManager().CreatePhysiologyDataRequest("DiastolicArterialPressure", PressureUnit::mmHg);
  pe->GetEngineTracker()->GetDataRequestManager().CreatePhysiologyDataRequest("HemoglobinContent",MassUnit::g);
  
  pe->GetEngineTracker()->GetDataRequestManager().SetResultsFilename("HowToHemorrhage.txt");
  
  pe->GetLogger()->Info("The patient is nice and healthy");
  pe->GetLogger()->Info(std::stringstream() <<"Cardiac Output : " << pe->GetCardiovascularSystem()->GetCardiacOutput(VolumePerTimeUnit::mL_Per_min) << VolumePerTimeUnit::mL_Per_min);
  pe->GetLogger()->Info(std::stringstream() <<"Hemoglobin Content : " << pe->GetBloodChemistrySystem()->GetHemoglobinContent(MassUnit::g) << MassUnit::g);
  pe->GetLogger()->Info(std::stringstream() <<"Blood Volume : " << pe->GetCardiovascularSystem()->GetBloodVolume(VolumeUnit::mL) << VolumeUnit::mL);
  pe->GetLogger()->Info(std::stringstream() <<"Mean Arterial Pressure : " << pe->GetCardiovascularSystem()->GetMeanArterialPressure(PressureUnit::mmHg) << PressureUnit::mmHg);
  pe->GetLogger()->Info(std::stringstream() <<"Systolic Pressure : " << pe->GetCardiovascularSystem()->GetSystolicArterialPressure(PressureUnit::mmHg) << PressureUnit::mmHg);
  pe->GetLogger()->Info(std::stringstream() <<"Diastolic Pressure : " << pe->GetCardiovascularSystem()->GetDiastolicArterialPressure(PressureUnit::mmHg) << PressureUnit::mmHg);
  pe->GetLogger()->Info(std::stringstream() <<"Heart Rate : " << pe->GetCardiovascularSystem()->GetHeartRate(FrequencyUnit::Per_min) << "bpm");;

  // Hemorrhage Starts - instantiate a hemorrhage action and have the engine process it
  SEHemorrhage hemorrhageLeg;
  hemorrhageLeg.SetCompartment(pulse::VascularCompartment::RightLeg);//the location of the hemorrhage
  hemorrhageLeg.GetRate().SetValue(250,VolumePerTimeUnit::mL_Per_min);//the rate of hemorrhage
  pe->ProcessAction(hemorrhageLeg);

  // Advance some time to let the body bleed out a bit
  tracker.AdvanceModelTime(300);

  pe->GetLogger()->Info("The patient has been hemorrhaging for 300s");
  pe->GetLogger()->Info(std::stringstream() <<"Cardiac Output : " << pe->GetCardiovascularSystem()->GetCardiacOutput(VolumePerTimeUnit::mL_Per_min) << VolumePerTimeUnit::mL_Per_min);
  pe->GetLogger()->Info(std::stringstream() <<"Hemoglobin Content : " << pe->GetBloodChemistrySystem()->GetHemoglobinContent(MassUnit::g) << MassUnit::g);
  pe->GetLogger()->Info(std::stringstream() <<"Blood Volume : " << pe->GetCardiovascularSystem()->GetBloodVolume(VolumeUnit::mL) << VolumeUnit::mL);
  pe->GetLogger()->Info(std::stringstream() <<"Mean Arterial Pressure : " << pe->GetCardiovascularSystem()->GetMeanArterialPressure(PressureUnit::mmHg) << PressureUnit::mmHg);
  pe->GetLogger()->Info(std::stringstream() <<"Systolic Pressure : " << pe->GetCardiovascularSystem()->GetSystolicArterialPressure(PressureUnit::mmHg) << PressureUnit::mmHg);
  pe->GetLogger()->Info(std::stringstream() <<"Diastolic Pressure : " << pe->GetCardiovascularSystem()->GetDiastolicArterialPressure(PressureUnit::mmHg) << PressureUnit::mmHg);
  pe->GetLogger()->Info(std::stringstream() <<"Heart Rate : " << pe->GetCardiovascularSystem()->GetHeartRate(FrequencyUnit::Per_min) << "bpm");;

  // Hemorrhage is sealed
  hemorrhageLeg.SetCompartment(pulse::VascularCompartment::RightLeg);//location of hemorrhage
  hemorrhageLeg.GetRate().SetValue(0,VolumePerTimeUnit::mL_Per_min);//rate is set to 0 to close the bleed
  pe->ProcessAction(hemorrhageLeg);
  
  
  // Advance some time while the medic gets the drugs ready
  tracker.AdvanceModelTime(100);

  pe->GetLogger()->Info("The patient has NOT been hemorrhaging for 100s");
  pe->GetLogger()->Info(std::stringstream() <<"Cardiac Output : " << pe->GetCardiovascularSystem()->GetCardiacOutput(VolumePerTimeUnit::mL_Per_min) << VolumePerTimeUnit::mL_Per_min);
  pe->GetLogger()->Info(std::stringstream() <<"Hemoglobin Content : " << pe->GetBloodChemistrySystem()->GetHemoglobinContent(MassUnit::g) << MassUnit::g);
  pe->GetLogger()->Info(std::stringstream() <<"Blood Volume : " << pe->GetCardiovascularSystem()->GetBloodVolume(VolumeUnit::mL) << VolumeUnit::mL);
  pe->GetLogger()->Info(std::stringstream() <<"Mean Arterial Pressure : " << pe->GetCardiovascularSystem()->GetMeanArterialPressure(PressureUnit::mmHg) << PressureUnit::mmHg);
  pe->GetLogger()->Info(std::stringstream() <<"Systolic Pressure : " << pe->GetCardiovascularSystem()->GetSystolicArterialPressure(PressureUnit::mmHg) << PressureUnit::mmHg);
  pe->GetLogger()->Info(std::stringstream() <<"Diastolic Pressure : " << pe->GetCardiovascularSystem()->GetDiastolicArterialPressure(PressureUnit::mmHg) << PressureUnit::mmHg);
  pe->GetLogger()->Info(std::stringstream() <<"Heart Rate : " << pe->GetCardiovascularSystem()->GetHeartRate(FrequencyUnit::Per_min) << "bpm");;

  // Patient is stabilizing, but not great

  // Let's administer a saline drip, we need to get saline from the substance maganer
  SESubstanceCompound* saline = pe->GetSubstanceManager().GetCompound("Saline");
  SESubstanceCompoundInfusion iVSaline(*saline);
  iVSaline.GetBagVolume().SetValue(500,VolumeUnit::mL);//the total volume in the bag of Saline
  iVSaline.GetRate().SetValue(100,VolumePerTimeUnit::mL_Per_min);//The rate to admnister the compound in the bag in this case saline
  pe->ProcessAction(iVSaline);

  tracker.AdvanceModelTime(400);

  pe->GetLogger()->Info("The patient has been getting fluids for the past 400s");
  pe->GetLogger()->Info(std::stringstream() <<"Cardiac Output : " << pe->GetCardiovascularSystem()->GetCardiacOutput(VolumePerTimeUnit::mL_Per_min) << VolumePerTimeUnit::mL_Per_min);
  pe->GetLogger()->Info(std::stringstream() <<"Hemoglobin Content : " << pe->GetBloodChemistrySystem()->GetHemoglobinContent(MassUnit::g) << MassUnit::g);
  pe->GetLogger()->Info(std::stringstream() <<"Blood Volume : " << pe->GetCardiovascularSystem()->GetBloodVolume(VolumeUnit::mL) << VolumeUnit::mL);
  pe->GetLogger()->Info(std::stringstream() <<"Mean Arterial Pressure : " << pe->GetCardiovascularSystem()->GetMeanArterialPressure(PressureUnit::mmHg) << PressureUnit::mmHg);
  pe->GetLogger()->Info(std::stringstream() <<"Systolic Pressure : " << pe->GetCardiovascularSystem()->GetSystolicArterialPressure(PressureUnit::mmHg) << PressureUnit::mmHg);
  pe->GetLogger()->Info(std::stringstream() <<"Diastolic Pressure : " << pe->GetCardiovascularSystem()->GetDiastolicArterialPressure(PressureUnit::mmHg) << PressureUnit::mmHg);
  pe->GetLogger()->Info(std::stringstream() <<"Heart Rate : " << pe->GetCardiovascularSystem()->GetHeartRate(FrequencyUnit::Per_min) << "bpm");;
  pe->GetLogger()->Info("Finished");
}
