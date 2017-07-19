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

#include "stdafx.h"
#include "utils/testing/SETestSuite.h"

SETestSuite::SETestSuite(Logger* logger) : Loggable(logger)
{
  m_Performed = true;
  m_Name = "";
}

SETestSuite::~SETestSuite()
{
  Clear();
}

void SETestSuite::Clear()
{
  DELETE_VECTOR(m_SuiteEqualError);
  DELETE_VECTOR(m_TestCase);
}

void SETestSuite::Reset()
{
  for(unsigned int i = 0; i<m_TestCase.size(); i++)
  {
    m_TestCase.at(i)->Reset();
  }
  m_Performed = false;
  m_Name = "";
}

void SETestSuite::Load(const cdm::TestReportData_TestSuiteData& src, SETestSuite& dst)
{
  SETestSuite::Serialize(src, dst);
}
void SETestSuite::Serialize(const cdm::TestReportData_TestSuiteData& src, SETestSuite& dst)
{
  dst.Clear();

  dst.m_Name = src.name();
  dst.m_Performed = src.performed();  

  for (int i = 0; i<src.requirement_size(); i++)
    dst.m_Requirements.push_back(src.requirement(i));

  SETestErrorStatistics* ex;
  for (int i = 0; i < src.errorstats_size(); i++)
  {
    ex = new SETestErrorStatistics(dst.GetLogger());
    SETestErrorStatistics::Load(src.errorstats(i), *ex);
    dst.m_SuiteEqualError.push_back(ex);
  }

  SETestCase* tx;
  for (int i = 0; i < src.testcase_size(); i++)
  {
    tx = new SETestCase(dst.GetLogger());
    SETestCase::Load(src.testcase(i), *tx);
    dst.m_TestCase.push_back(tx);
  }
}

cdm::TestReportData_TestSuiteData* SETestSuite::Unload(const SETestSuite& src)
{
  cdm::TestReportData_TestSuiteData* dst = new cdm::TestReportData_TestSuiteData();
  SETestSuite::Serialize(src,*dst);
  return dst;
}
void SETestSuite::Serialize(const SETestSuite& src, cdm::TestReportData_TestSuiteData& dst)
{
  dst.set_name(src.m_Name);
  dst.set_performed(src.m_Performed);
  dst.set_errors((google::protobuf::uint32)src.GetNumberOfErrors());
  dst.set_tests((google::protobuf::uint32)src.GetTestCases().size());

  for (std::string s : src.m_Requirements)
    dst.mutable_requirement()->Add(s.c_str());

  for (auto er : src.m_SuiteEqualError)
    dst.mutable_errorstats()->AddAllocated(SETestErrorStatistics::Unload(*er));

  for (auto tc : src.m_TestCase)
    dst.mutable_testcase()->AddAllocated(SETestCase::Unload(*tc));
}

void SETestSuite::SetName(const std::string& Name)
{
  m_Name = Name;
}

std::string SETestSuite::GetName() const
{
  return m_Name;
}

void SETestSuite::PerformSuite(bool performed)
{
  m_Performed = performed;
}

bool SETestSuite::PerformedSuite()
{
  return m_Performed;
}

const SEScalarTime& SETestSuite::GetDuration() const
{
  double time = 0;
  for (unsigned int i = 0; i < m_TestCase.size(); i++)
    time += m_TestCase.at(i)->GetDuration().GetValue(TimeUnit::s);
  m_Time.SetValue(time,TimeUnit::s);
  return m_Time;
}

std::vector<std::string>& SETestSuite::GetRequirements()
{
  return m_Requirements;
}

SETestCase& SETestSuite::CreateTestCase()
{
  SETestCase* test = new SETestCase(GetLogger());
  m_TestCase.push_back(test);
  return *test;
}

const std::vector<SETestCase*>& SETestSuite::GetTestCases() const
{
  return m_TestCase;
}

size_t SETestSuite::GetNumberOfErrors() const
{
  size_t count = 0;
  for (unsigned int i = 0; i < m_TestCase.size(); i++)
    count += m_TestCase.at(i)->GetFailures().size();
  return count;
}
