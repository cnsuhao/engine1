/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "patient/actions/SEPatientAction.h"

class CDM_DECL SEAirwayObstruction : public SEPatientAction
{
public:

  SEAirwayObstruction();
  virtual ~SEAirwayObstruction();

  virtual void Clear();

  virtual bool IsValid() const;
  virtual bool IsActive() const;

  static void Load(const cdm::AirwayObstructionData& src, SEAirwayObstruction& dst);
  static cdm::AirwayObstructionData* Unload(const SEAirwayObstruction& src);
protected:
  static void Serialize(const cdm::AirwayObstructionData& src, SEAirwayObstruction& dst);
  static void Serialize(const SEAirwayObstruction& src, cdm::AirwayObstructionData& dst);

public:

  virtual bool HasSeverity() const;
  virtual SEScalar0To1& GetSeverity();  

  virtual void ToString(std::ostream &str) const;

protected:
  SEScalar0To1*           m_Severity;
};      