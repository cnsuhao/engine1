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

package mil.tatrc.physiology.datamodel.patient.actions;

import com.kitware.physiology.cdm.PatientActions.SubstanceCompoundInfusionData;

import mil.tatrc.physiology.datamodel.properties.SEScalarVolume;
import mil.tatrc.physiology.datamodel.properties.SEScalarVolumePerTime;
import mil.tatrc.physiology.datamodel.substance.SESubstanceCompound;

public class SESubstanceCompoundInfusion extends SEPatientAction
{
  protected SEScalarVolume bagVolume;
  protected SEScalarVolumePerTime rate;
  protected SESubstanceCompound compound;
  
  public SESubstanceCompoundInfusion(SESubstanceCompound compound)
  {
    this.rate = null;
    this.bagVolume = null;
    this.compound = compound;
  }

  public void copy(SESubstanceCompoundInfusion other)
  {
    if(this==other)
      return;
    super.copy(other);
    compound = other.compound;
    
    if (other.rate != null)
      getRate().set(other.rate);
    else if (rate != null)
      rate.invalidate();
    
    if (other.bagVolume != null)
      getBagVolume().set(other.bagVolume);
    else if (bagVolume != null)
      bagVolume.invalidate();
  }
  
  public void reset()
  {
    super.reset();
    if (rate != null)
      rate.invalidate();
    if (bagVolume != null)
      bagVolume.invalidate();
  }
  
  public boolean isValid()
  {
    return hasRate() && hasBagVolume() && hasSubstanceCompound();
  }
  
  public static void load(SubstanceCompoundInfusionData src, SESubstanceCompoundInfusion dst)
  {
    SEPatientAction.load(src.getPatientAction(), dst);
    if(src.hasRate())
      SEScalarVolumePerTime.load(src.getRate(),dst.getRate());
    if(src.hasBagVolume())
      SEScalarVolume.load(src.getBagVolume(),dst.getBagVolume());
  }
  
  public static SubstanceCompoundInfusionData unload(SESubstanceCompoundInfusion src)
  {
    SubstanceCompoundInfusionData.Builder dst = SubstanceCompoundInfusionData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  
  protected static void unload(SESubstanceCompoundInfusion src, SubstanceCompoundInfusionData.Builder dst)
  {
    SEPatientAction.unload(src,dst.getPatientActionBuilder());
    if (src.hasRate())
      dst.setRate(SEScalarVolumePerTime.unload(src.rate));
    if (src.hasBagVolume())
      dst.setBagVolume(SEScalarVolume.unload(src.bagVolume));
    dst.setSubstanceCompound(src.getSubstanceCompound().getName());
  }
  
  public boolean hasBagVolume()
  {
    return bagVolume == null ? false : bagVolume.isValid();
  }
  public SEScalarVolume getBagVolume()
  {
    if (bagVolume == null)
      bagVolume = new SEScalarVolume();
    return bagVolume;
  }
  
  public boolean hasRate()
  {
    return rate == null ? false : rate.isValid();
  }
  public SEScalarVolumePerTime getRate()
  {
    if (rate == null)
      rate = new SEScalarVolumePerTime();
    return rate;
  }
  
  public boolean hasSubstanceCompound(){return true;}
  public SESubstanceCompound getSubstanceCompound()
  {
    return compound;
  }
  
  public String toString()
  {
    if (rate != null || compound != null)
      return "Compound Infusion "
          + "\n\tRate: " + getRate() 
          + "\n\tBag Volume: " + getBagVolume() 
          + "\n\tSubstance Compound: " + getSubstanceCompound().getName();
    else
      return "Action not specified properly";
  }
}
