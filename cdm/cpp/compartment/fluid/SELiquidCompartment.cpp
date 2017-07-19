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
#include "compartment/fluid/SELiquidCompartment.h"
#include "compartment/substances/SELiquidSubstanceQuantity.h"
#include "substance/SESubstanceManager.h"
#include "properties/SEScalar.h"
#include "properties/SEScalar0To1.h"
#include "properties/SEScalarVolumePerTime.h"

SELiquidCompartment::SELiquidCompartment(const std::string& name, Logger* logger) : SEFluidCompartment(name, logger)
{
  m_pH = nullptr;
  m_WaterVolumeFraction = nullptr;
}
SELiquidCompartment::~SELiquidCompartment()
{
  Clear();
}


void SELiquidCompartment::Clear()
{
  SEFluidCompartment::Clear();
  SAFE_DELETE(m_pH);
  SAFE_DELETE(m_WaterVolumeFraction);
  m_Children.clear();
}

void SELiquidCompartment::Load(const cdm::LiquidCompartmentData& src, SELiquidCompartment& dst, SESubstanceManager& subMgr, SECircuitManager* circuits)
{
  SELiquidCompartment::Serialize(src, dst, subMgr, circuits);
}
void SELiquidCompartment::Serialize(const cdm::LiquidCompartmentData& src, SELiquidCompartment& dst, SESubstanceManager& subMgr, SECircuitManager* circuits)
{
  SEFluidCompartment::Serialize(src.fluidcompartment(), dst, circuits);

  if (src.substancequantity_size() > 0)
  {
    for (int i = 0; i<src.substancequantity_size(); i++)
    {
      const cdm::LiquidSubstanceQuantityData& d = src.substancequantity(i);
      SESubstance* sub = subMgr.GetSubstance(d.substancequantity().substance());
      if (sub == nullptr)
      {
        dst.Error("Could not find a substance for " + d.substancequantity().substance());
        continue;
      }
      SELiquidSubstanceQuantity::Load(d, dst.CreateSubstanceQuantity(*sub));
    }
  }
  if (src.has_ph())
    SEScalar::Load(src.ph(), dst.GetPH());
  if (src.has_watervolumefraction())
    SEScalar0To1::Load(src.watervolumefraction(), dst.GetWaterVolumeFraction());
}

cdm::LiquidCompartmentData* SELiquidCompartment::Unload(const SELiquidCompartment& src)
{
  cdm::LiquidCompartmentData* dst = new cdm::LiquidCompartmentData();
  Serialize(src, *dst);
  return dst;
}
void SELiquidCompartment::Serialize(const SELiquidCompartment& src, cdm::LiquidCompartmentData& dst)
{
  SEFluidCompartment::Serialize(src, *dst.mutable_fluidcompartment());
  for (SELiquidSubstanceQuantity* subQ : src.m_SubstanceQuantities)
    dst.mutable_substancequantity()->AddAllocated(SELiquidSubstanceQuantity::Unload(*subQ));

  if (src.HasPH())
    dst.set_allocated_ph(SEScalar::Unload(*src.m_pH));
  if (src.HasWaterVolumeFraction())
    dst.set_allocated_watervolumefraction(SEScalar0To1::Unload(*src.m_WaterVolumeFraction));
}

const SEScalar* SELiquidCompartment::GetScalar(const std::string& name)
{
  const SEScalar* s = SEFluidCompartment::GetScalar(name);
  if (s != nullptr)
    return s;
  if (name.compare("PH") == 0)
    return &GetPH(); 
  if (name.compare("WaterVolumeFraction") == 0)
    return &GetWaterVolumeFraction();
  return nullptr;
}

void SELiquidCompartment::StateChange()
{
  m_Leaves.clear();
  FindLeaves<SELiquidCompartment>(*this, m_Leaves);
  m_Nodes.StateChange();
}

void SELiquidCompartment::Balance(BalanceLiquidBy by)
{
  for (SELiquidSubstanceQuantity* subQ : m_SubstanceQuantities)
  {
    if (by == BalanceLiquidBy::PartialPressure && subQ->GetSubstance().GetState() != cdm::SubstanceData_eState_Gas)
      continue;

    //Partial pressures only make sense for gases in liquids
    if(HasVolume())
      subQ->Balance(by);
  }
}

bool SELiquidCompartment::HasPH() const
{
  return m_pH == nullptr ? false : m_pH->IsValid();
}
SEScalar& SELiquidCompartment::GetPH()
{
  if (m_pH == nullptr)
    m_pH = new SEScalar();
  if (!m_FluidChildren.empty())
  {
    m_pH->SetReadOnly(false);
    m_pH->SetValue(const_cast<const SELiquidCompartment*>(this)->GetPH());
    m_pH->SetReadOnly(true);
  }
  return *m_pH;
}
double SELiquidCompartment::GetPH() const
{
  if (!m_Children.empty())
  {
    double pH = 0;
    for (SELiquidCompartment* child : m_Children)
      pH += pow(10, -child->GetPH().GetValue())*child->GetVolume(VolumeUnit::mL);
    pH = -log10(pH / GetVolume(VolumeUnit::mL));
    return pH;
  }
  if (m_pH == nullptr)
    return SEScalar::dNaN();
  return m_pH->GetValue();
}

bool SELiquidCompartment::HasWaterVolumeFraction() const
{
  return m_WaterVolumeFraction == nullptr ? false : m_WaterVolumeFraction->IsValid();
}
SEScalar0To1& SELiquidCompartment::GetWaterVolumeFraction()
{
  if (m_WaterVolumeFraction == nullptr)
    m_WaterVolumeFraction = new SEScalar0To1();
  if (!m_FluidChildren.empty())
  {
    m_WaterVolumeFraction->SetReadOnly(false);
    m_WaterVolumeFraction->SetValue(const_cast<const SELiquidCompartment*>(this)->GetWaterVolumeFraction());
    m_WaterVolumeFraction->SetReadOnly(true);
  }
  return *m_WaterVolumeFraction;
}
double SELiquidCompartment::GetWaterVolumeFraction() const
{
  if (!m_Children.empty())
  {
    double waterVolume_mL = 0;
    for (SELiquidCompartment* child : m_Children)
      waterVolume_mL += child->GetWaterVolumeFraction().GetValue()*child->GetVolume(VolumeUnit::mL);
    return waterVolume_mL / GetVolume(VolumeUnit::mL);
  }
  if (m_WaterVolumeFraction == nullptr)
    return SEScalar::dNaN();
  return m_WaterVolumeFraction->GetValue();
}

void SELiquidCompartment::AddChild(SELiquidCompartment& child)
{
  if (HasNodeMapping())
  {
    Fatal("You cannont add a child compartment to a compartment mapped to nodes");
    return;
  }
  if (HasChild(child.GetName()))
    return;
  m_FluidChildren.push_back(&child);
  m_Children.push_back(&child);
  for (SELiquidSubstanceQuantity* subQ : m_SubstanceQuantities)
    subQ->AddChild(child.CreateSubstanceQuantity(subQ->GetSubstance()));
}

SELiquidSubstanceQuantity& SELiquidCompartment::CreateSubstanceQuantity(SESubstance& substance)
{
  SELiquidSubstanceQuantity* subQ = GetSubstanceQuantity(substance);
  if (subQ == nullptr)
  {
    subQ = new SELiquidSubstanceQuantity(substance, *this);
    subQ->SetToZero();
    m_SubstanceQuantities.push_back(subQ);
    m_TransportSubstances.push_back(subQ);
  }
  if (!m_FluidChildren.empty())
  {
    for (SELiquidCompartment* child : m_Children)
      subQ->AddChild(child->CreateSubstanceQuantity(substance));
  }
  return *subQ;
}