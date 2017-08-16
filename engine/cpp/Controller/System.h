/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
class PulseEngine;

/**
 * @brief Generic class for handling the %Pulse stabilization methodology
 */
class PULSE_DECL PulseSystem
{
  friend PulseEngine;
public:
  /**
  * @brief - Default system values to their homeostatic values
  */
  virtual void Initialize()
  {
    SetUp();
  }
  /// Notify systems that steady state has been achieved
  virtual void AtSteadyState() {};
  virtual void PreProcess() = 0;
  virtual void Process() = 0;
  virtual void PostProcess() = 0;

protected:
  virtual void SetUp() = 0;
};
