/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "scenario/SEAction.h"
CDM_BIND_DECL(PatientActionData)

class CDM_DECL SEPatientAction : public SEAction
{
public:

  SEPatientAction();
  virtual ~SEPatientAction();

  virtual void Clear(); //clear memory

  virtual bool IsValid() const;

  /** Create a new action based on the binding object, load that data into the new action, and return said action */
  static SEPatientAction* Load(const cdm::AnyPatientActionData& any, SESubstanceManager& subMgr);
  /** Create a new bind object, unload the action, put that in the bind object, and return said bind object */
  static cdm::AnyPatientActionData* Unload(const SEPatientAction& action);
protected:
  static void Serialize(const cdm::PatientActionData& src, SEPatientAction& dst);
  static void Serialize(const SEPatientAction& src, cdm::PatientActionData& dst);

public:
  virtual void ToString(std::ostream &str) const = 0;
  
};  