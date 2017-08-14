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
#include "bind/cdm/InhalerActions.pb.h"
#include "substance/SESubstanceManager.h"

class CDM_DECL SEInhalerAction : public SEAction
{
public:

  SEInhalerAction();
  virtual ~SEInhalerAction();

  virtual void Clear();// Deletes all members
  
  virtual bool IsValid() const;

  /** Create a new action based on the binding object, load that data into the new action, and return said action */
  static SEInhalerAction* Load(const cdm::AnyInhalerActionData& any, SESubstanceManager& subMgr);
  /** Create a new bind object, unload the action, put that in the bind object, and return said bind object */
  static cdm::AnyInhalerActionData* Unload(const SEInhalerAction& action);
protected:
  static void Serialize(const cdm::InhalerActionData& src, SEInhalerAction& dst);
  static void Serialize(const SEInhalerAction& src, cdm::InhalerActionData& dst);

public:
  virtual void ToString(std::ostream &str) const = 0;
};  