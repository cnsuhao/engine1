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
#include "system/equipment/ElectroCardioGram/SEElectroCardioGramWaveform.h"


class CDM_DECL SEElectroCardioGramWaveformInterpolator : public Loggable
{
public:

  SEElectroCardioGramWaveformInterpolator(Logger* logger);
  virtual ~SEElectroCardioGramWaveformInterpolator();

  virtual void Clear();// Deletes all members

  virtual bool LoadFile(const std::string& file, const SEScalarTime* timeStep = nullptr);

  static void Load(const cdm::ElectroCardioGramWaveformListData& src, SEElectroCardioGramWaveformInterpolator& dst);
  static cdm::ElectroCardioGramWaveformListData* Unload(const SEElectroCardioGramWaveformInterpolator& src);
protected:
  static void Serialize(const cdm::ElectroCardioGramWaveformListData& src, SEElectroCardioGramWaveformInterpolator& dst);
  static void Serialize(const SEElectroCardioGramWaveformInterpolator& src, cdm::ElectroCardioGramWaveformListData& dst);

public: 
  virtual void Interpolate(const SEScalarTime& timeStep);
  virtual bool StartNewCycle(cdm::eHeartRhythm rhythm);
  virtual void CalculateWaveformsElectricPotential();

  // These are where the interpolator will put the interpolated electric potential data for each lead when you call CalculateWaveformsElectricPotential
  // You must have a waveform for the lead of the current rhythm for these scalars to be populated
  virtual bool CanInterpolateLeadPotential(cdm::ElectroCardioGramWaveformData_eLead lead, cdm::eHeartRhythm rhythm) const;
  virtual void SetLeadElectricPotential(cdm::ElectroCardioGramWaveformData_eLead lead, SEScalarElectricPotential& ep);


  virtual bool HasWaveform(cdm::ElectroCardioGramWaveformData_eLead lead, cdm::eHeartRhythm rhythm) const;
  virtual SEElectroCardioGramWaveform& GetWaveform(cdm::ElectroCardioGramWaveformData_eLead lead, cdm::eHeartRhythm rhythm);
  virtual const SEElectroCardioGramWaveform* GetWaveform(cdm::ElectroCardioGramWaveformData_eLead lead, cdm::eHeartRhythm rhythm) const;
  virtual void RemoveWaveform(cdm::ElectroCardioGramWaveformData_eLead lead, cdm::eHeartRhythm rhythm);

protected:

  virtual void Interpolate(SEElectroCardioGramWaveform& waveform, const SEScalarTime& timeStep);
  
  std::map<cdm::ElectroCardioGramWaveformData_eLead, SEScalarElectricPotential*> m_Leads;
  std::map<cdm::ElectroCardioGramWaveformData_eLead, std::map<cdm::eHeartRhythm, SEElectroCardioGramWaveform*>> m_Waveforms;
};