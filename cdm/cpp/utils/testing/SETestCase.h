/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "properties/SEScalarTime.h"
#include "utils/testing/SETestErrorStatistics.h"
class SETestSuite;

class CDM_DECL SETestCase : public Loggable
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