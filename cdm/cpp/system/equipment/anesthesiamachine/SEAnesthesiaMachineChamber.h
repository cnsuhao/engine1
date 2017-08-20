/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
class SESubstance;
class SESubstanceManager;
class SEAnesthesiaMachine;
PROTO_PUSH
#include "bind/cdm/AnesthesiaMachine.pb.h"
PROTO_POP

class CDM_DECL SEAnesthesiaMachineChamber : Loggable
{
protected:
  friend SEAnesthesiaMachine;
public:

  SEAnesthesiaMachineChamber(SESubstanceManager& substances);
  virtual ~SEAnesthesiaMachineChamber();

  virtual void Clear();

  static void Load(const cdm::AnesthesiaMachineData_ChamberData& src, SEAnesthesiaMachineChamber& dst);
  static cdm::AnesthesiaMachineData_ChamberData* Unload(const SEAnesthesiaMachineChamber& src);
protected:
  static void Serialize(const cdm::AnesthesiaMachineData_ChamberData& src, SEAnesthesiaMachineChamber& dst);
  static void Serialize(const SEAnesthesiaMachineChamber& src, cdm::AnesthesiaMachineData_ChamberData& dst);

  virtual void Merge(const SEAnesthesiaMachineChamber& from);
public:

  virtual const SEScalar* GetScalar(const std::string& name);

  virtual cdm::eSwitch GetState() const;
  virtual void SetState(cdm::eSwitch s);

  virtual bool HasSubstanceFraction() const;
  virtual SEScalar0To1& GetSubstanceFraction();
  virtual double GetSubstanceFraction() const;

  virtual bool HasSubstance() const;
  virtual SESubstance* GetSubstance() const;
  virtual void SetSubstance(const SESubstance& substance);
  virtual void RemoveSubstance();

  virtual void ToString(std::ostream &str) const;

protected:

  cdm::eSwitch          m_State;
  const SESubstance*    m_Substance;
  SEScalar0To1*         m_SubstanceFraction;

  SESubstanceManager&   m_Substances;
};
