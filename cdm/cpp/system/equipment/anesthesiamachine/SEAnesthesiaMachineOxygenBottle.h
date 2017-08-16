/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
class SEAnesthesiaMachine;
class SESubstanceManager;
#include "bind/cdm/AnesthesiaMachine.pb.h"

class CDM_DECL SEAnesthesiaMachineOxygenBottle : Loggable
{
protected:
  friend SEAnesthesiaMachine;
public:

  SEAnesthesiaMachineOxygenBottle(Logger* logger);
  virtual ~SEAnesthesiaMachineOxygenBottle();

  virtual void Clear();

  static void Load(const cdm::AnesthesiaMachineData_OxygenBottleData& src, SEAnesthesiaMachineOxygenBottle& dst);
  static cdm::AnesthesiaMachineData_OxygenBottleData* Unload(const SEAnesthesiaMachineOxygenBottle& src);
protected:
  static void Serialize(const cdm::AnesthesiaMachineData_OxygenBottleData& src, SEAnesthesiaMachineOxygenBottle& dst);
  static void Serialize(const SEAnesthesiaMachineOxygenBottle& src, cdm::AnesthesiaMachineData_OxygenBottleData& dst);

  virtual void Merge(const SEAnesthesiaMachineOxygenBottle& from);
public:

  virtual const SEScalar* GetScalar(const std::string& name);

  virtual bool HasVolume() const;
  virtual SEScalarVolume& GetVolume();
  virtual double GetVolume(const VolumeUnit& unit) const;

  virtual void ToString(std::ostream &str);

protected:

  SEScalarVolume*     m_Volume;

};
