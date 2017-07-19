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
#include "utils/testing/SETestErrorStatistics.h"
#include "properties/SEFunction.h"

SETestErrorStatistics::SETestErrorStatistics(Logger* logger) : Loggable(logger)
{
  m_PercentToleranceVsNumErrorsHistogram = nullptr;
}

SETestErrorStatistics::~SETestErrorStatistics()
{
  Clear();
}

void SETestErrorStatistics::Clear()
{
  SAFE_DELETE(m_PercentToleranceVsNumErrorsHistogram);
}

void SETestErrorStatistics::Reset()
{
}

void SETestErrorStatistics::Load(const cdm::TestReportData_TestErrorStatisticsData& src, SETestErrorStatistics& dst)
{
  SETestErrorStatistics::Serialize(src, dst);
}
void SETestErrorStatistics::Serialize(const cdm::TestReportData_TestErrorStatisticsData& src, SETestErrorStatistics& dst)
{
  dst.Clear();

  dst.m_PropertyName = src.propertyname();
  dst.m_PercentTolerance = src.percenttolerance();
  dst.m_NumberOfErrors = src.numberoferrors();
  dst.m_ComputedPropertyID = src.computedpropertyid();
  dst.m_ExpectedPropertyID = src.expectedpropertyid();

  dst.m_MinimumError = src.minimumerror();
  dst.m_MaximumError = src.maximumerror();
  dst.m_AverageError = src.averageerror();
  dst.m_StandardDeviation = src.standarddeviation();

  if (src.has_percenttolerancevsnumerrors())
    SEFunction::Load(src.percenttolerancevsnumerrors(), dst.GetPercentToleranceVsNumErrorsHistogram());

  for (int i=0; i<src.differences_size(); i++)
    dst.m_Differences.push_back(src.differences(i));
}

cdm::TestReportData_TestErrorStatisticsData* SETestErrorStatistics::Unload(const SETestErrorStatistics& src)
{
  cdm::TestReportData_TestErrorStatisticsData* dst = new cdm::TestReportData_TestErrorStatisticsData();
  SETestErrorStatistics::Serialize(src,*dst);
  return dst;
}
void SETestErrorStatistics::Serialize(const SETestErrorStatistics& src, cdm::TestReportData_TestErrorStatisticsData& dst)
{
  if (!src.m_PropertyName.empty())
    dst.set_propertyname(src.m_PropertyName);
  dst.set_percenttolerance(src.m_PercentTolerance);
  dst.set_numberoferrors(src.m_NumberOfErrors);
  if (!src.m_ComputedPropertyID.empty())
    dst.set_computedpropertyid(src.m_ComputedPropertyID);
  if (!src.m_ExpectedPropertyID.empty())
    dst.set_expectedpropertyid(src.m_ExpectedPropertyID);
   
  if (!std::isnan(src.m_MinimumError))
    dst.set_minimumerror(src.m_MinimumError);
  if (!std::isnan(src.m_MaximumError))
    dst.set_maximumerror(src.m_MaximumError);
  if (!std::isnan(src.m_AverageError))
    dst.set_averageerror(src.m_AverageError);
  if (!std::isnan(src.m_StandardDeviation))
    dst.set_standarddeviation(src.m_StandardDeviation);

  std::string dData;
  for (auto s : src.m_Differences)
      dst.mutable_differences()->Add(s.c_str());

  if (src.m_PercentToleranceVsNumErrorsHistogram != nullptr)
    dst.set_allocated_percenttolerancevsnumerrors(SEFunction::Unload(*src.m_PercentToleranceVsNumErrorsHistogram));
}

void SETestErrorStatistics::SetMinimumError(double MinimumError)
{
  m_MinimumError = MinimumError;
}

double SETestErrorStatistics::GetMinimumError() const
{
  return m_MinimumError;
}

void SETestErrorStatistics::SetMaximumError(double MaximumError)
{
  m_MaximumError = MaximumError;
}

double SETestErrorStatistics::GetMaximumError() const
{
  return m_MaximumError;
}

void SETestErrorStatistics::SetAverageError(double AverageError)
{
  m_AverageError = AverageError;
}

double SETestErrorStatistics::GetAverageError() const
{
  return m_AverageError;
}

void SETestErrorStatistics::SetStandardDeviation(double StandardDeviation)
{
  m_StandardDeviation = StandardDeviation;
}

double SETestErrorStatistics::GetStandardDeviation() const
{
  return m_StandardDeviation;
}

void SETestErrorStatistics::AddDifference(const std::string& difference)
{
  std::string n;
  for(unsigned int i=0; i<m_Differences.size(); i++)
  {
    n=m_Differences.at(i);
    if(n==difference)
      return;
  }
  m_Differences.push_back(difference);
}

const std::vector<std::string>* SETestErrorStatistics::GetDifferences() const
{
  return &m_Differences;
}

void SETestErrorStatistics::SetComputedPropertyID(const std::string& ComputedPropertyID)
{
  m_ComputedPropertyID = ComputedPropertyID;
}

std::string SETestErrorStatistics::GetComputedPropertyID() const
{
  return m_ComputedPropertyID;
}

void SETestErrorStatistics::SetExpectedPropertyID(const std::string& ExpectedPropertyID)
{
  m_ExpectedPropertyID = ExpectedPropertyID;
}

std::string SETestErrorStatistics::GetExpectedPropertyID() const
{
  return m_ExpectedPropertyID;
}

void SETestErrorStatistics::SetNumberOfErrors(int NumberOfErrors)
{
  m_NumberOfErrors = NumberOfErrors;
}

int SETestErrorStatistics::GetNumberOfErrors() const
{
  return m_NumberOfErrors;
}

void SETestErrorStatistics::SetPropertyName(const std::string& PropertyName)
{
  m_PropertyName = PropertyName;
}

std::string SETestErrorStatistics::GetPropertyName() const
{
  return m_PropertyName;
}

bool SETestErrorStatistics::HasPercentTolerancevsNumErrorsHistogram() const
{
  if(m_PercentToleranceVsNumErrorsHistogram==nullptr)
    return false;
  return true;
}

SEFunction&  SETestErrorStatistics::GetPercentToleranceVsNumErrorsHistogram()
{
  if(HasPercentTolerancevsNumErrorsHistogram())
    return *m_PercentToleranceVsNumErrorsHistogram;

  m_PercentToleranceVsNumErrorsHistogram = new SEFunction();
  m_PercentToleranceVsNumErrorsHistogram->GetIndependent().push_back(m_PercentTolerance);
  m_PercentToleranceVsNumErrorsHistogram->GetDependent().push_back(m_NumberOfErrors);
  return *m_PercentToleranceVsNumErrorsHistogram;
}

void SETestErrorStatistics::SetPercentToleranceVsNumErrorsHistogram(SEFunction* PercentToleranceVsNumErrors)
{
  m_PercentToleranceVsNumErrorsHistogram = PercentToleranceVsNumErrors;
}
