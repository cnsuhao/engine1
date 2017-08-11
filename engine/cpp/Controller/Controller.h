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
#include "PulseConfiguration.h"
#include "Controller/Circuits.h"
#include "Controller/Compartments.h"
#include "Controller/Substances.h"

// CDM 
#include "scenario/SEActionManager.h"
#include "scenario/SEConditionManager.h"
#include "properties/SEScalarTime.h"

#include "utils/DataTrack.h"
#include "engine/SEEngineTracker.h"

// Pulse
#include "Systems/BloodChemistry.h"
#include "Systems/Cardiovascular.h"
#include "Systems/Endocrine.h"
#include "Systems/Energy.h"
#include "Systems/Gastrointestinal.h"
#include "Systems/Hepatic.h"
#include "Systems/Nervous.h"
#include "Systems/Renal.h"
#include "Systems/Respiratory.h"
#include "Systems/Drugs.h"
#include "Systems/Tissue.h"
#include "Systems/Environment.h"

#include "Equipment/ECG.h"
#include "Equipment/AnesthesiaMachine.h"
#include "Equipment/Inhaler.h"

#include "Systems/Saturation.h"

class PulseScenarioExec;
enum class EngineState { NotReady=0, Initialization, InitialStabilization, AtInitialStableState, SecondaryStabilization, AtSecondaryStableState, Active };

/**
* @brief Manages and controls execution of all data/systems in %Pulse
*/
class PULSE_DECL PulseController : public Loggable, protected LoggerForward
{
  friend class PulseEngineTest;
  friend class PulseScenarioExec;
protected:
  EngineState m_State;
public:
  

  PulseController(Logger* logger);
  PulseController(const std::string& logfileName);
  virtual ~PulseController();

 
  EngineState                             GetState() { return m_State; }

  DataTrack&                              GetDataTrack();
  SaturationCalculator&                   GetSaturationCalculator() { return *m_SaturationCalculator; }

  PulseSubstances&                        GetSubstances() { return *m_Substances; }

  SEPatient&                              GetPatient() { return *m_Patient; }
  bool                                    GetPatientAssessment(SEPatientAssessment& assessment);

  SEBloodChemistrySystem&                 GetBloodChemistry() { return *m_BloodChemistrySystem; }
  SECardiovascularSystem&                 GetCardiovascular() { return *m_CardiovascularSystem; }
  SEDrugSystem&                           GetDrugs() { return *m_DrugSystem; }
  SEEndocrineSystem&                      GetEndocrine() { return *m_EndocrineSystem; }
  SEEnergySystem&                         GetEnergy() { return *m_EnergySystem; }
  SEGastrointestinalSystem&               GetGastrointestinal() { return *m_GastrointestinalSystem; }
  SEHepaticSystem&                        GetHepatic() { return *m_HepaticSystem; }
  SENervousSystem&                        GetNervous() { return *m_NervousSystem; }
  SERenalSystem&                          GetRenal() { return *m_RenalSystem; }
  SERespiratorySystem&                    GetRespiratory() { return *m_RespiratorySystem; }
  SETissueSystem&                         GetTissue() { return *m_TissueSystem; }

  SEEnvironment&                          GetEnvironment() { return *m_Environment; }

  SEAnesthesiaMachine&                    GetAnesthesiaMachine() { return *m_AnesthesiaMachine; }

  SEElectroCardioGram&                    GetECG() { return *m_ECG; }

  SEInhaler&                              GetInhaler() { return *m_Inhaler; }

  SEActionManager&                        GetActions() { return *m_Actions; }

  SEConditionManager&                     GetConditions() { return *m_Conditions; }

  PulseCircuits&                          GetCircuits() { return *m_Circuits; }


  PulseCompartments&                      GetCompartments() { return *m_Compartments; }

  const PulseConfiguration&               GetConfiguration() { return *m_Config; }

  const SEScalarTime&                     GetEngineTime() { return *m_CurrentTime; }
  const SEScalarTime&                     GetSimulationTime() { return *m_SimulationTime; }
  const SEScalarTime&                     GetTimeStep() { return m_Config->GetTimeStep(); }

  pulse::eAirwayMode                      GetAirwayMode() { return m_AirwayMode; }
  void                                    SetAirwayMode(pulse::eAirwayMode mode);

  cdm::eSwitch                            GetIntubation() { return m_Intubation; }
  void                                    SetIntubation(cdm::eSwitch s);

  bool CreateCircuitsAndCompartments();
protected:
  void SetupCardiovascular();
  void SetupRenal();
  void SetupTissue();
  void SetupGastrointestinal();
  void SetupRespiratory();
  void SetupAnesthesiaMachine();
  void SetupInhaler();
  void SetupMechanicalVentilator();
  void SetupExternalTemperature();
  void SetupInternalTemperature();

  bool Initialize(const PulseConfiguration* config);
  bool SetupPatient();

  // Notify systems that steady state has been achieved
  virtual void AtSteadyState(EngineState state);
  void PreProcess();
  void Process();
  void PostProcess();

  void ForwardFatal(const std::string&  msg, const std::string&  origin);

  DataTrack*                                                    m_DataTrack;

  std::unique_ptr<SEScalarTime>                                 m_CurrentTime;
  std::unique_ptr<SEScalarTime>                                 m_SimulationTime;
  pulse::eAirwayMode                                            m_AirwayMode;
  cdm::eSwitch                                                  m_Intubation;

  std::unique_ptr<PulseConfiguration>                           m_Config;
  std::unique_ptr<SaturationCalculator>                         m_SaturationCalculator;

  std::unique_ptr<PulseSubstances>                              m_Substances;

  std::unique_ptr<SEActionManager>                              m_Actions;
  std::unique_ptr<SEConditionManager>                           m_Conditions;
  std::unique_ptr<PulseCircuits>                                m_Circuits;
  std::unique_ptr<PulseCompartments>                            m_Compartments;

  std::unique_ptr<Environment>                                  m_Environment;

  std::unique_ptr<BloodChemistry>                               m_BloodChemistrySystem;
  std::unique_ptr<Cardiovascular>                               m_CardiovascularSystem;
  std::unique_ptr<Endocrine>                                    m_EndocrineSystem;
  std::unique_ptr<Energy>                                       m_EnergySystem;
  std::unique_ptr<Gastrointestinal>                             m_GastrointestinalSystem;
  std::unique_ptr<Hepatic>                                      m_HepaticSystem;
  std::unique_ptr<Nervous>                                      m_NervousSystem;
  std::unique_ptr<Renal>                                        m_RenalSystem;
  std::unique_ptr<Respiratory>                                  m_RespiratorySystem;
  std::unique_ptr<Drugs>                                        m_DrugSystem;
  std::unique_ptr<Tissue>                                       m_TissueSystem;

  std::unique_ptr<ECG>                                          m_ECG;

  std::unique_ptr<AnesthesiaMachine>                            m_AnesthesiaMachine;

  std::unique_ptr<Inhaler>                                      m_Inhaler;

  std::unique_ptr<SEPatient>                                    m_Patient;

  // Flag to destroy the logger or not                          
  bool                                                          myLogger;
};

