/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.substance;

import com.kitware.physiology.cdm.Substance.SubstanceData;

import mil.tatrc.physiology.datamodel.properties.*;
import mil.tatrc.physiology.datamodel.system.physiology.SEPupillaryResponse;

public class SESubstancePharmacodynamics
{
  protected SEScalar0To1          bronchodilation;
  protected SEScalar0To1          diastolicPressureModifier;
  protected SEScalarMassPerVolume EC50;
  protected SEScalar              EMaxShapeParameter;
  protected SEScalar0To1          heartRateModifier;
  protected SEScalar0To1          neuromuscularBlock;
  protected SEPupillaryResponse   pupillaryResponse;
  protected SEScalar0To1          respirationRateModifier;
  protected SEScalar0To1          sedation;
  protected SEScalar0To1          systolicPressureModifier;
  protected SEScalar0To1          tidalVolumeModifier;
  protected SEScalar0To1          tubularPermeabilityModifier;
  
  public SESubstancePharmacodynamics()
  {
    
  }
  
  public void reset()
  {
    if(this.bronchodilation!=null)
      this.bronchodilation.invalidate();
    if(this.diastolicPressureModifier!=null)
      this.diastolicPressureModifier.invalidate();
    if(this.EC50!=null)
      this.EC50.invalidate();
    if(this.EMaxShapeParameter!=null)
      this.EMaxShapeParameter.invalidate();
    if(this.heartRateModifier!=null)
      this.heartRateModifier.invalidate();
    if(this.neuromuscularBlock!=null)
      this.neuromuscularBlock.invalidate();
    if(this.pupillaryResponse!=null)
      this.pupillaryResponse.reset();
    if(this.respirationRateModifier!=null)
      this.respirationRateModifier.invalidate();
    if(this.sedation!=null)
      this.sedation.invalidate();
    if(this.systolicPressureModifier!=null)
      this.systolicPressureModifier.invalidate();
    if(this.tidalVolumeModifier!=null)
      this.tidalVolumeModifier.invalidate();
    if(this.tubularPermeabilityModifier!=null)
      this.tubularPermeabilityModifier.invalidate();
  }
  
  public boolean isValid()
  {
    if(!hasBronchodilation() || 
       !hasDiastolicPressureModifier() ||
       !hasEC50() ||
       !hasEMaxShapeParameter() ||
       !hasHeartRateModifier() ||
       !hasNeuromuscularBlock() ||
       !hasPupillaryResponse() ||
       !hasRespirationRateModifier() ||
       !hasSedation() ||
       !hasSystolicPressureModifier() ||
       !hasTidalVolumeModifier() ||
       !hasTubularPermeabilityModifier())       
      return false;
    return true;
  }
  
  public static void load(SubstanceData.PharmacodynamicsData src, SESubstancePharmacodynamics dst)
  {
    dst.reset();
    
    if(src.hasBronchodilation())
      SEScalar0To1.load(src.getBronchodilation(),dst.getBronchodilation());
    if(src.hasDiastolicPressureModifier())
      SEScalar0To1.load(src.getDiastolicPressureModifier(),dst.getDiastolicPressureModifier());
    if(src.hasEC50())
      SEScalarMassPerVolume.load(src.getEC50(),dst.getEC50());
    if(src.hasEMaxShapeParameter())
      SEScalar.load(src.getEMaxShapeParameter(),dst.getEMaxShapeParameter());
    if(src.hasHeartRateModifier())
      SEScalar0To1.load(src.getHeartRateModifier(),dst.getHeartRateModifier());
    if(src.hasNeuromuscularBlock())
      SEScalar0To1.load(src.getNeuromuscularBlock(),dst.getNeuromuscularBlock());
    if(src.hasPupillaryResponse())
      SEPupillaryResponse.load(src.getPupillaryResponse(),dst.getPupillaryResponse());
    if(src.hasRespirationRateModifier())
      SEScalar0To1.load(src.getRespirationRateModifier(),dst.getRespirationRateModifier());
    if(src.hasSedation())
      SEScalar0To1.load(src.getSedation(),dst.getSedation());
    if(src.hasSystolicPressureModifier())
      SEScalar0To1.load(src.getSystolicPressureModifier(),dst.getSystolicPressureModifier());
    if(src.hasTidalVolumeModifier())
      SEScalar0To1.load(src.getTidalVolumeModifier(),dst.getTidalVolumeModifier());
    if(src.hasTubularPermeabilityModifier())
      SEScalar0To1.load(src.getTubularPermeabilityModifier(),dst.getTubularPermeabilityModifier());
  }
  public static SubstanceData.PharmacodynamicsData unload(SESubstancePharmacodynamics src)
  {
    if(!src.isValid())
      return null;
    SubstanceData.PharmacodynamicsData.Builder dst = SubstanceData.PharmacodynamicsData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(SESubstancePharmacodynamics src, SubstanceData.PharmacodynamicsData.Builder dst)
  {
    if(src.hasBronchodilation())
      dst.setBronchodilation(SEScalar0To1.unload(src.getBronchodilation()));
    if(src.hasDiastolicPressureModifier())
      dst.setDiastolicPressureModifier(SEScalar0To1.unload(src.getDiastolicPressureModifier()));
    if(src.hasEC50())
      dst.setEC50(SEScalarMassPerVolume.unload(src.getEC50()));
    if(src.hasEMaxShapeParameter())
      dst.setEMaxShapeParameter(SEScalar0To1.unload(src.getEMaxShapeParameter()));
    if(src.hasHeartRateModifier())
      dst.setHeartRateModifier(SEScalar0To1.unload(src.getHeartRateModifier()));
    if(src.hasNeuromuscularBlock())
      dst.setNeuromuscularBlock(SEScalar0To1.unload(src.getNeuromuscularBlock()));
    if(src.hasPupillaryResponse())
      dst.setPupillaryResponse(SEPupillaryResponse.unload(src.getPupillaryResponse()));
    if(src.hasRespirationRateModifier())
      dst.setRespirationRateModifier(SEScalar0To1.unload(src.getRespirationRateModifier()));
    if(src.hasSedation())
      dst.setSedation(SEScalar0To1.unload(src.getSedation()));
    if(src.hasSystolicPressureModifier())
      dst.setSystolicPressureModifier(SEScalar0To1.unload(src.getSystolicPressureModifier()));
    if(src.hasTidalVolumeModifier())
      dst.setTidalVolumeModifier(SEScalar0To1.unload(src.getTidalVolumeModifier()));
    if(src.hasTubularPermeabilityModifier())
      dst.setTubularPermeabilityModifier(SEScalar0To1.unload(src.getTubularPermeabilityModifier()));
  }
  
  public SEScalar0To1 getBronchodilation() 
  { 
    if(this.bronchodilation==null)
      this.bronchodilation=new SEScalar0To1();
    return this.bronchodilation;
  }
  public boolean      hasBronchodilation() {return this.bronchodilation==null?false:this.bronchodilation.isValid();}
  
  public SEScalar0To1 getDiastolicPressureModifier() 
  { 
    if(this.diastolicPressureModifier==null)
      this.diastolicPressureModifier=new SEScalar0To1();
    return this.diastolicPressureModifier;
  }
  public boolean      hasDiastolicPressureModifier() {return this.diastolicPressureModifier==null?false:this.diastolicPressureModifier.isValid();}
  
  public SEScalarMassPerVolume getEC50() 
  { 
    if(this.EC50==null)
      this.EC50=new SEScalarMassPerVolume();
    return this.EC50;
  }
  public boolean      hasEC50() {return this.EC50==null?false:this.EC50.isValid();}
  
  public SEScalar getEMaxShapeParameter() 
  { 
    if(this.EMaxShapeParameter==null)
      this.EMaxShapeParameter=new SEScalar();
    return this.EMaxShapeParameter;
  }
  public boolean      hasEMaxShapeParameter() {return this.EMaxShapeParameter==null?false:this.EMaxShapeParameter.isValid();}
  
  public SEScalar0To1 getHeartRateModifier() 
  { 
    if(this.heartRateModifier==null)
      this.heartRateModifier=new SEScalar0To1();
    return this.heartRateModifier;
  }
  public boolean      hasHeartRateModifier() {return this.heartRateModifier==null?false:this.heartRateModifier.isValid();}
  
  public SEScalar0To1 getNeuromuscularBlock() 
  { 
    if(this.neuromuscularBlock==null)
      this.neuromuscularBlock=new SEScalar0To1();
    return this.neuromuscularBlock;
  }
  public boolean      hasNeuromuscularBlock() {return this.neuromuscularBlock==null?false:this.neuromuscularBlock.isValid();}
  
  public SEPupillaryResponse getPupillaryResponse() 
  { 
    if(this.pupillaryResponse==null)
      this.pupillaryResponse=new SEPupillaryResponse();
    return this.pupillaryResponse;
  }
  public boolean      hasPupillaryResponse() {return this.pupillaryResponse!=null;}
  
  public SEScalar0To1 getRespirationRateModifier() 
  { 
    if(this.respirationRateModifier==null)
      this.respirationRateModifier=new SEScalar0To1();
    return this.respirationRateModifier;
  }
  public boolean      hasRespirationRateModifier() {return this.respirationRateModifier==null?false:this.respirationRateModifier.isValid();}
  
  public SEScalar0To1 getSedation() 
  { 
    if(this.sedation==null)
      this.sedation=new SEScalar0To1();
    return this.sedation;
  }
  public boolean      hasSedation() {return this.sedation==null?false:this.sedation.isValid();}
  
  public SEScalar0To1 getSystolicPressureModifier() 
  { 
    if(this.systolicPressureModifier==null)
      this.systolicPressureModifier=new SEScalar0To1();
    return this.systolicPressureModifier;
  }
  public boolean      hasSystolicPressureModifier() {return this.systolicPressureModifier==null?false:this.systolicPressureModifier.isValid();}
  
  public SEScalar0To1 getTidalVolumeModifier() 
  { 
    if(this.tidalVolumeModifier==null)
      this.tidalVolumeModifier=new SEScalar0To1();
    return this.tidalVolumeModifier;
  }
  public boolean      hasTidalVolumeModifier() {return this.tidalVolumeModifier==null?false:this.tidalVolumeModifier.isValid();}
  
  public SEScalar0To1 getTubularPermeabilityModifier() 
  { 
    if(this.tubularPermeabilityModifier==null)
      this.tubularPermeabilityModifier=new SEScalar0To1();
    return this.tubularPermeabilityModifier;
  }
  public boolean      hasTubularPermeabilityModifier() {return this.tubularPermeabilityModifier==null?false:this.tubularPermeabilityModifier.isValid();}
}
