/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
package mil.tatrc.physiology.datamodel.system.physiology;

import com.kitware.physiology.cdm.Physiology.GastrointestinalSystemData;

import mil.tatrc.physiology.datamodel.patient.nutrition.SENutrition;
import mil.tatrc.physiology.datamodel.properties.*;
import mil.tatrc.physiology.datamodel.system.SESystem;

public class SEGastrointestinalSystem extends SEPhysiologySystem implements SESystem
{
  protected SEScalarVolumePerTime chymeAbsorptionRate;
  protected SENutrition            stomachContents;

  public SEGastrointestinalSystem()
  {
    chymeAbsorptionRate = null;
    stomachContents = null;
  }

  public void reset()
  {    
    if (chymeAbsorptionRate != null)
      chymeAbsorptionRate.invalidate();
    if (stomachContents != null)
      stomachContents.reset();
  }

  public static void load(GastrointestinalSystemData src, SEGastrointestinalSystem dst)
  {    
    if (src.hasChymeAbsorptionRate())
      SEScalarVolumePerTime.load(src.getChymeAbsorptionRate(),dst.getChymeAbsorptionRate());
    if (src.hasStomachContents())
      SENutrition.load(src.getStomachContents(),dst.getStomachContents());
  }

  public static GastrointestinalSystemData unload(SEGastrointestinalSystem src)
  {
    GastrointestinalSystemData.Builder dst = GastrointestinalSystemData.newBuilder();
    unload(src,dst);
    return dst.build();
  }

  protected static void unload(SEGastrointestinalSystem src, GastrointestinalSystemData.Builder dst)
  {    
    if (src.hasChymeAbsorptionRate())
      dst.setChymeAbsorptionRate(SEScalarVolumePerTime.unload(src.getChymeAbsorptionRate()));
    if (src.hasStomachContents())
      dst.setStomachContents(SENutrition.unload(src.getStomachContents()));
  }

  public boolean hasChymeAbsorptionRate()
  {
    return chymeAbsorptionRate == null ? false : chymeAbsorptionRate.isValid();
  }
  public SEScalarVolumePerTime getChymeAbsorptionRate()
  {
    if (chymeAbsorptionRate == null)
      chymeAbsorptionRate = new SEScalarVolumePerTime();
    return chymeAbsorptionRate;
  }

  public boolean hasStomachContents()
  {
    return stomachContents == null ? false : true;
  }
  public SENutrition getStomachContents()
  {
    if (stomachContents == null)
      stomachContents = new SENutrition();
    return stomachContents;
  }
}
