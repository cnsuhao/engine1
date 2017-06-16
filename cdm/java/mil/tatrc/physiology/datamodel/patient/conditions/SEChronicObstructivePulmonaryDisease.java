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

package mil.tatrc.physiology.datamodel.patient.conditions;

import com.kitware.physiology.cdm.PatientConditions.ChronicObstructivePulmonaryDiseaseData;

import mil.tatrc.physiology.datamodel.properties.SEScalar0To1;

public class SEChronicObstructivePulmonaryDisease extends SEPatientCondition
{
  protected SEScalar0To1 bronchitisSeverity;
  protected SEScalar0To1 emphysemaSeverity;
  
  public SEChronicObstructivePulmonaryDisease()
  {
    bronchitisSeverity = null;
    emphysemaSeverity = null;
  }
  
  public void reset()
  {
    super.reset();
    if (bronchitisSeverity != null)
      bronchitisSeverity.invalidate();
    if (emphysemaSeverity != null)
      emphysemaSeverity.invalidate();
  }
  
  public void copy(SEChronicObstructivePulmonaryDisease other)
  {
    if(this==other)
      return;
    super.copy(other);
    if (other.bronchitisSeverity != null)
      getBronchitisSeverity().set(other.getBronchitisSeverity());
    if (other.emphysemaSeverity != null)
      getEmphysemaSeverity().set(other.getEmphysemaSeverity());
  }
  
  public static void load(ChronicObstructivePulmonaryDiseaseData src, SEChronicObstructivePulmonaryDisease dst) 
  {
    SEPatientCondition.load(src.getPatientCondition(), dst);
    if(src.hasBronchitisSeverity())
      SEScalar0To1.load(src.getBronchitisSeverity(),dst.getBronchitisSeverity());
    if(src.hasEmphysemaSeverity())
      SEScalar0To1.load(src.getEmphysemaSeverity(),dst.getEmphysemaSeverity());
  }
  
  public static ChronicObstructivePulmonaryDiseaseData unload(SEChronicObstructivePulmonaryDisease src)
  {
    ChronicObstructivePulmonaryDiseaseData.Builder dst = ChronicObstructivePulmonaryDiseaseData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  
  protected static void unload(SEChronicObstructivePulmonaryDisease src, ChronicObstructivePulmonaryDiseaseData.Builder dst)
  {
    SEPatientCondition.unload(src, dst.getPatientConditionBuilder());
    if (src.hasBronchitisSeverity())
      dst.setBronchitisSeverity(SEScalar0To1.unload(src.bronchitisSeverity));
    if (src.hasEmphysemaSeverity())
      dst.setEmphysemaSeverity(SEScalar0To1.unload(src.emphysemaSeverity));
  }
  
  public boolean hasBronchitisSeverity()
  {
    return bronchitisSeverity == null ? false : bronchitisSeverity.isValid();
  }
  public SEScalar0To1 getBronchitisSeverity()
  {
    if (bronchitisSeverity == null)
      bronchitisSeverity = new SEScalar0To1();
    return bronchitisSeverity;
  }
  
  public boolean hasEmphysemaSeverity()
  {
    return emphysemaSeverity == null ? false : emphysemaSeverity.isValid();
  }
  public SEScalar0To1 getEmphysemaSeverity()
  {
    if (emphysemaSeverity == null)
      emphysemaSeverity = new SEScalar0To1();
    return emphysemaSeverity;
  }
  
  public String toString()
  {
    return "COPD" 
        + "\n\tBronchitis Severity: " + getBronchitisSeverity()
        + "\n\tEmphysema Severity: " + getEmphysemaSeverity();
  }
}
