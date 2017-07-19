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
#include "compartment/fluid/SEGasCompartment.h"
#include "substance/SESubstanceManager.h"
#include "properties/SEScalarVolume.h"
#include "properties/SEScalar0To1.h"

SEGasCompartment::SEGasCompartment(const std::string& name, Logger* logger) : SEFluidCompartment(name, logger)
{

}
SEGasCompartment::~SEGasCompartment()
{
  
}

void SEGasCompartment::Load(const cdm::GasCompartmentData& src, SEGasCompartment& dst, SESubstanceManager& subMgr, SECircuitManager* circuits)
{
  SEGasCompartment::Serialize(src, dst, subMgr, circuits);
}
void SEGasCompartment::Serialize(const cdm::GasCompartmentData& src, SEGasCompartment& dst, SESubstanceManager& subMgr, SECircuitManager* circuits)
{
  SEFluidCompartment::Serialize(src.fluidcompartment(), dst, circuits);

  if (src.substancequantity_size() > 0)
  {
    for (int i=0; i<src.substancequantity_size(); i++)
    {
      const cdm::GasSubstanceQuantityData& d = src.substancequantity(i);
      SESubstance* sub = subMgr.GetSubstance(d.substancequantity().substance());
      if (sub == nullptr)
      {
        dst.Error("Could not find a substance for " + d.substancequantity().substance());
        continue;
      }
      SEGasSubstanceQuantity::Load(d,dst.CreateSubstanceQuantity(*sub));
    }
  }
}

cdm::GasCompartmentData* SEGasCompartment::Unload(const SEGasCompartment& src)
{
  cdm::GasCompartmentData* dst = new cdm::GasCompartmentData();
  Serialize(src,*dst);
  return dst;
}
void SEGasCompartment::Serialize(const SEGasCompartment& src, cdm::GasCompartmentData& dst)
{
  SEFluidCompartment::Serialize(src,*dst.mutable_fluidcompartment());
  for (SEGasSubstanceQuantity* subQ : src.m_SubstanceQuantities)
    dst.mutable_substancequantity()->AddAllocated(SEGasSubstanceQuantity::Unload(*subQ));
}

void SEGasCompartment::StateChange()
{
  m_Leaves.clear();
  FindLeaves<SEGasCompartment>(*this, m_Leaves);
  m_Nodes.StateChange();
}

void SEGasCompartment::Balance(BalanceGasBy by)
{
  if (!m_FluidChildren.empty())
    Fatal("You cannot balance a quantity with children", "SEGasCompartment::Balance");
  switch (by)
  {
    case BalanceGasBy::Volume:
    {
    //Note: We won't modify the compartment volume, just the fractions
    double totalVolume_mL = 0;
      for (SEGasSubstanceQuantity* subQ : GetSubstanceQuantities())
      {
        if (subQ->HasVolume())
          totalVolume_mL += subQ->GetVolume(VolumeUnit::mL);
      }
      for (SEGasSubstanceQuantity* subQ : GetSubstanceQuantities())
      {
        if (!subQ->HasVolume())
        {
          subQ->Invalidate();
          continue;
        }
        else
        {
          subQ->GetVolumeFraction().SetValue(subQ->GetVolume(VolumeUnit::mL) / totalVolume_mL);
      subQ->GetVolume().SetValue(subQ->GetVolumeFraction().GetValue() * GetVolume(VolumeUnit::mL), VolumeUnit::mL);
          if(HasPressure())
            GeneralMath::CalculatePartialPressureInGas(subQ->GetVolumeFraction(), GetPressure(), subQ->GetPartialPressure(), m_Logger);
        }
      }
      break;
    }
    case BalanceGasBy::VolumeFraction:
    {
      if (!HasVolume())
      {
        for (SEGasSubstanceQuantity* subQ : GetSubstanceQuantities())
        {
          subQ->Invalidate();
          if (HasPressure())
            GeneralMath::CalculatePartialPressureInGas(subQ->GetVolumeFraction(), GetPressure(), subQ->GetPartialPressure(), m_Logger);
        }
        return;
      }
      if(GetVolume().IsInfinity())
      {
      for (SEGasSubstanceQuantity* subQ : GetSubstanceQuantities())
      {
        subQ->GetVolume().SetValue(std::numeric_limits<double>::infinity(), VolumeUnit::mL);
        if (HasPressure())
          GeneralMath::CalculatePartialPressureInGas(subQ->GetVolumeFraction(), GetPressure(), subQ->GetPartialPressure(), m_Logger);
      }
    }
      else
      {
        double totalFraction = 0;
        double totalVolume_mL = GetVolume(VolumeUnit::mL);
        for (SEGasSubstanceQuantity* subQ : GetSubstanceQuantities())
        {
          if (!subQ->HasVolumeFraction())
            subQ->Invalidate();
          else
          {
            totalFraction += subQ->GetVolumeFraction().GetValue();
            subQ->GetVolume().SetValue(subQ->GetVolumeFraction().GetValue() * totalVolume_mL, VolumeUnit::mL);
          }
          if (HasPressure())
            GeneralMath::CalculatePartialPressureInGas(subQ->GetVolumeFraction(), GetPressure(), subQ->GetPartialPressure(), m_Logger);
        }
        if (!SEScalar::IsZero(1-totalFraction, ZERO_APPROX))
          Fatal(GetName() + " Compartment's volume fractions do not sum up to 1");
      }
      break;
    }
  }
}

void SEGasCompartment::AddChild(SEGasCompartment& child)
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
  for (SEGasSubstanceQuantity* subQ : m_SubstanceQuantities)
    subQ->AddChild(child.CreateSubstanceQuantity(subQ->GetSubstance()));
}

SEGasSubstanceQuantity& SEGasCompartment::CreateSubstanceQuantity(SESubstance& substance)
{
  SEGasSubstanceQuantity* subQ = GetSubstanceQuantity(substance);
  if (subQ == nullptr)
  {
    subQ = new SEGasSubstanceQuantity(substance, *this);
    subQ->SetToZero();
    m_SubstanceQuantities.push_back(subQ);
    m_TransportSubstances.push_back(subQ);
  }
  if (!m_FluidChildren.empty())
  {
    for (SEGasCompartment* child : m_Children)
      subQ->AddChild(child->CreateSubstanceQuantity(substance));
  }
  return *subQ;
}
