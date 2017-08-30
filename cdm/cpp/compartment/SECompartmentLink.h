/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
class SECircuitManager;
CDM_BIND_DECL(CompartmentLinkData);

class CDM_DECL SECompartmentLink : public Loggable
{
protected:
  SECompartmentLink(const std::string& nam, Logger* logger);
public: 
  virtual ~SECompartmentLink();

  virtual void Clear();

protected:
  static void Serialize(const cdm::CompartmentLinkData& src, SECompartmentLink& dst);
  static void Serialize(const SECompartmentLink& src, cdm::CompartmentLinkData& dst);

public:
  virtual std::string GetName() const;

  virtual const SEScalar* GetScalar(const std::string& name) = 0;

protected:
  std::string  m_Name;
};