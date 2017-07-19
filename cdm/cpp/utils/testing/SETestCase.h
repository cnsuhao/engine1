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
#include "properties/SEScalarTime.h"
#include "utils/testing/SETestErrorStatistics.h"
class SETestSuite;

class DLL_DECL SETestCase : public Loggable
{
  friend SETestSuite;
protected:
  SETestCase(Logger* logger);
  SETestCase(const std::string& name, Logger* logger);
public:
  virtual ~SETestCase();

  virtual void Reset(); //reset values
  virtual void Clear(); //clear memory

  static void Load(const cdm::TestReportData_TestCaseData& src, SETestCase& dst);
  static cdm::TestReportData_TestCaseData* Unload(const SETestCase& src);
protected:
  static void Serialize(const cdm::TestReportData_TestCaseData& src, SETestCase& dst);
  static void Serialize(const SETestCase& src, cdm::TestReportData_TestCaseData& dst);

public:

  void                                 SetName(const std::string& name);
  std::string                          GetName() const;
  SEScalarTime&                        GetDuration();
  void                                 AddFailure(std::stringstream &msg);
  void                                 AddFailure(const std::string& err);
  const std::vector<std::string>&      GetFailures();

  SETestErrorStatistics& CreateErrorStatistic();
  const std::vector<SETestErrorStatistics*>& GetErrorStatistics() const;

protected:
  std::string  m_Name;
  SEScalarTime m_Duration;

  std::vector<std::string> m_Failure;
  std::vector<SETestErrorStatistics*> m_CaseEqualsErrors;
};