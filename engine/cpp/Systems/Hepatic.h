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
#include "system/physiology/SEHepaticSystem.h"

/**
 * @copydoc Physiology_HepaticystemData
 */  
class PULSE_API Hepatic : public SEHepaticSystem, public PulseSystem
{
  friend Pulse;
  friend class PulseEngineTest;
protected:
  Hepatic(Pulse& bg);
  Pulse& m_data;

public:
  virtual ~Hepatic();

  void Clear();

  // Set members to a stable homeostatic state
  void Initialize();

  static void Load(const cdm::PatientData& src, SEPatient& dst);
  static cdm::PatientData* Unload(const SEPatient& src);
protected:
  static void Serialize(const cdm::PatientData& src, SEPatient& dst);
  static void Serialize(const SEPatient& src, cdm::PatientData& dst);

  // Load a state
  virtual bool Load(const CDM::PulseHepaticSystemData& in);
  virtual CDM::PulseHepaticSystemData* Unload() const;
protected:
  virtual void Unload(CDM::PulseHepaticSystemData& data) const;

  // Set pointers and other member varialbes common to both homeostatic initialization and loading a state
  void SetUp();

public:
  void AtSteadyState();
  void PreProcess();
  void Process();
  void PostProcess();

protected:

};