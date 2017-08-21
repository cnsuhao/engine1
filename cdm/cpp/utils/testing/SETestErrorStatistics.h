/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
class SETestCase;
class SETestSuite;
PROTO_PUSH
#include "bind/cdm/TestReport.pb.h"
PROTO_POP

// This data class is intended for use in array based data
// Each value in the array is compared and can be tracked
// and this provides a summary of how many values in the array
// were wrong and some statistics to go along with all of those errors
class CDM_DECL SETestErrorStatistics : public Loggable
{
  friend SETestCase;
  friend SETestSuite;
protected:
  SETestErrorStatistics(Logger* logger);
public:
  virtual ~SETestErrorStatistics();

  virtual void Reset(); //reset values
  virtual void Clear(); //clear memory

  static void Load(const cdm::TestReportData_TestErrorStatisticsData& src, SETestErrorStatistics& dst);
  static cdm::TestReportData_TestErrorStatisticsData* Unload(const SETestErrorStatistics& src);
protected:
  static void Serialize(const cdm::TestReportData_TestErrorStatisticsData& src, SETestErrorStatistics& dst);
  static void Serialize(const SETestErrorStatistics& src, cdm::TestReportData_TestErrorStatisticsData& dst);

public:

  void             SetPropertyName(const std::string& PropertyName);              
  std::string      GetPropertyName() const;

  void             SetComputedPropertyID(const std::string& ComputedPropertyID);        
  std::string      GetComputedPropertyID() const;

  void             SetExpectedPropertyID(const std::string& ExpectedPropertyID);        
  std::string      GetExpectedPropertyID() const;

  void             SetNumberOfErrors(int NumberOfErrors);                      
  int              GetNumberOfErrors() const;

  void             SetMinimumError(double MinimumError);                    
  double           GetMinimumError() const;

  void             SetMaximumError(double MaximumError);                    
  double           GetMaximumError() const;

  void             SetAverageError(double AverageError);                    
  double           GetAverageError() const;

  void             SetStandardDeviation(double StandardDeviation);                
  double           GetStandardDeviation() const;

  void             AddDifference(const std::string& difference);            
  const std::vector<std::string>*  GetDifferences()  const;

  // This a histogram that shows a percent tolerance and how many errors fall with in each bin
  bool             HasPercentTolerancevsNumErrorsHistogram() const;
  SEFunction&      GetPercentToleranceVsNumErrorsHistogram();    
  void             SetPercentToleranceVsNumErrorsHistogram(SEFunction* PercentToleranceVsNumErrors);

protected:
  int m_NumberOfErrors;
  double m_MinimumError;
  double m_MaximumError;
  double m_AverageError;
  double m_StandardDeviation;
  double m_PercentTolerance;
  std::string m_PropertyName;
  std::string m_ComputedPropertyID;
  std::string m_ExpectedPropertyID;
  SEFunction* m_PercentToleranceVsNumErrorsHistogram;
  std::vector<std::string> m_Differences;  
};