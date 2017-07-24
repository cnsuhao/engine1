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
#include "substance/SESubstanceCompound.h"
#include "substance/SESubstanceConcentration.h"
#include "substance/SESubstanceManager.h"
#include "properties/SEScalarMassPerVolume.h"

SESubstanceCompound::SESubstanceCompound(Logger* logger) : Loggable(logger)
{
  m_Name = "";
}

SESubstanceCompound::~SESubstanceCompound()
{
  Clear();
}

void SESubstanceCompound::Clear()
{
  m_Name = "";
  DELETE_VECTOR(m_Components);
  m_cComponents.clear();
}

void SESubstanceCompound::Load(const cdm::SubstanceData_CompoundData& src, SESubstanceCompound& dst, const SESubstanceManager& subMgr)
{
  SESubstanceCompound::Serialize(src, dst, subMgr);
}
void SESubstanceCompound::Serialize(const cdm::SubstanceData_CompoundData& src, SESubstanceCompound& dst, const SESubstanceManager& subMgr)
{
  dst.Clear();
  dst.m_Name = src.name();

  std::string err;

  SESubstance* substance = nullptr;
  SESubstanceConcentration* cc;
  for (int i = 0; i<src.component_size(); i++)
  {
    const cdm::SubstanceData_ConcentrationData& cData = src.component(i);
    substance = subMgr.GetSubstance(cData.name());
    if (substance == nullptr)
    {
      /// \fatal Could not load find substance compound component for specified substance
      dst.Fatal("Could not load find substance compound component : "+cData.name(), "SESubstanceCompound::Load");
      continue;
    }
    cc = new SESubstanceConcentration(*substance);
    SESubstanceConcentration::Load(cData, *cc);
    dst.m_Components.push_back(cc);
    dst.m_cComponents.push_back(cc);
  }
}

cdm::SubstanceData_CompoundData* SESubstanceCompound::Unload(const SESubstanceCompound& src)
{
  cdm::SubstanceData_CompoundData* dst = new cdm::SubstanceData_CompoundData();
  SESubstanceCompound::Serialize(src,*dst);
  return dst;
}
void SESubstanceCompound::Serialize(const SESubstanceCompound& src, cdm::SubstanceData_CompoundData& dst)
{
  if (src.HasName())
    dst.set_name(src.m_Name);

  for (SESubstanceConcentration* c : src.m_Components)
    dst.mutable_component()->AddAllocated(SESubstanceConcentration::Unload(*c));
}

std::string SESubstanceCompound::GetName() const
{
  return m_Name;
}
void SESubstanceCompound::SetName(const std::string& name)
{
  m_Name = name;
}
bool SESubstanceCompound::HasName() const
{
  return m_Name.empty()?false:true;
}
void SESubstanceCompound::InvalidateName()
{
  m_Name = "";
}

bool SESubstanceCompound::HasComponent() const
{
  return m_Components.size()==0?false:true;
}
bool SESubstanceCompound::HasComponent(const SESubstance& substance) const
{
  for (SESubstanceConcentration* q : m_Components)
  {
    if(&substance==&q->GetSubstance())
      return true;
  }
  return false;
}
const std::vector<SESubstanceConcentration*>& SESubstanceCompound::GetComponents()
{
  return m_Components;
}
const std::vector<const SESubstanceConcentration*>& SESubstanceCompound::GetComponents() const
{
  return m_cComponents;
}
const SESubstanceConcentration& SESubstanceCompound::GetComponent(SESubstance& substance)
{
  for (SESubstanceConcentration* sq : m_Components)
  {
    if(&substance==&sq->GetSubstance())
      return *sq;
  }
  SESubstanceConcentration* sq = new SESubstanceConcentration(substance);
  sq->GetConcentration().SetValue(0,MassPerVolumeUnit::ug_Per_mL);
  m_Components.push_back(sq);
  m_cComponents.push_back(sq);
  return *sq;
}
const SESubstanceConcentration* SESubstanceCompound::GetComponent(SESubstance& substance) const
{
  for (SESubstanceConcentration* sq : m_Components)
  {
    if (&substance == &sq->GetSubstance())
      return sq;
  }
  return nullptr;
}
void SESubstanceCompound::RemoveComponent(const SESubstance& substance)
{
  unsigned int i = 0;
  for (SESubstanceConcentration* sq : m_Components)
  {
    if(&substance==&sq->GetSubstance())
    {
      m_Components.erase(m_Components.begin() + i);
      m_cComponents.erase(m_cComponents.begin() + i);
      delete sq;
    }
    i++;
  }
}

