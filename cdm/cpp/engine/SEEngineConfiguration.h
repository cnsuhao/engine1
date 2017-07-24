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
#include "utils/GeneralMath.h"
#include "engine/SEDynamicStabilization.h"
#include "engine/SETimedStabilization.h"
#include "bind/cdm/Engine.pb.h"


class DLL_DECL SEEngineConfiguration : public Loggable
{
public:

  SEEngineConfiguration(Logger* logger);
  virtual ~SEEngineConfiguration();

  virtual void Clear();

  virtual void Merge(const SEEngineConfiguration& from);

  static void Load(const cdm::EngineConfigurationData& src, SEEngineConfiguration& dst);
  static cdm::EngineConfigurationData* Unload(const SEEngineConfiguration& src);
protected:
  static void Serialize(const cdm::EngineConfigurationData& src, SEEngineConfiguration& dst);
  static void Serialize(const SEEngineConfiguration& src, cdm::EngineConfigurationData& dst);
  virtual void LoadCustomConfig(const google::protobuf::Any& any) {}
  virtual google::protobuf::Any* UnloadCustomConfig() const { return nullptr; }

public:
  virtual bool LoadFile(const std::string& file);

  virtual bool HasTimeStep() const;
  virtual SEScalarTime& GetTimeStep();
  virtual double GetTimeStep(const TimeUnit& unit) const;

  // You can have either a timed or dynamic stabilization object (cannot have both)
  virtual bool HasStabilization() const;
  virtual SEEngineStabilization* GetStabilization();
  virtual void RemoveStabilization();
  // Timed Methods, If you have dynamic, calling GetTimedStabilization will remove the dynamic object
  virtual bool HasTimedStabilization() const;
  virtual SETimedStabilization& GetTimedStabilization();
  virtual const SETimedStabilization* GetTimedStabilization() const;
  virtual void RemoveTimedStabilization();
  // Dynamic Methods, If you have timed, calling GetDynamicStabilization will remove the timed object
  virtual bool HasDynamicStabilization() const;
  virtual SEDynamicStabilization& GetDynamicStabilization();
  virtual const SEDynamicStabilization* GetDynamicStabilization() const;
  virtual void RemoveDynamicStabilization();

protected:
  bool                       m_Merge;

  SEScalarTime*              m_TimeStep;
  SETimedStabilization*      m_TimedStabilization;
  SEDynamicStabilization*    m_DynamicStabilization;
};