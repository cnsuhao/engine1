/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "properties/SEHistogram.h"

static std::stringstream err;

SEHistogram::SEHistogram() : SEProperty()
{

}

SEHistogram::~SEHistogram()
{
  Clear();
}

void SEHistogram::Clear()
{
  m_Dependent.clear();
  m_Independent.clear();
}

bool SEHistogram::IsValid() const
{  
  if (m_Dependent.size() == 0 || m_Independent.size() == 0)
  {
    std::cerr << "Histogram: No data provided." << std::endl;//todo make properties have a logger
    return false;
  }
  if (m_Dependent.size() + 1 != m_Independent.size())
  {
    std::cerr << "Histogram: Size mismatch between boundaries and bins." << std::endl;//todo make properties have a logger
    return false;
  }
  return true;
}

void SEHistogram::Invalidate()
{
  Clear();
}

void SEHistogram::Load(const cdm::HistogramData& src, SEHistogram& dst)
{
  SEHistogram::Serialize(src, dst);

  if (!src.histogram().dependentunit().empty())
  {
    if (src.histogram().dependentunit() != "unitless")
      throw CommonDataModelException("CDM::Histogram API is intended to be unitless, You are trying to load a dependent axis with a unit defined");
  }
  if (!src.histogram().independentunit().empty())
  {
    if (src.histogram().independentunit() != "unitless")
      throw CommonDataModelException("CDM::Histogram API is intended to be unitless, You are trying to load an independent axis with a unit defined");
  }
}
void SEHistogram::Serialize(const cdm::HistogramData& src, SEHistogram& dst)
{
  dst.Clear();
  for (int i = 0; i<src.histogram().dependent().value_size(); i++)
    dst.m_Dependent.push_back(src.histogram().dependent().value(i));
  for (int i = 0; i<src.histogram().independent().value_size(); i++)
    dst.m_Independent.push_back(src.histogram().independent().value(i));
}

cdm::HistogramData* SEHistogram::Unload(const SEHistogram& src)
{
  if (!src.IsValid())
    return nullptr;
  cdm::HistogramData* dst = new cdm::HistogramData();
  SEHistogram::Serialize(src, *dst);
  return dst;
}
void SEHistogram::Serialize(const SEHistogram& src, cdm::HistogramData& dst)
{
  for (size_t i = 0; i<src.m_Dependent.size(); i++)
  {
    dst.mutable_histogram()->mutable_dependent()->add_value(src.m_Dependent[i]);
    dst.mutable_histogram()->mutable_independent()->add_value(src.m_Independent[i]);
  }
}

size_t SEHistogram::NumberOfBins() const
{
  if(IsValid())
    return m_Dependent.size();
  return 0;
}

size_t SEHistogram::NumberOfBoundaries() const
{
  if (IsValid())
    return m_Independent.size();
  return 0;
}

double SEHistogram::GetDependentValue(size_t index) const
{
  if (index >= m_Dependent.size())
    throw CommonDataModelException("Dependent index out of bounds");
  return m_Dependent[index];
}

std::vector<double>& SEHistogram::GetDependent()                                  
{
  return m_Dependent;
}
const std::vector<double>& SEHistogram::GetDependent() const
{
  return m_Dependent;
}

double SEHistogram::GetIndependentValue(size_t index) const
{
  if (index >= m_Independent.size())
    throw CommonDataModelException("Independent index out of bounds");
  return m_Independent[index];
}

std::vector<double>& SEHistogram::GetIndependent()                                  
{
  return m_Independent;
}
const std::vector<double>& SEHistogram::GetIndependent() const
{
  return m_Independent;
}
