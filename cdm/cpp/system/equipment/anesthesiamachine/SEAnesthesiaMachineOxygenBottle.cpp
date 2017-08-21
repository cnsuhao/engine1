/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "system/equipment/anesthesiamachine/SEAnesthesiaMachineOxygenBottle.h"
#include "substance/SESubstanceManager.h"
#include "properties/SEScalarVolume.h"

SEAnesthesiaMachineOxygenBottle::SEAnesthesiaMachineOxygenBottle(Logger* logger) : Loggable(logger)
{
  m_Volume = nullptr;
}

SEAnesthesiaMachineOxygenBottle::~SEAnesthesiaMachineOxygenBottle()
{
  Clear();
}

void SEAnesthesiaMachineOxygenBottle::Clear()
{
  SAFE_DELETE(m_Volume);
}

void SEAnesthesiaMachineOxygenBottle::Load(const cdm::AnesthesiaMachineData_OxygenBottleData& src, SEAnesthesiaMachineOxygenBottle& dst)
{
  SEAnesthesiaMachineOxygenBottle::Serialize(src, dst);
}
void SEAnesthesiaMachineOxygenBottle::Serialize(const cdm::AnesthesiaMachineData_OxygenBottleData& src, SEAnesthesiaMachineOxygenBottle& dst)
{
  dst.Clear();
  if (src.has_volume())
    SEScalarVolume::Load(src.volume(), dst.GetVolume());
}

cdm::AnesthesiaMachineData_OxygenBottleData* SEAnesthesiaMachineOxygenBottle::Unload(const SEAnesthesiaMachineOxygenBottle& src)
{
  cdm::AnesthesiaMachineData_OxygenBottleData* dst = new cdm::AnesthesiaMachineData_OxygenBottleData();
  SEAnesthesiaMachineOxygenBottle::Serialize(src, *dst);
  return dst;
}
void SEAnesthesiaMachineOxygenBottle::Serialize(const SEAnesthesiaMachineOxygenBottle& src, cdm::AnesthesiaMachineData_OxygenBottleData& dst)
{
  if (src.HasVolume())
    dst.set_allocated_volume(SEScalarVolume::Unload(*src.m_Volume));
}

void SEAnesthesiaMachineOxygenBottle::Merge(const SEAnesthesiaMachineOxygenBottle& from)
{
  COPY_PROPERTY(Volume);
}

const SEScalar* SEAnesthesiaMachineOxygenBottle::GetScalar(const std::string& name)
{
  if (name == "Volume")
    return &GetVolume();
  return nullptr;
}

bool SEAnesthesiaMachineOxygenBottle::HasVolume() const
{
  return m_Volume==nullptr?false:m_Volume->IsValid();
}

SEScalarVolume& SEAnesthesiaMachineOxygenBottle::GetVolume()
{
  if(m_Volume==nullptr)
    m_Volume = new SEScalarVolume();
  return *m_Volume;
}
double SEAnesthesiaMachineOxygenBottle::GetVolume(const VolumeUnit& unit) const
{
  if (m_Volume == nullptr)
    return SEScalar::dNaN();
  return m_Volume->GetValue(unit);
}

void SEAnesthesiaMachineOxygenBottle::ToString(std::ostream &str)
{
  str<<" Anesthesia Machine Oxygen Bottle, ";
  if(HasVolume())
    str<<"\rVolume : "<<GetVolume();
  else
    str<<"\rVolume : NaN"<<GetVolume();
  str<<std::flush;
}
