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
#include "system/equipment/Anesthesia/actions/SEAnesthesiaMachineAction.h"

class DLL_DECL SEOxygenWallPortPressureLoss : public SEAnesthesiaMachineAction
{
public:
  SEOxygenWallPortPressureLoss();
  virtual ~SEOxygenWallPortPressureLoss();

  virtual void Clear();

  virtual bool IsValid() const;
  virtual bool IsActive() const;
  virtual void SetActive(bool b);

  static void Load(const cdm::OxygenWallPortPressureLossData& src, SEOxygenWallPortPressureLoss& dst);
  static cdm::OxygenWallPortPressureLossData* Unload(const SEOxygenWallPortPressureLoss& src);
protected:
  static void Serialize(const cdm::OxygenWallPortPressureLossData& src, SEOxygenWallPortPressureLoss& dst);
  static void Serialize(const SEOxygenWallPortPressureLoss& src, cdm::OxygenWallPortPressureLossData& dst);

public:

  virtual void ToString(std::ostream &str) const;

protected:
  
  cdm::eSwitch m_State;
};  