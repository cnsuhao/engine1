/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "patient/actions/SEForcedInhale.h"
#include "properties/SEScalar0To1.h"
#include "properties/SEScalarTime.h"

SEForcedInhale::SEForcedInhale() : SEConsciousRespirationCommand()
{
  m_InspiratoryCapacityFraction = nullptr;
  m_Period = nullptr;
}

SEForcedInhale::~SEForcedInhale()
{
  Clear();
}

void SEForcedInhale::Clear()
{
  SEConsciousRespirationCommand::Clear();
  SAFE_DELETE(m_InspiratoryCapacityFraction);
  SAFE_DELETE(m_Period);
}

bool SEForcedInhale::IsValid() const
{
  return SEConsciousRespirationCommand::IsValid() && HasInspiratoryCapacityFraction() && HasPeriod();
}

bool SEForcedInhale::IsActive() const
{
  return SEConsciousRespirationCommand::IsActive();
}

void SEForcedInhale::Load(const cdm::ConsciousRespirationData_ForcedInhaleData& src, SEForcedInhale& dst)
{
  SEForcedInhale::Serialize(src, dst);
}
void SEForcedInhale::Serialize(const cdm::ConsciousRespirationData_ForcedInhaleData& src, SEForcedInhale& dst)
{
  dst.Clear();
  if (src.has_inspiratorycapacityfraction())
    SEScalar0To1::Load(src.inspiratorycapacityfraction(), dst.GetInspiratoryCapacityFraction());
  if (src.has_period())
    SEScalarTime::Load(src.period(), dst.GetPeriod());
}

cdm::ConsciousRespirationData_ForcedInhaleData* SEForcedInhale::Unload(const SEForcedInhale& src)
{
  cdm::ConsciousRespirationData_ForcedInhaleData* dst = new cdm::ConsciousRespirationData_ForcedInhaleData();
  SEForcedInhale::Serialize(src, *dst);
  return dst;
}
void SEForcedInhale::Serialize(const SEForcedInhale& src, cdm::ConsciousRespirationData_ForcedInhaleData& dst)
{
  if (src.HasInspiratoryCapacityFraction())
    dst.set_allocated_inspiratorycapacityfraction(SEScalar0To1::Unload(*src.m_InspiratoryCapacityFraction));
  if (src.HasPeriod())
    dst.set_allocated_period(SEScalarTime::Unload(*src.m_Period));
}

bool SEForcedInhale::HasInspiratoryCapacityFraction() const
{
  return m_InspiratoryCapacityFraction == nullptr ? false : m_InspiratoryCapacityFraction->IsValid();
}
SEScalar0To1& SEForcedInhale::GetInspiratoryCapacityFraction()
{
  if (m_InspiratoryCapacityFraction == nullptr)
    m_InspiratoryCapacityFraction = new SEScalar0To1();
  return *m_InspiratoryCapacityFraction;
}

bool SEForcedInhale::HasPeriod() const
{
  return m_Period == nullptr ? false : m_Period->IsValid();
}
SEScalarTime& SEForcedInhale::GetPeriod()
{
  if (m_Period == nullptr)
    m_Period = new SEScalarTime();
  return *m_Period;
}

void SEForcedInhale::ToString(std::ostream &str) const
{
  str << "Forced Inhale";
  if (HasComment())
    str << "\n\tComment: " << m_Comment;
  str << "\n\tInspiratoryCapacityFraction: "; HasInspiratoryCapacityFraction() ? str << *m_InspiratoryCapacityFraction : str << "NaN";
  str << "\n\tPeriod: "; HasPeriod() ? str << *m_Period : str << "NaN";
  str << std::flush;
}