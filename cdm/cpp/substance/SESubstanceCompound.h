/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
class SESubstance;
class SESubstanceManager;
class SESubstanceConcentration;
#include "bind/cdm/Substance.pb.h"

class CDM_DECL SESubstanceCompound : public Loggable
{
public:

  SESubstanceCompound(Logger* logger);
  virtual ~SESubstanceCompound();

  virtual void Clear();

  static void Load(const cdm::SubstanceData_CompoundData& src, SESubstanceCompound& dst, const SESubstanceManager& subMgr);
  static cdm::SubstanceData_CompoundData* Unload(const SESubstanceCompound& src);
protected:
  static void Serialize(const cdm::SubstanceData_CompoundData& src, SESubstanceCompound& dst, const SESubstanceManager& subMgr);
  static void Serialize(const SESubstanceCompound& src, cdm::SubstanceData_CompoundData& dst);

public:
  virtual std::string GetName() const;
  virtual void SetName(const std::string& name);
  virtual bool HasName() const;
  virtual void InvalidateName();

  bool HasComponent() const;
  bool HasComponent(const SESubstance& substance) const;
  const std::vector<SESubstanceConcentration*>& GetComponents();  
  const std::vector<const SESubstanceConcentration*>& GetComponents() const;
  const SESubstanceConcentration& GetComponent(SESubstance& substance);
  const SESubstanceConcentration* GetComponent(SESubstance& substance) const;
  void RemoveComponent(const SESubstance& substance);

protected: 

  std::string m_Name;

  std::vector<SESubstanceConcentration*>       m_Components;
  std::vector<const SESubstanceConcentration*> m_cComponents;
};