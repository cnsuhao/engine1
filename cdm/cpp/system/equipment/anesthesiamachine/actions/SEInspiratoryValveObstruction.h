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
#include "system/equipment/anesthesiamachine/actions/SEAnesthesiaMachineAction.h"

class CDM_DECL SEInspiratoryValveObstruction : public SEAnesthesiaMachineAction
{
public:

  SEInspiratoryValveObstruction();
  virtual ~SEInspiratoryValveObstruction();

  virtual void Clear();

  virtual bool IsValid() const;
  virtual bool IsActive() const;

  static void Load(const cdm::InspiratoryValveObstructionData& src, SEInspiratoryValveObstruction& dst);
  static cdm::InspiratoryValveObstructionData* Unload(const SEInspiratoryValveObstruction& src);
protected:
  static void Serialize(const cdm::InspiratoryValveObstructionData& src, SEInspiratoryValveObstruction& dst);
  static void Serialize(const SEInspiratoryValveObstruction& src, cdm::InspiratoryValveObstructionData& dst);

public:

  virtual bool HasSeverity() const;
  virtual SEScalar0To1& GetSeverity();

  virtual void ToString(std::ostream &str) const;

protected:

  SEScalar0To1*     m_Severity;
};  