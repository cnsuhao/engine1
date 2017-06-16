/**************************************************************************************
Copyright 2015 Applied Research Associates, Inc.
Licensed under the Apache License, Version 2.0 (the "License"); you may not use
this file except in compliance with the License. You may obtain a copy of the License
at:
http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software distributed under
the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License.
 **************************************************************************************/

package mil.tatrc.physiology.datamodel.system.physiology;

import com.kitware.physiology.cdm.Physiology.EnergySystemData;

import mil.tatrc.physiology.datamodel.properties.*;
import mil.tatrc.physiology.datamodel.system.SESystem;

public class SEEnergySystem extends SEPhysiologySystem implements SESystem
{
  protected SEScalar0To1          achievedExerciseLevel;
  protected SEScalarTemperature   coreTemperature;
  protected SEScalarAmountPerTime creatinineProductionRate;
  protected SEScalarPressure      exerciseMeanArterialPressureDelta;
  protected SEScalar0To1          fatigueLevel;
  protected SEScalarAmountPerTime ketoneProductionRate;
  protected SEScalarAmountPerTime lactateProductionRate;
  protected SEScalarTemperature   skinTemperature;
  protected SEScalarMassPerTime   sweatRate;
  protected SEScalarPower         totalMetabolicRate;
  protected SEScalar0To1          totalWorkRateLevel;

  public SEEnergySystem()
  {
    coreTemperature = null;
    creatinineProductionRate = null;
    exerciseMeanArterialPressureDelta = null;
    achievedExerciseLevel = null;
    fatigueLevel = null;
    ketoneProductionRate = null;
    lactateProductionRate = null;
    skinTemperature = null;
    sweatRate = null;
    totalMetabolicRate = null;
    totalWorkRateLevel = null;
  }

  public void reset()
  {    
    if (coreTemperature != null)
      coreTemperature.invalidate();
    if (creatinineProductionRate != null)
      creatinineProductionRate.invalidate();
    if (exerciseMeanArterialPressureDelta != null)
      exerciseMeanArterialPressureDelta.invalidate();
    if (achievedExerciseLevel != null)
      achievedExerciseLevel.invalidate();
    if (fatigueLevel != null)
      fatigueLevel.invalidate();
    if (ketoneProductionRate != null)
      ketoneProductionRate.invalidate();
    if (lactateProductionRate != null)
      lactateProductionRate.invalidate();
    if (skinTemperature != null)
      skinTemperature.invalidate();
    if (sweatRate != null)
      sweatRate.invalidate();
    if (totalMetabolicRate != null)
      totalMetabolicRate.invalidate();
    if (totalWorkRateLevel != null)
      totalWorkRateLevel.invalidate();    
  }

  public static void load(EnergySystemData src, SEEnergySystem dst)
  {    
    if (src.hasCoreTemperature())
      SEScalarTemperature.load(src.getCoreTemperature(),dst.getCoreTemperature());
    if (src.hasCreatinineProductionRate())
      SEScalarAmountPerTime.load(src.getCreatinineProductionRate(),dst.getCreatinineProductionRate());
    if (src.hasExerciseMeanArterialPressureDelta())
      SEScalarPressure.load(src.getExerciseMeanArterialPressureDelta(),dst.getExerciseMeanArterialPressureDelta());
    if (src.hasAchievedExerciseLevel())
      SEScalar0To1.load(src.getAchievedExerciseLevel(),dst.getAchievedExerciseLevel());
    if (src.hasFatigueLevel())
      SEScalar0To1.load(src.getFatigueLevel(),dst.getFatigueLevel());
    if (src.hasKetoneProductionRate())
      SEScalarAmountPerTime.load(src.getKetoneProductionRate(),dst.getKetoneProductionRate());
    if (src.hasLactateProductionRate())
      SEScalarAmountPerTime.load(src.getLactateProductionRate(),dst.getLactateProductionRate());
    if (src.hasSkinTemperature())
      SEScalarTemperature.load(src.getSkinTemperature(),dst.getSkinTemperature());
    if (src.hasSweatRate())
      SEScalarMassPerTime.load(src.getSweatRate(),dst.getSweatRate());
    if (src.hasTotalMetabolicRate())
      SEScalarPower.load(src.getTotalMetabolicRate(),dst.getTotalMetabolicRate());
    if (src.hasTotalWorkRateLevel())
      SEScalar0To1.load(src.getTotalWorkRateLevel(),dst.getTotalWorkRateLevel());
  }

  public static EnergySystemData unload(SEEnergySystem src)
  {
    EnergySystemData.Builder dst = EnergySystemData.newBuilder();
    unload(src,dst);
    return dst.build();
  }

  protected static void unload(SEEnergySystem src, EnergySystemData.Builder dst)
  {    
    if (src.hasCoreTemperature())
      dst.setCoreTemperature(SEScalarTemperature.unload(src.getCoreTemperature()));
    if (src.hasCreatinineProductionRate())
      dst.setCreatinineProductionRate(SEScalarAmountPerTime.unload(src.getCreatinineProductionRate()));
    if (src.hasExerciseMeanArterialPressureDelta())
      dst.setExerciseMeanArterialPressureDelta(SEScalarPressure.unload(src.getExerciseMeanArterialPressureDelta()));
    if (src.hasAchievedExerciseLevel())
      dst.setAchievedExerciseLevel(SEScalar0To1.unload(src.getAchievedExerciseLevel()));
    if (src.hasFatigueLevel())
      dst.setFatigueLevel(SEScalar0To1.unload(src.getFatigueLevel()));
    if (src.hasKetoneProductionRate())
      dst.setKetoneProductionRate(SEScalarAmountPerTime.unload(src.getKetoneProductionRate()));
    if (src.hasLactateProductionRate())
      dst.setLactateProductionRate(SEScalarAmountPerTime.unload(src.getLactateProductionRate()));
    if (src.hasSkinTemperature())
      dst.setSkinTemperature(SEScalarTemperature.unload(src.getSkinTemperature()));
    if (src.hasSweatRate())
      dst.setSweatRate(SEScalarMassPerTime.unload(src.getSweatRate()));
    if (src.hasTotalMetabolicRate())
      dst.setTotalMetabolicRate(SEScalarPower.unload(src.getTotalMetabolicRate()));
    if (src.hasTotalWorkRateLevel())
      dst.setTotalWorkRateLevel(SEScalar0To1.unload(src.getTotalWorkRateLevel()));    
  }

  public boolean hasCoreTemperature()
  {
    return coreTemperature == null ? false : coreTemperature.isValid();
  }
  public SEScalarTemperature getCoreTemperature()
  {
    if (coreTemperature == null)
      coreTemperature = new SEScalarTemperature();
    return coreTemperature;
  }

  public boolean hasCreatinineProductionRate()
  {
    return creatinineProductionRate == null ? false : creatinineProductionRate.isValid();
  }
  public SEScalarAmountPerTime getCreatinineProductionRate()
  {
    if (creatinineProductionRate == null)
      creatinineProductionRate = new SEScalarAmountPerTime();
    return creatinineProductionRate;
  }

  public boolean hasExerciseMeanArterialPressureDelta()
  {
    return exerciseMeanArterialPressureDelta == null ? false : exerciseMeanArterialPressureDelta.isValid();
  }
  public SEScalarPressure getExerciseMeanArterialPressureDelta()
  {
    if (exerciseMeanArterialPressureDelta == null)
      exerciseMeanArterialPressureDelta = new SEScalarPressure();
    return exerciseMeanArterialPressureDelta;
  }
  
  public boolean hasAchievedExerciseLevel()
  {
    return achievedExerciseLevel == null ? false : achievedExerciseLevel.isValid();
  }
  public SEScalar0To1 getAchievedExerciseLevel()
  {
    if (achievedExerciseLevel == null)
      achievedExerciseLevel = new SEScalar0To1();
    return achievedExerciseLevel;
  }
  
  public boolean hasFatigueLevel()
  {
    return fatigueLevel == null ? false : fatigueLevel.isValid();
  }
  public SEScalar0To1 getFatigueLevel()
  {
    if (fatigueLevel == null)
      fatigueLevel = new SEScalar0To1();
    return fatigueLevel;
  }

  public boolean hasKetoneProductionRate()
  {
    return ketoneProductionRate == null ? false : ketoneProductionRate.isValid();
  }
  public SEScalarAmountPerTime getKetoneProductionRate()
  {
    if (ketoneProductionRate == null)
      ketoneProductionRate = new SEScalarAmountPerTime();
    return ketoneProductionRate;
  }

  public boolean hasLactateProductionRate()
  {
    return lactateProductionRate == null ? false : lactateProductionRate.isValid();
  }
  public SEScalarAmountPerTime getLactateProductionRate()
  {
    if (lactateProductionRate == null)
      lactateProductionRate = new SEScalarAmountPerTime();
    return lactateProductionRate;
  }

  public boolean hasSkinTemperature()
  {
    return skinTemperature == null ? false : skinTemperature.isValid();
  }
  public SEScalarTemperature getSkinTemperature()
  {
    if (skinTemperature == null)
      skinTemperature = new SEScalarTemperature();
    return skinTemperature;
  }

  public boolean hasSweatRate()
  {
    return sweatRate == null ? false : sweatRate.isValid();
  }
  public SEScalarMassPerTime getSweatRate()
  {
    if (sweatRate == null)
      sweatRate = new SEScalarMassPerTime();
    return sweatRate;
  }

  public boolean hasTotalMetabolicRate()
  {
    return totalMetabolicRate == null ? false : totalMetabolicRate.isValid();
  }
  public SEScalarPower getTotalMetabolicRate()
  {
    if (totalMetabolicRate == null)
      totalMetabolicRate = new SEScalarPower();
    return totalMetabolicRate;
  }
  
  public boolean hasTotalWorkRateLevel()
  {
    return totalWorkRateLevel == null ? false : totalWorkRateLevel.isValid();
  }
  public SEScalar0To1 getTotalWorkRateLevel()
  {
    if (totalWorkRateLevel == null)
      totalWorkRateLevel = new SEScalar0To1();
    return totalWorkRateLevel;
  }
  
  
}
