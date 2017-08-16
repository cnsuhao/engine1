/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "utils/testing/SETestReport.h"
#include <google/protobuf/text_format.h>

SETestReport::SETestReport(Logger* logger) : Loggable(logger)
{
}

SETestReport::~SETestReport()
{
  Clear();
}

void SETestReport::Clear()
{
  DELETE_VECTOR(m_testSuite);
}

void SETestReport::Reset()
{
}

void SETestReport::Load(const cdm::TestReportData& src, SETestReport& dst)
{
  SETestReport::Serialize(src, dst);
}
void SETestReport::Serialize(const cdm::TestReportData& src, SETestReport& dst)
{
  dst.Clear();

  SETestSuite* sx;
  for (int i = 0; i < src.testsuite_size(); i++)
  {
    sx = new SETestSuite(dst.GetLogger());
    SETestSuite::Load(src.testsuite(i), *sx);
    dst.m_testSuite.push_back(sx);
  }
}

cdm::TestReportData* SETestReport::Unload(const SETestReport& src)
{
  cdm::TestReportData* dst = new cdm::TestReportData();
  SETestReport::Serialize(src,*dst);
  return dst;
}
void SETestReport::Serialize(const SETestReport& src, cdm::TestReportData& dst)
{
  for (auto ts : src.m_testSuite)
    dst.mutable_testsuite()->AddAllocated(SETestSuite::Unload(*ts));
}

bool SETestReport::WriteFile(const std::string& fileName)
{ 
  try
  {
    std::string content;
    cdm::TestReportData* pbuff = SETestReport::Unload(*this);
    google::protobuf::TextFormat::PrintToString(*pbuff, &content);
    std::ofstream ascii_ostream(fileName, std::ios::out | std::ios::trunc);
    ascii_ostream << content;
    ascii_ostream.flush();
    ascii_ostream.close();
    delete pbuff;
  }
  catch (std::exception e)
  {
    Error(e.what());
    return false;
  }
  return true;
}

SETestSuite& SETestReport::CreateTestSuite()
{
  SETestSuite* suite = new SETestSuite(GetLogger());
  m_testSuite.push_back(suite);
  return *suite;
}
const std::vector<SETestSuite*>& SETestReport::GetTestSuites() const
{
  return m_testSuite;
}