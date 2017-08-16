/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "patient/actions/SEChestCompression.h"

SEChestCompression::SEChestCompression() : SEPatientAction()
{

}

SEChestCompression::~SEChestCompression()
{
  Clear();
}

void SEChestCompression::Clear()
{
  SEPatientAction::Clear();
}

bool SEChestCompression::IsValid() const
{
  return SEPatientAction::IsValid();
}

bool SEChestCompression::IsActive() const
{
  return IsValid();
}
