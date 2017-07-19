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

#include "compartment/substances/SEGasSubstanceQuantity.h"
#include "compartment/fluid/SEGasCompartment.h"
#include "compartment/fluid/SEGasCompartmentLink.h"
#include "substance/SESubstanceTransport.h"
#include "substance/SESubstance.h"

#include "properties/SEScalarPressure.h"
#include "properties/SEScalarVolume.h"
#include "properties/SEScalar0To1.h"

SEGasSubstanceQuantity::SEGasSubstanceQuantity(SESubstance& sub, SEGasCompartment& compartment) : SESubstanceQuantity(sub), m_Compartment(compartment)
{
  m_PartialPressure = nullptr;
  m_Volume = nullptr;
  m_VolumeFraction = nullptr;

  if (m_Substance.GetState() != cdm::SubstanceData_eState_Gas)
    Fatal("The substance for a Gas Substance quantity must be a gas");
}

SEGasSubstanceQuantity::~SEGasSubstanceQuantity()
{
  Clear();
}
void SEGasSubstanceQuantity::Invalidate()
{
  if(m_PartialPressure!=nullptr)
    m_PartialPressure->Invalidate();
  if (m_Volume!=nullptr)
    m_Volume->Invalidate();
  if (m_VolumeFraction!=nullptr)
    m_VolumeFraction->Invalidate();
}

void SEGasSubstanceQuantity::Clear()
{
  SAFE_DELETE(m_PartialPressure);
  SAFE_DELETE(m_Volume);
  SAFE_DELETE(m_VolumeFraction);
  m_Children.clear();
}

void SEGasSubstanceQuantity::Load(const cdm::GasSubstanceQuantityData& src, SEGasSubstanceQuantity& dst)
{
  SEGasSubstanceQuantity::Serialize(src, dst);
}
void SEGasSubstanceQuantity::Serialize(const cdm::GasSubstanceQuantityData& src, SEGasSubstanceQuantity& dst)
{
  SESubstanceQuantity::Serialize(src.substancequantity(), dst);
  if (!dst.m_Compartment.HasChildren())
  {
    if (src.has_partialpressure())
      SEScalarPressure::Load(src.partialpressure(), dst.GetPartialPressure());
    if (src.has_volume())
      SEScalarVolume::Load(src.volume(), dst.GetVolume());
    if (src.has_volumefraction())
      SEScalar0To1::Load(src.volumefraction(), dst.GetVolumeFraction());
  }
}

cdm::GasSubstanceQuantityData* SEGasSubstanceQuantity::Unload(const SEGasSubstanceQuantity& src)
{
  cdm::GasSubstanceQuantityData* dst = new cdm::GasSubstanceQuantityData();
  SEGasSubstanceQuantity::Serialize(src, *dst);
  return dst;
}
void SEGasSubstanceQuantity::Serialize(const SEGasSubstanceQuantity& src, cdm::GasSubstanceQuantityData& dst)
{
  SESubstanceQuantity::Serialize(src, *dst.mutable_substancequantity());
  // Even if you have children, I am unloading everything, this makes the output actually usefull...
  if (src.HasPartialPressure())
    dst.set_allocated_partialpressure(SEScalarPressure::Unload(*src.m_PartialPressure));
  if (src.HasVolume())
    dst.set_allocated_volume(SEScalarVolume::Unload(*src.m_Volume));
  if (src.HasVolumeFraction())
    dst.set_allocated_volumefraction(SEScalar0To1::Unload(*src.m_VolumeFraction));
}

void SEGasSubstanceQuantity::SetToZero()
{
  GetPartialPressure().SetValue(0, PressureUnit::mmHg);
  GetVolume().SetValue(0, VolumeUnit::mL);
  GetVolumeFraction().SetValue(0);
}

const SEScalar* SEGasSubstanceQuantity::GetScalar(const std::string& name)
{
  if (name.compare("PartialPressure") == 0)
    return &GetPartialPressure();
  if (name.compare("Volume") == 0)
    return &GetVolume();
  if (name.compare("VolumeFraction") == 0)
    return &GetVolumeFraction();
  return nullptr;
}

bool SEGasSubstanceQuantity::HasPartialPressure() const
{
  if (!m_Children.empty())
  {
    for (SEGasSubstanceQuantity* child : m_Children)
      if (child->HasPartialPressure())
        return true;
    return false;
  }
  return (m_PartialPressure == nullptr) ? false : m_PartialPressure->IsValid();
}
SEScalarPressure& SEGasSubstanceQuantity::GetPartialPressure()
{
  if (m_PartialPressure == nullptr)
    m_PartialPressure = new SEScalarPressure();
  if (!m_Children.empty())
  {
    m_PartialPressure->SetReadOnly(false);
    if (HasVolumeFraction() && m_Compartment.HasPressure())
      GeneralMath::CalculatePartialPressureInGas(GetVolumeFraction(), m_Compartment.GetPressure(), *m_PartialPressure, m_Logger);
    else
      m_PartialPressure->Invalidate();
    m_PartialPressure->SetReadOnly(true);
  }
  return *m_PartialPressure;
}
double SEGasSubstanceQuantity::GetPartialPressure(const PressureUnit& unit) const
{
  if (!m_Children.empty())
  {
    if (!HasVolumeFraction() || !m_Compartment.HasPressure())
      return SEScalar::dNaN();
    SEScalar0To1 volFrac;
    SEScalarPressure partialPressure;
    volFrac.SetValue(const_cast<const SEGasSubstanceQuantity*>(this)->GetVolumeFraction());
    GeneralMath::CalculatePartialPressureInGas(volFrac, m_Compartment.GetPressure(), partialPressure, m_Logger);
    return partialPressure.GetValue(unit);
  }
  if (m_PartialPressure == nullptr)
    return SEScalar::dNaN();  
  return m_PartialPressure->GetValue(unit);
}

bool SEGasSubstanceQuantity::HasVolume() const
{
  if (!m_Children.empty())
  {
    for (SEGasSubstanceQuantity* child : m_Children)
      if (child->HasVolume())
        return true;
    return false;
  }
  return (m_Volume == nullptr) ? false : m_Volume->IsValid();
}
SEScalarVolume& SEGasSubstanceQuantity::GetVolume()
{
  if (m_Volume == nullptr)
    m_Volume = new SEScalarVolume();
  if (!m_Children.empty())
  {
    m_Volume->SetReadOnly(false);
    m_Volume->Invalidate();
    for (SEGasSubstanceQuantity* child : m_Children)
      if (child->HasVolume())
        m_Volume->Increment(child->GetVolume());
    m_Volume->SetReadOnly(true);
  }
  return *m_Volume;
}
double SEGasSubstanceQuantity::GetVolume(const VolumeUnit& unit) const
{
  if (!m_Children.empty())
  {
    double volume = 0;
    for (SEGasSubstanceQuantity* child : m_Children)
      if (child->HasVolume())
        volume += child->GetVolume(unit);
    return volume;
  }
  if (m_Volume == nullptr)
    return SEScalar::dNaN();
  return m_Volume->GetValue(unit);
}

bool SEGasSubstanceQuantity::HasVolumeFraction() const
{
  if (!m_Children.empty())
  {
    for (SEGasSubstanceQuantity* child : m_Children)
      if (child->HasVolumeFraction())
        return true;
    return false;
  }
  return (m_VolumeFraction == nullptr) ? false : m_VolumeFraction->IsValid();
}
SEScalar0To1& SEGasSubstanceQuantity::GetVolumeFraction()
{
  if (m_VolumeFraction == nullptr)
    m_VolumeFraction = new SEScalar0To1();
  if (!m_Children.empty())
  {
    m_VolumeFraction->SetReadOnly(false);
    if (HasVolume() && m_Compartment.HasVolume())
      m_VolumeFraction->SetValue(GetVolume(VolumeUnit::mL) / m_Compartment.GetVolume(VolumeUnit::mL));
    else
      m_VolumeFraction->Invalidate();
    m_VolumeFraction->SetReadOnly(true);
  }
  return *m_VolumeFraction;
}
double SEGasSubstanceQuantity::GetVolumeFraction() const
{
  if (!m_Children.empty())
  {
    if (!HasVolume() || !m_Compartment.HasVolume())
      return SEScalar::dNaN();
    return GetVolume(VolumeUnit::mL) / m_Compartment.GetVolume(VolumeUnit::mL);
  }
  if (m_VolumeFraction == nullptr)
    return SEScalar::dNaN();
  return m_VolumeFraction->GetValue();
}

void SEGasSubstanceQuantity::AddChild(SEGasSubstanceQuantity& subQ)
{
  if (!Contains(m_Children, subQ))
    m_Children.push_back(&subQ);
}