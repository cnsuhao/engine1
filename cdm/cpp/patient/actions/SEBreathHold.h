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
#include "patient/actions/SEConsciousRespirationCommand.h"

class DLL_DECL SEBreathHold : public SEConsciousRespirationCommand
{
  friend class SEConsciousRespiration;
  SEBreathHold();
public:

  virtual ~SEBreathHold();

  virtual void Clear(); //clear memory

  virtual bool IsValid() const;
  virtual bool IsActive() const;

  static void Load(const cdm::ConsciousRespirationData_BreathHoldData& src, SEBreathHold& dst);
  static cdm::ConsciousRespirationData_BreathHoldData* Unload(const SEBreathHold& src);
protected:
	static void Serialize(const cdm::ConsciousRespirationData_BreathHoldData& src, SEBreathHold& dst);
	static void Serialize(const SEBreathHold& src, cdm::ConsciousRespirationData_BreathHoldData& dst);

public:

  virtual bool HasPeriod() const;
  virtual SEScalarTime& GetPeriod();

  virtual void ToString(std::ostream &str) const;
protected:
  SEScalarTime*     m_Period;
};  