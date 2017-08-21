/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "patient/conditions/SEChronicHeartFailure.h"

SEChronicHeartFailure::SEChronicHeartFailure() : SEPatientCondition()
{
}

SEChronicHeartFailure::~SEChronicHeartFailure()
{
  Clear();
}

void SEChronicHeartFailure::Clear()
{
  SEPatientCondition::Clear();
}

bool SEChronicHeartFailure::IsValid() const
{
  return SEPatientCondition::IsValid();
}


