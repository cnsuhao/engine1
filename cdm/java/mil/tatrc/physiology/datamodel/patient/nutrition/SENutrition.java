/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
package mil.tatrc.physiology.datamodel.patient.nutrition;

import com.google.protobuf.TextFormat;
import com.google.protobuf.TextFormat.ParseException;
import com.kitware.physiology.cdm.Environment.EnvironmentData;
import com.kitware.physiology.cdm.PatientNutrition.NutritionData;

import mil.tatrc.physiology.datamodel.properties.SEScalarMass;
import mil.tatrc.physiology.datamodel.properties.SEScalarMassPerTime;
import mil.tatrc.physiology.datamodel.properties.SEScalarVolume;
import mil.tatrc.physiology.datamodel.substance.SESubstanceManager;
import mil.tatrc.physiology.datamodel.system.environment.SEEnvironmentalConditions;
import mil.tatrc.physiology.utilities.FileUtils;

public class SENutrition 
{
  protected SEScalarMass           carbohydrate;
  protected SEScalarMassPerTime    carbohydrateDigestionRate;
  protected SEScalarMass           fat;
  protected SEScalarMassPerTime    fatDigestionRate;
  protected SEScalarMass           protein;
  protected SEScalarMassPerTime    proteinDigestionRate;
  protected SEScalarMass           calcium;
  protected SEScalarMass           sodium;
  protected SEScalarVolume         water;
  
  
  public SENutrition()
  {    
    this.carbohydrate=null;
    this.carbohydrateDigestionRate=null;
    this.fat=null;
    this.fatDigestionRate=null;
    this.protein=null;
    this.proteinDigestionRate=null;
    this.calcium=null;
    this.sodium=null;
    this.water=null;
  }
  
  public void reset()
  {
    if (carbohydrate != null)
      carbohydrate.invalidate();
    if (carbohydrateDigestionRate != null)
      carbohydrateDigestionRate.invalidate();
    if (fat != null)
      fat.invalidate();
    if (fatDigestionRate != null)
      fatDigestionRate.invalidate();
    if (protein != null)
      protein.invalidate();
    if (proteinDigestionRate != null)
      proteinDigestionRate.invalidate();
    if (calcium != null)
      calcium.invalidate();  
    if (sodium != null)
      sodium.invalidate();  
    if (water != null)
      water.invalidate();    
  }
  
  public void readFile(String fileName) throws ParseException
  {
    NutritionData.Builder builder = NutritionData.newBuilder();
    TextFormat.getParser().merge(FileUtils.readFile(fileName), builder);
    SENutrition.load(builder.build(), this);
  }
  public void writeFile(String fileName)
  {
    FileUtils.writeFile(fileName, SENutrition.unload(this).toString());
  }
  
  public void copy(SENutrition from)
  {
    this.reset();
    if(from.hasCarbohydrate())
      this.getCarbohydrate().set(from.getCarbohydrate());
    if(from.hasCarbohydrateDigestionRate())
      this.getCarbohydrateDigestionRate().set(from.getCarbohydrateDigestionRate());
    if(from.hasFat())
      this.getFat().set(from.getFat());
    if(from.hasFatDigestionRate())
      this.getFatDigestionRate().set(from.getFatDigestionRate());
    if(from.hasProtein())
      this.getProtein().set(from.getProtein());
    if(from.hasProteinDigestionRate())
      this.getProteinDigestionRate().set(from.getProteinDigestionRate());
    if(from.hasSodium())
      this.getSodium().set(from.getSodium());   
    if(from.hasCalcium())
      this.getCalcium().set(from.getCalcium()); 
    if(from.hasWater())
      this.getWater().set(from.getWater());
  }
  
  public static void load(NutritionData src, SENutrition dst)
  {
    if (src.hasCarbohydrate())
      SEScalarMass.load(src.getCarbohydrate(),dst.getCarbohydrate());
    if (src.hasCarbohydrateDigestionRate())
      SEScalarMassPerTime.load(src.getCarbohydrateDigestionRate(),dst.getCarbohydrateDigestionRate());
    if (src.hasFat())
      SEScalarMass.load(src.getFat(),dst.getFat());
    if (src.hasFatDigestionRate())
      SEScalarMassPerTime.load(src.getFatDigestionRate(),dst.getFatDigestionRate());
    if (src.hasProtein())
      SEScalarMass.load(src.getProtein(),dst.getProtein());
    if (src.hasProteinDigestionRate())
      SEScalarMassPerTime.load(src.getProteinDigestionRate(),dst.getProteinDigestionRate());
    if (src.hasCalcium())
      SEScalarMass.load(src.getCalcium(),dst.getCalcium()); 
    if (src.hasSodium())
      SEScalarMass.load(src.getSodium(),dst.getSodium()); 
    if (src.hasWater())
      SEScalarVolume.load(src.getWater(),dst.getWater());
  }
  
  public static NutritionData unload(SENutrition src)
  {
    NutritionData.Builder dst = NutritionData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  
  protected static void unload(SENutrition src, NutritionData.Builder dst)
  {
    if (src.hasCarbohydrate())
      dst.setCarbohydrate(SEScalarMass.unload(src.carbohydrate));
    if (src.hasCarbohydrateDigestionRate())
      dst.setCarbohydrateDigestionRate(SEScalarMassPerTime.unload(src.carbohydrateDigestionRate));
    if (src.hasFat())
      dst.setFat(SEScalarMass.unload(src.fat));
    if (src.hasFatDigestionRate())
      dst.setFatDigestionRate(SEScalarMassPerTime.unload(src.fatDigestionRate));
    if (src.hasProtein())
      dst.setProtein(SEScalarMass.unload(src.protein));
    if (src.hasProteinDigestionRate())
      dst.setProteinDigestionRate(SEScalarMassPerTime.unload(src.proteinDigestionRate));
    if (src.hasSodium())
      dst.setSodium(SEScalarMass.unload(src.sodium));  
    if (src.hasCalcium())
      dst.setCalcium(SEScalarMass.unload(src.calcium));  
    if (src.hasWater())
      dst.setWater(SEScalarVolume.unload(src.water));
  }    
  
  public SEScalarMass getCarbohydrate()
  {
    if (carbohydrate == null)
      carbohydrate = new SEScalarMass();
    return carbohydrate;
  }
  public boolean hasCarbohydrate()
  {
    return carbohydrate == null ? false : carbohydrate.isValid();
  }
  
  public SEScalarMassPerTime getCarbohydrateDigestionRate()
  {
    if (carbohydrateDigestionRate == null)
      carbohydrateDigestionRate = new SEScalarMassPerTime();
    return carbohydrateDigestionRate;
  }
  public boolean hasCarbohydrateDigestionRate()
  {
    return carbohydrateDigestionRate == null ? false : carbohydrateDigestionRate.isValid();
  }
  
  public SEScalarMass getFat()
  {
    if (fat == null)
      fat = new SEScalarMass();
    return fat;
  }
  public boolean hasFat()
  {
    return fat == null ? false : fat.isValid();
  }
  
  public SEScalarMassPerTime getFatDigestionRate()
  {
    if (fatDigestionRate == null)
      fatDigestionRate = new SEScalarMassPerTime();
    return fatDigestionRate;
  }
  public boolean hasFatDigestionRate()
  {
    return fatDigestionRate == null ? false : fatDigestionRate.isValid();
  }
  
  public SEScalarMass getProtein()
  {
    if (protein == null)
      protein = new SEScalarMass();
    return protein;
  }
  public boolean hasProtein()
  {
    return protein == null ? false : protein.isValid();
  }
  
  public SEScalarMassPerTime getProteinDigestionRate()
  {
    if (proteinDigestionRate == null)
      proteinDigestionRate = new SEScalarMassPerTime();
    return proteinDigestionRate;
  }
  public boolean hasProteinDigestionRate()
  {
    return protein == null ? false : protein.isValid();
  }

  public SEScalarMass getSodium()
  {
    if (sodium == null)
      sodium = new SEScalarMass();
    return sodium;
  }
  public boolean hasSodium()
  {
    return sodium == null ? false : sodium.isValid();
  }
  
  public SEScalarMass getCalcium()
  {
    if (calcium == null)
      calcium = new SEScalarMass();
    return calcium;
  }
  public boolean hasCalcium()
  {
    return calcium == null ? false : calcium.isValid();
  }
  
  public SEScalarVolume getWater()
  {
      if (water == null)
        water = new SEScalarVolume();
      return water;
  }
  public boolean hasWater()
  {
      return water == null ? false : water.isValid();
  }
}
