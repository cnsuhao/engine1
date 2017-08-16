/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "utils/DataPeak.h"

DataPeak::DataPeak(unsigned int samples, double epsilon)
{    
  m_Samples=samples;
  m_Epsilon=epsilon;
  m_FindMax = true;
  m_FindMin = false;
  Reset();
}

void DataPeak::Reset()
{
  m_PeakCount      = 0;
  m_SamplePeak     = 0;
  m_LastTopPeak    = 0;
  m_LastBottomPeak = 0;  
  m_PositiveTrend  = true;
}

double DataPeak::LastTopPeak()
{
  return m_LastTopPeak;
}

double DataPeak::LastBottomPeak()
{
  return m_LastBottomPeak;
}

bool DataPeak::Peaked(double value)
{
  if(m_PositiveTrend)
  {
    double p = m_SamplePeak-m_Epsilon;
    if(value<p)
    {
      // We may want to move the window to extend
      // over the down trending point-epsilon to enforce
      // the data is actually trending down.
      // Make sure the data is moving below a moving window
      // Currently the window stays at the peak
      // But you could get a plateau below the window
      // then another peak
      //                  .--.   
      //        peak     /    \
      //       .--      .
      // ----./---\..../-------window
      //   ./
      m_PeakCount++;
      if(m_PeakCount==m_Samples)
      {
        m_PeakCount=0;
        m_LastTopPeak = m_SamplePeak;        
        m_SamplePeak=value;
        m_PositiveTrend=false;
        return m_FindMax?true:false;
      }
    }
    else if(value>=p&&value<=m_SamplePeak)
    {
      // Do Nothing, in limbo right now...
    }
    else
    {
      m_PeakCount=0;
      m_SamplePeak=value;
    }
  }
  else
  {
    double p = m_SamplePeak+m_Epsilon;
    if(value>p)
    {
      m_PeakCount++;
      if(m_PeakCount==m_Samples)
      {
        m_PeakCount=0;
        m_LastBottomPeak = m_SamplePeak;
        m_SamplePeak=value;
        m_PositiveTrend=true;
        return m_FindMin?true:false;
      }
    }
    else if(value<=p&&value>=m_SamplePeak)
    {
      // Do Nothing, in limbo right now...
    }
    else
    {
      m_PeakCount=0;
      m_SamplePeak=value;
    }
  }
  return false;
}
