/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "utils/testing/SETestCase.h"
#include "properties/SEScalarTime.h"

SETestCase::SETestCase(Logger* logger) : Loggable(logger)
{
  SETestCase("default", logger);
}
SETestCase::SETestCase(const std::string& name, Logger* logger) : Loggable(logger)
{
  m_Name = name;
}

SETestCase::~SETestCase()
{
  Clear();
}

void SETestCase::Clear()
{
  m_Failure.clear();
  m_Duration.SetValue(0, TimeUnit::s);
  DELETE_VECTOR(m_CaseEqualsErrors);
}

void SETestCase::Reset()
{
  m_Failure.clear();
  m_Duration.SetValue(0,TimeUnit::s);
  DELETE_VECTOR(m_CaseEqualsErrors);
}

void SETestCase::Load(const cdm::TestReportData_TestCaseData& src, SETestCase& dst)
{
  SETestCase::Serialize(src, dst);
}
void SETestCase::Serialize(const cdm::TestReportData_TestCaseData& src, SETestCase& dst)
{
  dst.Clear();

  dst.m_Name = src.name();
  if(src.has_duration())
    SEScalarTime::Load(src.duration(), dst.GetDuration());

  SETestErrorStatistics* ex;
  for (int i = 0; i<src.errorstats_size(); i++)
  {
    auto eData = src.errorstats(i);
    ex = new SETestErrorStatistics(dst.GetLogger());
    SETestErrorStatistics::Load(eData, *ex);
    dst.m_CaseEqualsErrors.push_back(ex);
  }

  for (int i=0; i<src.failure_size(); i++)
    dst.m_Failure.push_back(src.failure(i));
}

cdm::TestReportData_TestCaseData* SETestCase::Unload(const SETestCase& src)
{
  cdm::TestReportData_TestCaseData* dst = new cdm::TestReportData_TestCaseData();
  SETestCase::Serialize(src,*dst);
  return dst;
}
void SETestCase::Serialize(const SETestCase& src, cdm::TestReportData_TestCaseData& dst)
{
  dst.set_name(src.m_Name);

  dst.set_allocated_duration(SEScalarTime::Unload(src.m_Duration));

  for (std::string s : src.m_Failure)
    dst.mutable_failure()->Add(s.c_str());

  for (auto s : src.m_CaseEqualsErrors)
    dst.mutable_errorstats()->AddAllocated(SETestErrorStatistics::Unload(*s));
}

void SETestCase::SetName(const std::string& Name)
{
  m_Name = Name;
}

std::string SETestCase::GetName() const
{
  return m_Name;
}

SEScalarTime& SETestCase::GetDuration()
{
  return m_Duration;
}


void SETestCase::AddFailure(std::stringstream &err)
{
  AddFailure(err.str());
  err.str("");
  err.clear();
}
void SETestCase::AddFailure(const std::string& err)
{
  m_Failure.push_back(err);
  Error(err);
}
const std::vector<std::string>& SETestCase::GetFailures()
{
  return m_Failure;
}

SETestErrorStatistics& SETestCase::CreateErrorStatistic()
{
  SETestErrorStatistics* err = new SETestErrorStatistics(GetLogger());
  m_CaseEqualsErrors.push_back(err);
  return *err;
}
const std::vector<SETestErrorStatistics*>& SETestCase::GetErrorStatistics() const
{
  return m_CaseEqualsErrors;
}
