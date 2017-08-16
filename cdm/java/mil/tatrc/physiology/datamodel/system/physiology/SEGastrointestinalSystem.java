/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
package mil.tatrc.physiology.datamodel.system.physiology;

import com.kitware.physiology.cdm.Physiology.GastrointestinalSystemData;

import mil.tatrc.physiology.datamodel.patient.nutrition.SENutrition;
import mil.tatrc.physiology.datamodel.properties.*;
import mil.tatrc.physiology.datamodel.system.SESystem;

public class SEGastrointestinalSystem extends SEPhysiologySystem implements SESystem
{
  protected SEScalarVolumePerTime chymeAbsorbtionRate;
  protected SENutrition            stomachContents;

  public SEGastrointestinalSystem()
  {
    chymeAbsorbtionRate = null;
    stomachContents = null;
  }

  public void reset()
  {    
    if (chymeAbsorbtionRate != null)
      chymeAbsorbtionRate.invalidate();
    if (stomachContents != null)
      stomachContents.reset();
  }

  public static void load(GastrointestinalSystemData src, SEGastrointestinalSystem dst)
  {    
    if (src.hasChymeAbsorbtionRate())
      SEScalarVolumePerTime.load(src.getChymeAbsorbtionRate(),dst.getChymeAbsorbtionRate());
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
    if (src.hasChymeAbsorbtionRate())
      dst.setChymeAbsorbtionRate(SEScalarVolumePerTime.unload(src.getChymeAbsorbtionRate()));
    if (src.hasStomachContents())
      dst.setStomachContents(SENutrition.unload(src.getStomachContents()));
  }

  public boolean hasChymeAbsorbtionRate()
  {
    return chymeAbsorbtionRate == null ? false : chymeAbsorbtionRate.isValid();
  }
  public SEScalarVolumePerTime getChymeAbsorbtionRate()
  {
    if (chymeAbsorbtionRate == null)
      chymeAbsorbtionRate = new SEScalarVolumePerTime();
    return chymeAbsorbtionRate;
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
