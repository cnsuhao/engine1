/* Distributed under the Apache License, Version 2.0.
See accompanying NOTICE file for details.*/

#pragma once 
#include <string>

class PhysiologyEngine;

public ref class PulseEngineRef
{
public:

  PulseEngineRef();
  PulseEngineRef(const std::string& logfile);
  //PulseEngineRef(Logger*);
  virtual ~PulseEngineRef();

  bool LoadStateFile(const std::string& filename);

  void AdvanceModelTime(double time_s);

  double GetLungVolume();


internal: // Should be hidden from C#, which is what we want for these.
  PhysiologyEngine* _pulse;
};