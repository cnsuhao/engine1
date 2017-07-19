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
#include "compartment/thermal/SEThermalCompartmentLink.h"
#include "circuit/SECircuitManager.h"

#include "properties/SEScalarPower.h"

SEThermalCompartmentLink::SEThermalCompartmentLink(SEThermalCompartment& src, SEThermalCompartment & tgt, const std::string& name) : SECompartmentLink(name,src.GetLogger()), m_SourceCmpt(src), m_TargetCmpt(tgt)
{
  m_HeatTransferRate = nullptr;
  m_Path = nullptr;
}
SEThermalCompartmentLink::~SEThermalCompartmentLink()
{

}

void SEThermalCompartmentLink::Load(const cdm::ThermalCompartmentLinkData& src, SEThermalCompartmentLink& dst, SECircuitManager* circuits)
{
  SEThermalCompartmentLink::Serialize(src, dst, circuits);
}
void SEThermalCompartmentLink::Serialize(const cdm::ThermalCompartmentLinkData& src, SEThermalCompartmentLink& dst, SECircuitManager* circuits)
{
  SECompartmentLink::Serialize(src.link(), dst);

  if (!src.link().path().empty())
  {
    if (circuits == nullptr)
    {
      dst.Error("Link is mapped to circuit path, " + src.link().path() + ", but no circuit manager was provided, cannot load");
      return;
    }
    SEThermalCircuitPath* path = circuits->GetThermalPath(src.link().path());
    if (path == nullptr)
    {
      dst.Error("Link is mapped to circuit path, " + src.link().path() + ", but provided circuit manager did not have that path");
      return;
    }
    dst.MapPath(*path);
  }
  else
  {
    if (src.has_heattransferrate())
      SEScalarPower::Load(src.heattransferrate(), dst.GetHeatTransferRate());
  }  
}

cdm::ThermalCompartmentLinkData* SEThermalCompartmentLink::Unload(const SEThermalCompartmentLink& src)
{
  cdm::ThermalCompartmentLinkData* dst = new cdm::ThermalCompartmentLinkData();
  Serialize(src,*dst);
  return dst;
}
void SEThermalCompartmentLink::Serialize(const SEThermalCompartmentLink& src, cdm::ThermalCompartmentLinkData& dst)
{
  SECompartmentLink::Serialize(src,*dst.mutable_link());
  dst.mutable_link()->set_sourcecompartment(src.m_SourceCmpt.GetName());
  dst.mutable_link()->set_targetcompartment(src.m_TargetCmpt.GetName());
  if (src.m_Path != nullptr)
    dst.mutable_link()->set_path(src.m_Path->GetName());
  // Even if you have a path, I am unloading everything, this makes the xml actually usefull...
  if (src.HasHeatTransferRate())
    dst.set_allocated_heattransferrate(SEScalarPower::Unload(*src.m_HeatTransferRate));
}

void SEThermalCompartmentLink::Clear()
{
  m_Path = nullptr;
  SAFE_DELETE(m_HeatTransferRate);
}

const SEScalar* SEThermalCompartmentLink::GetScalar(const std::string& name)
{
  if (name.compare("HeatTransferRate") == 0)
    return &GetHeatTransferRate();
  return nullptr;
}

bool SEThermalCompartmentLink::HasHeatTransferRate() const
{
  if (m_Path != nullptr)
    return m_Path->HasNextHeatTransferRate();
  return m_HeatTransferRate == nullptr ? false : m_HeatTransferRate->IsValid();
}
SEScalarPower& SEThermalCompartmentLink::GetHeatTransferRate()
{
  if (m_Path != nullptr)
    return m_Path->GetNextHeatTransferRate();
  if (m_HeatTransferRate == nullptr)
    m_HeatTransferRate = new SEScalarPower();
  return *m_HeatTransferRate;
}
double SEThermalCompartmentLink::GetHeatTransferRate(const PowerUnit& unit) const
{
  if (m_Path != nullptr)
    return m_Path->GetNextHeatTransferRate(unit);
  if (m_HeatTransferRate == nullptr)
    return SEScalar::dNaN();
  return m_HeatTransferRate->GetValue(unit);
}