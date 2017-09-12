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
PulseEngineRef::PulseEngineRef(System::String^ log) : _pulse(CreatePulseEngine(MarshalString(log)).release())
{

}
PulseEngineRef::~PulseEngineRef()
{
  delete _pulse;
}


bool PulseEngineRef::LoadStateFile(System::String^ filename)
{
  return _pulse->LoadStateFile(MarshalString(filename));
}

void PulseEngineRef::AdvanceModelTime(double time_s)
{
  _pulse->AdvanceModelTime(time_s, TimeUnit::s);
}

double PulseEngineRef::GetLungVolume()
{
  return _pulse->GetRespiratorySystem()->GetTotalLungVolume(VolumeUnit::mL);
}

std::string PulseEngineRef::MarshalString(System::String^ s)
{
  using namespace System::Runtime::InteropServices;
  const char* chars =
    (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
  std::string os = chars;
  Marshal::FreeHGlobal(System::IntPtr((void*)chars));
  return os;
}
