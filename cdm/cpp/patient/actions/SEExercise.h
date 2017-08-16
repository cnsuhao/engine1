/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "patient/actions/SEPatientAction.h"

class CDM_DECL SEExercise : public SEPatientAction
{
public:

  SEExercise();
  virtual ~SEExercise();

  virtual void Clear(); //clear memory

  virtual bool IsValid() const;
  virtual bool IsActive() const;

  static void Load(const cdm::ExerciseData& src, SEExercise& dst);
  static cdm::ExerciseData* Unload(const SEExercise& src);
protected:
  static void Serialize(const cdm::ExerciseData& src, SEExercise& dst);
  static void Serialize(const SEExercise& src, cdm::ExerciseData& dst);

public:

  virtual bool HasIntensity() const;
  virtual SEScalar0To1& GetIntensity();
  
  virtual void ToString(std::ostream &str) const;

protected:
  SEScalar0To1* m_Intensity;
};    
