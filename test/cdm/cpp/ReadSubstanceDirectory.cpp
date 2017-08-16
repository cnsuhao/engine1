/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "CommonDataModelTest.h"
#include "substance/SESubstanceManager.h"
#include "utils/testing/SETestReport.h"
#include "utils/testing/SETestCase.h"
#include "utils/testing/SETestSuite.h"
#include "utils/FileUtils.h"
#include "utils/TimingProfile.h"

void CommonDataModelTest::ReadSubstanceDirectory(const std::string& rptDirectory)
{
  TimingProfile pTimer;
  std::string testName = "ReadSubstanceDirectory";
  m_Logger->ResetLogFile(rptDirectory + "/" + testName + ".log");
  SESubstance obj(m_Logger);

  std::string dir = GetCurrentWorkingDirectory();
  dir.append("/substances");

  SETestReport testReport(m_Logger);
  SETestSuite&  testSuite = testReport.CreateTestSuite();
  testSuite.SetName(testName);

  SETestCase& testCase = testSuite.CreateTestCase();
  pTimer.Start("Case");
  SESubstanceManager subMgr(m_Logger);
  if(!subMgr.LoadSubstanceDirectory())
    testCase.AddFailure("Unable to load substances");
  testCase.GetDuration().SetValue(pTimer.GetElapsedTime_s("Case"), TimeUnit::s);
  testCase.SetName(obj.GetName());
  // TODO would be nice to listen to errors on the logger and add them to the testCase failures...

  testReport.WriteFile(rptDirectory +"/"+testName+"Report.pba");
}
