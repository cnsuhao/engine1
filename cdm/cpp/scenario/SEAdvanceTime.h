/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "scenario/SEAction.h"

class CDM_DECL SEAdvanceTime : public SEAction
{
public:

  SEAdvanceTime();
  virtual ~SEAdvanceTime();

  virtual void Clear(); //clear memory

  virtual bool IsValid() const;

  static void Load(const cdm::AdvanceTimeData& src, SEAdvanceTime& dst);
  static cdm::AdvanceTimeData* Unload(const SEAdvanceTime& src);
protected:
  static void Serialize(const cdm::AdvanceTimeData& src, SEAdvanceTime& dst);
  static void Serialize(const SEAdvanceTime& src, cdm::AdvanceTimeData& dst);

public:

  virtual void ToString(std::ostream &str) const;

  virtual bool HasTime() const;
  virtual SEScalarTime& GetTime();
  virtual double GetTime(const TimeUnit& unit) const;

protected:

  SEScalarTime *m_Time;
};                  