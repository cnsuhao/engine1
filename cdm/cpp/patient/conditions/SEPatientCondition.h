/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "scenario/SECondition.h"
#include "bind/cdm/PatientConditions.pb.h"

class CDM_DECL SEPatientCondition : public SECondition
{
public:

  SEPatientCondition();
  virtual ~SEPatientCondition();

  virtual void Clear(); //clear memory

  virtual bool IsValid() const = 0;

  /** Create a new condition based on the binding object, load that data into the new condition, and return said condition */
  static SEPatientCondition* Load(const cdm::AnyPatientConditionData& any, SESubstanceManager& subMgr);
  /** Create a new bind object, unload the action, put that in the bind object, and return said bind object */
  static cdm::AnyPatientConditionData* Unload(const SEPatientCondition& condition);
protected:
  static void Serialize(const cdm::PatientConditionData& src, SEPatientCondition& dst);
  static void Serialize(const SEPatientCondition& src, cdm::PatientConditionData& dst);

public:
  virtual void ToString(std::ostream &str) const = 0;
  
};  