/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "properties/SEDecimalFormat.h"
PROTO_PUSH
#include "bind/cdm/Scenario.pb.h"
PROTO_POP
class SESubstanceManager;
class CCompoundUnit;
class SEDecimalFormat;
class SEDataRequestManager;

class CDM_DECL SEDataRequest : public SEDecimalFormat
{
  friend class SEDataRequestManager;
protected:
  SEDataRequest(cdm::DataRequestData_eCategory category, const SEDecimalFormat* dfault = nullptr);
public:

  virtual ~SEDataRequest();

  virtual void Clear(); //clear memory
  virtual bool IsValid();

  static void Load(const cdm::DataRequestData& src, SEDataRequest& dst);
  static cdm::DataRequestData* Unload(const SEDataRequest& src);
protected:
  static void Serialize(const cdm::DataRequestData& src, SEDataRequest& dst);
  static void Serialize(const SEDataRequest& src, cdm::DataRequestData& dst);

public:

  virtual size_t HashCode() const;

  // The Request Category
  virtual cdm::DataRequestData_eCategory GetCategory() const;

  // OPTIONAL The Compartment Name holding the property
  virtual std::string GetCompartmentName() const;
  virtual void SetCompartmentName(const std::string& name);
  virtual bool HasCompartmentName() const;
  virtual void InvalidateCompartmentName();

  // OPTIONAL The Substance Name holding the property
  virtual std::string GetSubstanceName() const;
  virtual void SetSubstanceName(const std::string& name);
  virtual bool HasSubstanceName() const;
  virtual void InvalidateSubstanceName();

  // The System Property Name
  virtual std::string GetPropertyName() const;
  virtual void SetPropertyName(const std::string& name);
  virtual bool HasPropertyName() const;
  virtual void InvalidatePropertyName();

  // The Requested Unit String
  virtual std::string GetRequestedUnit() const;
  virtual void SetRequestedUnit(const std::string& unit);
  virtual bool HasRequestedUnit() const;
  virtual void InvalidateRequestedUnit();

  // The Unit that data will be retrieved in
  // If the Requested unit is present, this should be set to that unit
  // I cannot do this automatically, since I don't know what the quantity of the property is, so some other logic needs to complete this logic
  // If the Requested unit is NOT present, this should be set to whatever the unit of the System Property is set as
  virtual const CCompoundUnit* GetUnit() const;
  virtual void SetUnit(const CCompoundUnit& unit);
  virtual bool HasUnit() const;
  virtual void InvalidateUnit();

protected:

  cdm::DataRequestData_eCategory m_Category;
  std::string                    m_CompartmentName;
  std::string                    m_SubstanceName;
  std::string                    m_PropertyName;
  std::string                    m_RequestedUnit;
  const CCompoundUnit*           m_Unit;
};