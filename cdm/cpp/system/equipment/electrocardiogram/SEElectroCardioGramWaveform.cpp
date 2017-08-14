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

#include "stdafx.h"
#include "system/equipment/electrocardiogram/SEElectroCardioGramWaveform.h"
#include "properties/SEScalarTime.h"
#include "properties/SEScalarElectricPotential.h"
#include "properties/SEFunctionElectricPotentialVsTime.h"

SEElectroCardioGramWaveform::SEElectroCardioGramWaveform(Logger* logger) : Loggable(logger)
{
  m_TimeStep = nullptr;
  m_Data = nullptr;
  m_Rhythm = cdm::eHeartRhythm::NormalSinus;
  m_LeadNumber = cdm::ElectroCardioGramWaveformData_eLead_NullLead;
}

SEElectroCardioGramWaveform::~SEElectroCardioGramWaveform()
{
  Clear();
}

void SEElectroCardioGramWaveform::Clear()
{
  m_Rhythm = cdm::eHeartRhythm::NormalSinus;
  m_LeadNumber = cdm::ElectroCardioGramWaveformData_eLead_NullLead;
  SAFE_DELETE(m_TimeStep);
  SAFE_DELETE(m_Data);
  m_ActiveIndicies.clear();
}

void SEElectroCardioGramWaveform::Load(const cdm::ElectroCardioGramWaveformData& src, SEElectroCardioGramWaveform& dst)
{
  SEElectroCardioGramWaveform::Serialize(src, dst);
}
void SEElectroCardioGramWaveform::Serialize(const cdm::ElectroCardioGramWaveformData& src, SEElectroCardioGramWaveform& dst)
{
  dst.Clear();
  dst.m_Rhythm = src.rhythm();
  dst.m_LeadNumber = src.lead(); 
  if (src.has_timestep())
    SEScalarTime::Load(src.timestep(), dst.GetTimeStep());
  if(src.has_data())
    SEFunctionElectricPotentialVsTime::Load(src.data(), dst.GetData());
  for (int i = 0; i < src.activeindicies_size(); i++)
    dst.m_ActiveIndicies.push_back(src.activeindicies()[i]);
}

cdm::ElectroCardioGramWaveformData* SEElectroCardioGramWaveform::Unload(const SEElectroCardioGramWaveform& src)
{
  cdm::ElectroCardioGramWaveformData* dst = new cdm::ElectroCardioGramWaveformData();
  SEElectroCardioGramWaveform::Serialize(src,*dst);
  return dst;
}
void SEElectroCardioGramWaveform::Serialize(const SEElectroCardioGramWaveform& src, cdm::ElectroCardioGramWaveformData& dst)
{
  dst.set_rhythm(src.m_Rhythm);
  dst.set_lead(src.m_LeadNumber);
  if (src.HasData())
  {
    dst.set_allocated_data(SEFunctionElectricPotentialVsTime::Unload(*src.m_Data));
    for (int i : src.m_ActiveIndicies)
      dst.add_activeindicies(i);
  }
  if (src.HasTimeStep())
    dst.set_allocated_timestep(SEScalarTime::Unload(*src.m_TimeStep));
}


cdm::ElectroCardioGramWaveformData_eLead SEElectroCardioGramWaveform::GetLeadNumber() const
{
  return m_LeadNumber;
}
void SEElectroCardioGramWaveform::SetLeadNumber(cdm::ElectroCardioGramWaveformData_eLead n)
{
  m_LeadNumber = n;
}
bool SEElectroCardioGramWaveform::HasLeadNumber() const
{
  return m_LeadNumber == cdm::ElectroCardioGramWaveformData_eLead_NullLead ? false : true;
}
void SEElectroCardioGramWaveform::InvalidateLeadNumber()
{
  m_LeadNumber = cdm::ElectroCardioGramWaveformData_eLead_NullLead;
}

cdm::eHeartRhythm SEElectroCardioGramWaveform::GetRhythm() const
{
  return m_Rhythm;
}
void SEElectroCardioGramWaveform::SetRhythm(cdm::eHeartRhythm rhythm)
{
  m_Rhythm = rhythm;
}

bool SEElectroCardioGramWaveform::HasData() const
{
  return m_Data == nullptr ? false : m_Data->IsValid();
}
SEFunctionElectricPotentialVsTime& SEElectroCardioGramWaveform::GetData()
{
  if (m_Data == nullptr)
    m_Data = new SEFunctionElectricPotentialVsTime();
  return *m_Data;
}
const SEFunctionElectricPotentialVsTime* SEElectroCardioGramWaveform::GetData() const
{
  return m_Data;
}

bool SEElectroCardioGramWaveform::HasTimeStep() const
{
  return m_TimeStep == nullptr ? false : m_TimeStep->IsValid();
}
SEScalarTime& SEElectroCardioGramWaveform::GetTimeStep()
{
  if (m_TimeStep == nullptr)
    m_TimeStep = new SEScalarTime();
  return *m_TimeStep;
}
double SEElectroCardioGramWaveform::GetTimeStep(const TimeUnit& unit) const
{
  if (m_TimeStep == nullptr)
    return SEScalar::dNaN();
  return m_TimeStep->GetValue(unit);
}


