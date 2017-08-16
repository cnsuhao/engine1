/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "patient/actions/SEUseInhaler.h"
#include "substance/SESubstance.h"
#include "properties/SEScalarMass.h"
#include "properties/SEScalarVolume.h"

SEUseInhaler::SEUseInhaler() : SEConsciousRespirationCommand()
{
  
}

SEUseInhaler::~SEUseInhaler()
{
  Clear();
}

void SEUseInhaler::Clear()
{
  SEConsciousRespirationCommand::Clear();
}

bool SEUseInhaler::IsValid() const
{
  return SEConsciousRespirationCommand::IsValid();
}

bool SEUseInhaler::IsActive() const
{
  return SEConsciousRespirationCommand::IsActive();
}

void SEUseInhaler::Load(const cdm::ConsciousRespirationData_UseInhalerData& src, SEUseInhaler& dst)
{
  SEUseInhaler::Serialize(src, dst);
}
void SEUseInhaler::Serialize(const cdm::ConsciousRespirationData_UseInhalerData& src, SEUseInhaler& dst)
{
  dst.Clear();
}

cdm::ConsciousRespirationData_UseInhalerData* SEUseInhaler::Unload(const SEUseInhaler& src)
{
  cdm::ConsciousRespirationData_UseInhalerData* dst = new cdm::ConsciousRespirationData_UseInhalerData();
  SEUseInhaler::Serialize(src, *dst);
  return dst;
}
void SEUseInhaler::Serialize(const SEUseInhaler& src, cdm::ConsciousRespirationData_UseInhalerData& dst)
{

}

void SEUseInhaler::ToString(std::ostream &str) const
{
  str << "Use Inhaler";
  if (HasComment())
    str << "\n\tComment: " << m_Comment;  
  str << std::flush;
}