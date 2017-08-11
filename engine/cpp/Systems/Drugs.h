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
#include "Controller/System.h"
#include "system/physiology/SEDrugSystem.h"
#include "bind/engine/EnginePhysiology.pb.h"

/**
 * @brief
 * The drug system contains the physiologically based pharmacokinetic (PBPK) model and the pharmacodynamic (PD) model.
 * @details 
 * Drug transvascular transport is modeled with a physiologically-based pharmacokinetic (PBPK) model,
 * and the physiologic effects on the body are modeled with a low-fidelity pharmacodynamic (PD) model.
 */  
class PULSE_DECL Drugs : public SEDrugSystem, public PulseSystem
{
  friend PulseController;
  friend class PulseEngineTest;
protected:
  Drugs(PulseController& data);
  PulseController& m_data;

public:
  virtual ~Drugs();

  void Clear();

  // Set members to a stable homeostatic state
  void Initialize();

  static void Load(const pulse::DrugSystemData& src, Drugs& dst);
  static pulse::DrugSystemData* Unload(const Drugs& src);
protected:
  static void Serialize(const pulse::DrugSystemData& src, Drugs& dst);
  static void Serialize(const Drugs& src, pulse::DrugSystemData& dst);

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