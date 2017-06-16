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
package mil.tatrc.physiology.datamodel.engine;

import com.google.protobuf.TextFormat.ParseException;
import com.kitware.physiology.cdm.EngineConfiguration.PhysiologyEngineConfigurationData;

import mil.tatrc.physiology.datamodel.properties.SEScalarTime;
import mil.tatrc.physiology.datamodel.system.equipment.electrocardiogram.SEElectroCardioGramWaveformInterpolator;
import mil.tatrc.physiology.utilities.Log;

public class PhysiologyEngineConfiguration
{
  protected SEElectroCardioGramWaveformInterpolator  ecgInterpolator;
  protected PhysiologyEngineTimedStabilization       timedStabilization;
  protected PhysiologyEngineDynamicStabilization     dynamicStabilization;
  protected SEScalarTime                             timeStep;
  
  public PhysiologyEngineConfiguration()
  {
    clear();
  }
  
  public void reset()
  {
    if(ecgInterpolator!=null)
      this.ecgInterpolator.reset();
    if(timedStabilization!=null)
      this.timedStabilization.reset();
    if(dynamicStabilization!=null)
      this.dynamicStabilization.reset();
    if(timeStep!=null)
      this.timeStep.invalidate();
  }
  
  public void clear()
  {
    this.ecgInterpolator=null;
    this.timedStabilization=null;   
    this.dynamicStabilization=null;
    this.timeStep=null;
  }
  
  public static void load(PhysiologyEngineConfigurationData src, PhysiologyEngineConfiguration dst)
  {
    dst.clear();
    switch(src.getElectroCardioGramInterpolatorCase())
    {
    case INTERPOLATOR:
      SEElectroCardioGramWaveformInterpolator.load(src.getInterpolator(), dst.getECGInterpolator());
      break;
    case INTERPOLATORFILENAME:
      try
      {dst.getECGInterpolator().readFile(src.getInterpolatorFileName());}
      catch(ParseException ex){Log.error("Unable to load ECG File : "+src.getInterpolatorFileName());}
      break;
    }
    
    switch(src.getStabilizationCriteriaCase())
    {
    case TIMEDSTABILIZATION:
      PhysiologyEngineTimedStabilization.load(src.getTimedStabilization(), dst.getTimedStabilization());
      break;
    case DYNAMICSTABILIZATION:
      PhysiologyEngineDynamicStabilization.load(src.getDynamicStabilization(), dst.getDynamicStabilization());
      break;
    case STABILIZATIONFILENAME:
      try
      {dst.getTimedStabilization().readFile(src.getStabilizationFileName());}
      catch(ParseException ex){}
      try
      {dst.getDynamicStabilization().readFile(src.getStabilizationFileName());}
      catch(ParseException ex){}
      break;
    }
     
    if(src.hasTimeStep())
      SEScalarTime.load(src.getTimeStep(),dst.getTimeStep());
  }
  
  public static PhysiologyEngineConfigurationData unload(PhysiologyEngineConfiguration src)
  {
    PhysiologyEngineConfigurationData.Builder dst = PhysiologyEngineConfigurationData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(PhysiologyEngineConfiguration src, PhysiologyEngineConfigurationData.Builder dst)
  {
    if(src.hasECGInterpolator())
      dst.setInterpolator(SEElectroCardioGramWaveformInterpolator.unload(src.ecgInterpolator));
    if(src.hasTimedStabilization())
      dst.setTimedStabilization(PhysiologyEngineTimedStabilization.unload(src.timedStabilization));
    if(src.hasDynamicStabilization())
      dst.setDynamicStabilization(PhysiologyEngineDynamicStabilization.unload(src.dynamicStabilization));
    if(src.hasTimeStep())
      dst.setTimeStep(SEScalarTime.unload(src.timeStep));
  }
  
  public boolean hasECGInterpolator()
  {
    return ecgInterpolator!=null;
  }
  public SEElectroCardioGramWaveformInterpolator getECGInterpolator()
  {
    if(ecgInterpolator==null)
      ecgInterpolator=new SEElectroCardioGramWaveformInterpolator();
    return ecgInterpolator;
  }
  
  public boolean hasDynamicStabilization()
  {
    return dynamicStabilization!=null;
  }
  public PhysiologyEngineDynamicStabilization getDynamicStabilization()
  {
    if(this.dynamicStabilization==null)
    {
      this.dynamicStabilization = new PhysiologyEngineDynamicStabilization();
      if(this.timedStabilization!=null)
        this.timedStabilization=null;
    }
    return dynamicStabilization;
  }
  
  public boolean hasTimedStabilization()
  {
    return timedStabilization!=null;
  }
  public PhysiologyEngineTimedStabilization getTimedStabilization()
  {
    if(this.timedStabilization==null)
    {
      this.timedStabilization = new PhysiologyEngineTimedStabilization();
      if(this.dynamicStabilization!=null)
        this.dynamicStabilization=null;
    }
    return timedStabilization;
  }

  public boolean hasTimeStep()
  {
    return timeStep!=null && timeStep.isValid();
  }
  public SEScalarTime getTimeStep()
  {
    if(timeStep==null)
      timeStep=new SEScalarTime();
    return timeStep;
  }
}
