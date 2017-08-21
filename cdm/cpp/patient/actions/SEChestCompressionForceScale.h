/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "patient/actions/SEChestCompression.h"

class CDM_DECL SEChestCompressionForceScale : public SEChestCompression
{
public:
  SEChestCompressionForceScale();
  virtual ~SEChestCompressionForceScale();

  virtual void Clear(); //clear memory

  virtual bool IsValid() const;
  virtual bool IsActive() const;

  static void Load(const cdm::ChestCompressionForceScaleData& src, SEChestCompressionForceScale& dst);
  static cdm::ChestCompressionForceScaleData* Unload(const SEChestCompressionForceScale& src);
protected:
  static void Serialize(const cdm::ChestCompressionForceScaleData& src, SEChestCompressionForceScale& dst);
  static void Serialize(const SEChestCompressionForceScale& src, cdm::ChestCompressionForceScaleData& dst);

public:

  virtual bool HasForceScale() const;
  virtual SEScalar0To1& GetForceScale();

  virtual bool HasForcePeriod() const;
  virtual SEScalarTime& GetForcePeriod();

  virtual void ToString(std::ostream &str) const;

protected:
  SEScalar0To1*           m_ForceScale;
  SEScalarTime*               m_ForcePeriod;
};