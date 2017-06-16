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

import com.kitware.physiology.cdm.EngineConfiguration.PhysiologyEngineDynamicStabilizationData;

import mil.tatrc.physiology.datamodel.properties.SEScalarTime;

public class PhysiologyEngineDynamicStabilizationCriteria
{
  public class PropertyConvergence
  {
    public String name;
    public double percentDifference;
  }
  
  protected SEScalarTime convergenceTime;
  protected SEScalarTime minimumReactionTime;
  protected SEScalarTime maximumAllowedStabilizationTime;
  protected List<PropertyConvergence> properties=new ArrayList<PropertyConvergence>();
  
  public void reset()
  {
    this.convergenceTime=null;
    this.minimumReactionTime=null;
    this.maximumAllowedStabilizationTime=null;
    this.properties.clear();
  }

  public static void load(PhysiologyEngineDynamicStabilizationData.CriteriaData src, PhysiologyEngineDynamicStabilizationCriteria dst)
  {
    if(src.hasConvergenceTime())
      SEScalarTime.load(src.getConvergenceTime(), dst.getConvergenceTime());
    if(src.hasMinimumReactionTime())
      SEScalarTime.load(src.getMinimumReactionTime(),dst.getMinimumReactionTime());
    if(src.hasMaximumAllowedStabilizationTime())
      SEScalarTime.load(src.getMaximumAllowedStabilizationTime(),dst.getMaximumAllowedStabilizationTime());      
    for(PhysiologyEngineDynamicStabilizationData.PropertyConvergenceData pcData : src.getPropertyConvergenceList())
    {
      dst.createProperty(pcData.getPercentDifference(),pcData.getName());
    }
  }
  public static PhysiologyEngineDynamicStabilizationData.CriteriaData unload(PhysiologyEngineDynamicStabilizationCriteria src)
  {
    PhysiologyEngineDynamicStabilizationData.CriteriaData.Builder dst = PhysiologyEngineDynamicStabilizationData.CriteriaData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  public static void unload(PhysiologyEngineDynamicStabilizationCriteria src, PhysiologyEngineDynamicStabilizationData.CriteriaData.Builder dst)
  {
    if(src.hasConvergenceTime())
      dst.setConvergenceTime(SEScalarTime.unload(src.convergenceTime));
    if(src.hasMinimumReactionTime())
      dst.setMinimumReactionTime(SEScalarTime.unload(src.minimumReactionTime));
    if(src.hasMaximumAllowedStabilizationTime())
      dst.setMaximumAllowedStabilizationTime(SEScalarTime.unload(src.maximumAllowedStabilizationTime));
    for(PropertyConvergence pc : src.properties)
    {
      PhysiologyEngineDynamicStabilizationData.PropertyConvergenceData.Builder pcData = dst.addPropertyConvergenceBuilder();
      pcData.setName(pc.name);
      pcData.setPercentDifference(pc.percentDifference);
    }
  }
  
  public boolean hasConvergenceTime()
  {
    return convergenceTime == null ? false : convergenceTime.isValid();
  }
  public SEScalarTime getConvergenceTime()
  {
    if (convergenceTime == null)
      convergenceTime = new SEScalarTime();
    return convergenceTime;
  }
  
  public boolean hasMinimumReactionTime()
  {
    return minimumReactionTime == null ? false : minimumReactionTime.isValid();
  }
  public SEScalarTime getMinimumReactionTime()
  {
    if (minimumReactionTime == null)
      minimumReactionTime = new SEScalarTime();
    return minimumReactionTime;
  }
  
  public boolean hasMaximumAllowedStabilizationTime()
  {
    return maximumAllowedStabilizationTime == null ? false : maximumAllowedStabilizationTime.isValid();
  }
  public SEScalarTime getMaximumAllowedStabilizationTime()
  {
    if (maximumAllowedStabilizationTime == null)
      maximumAllowedStabilizationTime = new SEScalarTime();
    return maximumAllowedStabilizationTime;
  }
  
  public void createProperty(double percentDifference, String property)
  {
    PropertyConvergence pc = new PropertyConvergence();
    pc.name=property;
    pc.percentDifference=percentDifference;
    this.properties.add(pc);
  }
  List<PropertyConvergence> getProperties()
  {
    return Collections.unmodifiableList(this.properties);
  }
}
