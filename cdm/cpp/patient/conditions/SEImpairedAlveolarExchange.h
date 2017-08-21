/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
#pragma once
#include "patient/conditions/SEPatientCondition.h"

class CDM_DECL SEImpairedAlveolarExchange : public SEPatientCondition
{
public:

  SEImpairedAlveolarExchange();
  virtual ~SEImpairedAlveolarExchange();
  
  virtual void Clear();

  virtual bool IsValid() const;

  static void Load(const cdm::ImpairedAlveolarExchangeData& src, SEImpairedAlveolarExchange& dst);
  static cdm::ImpairedAlveolarExchangeData* Unload(const SEImpairedAlveolarExchange& src);
protected:
  static void Serialize(const cdm::ImpairedAlveolarExchangeData& src, SEImpairedAlveolarExchange& dst);
  static void Serialize(const SEImpairedAlveolarExchange& src, cdm::ImpairedAlveolarExchangeData& dst);

public:
  virtual std::string GetName() const { return "ImpairedAlveolarExchange"; }

  virtual bool HasImpairedSurfaceArea() const;
  virtual SEScalarArea& GetImpairedSurfaceArea();
  virtual double GetImpairedSurfaceArea(const AreaUnit& unit) const;

  virtual bool HasImpairedFraction() const;
  virtual SEScalar0To1& GetImpairedFraction();
  virtual double GetImpairedFraction() const;

  virtual void ToString(std::ostream &str) const;

protected:
  
  SEScalarArea*       m_ImpairedSurfaceArea;
  SEScalar0To1*      m_ImpairedFraction;  
};