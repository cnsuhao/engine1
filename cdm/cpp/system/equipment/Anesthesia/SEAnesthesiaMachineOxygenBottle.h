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
class SEAnesthesiaMachine;
class SESubstanceManager;
#include "bind/cdm/AnesthesiaMachine.pb.h"

class DLL_DECL SEAnesthesiaMachineOxygenBottle : Loggable
{
protected:
  friend SEAnesthesiaMachine;
public:

  SEAnesthesiaMachineOxygenBottle(Logger* logger);
  virtual ~SEAnesthesiaMachineOxygenBottle();

  virtual void Clear();

  static void Load(const cdm::AnesthesiaMachineData_OxygenBottleData& src, SEAnesthesiaMachineOxygenBottle& dst);
  static cdm::AnesthesiaMachineData_OxygenBottleData* Unload(const SEAnesthesiaMachineOxygenBottle& src);
protected:
  static void Serialize(const cdm::AnesthesiaMachineData_OxygenBottleData& src, SEAnesthesiaMachineOxygenBottle& dst);
  static void Serialize(const SEAnesthesiaMachineOxygenBottle& src, cdm::AnesthesiaMachineData_OxygenBottleData& dst);

  virtual void Merge(const SEAnesthesiaMachineOxygenBottle& from);
public:

  virtual const SEScalar* GetScalar(const std::string& name);

  virtual bool HasVolume() const;
  virtual SEScalarVolume& GetVolume();
  virtual double GetVolume(const VolumeUnit& unit) const;

  virtual void ToString(std::ostream &str);

protected:

  SEScalarVolume*     m_Volume;

};
