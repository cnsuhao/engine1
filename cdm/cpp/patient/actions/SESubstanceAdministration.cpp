/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "patient/actions/SESubstanceAdministration.h"

SESubstanceAdministration::SESubstanceAdministration() : SEPatientAction()
{
}

SESubstanceAdministration::~SESubstanceAdministration()
{
  Clear();
}

void SESubstanceAdministration::Clear()
{
  SEPatientAction::Clear();
}

bool SESubstanceAdministration::IsValid() const
{
  return SEPatientAction::IsValid();
}

bool SESubstanceAdministration::IsActive() const
{
  return IsValid();
}