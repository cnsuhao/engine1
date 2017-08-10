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
#include "bind/engine/EngineEquipment.pb.h"
#include "../Controller/PulseSystem.h"
#include "system/equipment/Anesthesia/SEAnesthesiaMachine.h"
class SEAnesthesiaMachineActionCollection;

/**
 * @brief 
 * Generic anesthesia machine for positive pressure ventilation.
 */    
class PULSE_DECL AnesthesiaMachine : public SEAnesthesiaMachine, public PulseSystem
{
  friend Pulse;
  friend class PulseEngineTest;
protected:
  AnesthesiaMachine(Pulse& bg);
  Pulse& m_data;

public:
  virtual ~AnesthesiaMachine();

  void Clear();

  // Set members to a stable homeostatic state
  void Initialize();

  static void Load(const pulse::AnesthesiaMachineData& src, AnesthesiaMachine& dst);
  static pulse::AnesthesiaMachineData* Unload(const AnesthesiaMachine& src);
protected:
  static void Serialize(const pulse::AnesthesiaMachineData& src, AnesthesiaMachine& dst);
  static void Serialize(const AnesthesiaMachine& src, pulse::AnesthesiaMachineData& dst);

  // Set pointers and other member varialbes common to both homeostatic initialization and loading a state
  void SetUp();

public:
  void StateChange();

  void PreProcess();
  void Process();
  void PostProcess();

  void CalculateScrubber();

  // Extending some functionality to these base class methods
  // We will update the Pulse Airway mode when these are called
  virtual void SetConnection(cdm::AnesthesiaMachineData_eConnection c);
  virtual void InvalidateConnection();

private:
  void CalculateSourceStatus();
  void CalculateEquipmentLeak();
  void SetConnection();
  void CalculateValveResistances();
  void CalculateVentilator();
  void CalculateGasSource();
  void CalculateCyclePhase();
  void CheckReliefValve();

  // Serializable member variables (Set in Initialize and in schema)
  bool         m_inhaling; 
  SEScalarTime m_inspirationTime;
  SEScalar     m_O2InletVolumeFraction;
  SEScalarTime m_currentbreathingCycleTime;
  SEScalarTime m_totalBreathingCycleTime;

  // Stateless member variable (Set in SetUp())
  double m_dt_s;
  double m_dValveOpenResistance_cmH2O_s_Per_L;
  double m_dValveClosedResistance_cmH2O_s_Per_L;
  double m_dSwitchOpenResistance_cmH2O_s_Per_L;
  double m_dSwitchClosedResistance_cmH2O_s_Per_L;
  SEAnesthesiaMachineActionCollection* m_actions;
  SEGasCompartment*                    m_ambient;
  SEGasSubstanceQuantity*              m_ambientCO2;
  SEGasSubstanceQuantity*              m_ambientN2;
  SEGasSubstanceQuantity*              m_ambientO2;
  SEGasCompartment*                    m_gasSource;
  SEGasSubstanceQuantity*              m_gasSourceCO2;
  SEGasSubstanceQuantity*              m_gasSourceN2;
  SEGasSubstanceQuantity*              m_gasSourceO2;
  SEGasCompartment*                    m_scrubber;
  SEGasSubstanceQuantity*              m_scubberCO2;
  SEGasSubstanceQuantity*              m_scrubberN2;
  SEFluidCircuitNode*                  m_nVentilator;
  SEFluidCircuitPath*                  m_pAnesthesiaConnectionToEnvironment;
  SEFluidCircuitPath*                  m_pYPieceToExpiratoryLimb;
  SEFluidCircuitPath*                  m_pGasSourceToGasInlet;
  SEFluidCircuitPath*                  m_pInspiratoryLimbToYPiece;
  SEFluidCircuitPath*                  m_pSelectorToReliefValve;
  SEFluidCircuitPath*                  m_pEnvironmentToReliefValve;
  SEFluidCircuitPath*                  m_pSelectorToEnvironment;
  SEFluidCircuitPath*                  m_pEnvironmentToVentilator;
  SEFluidCircuitPath*                  m_pExpiratoryLimbToSelector;
  SEFluidCircuitPath*                  m_pSelectorToScrubber;
};





