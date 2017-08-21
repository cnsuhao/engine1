/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "properties/SEScalar.h"

class CDM_DECL OsmolarityUnit : public CCompoundUnit
{
public:
  OsmolarityUnit(const std::string& u) : CCompoundUnit(u) {}
  virtual ~OsmolarityUnit() {}

  static bool IsValidUnit(const std::string& unit);
  static const OsmolarityUnit& GetCompoundUnit(const std::string& unit);

  static const OsmolarityUnit Osm_Per_L;
  static const OsmolarityUnit mOsm_Per_L;
};

class CDM_DECL SEScalarOsmolarity : public SEScalarQuantity<OsmolarityUnit>
{
public:
  SEScalarOsmolarity() {}
  virtual ~SEScalarOsmolarity() {}

  static void Load(const cdm::ScalarOsmolarityData& src, SEScalarOsmolarity& dst);
  static cdm::ScalarOsmolarityData* Unload(const SEScalarOsmolarity& src);
protected:
  static void Serialize(const cdm::ScalarOsmolarityData& src, SEScalarOsmolarity& dst);
  static void Serialize(const SEScalarOsmolarity& src, cdm::ScalarOsmolarityData& dst);
};
