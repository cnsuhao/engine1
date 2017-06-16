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
import com.kitware.physiology.cdm.PatientNutrition.NutritionData;
import com.kitware.physiology.cdm.Properties.eSwitch;

import mil.tatrc.physiology.datamodel.patient.nutrition.SENutrition;
import mil.tatrc.physiology.datamodel.properties.SEScalarTime;
import mil.tatrc.physiology.utilities.FileUtils;

public class PhysiologyEngineDynamicStabilization
{
  protected eSwitch                                                  trackingStabilization;
  protected PhysiologyEngineDynamicStabilizationCriteria             restingStabilizationCriteria;
  protected PhysiologyEngineDynamicStabilizationCriteria             feedbackStabilizationCriteria;
  protected Map<String,PhysiologyEngineDynamicStabilizationCriteria> conditionStabilizationCriteria;
  
  public PhysiologyEngineDynamicStabilization()
  {
    this.conditionStabilizationCriteria=new HashMap<String,PhysiologyEngineDynamicStabilizationCriteria>();
  }
  
  public void reset()
  {
    this.trackingStabilization=eSwitch.Off;
    this.restingStabilizationCriteria=null;
    this.feedbackStabilizationCriteria=null;
    this.conditionStabilizationCriteria.clear();
  }
  
  public void readFile(String fileName) throws ParseException
  {
    PhysiologyEngineDynamicStabilizationData.Builder builder = PhysiologyEngineDynamicStabilizationData.newBuilder();
    TextFormat.getParser().merge(FileUtils.readFile(fileName), builder);
    PhysiologyEngineDynamicStabilization.load(builder.build(), this);
  }
  public void writeFile(String fileName)
  {
    FileUtils.writeFile(fileName, PhysiologyEngineDynamicStabilization.unload(this).toString());
  }
  
  public static void load(PhysiologyEngineDynamicStabilizationData src, PhysiologyEngineDynamicStabilization dst) 
  {
    if(src.getTrackingStabilization()!=eSwitch.UNRECOGNIZED)
      dst.trackingStabilization=src.getTrackingStabilization();
    if(src.hasRestingStabilizationCriteria())
      PhysiologyEngineDynamicStabilizationCriteria.load(src.getRestingStabilizationCriteria(),dst.getRestingStabilizationCriteria());
    if(src.hasFeedbackStabilizationCriteria())
      PhysiologyEngineDynamicStabilizationCriteria.load(src.getFeedbackStabilizationCriteria(),dst.getFeedbackStabilizationCriteria());
    for(PhysiologyEngineDynamicStabilizationData.ConditionCriteriaData cData : src.getConditionStabilizationCriteriaList())
    {
      PhysiologyEngineDynamicStabilizationCriteria.load(cData.getCriteria(), dst.createConditionCriteria(cData.getName()));
    }
  }
  public static PhysiologyEngineDynamicStabilizationData unload(PhysiologyEngineDynamicStabilization src)
  {
    PhysiologyEngineDynamicStabilizationData.Builder dst = PhysiologyEngineDynamicStabilizationData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(PhysiologyEngineDynamicStabilization src, PhysiologyEngineDynamicStabilizationData.Builder dst)
  {
    if(src.hasTrackingStabilization())
      dst.setTrackingStabilization(src.trackingStabilization);
    if(src.hasRestingStabilizationCriteria())
      dst.setRestingStabilizationCriteria(PhysiologyEngineDynamicStabilizationCriteria.unload(src.restingStabilizationCriteria));
    if(src.hasFeedbackStabilizationCriteria())
      dst.setFeedbackStabilizationCriteria(PhysiologyEngineDynamicStabilizationCriteria.unload(src.feedbackStabilizationCriteria));
    for(String name : src.conditionStabilizationCriteria.keySet())
    {
      PhysiologyEngineDynamicStabilizationData.ConditionCriteriaData.Builder c = dst.addConditionStabilizationCriteriaBuilder();
      c.setName(name);
      c.setCriteria(PhysiologyEngineDynamicStabilizationCriteria.unload(src.conditionStabilizationCriteria.get(name)));
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
  
  public boolean hasRestingStabilizationCriteria()
  {
    return restingStabilizationCriteria != null;
  }
  public PhysiologyEngineDynamicStabilizationCriteria getRestingStabilizationCriteria()
  {
    if (restingStabilizationCriteria == null)
      restingStabilizationCriteria = new PhysiologyEngineDynamicStabilizationCriteria();
    return restingStabilizationCriteria;
  }
  
  public boolean hasFeedbackStabilizationCriteria()
  {
    return feedbackStabilizationCriteria != null;
  }
  public PhysiologyEngineDynamicStabilizationCriteria getFeedbackStabilizationCriteria()
  {
    if (feedbackStabilizationCriteria == null)
      feedbackStabilizationCriteria = new PhysiologyEngineDynamicStabilizationCriteria();
    return feedbackStabilizationCriteria;
  }
  
  public PhysiologyEngineDynamicStabilizationCriteria createConditionCriteria(String type)
  {
    PhysiologyEngineDynamicStabilizationCriteria c = new PhysiologyEngineDynamicStabilizationCriteria();
    this.conditionStabilizationCriteria.put(type, c);
    return c;
  }
  public boolean hasConditionCriteria(String type)
  {
    return this.conditionStabilizationCriteria.containsKey(type);
  }
  public PhysiologyEngineDynamicStabilizationCriteria getConditionCriteria(String type)
  {
    return this.conditionStabilizationCriteria.get(type);
  }
}
