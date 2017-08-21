/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "patient/conditions/SEPatientCondition.h"

class CDM_DECL SEChronicHeartFailure : public SEPatientCondition
{
public:

  SEChronicHeartFailure();
  virtual ~SEChronicHeartFailure();

  virtual void Clear(); //clear memory

  virtual bool IsValid() const;

public:
  virtual void ToString(std::ostream &str) const = 0;

protected:
};    