/* Distributed under the Apache License, Version 2.0.
See accompanying NOTICE file for details.*/

#include "PulseEngine.h"

#include "PulsePhysiologyEngine.h"
#include "properties/SEScalarTime.h"
#include "properties/SEScalarVolume.h"
#include "system/physiology/SERespiratorySystem.h"

PulseEngineRef::PulseEngineRef() : _pulse(CreatePulseEngine("").release())
{

}
PulseEngineRef::PulseEngineRef(const std::string& log) : _pulse(CreatePulseEngine(log).release())
{

}
PulseEngineRef::~PulseEngineRef()
{
  delete _pulse;
}


bool PulseEngineRef::LoadStateFile(const std::string& filename)
{
  return _pulse->LoadStateFile(filename);
}

void PulseEngineRef::AdvanceModelTime(double time_s)
{
  _pulse->AdvanceModelTime(time_s, TimeUnit::s);
}

double PulseEngineRef::GetLungVolume()
{
  return _pulse->GetRespiratorySystem()->GetTotalLungVolume(VolumeUnit::mL);
}
