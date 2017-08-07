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
import com.kitware.physiology.cdm.Engine.EngineConfigurationData;

import mil.tatrc.physiology.datamodel.properties.SEScalarTime;
import mil.tatrc.physiology.datamodel.system.equipment.electrocardiogram.SEElectroCardioGramWaveformList;
import mil.tatrc.physiology.utilities.Log;

public class SEEngineConfiguration
{
  protected SETimedStabilization       timedStabilization;
  protected SEDynamicStabilization     dynamicStabilization;
  protected SEScalarTime                             timeStep;
  
  public SEEngineConfiguration()
  {
    clear();
  }
  
  public void reset()
  {
    if(timedStabilization!=null)
      this.timedStabilization.reset();
    if(dynamicStabilization!=null)
      this.dynamicStabilization.reset();
    if(timeStep!=null)
      this.timeStep.invalidate();
  }
  
  public void clear()
  {
    this.timedStabilization=null;   
    this.dynamicStabilization=null;
    this.timeStep=null;
  }
  
  public static void load(EngineConfigurationData src, SEEngineConfiguration dst)
  {
    dst.clear();
    
    switch(src.getStabilizationCriteriaCase())
    {
    case TIMEDSTABILIZATION:
      SETimedStabilization.load(src.getTimedStabilization(), dst.getTimedStabilization());
      break;
    case DYNAMICSTABILIZATION:
      SEDynamicStabilization.load(src.getDynamicStabilization(), dst.getDynamicStabilization());
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
  
  public static EngineConfigurationData unload(SEEngineConfiguration src)
  {
    EngineConfigurationData.Builder dst = EngineConfigurationData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(SEEngineConfiguration src, EngineConfigurationData.Builder dst)
  {
    if(src.hasTimedStabilization())
      dst.setTimedStabilization(SETimedStabilization.unload(src.timedStabilization));
    if(src.hasDynamicStabilization())
      dst.setDynamicStabilization(SEDynamicStabilization.unload(src.dynamicStabilization));
    if(src.hasTimeStep())
      dst.setTimeStep(SEScalarTime.unload(src.timeStep));
  }
  
  public boolean hasDynamicStabilization()
  {
    return dynamicStabilization!=null;
  }
  public SEDynamicStabilization getDynamicStabilization()
  {
    if(this.dynamicStabilization==null)
    {
      this.dynamicStabilization = new SEDynamicStabilization();
      if(this.timedStabilization!=null)
        this.timedStabilization=null;
    }
    return dynamicStabilization;
  }
  
  public boolean hasTimedStabilization()
  {
    return timedStabilization!=null;
  }
  public SETimedStabilization getTimedStabilization()
  {
    if(this.timedStabilization==null)
    {
      this.timedStabilization = new SETimedStabilization();
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
