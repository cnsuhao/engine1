/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

//----------------------------------------------------------------------------
/// @file QuantityConversionKey.h
/// @author Chris Volpe
///

#include "stdafx.h"
#include "utils/unitconversion/UCCommon.h"

CQuantityConversionKey::CQuantityConversionKey(int fromID, int toID)
{
  // Get the dimensions from the associated quantity type IDs
  CUnitConversionEngine &uce = CUnitConversionEngine::GetEngine();
  
  const CQuantityTypeDescriptor &fromType = uce.GetQuantityTypeDescriptor(fromID);
  const CQuantityTypeDescriptor &toType = uce.GetQuantityTypeDescriptor(toID);

  m_CUDfromDim = fromType.GetDimension();
  m_CUDtoDim = toType.GetDimension();

}

// Compute a hash value from an array of the two hash values of the From and
// To Dimension objects
size_t CQuantityConversionKey::hash_value() const
{
  size_t hashes[2] = {m_CUDfromDim->hash_value(), m_CUDtoDim->hash_value()};
  // Use the templated method in <xhash> to compute the hash value for
  // the array
  return _Hash_value(hashes, hashes+2);
}

// override less-than operator to facilitate default hash comparison function
bool CQuantityConversionKey::operator< (const CQuantityConversionKey &rhs) const
{
  // Perform lexicographic comparison, treating From Dimension and
  // To Dimension as a two-letter word

  if (*m_CUDfromDim == *rhs.m_CUDfromDim)
  {
    // let the second half rule
    bool rv1 = *m_CUDtoDim < *rhs.m_CUDtoDim;
    return rv1;
  }
  bool rv2 = *m_CUDfromDim < *rhs.m_CUDfromDim;
  return rv2;
}

bool CQuantityConversionKey::operator== (const CQuantityConversionKey &rhs) const
{
  return ((*m_CUDfromDim == *rhs.m_CUDfromDim) && (*m_CUDtoDim == *rhs.m_CUDtoDim));
}