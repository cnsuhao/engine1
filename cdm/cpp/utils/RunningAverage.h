/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "bind/cdm/Properties.pb.h"

class CDM_DECL RunningAverage
{
public:
  
  RunningAverage();
  virtual ~RunningAverage();


  static void Load(const cdm::RunningAverageData& src, RunningAverage& dst);
  static cdm::RunningAverageData* Unload(const RunningAverage& src);
protected:
  static void Serialize(const cdm::RunningAverageData& src, RunningAverage& dst);
  static void Serialize(const RunningAverage& src, cdm::RunningAverageData& dst);

public:
  /** Reset Counter info */
  void Reset();
  /** Add value to Sample list and return the new average */
  double Sample(double d);
  /** Return the average value */
  double Value();

  unsigned int NumSamples() { return m_NumSamples; }
  
protected:

  double          m_Sum;
  unsigned int    m_NumSamples;
};
