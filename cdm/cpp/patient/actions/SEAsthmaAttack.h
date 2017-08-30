/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "patient/actions/SEPatientAction.h"
CDM_BIND_DECL(AsthmaAttackData)

class CDM_DECL SEAsthmaAttack : public SEPatientAction
{
public:

  SEAsthmaAttack();
  virtual ~SEAsthmaAttack();

  virtual void Clear(); //clear memory

  virtual bool IsValid() const;
  virtual bool IsActive() const;

  static void Load(const cdm::AsthmaAttackData& src, SEAsthmaAttack& dst);
  static cdm::AsthmaAttackData* Unload(const SEAsthmaAttack& src);
protected:
  static void Serialize(const cdm::AsthmaAttackData& src, SEAsthmaAttack& dst);
  static void Serialize(const SEAsthmaAttack& src, cdm::AsthmaAttackData& dst);

public:

  virtual bool HasSeverity() const;
  virtual SEScalar0To1& GetSeverity();  

  virtual void ToString(std::ostream &str) const;

protected:
  SEScalar0To1*           m_Severity;
};      
