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

package mil.tatrc.physiology.datamodel.system.environment.actions;

import com.kitware.physiology.cdm.EnvironmentActions.ChangeEnvironmentConditionsData;

import mil.tatrc.physiology.datamodel.substance.SESubstanceManager;
import mil.tatrc.physiology.datamodel.system.environment.SEEnvironmentalConditions;

public class SEChangeEnvironmentConditions extends SEEnvironmentAction
{
  protected SEEnvironmentalConditions conditions;
  protected String                    conditionsFile;
  
  public SEChangeEnvironmentConditions()
  {
    this.conditions=new SEEnvironmentalConditions();
  }
  
  public SEChangeEnvironmentConditions(SEChangeEnvironmentConditions other)
  {
    this();
    copy(other);    
  }
  
  public void copy(SEChangeEnvironmentConditions other)
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
  
  public static void load(ChangeEnvironmentConditionsData src, SEChangeEnvironmentConditions dst, SESubstanceManager subMgr)
  {
    SEEnvironmentAction.load(src.getEnvironmentAction(), dst);
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
  public static ChangeEnvironmentConditionsData unload(SEChangeEnvironmentConditions src)
  {
    ChangeEnvironmentConditionsData.Builder dst = ChangeEnvironmentConditionsData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(SEChangeEnvironmentConditions src, ChangeEnvironmentConditionsData.Builder dst)
  {
    SEEnvironmentAction.unload(src, dst.getEnvironmentActionBuilder());
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
      return "Environment Configuration : "+conditions.toString();
    else if(this.hasConditionsFile())
      return "Envrioment Configuration:"
          + "\n\tConditionsFile: "+this.conditionsFile;
    else
      return "Action not specified properly";
  }
}