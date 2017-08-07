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
#include "system/equipment/ElectroCardioGram/SEElectroCardioGramWaveformInterpolator.h"
#include "properties/SEScalarTime.h"
#include "properties/SEScalarElectricPotential.h"
#include "properties/SEFunctionElectricPotentialVsTime.h"
#include <google/protobuf/text_format.h>

SEElectroCardioGramWaveformInterpolator::SEElectroCardioGramWaveformInterpolator(Logger* logger) : Loggable(logger)
{

}

SEElectroCardioGramWaveformInterpolator::~SEElectroCardioGramWaveformInterpolator()
{
  Clear();
}

void SEElectroCardioGramWaveformInterpolator::Clear()
{
  for (auto i : m_Waveforms)
    for (auto j : i.second)
      delete j.second;
  m_Waveforms.clear();
  m_Leads.clear();
}

void SEElectroCardioGramWaveformInterpolator::Load(const cdm::ElectroCardioGramWaveformListData& src, SEElectroCardioGramWaveformInterpolator& dst)
{
  SEElectroCardioGramWaveformInterpolator::Serialize(src, dst);
}
void SEElectroCardioGramWaveformInterpolator::Serialize(const cdm::ElectroCardioGramWaveformListData& src, SEElectroCardioGramWaveformInterpolator& dst)
{
  dst.Clear();
  for (int i = 0; i<src.waveform_size(); i++)
  {
    SEElectroCardioGramWaveform* waveform = new SEElectroCardioGramWaveform(dst.GetLogger());
    SEElectroCardioGramWaveform::Load(src.waveform()[i], *waveform);
    dst.m_Waveforms[waveform->GetLeadNumber()][waveform->GetRhythm()] = waveform;
  }
}

cdm::ElectroCardioGramWaveformListData* SEElectroCardioGramWaveformInterpolator::Unload(const SEElectroCardioGramWaveformInterpolator& src)
{
  cdm::ElectroCardioGramWaveformListData* dst = new cdm::ElectroCardioGramWaveformListData();
  SEElectroCardioGramWaveformInterpolator::Serialize(src, *dst);
  return dst;
}
void SEElectroCardioGramWaveformInterpolator::Serialize(const SEElectroCardioGramWaveformInterpolator& src, cdm::ElectroCardioGramWaveformListData& dst)
{
  for (auto i : src.m_Waveforms)
    for (auto j : i.second)
      dst.mutable_waveform()->AddAllocated(SEElectroCardioGramWaveform::Unload(*j.second));
}

bool SEElectroCardioGramWaveformInterpolator::LoadFile(const std::string& file, const SEScalarTime* timeStep)
{
  Clear();

  cdm::ElectroCardioGramWaveformListData src;
  std::ifstream file_stream(file, std::ios::in);
  std::string fmsg((std::istreambuf_iterator<char>(file_stream)), std::istreambuf_iterator<char>());
  if (!google::protobuf::TextFormat::ParseFromString(fmsg, &src))
    return false;
  SEElectroCardioGramWaveformInterpolator::Load(src, *this);

  // If its a binary string in the file...
  //std::ifstream binary_istream(patientFile, std::ios::in | std::ios::binary);
  //src.ParseFromIstream(&binary_istream);

  if (timeStep != nullptr)
    Interpolate(*timeStep);
  return true;
}

void SEElectroCardioGramWaveformInterpolator::Interpolate(const SEScalarTime& timeStep)
{
  for (auto& l : m_Waveforms)
    for(auto& w : l.second)
      if (w.second!=nullptr)
        Interpolate(*w.second, timeStep);
}
void SEElectroCardioGramWaveformInterpolator::Interpolate(SEElectroCardioGramWaveform& w, const SEScalarTime& timeStep)
{
    SEFunctionElectricPotentialVsTime& data = w.GetData();
    SEScalarTime* waveformTimeStep = nullptr;
    if (w.HasTimeStep())
      waveformTimeStep = &w.GetTimeStep();

    bool interpolate = true; // now we need to make the data correspond to our time step.      
    if (waveformTimeStep != nullptr)
    {
      if (waveformTimeStep->Equals(timeStep)) // if the data is already sampled at the engine's time step, no interpolation is needed
        interpolate = false;
    }
    if (interpolate)
    {
      // NOTE: This assumes that the data is a SINGLE waveform
      std::vector<double>  iTime;
      std::vector<double>& wTime = data.GetTime();
      std::vector<double>& wEleP = data.GetElectricPotential();
      double currentTime_s = 0;
      double timeStep_s = timeStep.GetValue(TimeUnit::s);
      double endTime_s = wTime[wTime.size()-1];
      while (currentTime_s <= endTime_s) // figure out how many data points are needed and populate the new time vector
      {
        iTime.push_back(currentTime_s);
        currentTime_s += timeStep_s;
      }
      SEFunctionElectricPotentialVsTime* iWaveForm = data.InterpolateToTime(iTime, TimeUnit::s); // creates the new waveform data
      cdm::FunctionElectricPotentialVsTimeData* wfData = SEFunctionElectricPotentialVsTime::Unload(*iWaveForm);
      SEFunctionElectricPotentialVsTime::Load(*wfData, data);
      delete wfData;
      delete iWaveForm;
    }
}

bool SEElectroCardioGramWaveformInterpolator::CanInterpolateLeadPotential(cdm::ElectroCardioGramWaveformData_eLead lead, cdm::eHeartRhythm rhythm) const
{
  if (!HasWaveform(lead, rhythm))
    return false;
  auto l = m_Leads.find(lead);
  if (l == m_Leads.end())
    return false;  
  return l->second != nullptr;
}
void SEElectroCardioGramWaveformInterpolator::SetLeadElectricPotential(cdm::ElectroCardioGramWaveformData_eLead lead, SEScalarElectricPotential& ep)
{
  m_Leads[lead] = &ep;
}

bool SEElectroCardioGramWaveformInterpolator::StartNewCycle(cdm::eHeartRhythm rhythm)
{
  for (auto l2rw : m_Waveforms)
  {
    if (m_Leads.find(l2rw.first)==m_Leads.end() && !HasWaveform(l2rw.first, rhythm))
    {
      std::stringstream ss;
      ss << "Waveform not provided for Lead " << l2rw.first << " rhythm " << rhythm;
      Error(ss);
      return false;
    }
    l2rw.second[rhythm]->GetActiveIndicies().push_back(0);
  }
  return true;
}

//--------------------------------------------------------------------------------------------------
/// \brief
/// Prepares the ECG output data
///
/// \details
/// CalculateWaveform takes data from all active iterators and sums them together. It also assigns
/// the unit of millivolts to the output. If there are no active iterators, the output defaults to 0.
//--------------------------------------------------------------------------------------------------
void SEElectroCardioGramWaveformInterpolator::CalculateWaveformsElectricPotential()
{ 
  // Pull Data from our iterators
  int idx;
  double val;
  for (auto &l2s : m_Leads)//Lead# to Scalar
  {
    SEScalarElectricPotential* ep = l2s.second;
    if (ep == nullptr)
      continue;
    ep->SetValue(0, ElectricPotentialUnit::mV);

    for (auto & r2w : m_Waveforms[l2s.first])//rhythm to indecies
    {
      int i = 0;
      SEElectroCardioGramWaveform* waveform = r2w.second;
      if (waveform == nullptr)
        continue;
      SEFunctionElectricPotentialVsTime& data = waveform->GetData();
      for (unsigned int i = 0; i < waveform->GetActiveIndicies().size(); i++)
      {
        idx = waveform->GetActiveIndicies()[i];
        val = data.GetElectricPotentialValue(idx++, *data.GetElectricPotentialUnit());
        ep->IncrementValue(val, *data.GetElectricPotentialUnit());
        if (idx == data.Length())
          waveform->GetActiveIndicies().erase(waveform->GetActiveIndicies().begin() + i--);// Remove the iterator if we are at the end
        else
          waveform->GetActiveIndicies()[i] = idx;// Increment iterator  
      }
    }
  }
    
}

bool SEElectroCardioGramWaveformInterpolator::HasWaveform(cdm::ElectroCardioGramWaveformData_eLead lead, cdm::eHeartRhythm rhythm) const
{
  auto l = m_Waveforms.find(lead);
  if (l == m_Waveforms.end())
    return false;
  auto w = l->second.find(rhythm);
  if (w == l->second.end())
    return false;
  return w->second != nullptr;
}
SEElectroCardioGramWaveform& SEElectroCardioGramWaveformInterpolator::GetWaveform(cdm::ElectroCardioGramWaveformData_eLead lead, cdm::eHeartRhythm rhythm)
{
  SEElectroCardioGramWaveform* w = m_Waveforms[lead][rhythm];
  if (w == nullptr)
  {
    w = new SEElectroCardioGramWaveform(GetLogger());
    m_Waveforms[lead][rhythm] = w;
  }
  return *w;
}
const SEElectroCardioGramWaveform* SEElectroCardioGramWaveformInterpolator::GetWaveform(cdm::ElectroCardioGramWaveformData_eLead lead, cdm::eHeartRhythm rhythm) const
{
  auto l = m_Waveforms.find(lead);
  if (l == m_Waveforms.end())
    return nullptr;
  auto w = l->second.find(rhythm);
  if (w == l->second.end())
    return nullptr;
  return w->second;
}
void SEElectroCardioGramWaveformInterpolator::RemoveWaveform(cdm::ElectroCardioGramWaveformData_eLead lead, cdm::eHeartRhythm rhythm)
{
  auto l = m_Waveforms.find(lead);
  if (l == m_Waveforms.end())
    return;
  auto w = l->second.find(rhythm);
  if (w == l->second.end())
    return;
  delete w->second;
  w->second = nullptr;
}