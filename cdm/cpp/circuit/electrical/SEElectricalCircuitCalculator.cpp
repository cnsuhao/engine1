/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "circuit/electrical/SEElectricalCircuitCalculator.h"


SEElectricalCircuitCalculator::SEElectricalCircuitCalculator(Logger* logger) : SECircuitCalculator<SEElectricalCircuit, SEElectricalCircuitNode,SEElectricalCircuitPath, ElectricCapacitanceUnit, ElectricCurrentUnit, ElectricInductanceUnit, ElectricPotentialUnit, ElectricChargeUnit, ElectricResistanceUnit>(
  ElectricCapacitanceUnit::F, ElectricCurrentUnit::A, ElectricInductanceUnit::H, ElectricPotentialUnit::V, ElectricChargeUnit::C, ElectricResistanceUnit::Ohm,logger)
{

}
SEElectricalCircuitCalculator::SEElectricalCircuitCalculator(const ElectricCapacitanceUnit& c, const ElectricCurrentUnit& f, const ElectricInductanceUnit& i, const ElectricPotentialUnit& p, const ElectricChargeUnit& q, const ElectricResistanceUnit& r, Logger* logger) : SECircuitCalculator<SEElectricalCircuit, SEElectricalCircuitNode, SEElectricalCircuitPath, ElectricCapacitanceUnit, ElectricCurrentUnit, ElectricInductanceUnit, ElectricPotentialUnit, ElectricChargeUnit, ElectricResistanceUnit>(c, f, i, p, q, r, logger)
{

}
SEElectricalCircuitCalculator::~SEElectricalCircuitCalculator()
{
  
}
