/* Distributed under the Apache License, Version 2.0.
See accompanying NOTICE file for details.*/

#pragma once
class SESubstance;
class SESubstanceManager;
class SEEnvironmentalConditions;
PROTO_PUSH
#include "bind/cdm/Substance.pb.h"
PROTO_POP

class CDM_DECL SESubstanceFraction : public Loggable
{
protected:
  friend SEEnvironmentalConditions;// So it can add substances to the manager
public:

  SESubstanceFraction(SESubstance&);
  virtual ~SESubstanceFraction();

  virtual void Clear();

  static void Load(const cdm::SubstanceData_FractionAmountData& src, SESubstanceFraction& dst);
  static cdm::SubstanceData_FractionAmountData* Unload(const SESubstanceFraction& src);
protected:
  static void Serialize(const cdm::SubstanceData_FractionAmountData& src, SESubstanceFraction& dst);
  static void Serialize(const SESubstanceFraction& src, cdm::SubstanceData_FractionAmountData& dst);

public:

  virtual bool HasFractionAmount() const;
  virtual SEScalar0To1& GetFractionAmount();
  virtual double GetFractionAmount() const;

  virtual SESubstance& GetSubstance() const;

protected:

  SESubstance&       m_Substance;
  SEScalar0To1*  m_FractionAmount;
};  