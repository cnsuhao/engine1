/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "utils/testing/SETestSuite.h"

class CDM_DECL SETestReport : public Loggable
{
public:

  SETestReport(Logger* logger);
  virtual ~SETestReport();
  
  virtual void Reset(); //reset values
  virtual void Clear(); //clear memory

  static void Load(const cdm::TestReportData& src, SETestReport& dst);
  static cdm::TestReportData* Unload(const SETestReport& src);
protected:
  static void Serialize(const cdm::TestReportData& src, SETestReport& dst);
  static void Serialize(const SETestReport& src, cdm::TestReportData& dst);

public:

  bool WriteFile(const std::string& filename);

  SETestSuite& CreateTestSuite();
  const std::vector<SETestSuite*>&  GetTestSuites() const;

protected: 
  std::vector<SETestSuite*> m_testSuite;
};