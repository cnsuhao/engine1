/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
#pragma once
#include "scenario/SEAction.h"
#include "bind/cdm/AnesthesiaMachineActions.pb.h"
#include "substance/SESubstanceManager.h"

class CDM_DECL SEAnesthesiaMachineAction : public SEAction
{
public:

  SEAnesthesiaMachineAction();
  virtual ~SEAnesthesiaMachineAction();

  virtual void Clear();

  virtual bool IsValid() const;

  /** Create a new action based on the binding object, load that data into the new action, and return said action */
  static SEAnesthesiaMachineAction* Load(const cdm::AnyAnesthesiaMachineActionData& any, SESubstanceManager& subMgr);
  /** Create a new bind object, unload the action, put that in the bind object, and return said bind object */
  static cdm::AnyAnesthesiaMachineActionData* Unload(const SEAnesthesiaMachineAction& action);
protected:
  static void Serialize(const cdm::AnesthesiaMachineActionData& src, SEAnesthesiaMachineAction& dst);
  static void Serialize(const SEAnesthesiaMachineAction& src, cdm::AnesthesiaMachineActionData& dst);

public:
  virtual void ToString(std::ostream &str) const = 0;
};  