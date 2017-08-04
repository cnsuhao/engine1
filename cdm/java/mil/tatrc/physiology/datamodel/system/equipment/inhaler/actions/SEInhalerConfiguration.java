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

package mil.tatrc.physiology.datamodel.system.equipment.inhaler.actions;

import org.jfree.util.Log;

import com.kitware.physiology.cdm.InhalerActions.InhalerConfigurationData;

import mil.tatrc.physiology.datamodel.substance.SESubstanceManager;
import mil.tatrc.physiology.datamodel.system.equipment.inhaler.SEInhaler;

public class SEInhalerConfiguration extends SEInhalerAction
{
  protected SEInhaler configuration;
  protected String    configurationFile;
  
  public SEInhalerConfiguration()
  {
  }
  
  public SEInhalerConfiguration(SEInhalerConfiguration other)
  {
    this();
    copy(other);    
  }
  
  public void copy(SEInhalerConfiguration other)
  {
    if(this==other)
      return;
    super.copy(other);
    this.configuration.copy(other.configuration);
    this.configurationFile=other.configurationFile;
  }
  
  public void reset()
  {
    super.reset();
    
    if (this.configuration != null)
      this.configuration.reset();
    if (this.configurationFile != null)
      this.configurationFile="";
  }
  
  public boolean isValid()
  {
    return hasConfiguration() || hasConfigurationFile();
  }
  
  public static void load(InhalerConfigurationData src, SEInhalerConfiguration dst, SESubstanceManager subMgr)
  {
    dst.reset();
    switch(src.getOptionCase())
    {
    case CONFIGURATIONFILE:
      dst.configurationFile = src.getConfigurationFile();
      break;
    case CONFIGURATION:
      SEInhaler.load(src.getConfiguration(),dst.getConfiguration(),subMgr);
      break;
    default:
    	Log.error("Unknown InhalerConfiguationData OptionCase");
    }
  }
  public static InhalerConfigurationData unload(SEInhalerConfiguration src)
  {
    InhalerConfigurationData.Builder dst = InhalerConfigurationData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(SEInhalerConfiguration src, InhalerConfigurationData.Builder dst)
  {
    if(src.hasConfiguration())
      dst.setConfiguration(SEInhaler.unload(src.configuration));
    else if(src.hasConfigurationFile())
      dst.setConfigurationFile(src.configurationFile);
  }
  
  public boolean hasConfiguration()
  {
    return this.configuration!=null;
  }
  public SEInhaler getConfiguration()
  {
    if(this.configuration==null)
      this.configuration=new SEInhaler();
    return this.configuration;
  }
  
  public boolean hasConfigurationFile()
  {
    return this.configurationFile!=null&&!this.configurationFile.isEmpty();
  }
  public String getConfigurationFile()
  {
    return this.configurationFile;
  }
  public void setConfigurationFile(String s)
  {
    this.configurationFile = s;
  }
  
  public String toString()
  {
    String str = "Inhaler Configuration";
    if(hasConfiguration())
    {
      str += configuration.toString();
    }
    
    if(this.hasConfigurationFile())
      str +="\n\tInhaler File: "+this.configurationFile;
    
    return str;
  }
}