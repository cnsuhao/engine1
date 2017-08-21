/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "substance/SESubstancePhysicochemicals.h"
#include "substance/SESubstanceTissuePharmacokinetics.h"

class CDM_DECL SESubstancePharmacokinetics : public Loggable
{
public:

  SESubstancePharmacokinetics(Logger* logger);
  virtual ~SESubstancePharmacokinetics();

  virtual void Clear();
  virtual bool IsValid() const;

  virtual const SEScalar* GetScalar(const std::string& name);

  static void Load(const cdm::SubstanceData_PharmacokineticsData& src, SESubstancePharmacokinetics& dst);
  static cdm::SubstanceData_PharmacokineticsData* Unload(const SESubstancePharmacokinetics& src);
protected:
  static void Serialize(const cdm::SubstanceData_PharmacokineticsData& src, SESubstancePharmacokinetics& dst);
  static void Serialize(const SESubstancePharmacokinetics& src, cdm::SubstanceData_PharmacokineticsData& dst);

public:
  virtual bool HasPhysicochemicals() const;
  virtual SESubstancePhysicochemicals& GetPhysicochemicals();
  virtual const SESubstancePhysicochemicals* GetPhysicochemicals() const;

  virtual bool HasTissueKinetics() const;
  virtual bool HasTissueKinetics(const std::string& name) const;
  virtual SESubstanceTissuePharmacokinetics& GetTissueKinetics(const std::string& name);
  virtual const SESubstanceTissuePharmacokinetics* GetTissueKinetics(const std::string& name) const;
  virtual void RemoveTissueKinetics(const std::string& name);

protected: 

  SESubstancePhysicochemicals*                              m_Physicochemicals;
  std::map<std::string, SESubstanceTissuePharmacokinetics*> m_TissueKinetics;

};