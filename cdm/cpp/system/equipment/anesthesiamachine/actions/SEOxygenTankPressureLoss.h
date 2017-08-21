/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
#pragma once
#include "system/equipment/anesthesiamachine/actions/SEAnesthesiaMachineAction.h"

class CDM_DECL SEOxygenTankPressureLoss : public SEAnesthesiaMachineAction
{
public:
  SEOxygenTankPressureLoss();
  virtual ~SEOxygenTankPressureLoss();

  virtual void Clear();

  virtual bool IsValid() const;
  virtual bool IsActive() const;
  virtual void SetActive(bool b);

  static void Load(const cdm::OxygenTankPressureLossData& src, SEOxygenTankPressureLoss& dst);
  static cdm::OxygenTankPressureLossData* Unload(const SEOxygenTankPressureLoss& src);
protected:
  static void Serialize(const cdm::OxygenTankPressureLossData& src, SEOxygenTankPressureLoss& dst);
  static void Serialize(const SEOxygenTankPressureLoss& src, cdm::OxygenTankPressureLossData& dst);

public:

  virtual void ToString(std::ostream &str) const;

protected:
  
  cdm::eSwitch m_State;
};  