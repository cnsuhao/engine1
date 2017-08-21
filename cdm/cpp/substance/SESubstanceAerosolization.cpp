/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "substance/SESubstanceAerosolization.h"
#include "properties/SEScalarLength.h"
#include "properties/SEScalarMassPerVolume.h"
#include "properties/SEHistogramFractionVsLength.h"
#include "properties/SEScalar0To1.h"
#include "properties/SEScalarNegative1To1.h"

SESubstanceAerosolization::SESubstanceAerosolization(Logger* logger) : Loggable(logger)
{
  m_BronchioleModifier = nullptr;
  m_InflammationCoefficient = nullptr;
  m_ParticulateSizeDistribution = nullptr;
}

SESubstanceAerosolization::~SESubstanceAerosolization()
{
  Clear();
}

void SESubstanceAerosolization::Clear()
{
  SAFE_DELETE(m_BronchioleModifier);
  SAFE_DELETE(m_InflammationCoefficient);
  SAFE_DELETE(m_ParticulateSizeDistribution);
}

bool SESubstanceAerosolization::IsValid() const
{
  if (!HasBronchioleModifier())
    return false;
  if (!HasInflammationCoefficient())
    return false;
  if (!HasParticulateSizeDistribution())
    return false;
  return true;
}

const SEScalar* SESubstanceAerosolization::GetScalar(const std::string& name)
{
  if (name.compare("BronchioleModifier") == 0)
    return &GetBronchioleModifier();
  if (name.compare("InflammationCoefficient") == 0)
    return &GetInflammationCoefficient();
  return nullptr;
}

void SESubstanceAerosolization::Load(const cdm::SubstanceData_AerosolizationData& src, SESubstanceAerosolization& dst)
{
  SESubstanceAerosolization::Serialize(src, dst);
}
void SESubstanceAerosolization::Serialize(const cdm::SubstanceData_AerosolizationData& src, SESubstanceAerosolization& dst)
{
  dst.Clear();
  if (src.has_bronchiolemodifier())
    SEScalarNegative1To1::Load(src.bronchiolemodifier(), dst.GetBronchioleModifier());
  if (src.has_inflammationcoefficient())
    SEScalar0To1::Load(src.inflammationcoefficient(), dst.GetInflammationCoefficient());
  if (src.has_particulatesizedistribution())
    SEHistogramFractionVsLength::Load(src.particulatesizedistribution(), dst.GetParticulateSizeDistribution());
}

cdm::SubstanceData_AerosolizationData* SESubstanceAerosolization::Unload(const SESubstanceAerosolization& src)
{
  cdm::SubstanceData_AerosolizationData* dst = new cdm::SubstanceData_AerosolizationData();
  SESubstanceAerosolization::Serialize(src, *dst);
  return dst;
}
void SESubstanceAerosolization::Serialize(const SESubstanceAerosolization& src, cdm::SubstanceData_AerosolizationData& dst)
{
  if (src.HasBronchioleModifier())
    dst.set_allocated_bronchiolemodifier(SEScalarNegative1To1::Unload(*src.m_BronchioleModifier));
  if (src.HasInflammationCoefficient())
    dst.set_allocated_inflammationcoefficient(SEScalar0To1::Unload(*src.m_InflammationCoefficient));
  if (src.HasParticulateSizeDistribution())
    dst.set_allocated_particulatesizedistribution(SEHistogramFractionVsLength::Unload(*src.m_ParticulateSizeDistribution));
}


bool SESubstanceAerosolization::HasBronchioleModifier() const
{
  return (m_BronchioleModifier == nullptr) ? false : m_BronchioleModifier->IsValid();
}
SEScalarNegative1To1& SESubstanceAerosolization::GetBronchioleModifier()
{
  if (m_BronchioleModifier == nullptr)
    m_BronchioleModifier = new SEScalarNegative1To1();
  return *m_BronchioleModifier;
}
double SESubstanceAerosolization::GetBronchioleModifier() const
{
  if (m_BronchioleModifier == nullptr)
    return SEScalar::dNaN();
  return m_BronchioleModifier->GetValue();
}

bool SESubstanceAerosolization::HasInflammationCoefficient() const
{
  return (m_InflammationCoefficient == nullptr) ? false : m_InflammationCoefficient->IsValid();
}
SEScalar0To1& SESubstanceAerosolization::GetInflammationCoefficient()
{
  if (m_InflammationCoefficient == nullptr)
    m_InflammationCoefficient = new SEScalar0To1();
  return *m_InflammationCoefficient;
}
double SESubstanceAerosolization::GetInflammationCoefficient() const
{
  if (m_InflammationCoefficient == nullptr)
    return SEScalar::dNaN();
  return m_InflammationCoefficient->GetValue();
}

bool SESubstanceAerosolization::HasParticulateSizeDistribution() const
{
  return (m_ParticulateSizeDistribution == nullptr) ? false : m_ParticulateSizeDistribution->IsValid();
}
SEHistogramFractionVsLength& SESubstanceAerosolization::GetParticulateSizeDistribution()
{
  if (m_ParticulateSizeDistribution == nullptr)
    m_ParticulateSizeDistribution = new SEHistogramFractionVsLength();
  return *m_ParticulateSizeDistribution;
}
const SEHistogramFractionVsLength* SESubstanceAerosolization::GetParticulateSizeDistribution() const
{
  return m_ParticulateSizeDistribution;
}
