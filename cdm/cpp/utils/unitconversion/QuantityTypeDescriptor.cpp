/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

//----------------------------------------------------------------------------
/// @file QuantityTypeDescriptor.cpp
/// @author Chris Volpe
//----------------------------------------------------------------------------
#include "stdafx.h"
#include "utils/unitconversion/UCCommon.h"

//----------------------------------------------------------------------------
CQuantityTypeDescriptor::CQuantityTypeDescriptor(const std::string &name, int fundIdx, bool twentyLog)
: m_sName(name), m_iFundIdx(fundIdx), m_CUExpansion(nullptr),m_bTwentyLogRule(twentyLog)
{  
  // This ctor is for fundamental quantities, and the bigness is 1.0 by definition.
  m_dBigness = 1.0;
  m_CUD = new CUnitDimension();
  (*m_CUD)[m_iFundIdx] = 1.0;
}

//----------------------------------------------------------------------------
CQuantityTypeDescriptor::CQuantityTypeDescriptor(const std::string &name, CCompoundUnit *expansion, bool twentyLog)
: m_sName(name), m_iFundIdx(-1), m_CUExpansion(expansion), m_bTwentyLogRule(twentyLog)
{
  // By convention, when the engine hands expansion to us, we own it. So we'll free it
  // in our dtor
  // This ctor is for derived quantities, and the bigness is that of the expansion.
  m_dBigness = m_CUExpansion->GetBigness();
  // Copy our expansion's dimension. Since the other constructors allocate their
  // own, we can't simply copy the pointer from our expansion
  m_CUD = new CUnitDimension(*m_CUExpansion->GetDimension());
}


//----------------------------------------------------------------------------
CQuantityTypeDescriptor::~CQuantityTypeDescriptor()
{
  if (m_CUExpansion)
  {
    delete m_CUExpansion;
  }
  delete m_CUD;
}