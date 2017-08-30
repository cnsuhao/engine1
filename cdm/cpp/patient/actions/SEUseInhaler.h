/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "patient/actions/SEConsciousRespirationCommand.h"
CDM_BIND_DECL(ConsciousRespirationData_UseInhalerData)
class SESubstance;

class CDM_DECL SEUseInhaler : public SEConsciousRespirationCommand
{
  friend class SEConsciousRespiration;
  SEUseInhaler();
public:
  virtual ~SEUseInhaler();

  virtual void Clear(); //clear memory

  virtual bool IsValid() const;
  virtual bool IsActive() const;

  static void Load(const cdm::ConsciousRespirationData_UseInhalerData& src, SEUseInhaler& dst);
  static cdm::ConsciousRespirationData_UseInhalerData* Unload(const SEUseInhaler& src);
protected:
  static void Serialize(const cdm::ConsciousRespirationData_UseInhalerData& src, SEUseInhaler& dst);
  static void Serialize(const SEUseInhaler& src, cdm::ConsciousRespirationData_UseInhalerData& dst);

public:

  virtual void ToString(std::ostream &str) const;
protected:

};  
