/* Distributed under the Apache License, Version 2.0.
See accompanying NOTICE file for details.*/

#pragma once 
#include <string>

class PhysiologyEngine;
class PulseLogger;
class PulseEventHandler;

class SEGasCompartment;
class SEGasSubstanceQuantity;
class SELiquidCompartment;
class SELiquidSubstanceQuantity;


public ref class PulseEngineRef
{
public:

  PulseEngineRef();
  PulseEngineRef(System::String^ logfile);
  //PulseEngineRef(Logger*);
  virtual ~PulseEngineRef();

  bool LoadStateFile(System::String^ filename);

  void AdvanceModelTime(double time_s);

  double GetLungVolume();

  double GetMusclePressure();

  double GetRespiratoryRate();

  double GetPulmonaryResistance();

  double GetPulmonaryCompliance();

  double GetInspTime();

  double GetExpTime();

protected:

internal: // Should be hidden from C#, which is what we want for these.
  // Utility to convert C# strings to C++ Strings
  std::string MarshalString(System::String^ s);

  PhysiologyEngine*  _pulse;
  PulseLogger*       _logger;
  PulseEventHandler* _events;

  // Get substances and compartments we are interested in
  const SELiquidCompartment* _aorta;
  const SELiquidSubstanceQuantity* _aorta_O2;
  const SELiquidSubstanceQuantity* _aorta_CO2;

  const SEGasCompartment* _carina;
  const SEGasSubstanceQuantity* _carina_O2;
  const SEGasSubstanceQuantity* _carina_CO2;
};

// Create function pointers to call when we get events that are of interest to us
// If you want, you can add the active bool and/or time to the function definition
// For this example, I can check activity in my handler and I don't need to propagate time
// It's up to you what data you provide your system, just know you can!
typedef void(__stdcall *fpStartOfInhale)(void); 
// When I get more time, I think we can make a single function pointer such as
typedef void(__stdcall *fpPatientEvent)(unsigned int type, bool active, double time_s);
// But type is an enum from C++, and I don't want to change an enum to a uint...
// I am not sure what datatype I would use in a C# delegate to map to a C++ enum at this point...
// And do it clean... TBD

public ref class PulseEventsRef abstract
{
  delegate void StartOfInhale();// This can be cast to the C++ function pointer, so it needs the same spec as our function pointer above
public:
  void SetupEventHandler(PulseEngineRef^ pulse);// A method to setup the function handshake between C# an C++
protected:
  virtual void OnStartOfInhale() abstract;// CSharp will override this, and it will be called by the Pulse Event Handler
};

// Doing the same thing for the logger
typedef void(__stdcall *fpLog)(const std::string&);
public ref class PulseLoggerRef abstract
{
  delegate void Fatal(const std::string& msg);
  delegate void Error(const std::string& msg);
  delegate void Warn(const std::string& msg);
  delegate void Info(const std::string& msg);
  delegate void Debug(const std::string& msg);

  System::String^ MarshalString(const std::string& s);
  void MarshalFatal(const std::string& msg) { OnFatal(MarshalString(msg)); }
  void MarshalError(const std::string& msg) { OnError(MarshalString(msg)); }
  void MarshalWarn(const std::string& msg)  { OnWarn(MarshalString(msg));  }
  void MarshalInfo(const std::string& msg)  { OnInfo(MarshalString(msg));  }
  void MarshalDebug(const std::string& msg) { OnDebug(MarshalString(msg)); }
public:
  void SetupCallbacks(PulseEngineRef^ pulse);// A method to setup the function handshake between C# an C++
protected:
  virtual void OnFatal(System::String^ msg) abstract;// CSharp will override this, and it will be called by the Pulse Logger
  virtual void OnError(System::String^ msg) abstract;// CSharp will override this, and it will be called by the Pulse Logger
  virtual void OnWarn(System::String^ msg) abstract;// CSharp will override this, and it will be called by the Pulse Logger
  virtual void OnInfo(System::String^ msg) abstract;// CSharp will override this, and it will be called by the Pulse Logger
  virtual void OnDebug(System::String^ msg) abstract;// CSharp will override this, and it will be called by the Pulse Logger
};

