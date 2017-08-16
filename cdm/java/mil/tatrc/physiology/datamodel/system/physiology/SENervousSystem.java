/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
package mil.tatrc.physiology.datamodel.system.physiology;

import com.kitware.physiology.cdm.Physiology.NervousSystemData;

import mil.tatrc.physiology.datamodel.properties.*;
import mil.tatrc.physiology.datamodel.system.SESystem;

public class SENervousSystem extends SEPhysiologySystem implements SESystem
{
  protected SEScalar            baroreceptorHeartRateScale;
  protected SEScalar            baroreceptorHeartElastanceScale;
  protected SEScalar            baroreceptorResistanceScale;
  protected SEScalar            baroreceptorComplianceScale;
  protected SEPupillaryResponse leftPupillaryResponse;
  protected SEPupillaryResponse rightPupillaryResponse;
  protected SEScalar            chemoreceptorHeartRateScale;
  protected SEScalar            chemoreceptorHeartElastanceScale;

  public SENervousSystem()
  {
    baroreceptorHeartRateScale=null;
    baroreceptorHeartElastanceScale=null;
    baroreceptorResistanceScale=null;
    baroreceptorComplianceScale=null;
    leftPupillaryResponse=null;
    rightPupillaryResponse=null;
    chemoreceptorHeartRateScale=null;
    chemoreceptorHeartElastanceScale=null;
  }

  public void reset()
  {    
    if(baroreceptorHeartRateScale!=null)
      baroreceptorHeartRateScale.invalidate();
    if(baroreceptorHeartElastanceScale!=null)
      baroreceptorHeartElastanceScale.invalidate();
    if(baroreceptorResistanceScale!=null)
      baroreceptorResistanceScale.invalidate();
    if(baroreceptorComplianceScale!=null)
      baroreceptorComplianceScale.invalidate();
    if(leftPupillaryResponse != null)
      this.leftPupillaryResponse.reset();
    if(rightPupillaryResponse != null)
      this.rightPupillaryResponse.reset();
    if(chemoreceptorHeartRateScale!=null)
      chemoreceptorHeartRateScale.invalidate();
    if(chemoreceptorHeartElastanceScale!=null)
      chemoreceptorHeartElastanceScale.invalidate();
  }

  public static void load(NervousSystemData src, SENervousSystem dst)
  {    
    if (src.hasBaroreceptorHeartRateScale())
      SEScalar.load(src.getBaroreceptorHeartRateScale(),dst.getBaroreceptorHeartRateScale());
    if (src.hasBaroreceptorHeartElastanceScale())
      SEScalar.load(src.getBaroreceptorHeartElastanceScale(),dst.getBaroreceptorHeartElastanceScale());
    if (src.hasBaroreceptorResistanceScale())
      SEScalar.load(src.getBaroreceptorResistanceScale(),dst.getBaroreceptorResistanceScale());
    if (src.hasBaroreceptorComplianceScale())
      SEScalar.load(src.getBaroreceptorComplianceScale(),dst.getBaroreceptorComplianceScale());
    
    if (src.hasChemoreceptorHeartRateScale())
      SEScalar.load(src.getChemoreceptorHeartRateScale(),dst.getChemoreceptorHeartRateScale());
    if (src.hasChemoreceptorHeartElastanceScale())
      SEScalar.load(src.getChemoreceptorHeartElastanceScale(),dst.getChemoreceptorHeartElastanceScale());

    if(src.hasLeftEyePupillaryResponse())
      SEPupillaryResponse.load(src.getLeftEyePupillaryResponse(),dst.getLeftEyePupillaryResponse());
    if(src.hasRightEyePupillaryResponse())
      SEPupillaryResponse.load(src.getRightEyePupillaryResponse(),dst.getRightEyePupillaryResponse());
  }

  public static NervousSystemData unload(SENervousSystem src)
  {
    NervousSystemData.Builder dst = NervousSystemData.newBuilder();
    unload(src,dst);
    return dst.build();
  }

  protected static void unload(SENervousSystem src, NervousSystemData.Builder dst)
  {    
    if (src.hasBaroreceptorHeartRateScale())
      dst.setBaroreceptorHeartRateScale(SEScalar.unload(src.getBaroreceptorHeartRateScale()));
    if (src.hasBaroreceptorHeartElastanceScale())
      dst.setBaroreceptorHeartElastanceScale(SEScalar.unload(src.getBaroreceptorHeartElastanceScale()));
    if (src.hasBaroreceptorResistanceScale())
      dst.setBaroreceptorResistanceScale(SEScalar.unload(src.getBaroreceptorResistanceScale()));
    if (src.hasBaroreceptorComplianceScale())
      dst.setBaroreceptorComplianceScale(SEScalar.unload(src.getBaroreceptorComplianceScale()));
    
    if (src.hasChemoreceptorHeartRateScale())
      dst.setChemoreceptorHeartRateScale(SEScalar.unload(src.getChemoreceptorHeartRateScale()));
    if (src.hasChemoreceptorHeartElastanceScale())
      dst.setChemoreceptorHeartElastanceScale(SEScalar.unload(src.getChemoreceptorHeartElastanceScale()));

    if(src.hasLeftEyePupillaryResponse())
      dst.setLeftEyePupillaryResponse(SEPupillaryResponse.unload(src.leftPupillaryResponse));
    if(src.hasRightEyePupillaryResponse())
      dst.setRightEyePupillaryResponse(SEPupillaryResponse.unload(src.rightPupillaryResponse));
  }

  public boolean hasBaroreceptorHeartRateScale()
  {
    return baroreceptorHeartRateScale == null ? false : baroreceptorHeartRateScale.isValid();
  }
  public SEScalar getBaroreceptorHeartRateScale()
  {
    if (baroreceptorHeartRateScale == null)
      baroreceptorHeartRateScale = new SEScalar();
    return baroreceptorHeartRateScale;
  }

  public boolean hasBaroreceptorHeartElastanceScale()
  {
    return baroreceptorHeartElastanceScale == null ? false : baroreceptorHeartElastanceScale.isValid();
  }
  public SEScalar getBaroreceptorHeartElastanceScale()
  {
    if (baroreceptorHeartElastanceScale == null)
      baroreceptorHeartElastanceScale = new SEScalar();
    return baroreceptorHeartElastanceScale;
  }

  public boolean hasBaroreceptorResistanceScale()
  {
    return baroreceptorResistanceScale == null ? false : baroreceptorResistanceScale.isValid();
  }
  public SEScalar getBaroreceptorResistanceScale()
  {
    if (baroreceptorResistanceScale == null)
      baroreceptorResistanceScale = new SEScalar();
    return baroreceptorResistanceScale;
  }

  public boolean hasBaroreceptorComplianceScale()
  {
    return baroreceptorComplianceScale == null ? false : baroreceptorComplianceScale.isValid();
  }
  public SEScalar getBaroreceptorComplianceScale()
  {
    if (baroreceptorComplianceScale == null)
      baroreceptorComplianceScale = new SEScalar();
    return baroreceptorComplianceScale;
  }

  public boolean hasChemoreceptorHeartRateScale()
  {
    return chemoreceptorHeartRateScale == null ? false : chemoreceptorHeartRateScale.isValid();
  }
  public SEScalar getChemoreceptorHeartRateScale()
  {
    if (chemoreceptorHeartRateScale == null)
      chemoreceptorHeartRateScale = new SEScalar();
    return chemoreceptorHeartRateScale;
  }

  public boolean hasChemoreceptorHeartElastanceScale()
  {
    return chemoreceptorHeartElastanceScale == null ? false : chemoreceptorHeartElastanceScale.isValid();
  }
  public SEScalar getChemoreceptorHeartElastanceScale()
  {
    if (chemoreceptorHeartElastanceScale == null)
      chemoreceptorHeartElastanceScale = new SEScalar();
    return chemoreceptorHeartElastanceScale;
  }

  public SEPupillaryResponse getLeftEyePupillaryResponse() 
  { 
    if(this.leftPupillaryResponse==null)
      this.leftPupillaryResponse=new SEPupillaryResponse();
    return this.leftPupillaryResponse;
  }  
  public boolean  hasLeftEyePupillaryResponse() {return this.leftPupillaryResponse!=null;}

  public SEPupillaryResponse getRightEyePupillaryResponse() 
  { 
    if(this.rightPupillaryResponse==null)
      this.rightPupillaryResponse=new SEPupillaryResponse();
    return this.rightPupillaryResponse;
  }  
  public boolean  hasRightEyePupillaryResponse() {return this.rightPupillaryResponse!=null;}


}
