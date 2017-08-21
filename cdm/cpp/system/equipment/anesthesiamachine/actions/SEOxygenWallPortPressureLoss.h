/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
#pragma once
#include "system/equipment/anesthesiamachine/actions/SEAnesthesiaMachineAction.h"

class CDM_DECL SEOxygenWallPortPressureLoss : public SEAnesthesiaMachineAction
{
public:
  SEOxygenWallPortPressureLoss();
  virtual ~SEOxygenWallPortPressureLoss();

  virtual void Clear();

  virtual bool IsValid() const;
  virtual bool IsActive() const;
  virtual void SetActive(bool b);

  static void Load(const cdm::OxygenWallPortPressureLossData& src, SEOxygenWallPortPressureLoss& dst);
  static cdm::OxygenWallPortPressureLossData* Unload(const SEOxygenWallPortPressureLoss& src);
protected:
  static void Serialize(const cdm::OxygenWallPortPressureLossData& src, SEOxygenWallPortPressureLoss& dst);
  static void Serialize(const SEOxygenWallPortPressureLoss& src, cdm::OxygenWallPortPressureLossData& dst);

public:

  virtual void ToString(std::ostream &str) const;

protected:
  
  cdm::eSwitch m_State;
};  