/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "system/SESystem.h"
#include "bind/cdm/Physiology.pb.h"

class CDM_DECL SEEndocrineSystem : public SESystem
{
public:

  SEEndocrineSystem(Logger* logger);
  virtual ~SEEndocrineSystem();

  virtual void Clear();// Deletes all members
  
  virtual const SEScalar* GetScalar(const std::string& name);
  
  static void Load(const cdm::EndocrineSystemData& src, SEEndocrineSystem& dst);
  static cdm::EndocrineSystemData* Unload(const SEEndocrineSystem& src);
protected:
  static void Serialize(const cdm::EndocrineSystemData& src, SEEndocrineSystem& dst);
  static void Serialize(const SEEndocrineSystem& src, cdm::EndocrineSystemData& dst);

public:

  virtual bool HasInsulinSynthesisRate() const;
  virtual SEScalarAmountPerTime& GetInsulinSynthesisRate();
  virtual double GetInsulinSynthesisRate(const AmountPerTimeUnit& unit) const;

protected:

  SEScalarAmountPerTime* m_InsulinSynthesisRate;

};
