/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.patient.actions;

import com.kitware.physiology.cdm.PatientActions.PericardialEffusionData;

import mil.tatrc.physiology.datamodel.properties.SEScalarVolumePerTime;

public class SEPericardialEffusion extends SEPatientAction
{
  protected SEScalarVolumePerTime effusionRate;
  
  public SEPericardialEffusion()
  {
    effusionRate=null;
  }
  
  public void copy(SEPericardialEffusion other)
  {
    if(this==other)
      return;
    super.copy(other);
    if (other.effusionRate != null)
      getEffusionRate().set(other.getEffusionRate());
    else if (effusionRate != null)
      effusionRate.invalidate();
  }
  
  public void reset()
  {
    super.reset();
    if (effusionRate != null)
      effusionRate.invalidate();
  }
  
  public boolean isValid()
  {
    return hasEffusionRate();
  }
  
  public static void load(PericardialEffusionData src, SEPericardialEffusion dst)
  {
    SEPatientAction.load(src.getPatientAction(), dst);
    if(src.hasEffusionRate())
      SEScalarVolumePerTime.load(src.getEffusionRate(),dst.getEffusionRate());
  }
  
  public static PericardialEffusionData unload(SEPericardialEffusion src) 
  {
    PericardialEffusionData.Builder dst = PericardialEffusionData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  
  protected static void unload(SEPericardialEffusion src, PericardialEffusionData.Builder dst)
  {
    SEPatientAction.unload(src,dst.getPatientActionBuilder());
    if (src.hasEffusionRate())
      dst.setEffusionRate(SEScalarVolumePerTime.unload(src.effusionRate));
  }
  
  public boolean hasEffusionRate()
  {
    return effusionRate == null ? false : effusionRate.isValid();
  }
  public SEScalarVolumePerTime getEffusionRate()
  {
    if (effusionRate == null)
      effusionRate = new SEScalarVolumePerTime();
    return effusionRate;
  }
  
  public String toString() 
  {
    if (effusionRate != null)
      return "Pericardial Effusion" 
          + "\n\tEffusion Rate: " + getEffusionRate(); 
    else
      return "Action not properly specified";
  }
}
