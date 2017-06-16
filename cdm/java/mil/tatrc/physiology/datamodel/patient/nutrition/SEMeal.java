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
package mil.tatrc.physiology.datamodel.patient.nutrition;

import com.kitware.physiology.cdm.PatientNutrition.MealData;

import mil.tatrc.physiology.datamodel.properties.SEScalarTime;

public class SEMeal extends SENutrition
{
  protected SEScalarTime  elapsedTime;
  
  public SEMeal()
  {    
    super();
    this.elapsedTime=null;
  }
  
  public void reset()
  {
    super.reset();
    if (elapsedTime != null)
      elapsedTime.invalidate();  
  }
  
  public void copy(SEMeal from)
  {
    super.copy(from);
    if(from.hasElapsedTime())
      this.getElapsedTime().set(from.getElapsedTime());
  }
  
  public static void load(MealData src, SEMeal dst)
  {
    dst.reset();
    if(src.hasNutrition())
      SENutrition.load(src.getNutrition(),dst);
    if (src.hasElapsedTime())
      SEScalarTime.load(src.getElapsedTime(),dst.getElapsedTime());
  }
  
  public static MealData unload(SEMeal src)
  {
    MealData.Builder dst = MealData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  
  protected static void unload(SEMeal src, MealData.Builder dst)
  {
    SENutrition.unload(src,dst.getNutritionBuilder());
    if (src.hasElapsedTime())
      dst.setElapsedTime(SEScalarTime.unload(src.elapsedTime));
  }    
  
  public SEScalarTime getElapsedTime()
  {
    if (elapsedTime == null)
      elapsedTime = new SEScalarTime();
    return elapsedTime;
  }
  public boolean hasElapsedTime()
  {
    return elapsedTime == null ? false : elapsedTime.isValid();
  }
}
