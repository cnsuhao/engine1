/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
#pragma once
#include "bind/cdm/Environment.pb.h"

class CDM_DECL SEAppliedTemperature : public Loggable
{
public:

  SEAppliedTemperature(Logger* logger);
  virtual ~SEAppliedTemperature();
  
  virtual void Clear();

  static void Load(const cdm::EnvironmentData_AppliedTemperatureData& src, SEAppliedTemperature& dst);
  static cdm::EnvironmentData_AppliedTemperatureData* Unload(const SEAppliedTemperature& src);
protected:
  static void Serialize(const cdm::EnvironmentData_AppliedTemperatureData& src, SEAppliedTemperature& dst);
  static void Serialize(const SEAppliedTemperature& src, cdm::EnvironmentData_AppliedTemperatureData& dst);

public:

  virtual const SEScalar* GetScalar(const std::string& name);

  virtual bool HasTemperature() const;
  virtual SEScalarTemperature& GetTemperature();
  virtual double GetTemperature(const TemperatureUnit& unit) const;

  virtual bool HasSurfaceArea() const;
  virtual SEScalarArea& GetSurfaceArea();
  virtual double GetSurfaceArea(const AreaUnit& unit) const;

  virtual bool HasSurfaceAreaFraction() const;
  virtual SEScalar0To1& GetSurfaceAreaFraction();
  virtual double GetSurfaceAreaFraction() const;

  virtual cdm::eSwitch GetState() const;
  virtual void SetState(cdm::eSwitch onOff);

  virtual void ToString(std::ostream &str) const;

protected:
  
  SEScalarTemperature*   m_Temperature;
  SEScalarArea*           m_SurfaceArea;
  SEScalar0To1*      m_SurfaceAreaFraction;
  cdm::eSwitch  m_State;
};