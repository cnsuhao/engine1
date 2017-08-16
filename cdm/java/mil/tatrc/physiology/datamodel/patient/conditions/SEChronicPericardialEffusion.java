/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.patient.conditions;

import com.kitware.physiology.cdm.PatientConditions.ChronicPericardialEffusionData;

import mil.tatrc.physiology.datamodel.properties.SEScalar0To1;
import mil.tatrc.physiology.datamodel.properties.SEScalarVolume;

public class SEChronicPericardialEffusion extends SEPatientCondition
{
  protected SEScalarVolume accumulatedVolume;
  
  public SEChronicPericardialEffusion()
  {
    accumulatedVolume = null;
  }
  
  public void reset()
  {
    super.reset();
    if (accumulatedVolume != null)
      accumulatedVolume.invalidate();
  }
  
  public void copy(SEChronicPericardialEffusion other)
  {
    if(this==other)
      return;
    super.copy(other);
    if (other.accumulatedVolume != null)
      getAccumulatedVolume().set(other.getAccumulatedVolume());
    else if (accumulatedVolume != null)
      accumulatedVolume.invalidate();
  }
  
  public static void load(ChronicPericardialEffusionData src, SEChronicPericardialEffusion dst) 
  {
    SEPatientCondition.load(src.getPatientCondition(), dst);
    if(src.hasAccumulatedVolume())
      SEScalarVolume.load(src.getAccumulatedVolume(),dst.getAccumulatedVolume());
  }
  
  public static ChronicPericardialEffusionData unload(SEChronicPericardialEffusion src) 
  {
    ChronicPericardialEffusionData.Builder dst = ChronicPericardialEffusionData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  
  protected static void unload(SEChronicPericardialEffusion src, ChronicPericardialEffusionData.Builder dst)
  {
    SEPatientCondition.unload(src, dst.getPatientConditionBuilder());
    if (src.hasAccumulatedVolume())
      dst.setAccumulatedVolume(SEScalarVolume.unload(src.accumulatedVolume));
  }
  
  public boolean hasAccumulatedVolume()
  {
    return accumulatedVolume == null ? false : accumulatedVolume.isValid();
  }
  public SEScalarVolume getAccumulatedVolume()
  {
    if (accumulatedVolume == null)
      accumulatedVolume = new SEScalarVolume();
    return accumulatedVolume;
  }
  
  public String toString()
  {
    return "Pericardial Effusion" 
        + "\n\tAccumulated Volume: " + getAccumulatedVolume();
  }

  
}
