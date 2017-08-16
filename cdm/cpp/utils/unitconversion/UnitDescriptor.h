/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

//----------------------------------------------------------------------------
/// @file UnitDescriptor.h
/// @author Chris Volpe
///
/// This class encapsulates the definition of a particular unit symbol
//----------------------------------------------------------------------------
#pragma once

class CUnitDescriptor
{
public:
  // Defines what kind of constraint we impose on prefixes for this unit.
  typedef enum {NONE, SOME, ALLBUT, ALL} PrefixModeType;

  // ctor
  CUnitDescriptor(const std::string &name, const std::string &symbol, unsigned int quantityTypeId, const std::string &targetUnit,
    const double &convFac, const double &bias, PrefixModeType mode, const std::string &prefixSet);
  
  bool IsPrefixAllowed(char prefix) const;

  const double & GetConvFac() const
  {
    return m_dConvFac;
  }

  const double & GetBias() const
  {
    return m_dBias;
  }

  const std::string &GetName() const
  {
    return m_strName;
  }

  const std::string &GetSymbol() const
  {
    return m_strSymbol;
  }

  unsigned int GetQuantityTypeID() const
  {
    return m_uiQuantityTypeId;
  }

  bool IsDecibel() const
  {
    return m_bDBFlag;
  }

private:
  double m_dConvFac;
  double m_dBias;
  std::string m_strName;
  std::string m_strSymbol;
  unsigned int m_uiQuantityTypeId;
  PrefixModeType m_uiPrefixMode;
  std::string m_strPrefixSet;
  bool m_bDBFlag;

};