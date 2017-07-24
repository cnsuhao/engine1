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
#include "substance/SESubstancePharmacokinetics.h"
#include "properties/SEScalar0To1.h"

SESubstancePharmacokinetics::SESubstancePharmacokinetics(Logger* logger) : Loggable(logger)
{
  m_Physicochemicals = nullptr;
}

SESubstancePharmacokinetics::~SESubstancePharmacokinetics()
{
  Clear();
}

void SESubstancePharmacokinetics::Clear()
{
  SAFE_DELETE(m_Physicochemicals);
  DELETE_MAP_SECOND(m_TissueKinetics);
  m_TissueKinetics.clear();
}

bool SESubstancePharmacokinetics::IsValid() const
{
  if (HasPhysicochemicals())
    return true;
  if (HasTissueKinetics())
    return true;
  return false;
}

const SEScalar* SESubstancePharmacokinetics::GetScalar(const std::string& name)
{
  if (HasPhysicochemicals())
    return GetPhysicochemicals().GetScalar(name);  
  // I did not support for getting a specific tissue kinetic scalar due to lack of coffee
  return nullptr;
}

void SESubstancePharmacokinetics::Load(const cdm::SubstanceData_PharmacokineticsData& src, SESubstancePharmacokinetics& dst)
{
  SESubstancePharmacokinetics::Serialize(src, dst);
}
void SESubstancePharmacokinetics::Serialize(const cdm::SubstanceData_PharmacokineticsData& src, SESubstancePharmacokinetics& dst)
{
  dst.Clear();

  if (src.has_physicochemicals())
    SESubstancePhysicochemicals::Load(src.physicochemicals(), dst.GetPhysicochemicals());

  SESubstanceTissuePharmacokinetics* fx;
  for (int i = 0; i < src.tissuekinetics_size(); i++)
  {
    const cdm::SubstanceData_TissuePharmacokineticsData& fxData = src.tissuekinetics(i);
    fx = new SESubstanceTissuePharmacokinetics(fxData.name(), dst.GetLogger());
    SESubstanceTissuePharmacokinetics::Load(fxData, *fx);
    dst.m_TissueKinetics[fx->GetName()] = (fx);
  }
}

cdm::SubstanceData_PharmacokineticsData* SESubstancePharmacokinetics::Unload(const SESubstancePharmacokinetics& src)
{
  if (!src.IsValid())
    return nullptr;
  cdm::SubstanceData_PharmacokineticsData* dst = new cdm::SubstanceData_PharmacokineticsData();
  SESubstancePharmacokinetics::Serialize(src,*dst);
  return dst;
}
void SESubstancePharmacokinetics::Serialize(const SESubstancePharmacokinetics& src, cdm::SubstanceData_PharmacokineticsData& dst)
{
  if (src.HasPhysicochemicals())
    dst.set_allocated_physicochemicals(SESubstancePhysicochemicals::Unload(*src.m_Physicochemicals));

  for (auto itr : src.m_TissueKinetics)
    dst.mutable_tissuekinetics()->AddAllocated(SESubstanceTissuePharmacokinetics::Unload(*itr.second));
}

bool SESubstancePharmacokinetics::HasPhysicochemicals() const
{
  return m_Physicochemicals == nullptr ? false : m_Physicochemicals->IsValid();
}
SESubstancePhysicochemicals& SESubstancePharmacokinetics::GetPhysicochemicals()
{
  if (m_Physicochemicals == nullptr)
    m_Physicochemicals = new SESubstancePhysicochemicals(GetLogger());
  return *m_Physicochemicals;
}
const SESubstancePhysicochemicals* SESubstancePharmacokinetics::GetPhysicochemicals() const
{
  return m_Physicochemicals;
}


bool SESubstancePharmacokinetics::HasTissueKinetics() const
{
  return m_TissueKinetics.size() > 0;
}
bool SESubstancePharmacokinetics::HasTissueKinetics(const std::string& name) const
{
  auto idx = m_TissueKinetics.find(name);
  if (idx != m_TissueKinetics.end())
    return true;
  return false;
}
SESubstanceTissuePharmacokinetics& SESubstancePharmacokinetics::GetTissueKinetics(const std::string& name)
{
  auto idx = m_TissueKinetics.find(name);
  if (idx != m_TissueKinetics.end())
    return *(idx->second);
  SESubstanceTissuePharmacokinetics* fx = new SESubstanceTissuePharmacokinetics(name, GetLogger());
  m_TissueKinetics[name] = fx;
  return *fx;
}
const SESubstanceTissuePharmacokinetics* SESubstancePharmacokinetics::GetTissueKinetics(const std::string& name) const
{
  auto idx = m_TissueKinetics.find(name);
  if (idx != m_TissueKinetics.end())
    return (idx->second);
  return nullptr;
}
void SESubstancePharmacokinetics::RemoveTissueKinetics(const std::string& name)
{
  m_TissueKinetics.erase(name);
}
