/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.patient.conditions;

import com.kitware.physiology.cdm.PatientConditions.ChronicVentricularSystolicDysfunctionData;

public class SEChronicVentricularSystolicDysfunction extends SEPatientCondition
{
  public SEChronicVentricularSystolicDysfunction()
  {
    
  }
  
  public void reset()
  {
    super.reset();
  }
  
  public void copy(SEChronicVentricularSystolicDysfunction other)
  {
    if(this==other)
      return;
    super.copy(other);    
  }
  
  public static void load(ChronicVentricularSystolicDysfunctionData src, SEChronicVentricularSystolicDysfunction dst) 
  {
    SEPatientCondition.load(src.getPatientCondition(), dst);
  }
  
  public static ChronicVentricularSystolicDysfunctionData unload(SEChronicVentricularSystolicDysfunction src) 
  {
    ChronicVentricularSystolicDysfunctionData.Builder dst = ChronicVentricularSystolicDysfunctionData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  
  protected static void unload(SEChronicVentricularSystolicDysfunction src, ChronicVentricularSystolicDysfunctionData.Builder dst)
  {
    SEPatientCondition.unload(src, dst.getPatientConditionBuilder());
  }
  
  public String toString()
  {
    return "Chronic Ventricular Systolic Dysfunction";
  }

  
}
