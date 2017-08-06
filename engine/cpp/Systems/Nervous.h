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
#include "system/physiology/SENervousSystem.h"

/**
 * @brief 
 * The nervous class holds models of the peripheral and central nervous system. Currently, on the baroreceptor reflex is modeled.
 */  
class PULSE_API Nervous : public SENervousSystem, public PulseSystem
{
  friend Pulse;
  friend class PulseEngineTest;
protected:
  Nervous(Pulse& bg);
  Pulse& m_data;

public:
  virtual ~Nervous();

  void Clear();

  // Set members to a stable homeostatic state
  void Initialize();

  static void Load(const cdm::PatientData& src, SEPatient& dst);
  static cdm::PatientData* Unload(const SEPatient& src);
protected:
  static void Serialize(const cdm::PatientData& src, SEPatient& dst);
  static void Serialize(const SEPatient& src, cdm::PatientData& dst);

  // Load a state
  virtual bool Load(const CDM::PulseNervousSystemData& in);
  virtual CDM::PulseNervousSystemData* Unload() const;
protected:
  virtual void Unload(CDM::PulseNervousSystemData& data) const;

  // Set pointers and other member variables common to both homeostatic initialization and loading a state
  void SetUp();

public:
  void AtSteadyState();  
  void PreProcess();
  void Process();
  void PostProcess();

protected:
  void BaroreceptorFeedback();
  void CheckBrainStatus();
  void ChemoreceptorFeedback();
  void SetPupilEffects();

  // Serializable member variables (Set in Initialize and in schema)    
  double m_ArterialOxygenSetPoint_mmHg; /// \todo Aaron these should be baselines.
  double m_ArterialCarbonDioxideSetPoint_mmHg;

  // Stateless member variable (Set in SetUp())
  bool m_FeedbackActive;
  double m_dt_s;
  // Configuration fractions representing the amount by which each quantity can change due to baroreceptors;
  double m_normalizedGammaHeartRate;
  double m_normalizedGammaElastance;
  double m_normalizedGammaCompliance;
  double m_normalizedGammaResistance;
  double m_normalizedAlphaHeartRate;
  double m_normalizedAlphaElastance;
  double m_normalizedAlphaCompliance;
  double m_normalizedAlphaResistance;
  double m_normalizedBetaHeartRate;
};
