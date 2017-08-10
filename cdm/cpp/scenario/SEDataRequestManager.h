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

#pragma once
#include "scenario/SEDataRequest.h"

class CDM_DECL SEDataRequestManager : public Loggable
{
public:
  SEDataRequestManager(Logger* logger);
  ~SEDataRequestManager();

  void Clear();

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
  
protected:
  std::string                  m_ResultsFilename;
  double                       m_SamplesPerSecond;
  std::vector<SEDataRequest*>  m_Requests;

  SEDecimalFormat*             m_DefaultDecimalFormatting;
  SEDecimalFormat*             m_OverrideDecimalFormatting;
};