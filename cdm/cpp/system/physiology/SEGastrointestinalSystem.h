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
#include "system/SESystem.h"
#include "patient/SENutrition.h"
#include "bind/cdm/Physiology.pb.h"

class DLL_DECL SEGastrointestinalSystem : public SESystem
{
public:

  SEGastrointestinalSystem(Logger* logger);
  virtual ~SEGastrointestinalSystem();

  virtual void Clear();// Deletes all members

  virtual const SEScalar* GetScalar(const std::string& name);

  static void Load(const cdm::GastrointestinalSystemData& src, SEGastrointestinalSystem& dst);
  static cdm::GastrointestinalSystemData* Unload(const SEGastrointestinalSystem& src);
protected:
  static void Serialize(const cdm::GastrointestinalSystemData& src, SEGastrointestinalSystem& dst);
  static void Serialize(const SEGastrointestinalSystem& src, cdm::GastrointestinalSystemData& dst);
  
public:
  virtual bool HasChymeAbsorbtionRate() const;
  virtual SEScalarVolumePerTime& GetChymeAbsorbtionRate();
  virtual double GetChymeAbsorbtionRate(const VolumePerTimeUnit& unit) const;

  virtual bool HasStomachContents() const;
  virtual SENutrition& GetStomachContents();
  virtual const SENutrition* GetStomachContents() const;
  virtual void RemoveStomachContents();

protected:

  SEScalarVolumePerTime* m_ChymeAbsorbtionRate;
  SENutrition* m_StomachContents;
};
