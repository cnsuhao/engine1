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
#pragma once

#pragma warning(push)
// Disabling the waring about STL classes used have 
// to have a dll interface to be used by clients
// From what I have read STL is compiler dependent
// But since we are releasing source, you can build
// the project necessary to ensure proper linkage
// If anyone else has opinions on this, let us know
// physiology@kitware.com
#pragma warning(disable : 4251)
#include "Controller.h"
#pragma warning(pop)


//--------------------------------------------------------------------------------------------------
/// @brief  
/// This is the implementation of the PhysiologyEngine interface for the this engines.
/// @details
/// It contains the necessary execution calls, patient customization calls, insult and intervention 
/// calls as well as assessment calls for obtaining the results. During engine execution a log files
/// is generated containing information, warning and error data.
//--------------------------------------------------------------------------------------------------
class PULSE_DECL PulseEngine : public PhysiologyEngine, public PulseController
{
public:

  PulseEngine(Logger* logger);
  PulseEngine(const std::string&);
  virtual ~PulseEngine();

  virtual bool LoadStateFile(const std::string& file, const SEScalarTime* simTime = nullptr, const SEEngineConfiguration* config = nullptr);
  virtual bool LoadState(const google::protobuf::Message& state, const SEScalarTime* simTime = nullptr, const SEEngineConfiguration* config = nullptr);
  virtual std::unique_ptr<google::protobuf::Message> SaveState(const std::string& file = "");

  virtual Logger* GetLogger();
  virtual SEEngineTracker* GetEngineTracker();

  virtual bool InitializeEngine(const std::string& patientFile, const std::vector<const SECondition*>* conditions = nullptr, const SEEngineConfiguration* config = nullptr);
  virtual bool InitializeEngine(const SEPatient& patient, const std::vector<const SECondition*>* conditions = nullptr, const SEEngineConfiguration* config = nullptr);

  virtual const SEEngineConfiguration* GetConfiguration();

  virtual double GetTimeStep(const TimeUnit& unit);
  virtual double GetSimulationTime(const TimeUnit& unit);

  virtual void AdvanceModelTime();
  virtual void AdvanceModelTime(double time, const TimeUnit& unit);
  virtual bool ProcessAction(const SEAction& action); 

  virtual SESubstanceManager& GetSubstanceManager();
  virtual void SetEventHandler(SEEventHandler* handler);
  virtual const SEPatient& GetPatient();
  virtual bool GetPatientAssessment(SEPatientAssessment& assessment); 

  virtual const SEEnvironment*                         GetEnvironment();
  virtual const SEBloodChemistrySystem*                GetBloodChemistrySystem();
  virtual const SECardiovascularSystem*                GetCardiovascularSystem();
  virtual const SEDrugSystem*                          GetDrugSystem();
  virtual const SEEndocrineSystem*                     GetEndocrineSystem();
  virtual const SEEnergySystem*                        GetEnergySystem();
  virtual const SEGastrointestinalSystem*              GetGastrointestinalSystem();
  virtual const SEHepaticSystem*                       GetHepaticSystem();
  virtual const SENervousSystem*                       GetNervousSystem();
  virtual const SERenalSystem*                         GetRenalSystem();
  virtual const SERespiratorySystem*                   GetRespiratorySystem();
  virtual const SETissueSystem*                        GetTissueSystem();
  virtual const SEAnesthesiaMachine*                   GetAnesthesiaMachine();
  virtual const SEElectroCardioGram*                   GetElectroCardioGram();
  virtual const SEInhaler*                             GetInhaler();

  virtual const SECompartmentManager&                  GetCompartments();

protected:

  virtual bool IsReady();
  virtual bool InitializeEngine(const std::vector<const SECondition*>* conditions = nullptr, const SEEngineConfiguration* config = nullptr);

  SEEventHandler*                                 m_EventHandler;
  SEEngineTracker                                 m_EngineTrack;
  std::stringstream                               m_ss;
};