/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
//CDM_BIND_DECL(ThermalCircuitData)
#include "circuit/SECircuitCalculator.h"
#include "circuit/thermal/SEThermalCircuit.h"

#include "properties/SEScalarHeatCapacitance.h"
#include "properties/SEScalarPower.h"
#include "properties/SEScalarHeatInductance.h"
#include "properties/SEScalarTemperature.h"
#include "properties/SEScalarEnergy.h"
#include "properties/SEScalarHeatResistance.h"

class CDM_DECL SEThermalCircuitCalculator : public SECircuitCalculator<SEThermalCircuit, SEThermalCircuitNode, SEThermalCircuitPath, HeatCapacitanceUnit, PowerUnit, HeatInductanceUnit, TemperatureUnit, EnergyUnit, HeatResistanceUnit>
{
public:

  SEThermalCircuitCalculator(Logger* logger);
  SEThermalCircuitCalculator(const HeatCapacitanceUnit&, const PowerUnit&, const HeatInductanceUnit&, const TemperatureUnit&, const EnergyUnit&, const HeatResistanceUnit&, Logger* logger);
  virtual ~SEThermalCircuitCalculator();
};