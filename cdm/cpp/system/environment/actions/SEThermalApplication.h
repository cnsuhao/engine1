/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
#pragma once
#include "system/environment/actions/SEEnvironmentAction.h"
#include "system/environment/SEActiveConditioning.h"
#include "system/environment/SEAppliedTemperature.h"

class CDM_DECL SEThermalApplication : public SEEnvironmentAction
{
public:

  SEThermalApplication();
  virtual ~SEThermalApplication();

  virtual void Clear();

  virtual bool IsValid() const;
  virtual bool IsActive() const;

  static void Load(const cdm::ThermalApplicationData& src, SEThermalApplication& dst);
  static cdm::ThermalApplicationData* Unload(const SEThermalApplication& src);
protected:
  static void Serialize(const cdm::ThermalApplicationData& src, SEThermalApplication& dst);
  static void Serialize(const SEThermalApplication& src, cdm::ThermalApplicationData& dst);

public:

  virtual bool HasActiveHeating() const;
  virtual SEActiveConditioning& GetActiveHeating();
  virtual void RemoveActiveHeating();

  virtual bool HasActiveCooling() const;
  virtual SEActiveConditioning& GetActiveCooling();
  virtual void RemoveActiveCooling();

  virtual bool HasAppliedTemperature() const;
  virtual SEAppliedTemperature& GetAppliedTemperature();
  virtual void RemoveAppliedTemperature();

  virtual void ToString(std::ostream &str) const;

protected:
  bool                   m_ClearContents;
  SEActiveConditioning*  m_ActiveHeating;
  SEActiveConditioning*  m_ActiveCooling;
  SEAppliedTemperature*  m_AppliedTemperature;
};