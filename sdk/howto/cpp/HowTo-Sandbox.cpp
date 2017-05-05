/**************************************************************************************
Copyright 2017 by Kitware, Inc.
Licensed under the Apache License, Version 2.0 (the "License"); you may not use
this file except in compliance with the License. You may obtain a copy of the License
at:
http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software distributed under
the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License.
**************************************************************************************/

#include "BioGearsEngineHowTo.h"

#include "system/physiology/SECardiovascularSystem.h"
#include "system/physiology/SERespiratorySystem.h"
#include "properties/SEScalarFrequency.h"
#include "properties/SEScalarTime.h"

//--------------------------------------------------------------------------------------------------
/// \brief
/// A place to do experiment with BioGears
///
/// \details
/// This is a good place to code up something that demonstrates an issue for reproduction and debugging
//--------------------------------------------------------------------------------------------------
void HowToSandbox()
{
	std::stringstream ss;
	// Create a BioGears Engine and load the standard patient
	std::unique_ptr<PhysiologyEngine> bg = CreateBioGearsEngine("Sandbox.log");
	if (!bg->LoadState("./states/StandardMale@0s.xml"))
	{
		bg->GetLogger()->Error("Could not load state, check the error");
		return;
	}
	bg->AdvanceModelTime(5, TimeUnit::s);
	bg->GetLogger()->Info(std::stringstream() << "Heart Rate : " << bg->GetCardiovascularSystem()->GetHeartRate(FrequencyUnit::Per_min) << "bpm");
	bg->GetLogger()->Info(std::stringstream() << "Respiration Rate : " << bg->GetRespiratorySystem()->GetRespirationRate(FrequencyUnit::Per_min) << "bpm");

	// Ok we are done with that patient, let's do another patient with the same engine
	if (!bg->LoadState("./states/StandardFemale@0s.xml"))
	{
		bg->GetLogger()->Error("Could not load state, check the error");
		return;
	}
	bg->AdvanceModelTime(5, TimeUnit::s);
	bg->GetLogger()->Info(std::stringstream() << "Heart Rate : " << bg->GetCardiovascularSystem()->GetHeartRate(FrequencyUnit::Per_min) << "bpm");
	bg->GetLogger()->Info(std::stringstream() << "Respiration Rate : " << bg->GetRespiratorySystem()->GetRespirationRate(FrequencyUnit::Per_min) << "bpm");

	bg->AdvanceModelTime(5, TimeUnit::min);
}