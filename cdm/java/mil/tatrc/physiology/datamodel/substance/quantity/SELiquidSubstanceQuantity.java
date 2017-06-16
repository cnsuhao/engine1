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

package mil.tatrc.physiology.datamodel.substance.quantity;

import mil.tatrc.physiology.datamodel.properties.CommonUnits.AmountPerVolumeUnit;
import mil.tatrc.physiology.datamodel.properties.CommonUnits.MassPerAmountUnit;
import mil.tatrc.physiology.datamodel.properties.SEScalarAmountPerVolume;

import com.kitware.physiology.cdm.SubstanceQuantity.GasSubstanceQuantityData;
import com.kitware.physiology.cdm.SubstanceQuantity.LiquidSubstanceQuantityData;

import mil.tatrc.physiology.datamodel.properties.SEScalar0To1;
import mil.tatrc.physiology.datamodel.properties.SEScalarMass;
import mil.tatrc.physiology.datamodel.properties.SEScalarMassPerVolume;
import mil.tatrc.physiology.datamodel.properties.SEScalarPressure;
import mil.tatrc.physiology.datamodel.properties.CommonUnits.MassPerVolumeUnit;
import mil.tatrc.physiology.datamodel.substance.SESubstance;

public class SELiquidSubstanceQuantity extends SESubstanceQuantity
{
  protected SEScalarMassPerVolume   concentration;
  protected SEScalarMass            mass;
  protected SEScalarMass            massCleared;
  protected SEScalarMass            massDeposited;
  protected SEScalarMass            massExcreted;
  protected SEScalarAmountPerVolume molarity;
  protected SEScalarPressure        partialPressure;
  protected SEScalar0To1        saturation;

  public SELiquidSubstanceQuantity(SESubstance s)
  {
    super(s);
    concentration = null;
    mass = null;
    massCleared = null;
    massDeposited = null;
    massExcreted = null;
    molarity = null;
    partialPressure = null;
    saturation = null;
  }

  public void reset()
  {
    super.reset();
    if (concentration != null)
      concentration.invalidate();
    if (mass != null)
      mass.invalidate();
    if(massCleared!=null)
      massCleared.invalidate();
    if(massDeposited!=null)
      massDeposited.invalidate();    
    if(massExcreted!=null)
      massExcreted.invalidate();    
    if (molarity != null)
      molarity.invalidate();
    if (partialPressure != null)
      partialPressure.invalidate();
    if (saturation != null)
      saturation.invalidate();
  }

  public static void load(LiquidSubstanceQuantityData src, SELiquidSubstanceQuantity dst)
  {
    SESubstanceQuantity.load(src.getSubstanceQuantity(),dst);
    if (src.hasConcentration()) 
      SEScalarMassPerVolume.load(src.getConcentration(),dst.getConcentration()); 
    if (src.hasMass()) 
      SEScalarMass.load(src.getMass(),dst.getMass()); 
    if (src.hasMassCleared())
      SEScalarMass.load(src.getMassCleared(),dst.getMassCleared());
    if (src.hasMassDeposited())
      SEScalarMass.load(src.getMassDeposited(),dst.getMassDeposited());
    if (src.hasMassExcreted())
      SEScalarMass.load(src.getMassExcreted(),dst.getMassExcreted());        
    if (src.hasPartialPressure()) 
      SEScalarPressure.load(src.getPartialPressure(),dst.getPartialPressure()); 
    if (src.hasSaturation()) 
      SEScalar0To1.load(src.getSaturation(),dst.getSaturation());
  }
  public static LiquidSubstanceQuantityData unload(SELiquidSubstanceQuantity src)
  {
    LiquidSubstanceQuantityData.Builder dst = LiquidSubstanceQuantityData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(SELiquidSubstanceQuantity src, LiquidSubstanceQuantityData.Builder dst)
  {
    SESubstanceQuantity.unload(src,dst.getSubstanceQuantityBuilder());
    if (src.hasConcentration())
      dst.setConcentration(SEScalarMassPerVolume.unload(src.concentration));
    if (src.hasMass())
      dst.setMass(SEScalarMass.unload(src.mass));
    if (src.hasMassCleared())
      dst.setMassCleared(SEScalarMass.unload(src.massCleared));
    if (src.hasMassDeposited())
      dst.setMassDeposited(SEScalarMass.unload(src.massDeposited));
    if (src.hasMassExcreted())
      dst.setMassExcreted(SEScalarMass.unload(src.massExcreted));    
    if (src.hasPartialPressure())
      dst.setPartialPressure(SEScalarPressure.unload(src.partialPressure));
    if (src.hasSaturation())
      dst.setSaturation(SEScalar0To1.unload(src.saturation));   
  }  

  public boolean hasConcentration()
  {
    return concentration == null ? false : concentration.isValid();
  }
  public SEScalarMassPerVolume getConcentration()
  {
    if (concentration == null)
      concentration = new SEScalarMassPerVolume();
    return concentration;
  }

  public boolean hasMass()
  {
    return mass == null ? false : mass.isValid();
  }
  public SEScalarMass getMass()
  {
    if (mass == null)
      mass = new SEScalarMass();
    return mass;
  }
  
  public SEScalarMass getMassCleared() 
  { 
    if(this.massCleared==null)
      this.massCleared=new SEScalarMass();
    return this.massCleared;
  }
  public boolean      hasMassCleared() {return this.massCleared==null?false:this.massCleared.isValid();}
  
  public SEScalarMass getMassDeposited() 
  { 
    if(this.massDeposited==null)
      this.massDeposited=new SEScalarMass();
    return this.massDeposited;
  }
  public boolean      hasMassDeposited() {return this.massDeposited==null?false:this.massDeposited.isValid();}
  
  public SEScalarMass getMassExcreted() 
  { 
    if(this.massExcreted==null)
      this.massExcreted=new SEScalarMass();
    return this.massExcreted;
  }
  public boolean      hasMassExcreted() {return this.massExcreted==null?false:this.massExcreted.isValid();}
   
  public boolean hasMolarity()
  {
    return molarity == null ? false : molarity.isValid();
  }
  public SEScalarAmountPerVolume getMolarity()
  {
    if (molarity == null)
      molarity = new SEScalarAmountPerVolume();
    molarity.setValue(getConcentration().getValue(MassPerVolumeUnit.ug_Per_mL)/substance.getMolarMass().getValue(MassPerAmountUnit.ug_Per_mol),AmountPerVolumeUnit.mol_Per_mL);
    return molarity;
  }

  public boolean hasPartialPressure()
  {
    return partialPressure == null ? false : partialPressure.isValid();
  }
  public SEScalarPressure getPartialPressure()
  {
    if (partialPressure == null)
      partialPressure = new SEScalarPressure();
    return partialPressure;
  }

  public boolean hasSaturation()
  {
    return saturation == null ? false : saturation.isValid();
  }
  public SEScalar0To1 getSaturation()
  {
    if (saturation == null)
      saturation = new SEScalar0To1();
    return saturation;
  }
}
