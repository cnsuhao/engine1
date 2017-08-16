/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include <iomanip> 
#include "properties/SEDecimalFormat.h"

SEDecimalFormat::SEDecimalFormat(const SEDecimalFormat* dfault)
{
  Clear();
  if (dfault != nullptr) 
    Set(*dfault); 
}

SEDecimalFormat::~SEDecimalFormat()
{
  Clear();
}

void SEDecimalFormat::Clear()
{
  m_Precision = 6;
  m_Notation = cdm::DecimalFormatData_eType_SystemFormatting;
}

void SEDecimalFormat::Set(const SEDecimalFormat& f)
{
  m_Precision = f.m_Precision;
  m_Notation = f.m_Notation;
}

void SEDecimalFormat::Load(const cdm::DecimalFormatData& src, SEDecimalFormat& dst)
{
  SEDecimalFormat::Serialize(src, dst);
}
void SEDecimalFormat::Serialize(const cdm::DecimalFormatData& src, SEDecimalFormat& dst)
{
  dst.Clear();
  dst.SetNotation(src.type());
  dst.SetPrecision(src.precision());
}

cdm::DecimalFormatData* SEDecimalFormat::Unload(const SEDecimalFormat& src)
{
  cdm::DecimalFormatData* dst = new cdm::DecimalFormatData();
  Serialize(src, *dst);
  return dst;
}
void SEDecimalFormat::Serialize(const SEDecimalFormat& src, cdm::DecimalFormatData& dst)
{
  dst.set_type(src.m_Notation);
  dst.set_precision((google::protobuf::uint32)src.m_Precision);
}

void SEDecimalFormat::SetPrecision(std::streamsize p)
{
  m_Precision = p;
}
std::streamsize SEDecimalFormat::GetPrecision()
{
  return m_Precision;
}

void SEDecimalFormat::SetNotation(cdm::DecimalFormatData::eType n)
{
  m_Notation = n;
}
cdm::DecimalFormatData::eType SEDecimalFormat::GetNotation()
{
  return m_Notation;
}

void SEDecimalFormat::SetStream(std::ofstream& s)
{
  switch (m_Notation)
  {
  case cdm::DecimalFormatData_eType_SystemFormatting:
    s << std::fixed << std::setprecision(m_Precision);
    break;
  case cdm::DecimalFormatData_eType_DefaultFloat:
    s << std::defaultfloat << std::setprecision(m_Precision);
    break;
  case cdm::DecimalFormatData_eType_FixedMantissa:
    s << std::fixed << std::setprecision(m_Precision);
    break;
  case cdm::DecimalFormatData_eType_SignificantDigits:
    s << std::scientific << std::setprecision(m_Precision);
  }
}
