/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "properties/SEProperty.h"
#include "utils/unitconversion/UCCommon.h"
#include "bind/cdm/Properties.pb.h"

class CDM_DECL SEFunction : public SEProperty
{
public:

  SEFunction();
  virtual ~SEFunction();

  virtual void Clear(); //clear memory

  static void Load(const cdm::FunctionData& src, SEFunction& dst);
  static cdm::FunctionData* Unload(const SEFunction& src);
protected:
  static void Serialize(const cdm::FunctionData& src, SEFunction& dst);
  static void Serialize(const SEFunction& src, cdm::FunctionData& dst);

public:
  virtual bool                          IsValid() const;
  virtual void                          Invalidate();

  virtual size_t                        Length();
  
  double                                GetDependentValue(size_t index);
  std::vector<double>&                  GetDependent();      

  double                                GetIndependentValue(size_t index);
  std::vector<double>&                  GetIndependent();
  
protected:

  std::vector<double> m_Dependent;
  std::vector<double> m_Independent;
};