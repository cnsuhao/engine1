/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
package mil.tatrc.physiology.datamodel.utilities;

import com.kitware.physiology.cdm.AnesthesiaMachine.AnesthesiaMachineData;
import com.kitware.physiology.cdm.Patient.PatientData;

import mil.tatrc.physiology.datamodel.properties.SEScalarTime;

public interface SEEventHandler
{
  public void handlePatientEvent(PatientData.eEvent type, boolean active, SEScalarTime time);
  public void handleAnesthesiaMachineEvent(AnesthesiaMachineData.eEvent type, boolean active, SEScalarTime time);
}
