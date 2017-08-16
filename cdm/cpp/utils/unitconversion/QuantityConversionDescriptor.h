/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

//----------------------------------------------------------------------------
/// @file QuantityConversionDescriptor.h
/// @author Chris Volpe
/// 
/// This class contains a representation of the formula for converting values
/// of one quantity type to values of another quantity type. 
//----------------------------------------------------------------------------
#pragma once

class CQuantityConversionDescriptor
{
public:
  CQuantityConversionDescriptor(double fromExp, const std::string & mappingUnit);

  ~CQuantityConversionDescriptor();

  void Validate(int fromQTID, int toQTID);
  
  const double &GetFromExponent() const
  {
    return m_dFromExponent;
  }

  const CCompoundUnit *GetMappingUnit() const
  {
    return m_CUMappingUnit;
  }

private:
  // What we raise the original quantity to
  double m_dFromExponent;

  // Mapping Unit Identifier
  CCompoundUnit *m_CUMappingUnit;
};