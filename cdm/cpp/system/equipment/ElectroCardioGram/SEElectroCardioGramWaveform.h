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
#include "bind/cdm/ElectroCardioGram.pb.h"

class DLL_DECL SEElectroCardioGramWaveform : public Loggable
{
public:

  SEElectroCardioGramWaveform(Logger* logger);
  virtual ~SEElectroCardioGramWaveform();

  virtual void Clear();// Deletes all members

  static void Load(const cdm::ElectroCardioGramWaveformData& src, SEElectroCardioGramWaveform& dst);
  static cdm::ElectroCardioGramWaveformData* Unload(const SEElectroCardioGramWaveform& src);
protected:
  static void Serialize(const cdm::ElectroCardioGramWaveformData& src, SEElectroCardioGramWaveform& dst);
  static void Serialize(const SEElectroCardioGramWaveform& src, cdm::ElectroCardioGramWaveformData& dst);

public:  
  virtual bool HasLeadNumber() const;
  virtual cdm::ElectroCardioGramWaveformData_eLead  GetLeadNumber() const;
  virtual void SetLeadNumber(cdm::ElectroCardioGramWaveformData_eLead n);
  virtual void InvalidateLeadNumber();

  virtual cdm::eHeartRhythm GetRhythm() const;
  virtual void SetRhythm(cdm::eHeartRhythm name);

  virtual bool HasData() const;
  virtual SEFunctionElectricPotentialVsTime& GetData();
  virtual const SEFunctionElectricPotentialVsTime* GetData() const;

  virtual bool HasTimeStep() const;
  virtual SEScalarTime& GetTimeStep();
  virtual double GetTimeStep(const TimeUnit& unit) const;

  virtual std::vector<unsigned int>& GetActiveIndicies() { return m_ActiveIndicies; }

protected:

  cdm::ElectroCardioGramWaveformData_eLead m_LeadNumber;
  cdm::eHeartRhythm                        m_Rhythm;
  SEScalarTime*                            m_TimeStep;
  SEFunctionElectricPotentialVsTime*       m_Data;
  std::vector<unsigned int>                m_ActiveIndicies;
};