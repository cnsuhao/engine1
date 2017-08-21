/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
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