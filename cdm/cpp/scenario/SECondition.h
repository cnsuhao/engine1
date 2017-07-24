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
#include "bind/cdm/Conditions.pb.h"

class DLL_DECL SECondition : public Loggable
{
public:

  SECondition();
  virtual ~SECondition();
  
  virtual void Clear();// Deletes all members
 
  static SECondition* newFromBind(const cdm::ConditionData& condition, SESubstanceManager& substances);

  static void Load(const cdm::ConditionData& src, SECondition& dst);
  static cdm::ConditionData* Unload(const SECondition& src);
protected:
  static void Serialize(const cdm::ConditionData& src, SECondition& dst);
  static void Serialize(const SECondition& src, cdm::ConditionData& dst);

public:
  /** Test if the Condition has all data it needs */
  virtual bool IsValid() const { return true; }

  virtual std::string GetName() const = 0;

  virtual std::string GetComment() const;
  virtual void SetComment(const std::string& comment);
  virtual bool HasComment()const;
  virtual void InvalidateComment();

  virtual void ToString(std::ostream &str) const=0;

protected:

  std::string  m_Comment;
};  

inline std::ostream& operator<< (std::ostream& out, const SECondition& a) 
{
    a.ToString(out);
    return out;
}
