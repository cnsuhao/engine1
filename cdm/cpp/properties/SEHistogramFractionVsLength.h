/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "properties/SEHistogram.h"

class CDM_DECL SEHistogramFractionVsLength : public SEHistogram
{
public:

  SEHistogramFractionVsLength();
  virtual ~SEHistogramFractionVsLength();

  virtual void Clear();

  virtual bool IsVaild() const;

  static void Load(const cdm::HistogramFractionVsLengthData& src, SEHistogramFractionVsLength& dst);
  static cdm::HistogramFractionVsLengthData* Unload(const SEHistogramFractionVsLength& src);
protected:
  static void Serialize(const cdm::HistogramFractionVsLengthData& src, SEHistogramFractionVsLength& dst);
  static void Serialize(const SEHistogramFractionVsLength& src, cdm::HistogramFractionVsLengthData& dst);
public:

  virtual double                     GetFractionValue(size_t index) const;
  virtual std::vector<double>&       GetFraction();
  virtual const std::vector<double>& GetFraction() const;
  
  virtual double                     GetLengthValue(size_t index, const LengthUnit& unit)  const;
  virtual std::vector<double>&       GetLength();
  virtual const std::vector<double>& GetLength() const;
  virtual const LengthUnit*          GetLengthUnit()  const;
  virtual void                       SetLengthUnit(const LengthUnit& unit);

protected:
  const LengthUnit* m_LengthUnit;
};