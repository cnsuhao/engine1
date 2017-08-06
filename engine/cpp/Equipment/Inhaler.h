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

#include "system/equipment/Inhaler/SEInhaler.h"

/**
* @brief 
* Generic inhaler for substance administration.
*/
class PULSE_API Inhaler : public SEInhaler, public PulseSystem
{
  friend Pulse;
  friend class PulseEngineTest;
protected:
  Inhaler(Pulse& bg);
  Pulse& m_data;

public:
  virtual ~Inhaler();

  void Clear();

  // Set members to a stable homeostatic state
  void Initialize();

  static void Load(const cdm::PatientData& src, SEPatient& dst);
  static cdm::PatientData* Unload(const SEPatient& src);
protected:
  static void Serialize(const cdm::PatientData& src, SEPatient& dst);
  static void Serialize(const SEPatient& src, cdm::PatientData& dst);

  // Load a state
  bool Load(const CDM::PulseInhalerData& in);
  CDM::PulseInhalerData* Unload() const;
protected:
  void Unload(CDM::PulseInhalerData& data) const;

  // Set pointers and other member varialbes common to both homeostatic initialization and loading a state
  void SetUp();
 
public:

  // main driver function responsible for calling the various ECG functions:
  void PreProcess();
  void Process();
  void PostProcess();

protected:
  void StateChange();
  void Administer();

  // Serializable member variables (Set in Initialize and in schema)

  // Stateless member variable (Set in SetUp())
  double                     m_dt_s;
  SEGasCompartment          *m_Mouthpiece;
  SELiquidCompartment       *m_AerosolMouthpiece;
  SEGasCompartment          *m_AmbientEnv;
  SELiquidSubstanceQuantity *m_InhalerDrug;
};
