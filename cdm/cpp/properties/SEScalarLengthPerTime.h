/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "properties/SEScalar.h"

class CDM_DECL LengthPerTimeUnit : public CCompoundUnit
{
public:
  LengthPerTimeUnit(const std::string& u) : CCompoundUnit(u) {}
  virtual ~LengthPerTimeUnit() {}

  static bool IsValidUnit(const std::string& unit);
  static const LengthPerTimeUnit& GetCompoundUnit(const std::string& unit);

  static const LengthPerTimeUnit m_Per_s;
  static const LengthPerTimeUnit cm_Per_s;
  static const LengthPerTimeUnit m_Per_min;
  static const LengthPerTimeUnit cm_Per_min;
  static const LengthPerTimeUnit ft_Per_s;
  static const LengthPerTimeUnit ft_Per_min;
};

class CDM_DECL SEScalarLengthPerTime : public SEScalarQuantity<LengthPerTimeUnit>
{
public:
  SEScalarLengthPerTime() {}
  virtual ~SEScalarLengthPerTime() {}

  static void Load(const cdm::ScalarLengthPerTimeData& src, SEScalarLengthPerTime& dst);
  static cdm::ScalarLengthPerTimeData* Unload(const SEScalarLengthPerTime& src);
protected:
  static void Serialize(const cdm::ScalarLengthPerTimeData& src, SEScalarLengthPerTime& dst);
  static void Serialize(const SEScalarLengthPerTime& src, cdm::ScalarLengthPerTimeData& dst);
};
