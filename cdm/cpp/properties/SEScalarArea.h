/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "properties/SEScalar.h"

class CDM_DECL AreaUnit : public CCompoundUnit
{
public:
  AreaUnit(const std::string& u) : CCompoundUnit(u) {}
  virtual ~AreaUnit() {}

  static bool IsValidUnit(const std::string& unit);
  static const AreaUnit& GetCompoundUnit(const std::string& unit);

  static const AreaUnit cm2;
  static const AreaUnit m2;
};

class CDM_DECL SEScalarArea : public SEScalarQuantity<AreaUnit>
{
public:
  SEScalarArea() {}
  virtual ~SEScalarArea() {}

  static void Load(const cdm::ScalarAreaData& src, SEScalarArea& dst);
  static cdm::ScalarAreaData* Unload(const SEScalarArea& src);
protected:
  static void Serialize(const cdm::ScalarAreaData& src, SEScalarArea& dst);
  static void Serialize(const SEScalarArea& src, cdm::ScalarAreaData& dst);
};