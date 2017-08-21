/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
class SESubstanceManager;
PROTO_PUSH
#include "bind/cdm/Conditions.pb.h"
#include "bind/cdm/Scenario.pb.h"
PROTO_POP

class CDM_DECL SECondition : public Loggable
{
public:

  SECondition();
  virtual ~SECondition();
  
  virtual void Clear();// Deletes all members
 
  /** Create a new action based on the binding object, load that data into the new action, and return said action */
  static SECondition* Load(const cdm::AnyConditionData& condition, SESubstanceManager& subMgr);
  /** Create a new bind object, unload the action, put that in the bind object, and return said bind object */
  static cdm::AnyConditionData* Unload(const SECondition& condition);
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
