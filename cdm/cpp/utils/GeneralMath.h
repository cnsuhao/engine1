/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
class SESubstance;
class SESubstanceManager;
class SELiquidCompartment;
class SELiquidSubstanceQuantity;

class CDM_DECL GeneralMath
{
public:
  static void CalculateConcentration(const SEScalarMass& mass, const SEScalarVolume& volume, SEScalarMassPerVolume& concentration, Logger* logger = nullptr);
  static void CalculateMass(const SEScalarVolume& volume, const SEScalarMassPerVolume& concentration, SEScalarMass& mass, Logger* logger = nullptr);
  static void CalculateHenrysLawConcentration(const SESubstance& substance, const SEScalarPressure& partialPressure, SEScalarMassPerVolume& concentration, Logger* logger = nullptr);
  static void CalculatePartialPressureInGas(const SEScalar0To1& volumeFraction, const SEScalarPressure& pressure, SEScalarPressure& partialPressure, Logger* logger = nullptr);
  static void CalculatePartialPressureInLiquid(const SESubstance& substance, const SEScalarMassPerVolume& concentration, SEScalarPressure& partialPressure, Logger* logger = nullptr);
  static void CalculateOsmolarity(const SEScalarAmountPerVolume& sodiumMolarity, const SEScalarAmountPerVolume& potassiumMolarity, const SEScalarAmountPerVolume& glucoseMolarity, const SEScalarAmountPerVolume& ureaMolarity, SEScalarOsmolarity& fluidOsmolarity);
  static void CalculateOsmolality(const SEScalarAmountPerVolume& sodiumMolarity, const SEScalarAmountPerVolume& potassiumMolarity, const SEScalarAmountPerVolume& glucoseMolarity, const SEScalarAmountPerVolume& ureaMolarity, const SEScalar& specificGravity, SEScalarOsmolality& fluidOsmolality);
  static void CalculateSpecificGravity(const SEScalarMass& mass, const SEScalarVolume& volume, SEScalar& specificGravity, Logger* logger = nullptr);

  static void   Combinations(std::vector<int> maxValues, std::vector<std::vector<int>>& permutations);
  static double LinearInterpolator(double x1, double x2, double y1, double y2, double xPrime);
  static double PercentDifference(double expected, double calculated);
  static double PercentTolerance(double expected, double calculated, double epsilon = 1e-20);
  static double ResistanceFunction(double dbase, double dmin, double dmax, double dx);
  static double LogisticFunction(double a, double x50, double k, double x);
};


