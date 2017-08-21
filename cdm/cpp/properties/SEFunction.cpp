/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "properties/SEFunction.h"
#include "properties/SEScalar.h"//Utils

static std::stringstream err;

SEFunction::SEFunction() : SEProperty()
{

}

SEFunction::~SEFunction()
{
  Clear();
}

void SEFunction::Clear()
{
  m_Dependent.clear();
  m_Independent.clear();
}

bool SEFunction::IsValid() const
{  
  if(m_Dependent.size()==0||m_Independent.size()==0)
    return false;
  if(m_Dependent.size()!=m_Independent.size())
    return false;
  return true;
}

void SEFunction::Invalidate()
{
  Clear();
}

void SEFunction::Load(const cdm::FunctionData& src, SEFunction& dst)
{
  SEFunction::Serialize(src, dst);

  if (!src.dependentunit().empty())
  {
    if (src.dependentunit() != "unitless")
      throw CommonDataModelException("CDM::Function API is intended to be unitless, You are trying to load a dependent axis with a unit defined");
  }
  if (!src.independentunit().empty())
  {
    if (src.independentunit() != "unitless")
      throw CommonDataModelException("CDM::Function API is intended to be unitless, You are trying to load an independent axis with a unit defined");
  }
}
void SEFunction::Serialize(const cdm::FunctionData& src, SEFunction& dst)
{
  dst.Clear();
  for (int i = 0; i<src.dependent().value_size(); i++)
    dst.m_Dependent.push_back(src.dependent().value(i));
  for (int i = 0; i<src.independent().value_size(); i++)
    dst.m_Independent.push_back(src.independent().value(i));
}

cdm::FunctionData* SEFunction::Unload(const SEFunction& src)
{
  if (!src.IsValid())
    return nullptr;
  cdm::FunctionData* dst = new cdm::FunctionData();
  SEFunction::Serialize(src, *dst);
  return dst;
}
void SEFunction::Serialize(const SEFunction& src, cdm::FunctionData& dst)
{
  for (size_t i = 0; i<src.m_Dependent.size(); i++)
  {
    dst.mutable_dependent()->add_value(src.m_Dependent[i]);
    dst.mutable_independent()->add_value(src.m_Independent[i]);
  }
}

size_t SEFunction::Length()
{
  if(IsValid())
    return m_Independent.size();
  return 0;
}

double SEFunction::GetDependentValue(size_t index)
{
  if (index >= m_Dependent.size())
    throw CommonDataModelException("Dependent index out of bounds");
  return m_Dependent[index];
}

std::vector<double>& SEFunction::GetDependent()                                  
{
  return m_Dependent;
}

double SEFunction::GetIndependentValue(size_t index)
{
  if (index >= m_Independent.size())
    throw CommonDataModelException("Independent index out of bounds");
  return m_Independent[index];
}

std::vector<double>& SEFunction::GetIndependent()                                  
{
  return m_Independent;
}
