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
