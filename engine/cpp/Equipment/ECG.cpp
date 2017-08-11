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
#include "ECG.h"
#include "../Systems/Cardiovascular.h"
#include "properties/SEScalarFrequency.h"
#include "properties/SEFunctionElectricPotentialVsTime.h"
#include "properties/SEScalarTime.h"

/*
========================
Constructors
========================
*/

ECG::ECG(PulseController& data) : SEElectroCardioGram(data.GetLogger()), m_data(data), m_interpolator(data.GetLogger())
{
  Clear();
}

ECG::~ECG()
{
  Clear();
}

//--------------------------------------------------------------------------------------------------
/// \brief Cleans up any memory this class is responsible for
//--------------------------------------------------------------------------------------------------
void ECG::Clear()
{
  SEElectroCardioGram::Clear();
}

//--------------------------------------------------------------------------------------------------
/// \brief
/// Initializes the ECG specific quantities
///
/// \details
/// Local member variables used in the ECG class are initialized here. These variables are used to
/// keep track of the heart cycle and to create the ECG machine's output. 
/// SEElectrocardioGramInterpolater also loads in the data needed to create the output and
/// interpolates it to match our time step. Placing the variables in this function allows for the 
/// system to be easy initialized at the beginning of a simulation or after a crash.
//--------------------------------------------------------------------------------------------------
void ECG::Initialize()
{
  PulseSystem::Initialize();

  m_heartRhythmTime.SetValue(0,TimeUnit::s);
  m_heartRhythmPeriod.SetValue(0, TimeUnit::s);
  auto* d = SEElectroCardioGramWaveformInterpolator::Unload(*m_data.GetConfiguration().GetECGInterpolator());
  SEElectroCardioGramWaveformInterpolator::Load(*d, m_interpolator);
  delete d;
  // You can uncomment this code to compare the original waveform to the interpolated waveform and make sure you are capturing the data properly
/* Code to write out the ECG data in a format easy to view in plotting tools 
  std::vector<double> original_s = m_interpolator.GetWaveform(3, CDM::enumHeartRhythm::NormalSinus).GetData().GetTime();
  std::vector<double> original_mV = m_interpolator.GetWaveform(3, CDM::enumHeartRhythm::NormalSinus).GetData().GetElectricPotential();
  DataTrack Original;  
  for (size_t i = 0; i < original_s.size(); i++)
    Original.Track("Original_ECG",original_s[i], original_mV[i]);
  Original.WriteTrackToFile("OriginalECG.txt");
*/
  // jbw m_interpolator.Interpolate(m_data.GetTimeStep());
/* Code to write out the Interpolated ECG data in a format easy to view in plotting tools
  std::vector<double> interpolated_s = m_interpolator.GetWaveform(3, CDM::enumHeartRhythm::NormalSinus).GetData().GetTime();
  std::vector<double> interpolated_mV = m_interpolator.GetWaveform(3, CDM::enumHeartRhythm::NormalSinus).GetData().GetElectricPotential();
  DataTrack Interpolated;
  for (size_t i = 0; i < interpolated_s.size(); i++)
    Interpolated.Track("Interpolated_ECG", interpolated_s[i], interpolated_mV[i]);
  Interpolated.WriteTrackToFile("InterpolatedECG.txt");
*/
  m_interpolator.SetLeadElectricPotential(cdm::ElectroCardioGramWaveformData_eLead_Lead3, GetLead3ElectricPotential());
}

void ECG::Load(const pulse::ElectroCardioGramData& src, ECG& dst)
{
  ECG::Serialize(src, dst);
  dst.SetUp();
}
void ECG::Serialize(const pulse::ElectroCardioGramData& src, ECG& dst)
{
  dst.m_heartRhythmTime.SetValue(src.heartrythmtime_s(),TimeUnit::s);
  dst.m_heartRhythmPeriod.SetValue(src.heartrythmperiod_s(),TimeUnit::s);
  SEElectroCardioGramWaveformInterpolator::Load(src.waveforms(),dst.m_interpolator);
  dst.m_interpolator.SetLeadElectricPotential(cdm::ElectroCardioGramWaveformData_eLead_Lead3, dst.GetLead3ElectricPotential());
}

pulse::ElectroCardioGramData* ECG::Unload(const ECG& src)
{
  pulse::ElectroCardioGramData* dst = new pulse::ElectroCardioGramData();
  ECG::Serialize(src,*dst);
  return dst;
}
void ECG::Serialize(const ECG& src, pulse::ElectroCardioGramData& dst)
{
  dst.set_heartrythmtime_s(src.m_heartRhythmTime.GetValue(TimeUnit::s));
  dst.set_heartrythmperiod_s(src.m_heartRhythmPeriod.GetValue(TimeUnit::s));
  dst.set_allocated_waveforms(SEElectroCardioGramWaveformInterpolator::Unload(src.m_interpolator));
}

void ECG::SetUp()
{
  m_dt_s = m_data.GetTimeStep().GetValue(TimeUnit::s);
}

//--------------------------------------------------------------------------------------------------
/// \brief
/// Prepares the ECG machine for the circuit solver
///
/// \details
/// At this time, we do not have a circuit model for the ECG machine so this function is left empty.
/// The PreProcess function is included to preserve our system methodology and as a placeholder for
/// models developed in the future.
//--------------------------------------------------------------------------------------------------
void ECG::PreProcess()
{

}

//--------------------------------------------------------------------------------------------------
/// \brief
/// Process creates the ECG output
///
/// \details
/// The process function queries the heart rhythm and heart rate from the cardiovascular system. The
/// time period of the heart beat is determined from the heart rate and a new iterator on the waveform
/// is initialized if the queried rhythm is Normal Sinus. The iterator holds the value of the waveform
/// data at a specific time point on the interpolated waveform data. Process increments the time point
/// and sums up the value of any active iterators. The iterators continue being incremented until they
/// reach the end of the interpolated waveform data. If there are no active iterators, the output
/// defaults to 0 mV.
//--------------------------------------------------------------------------------------------------
void ECG::Process()
{
  m_heartRhythmTime.IncrementValue(m_dt_s,TimeUnit::s);
  if (m_heartRhythmTime.GetValue(TimeUnit::s) >= m_heartRhythmPeriod.GetValue(TimeUnit::s))
  {
    m_heartRhythmTime.SetValue(0,TimeUnit::s);
    m_heartRhythmPeriod.SetValue(1/m_data.GetCardiovascular().GetHeartRate(FrequencyUnit::Per_s),TimeUnit::s);  
    // Currently we  have one data set for all currently supported Heart Rhythms
    // Eventually we will support multiple rhythmic data
    if(m_data.GetCardiovascular().GetHeartRhythm() == cdm::eHeartRhythm::NormalSinus)
      m_interpolator.StartNewCycle(cdm::eHeartRhythm::NormalSinus);
    else
    {
      m_ss << m_data.GetCardiovascular().GetHeartRhythm() << " is not a supported Heart Rhythm for ECG";
      Error(m_ss);
    }
  }
  m_interpolator.CalculateWaveformsElectricPotential();
}

//--------------------------------------------------------------------------------------------------
/// \brief
/// Post process updates the math after the circuit calculation are done
///
/// \details
/// At this time, we do not have a circuit model for the ECG machine so this function is left empty.
/// The PostProcess function is included to preserve our system methodology and as a placeholder for
/// models developed in the future.
//--------------------------------------------------------------------------------------------------
void ECG::PostProcess()
{

}