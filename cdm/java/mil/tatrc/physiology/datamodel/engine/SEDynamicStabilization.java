/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
package mil.tatrc.physiology.datamodel.engine;

import java.util.*;

import com.google.protobuf.TextFormat;
import com.google.protobuf.TextFormat.ParseException;
import com.kitware.physiology.cdm.Engine.DynamicStabilizationData;
import com.kitware.physiology.cdm.PatientNutrition.NutritionData;
import com.kitware.physiology.cdm.Properties.eSwitch;

import mil.tatrc.physiology.datamodel.patient.nutrition.SENutrition;
import mil.tatrc.physiology.datamodel.properties.SEScalarTime;
import mil.tatrc.physiology.utilities.FileUtils;

public class SEDynamicStabilization
{
  protected eSwitch                                             trackingStabilization;
  protected SEDynamicStabilizationEngineConvergence             restingConvergence;
  protected SEDynamicStabilizationEngineConvergence             feedbackConvergence;
  protected Map<String,SEDynamicStabilizationEngineConvergence> conditionConvergence;
  
  public SEDynamicStabilization()
  {
    this.conditionConvergence=new HashMap<String,SEDynamicStabilizationEngineConvergence>();
  }
  
  public void reset()
  {
    this.trackingStabilization=eSwitch.Off;
    this.restingConvergence=null;
    this.feedbackConvergence=null;
    this.conditionConvergence.clear();
  }
  
  public void readFile(String fileName) throws ParseException
  {
    DynamicStabilizationData.Builder builder = DynamicStabilizationData.newBuilder();
    TextFormat.getParser().merge(FileUtils.readFile(fileName), builder);
    SEDynamicStabilization.load(builder.build(), this);
  }
  public void writeFile(String fileName)
  {
    FileUtils.writeFile(fileName, SEDynamicStabilization.unload(this).toString());
  }
  
  public static void load(DynamicStabilizationData src, SEDynamicStabilization dst) 
  {
    if(src.getTrackingStabilization()!=eSwitch.UNRECOGNIZED && src.getTrackingStabilization()!=eSwitch.NullSwitch)
      dst.trackingStabilization=src.getTrackingStabilization();
    if(src.hasRestingConvergence())
      SEDynamicStabilizationEngineConvergence.load(src.getRestingConvergence(),dst.getRestingConvergence());
    if(src.hasFeedbackConvergence())
      SEDynamicStabilizationEngineConvergence.load(src.getFeedbackConvergence(),dst.getFeedbackConvergence());
    for(String name : src.getConditionConvergenceMap().keySet())
    {
      SEDynamicStabilizationEngineConvergence.load(src.getConditionConvergenceMap().get(name), dst.createConditionConvergence(name));
    }
  }
  public static DynamicStabilizationData unload(SEDynamicStabilization src)
  {
    DynamicStabilizationData.Builder dst = DynamicStabilizationData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(SEDynamicStabilization src, DynamicStabilizationData.Builder dst)
  {
    dst.setTrackingStabilization(src.trackingStabilization);
    if(src.hasRestingConvergence())
      dst.setRestingConvergence(SEDynamicStabilizationEngineConvergence.unload(src.restingConvergence));
    if(src.hasFeedbackConvergence())
      dst.setFeedbackConvergence(SEDynamicStabilizationEngineConvergence.unload(src.feedbackConvergence));
    for(String name : src.conditionConvergence.keySet())
    {
    	dst.putConditionConvergence(name, SEDynamicStabilizationEngineConvergence.unload(src.conditionConvergence.get(name)));
    }
  }
  
  public eSwitch isTrackingStabilization()
  {
    return this.trackingStabilization;
  }
  public void TrackStabilization(eSwitch b)
  {
    this.trackingStabilization = (b==eSwitch.NullSwitch) ? eSwitch.Off : b;
  }
  
  public boolean hasRestingConvergence()
  {
    return restingConvergence != null;
  }
  public SEDynamicStabilizationEngineConvergence getRestingConvergence()
  {
    if (restingConvergence == null)
      restingConvergence = new SEDynamicStabilizationEngineConvergence();
    return restingConvergence;
  }
  
  public boolean hasFeedbackConvergence()
  {
    return feedbackConvergence != null;
  }
  public SEDynamicStabilizationEngineConvergence getFeedbackConvergence()
  {
    if (feedbackConvergence == null)
    	feedbackConvergence = new SEDynamicStabilizationEngineConvergence();
    return feedbackConvergence;
  }
  
  public SEDynamicStabilizationEngineConvergence createConditionConvergence(String type)
  {
    SEDynamicStabilizationEngineConvergence c = new SEDynamicStabilizationEngineConvergence();
    this.conditionConvergence.put(type, c);
    return c;
  }
  public boolean hasConditionConvergence(String type)
  {
    return this.conditionConvergence.containsKey(type);
  }
  public SEDynamicStabilizationEngineConvergence getConditionConvergence(String type)
  {
    return this.conditionConvergence.get(type);
  }
}
