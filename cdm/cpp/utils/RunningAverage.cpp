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
