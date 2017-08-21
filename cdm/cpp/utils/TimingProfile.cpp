/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "TimingProfile.h"

void TimingProfile::Clear()
{
  m_timers.clear();
}

void TimingProfile::Reset(const std::string& label)
{
  if (label.empty())
  {
    return;
  }
  if (m_timers[label].state == State::Running)
  {
    m_timers[label].start = Clock::now();
  }
  else if (m_timers[label].state == State::Ran)
  {
    m_timers[label].state = State::Ready;
  }

  m_ss << "TimingProfile:Reset:" << label << std::ends;
  Debug(m_ss);
}

void TimingProfile::Start(const std::string& label)
{
  if (label.empty())
  {
    return;
  }

  m_timers[label].start = Clock::now();
  m_timers[label].state = State::Running;

  m_ss << "TimingProfile:Start:" << label << std::ends;
  Debug(m_ss);
}

void TimingProfile::Stop(const std::string& label)
{
  if (label.empty())
  {
    return;
  }

  if (m_timers[label].state == State::Running)
  {
    m_timers[label].end = Clock::now();
    m_timers[label].state = State::Ran;
  }

  m_ss << "TimingProfile:Stop:" << label << std::ends;
  Debug(m_ss);
}

double TimingProfile::GetElapsedTime_s(const std::string& label)
{
  if (label.empty())
  {
    return 0;
  }

  std::chrono::milliseconds::rep milliseconds = GetElapsedTime<std::chrono::milliseconds>(label);
  double seconds = milliseconds / 1000.0;

  m_ss << "TimingProfile:Profile:" << label << ":" << seconds << "s" << std::ends;
  Debug(m_ss);

  return seconds;
}

void TimingProfile::Print(const std::string& label)
{
  if (label.empty())
  {
    for (const std::pair<std::string, Timer>& timerPair : m_timers)
    {
      if (timerPair.second.state != State::Ready)
      {
        std::cout << "TimingProfile:Elapsed:" << timerPair.first << ":" << GetElapsedTime_s(timerPair.first) << std::endl;
      }
    }
  }
  else
  {
    std::cout << "TimingProfile:Elapsed:" << label << ":" << GetElapsedTime_s(label) << "s" << std::endl;
  }
}