/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
class SESubstanceManager;
PROTO_PUSH
#include "bind/cdm/Physiology.pb.h"
PROTO_POP

class CDM_DECL SESystem : public Loggable
{
public:

  SESystem(Logger* logger);
  virtual ~SESystem();

  virtual void Clear();// Deletes all members
  
  /** @name GetScalar
  *   @brief - A reflextion type call that will return the Scalar associated
  *            with the string. ex. GetScalar("Hematocrit") will return the
  *            SEScalarPercent object associated with Hematocrit
  *   @details - Note this is an expensive call as it will string compare many times
  *              This is best used, and intended for, you to dynamically prepopulate
  *              a mapping data structure that will help access what you need
  */
  virtual const SEScalar* GetScalar(const std::string& name) = 0; 

  /** @name GetScalar
  *   @brief - Look for the Scalar property in the systems contained in the provided vector
  */
  static const SEScalar* GetScalar(const std::string& name, std::vector<SESystem*>* systems);

protected:
  std::stringstream m_ss;
};
