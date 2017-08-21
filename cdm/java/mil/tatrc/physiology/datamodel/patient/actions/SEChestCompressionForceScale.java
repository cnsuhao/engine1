/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.patient.actions;

import com.kitware.physiology.cdm.PatientActions.ChestCompressionForceScaleData;

import mil.tatrc.physiology.datamodel.properties.SEScalar0To1;
import mil.tatrc.physiology.datamodel.properties.SEScalarTime;

public class SEChestCompressionForceScale extends SEPatientAction
{
  protected SEScalar0To1 forceScale;
  protected SEScalarTime forcePeriod;   
  
  public SEChestCompressionForceScale()
  {
    forceScale = null;
    forcePeriod = null;
  }
  
  public SEChestCompressionForceScale(SEChestCompressionForceScale other)
  {
    this();
    copy(other);
  }
  
  public void copy(SEChestCompressionForceScale other)
  {
    if (other.forceScale != null)
      getForceScale().set(other.forceScale);
    else if (forceScale != null)
      forceScale.invalidate();
    
    if (other.forcePeriod != null)
      getForcePeriod().set(other.forcePeriod);
    else if (forcePeriod != null)
      forcePeriod.invalidate();
  }
  
  public void reset()
  {
    super.reset();
    if (forceScale != null)
      forceScale.invalidate();
    if (forcePeriod != null)
      forcePeriod.invalidate();
  }
  
  public boolean isValid()
  {
    return hasForceScale() && hasForcePeriod();
  }
  
  public static void load(ChestCompressionForceScaleData src, SEChestCompressionForceScale dst)
  {
    SEPatientAction.load(src.getPatientAction(), dst);
    if(src.hasForceScale())
      SEScalar0To1.load(src.getForceScale(),dst.getForceScale());
    if(src.hasForcePeriod())
      SEScalarTime.load(src.getForcePeriod(),dst.getForcePeriod());
  }
  
  public static ChestCompressionForceScaleData unload(SEChestCompressionForceScale src)
  {
    ChestCompressionForceScaleData.Builder dst = ChestCompressionForceScaleData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  
  protected static void unload(SEChestCompressionForceScale src, ChestCompressionForceScaleData.Builder dst)
  {
    SEPatientAction.unload(src,dst.getPatientActionBuilder());
    if (src.hasForceScale())
      dst.setForceScale(SEScalar0To1.unload(src.forceScale));
    if (src.hasForcePeriod())
      dst.setForcePeriod(SEScalarTime.unload(src.forcePeriod));
  }
  
  public boolean hasForceScale()
  {
    return forceScale == null ? false : forceScale.isValid();
  }
  public SEScalar0To1 getForceScale()
  {
    if (forceScale == null)
      forceScale = new SEScalar0To1();
    return forceScale;
  }
  
  public boolean hasForcePeriod()
  {
    return forcePeriod == null ? false : forcePeriod.isValid();
  }
  public SEScalarTime getForcePeriod()
  {
    if (forcePeriod == null)
      forcePeriod = new SEScalarTime();
    return forcePeriod;
  }
  
  public String toString()
  {
    if (forceScale != null)
      return "Patient Intervention : Chest Compression" 
          + "\n\tForceScale: " + (hasForceScale() ? getForceScale() : "Not Provided")
          + "\n\tForcePeriod: " + (hasForcePeriod() ? getForcePeriod() : "Not Provided");
    else
      return "Action not specified properly";
  }
}