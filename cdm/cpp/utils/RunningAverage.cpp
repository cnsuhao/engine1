/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "utils/RunningAverage.h"

RunningAverage::RunningAverage()
{
  Reset();
}

RunningAverage::~RunningAverage()
{

}

void RunningAverage::Load(const cdm::RunningAverageData& src, RunningAverage& dst)
{
  RunningAverage::Serialize(src, dst);
}
void RunningAverage::Serialize(const cdm::RunningAverageData& src, RunningAverage& dst)
{
  dst.m_Sum = src.sum();
  dst.m_NumSamples = src.numsamples();
}

cdm::RunningAverageData* RunningAverage::Unload(const RunningAverage& src)
{
  cdm::RunningAverageData* dst = new cdm::RunningAverageData();
  RunningAverage::Serialize(src,*dst);
  return dst;
}
void RunningAverage::Serialize(const RunningAverage& src, cdm::RunningAverageData& dst)
{
  dst.set_sum(src.m_Sum);
  dst.set_numsamples(src.m_NumSamples);
}

void RunningAverage::Reset()
{
  m_Sum = 0.0;
  m_NumSamples = 0;
}

double RunningAverage::Sample(double d)
{
  m_Sum += d;
  m_NumSamples++;
  return Value();
}

double RunningAverage::Value()
{
  return m_Sum / double(m_NumSamples);
}
