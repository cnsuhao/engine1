/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
class SEGasCompartment;
class SELiquidCompartment;
class SEThermalCompartment;
class SETissueCompartment;
class SESubstance;
class SECircuitManager;
PROTO_PUSH
#include "bind/cdm/Compartment.pb.h"
PROTO_POP

class CDM_DECL SECompartment : public Loggable
{
protected:
  SECompartment(const std::string& name, Logger* logger);
public: 
  virtual ~SECompartment();

  virtual void Clear();

protected:
  static void Serialize(const cdm::CompartmentData& src, SECompartment& dst);
  static void Serialize(const SECompartment& src, cdm::CompartmentData& dst);

public:
  virtual std::string GetName() const;

  virtual const SEScalar* GetScalar(const std::string& name) = 0;

  virtual bool HasChildren() const = 0; // Compartments with children contain 'read only' scalars

  virtual void StateChange() = 0;

protected:
  std::string  m_Name;

public:

  template<typename CompartmentType>
  static void FindLeaves(CompartmentType& cmpt, std::vector<CompartmentType*>& leaves)
  {
    for (CompartmentType* child : cmpt.GetChildren())
    {
      if (!child->HasChildren())
        leaves.push_back(child);
      else
        FindLeaves(*child, leaves);
    }
  }
};