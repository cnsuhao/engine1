/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
#pragma once
PROTO_PUSH
#include "bind/cdm/Environment.pb.h"
PROTO_POP

class CDM_DECL SEActiveConditioning : public Loggable
{
public:

  SEActiveConditioning(Logger* logger);
  virtual ~SEActiveConditioning();

  virtual void Clear();
  virtual void Reset();

  static void Load(const cdm::EnvironmentData_ActiveConditioningData& src, SEActiveConditioning& dst);
  static cdm::EnvironmentData_ActiveConditioningData* Unload(const SEActiveConditioning& src);
protected:
  static void Serialize(const cdm::EnvironmentData_ActiveConditioningData& src, SEActiveConditioning& dst);
  static void Serialize(const SEActiveConditioning& src, cdm::EnvironmentData_ActiveConditioningData& dst);

public:

  virtual const SEScalar* GetScalar(const std::string& name);

  virtual bool HasPower() const;
  virtual SEScalarPower& GetPower();
  virtual double GetPower(const PowerUnit& unit) const;

  virtual bool HasSurfaceArea() const;
  virtual SEScalarArea& GetSurfaceArea();
  virtual double GetSurfaceArea(const AreaUnit& unit) const;

  virtual bool HasSurfaceAreaFraction() const;
  virtual SEScalar0To1& GetSurfaceAreaFraction();
  virtual double GetSurfaceAreaFraction() const;

  virtual void ToString(std::ostream &str) const;

protected:
  SEScalarPower*     m_Power;
  SEScalarArea*      m_SurfaceArea;
  SEScalar0To1*      m_SurfaceAreaFraction;
};