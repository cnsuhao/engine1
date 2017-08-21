/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "patient/actions/SEPatientAction.h"

class CDM_DECL SESubstanceAdministration : public SEPatientAction
{
public:

  SESubstanceAdministration();
  virtual ~SESubstanceAdministration();

  virtual void Clear(); //clear memory

  virtual bool IsValid() const;
  virtual bool IsActive() const;

};