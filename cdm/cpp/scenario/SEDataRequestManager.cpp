/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "SEDataRequestManager.h"
#include "substance/SESubstanceManager.h"
#include <google/protobuf/text_format.h>

SEDataRequestManager::SEDataRequestManager(Logger* logger) : Loggable(logger)
{
  m_DefaultDecimalFormatting = nullptr;
  m_OverrideDecimalFormatting = nullptr;
  Clear();
}

SEDataRequestManager::~SEDataRequestManager()
{
  Clear();
}

void SEDataRequestManager::Clear()
{
  m_SamplesPerSecond = 0; // Sample every time step
  DELETE_VECTOR(m_Requests);
  SAFE_DELETE(m_DefaultDecimalFormatting);
  SAFE_DELETE(m_OverrideDecimalFormatting);
}

bool SEDataRequestManager::Load(const std::string& str, SESubstanceManager& subMgr)
{
  cdm::DataRequestManagerData src;
  if (!google::protobuf::TextFormat::ParseFromString(str, &src))
    return false;
  SEDataRequestManager::Load(src, *this, subMgr);
  return true;
}

bool SEDataRequestManager::LoadFile(const std::string& filename, SESubstanceManager& subMgr)
{
  cdm::DataRequestManagerData src;
  std::ifstream file_stream(filename, std::ios::in);
  std::string fmsg((std::istreambuf_iterator<char>(file_stream)), std::istreambuf_iterator<char>());
  if (!google::protobuf::TextFormat::ParseFromString(fmsg, &src))
    return false;
  SEDataRequestManager::Load(src, *this, subMgr);
  return true;

  // If its a binary string in the file...
  //std::ifstream binary_istream(patientFile, std::ios::in | std::ios::binary);
  //src.ParseFromIstream(&binary_istream);
}

void SEDataRequestManager::SaveFile(const std::string& filename) const
{
  std::string content;
  cdm::DataRequestManagerData* src = SEDataRequestManager::Unload(*this);
  google::protobuf::TextFormat::PrintToString(*src, &content);
  std::ofstream ascii_ostream(filename, std::ios::out | std::ios::trunc);
  ascii_ostream << content;
  ascii_ostream.flush();
  ascii_ostream.close();
  delete src;
}

void SEDataRequestManager::Load(const cdm::DataRequestManagerData& src, SEDataRequestManager& dst, SESubstanceManager& subMgr)
{
  SEDataRequestManager::Serialize(src, dst,subMgr);
}
void SEDataRequestManager::Serialize(const cdm::DataRequestManagerData& src, SEDataRequestManager& dst, SESubstanceManager& subMgr)
{
  dst.Clear();
  dst.m_ResultsFilename = src.resultsfilename();
  dst.m_SamplesPerSecond = src.samplespersecond();
  if (src.has_defaultdecimalformatting())
    SEDecimalFormat::Load(src.defaultdecimalformatting(),dst.GetDefaultDecimalFormatting());
  if (src.has_overridedecimalformatting())
    SEDecimalFormat::Load(src.overridedecimalformatting(), dst.GetOverrideDecimalFormatting());

  for (int i=0; i<src.datarequest_size(); i++)
  {
    const cdm::DataRequestData& drData = src.datarequest(i);
    SEDataRequest* dr = new SEDataRequest(drData.category(), dst.HasOverrideDecimalFormatting() ? dst.m_OverrideDecimalFormatting : dst.m_DefaultDecimalFormatting);
    SEDataRequest::Load(drData, *dr);
    if (!dr->IsValid())
      dst.Error("Ignoring invalid DataRequest for property " + dr->m_PropertyName);
    else
      dst.m_Requests.push_back(dr);
  }
}

cdm::DataRequestManagerData* SEDataRequestManager::Unload(const SEDataRequestManager& src)
{
  cdm::DataRequestManagerData* dst = new cdm::DataRequestManagerData();
  SEDataRequestManager::Serialize(src,*dst);
  return dst;
}
void SEDataRequestManager::Serialize(const SEDataRequestManager& src, cdm::DataRequestManagerData& dst)
{
  dst.set_resultsfilename(src.m_ResultsFilename);
  dst.set_samplespersecond(src.m_SamplesPerSecond);
  if (src.HasDefaultDecimalFormatting())
    dst.set_allocated_defaultdecimalformatting(SEDecimalFormat::Unload(*src.m_DefaultDecimalFormatting));
  if (src.HasOverrideDecimalFormatting())
    dst.set_allocated_overridedecimalformatting(SEDecimalFormat::Unload(*src.m_OverrideDecimalFormatting));
  for (SEDataRequest* dr : src.m_Requests)
    dst.mutable_datarequest()->AddAllocated(SEDataRequest::Unload(*dr));
}

bool SEDataRequestManager::HasDefaultDecimalFormatting() const
{
  return m_DefaultDecimalFormatting != nullptr;
}
SEDecimalFormat& SEDataRequestManager::GetDefaultDecimalFormatting()
{
  if (m_DefaultDecimalFormatting == nullptr)
    m_DefaultDecimalFormatting = new SEDecimalFormat();
  return *m_DefaultDecimalFormatting;
}
void SEDataRequestManager::RemoveDefaultDecimalFormatting()
{
  SAFE_DELETE(m_DefaultDecimalFormatting);
}

bool SEDataRequestManager::HasOverrideDecimalFormatting() const
{
  return m_OverrideDecimalFormatting != nullptr;
}
SEDecimalFormat& SEDataRequestManager::GetOverrideDecimalFormatting()
{
  if (m_OverrideDecimalFormatting == nullptr)
    m_OverrideDecimalFormatting = new SEDecimalFormat();
  return *m_OverrideDecimalFormatting;
}
void SEDataRequestManager::RemoveOverrideDecimalFormatting()
{
  SAFE_DELETE(m_OverrideDecimalFormatting);
}

SEDataRequest& SEDataRequestManager::CreateDataRequest(cdm::DataRequestData_eCategory category, const SEDecimalFormat* dfault)
{
  SEDataRequest* dr = new SEDataRequest(category, dfault);
  m_Requests.push_back(dr);
  return *dr;
}

SEDataRequest& SEDataRequestManager::CreatePatientDataRequest(const std::string& property, const SEDecimalFormat* dfault)
{
  SEDataRequest* dr = new SEDataRequest(cdm::DataRequestData_eCategory_Patient, dfault);
  m_Requests.push_back(dr);
  dr->SetPropertyName(property);
  return *dr;
}
SEDataRequest& SEDataRequestManager::CreatePatientDataRequest(const std::string& property, const CCompoundUnit& unit, const SEDecimalFormat* dfault)
{
  SEDataRequest* dr = new SEDataRequest(cdm::DataRequestData_eCategory_Patient, dfault);
  m_Requests.push_back(dr);
  dr->SetPropertyName(property);
  dr->SetUnit(unit);
  return *dr;
}

SEDataRequest& SEDataRequestManager::CreatePhysiologyDataRequest(const std::string& property, const SEDecimalFormat* dfault)
{
  SEDataRequest* dr = new SEDataRequest(cdm::DataRequestData_eCategory_Physiology, dfault);
  m_Requests.push_back(dr);
  dr->SetPropertyName(property);
  return *dr;
}
SEDataRequest& SEDataRequestManager::CreatePhysiologyDataRequest(const std::string& property, const CCompoundUnit& unit, const SEDecimalFormat* dfault)
{
  SEDataRequest* dr = new SEDataRequest(cdm::DataRequestData_eCategory_Physiology, dfault);
  m_Requests.push_back(dr);
  dr->SetPropertyName(property);
  dr->SetUnit(unit);
  return *dr;
}

SEDataRequest& SEDataRequestManager::CreateEnvironmentDataRequest(const std::string& property, const SEDecimalFormat* dfault)
{
  SEDataRequest* dr = new SEDataRequest(cdm::DataRequestData_eCategory_Environment, dfault);
  m_Requests.push_back(dr);
  dr->SetPropertyName(property);
  return *dr;
}
SEDataRequest& SEDataRequestManager::CreateEnvironmentDataRequest(const std::string& property, const CCompoundUnit& unit, const SEDecimalFormat* dfault)
{
  SEDataRequest* dr = new SEDataRequest(cdm::DataRequestData_eCategory_Environment, dfault);
  m_Requests.push_back(dr);
  dr->SetPropertyName(property);
  dr->SetUnit(unit);
  return *dr;
}

SEDataRequest& SEDataRequestManager::CreateGasCompartmentDataRequest(const std::string& cmptName, const std::string& property, const SEDecimalFormat* dfault)
{
  SEDataRequest* dr = new SEDataRequest(cdm::DataRequestData_eCategory_GasCompartment, dfault);
  m_Requests.push_back(dr);
  dr->SetCompartmentName(cmptName);
  dr->SetPropertyName(property);
  return *dr;
}
SEDataRequest& SEDataRequestManager::CreateGasCompartmentDataRequest(const std::string& cmptName, const std::string& property, const CCompoundUnit& unit, const SEDecimalFormat* dfault)
{
  SEDataRequest* dr = new SEDataRequest(cdm::DataRequestData_eCategory_GasCompartment, dfault);
  m_Requests.push_back(dr);
  dr->SetCompartmentName(cmptName);
  dr->SetPropertyName(property);
  dr->SetUnit(unit);
  return *dr;
}

SEDataRequest& SEDataRequestManager::CreateGasCompartmentDataRequest(const std::string& cmptName, const SESubstance& sub, const std::string& property, const SEDecimalFormat* dfault)
{
  SEDataRequest* dr = new SEDataRequest(cdm::DataRequestData_eCategory_GasCompartment, dfault);
  m_Requests.push_back(dr);
  dr->SetCompartmentName(cmptName);
  dr->SetSubstanceName(sub.GetName());
  dr->SetPropertyName(property);
  return *dr;
}
SEDataRequest& SEDataRequestManager::CreateGasCompartmentDataRequest(const std::string& cmptName, const SESubstance& sub, const std::string& property, const CCompoundUnit& unit, const SEDecimalFormat* dfault)
{
  SEDataRequest* dr = new SEDataRequest(cdm::DataRequestData_eCategory_GasCompartment, dfault);
  m_Requests.push_back(dr);
  dr->SetCompartmentName(cmptName);
  dr->SetSubstanceName(sub.GetName());
  dr->SetPropertyName(property);
  dr->SetUnit(unit);
  return *dr;
}

SEDataRequest& SEDataRequestManager::CreateLiquidCompartmentDataRequest(const std::string& cmptName, const std::string& property, const SEDecimalFormat* dfault)
{
  SEDataRequest* dr = new SEDataRequest(cdm::DataRequestData_eCategory_LiquidCompartment, dfault);
  m_Requests.push_back(dr);
  dr->SetCompartmentName(cmptName);
  dr->SetPropertyName(property);
  return *dr;
}
SEDataRequest& SEDataRequestManager::CreateLiquidCompartmentDataRequest(const std::string& cmptName, const std::string& property, const CCompoundUnit& unit, const SEDecimalFormat* dfault)
{
  SEDataRequest* dr = new SEDataRequest(cdm::DataRequestData_eCategory_LiquidCompartment, dfault);
  m_Requests.push_back(dr);
  dr->SetCompartmentName(cmptName);
  dr->SetPropertyName(property);
  dr->SetUnit(unit);
  return *dr;
}

SEDataRequest& SEDataRequestManager::CreateLiquidCompartmentDataRequest(const std::string& cmptName, const SESubstance& sub, const std::string& property, const SEDecimalFormat* dfault)
{
  SEDataRequest* dr = new SEDataRequest(cdm::DataRequestData_eCategory_LiquidCompartment, dfault);
  m_Requests.push_back(dr);
  dr->SetCompartmentName(cmptName);
  dr->SetSubstanceName(sub.GetName());
  dr->SetPropertyName(property);
  return *dr;
}
SEDataRequest& SEDataRequestManager::CreateLiquidCompartmentDataRequest(const std::string& cmptName, const SESubstance& sub, const std::string& property, const CCompoundUnit& unit, const SEDecimalFormat* dfault)
{
  SEDataRequest* dr = new SEDataRequest(cdm::DataRequestData_eCategory_LiquidCompartment, dfault);
  m_Requests.push_back(dr);
  dr->SetCompartmentName(cmptName);
  dr->SetSubstanceName(sub.GetName());
  dr->SetPropertyName(property);
  dr->SetUnit(unit);
  return *dr;
}

SEDataRequest& SEDataRequestManager::CreateThermalCompartmentDataRequest(const std::string& property, const SEDecimalFormat* dfault)
{
  SEDataRequest* dr = new SEDataRequest(cdm::DataRequestData_eCategory_ThermalCompartment, dfault);
  m_Requests.push_back(dr);
  dr->SetPropertyName(property);
  return *dr;
}
SEDataRequest& SEDataRequestManager::CreateThermalCompartmentDataRequest(const std::string& property, const CCompoundUnit& unit, const SEDecimalFormat* dfault)
{
  SEDataRequest* dr = new SEDataRequest(cdm::DataRequestData_eCategory_ThermalCompartment, dfault);
  m_Requests.push_back(dr);
  dr->SetPropertyName(property);
  dr->SetUnit(unit);
  return *dr;
}

SEDataRequest& SEDataRequestManager::CreateTissueCompartmentDataRequest(const std::string& property, const SEDecimalFormat* dfault)
{
  SEDataRequest* dr = new SEDataRequest(cdm::DataRequestData_eCategory_TissueCompartment, dfault);
  m_Requests.push_back(dr);
  dr->SetPropertyName(property);
  return *dr;
}
SEDataRequest& SEDataRequestManager::CreateTissueCompartmentDataRequest(const std::string& property, const CCompoundUnit& unit, const SEDecimalFormat* dfault)
{
  SEDataRequest* dr = new SEDataRequest(cdm::DataRequestData_eCategory_TissueCompartment, dfault);
  m_Requests.push_back(dr);
  dr->SetPropertyName(property);
  dr->SetUnit(unit);
  return *dr;
}

SEDataRequest& SEDataRequestManager::CreateSubstanceDataRequest(const SESubstance& sub, const std::string& property, const SEDecimalFormat* dfault)
{
  SEDataRequest* dr = new SEDataRequest(cdm::DataRequestData_eCategory_Substance, dfault);
  m_Requests.push_back(dr);
  dr->SetSubstanceName(sub.GetName());
  dr->SetPropertyName(property);
  return *dr;
}
SEDataRequest& SEDataRequestManager::CreateSubstanceDataRequest(const SESubstance& sub, const std::string& property, const CCompoundUnit& unit, const SEDecimalFormat* dfault)
{
  SEDataRequest* dr = new SEDataRequest(cdm::DataRequestData_eCategory_Substance, dfault);
  m_Requests.push_back(dr);
  dr->SetSubstanceName(sub.GetName());
  dr->SetPropertyName(property);
  dr->SetUnit(unit);
  return *dr;
}

SEDataRequest& SEDataRequestManager::CreateAnesthesiaMachineDataRequest(const std::string& property, const SEDecimalFormat* dfault)
{
  SEDataRequest* dr = new SEDataRequest(cdm::DataRequestData_eCategory_AnesthesiaMachine, dfault);
  m_Requests.push_back(dr);
  dr->SetPropertyName(property);
  return *dr;
}
SEDataRequest& SEDataRequestManager::CreateAnesthesiaMachineDataRequest(const std::string& property, const CCompoundUnit& unit, const SEDecimalFormat* dfault)
{
  SEDataRequest* dr = new SEDataRequest(cdm::DataRequestData_eCategory_AnesthesiaMachine, dfault);
  m_Requests.push_back(dr);
  dr->SetPropertyName(property);
  dr->SetUnit(unit);
  return *dr;
}

SEDataRequest& SEDataRequestManager::CreateECGDataRequest(const std::string& property, const SEDecimalFormat* dfault)
{
  SEDataRequest* dr = new SEDataRequest(cdm::DataRequestData_eCategory_ECG, dfault);
  m_Requests.push_back(dr);
  dr->SetPropertyName(property);
  return *dr;
}
SEDataRequest& SEDataRequestManager::CreateECGDataRequest(const std::string& property, const CCompoundUnit& unit, const SEDecimalFormat* dfault)
{
  SEDataRequest* dr = new SEDataRequest(cdm::DataRequestData_eCategory_ECG, dfault);
  m_Requests.push_back(dr);
  dr->SetPropertyName(property);
  dr->SetUnit(unit);
  return *dr;
}

SEDataRequest& SEDataRequestManager::CreateInhalerDataRequest(const std::string& property, const SEDecimalFormat* dfault)
{
  SEDataRequest* dr = new SEDataRequest(cdm::DataRequestData_eCategory_Inhaler, dfault);
  m_Requests.push_back(dr);
  dr->SetPropertyName(property);
  return *dr;
}
SEDataRequest& SEDataRequestManager::CreateInhalerDataRequest(const std::string& property, const CCompoundUnit& unit, const SEDecimalFormat* dfault)
{
  SEDataRequest* dr = new SEDataRequest(cdm::DataRequestData_eCategory_Inhaler, dfault);
  m_Requests.push_back(dr);
  dr->SetPropertyName(property);
  dr->SetUnit(unit);
  return *dr;
}
