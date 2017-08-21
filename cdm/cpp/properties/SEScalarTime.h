/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "properties/SEScalar.h"

class CDM_DECL TimeUnit : public CCompoundUnit
{
public:
  TimeUnit(const std::string& u) : CCompoundUnit(u) {}
  virtual ~TimeUnit() {}

  static bool IsValidUnit(const std::string& unit);
  static const TimeUnit& GetCompoundUnit(const std::string& unit);

  static const TimeUnit s;
  static const TimeUnit min;
  static const TimeUnit hr;
  static const TimeUnit day;
  static const TimeUnit yr;
};

class CDM_DECL SEScalarTime : public SEScalarQuantity<TimeUnit>
{
public:
  SEScalarTime() {}
  virtual ~SEScalarTime() {}

  static void Load(const cdm::ScalarTimeData& src, SEScalarTime& dst);
  static cdm::ScalarTimeData* Unload(const SEScalarTime& src);
protected:
  static void Serialize(const cdm::ScalarTimeData& src, SEScalarTime& dst);
  static void Serialize(const SEScalarTime& src, cdm::ScalarTimeData& dst);
};
