/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
#pragma once
#include "system/equipment/anesthesiamachine/actions/SEAnesthesiaMachineAction.h"

class CDM_DECL SEVentilatorPressureLoss : public SEAnesthesiaMachineAction
{
public:

  SEVentilatorPressureLoss();
  virtual ~SEVentilatorPressureLoss();

  virtual void Clear();

  virtual bool IsValid() const;
  virtual bool IsActive() const;

  static void Load(const cdm::VentilatorPressureLossData& src, SEVentilatorPressureLoss& dst);
  static cdm::VentilatorPressureLossData* Unload(const SEVentilatorPressureLoss& src);
protected:
  static void Serialize(const cdm::VentilatorPressureLossData& src, SEVentilatorPressureLoss& dst);
  static void Serialize(const SEVentilatorPressureLoss& src, cdm::VentilatorPressureLossData& dst);

public:
  
  virtual bool HasSeverity() const;
  virtual SEScalar0To1& GetSeverity();

  virtual void ToString(std::ostream &str) const;

protected:

  SEScalar0To1*     m_Severity;
};  