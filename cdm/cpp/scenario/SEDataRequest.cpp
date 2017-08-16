/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "scenario/SEDataRequest.h"
#include "utils/unitconversion/UCCommon.h"

SEDataRequest::SEDataRequest(cdm::DataRequestData_eCategory category, const SEDecimalFormat* dfault) : SEDecimalFormat(dfault)
{
  m_Category = category;
  m_CompartmentName = "";
  m_SubstanceName = "";
  m_PropertyName="";
  m_RequestedUnit="";
  m_Unit=nullptr;
}

SEDataRequest::~SEDataRequest()
{
  Clear();
}

void SEDataRequest::Clear()
{
  m_CompartmentName = "";
  m_SubstanceName = "";
  m_PropertyName="";
  m_RequestedUnit="";
  m_Unit = nullptr;
}

bool SEDataRequest::IsValid()
{// TODO this could be a little stronger, and maybe logged, maybe pass in a logger?
 // Or this can go in the SEEngineTracker that is processing data requests
  // We also need to check that the substance name (and possibly Compartment Name) are valid
  if (m_PropertyName.empty())
    return false;
  switch (m_Category)
  {
    case cdm::DataRequestData_eCategory_Patient:
    {
      if (HasCompartmentName() || HasSubstanceName())
        std::cout << "Ignoring compartment and substance name on patient data request" << std::endl;
      return true;
    }
    case cdm::DataRequestData_eCategory_Physiology:
    {
      if (HasCompartmentName() || HasSubstanceName())
        std::cout << "Ignoring compartment and substance name on physiology data request" << std::endl;
      return true;
    }
    case cdm::DataRequestData_eCategory_Environment:
    {
      if (HasCompartmentName() || HasSubstanceName())
        std::cout << "Ignoring compartment and substance name on environment data request" << std::endl;
      return true;
    }
    case cdm::DataRequestData_eCategory_GasCompartment:
    case cdm::DataRequestData_eCategory_LiquidCompartment:
    case cdm::DataRequestData_eCategory_ThermalCompartment:
    case cdm::DataRequestData_eCategory_TissueCompartment:
    {
      if (!HasCompartmentName())
        return false;
      return true;
    }
    case cdm::DataRequestData_eCategory_Substance:
    {
      if (!HasSubstanceName())
        return false;
      return true;
    }
    default:
      return true;//??
  }
}

size_t SEDataRequest::HashCode() const
{
  size_t h = std::hash<std::string>()(m_PropertyName);
  return h;
}

void SEDataRequest::Load(const cdm::DataRequestData& src, SEDataRequest& dst)
{
  SEDataRequest::Serialize(src, dst);
}
void SEDataRequest::Serialize(const cdm::DataRequestData& src, SEDataRequest& dst)
{
  SEDecimalFormat::Serialize(src.decimalformat(),dst);
  dst.m_CompartmentName = src.compartmentname();
  dst.m_SubstanceName = src.substancename();
  dst.m_PropertyName = src.propertyname();
  dst.m_RequestedUnit = src.unit();
}

cdm::DataRequestData* SEDataRequest::Unload(const SEDataRequest& src)
{
  cdm::DataRequestData* dst = new cdm::DataRequestData();
  SEDataRequest::Serialize(src,*dst);
  return dst;
}
void SEDataRequest::Serialize(const SEDataRequest& src, cdm::DataRequestData& dst)
{
  SEDecimalFormat::Serialize(src,*dst.mutable_decimalformat());
  dst.set_category(src.m_Category);
  if(src.HasCompartmentName())
    dst.set_compartmentname(src.m_CompartmentName);
  if(src.HasSubstanceName())
    dst.set_substancename(src.m_SubstanceName);

  dst.set_propertyname(src.m_PropertyName);
  if (src.HasUnit())
    dst.set_unit(src.m_Unit->GetString());
  else if (src.HasRequestedUnit())
    dst.set_unit(src.m_RequestedUnit);
}

cdm::DataRequestData_eCategory SEDataRequest::GetCategory() const 
{ 
  return m_Category; 
}

std::string SEDataRequest::GetCompartmentName() const
{
  return m_CompartmentName;
}
void SEDataRequest::SetCompartmentName(const std::string& name)
{
  m_CompartmentName = name;
}
bool SEDataRequest::HasCompartmentName() const
{
  return m_CompartmentName.empty() ? false : true;
}
void SEDataRequest::InvalidateCompartmentName()
{
  m_CompartmentName = "";
}

std::string SEDataRequest::GetSubstanceName() const
{
  return m_SubstanceName;
}
void SEDataRequest::SetSubstanceName(const std::string& name)
{
  m_SubstanceName = name;
}
bool SEDataRequest::HasSubstanceName() const
{
  return m_SubstanceName.empty() ? false : true;
}
void SEDataRequest::InvalidateSubstanceName()
{
  m_SubstanceName = "";
}

std::string SEDataRequest::GetPropertyName() const
{
  return m_PropertyName;
}
void SEDataRequest::SetPropertyName(const std::string& name)
{
  m_PropertyName = name;
}
bool SEDataRequest::HasPropertyName() const
{
  return m_PropertyName.empty()?false:true;
}
void SEDataRequest::InvalidatePropertyName()
{
  m_PropertyName = "";
}

std::string SEDataRequest::GetRequestedUnit() const
{
  return m_RequestedUnit;
}
void SEDataRequest::SetRequestedUnit(const std::string& unit)
{
  m_RequestedUnit = unit;
  m_Unit = nullptr;
}
bool SEDataRequest::HasRequestedUnit() const
{
  return m_RequestedUnit.empty()?false:true;
}
void SEDataRequest::InvalidateRequestedUnit()
{
  m_RequestedUnit = "";
}

const CCompoundUnit* SEDataRequest::GetUnit() const
{
  return m_Unit;
}
void SEDataRequest::SetUnit(const CCompoundUnit& unit)
{
  m_Unit = &unit;
  m_RequestedUnit = "";
}
bool SEDataRequest::HasUnit() const
{
  return m_Unit==nullptr?false:true;
}
void SEDataRequest::InvalidateUnit()
{
  m_Unit = nullptr;
}


