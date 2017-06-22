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

class DLL_DECL SEHepaticSystem : public SESystem
{
public:

  SEHepaticSystem(Logger* logger);
  virtual ~SEHepaticSystem();

  virtual void Clear();// Deletes all members
  
  virtual const SEScalar* GetScalar(const std::string& name);
  
  static void Load(const cdm::HepaticSystemData& src, SEHepaticSystem& dst);
  static cdm::HepaticSystemData* Unload(const SEHepaticSystem& src);
protected:
  static void Serialize(const cdm::HepaticSystemData& src, SEHepaticSystem& dst);
  static void Serialize(const SEHepaticSystem& src, cdm::HepaticSystemData& dst);
public:

  
protected:

  
};