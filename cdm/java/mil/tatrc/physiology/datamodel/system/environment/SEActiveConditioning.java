/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
package mil.tatrc.physiology.datamodel.system.environment;

import mil.tatrc.physiology.datamodel.properties.SEScalarArea;

import com.kitware.physiology.cdm.Environment.EnvironmentData.ActiveConditioningData;

import mil.tatrc.physiology.datamodel.properties.SEScalar0To1;
import mil.tatrc.physiology.datamodel.properties.SEScalarPower;

public class SEActiveConditioning
{
  protected SEScalarPower   power;
  protected SEScalarArea    surfaceArea;
  protected SEScalar0To1    surfaceAreaFraction;

  public SEActiveConditioning() 
  {    
    power=null;
    surfaceArea=null;
    surfaceAreaFraction=null;
  }

  public void copy(SEActiveConditioning other)
  {
    if(this==other)
      return;
    if (other.power != null)
      getPower().set(other.getPower());
    else if (power != null)
      power.invalidate();
    if (other.surfaceArea != null)
      getSurfaceArea().set(other.getSurfaceArea());
    else if (surfaceArea != null)
      surfaceArea.invalidate();
    if (other.surfaceAreaFraction != null)
      getSurfaceAreaFraction().set(other.getSurfaceAreaFraction());
    else if (surfaceAreaFraction != null)
      surfaceAreaFraction.invalidate();    
  }

  public void reset()
  {
    if (power != null)
      power.invalidate();
    if (surfaceArea != null)
      surfaceArea.invalidate();
    if (surfaceAreaFraction != null)
      surfaceAreaFraction.invalidate();    
  }


  public static void load(ActiveConditioningData src, SEActiveConditioning dst)
  {
    dst.reset();
    if(src.hasPower())
      SEScalarPower.load(src.getPower(), dst.getPower());
    if(src.hasSurfaceArea())
      SEScalarArea.load(src.getSurfaceArea(),dst.getSurfaceArea());
    if(src.hasSurfaceAreaFraction())
      SEScalar0To1.load(src.getSurfaceAreaFraction(),dst.getSurfaceAreaFraction());
  }

  public static ActiveConditioningData unload(SEActiveConditioning src)
  {
    ActiveConditioningData.Builder dst = ActiveConditioningData.newBuilder();
    SEActiveConditioning.unload(src,dst);
    return dst.build();
  }

  protected static void unload(SEActiveConditioning src, ActiveConditioningData.Builder dst)
  {    
    if(src.hasPower())
      dst.setPower(SEScalarPower.unload(src.power));
    if(src.hasSurfaceArea())
      dst.setSurfaceArea(SEScalarArea.unload(src.surfaceArea));
    if(src.hasSurfaceAreaFraction())
      dst.setSurfaceAreaFraction(SEScalar0To1.unload(src.surfaceAreaFraction));
  }

  public boolean hasPower()
  {
    return power == null ? false : power.isValid();
  }
  public SEScalarPower getPower()
  {
    if (power == null)
      power = new SEScalarPower();
    return power;
  }
  public boolean hasSurfaceArea()
  {
    return surfaceArea == null ? false : surfaceArea.isValid();
  }
  public SEScalarArea getSurfaceArea()
  {
    if (surfaceArea == null)
      surfaceArea = new SEScalarArea();
    return surfaceArea;
  }
  public boolean hasSurfaceAreaFraction()
  {
    return surfaceAreaFraction == null ? false : surfaceAreaFraction.isValid();
  }
  public SEScalar0To1 getSurfaceAreaFraction()
  {
    if (surfaceAreaFraction == null)
      surfaceAreaFraction = new SEScalar0To1();
    return surfaceAreaFraction;
  }

  public String toString() 
  {
    return "Active Conditioning:"          
        + "\n\tPower: " + (this.hasPower()?this.getPower():"None")
        + "\n\tSurfaceArea: " + (this.hasSurfaceArea()?this.getSurfaceArea():"None")
        + "\n\tSurfaceAreaFraction: " + (this.hasSurfaceAreaFraction()?this.getSurfaceAreaFraction():"None");
  }
}
