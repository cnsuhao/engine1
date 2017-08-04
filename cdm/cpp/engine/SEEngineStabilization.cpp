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
#include "engine/SEEngineStabilization.h"
#include "properties/SEScalarTime.h"

SEEngineStabilization::SEEngineStabilization(Logger *logger) : Loggable(logger)
{
  m_StabilizationDuration = nullptr;
  m_currentTime_s = 0;
  m_TrackingStabilization = cdm::Off;
}

SEEngineStabilization::~SEEngineStabilization()
{
  Clear();
}

void SEEngineStabilization::Clear()
{
  m_LogProgress = true;
  m_TrackingStabilization = cdm::Off;
  SAFE_DELETE(m_StabilizationDuration);
}

void SEEngineStabilization::LogProgress(bool b)
{
  m_LogProgress = b;
}

void SEEngineStabilization::TrackStabilization(cdm::eSwitch state)
{
  m_TrackingStabilization = state;
}
bool SEEngineStabilization::IsTrackingStabilization()
{
  return m_TrackingStabilization==cdm::On;
}

void SEEngineStabilization::CancelStabilization()
{
  m_Cancelled = true;
}

bool SEEngineStabilization::HasStabilizationDuration()
{
  return m_StabilizationDuration == nullptr ? false : m_StabilizationDuration->IsValid();
}
SEScalarTime& SEEngineStabilization::GetStabilizationDuration()
{
  if (m_StabilizationDuration == nullptr)
    m_StabilizationDuration = new SEScalarTime();
  return *m_StabilizationDuration;
}