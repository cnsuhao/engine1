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
#include "properties/SEHistogramFractionVsLength.h"
#include "properties/SEScalarLength.h"
#include "properties/SEScalar0To1.h"
#include <numeric>


SEHistogramFractionVsLength::SEHistogramFractionVsLength() : SEHistogram()
{
  
}

SEHistogramFractionVsLength::~SEHistogramFractionVsLength()
{
  Clear();
}

void SEHistogramFractionVsLength::Clear()
{
  SEHistogram::Clear();
  m_LengthUnit = nullptr;
}

bool SEHistogramFractionVsLength::IsVaild() const
{
  if (!SEHistogram::IsValid())
    return false;

  double binned = std::accumulate(m_Dependent.begin(), m_Dependent.end(), 0.);
  if (!SEScalar::IsValue(1, binned))
  {
   std::cerr << "Particle distribution histogram: Failed to correct a distribution error. Check distribution histogram." << std::endl; // todo properties need a logger
   return false;
  }
  return true;
}

void SEHistogramFractionVsLength::Load(const cdm::HistogramFractionVsLengthData& src, SEHistogramFractionVsLength& dst)
{
  SEHistogramFractionVsLength::Serialize(src, dst);
}
void SEHistogramFractionVsLength::Serialize(const cdm::HistogramFractionVsLengthData& src, SEHistogramFractionVsLength& dst)
{
  dst.Clear();
  for (int i = 0; i<src.histogramfractionvslength().histogram().dependent().value_size(); i++)
    dst.m_Dependent.push_back(src.histogramfractionvslength().histogram().dependent().value(i));
  for (int i = 0; i<src.histogramfractionvslength().histogram().independent().value_size(); i++)
    dst.m_Independent.push_back(src.histogramfractionvslength().histogram().independent().value(i));
}

cdm::HistogramFractionVsLengthData* SEHistogramFractionVsLength::Unload(const SEHistogramFractionVsLength& src)
{
  if (!src.IsValid())
    return nullptr;
  cdm::HistogramFractionVsLengthData* dst = new cdm::HistogramFractionVsLengthData();
  SEHistogramFractionVsLength::Serialize(src, *dst);
  return dst;
}
void SEHistogramFractionVsLength::Serialize(const SEHistogramFractionVsLength& src, cdm::HistogramFractionVsLengthData& dst)
{
  for (unsigned int i = 0; i<src.m_Dependent.size(); i++)
  {
    dst.mutable_histogramfractionvslength()->mutable_histogram()->mutable_dependent()->add_value(src.m_Dependent[i]);
    dst.mutable_histogramfractionvslength()->mutable_histogram()->mutable_independent()->add_value(src.m_Independent[i]);
  }
}
double SEHistogramFractionVsLength::GetLengthValue(unsigned int index, const LengthUnit& unit) const
{
  if (m_LengthUnit == nullptr)
    throw CommonDataModelException("No length units have been set");
  if (index >= m_Independent.size())
    throw CommonDataModelException("Independent index out of bounds");
  return Convert(m_Independent[index], *m_LengthUnit, unit);
}
std::vector<double>& SEHistogramFractionVsLength::GetLength()
{
  return m_Independent;
}
const std::vector<double>& SEHistogramFractionVsLength::GetLength() const
{
  return m_Independent;
}
const LengthUnit* SEHistogramFractionVsLength::GetLengthUnit() const
{
  return m_LengthUnit;
}
void SEHistogramFractionVsLength::SetLengthUnit(const LengthUnit& unit)
{
  m_LengthUnit = &unit;
}

double SEHistogramFractionVsLength::GetFractionValue(unsigned int index) const
{
  if (index >= m_Dependent.size())
    throw CommonDataModelException("Dependent index out of bounds");
  return m_Dependent[index];
}
std::vector<double>& SEHistogramFractionVsLength::GetFraction()
{
  return m_Dependent;
}
const std::vector<double>& SEHistogramFractionVsLength::GetFraction() const
{
  return m_Dependent;
}

