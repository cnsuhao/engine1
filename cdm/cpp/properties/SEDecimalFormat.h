/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "bind/cdm/Properties.pb.h"

class CDM_DECL SEDecimalFormat
{
public:
  SEDecimalFormat(const SEDecimalFormat* dfault = nullptr);
  virtual ~SEDecimalFormat();

  virtual void Clear();
  virtual void Set(const SEDecimalFormat& f);

  static void Load(const cdm::DecimalFormatData& src, SEDecimalFormat& dst);
  static cdm::DecimalFormatData* Unload(const SEDecimalFormat& src);
protected:
  static void Serialize(const cdm::DecimalFormatData& src, SEDecimalFormat& dst);
  static void Serialize(const SEDecimalFormat& src, cdm::DecimalFormatData& dst);
public:

  void SetPrecision(std::streamsize p);
  std::streamsize GetPrecision();

  void SetNotation(cdm::DecimalFormatData::eType n);
  cdm::DecimalFormatData::eType GetNotation();

  void SetStream(std::ofstream& s);

protected:
  std::streamsize               m_Precision;
  cdm::DecimalFormatData::eType m_Notation;

};