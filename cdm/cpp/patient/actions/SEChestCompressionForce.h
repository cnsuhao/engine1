/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "patient/actions/SEChestCompression.h"
CDM_BIND_DECL(ChestCompressionForceData)

class CDM_DECL SEChestCompressionForce : public SEChestCompression
{
public:

  SEChestCompressionForce();
  virtual ~SEChestCompressionForce();

  virtual void Clear(); //clear memory

  virtual bool IsValid() const;
  virtual bool IsActive() const;


  static void Load(const cdm::ChestCompressionForceData& src, SEChestCompressionForce& dst);
  static cdm::ChestCompressionForceData* Unload(const SEChestCompressionForce& src);
protected:
  static void Serialize(const cdm::ChestCompressionForceData& src, SEChestCompressionForce& dst);
  static void Serialize(const SEChestCompressionForce& src, cdm::ChestCompressionForceData& dst);

public:

  virtual bool HasForce() const;
  virtual SEScalarForce& GetForce();

  virtual void ToString(std::ostream &str) const;

protected:
  SEScalarForce*           m_Force;
};