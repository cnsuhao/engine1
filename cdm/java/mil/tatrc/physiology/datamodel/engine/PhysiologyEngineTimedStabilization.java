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

import java.util.*;

import com.google.protobuf.TextFormat;
import com.google.protobuf.TextFormat.ParseException;
import com.kitware.physiology.cdm.EngineConfiguration.PhysiologyEngineDynamicStabilizationData;
import com.kitware.physiology.cdm.EngineConfiguration.PhysiologyEngineTimedStabilizationData;
import com.kitware.physiology.cdm.Properties.eSwitch;

import mil.tatrc.physiology.datamodel.properties.SEScalarTime;
import mil.tatrc.physiology.utilities.FileUtils;

public class PhysiologyEngineTimedStabilization
{
  protected eSwitch                  trackingStabilization;
  protected SEScalarTime             restingStabilizationTime;
  protected SEScalarTime             feedbackStabilizationTime;
  protected Map<String,SEScalarTime> conditionStabilizationTimes;
  
  public PhysiologyEngineTimedStabilization()
  {
    super();
    this.conditionStabilizationTimes=new HashMap<String,SEScalarTime>();
  }
  
  public void reset()
  {
    reset();
    this.trackingStabilization=eSwitch.Off;
    this.restingStabilizationTime=null;
    this.feedbackStabilizationTime=null;
    this.conditionStabilizationTimes.clear();
  }
  
  public void readFile(String fileName) throws ParseException
  {
    PhysiologyEngineTimedStabilizationData.Builder builder = PhysiologyEngineTimedStabilizationData.newBuilder();
    TextFormat.getParser().merge(FileUtils.readFile(fileName), builder);
    PhysiologyEngineTimedStabilization.load(builder.build(), this);
  }
  public void writeFile(String fileName)
  {
    FileUtils.writeFile(fileName, PhysiologyEngineTimedStabilization.unload(this).toString());
  }
  
  public static void load(PhysiologyEngineTimedStabilizationData src, PhysiologyEngineTimedStabilization dst) 
  {
    if(src.getTrackingStabilization()!=eSwitch.UNRECOGNIZED)
      dst.trackingStabilization=src.getTrackingStabilization();
    if(src.hasRestingStabilizationTime())
      SEScalarTime.load(src.getRestingStabilizationTime(),dst.getRestingStabilizationTime());
    if(src.hasFeedbackStabilizationTime())
      SEScalarTime.load(src.getFeedbackStabilizationTime(),dst.getFeedbackStabilizationTime());
    for(PhysiologyEngineTimedStabilizationData.ConditionTimingData c : src.getConditionStabilizationList())
    {
      SEScalarTime.load(c.getStabilizationTime(),dst.createConditionStabilizationTime(c.getName()));     
    }
  }
  
  public static PhysiologyEngineTimedStabilizationData unload(PhysiologyEngineTimedStabilization src)
  {
    PhysiologyEngineTimedStabilizationData.Builder dst = PhysiologyEngineTimedStabilizationData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  
  protected static void unload(PhysiologyEngineTimedStabilization src, PhysiologyEngineTimedStabilizationData.Builder dst)
  {
    if(src.hasTrackingStabilization())
      dst.setTrackingStabilization(src.trackingStabilization);
    if(src.hasRestingStabilizationTime())
      dst.setRestingStabilizationTime(SEScalarTime.unload(src.restingStabilizationTime));
    if(src.hasFeedbackStabilizationTime())
      dst.setFeedbackStabilizationTime(SEScalarTime.unload(src.feedbackStabilizationTime));
    for(String name : src.conditionStabilizationTimes.keySet())
    {
      PhysiologyEngineTimedStabilizationData.ConditionTimingData.Builder c = dst.addConditionStabilizationBuilder();
      c.setName(name);
      c.setStabilizationTime(SEScalarTime.unload(src.conditionStabilizationTimes.get(name)));
    }
  }
  
  public boolean hasTrackingStabilization()
  {
    return this.trackingStabilization!=null;
  }
  public eSwitch isTrackingStabilization()
  {
    return this.trackingStabilization;
  }
  public void TrackStabilization(eSwitch b)
  {
    this.trackingStabilization=b;
  }
  
  public boolean hasRestingStabilizationTime()
  {
    return restingStabilizationTime == null ? false : restingStabilizationTime.isValid();
  }
  public SEScalarTime getRestingStabilizationTime()
  {
    if (restingStabilizationTime == null)
      restingStabilizationTime = new SEScalarTime();
    return restingStabilizationTime;
  }
  
  public boolean hasFeedbackStabilizationTime()
  {
    return feedbackStabilizationTime == null ? false : feedbackStabilizationTime.isValid();
  }
  public SEScalarTime getFeedbackStabilizationTime()
  {
    if (feedbackStabilizationTime == null)
      feedbackStabilizationTime = new SEScalarTime();
    return feedbackStabilizationTime;
  }
  
  public SEScalarTime createConditionStabilizationTime(String type)
  {
    SEScalarTime stabilizationTime = new SEScalarTime();
    this.conditionStabilizationTimes.put(type, stabilizationTime);
    return stabilizationTime;
  }
  public boolean hasConditionStabilizationTime(String type)
  {
    return this.conditionStabilizationTimes.containsKey(type);
  }
  public SEScalarTime getConditionStabilizationTime(String type)
  {
    return this.conditionStabilizationTimes.get(type);
  }
}
