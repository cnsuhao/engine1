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

package mil.tatrc.physiology.datamodel.substance;


import java.util.Collection;
import java.util.HashMap;
import java.util.Map;

import com.kitware.physiology.cdm.Substance.SubstanceData;
import com.kitware.physiology.cdm.Substance.SubstanceData.eBindingProtein;
import com.kitware.physiology.cdm.Substance.SubstanceData.eIonicState;

import mil.tatrc.physiology.datamodel.properties.*;

public class SESubstancePhysicochemicals
{
  protected SEScalar         acidDissociationConstant;
  protected eBindingProtein  bindingProtien;
  protected SEScalar         bloodPlasmaRatio;
  protected SEScalar0To1     fractionUnboundInPlasma;
  protected eIonicState      ionicState;
  protected SEScalar         logP;
  protected SEScalar         oralAbsorptionRateConstant;  
    
  public SESubstancePhysicochemicals()
  {
    
  }
  
  public void reset()
  {
    if(this.acidDissociationConstant!=null)
      this.acidDissociationConstant.invalidate();
    this.bindingProtien = null;
    if(this.bloodPlasmaRatio!=null)
      this.bloodPlasmaRatio.invalidate();
    if(this.fractionUnboundInPlasma!=null)
      this.fractionUnboundInPlasma.invalidate();
    this.ionicState=null;
    if(this.logP!=null)
      this.logP.invalidate();  
    if(this.oralAbsorptionRateConstant!=null)
      this.oralAbsorptionRateConstant.invalidate();    
  }
  
  public boolean isValid()
  {    
    if(!hasAcidDissociationConstant() || 
       !hasBindingProtein() ||
       !hasBloodPlasmaRatio() ||
       !hasFractionUnboundInPlasma() ||
       !hasIonicState() ||
       !hasLogP())       
      return false;
    return true;
  }
  
  public static void load(SubstanceData.PhysicochemicalData src, SESubstancePhysicochemicals dst)
  {
    dst.reset();
    if(src.hasAcidDissociationConstant())
      SEScalar.load(src.getAcidDissociationConstant(),dst.getAcidDissociationConstant());
    if(src.getBindingProtein()!=null)
      dst.setBindingProtein(src.getBindingProtein());
    if(src.hasBloodPlasmaRatio())
      SEScalar.load(src.getBloodPlasmaRatio(),dst.getBloodPlasmaRatio());
    if(src.hasFractionUnboundInPlasma())
      SEScalar0To1.load(src.getFractionUnboundInPlasma(),dst.getFractionUnboundInPlasma());
    if(src.getIonicState()!=null)
      dst.setIonicState(src.getIonicState());
    if(src.hasLogP())
      SEScalar.load(src.getLogP(),dst.getLogP());
    if(src.hasOralAbsorptionRateConstant())
      SEScalar.load(src.getOralAbsorptionRateConstant(),dst.getOralAbsorptionRateConstant());      
  }
  public static SubstanceData.PhysicochemicalData unload(SESubstancePhysicochemicals src)
  {
    if(!src.isValid())
      return null;
    SubstanceData.PhysicochemicalData.Builder dst = SubstanceData.PhysicochemicalData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(SESubstancePhysicochemicals src, SubstanceData.PhysicochemicalData.Builder dst)
  {
    if(src.hasAcidDissociationConstant())
      dst.setAcidDissociationConstant(SEScalar.unload(src.acidDissociationConstant));
    if(src.hasBindingProtein())
      dst.setBindingProtein(src.bindingProtien);
    if(src.hasBloodPlasmaRatio())
      dst.setBloodPlasmaRatio(SEScalar.unload(src.bloodPlasmaRatio));
    if(src.hasFractionUnboundInPlasma())
      dst.setFractionUnboundInPlasma(SEScalar0To1.unload(src.fractionUnboundInPlasma));
    if(src.hasIonicState())
      dst.setIonicState(src.ionicState);
    if(src.hasLogP())
      dst.setLogP(SEScalar.unload(src.logP));
    if(src.hasOralAbsorptionRateConstant())
      dst.setOralAbsorptionRateConstant(SEScalar.unload(src.oralAbsorptionRateConstant));    
  }
  
  public SEScalar getAcidDissociationConstant() 
  { 
    if(this.acidDissociationConstant==null)
      this.acidDissociationConstant=new SEScalar();
    return this.acidDissociationConstant;
  }
  public boolean hasAcidDissociationConstant() {return this.acidDissociationConstant==null?false:this.acidDissociationConstant.isValid();}
  
  public eBindingProtein getBindingProtein() { return this.bindingProtien;}
  public void            setBindingProtein(eBindingProtein protein){this.bindingProtien=protein;}
  public boolean         hasBindingProtein(){return this.bindingProtien==null?false:true;}
  
  public SEScalar getBloodPlasmaRatio() 
  { 
    if(this.bloodPlasmaRatio==null)
      this.bloodPlasmaRatio=new SEScalar();
    return this.bloodPlasmaRatio;
  }
  public boolean hasBloodPlasmaRatio() {return this.bloodPlasmaRatio==null?false:this.bloodPlasmaRatio.isValid();}
  
  public SEScalar0To1 getFractionUnboundInPlasma() 
  { 
    if(this.fractionUnboundInPlasma==null)
      this.fractionUnboundInPlasma=new SEScalar0To1();
    return this.fractionUnboundInPlasma;
  }
  public boolean hasFractionUnboundInPlasma() {return this.fractionUnboundInPlasma==null?false:this.fractionUnboundInPlasma.isValid();}
  
  public eIonicState  getIonicState() { return this.ionicState;}
  public void         setIonicState(eIonicState state){this.ionicState=state;}
  public boolean      hasIonicState(){return this.ionicState==null?false:true;}
  
  public SEScalar getLogP() 
  { 
    if(this.logP==null)
      this.logP=new SEScalar();
    return this.logP;
  }
  public boolean hasLogP() {return this.logP==null?false:this.logP.isValid();}
  
  
  public SEScalar getOralAbsorptionRateConstant() 
  { 
    if(this.oralAbsorptionRateConstant==null)
      this.oralAbsorptionRateConstant=new SEScalar();
    return this.oralAbsorptionRateConstant;
  }
  public boolean hasOralAbsorptionRateConstant() {return this.oralAbsorptionRateConstant==null?false:this.oralAbsorptionRateConstant.isValid();}
}
