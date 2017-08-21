/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
//CDM_BIND_DECL(ElectricalCircuitData)
#include "circuit/SECircuitCalculator.h"
#include "circuit/electrical/SEElectricalCircuit.h"

#include "properties/SEScalarElectricCapacitance.h"
#include "properties/SEScalarElectricCurrent.h"
#include "properties/SEScalarElectricCharge.h"
#include "properties/SEScalarElectricInductance.h"
#include "properties/SEScalarElectricPotential.h"
#include "properties/SEScalarElectricResistance.h"

class CDM_DECL SEElectricalCircuitCalculator : public SECircuitCalculator<SEElectricalCircuit, SEElectricalCircuitNode, SEElectricalCircuitPath, ElectricCapacitanceUnit, ElectricCurrentUnit, ElectricInductanceUnit, ElectricPotentialUnit, ElectricChargeUnit, ElectricResistanceUnit>
{
public:

  SEElectricalCircuitCalculator(Logger* logger);
  SEElectricalCircuitCalculator(const ElectricCapacitanceUnit&, const ElectricCurrentUnit&, const ElectricInductanceUnit&, const ElectricPotentialUnit&, const ElectricChargeUnit&, const ElectricResistanceUnit&, Logger* logger);
  virtual ~SEElectricalCircuitCalculator();
};