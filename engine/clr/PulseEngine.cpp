 /* Distributed under the Apache License, Version 2.0.
See accompanying NOTICE file for details.*/

#include "PulseEngine.h"

#include "PulsePhysiologyEngine.h"
#include "properties/SEScalarTime.h"
#include "properties/SEScalarVolume.h"
#include "properties/SEScalarPressure.h"
#include "properties/SEScalarFrequency.h"
#include "properties/SEScalarFlowCompliance.h"
#include "properties/SEScalarFlowResistance.h"
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

double PulseEngineRef::GetMusclePressure()
{
	return  round(_pulse->GetRespiratorySystem()->GetRespirationMusclePressure(PressureUnit::cmH2O));
}

double PulseEngineRef::GetRespiratoryRate()
{
	return _pulse->GetRespiratorySystem()->GetRespirationRate(FrequencyUnit::Per_min);
}

double PulseEngineRef::GetPulmonaryResistance()
{
	return _pulse->GetRespiratorySystem()->GetPulmonaryResistance(FlowResistanceUnit::cmH2O_s_Per_L);
}

double PulseEngineRef::GetPulmonaryCompliance()
{
	return _pulse->GetRespiratorySystem()->GetPulmonaryCompliance(FlowComplianceUnit::L_Per_cmH2O);
}

double PulseEngineRef::GetInspTime()
{
	double ItoE = _pulse->GetRespiratorySystem()->GetInspiratoryExpiratoryRatio();
	double RespRate = _pulse->GetRespiratorySystem()->GetRespirationRate(FrequencyUnit::Per_min);
	return RespRate / (ItoE + 1);
}

double PulseEngineRef::GetExpTime()
{
	double ItoE = _pulse->GetRespiratorySystem()->GetInspiratoryExpiratoryRatio();
	double RespRate = _pulse->GetRespiratorySystem()->GetRespirationRate(FrequencyUnit::Per_min);
	return RespRate*ItoE / (ItoE + 1);
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
