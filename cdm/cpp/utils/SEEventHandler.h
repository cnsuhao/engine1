/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "bind/cdm/Patient.pb.h"
#include "bind/cdm/AnesthesiaMachine.pb.h"

class CDM_DECL SEEventHandler : public Loggable
{
public:
  SEEventHandler(Logger* logger) : Loggable(logger) {};
  virtual ~SEEventHandler(){};

  virtual void HandlePatientEvent(cdm::PatientData_eEvent type, bool active, const SEScalarTime* time = nullptr)=0;
  virtual void HandleAnesthesiaMachineEvent(cdm::AnesthesiaMachineData_eEvent type, bool active, const SEScalarTime* time = nullptr) = 0;
};