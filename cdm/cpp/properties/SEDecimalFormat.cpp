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
#include <iomanip> 
#include "properties/SEDecimalFormat.h"

SEDecimalFormat::SEDecimalFormat(const SEDecimalFormat* dfault)
{
  Reset();
  if (dfault != nullptr) 
    Set(*dfault); 
}

SEDecimalFormat::~SEDecimalFormat()
{
  Reset();
}

void SEDecimalFormat::Reset()
{
  m_Precision = 6;
  m_Notation = cdm::DecimalFormatData_eType_FixedMantissa;
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
  dst.Reset();
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
  dst.set_precision(src.m_Precision);
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
  case cdm::DecimalFormatData_eType_FixedMantissa:
    s << std::fixed << std::setprecision(m_Precision);
    break;
  case cdm::DecimalFormatData_eType_SignificantDigits:
    s << std::scientific << std::setprecision(m_Precision);
  }
}
