/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "circuit/SECircuitCalculator.h"

// Note this must match the enum values
template<> char const* enumStrings<EigenCircuitSolver>::values[] = { "Direct", "PartialPivLu", "FullPivLu", "JacobiSvd", "HouseholderQr", "Ldlt", "Llt", "SparseLU", "SparseQR", "BiCGSTAB", "ConjugateGradient" };
char const* EigenCircuitSolver::Value(size_t idx)
{
  return enumStrings<EigenCircuitSolver>::values[idx];  
}