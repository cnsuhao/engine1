/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.patient.actions;

import com.kitware.physiology.cdm.PatientActions.ConsumeNutrientsData;

import mil.tatrc.physiology.datamodel.patient.nutrition.SENutrition;

public class SEConsumeNutrients extends SEPatientAction
{
  protected SENutrition nutrition;
  protected String nutritionFile;
  
  public SEConsumeNutrients()
  {
    this.nutrition=new SENutrition();
  }
  
  public SEConsumeNutrients(SEConsumeNutrients other)
  {
    this();
    copy(other);    
  }
  
  public void copy(SEConsumeNutrients other)
  {
    if(this==other)
      return;
    super.copy(other);
    this.nutrition.copy(other.nutrition);
    this.nutritionFile=other.nutritionFile;
  }
  
  public void reset()
  {
    super.reset();
    this.nutrition.reset();
    this.nutritionFile="";
  }
  
  public boolean isValid()
  {
    return hasNutrition() || hasNutritionFile();
  }
  
  public static void load(ConsumeNutrientsData src, SEConsumeNutrients dst)
  {
    SEPatientAction.load(src.getPatientAction(), dst);
    switch(src.getOptionCase())
    {
    case NUTRITION:
      SENutrition.load(src.getNutrition(), dst.getNutrition());
      break;
    case NUTRITIONFILE:
      dst.setNutritionFile(src.getNutritionFile());
    }
  }
  
  public static ConsumeNutrientsData unload(SEConsumeNutrients src)
  {
    ConsumeNutrientsData.Builder dst = ConsumeNutrientsData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  
  protected static void unload(SEConsumeNutrients src, ConsumeNutrientsData.Builder dst)
  {
    SEPatientAction.unload(src,dst.getPatientActionBuilder());
    if(src.hasNutrition())
      dst.setNutrition(SENutrition.unload(src.nutrition));
    else if(src.hasNutritionFile())
      dst.setNutritionFile(src.nutritionFile);
  }
  
  public boolean hasNutrition()
  {
    return this.nutrition!=null;
  }
  public SENutrition getNutrition()
  {
    return this.nutrition;
  }
  
  public boolean hasNutritionFile()
  {
    return this.nutritionFile!=null&&!this.nutritionFile.isEmpty();
  }
  public String getNutritionFile()
  {
    return this.nutritionFile;
  }
  public void setNutritionFile(String s)
  {
    this.nutritionFile = s;
  }
  
  public String toString()
  {
    String str="Consume Nutrients:";
    if (nutrition != null)
      str +="\n\tCarbohydrate: " + (this.nutrition.hasCarbohydrate()?this.nutrition.getCarbohydrate():"None")
          + "\n\tFat: " + (this.nutrition.hasFat()?this.nutrition.getFat():"None")
          + "\n\tProtein: " + (this.nutrition.hasProtein()?this.nutrition.getProtein():"None")
          + "\n\tSodium: " + (this.nutrition.hasSodium()?this.nutrition.getSodium():"None")
          + "\n\tWater: " + (this.nutrition.hasWater()?this.nutrition.getWater():"None");
    if(this.hasNutritionFile())
      str +="\n\tFile: "+this.nutritionFile;
    return str;
  }
}