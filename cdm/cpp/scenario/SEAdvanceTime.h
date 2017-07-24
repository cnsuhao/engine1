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

#pragma once
#include "scenario/SEAction.h"

class DLL_DECL SEAdvanceTime : public SEAction
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