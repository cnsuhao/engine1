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

#include "../Controller/PulseSystem.h"
#include "system/physiology/SEDrugSystem.h"

/**
 * @brief
 * The drug system contains the physiologically based pharmacokinetic (PBPK) model and the pharmacodynamic (PD) model.
 * @details 
 * Drug transvascular transport is modeled with a physiologically-based pharmacokinetic (PBPK) model,
 * and the physiologic effects on the body are modeled with a low-fidelity pharmacodynamic (PD) model.
 */  
class PULSE_API Drugs : public SEDrugSystem, public PulseSystem
{
  friend Pulse;
  friend class PulseEngineTest;
protected:
  Drugs(Pulse& bg);
  Pulse& m_data;

public:
  virtual ~Drugs();

  void Clear();

  // Set members to a stable homeostatic state
  void Initialize();

  static void Load(const cdm::PatientData& src, SEPatient& dst);
  static cdm::PatientData* Unload(const SEPatient& src);
protected:
  static void Serialize(const cdm::PatientData& src, SEPatient& dst);
  static void Serialize(const SEPatient& src, cdm::PatientData& dst);

  // Load a state
  virtual bool Load(const CDM::PulseDrugSystemData& in);
  virtual CDM::PulseDrugSystemData* Unload() const;
protected:
  virtual void Unload(CDM::PulseDrugSystemData& data) const;

  // Set pointers and other member varialbes common to both homeostatic initialization and loading a state
  void SetUp();

public:
  void AtSteadyState();
  void PreProcess();
  void Process();
  void PostProcess(){}

protected:

  void AdministerSubstanceBolus();
  void AdministerSubstanceInfusion();
  void AdministerSubstanceCompoundInfusion();

  void CalculatePartitionCoefficients();
  void CalculateSubstanceClearance();
  void CalculatePlasmaSubstanceConcentration();
  void CalculateDrugEffects();

  // Serializable member variables (Set in Initialize and in schema)
  std::map<const SESubstance*, SESubstanceBolusState*> m_BolusAdministrations;

  // Stateless member variable (Set in SetUp())
  double m_dt_s;
  SELiquidCompartment*  m_aortaVascular;
  SELiquidCompartment*  m_venaCavaVascular;
  SELiquidCompartment*  m_muscleIntracellular;
  SELiquidCompartment*  m_liverVascular;
  SETissueCompartment*  m_liverTissue;
  SEFluidCircuitPath*   m_IVToVenaCava;
  SETissueCompartment*  m_fatTissue;
};