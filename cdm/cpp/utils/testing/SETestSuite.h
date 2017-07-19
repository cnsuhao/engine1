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
#include "utils/testing/SETestCase.h"
class SETestReport;

class DLL_DECL SETestSuite : public Loggable
{
  friend SETestReport;
protected:
  SETestSuite(Logger* logger);
public:
  virtual ~SETestSuite();

  virtual void Reset(); //reset values
  virtual void Clear(); //clear memory

  static void Load(const cdm::TestReportData_TestSuiteData& src, SETestSuite& dst);
  static cdm::TestReportData_TestSuiteData* Unload(const SETestSuite& src);
protected:
  static void Serialize(const cdm::TestReportData_TestSuiteData& src, SETestSuite& dst);
  static void Serialize(const SETestSuite& src, cdm::TestReportData_TestSuiteData& dst);

public:

  void                SetName(const std::string& Name);                        
  std::string          GetName() const;  

  void                PerformSuite(bool Performed);                      
  bool                PerformedSuite();  
  
  const SEScalarTime&  GetDuration() const;
          
  std::vector<std::string>&  GetRequirements();  

  SETestCase& CreateTestCase();
  const std::vector<SETestCase*>&  GetTestCases() const;

  size_t GetNumberOfErrors() const;

protected:

  bool m_Performed;
  std::string m_Name;
  std::vector<std::string> m_Requirements;
  std::vector<SETestErrorStatistics*> m_SuiteEqualError;
  std::vector<SETestCase*> m_TestCase;
  mutable SEScalarTime m_Time;
};