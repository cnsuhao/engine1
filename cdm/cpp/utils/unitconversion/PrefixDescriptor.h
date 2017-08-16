/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

//----------------------------------------------------------------------------
/// @file PrefixDescriptor.h
/// @author Chris Volpe
/// 
/// This class defines a representation of a prefix that can be applied to a
/// unit symbol
//----------------------------------------------------------------------------
#pragma once

class CPrefixDescriptor
{
public:
  CPrefixDescriptor(std::string name, std::string sym, double scaleFac) :
    m_strName(name), m_cSym(sym[0]), m_dScaleFac(scaleFac)
    {
      // All done already
    }

    CPrefixDescriptor(std::string name, char sym, double scaleFac) :
    m_strName(name), m_cSym(sym), m_dScaleFac(scaleFac)
    {
      // All done already
    }

  const std::string &GetName() const
  {
    return m_strName;
  };

  char GetSymbol() const
  {
    return m_cSym;
  }

  double GetScaleFactor() const
  {
    return m_dScaleFac;
  }

private:
  std::string m_strName;
  char m_cSym;
  double m_dScaleFac;
};