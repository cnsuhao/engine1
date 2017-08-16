/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.patient.conditions;

import com.kitware.physiology.cdm.PatientConditions.ChronicRenalStenosisData;
import com.kitware.physiology.cdm.PatientConditions.ChronicVentricularSystolicDysfunctionData;

import mil.tatrc.physiology.datamodel.properties.SEScalar0To1;

public class SEChronicRenalStenosis extends SEPatientCondition
{
  protected SEScalar0To1 leftKidneySeverity;
  protected SEScalar0To1 rightKidneySeverity;
  
  public SEChronicRenalStenosis()
  {
    leftKidneySeverity = null;
    rightKidneySeverity = null;
  }
  
  public void reset()
  {
    super.reset();
    if (leftKidneySeverity != null)
      leftKidneySeverity.invalidate();
    if (rightKidneySeverity != null)
      rightKidneySeverity.invalidate();
  }
  
  public void copy(SEChronicRenalStenosis other)
  {
    if(this==other)
      return;
    super.copy(other);
    if (other.leftKidneySeverity != null)
      getLeftKidneySeverity().set(other.getLeftKidneySeverity());
    else if (leftKidneySeverity != null)
      leftKidneySeverity.invalidate();
    
    if (other.rightKidneySeverity != null)
      getRightKidneySeverity().set(other.getRightKidneySeverity());
    else if (rightKidneySeverity != null)
      rightKidneySeverity.invalidate();
  }
  
  public static void load(ChronicRenalStenosisData src, SEChronicRenalStenosis dst) 
  {
    SEPatientCondition.load(src.getPatientCondition(), dst);
    if(src.hasLeftKidneySeverity())
      SEScalar0To1.load(src.getLeftKidneySeverity(),dst.getLeftKidneySeverity());
    if(src.hasRightKidneySeverity())
      SEScalar0To1.load(src.getRightKidneySeverity(),dst.getRightKidneySeverity());
  }
  
  public static ChronicRenalStenosisData unload(SEChronicRenalStenosis src) 
  {
    ChronicRenalStenosisData.Builder dst = ChronicRenalStenosisData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  
  protected static void unload(SEChronicRenalStenosis src, ChronicRenalStenosisData.Builder dst)
  {
    SEPatientCondition.unload(src, dst.getPatientConditionBuilder());
    if (src.hasLeftKidneySeverity())
      dst.setLeftKidneySeverity(SEScalar0To1.unload(src.leftKidneySeverity));
    if (src.hasRightKidneySeverity())
      dst.setRightKidneySeverity(SEScalar0To1.unload(src.rightKidneySeverity));
  }
  
  public boolean hasLeftKidneySeverity()
  {
    return leftKidneySeverity == null ? false : leftKidneySeverity.isValid();
  }
  public SEScalar0To1 getLeftKidneySeverity()
  {
    if (leftKidneySeverity == null)
      leftKidneySeverity = new SEScalar0To1();
    return leftKidneySeverity;
  }
  
  public boolean hasRightKidneySeverity()
  {
    return rightKidneySeverity == null ? false : rightKidneySeverity.isValid();
  }
  public SEScalar0To1 getRightKidneySeverity()
  {
    if (rightKidneySeverity == null)
      rightKidneySeverity = new SEScalar0To1();
    return rightKidneySeverity;
  }
  
  public String toString()
  {
    return "Chronic Renal Stenosis" 
        + "\n\tLeftKidneySeverity: " + getLeftKidneySeverity()
        + "\n\tRightKidneySeverity: " + getRightKidneySeverity();
  }

  
}
