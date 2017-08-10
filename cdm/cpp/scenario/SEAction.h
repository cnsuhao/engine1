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
class SESubstanceManager;
#include "bind/cdm/Actions.pb.h"
#include "bind/cdm/Scenario.pb.h"

class CDM_DECL SEAction : public Loggable
{
public:

  SEAction();
  virtual ~SEAction();

  virtual void Clear();// Deletes all members
  
  /** Test if the action has all data it needs */
  virtual bool IsValid() const { return true; }
  /** Actions can be turned off or on with various data combinations
  *  This method will encapsulate that logic in a single function */
  virtual bool IsActive() const { return IsValid(); }

  /** Create a new action based on the binding object, load that data into the new action, and return said action */
  static SEAction* Load(const cdm::AnyActionData& action, SESubstanceManager& subMgr);
  /** Create a new bind object, unload the action, put that in the bind object, and return said bind object */
  static cdm::AnyActionData* Unload(const SEAction& action);
protected:
  static void Serialize(const cdm::ActionData& src, SEAction& dst);
  static void Serialize(const SEAction& src, cdm::ActionData& dst);

public:

  virtual std::string GetComment() const;
  virtual void SetComment(const std::string& comment);
  virtual bool HasComment() const;
  virtual void InvalidateComment();

  virtual void ToString(std::ostream &str)const=0;

protected:

  std::string           m_Comment;
};  

inline std::ostream& operator<< (std::ostream& out, const SEAction& a) 
{
    a.ToString(out);
    return out;
}