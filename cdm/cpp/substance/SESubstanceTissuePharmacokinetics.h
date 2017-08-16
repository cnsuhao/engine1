/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "bind/cdm/Substance.pb.h"

class CDM_DECL SESubstanceTissuePharmacokinetics : public Loggable
{
public:

  SESubstanceTissuePharmacokinetics(const std::string& name, Logger* logger);
  virtual ~SESubstanceTissuePharmacokinetics();

  virtual void Clear();

  static void Load(const cdm::SubstanceData_TissuePharmacokineticsData& src, SESubstanceTissuePharmacokinetics& dst);
  static cdm::SubstanceData_TissuePharmacokineticsData* Unload(const SESubstanceTissuePharmacokinetics& src);
protected:
  static void Serialize(const cdm::SubstanceData_TissuePharmacokineticsData& src, SESubstanceTissuePharmacokinetics& dst);
  static void Serialize(const SESubstanceTissuePharmacokinetics& src, cdm::SubstanceData_TissuePharmacokineticsData& dst);

public:
  const SEScalar* GetScalar(const std::string& name);

  virtual std::string GetName() const;

  virtual bool HasPartitionCoefficient() const;
  virtual SEScalar& GetPartitionCoefficient();
  virtual double GetPartitionCoefficient() const;


protected:
  std::string    m_Name;
  SEScalar*     m_PartitionCoefficient;
};