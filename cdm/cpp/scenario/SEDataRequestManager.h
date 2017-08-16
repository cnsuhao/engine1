/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "scenario/SEDataRequest.h"
class SESubstance;

class CDM_DECL SEDataRequestManager : public Loggable
{
public:
  SEDataRequestManager(Logger* logger);
  ~SEDataRequestManager();

  void Clear();

  bool Load(const std::string& str, SESubstanceManager& subMgr);
  bool LoadFile(const std::string& filename, SESubstanceManager& subMgr);
  void SaveFile(const std::string& filename) const;

  static void Load(const cdm::DataRequestManagerData& src, SEDataRequestManager& dst, SESubstanceManager& subMgr);
  static cdm::DataRequestManagerData* Unload(const SEDataRequestManager& src);
protected:
  static void Serialize(const cdm::DataRequestManagerData& src, SEDataRequestManager& dst, SESubstanceManager& subMgr);
  static void Serialize(const SEDataRequestManager& src, cdm::DataRequestManagerData& dst);

public:
  bool HasResultsFilename() const { return !m_ResultsFilename.empty(); }
  std::string GetResultFilename() const { return m_ResultsFilename; }
  void SetResultsFilename(const std::string& name) { m_ResultsFilename = name; }

  double GetSamplesPerSecond() const { return m_SamplesPerSecond; }
  void SetSamplesPerSecond(double num) { m_SamplesPerSecond = num; }

  bool HasDataRequests() { return !m_Requests.empty(); }
  const std::vector<SEDataRequest*>& GetDataRequests() { return m_Requests; }

  virtual bool HasDefaultDecimalFormatting() const;
  virtual SEDecimalFormat& GetDefaultDecimalFormatting();
  virtual void RemoveDefaultDecimalFormatting();

  virtual bool HasOverrideDecimalFormatting() const;
  virtual SEDecimalFormat& GetOverrideDecimalFormatting();
  virtual void RemoveOverrideDecimalFormatting();

  SEDataRequest& CreateDataRequest(cdm::DataRequestData_eCategory category, const SEDecimalFormat* dfault = nullptr);
  SEDataRequest& CreatePatientDataRequest(const std::string& property, const SEDecimalFormat* dfault = nullptr);
  SEDataRequest& CreatePatientDataRequest(const std::string& property, const CCompoundUnit& unit, const SEDecimalFormat* dfault = nullptr);

  SEDataRequest& CreatePhysiologyDataRequest(const std::string& property, const SEDecimalFormat* dfault = nullptr);
  SEDataRequest& CreatePhysiologyDataRequest(const std::string& property, const CCompoundUnit& unit, const SEDecimalFormat* dfault = nullptr);

  SEDataRequest& CreateEnvironmentDataRequest(const std::string& property, const SEDecimalFormat* dfault = nullptr);
  SEDataRequest& CreateEnvironmentDataRequest(const std::string& property, const CCompoundUnit& unit, const SEDecimalFormat* dfault = nullptr);

  SEDataRequest& CreateGasCompartmentDataRequest(const std::string& cmptName, const std::string& property, const SEDecimalFormat* dfault = nullptr);
  SEDataRequest& CreateGasCompartmentDataRequest(const std::string& cmptName, const std::string& property, const CCompoundUnit& unit, const SEDecimalFormat* dfault = nullptr);
  SEDataRequest& CreateGasCompartmentDataRequest(const std::string& cmptName, const SESubstance& sub, const std::string& property, const SEDecimalFormat* dfault = nullptr);
  SEDataRequest& CreateGasCompartmentDataRequest(const std::string& cmptName, const SESubstance& sub, const std::string& property, const CCompoundUnit& unit, const SEDecimalFormat* dfault = nullptr);

  SEDataRequest& CreateLiquidCompartmentDataRequest(const std::string& cmptName, const std::string& property, const SEDecimalFormat* dfault = nullptr);
  SEDataRequest& CreateLiquidCompartmentDataRequest(const std::string& cmptName, const std::string& property, const CCompoundUnit& unit, const SEDecimalFormat* dfault = nullptr);
  SEDataRequest& CreateLiquidCompartmentDataRequest(const std::string& cmptName, const SESubstance& sub, const std::string& property, const SEDecimalFormat* dfault = nullptr);
  SEDataRequest& CreateLiquidCompartmentDataRequest(const std::string& cmptName, const SESubstance& sub, const std::string& property, const CCompoundUnit& unit, const SEDecimalFormat* dfault = nullptr);

  SEDataRequest& CreateThermalCompartmentDataRequest(const std::string& property, const SEDecimalFormat* dfault = nullptr);
  SEDataRequest& CreateThermalCompartmentDataRequest(const std::string& property, const CCompoundUnit& unit, const SEDecimalFormat* dfault = nullptr);

  SEDataRequest& CreateTissueCompartmentDataRequest(const std::string& property, const SEDecimalFormat* dfault = nullptr);
  SEDataRequest& CreateTissueCompartmentDataRequest(const std::string& property, const CCompoundUnit& unit, const SEDecimalFormat* dfault = nullptr);

  SEDataRequest& CreateSubstanceDataRequest(const SESubstance& sub, const std::string& property, const SEDecimalFormat* dfault = nullptr);
  SEDataRequest& CreateSubstanceDataRequest(const SESubstance& sub, const std::string& property, const CCompoundUnit& unit, const SEDecimalFormat* dfault = nullptr);

  SEDataRequest& CreateAnesthesiaMachineDataRequest(const std::string& property, const SEDecimalFormat* dfault = nullptr);
  SEDataRequest& CreateAnesthesiaMachineDataRequest(const std::string& property, const CCompoundUnit& unit, const SEDecimalFormat* dfault = nullptr);

  SEDataRequest& CreateECGDataRequest(const std::string& property, const SEDecimalFormat* dfault = nullptr);
  SEDataRequest& CreateECGDataRequest(const std::string& property, const CCompoundUnit& unit, const SEDecimalFormat* dfault = nullptr);

  SEDataRequest& CreateInhalerDataRequest(const std::string& property, const SEDecimalFormat* dfault = nullptr);
  SEDataRequest& CreateInhalerDataRequest(const std::string& property, const CCompoundUnit& unit, const SEDecimalFormat* dfault = nullptr);
  
protected:
  std::string                  m_ResultsFilename;
  double                       m_SamplesPerSecond;
  std::vector<SEDataRequest*>  m_Requests;

  SEDecimalFormat*             m_DefaultDecimalFormatting;
  SEDecimalFormat*             m_OverrideDecimalFormatting;
};