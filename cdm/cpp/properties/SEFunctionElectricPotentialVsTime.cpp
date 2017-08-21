/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "properties/SEFunctionElectricPotentialVsTime.h"
#include "properties/SEScalarTime.h"
#include "properties/SEScalarElectricPotential.h"
#include "utils/GeneralMath.h"
#include "utils/Logger.h"


SEFunctionElectricPotentialVsTime::SEFunctionElectricPotentialVsTime() : SEFunction()
{
  
}

SEFunctionElectricPotentialVsTime::~SEFunctionElectricPotentialVsTime()
{
  Clear();
}

void SEFunctionElectricPotentialVsTime::Clear()
{
  SEFunction::Clear();
  m_TimeUnit = nullptr;
  m_ElectricPotentialUnit = nullptr;
}

void SEFunctionElectricPotentialVsTime::Load(const cdm::FunctionElectricPotentialVsTimeData& src, SEFunctionElectricPotentialVsTime& dst)
{
  SEFunctionElectricPotentialVsTime::Serialize(src, dst);
}
void SEFunctionElectricPotentialVsTime::Serialize(const cdm::FunctionElectricPotentialVsTimeData& src, SEFunctionElectricPotentialVsTime& dst)
{
  SEFunction::Serialize(src.functionelectricpotentialvstime(), dst);
  dst.m_TimeUnit = &TimeUnit::GetCompoundUnit(src.functionelectricpotentialvstime().independentunit());
  dst.m_ElectricPotentialUnit = &ElectricPotentialUnit::GetCompoundUnit(src.functionelectricpotentialvstime().dependentunit());
}

cdm::FunctionElectricPotentialVsTimeData* SEFunctionElectricPotentialVsTime::Unload(const SEFunctionElectricPotentialVsTime& src)
{
  if (!src.IsValid())
    return nullptr;
  cdm::FunctionElectricPotentialVsTimeData* dst = new cdm::FunctionElectricPotentialVsTimeData();
  Serialize(src, *dst);
  return dst;
}
void SEFunctionElectricPotentialVsTime::Serialize(const SEFunctionElectricPotentialVsTime& src, cdm::FunctionElectricPotentialVsTimeData& dst)
{
  SEFunction::Serialize(src, *dst.mutable_functionelectricpotentialvstime());
  dst.mutable_functionelectricpotentialvstime()->set_independentunit(src.m_TimeUnit->GetString());
  dst.mutable_functionelectricpotentialvstime()->set_dependentunit(src.m_ElectricPotentialUnit->GetString());
}

double SEFunctionElectricPotentialVsTime::GetTimeValue(size_t index, const TimeUnit& unit)
{
  if (m_TimeUnit==nullptr)
    throw CommonDataModelException("No time units have been set");
  if (index >= m_Independent.size())
    throw CommonDataModelException("Independent index out of bounds");
  return Convert(m_Independent[index], *m_TimeUnit, unit);
}
std::vector<double>& SEFunctionElectricPotentialVsTime::GetTime()                                  
{
  return m_Independent;
}
const TimeUnit* SEFunctionElectricPotentialVsTime::GetTimeUnit()
{
  return m_TimeUnit;
}
void SEFunctionElectricPotentialVsTime::SetTimeUnit(const TimeUnit& unit)
{
  m_TimeUnit = &unit;
}

double SEFunctionElectricPotentialVsTime::GetElectricPotentialValue(size_t index, const ElectricPotentialUnit& unit)
{
  if (m_ElectricPotentialUnit == nullptr)
    throw CommonDataModelException("No electric potential units have been set");
  if (index >= m_Dependent.size())
    throw CommonDataModelException("Dependent index out of bounds");
  return Convert(m_Dependent[index], *m_ElectricPotentialUnit, unit);
}
std::vector<double>& SEFunctionElectricPotentialVsTime::GetElectricPotential()
{
  return m_Dependent;
}
const ElectricPotentialUnit* SEFunctionElectricPotentialVsTime::GetElectricPotentialUnit()
{
  return m_ElectricPotentialUnit;
}
void SEFunctionElectricPotentialVsTime::SetElectricPotentialUnit(const ElectricPotentialUnit& unit)
{
  m_ElectricPotentialUnit = &unit;
}


//--------------------------------------------------------------------------------------------------
/// \brief
/// Interpolates the original data to match the engine time step
///
/// \param  newTime  vector of the new time values
/// \param  unit    the unit to use when creating the output
///
/// \return the new waveform data
///
/// \details
/// This function creates the new waveform data for the ECG output by interpolating the data from the
/// original file. It inherits m_Independent and m_Dependent from the original data and calls
/// GeneralMath::LinearInterpolator to create the new vector of voltage points that correspond to the 
/// time points in newTime. It is then assigned the unit of the original data and output as the new
/// waveform.
//--------------------------------------------------------------------------------------------------
SEFunctionElectricPotentialVsTime*  SEFunctionElectricPotentialVsTime::InterpolateToTime(std::vector<double>& newTime, const TimeUnit& unit)
{
  if (!IsValid())
    return nullptr;

  SEFunctionElectricPotentialVsTime* newFunction = new SEFunctionElectricPotentialVsTime();
  std::vector<double>& fTime = newFunction->GetTime();
  std::vector<double>& fEleP = newFunction->GetElectricPotential();

  for (double t : newTime)
    fTime.push_back(t);
  newFunction->SetTimeUnit(unit);
  
  //m_Independent;// Original X (Time)
  //m_Dependent;// Original Y (ElectricPotential)
  double x1, x2, y1, y2, xPrime, yPrime;
  unsigned int x1Index = 0;

  for (unsigned int newTimeIterator = 0; newTimeIterator < newTime.size(); newTimeIterator++)
  {
    xPrime = newTime[newTimeIterator]; // new time point
    
    //find x1
    while (x1Index < m_Independent.size() - 2 &&
      GetTimeValue(x1Index + 1, unit) <= xPrime)
    {
      x1Index++;
    }

    // get the points needed for interpolation.
    x1 = GetTimeValue(x1Index, unit);
    x2 = GetTimeValue(x1Index + 1, unit);
    y1 = m_Dependent[x1Index];
    y2 = m_Dependent[x1Index + 1];

    //Shouldn't need this, but just to be sure we don't go beyond the data
    if (xPrime > x2)
    {
      xPrime = x2;
    }

    // call general math function LinearInterpolator to find yPrime at xPrime, xPrime must be between x1 and x2
    yPrime = GeneralMath::LinearInterpolator(x1, x2, y1, y2, xPrime);
    // populate the voltage vector
    fEleP.push_back(yPrime);
  }

  newFunction->SetElectricPotentialUnit(*m_ElectricPotentialUnit); // 

  if (!newFunction->IsValid())
    throw new CommonDataModelException("Could not Interpolate to provided time");
  return newFunction;
}
