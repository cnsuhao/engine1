/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

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
  m_TrackingStabilization = (state == cdm::eSwitch::NullSwitch) ? cdm::eSwitch::Off : state;
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