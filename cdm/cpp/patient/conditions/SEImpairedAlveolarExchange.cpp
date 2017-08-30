/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
#include "stdafx.h"
#include "patient/conditions/SEImpairedAlveolarExchange.h"
#include "properties/SEScalarArea.h"
#include "properties/SEScalar0To1.h"
PROTO_PUSH
#include "bind/cdm/PatientConditions.pb.h"
PROTO_POP

SEImpairedAlveolarExchange::SEImpairedAlveolarExchange() : SEPatientCondition()
{
  m_ImpairedSurfaceArea = nullptr;
  m_ImpairedFraction = nullptr;
}

SEImpairedAlveolarExchange::~SEImpairedAlveolarExchange()
{
  Clear();
}

void SEImpairedAlveolarExchange::Clear()
{
  SAFE_DELETE(m_ImpairedSurfaceArea);
  SAFE_DELETE(m_ImpairedFraction);
}

bool SEImpairedAlveolarExchange::IsValid() const
{
  return HasImpairedFraction() || HasImpairedSurfaceArea();
}

void SEImpairedAlveolarExchange::Load(const cdm::ImpairedAlveolarExchangeData& src, SEImpairedAlveolarExchange& dst)
{
  SEImpairedAlveolarExchange::Serialize(src, dst);
}
void SEImpairedAlveolarExchange::Serialize(const cdm::ImpairedAlveolarExchangeData& src, SEImpairedAlveolarExchange& dst)
{
  SEPatientCondition::Serialize(src.patientcondition(), dst);
  if (src.has_impairedfraction())
    SEScalar0To1::Load(src.impairedfraction(), dst.GetImpairedFraction());
  if (src.has_impairedsurfacearea())
    SEScalarArea::Load(src.impairedsurfacearea(), dst.GetImpairedSurfaceArea());
}

cdm::ImpairedAlveolarExchangeData* SEImpairedAlveolarExchange::Unload(const SEImpairedAlveolarExchange& src)
{
  cdm::ImpairedAlveolarExchangeData* dst = new cdm::ImpairedAlveolarExchangeData();
  SEImpairedAlveolarExchange::Serialize(src, *dst);
  return dst;
}
void SEImpairedAlveolarExchange::Serialize(const SEImpairedAlveolarExchange& src, cdm::ImpairedAlveolarExchangeData& dst)
{
  SEPatientCondition::Serialize(src, *dst.mutable_patientcondition());
  if (src.HasImpairedFraction())
    dst.set_allocated_impairedfraction(SEScalar0To1::Unload(*src.m_ImpairedFraction));
  if (src.HasImpairedSurfaceArea())
    dst.set_allocated_impairedsurfacearea(SEScalarArea::Unload(*src.m_ImpairedSurfaceArea));
}

bool SEImpairedAlveolarExchange::HasImpairedSurfaceArea() const
{
  return m_ImpairedSurfaceArea == nullptr ? false : m_ImpairedSurfaceArea->IsValid();
}
SEScalarArea& SEImpairedAlveolarExchange::GetImpairedSurfaceArea()
{
  if (m_ImpairedSurfaceArea == nullptr)
    m_ImpairedSurfaceArea = new SEScalarArea();
  return *m_ImpairedSurfaceArea;
}
double SEImpairedAlveolarExchange::GetImpairedSurfaceArea(const AreaUnit& unit) const
{
  if (m_ImpairedSurfaceArea == nullptr)
    return SEScalar::dNaN();
  return m_ImpairedSurfaceArea->GetValue(unit);
}

bool SEImpairedAlveolarExchange::HasImpairedFraction() const
{
  return m_ImpairedFraction == nullptr ? false : m_ImpairedFraction->IsValid();
}
SEScalar0To1& SEImpairedAlveolarExchange::GetImpairedFraction()
{
  if (m_ImpairedFraction == nullptr)
    m_ImpairedFraction = new SEScalar0To1();
  return *m_ImpairedFraction;
}
double SEImpairedAlveolarExchange::GetImpairedFraction() const
{
  if (m_ImpairedFraction == nullptr)
    return SEScalar::dNaN();
  return m_ImpairedFraction->GetValue();
}


void SEImpairedAlveolarExchange::ToString(std::ostream &str) const
{
  str << "Impaired Alveoli Exchange :";  
  str << "\n\tImpairedSurfaceArea :";HasImpairedSurfaceArea() ? str << *m_ImpairedSurfaceArea : str << "Not Provided";
  str << "\n\tImpairedFraction :"; HasImpairedFraction() ? str << *m_ImpairedFraction : str << "Not Provided";

  str << std::flush;
}