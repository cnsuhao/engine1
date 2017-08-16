/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
#pragma once
#include "scenario/SEAction.h"
#include "bind/cdm/EnvironmentActions.pb.h"

class CDM_DECL SEEnvironmentAction : public SEAction
{
public:

  SEEnvironmentAction();
  virtual ~SEEnvironmentAction();

  virtual void Clear();

  virtual bool IsValid() const;

  /** Create a new action based on the binding object, load that data into the new action, and return said action */
  static SEEnvironmentAction* Load(const cdm::AnyEnvironmentActionData& any, SESubstanceManager& subMgr);
  /** Create a new bind object, unload the action, put that in the bind object, and return said bind object */
  static cdm::AnyEnvironmentActionData* Unload(const SEEnvironmentAction& action);
protected:
  static void Serialize(const cdm::EnvironmentActionData& src, SEEnvironmentAction& dst);
  static void Serialize(const SEEnvironmentAction& src, cdm::EnvironmentActionData& dst);

public:
  virtual void ToString(std::ostream &str) const = 0;
};  