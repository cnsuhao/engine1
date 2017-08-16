/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

//----------------------------------------------------------------------------
/// @file CompoundUnitElement.cpp
/// @author Chris Volpe
//----------------------------------------------------------------------------
#include "stdafx.h"
#include "utils/unitconversion/UCCommon.h"

//----------------------------------------------------------------------------
double CCompoundUnitElement::GetBigness() const
{
  static CUnitConversionEngine &uce = CUnitConversionEngine::GetEngine();
  double dPrefixFac = 1.0;
  if (m_iPrefixID != -1)
  {
    const CPrefixDescriptor &pd(uce.GetPrefixDescriptor(m_iPrefixID));
    dPrefixFac = pd.GetScaleFactor();
  }

  const CUnitDescriptor &ud = uce.GetUnitDescriptor(m_iUnitID);

  // Combine the unit's conversion factor and prefix, and then
  // the exponent
  double dBigness = (ud.GetConvFac() * dPrefixFac);
  return pow(dBigness,m_CExponent);
}  

//----------------------------------------------------------------------------
double CCompoundUnitElement::GetBias() const
{
  static CUnitConversionEngine &uce = CUnitConversionEngine::GetEngine();
  const CUnitDescriptor &ud = uce.GetUnitDescriptor(m_iUnitID);
  return ud.GetBias();
}

//----------------------------------------------------------------------------
bool CCompoundUnitElement::IsDecibel() const
{
  static CUnitConversionEngine &uce = CUnitConversionEngine::GetEngine();
  const CUnitDescriptor &ud = uce.GetUnitDescriptor(m_iUnitID);
  return ud.IsDecibel();
}