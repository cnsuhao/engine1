/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.system.environment.conditions;

import com.kitware.physiology.cdm.EnvironmentConditions.InitialEnvironmentConditionsData;

import mil.tatrc.physiology.datamodel.substance.SESubstanceManager;
import mil.tatrc.physiology.datamodel.system.environment.SEEnvironmentalConditions;

public class SEInitialEnvironmentConditions extends SEEnvironmentCondition
{
  protected SEEnvironmentalConditions conditions;
  protected String                    conditionsFile;
  
  public SEInitialEnvironmentConditions()
  {
    this.conditions=new SEEnvironmentalConditions();
  }
  
  public SEInitialEnvironmentConditions(SEInitialEnvironmentConditions other)
  {
    this();
    copy(other);    
  }
  
  public void copy(SEInitialEnvironmentConditions other)
  {
    if(this==other)
      return;
    super.copy(other);
    this.conditions.copy(other.conditions);
    this.conditionsFile=other.conditionsFile;
  }
  
  public void reset()
  {
    super.reset();
    this.conditions.reset();
    this.conditionsFile="";
  }
  
  public boolean isValid()
  {
    return hasConditions() || hasConditionsFile();
  }
  
  public static void load(InitialEnvironmentConditionsData src, SEInitialEnvironmentConditions dst, SESubstanceManager subMgr)
  {
    SEEnvironmentCondition.load(src.getEnvironmentCondition(), dst);
    switch(src.getOptionCase())
    {
    case CONDITIONSFILE:
      dst.conditionsFile = src.getConditionsFile();
      break;
    case CONDITIONS:
      SEEnvironmentalConditions.load(src.getConditions(),dst.getConditions(),subMgr);
      break;
    }
  }
  public static InitialEnvironmentConditionsData unload(SEInitialEnvironmentConditions src)
  {
    InitialEnvironmentConditionsData.Builder dst = InitialEnvironmentConditionsData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(SEInitialEnvironmentConditions src, InitialEnvironmentConditionsData.Builder dst)
  {
    SEEnvironmentCondition.unload(src, dst.getEnvironmentConditionBuilder());
    if(src.hasConditions())
      dst.setConditions(SEEnvironmentalConditions.unload(src.conditions));
    else if(src.hasConditionsFile())
      dst.setConditionsFile(src.conditionsFile);
  }
  
  public boolean hasConditions()
  {
    return this.conditions!=null;
  }
  public SEEnvironmentalConditions getConditions()
  {
    return this.conditions;
  }
  
  public boolean hasConditionsFile()
  {
    return this.conditionsFile!=null&&!this.conditionsFile.isEmpty();
  }
  public String getConditionsFile()
  {
    return this.conditionsFile;
  }
  public void setConditionsFile(String s)
  {
    this.conditionsFile = s;
  }
  
  public String toString()
  {
    if (conditions != null)
      return "Initial Environment Configuration : "+conditions.toString();
    else if(this.hasConditionsFile())
      return "Initial Envrioment Configuration:"
          + "\n\tConditionsFile: "+this.conditionsFile;
    else
      return "Condition not specified properly";
  }
}