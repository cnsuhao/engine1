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
#include "utils/SEEventHandler.h"
#include "substance/SESubstanceManager.h"
#include "compartment/SECompartmentManager.h"
#include "compartment/substances/SEGasSubstanceQuantity.h"
#include "compartment/substances/SELiquidSubstanceQuantity.h"

class PulseLogger : public LoggerForward
{
public:
  // Make Set methods to set up a function pointer to call for each event we are interested in
  virtual void SetFatalCallback(fpLog callback) { _fatal = callback; }
  virtual void SetErrorCallback(fpLog callback) { _error = callback; }
  virtual void SetWarnCallback(fpLog callback) { _warn = callback; }
  virtual void SetInfoCallback(fpLog callback) { _info = callback; }
  virtual void SetDebugCallback(fpLog callback) { _debug = callback; }
protected:
  // Make a member variables for the function pointers we are to call
  fpLog _fatal;
  fpLog _error;
  fpLog _warn;
  fpLog _info;
  fpLog _debug;

public:// Note for my example, I am ignoring the origin (what class created this log msg)
  virtual void ForwardFatal(const std::string& msg, const std::string& origin)
  {
    _fatal(msg);
  }
  virtual void ForwardError(const std::string& msg, const std::string& origin)
  {
    _error(msg);
  }
  virtual void ForwardWarning(const std::string& msg, const std::string& origin)
  {
    _warn(msg);
  }
  virtual void ForwardInfo(const std::string& msg, const std::string& origin)
  {
    _info(msg);
  }
  virtual void ForwardDebug(const std::string& msg, const std::string& origin)
  {
    _debug(msg);
  }
};

void PulseLoggerRef::SetupCallbacks(PulseEngineRef^ pulse)
{
  using System::IntPtr;
  using System::Runtime::InteropServices::Marshal;
  IntPtr cbPtr;

  Fatal^ on_fatal = gcnew Fatal(
    this,
    &PulseLoggerRef::MarshalFatal
    );
  cbPtr = Marshal::GetFunctionPointerForDelegate(on_fatal);
  pulse->_logger->SetFatalCallback(static_cast<fpLog>(cbPtr.ToPointer()));

  Error^ on_error = gcnew Error(
    this,
    &PulseLoggerRef::MarshalError
    );
  cbPtr = Marshal::GetFunctionPointerForDelegate(on_error);
  pulse->_logger->SetErrorCallback(static_cast<fpLog>(cbPtr.ToPointer()));

  Warn^ on_warn = gcnew Warn(
    this,
    &PulseLoggerRef::MarshalWarn
    );
  cbPtr = Marshal::GetFunctionPointerForDelegate(on_warn);
  pulse->_logger->SetWarnCallback(static_cast<fpLog>(cbPtr.ToPointer()));

  Info^ on_info = gcnew Info(
    this,
    &PulseLoggerRef::MarshalInfo
    );
  cbPtr = Marshal::GetFunctionPointerForDelegate(on_info);
  pulse->_logger->SetInfoCallback(static_cast<fpLog>(cbPtr.ToPointer()));

  Debug^ on_debug = gcnew Debug(
    this,
    &PulseLoggerRef::MarshalFatal
    );
  cbPtr = Marshal::GetFunctionPointerForDelegate(on_debug);
  pulse->_logger->SetDebugCallback(static_cast<fpLog>(cbPtr.ToPointer()));
}

System::String^ PulseLoggerRef::MarshalString(const std::string& s)
{
  return gcnew System::String(s.c_str());
}


// This is the class to provide Pulse to call when any events are triggered in the engine
class PulseEventHandler : public SEEventHandler
{
public:
  PulseEventHandler(Logger *logger) : SEEventHandler(logger) {}

public:
  virtual void SetStartOfInhaleCallback(fpStartOfInhale callback) { _start_of_inhale = callback; }// Make Set methods to set up a function pointer to call for each event we are interested in
protected:
  fpStartOfInhale _start_of_inhale;// Make a member variables for the function pointers we are to call

  //These methods need definitions and should call your callback with what ever data you made it require
public:
  virtual void HandlePatientEvent(cdm::PatientData_eEvent type, bool active, const SEScalarTime* time = nullptr) 
  {
    // If you are looking for a lot of events, you should probably use a switch statement
    if (_start_of_inhale != nullptr && type == cdm::PatientData_eEvent_StartOfInhale && active)
    {
      _start_of_inhale();// Call the function pointer, from where ever it came and goes
    }
  }
  virtual void HandleAnesthesiaMachineEvent(cdm::AnesthesiaMachineData_eEvent type, bool active, const SEScalarTime* time = nullptr) 
  {

  }
};

void PulseEventsRef::SetupEventHandler(PulseEngineRef^ pulse)
{
  using System::IntPtr;
  using System::Runtime::InteropServices::Marshal;

  StartOfInhale^ start_of_inhale_callback = gcnew StartOfInhale(
    this,
    &PulseEventsRef::OnStartOfInhale
  );
  IntPtr cbPtr = Marshal::GetFunctionPointerForDelegate(start_of_inhale_callback);
  pulse->_events->SetStartOfInhaleCallback(static_cast<fpStartOfInhale>(cbPtr.ToPointer()));
}

PulseEngineRef::PulseEngineRef() : _pulse(CreatePulseEngine("").release())
{

}
PulseEngineRef::PulseEngineRef(System::String^ log) : _pulse(CreatePulseEngine(MarshalString(log)).release())
{

}
PulseEngineRef::~PulseEngineRef()
{
  delete _pulse;
  delete _events;
}


bool PulseEngineRef::LoadStateFile(System::String^ filename)
{
  if (_pulse->LoadStateFile(MarshalString(filename)))
  {
    // Grab any substances and compartments here
    // If you want substance quantity information, grab the substance first
    // You can find the string value identifying a substance from the bin/substance/*.pba files
    // The name of the file is the name of the substance, thje string name is also in the file
    // If the engine does not have a substance for the string you pass in, it will return nullptr!
    SESubstance* O2 = _pulse->GetSubstanceManager().GetSubstance("Oxygen");
    SESubstance* CO2 = _pulse->GetSubstanceManager().GetSubstance("CarbonDioxide");
    // Now get the compartment
    _aorta = _pulse->GetCompartments().GetLiquidCompartment(pulse::VascularCompartment::Aorta);
    //Now we can get the quantity properties of specific substances in this compartment
    _aorta_O2 = _aorta->GetSubstanceQuantity(*O2);
    _aorta_CO2 = _aorta->GetSubstanceQuantity(*CO2);
    // With liquid substance quantities you can get concentration/mass/etc. of the substance in this compartment

    _carina = _pulse->GetCompartments().GetGasCompartment(pulse::PulmonaryCompartment::Carina);
    //Now we can get the quantity properties of specific substances in this compartment
    _carina_O2 = _carina->GetSubstanceQuantity(*O2);
    _carina_CO2 = _carina->GetSubstanceQuantity(*CO2);
    // With gas substance quantities you can get volume/volume fraction/etc. of the substance in this compartment
    
    // Set up these communication classes to get information pushed 
    // from the engine when it happens so your app can process it
    _events = new PulseEventHandler(_pulse->GetLogger());
    _pulse->SetEventHandler(_events);
    _logger = new PulseLogger();
    _pulse->GetLogger()->SetForward(_logger);
    return true;
  }
  return false;
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
