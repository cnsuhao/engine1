/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "properties/SEProperty.h"
#include "utils/unitconversion/UCCommon.h"
#include "bind/cdm/Properties.pb.h"

class CDM_DECL SEHistogram : public SEProperty
{
public:

  SEHistogram();
  virtual ~SEHistogram();

  virtual void Clear(); //clear memory

  static void Load(const cdm::HistogramData& src, SEHistogram& dst);
  static cdm::HistogramData* Unload(const SEHistogram& src);
protected:
  static void Serialize(const cdm::HistogramData& src, SEHistogram& dst);
  static void Serialize(const SEHistogram& src, cdm::HistogramData& dst);
public:
  virtual bool                          IsValid() const;
  virtual void                          Invalidate();

  virtual size_t                        NumberOfBins() const;
  virtual size_t                        NumberOfBoundaries() const;
  
  double                                GetDependentValue(size_t index) const;
  std::vector<double>&                  GetDependent();      
  const std::vector<double>&            GetDependent() const;

  double                                GetIndependentValue(size_t index) const;
  std::vector<double>&                  GetIndependent();
  const std::vector<double>&            GetIndependent() const;
  
protected:

  std::vector<double> m_Dependent;
  std::vector<double> m_Independent;
};