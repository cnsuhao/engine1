/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
package mil.tatrc.physiology.datamodel.system.environment;

import com.kitware.physiology.cdm.Environment.EnvironmentData.AppliedTemperatureData;
import com.kitware.physiology.cdm.Properties.eSwitch;

import mil.tatrc.physiology.datamodel.properties.SEScalar0To1;
import mil.tatrc.physiology.datamodel.properties.SEScalarArea;
import mil.tatrc.physiology.datamodel.properties.SEScalarTemperature;

public class SEAppliedTemperature
{
  protected SEScalarTemperature temperature;
  protected SEScalarArea        surfaceArea;
  protected SEScalar0To1        surfaceAreaFraction;
  protected eSwitch             state;

  public SEAppliedTemperature() 
  {
    temperature=null;
    surfaceArea=null;
    surfaceAreaFraction=null;
    state = null;
  }

  public void copy(SEAppliedTemperature other)
  {
    if(this==other)
      return;
    state = other.state;
    if (other.temperature != null)
      getTemperature().set(other.getTemperature());
    else if (temperature != null)
      temperature.invalidate();
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
    state = null;
    if (temperature != null)
      temperature.invalidate();
    if (surfaceArea != null)
      surfaceArea.invalidate();
    if (surfaceAreaFraction != null)
      surfaceAreaFraction.invalidate();
  }


  public static void load(AppliedTemperatureData src, SEAppliedTemperature dst)
  {
    dst.reset();
    if(src.getState()!=eSwitch.UNRECOGNIZED)
      dst.state = src.getState();
    if(src.hasTemperature())
      SEScalarTemperature.load(src.getTemperature(), dst.getTemperature());
    if(src.hasSurfaceArea())
      SEScalarArea.load(src.getSurfaceArea(), dst.getSurfaceArea());
    if(src.hasSurfaceAreaFraction())
      SEScalar0To1.load(src.getSurfaceAreaFraction(), dst.getSurfaceAreaFraction());
  }

  public static AppliedTemperatureData unload(SEAppliedTemperature src)
  {
    AppliedTemperatureData.Builder dst = AppliedTemperatureData.newBuilder();
    unload(src,dst);
    return dst.build();
  }

  protected static void unload(SEAppliedTemperature src, AppliedTemperatureData.Builder dst)
  {
    if (src.hasState())
      dst.setState(src.state);
    if(src.hasTemperature())
      dst.setTemperature(SEScalarTemperature.unload(src.temperature));
    if(src.hasSurfaceArea())
      dst.setSurfaceArea(SEScalarArea.unload(src.surfaceArea));
    if(src.hasSurfaceAreaFraction())
      dst.setSurfaceAreaFraction(SEScalar0To1.unload(src.surfaceAreaFraction));
  }
  

  public eSwitch getState()
  {
    return state;
  }
  public void setState(eSwitch onOrOff)
  {
    state = onOrOff;
  }
  public boolean hasState()
  {
    return state == null ? false : true;
  }
  
  public boolean hasTemperature()
  {
    return temperature == null ? false : temperature.isValid();
  }
  public SEScalarTemperature getTemperature()
  {
    if (temperature == null)
      temperature = new SEScalarTemperature();
    return temperature;
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
    return "Thermal Application:" 
        + "\n\tState: " + getState()
        + "\n\tAppliedTemperature: " + (this.hasTemperature()?this.getTemperature():"None")
        + "\n\tAppliedSurfaceArea: " + (this.hasSurfaceArea()?this.getSurfaceArea():"None")
        + "\n\tAppliedSurfaceAreaFraction: " + (this.hasSurfaceAreaFraction()?this.getSurfaceAreaFraction():"None");
  }
}
