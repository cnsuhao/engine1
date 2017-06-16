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

import com.kitware.physiology.cdm.InhalerActions.InhalerConfigurationData;

import mil.tatrc.physiology.datamodel.substance.SESubstanceManager;
import mil.tatrc.physiology.datamodel.system.equipment.inhaler.SEInhaler;

public class SEInhalerConfiguration extends SEInhalerAction
{
  protected SEInhaler inhaler;
  protected String    inhalerFile;
  
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
    this.inhaler.copy(other.inhaler);
    this.inhalerFile=other.inhalerFile;
  }
  
  public void reset()
  {
    super.reset();
    
    if (this.inhaler != null)
      this.inhaler.reset();
    if (this.inhalerFile != null)
      this.inhalerFile="";
  }
  
  public boolean isValid()
  {
    return hasInhaler() || hasInhalerFile();
  }
  
  public static void load(InhalerConfigurationData src, SEInhalerConfiguration dst, SESubstanceManager subMgr)
  {
    dst.reset();
    switch(src.getOptionCase())
    {
    case INHALERFILE:
      dst.inhalerFile = src.getInhalerFile();
      break;
    case INHALER:
      SEInhaler.load(src.getInhaler(),dst.getInhaler(),subMgr);
      break;
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
    if(src.hasInhaler())
      dst.setInhaler(SEInhaler.unload(src.inhaler));
    else if(src.hasInhalerFile())
      dst.setInhalerFile(src.inhalerFile);
  }
  
  public boolean hasInhaler()
  {
    return this.inhaler!=null;
  }
  public SEInhaler getInhaler()
  {
    if(this.inhaler==null)
      this.inhaler=new SEInhaler();
    return this.inhaler;
  }
  
  public boolean hasInhalerFile()
  {
    return this.inhalerFile!=null&&!this.inhalerFile.isEmpty();
  }
  public String getInhalerFile()
  {
    return this.inhalerFile;
  }
  public void setInhalerFile(String s)
  {
    this.inhalerFile = s;
  }
  
  public String toString()
  {
    String str = "Inhaler Configuration";
    if(hasInhaler())
    {
      str += inhaler.toString();
    }
    
    if(this.hasInhalerFile())
      str +="\n\tInhaler File: "+this.inhalerFile;
    
    return str;
  }
}