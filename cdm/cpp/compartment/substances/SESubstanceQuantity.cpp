/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"

#include "compartment/substances/SESubstanceQuantity.h"
#include "substance/SESubstance.h"

void SESubstanceQuantity::Serialize(const cdm::SubstanceQuantityData& src, SESubstanceQuantity& dst)
{
  dst.Clear();
  // Name will be used to get substance for ctor
}
void SESubstanceQuantity::Serialize(const SESubstanceQuantity& src, cdm::SubstanceQuantityData& dst)
{
  dst.set_substance(src.m_Substance.GetName());
}
