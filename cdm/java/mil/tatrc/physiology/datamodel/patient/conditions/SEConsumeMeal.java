/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.patient.conditions;

import com.kitware.physiology.cdm.PatientConditions.ConsumeMealData;

import mil.tatrc.physiology.datamodel.patient.nutrition.SEMeal;

public class SEConsumeMeal extends SEPatientCondition
{
  protected SEMeal       meal;
  protected String       mealFile;
  
  public SEConsumeMeal()
  {
    this.meal=new SEMeal();
  }
  
  public SEConsumeMeal(SEConsumeMeal other)
  {
    this();
    copy(other);    
  }
  
  public void copy(SEConsumeMeal other)
  {
    if(this==other)
      return;
    super.copy(other);   
    this.meal.copy(other.meal);
    this.mealFile=other.mealFile;
  }
  
  public void reset()
  {
    super.reset();  
    this.meal.reset();
    this.mealFile="";
  }
  
  public static void load(ConsumeMealData src, SEConsumeMeal dst)
  {
    SEPatientCondition.load(src.getPatientCondition(), dst);  
    switch(src.getOptionCase())
    {
    case MEAL:
      SEMeal.load(src.getMeal(), dst.getMeal());
      break;
    case MEALFILE:
      dst.setMealFile(src.getMealFile());
    }      
  }
  
  public static ConsumeMealData unload(SEConsumeMeal src)
  {
    ConsumeMealData.Builder dst = ConsumeMealData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  
  protected static void unload(SEConsumeMeal src, ConsumeMealData.Builder dst)
  {
    SEPatientCondition.unload(src, dst.getPatientConditionBuilder()); 
    if(src.hasMeal())
      dst.setMeal(SEMeal.unload(src.meal));
    else if(src.hasMealFile())
      dst.setMealFile(src.mealFile);
  }
  
  public boolean hasMeal()
  {
    return this.meal!=null;
  }
  public SEMeal getMeal()
  {
    return this.meal;
  }
  
  public boolean hasMealFile()
  {
    return this.mealFile!=null&&!this.mealFile.isEmpty();
  }
  public String getMealFile()
  {
    return this.mealFile;
  }
  public void setMealFile(String s)
  {
    this.mealFile = s;
  }
  
  public String toString()
  {
    String str="Consume Meal:";
    if (meal != null)
      str +="\n\tElapsedTime: " + (this.meal.hasElapsedTime()?this.meal.getElapsedTime():"None")
          + "\n\tCarbohydrate: " + (this.meal.hasCarbohydrate()?this.meal.getCarbohydrate():"None")
          + "\n\tFat: " + (this.meal.hasFat()?this.meal.getFat():"None")
          + "\n\tProtein: " + (this.meal.hasProtein()?this.meal.getProtein():"None")
          + "\n\tSodium: " + (this.meal.hasSodium()?this.meal.getSodium():"None")
          + "\n\tWater: " + (this.meal.hasWater()?this.meal.getWater():"None");
    if(this.hasMealFile())
      str += "\n\tFile: "+this.mealFile;

    return str;
  }
}