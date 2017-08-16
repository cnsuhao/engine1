/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "patient/conditions/SEChronicHeartFailure.h"

class CDM_DECL SEChronicVentricularSystolicDysfunction : public SEChronicHeartFailure
{
public:

  SEChronicVentricularSystolicDysfunction();
  virtual ~SEChronicVentricularSystolicDysfunction();

  virtual void Clear(); //clear memory

  virtual bool IsValid() const;

  static void Load(const cdm::ChronicVentricularSystolicDysfunctionData& src, SEChronicVentricularSystolicDysfunction& dst);
  static cdm::ChronicVentricularSystolicDysfunctionData* Unload(const SEChronicVentricularSystolicDysfunction& src);
protected:
  static void Serialize(const cdm::ChronicVentricularSystolicDysfunctionData& src, SEChronicVentricularSystolicDysfunction& dst);
  static void Serialize(const SEChronicVentricularSystolicDysfunction& src, cdm::ChronicVentricularSystolicDysfunctionData& dst);

public:
  virtual std::string GetName() const { return "ChronicVentricularSystolicDysfunction"; }

  virtual void ToString(std::ostream &str) const;

protected:
};    