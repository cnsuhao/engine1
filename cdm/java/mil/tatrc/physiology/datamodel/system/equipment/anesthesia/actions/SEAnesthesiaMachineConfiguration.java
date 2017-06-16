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

package mil.tatrc.physiology.datamodel.system.equipment.anesthesia.actions;
import com.kitware.physiology.cdm.AnesthesiaMachine.AnesthesiaMachineData;
import com.kitware.physiology.cdm.AnesthesiaMachineActions.AnesthesiaMachineConfigurationData;

import mil.tatrc.physiology.datamodel.substance.SESubstanceManager;
import mil.tatrc.physiology.datamodel.system.environment.SEEnvironmentalConditions;
import mil.tatrc.physiology.datamodel.system.equipment.anesthesia.SEAnesthesiaMachine;

public class SEAnesthesiaMachineConfiguration extends SEAnesthesiaMachineAction
{
  protected SEAnesthesiaMachine anesthesiaMachine;
  protected String              anesthesiaMachineFile;
  
  public SEAnesthesiaMachineConfiguration()
  {
    
  }
  
  public SEAnesthesiaMachineConfiguration(SEAnesthesiaMachineConfiguration other)
  {
    this();
    copy(other);    
  }
  
  public void copy(SEAnesthesiaMachineConfiguration other)
  {
    if(this==other)
      return;
    super.copy(other);
    this.anesthesiaMachine.copy(other.anesthesiaMachine);
    this.anesthesiaMachineFile=other.anesthesiaMachineFile;
  }
  
  public void reset()
  {
    super.reset();
    
    if (this.anesthesiaMachine != null)
      this.anesthesiaMachine.reset();
    if (this.anesthesiaMachineFile != null)
      this.anesthesiaMachineFile="";
  }
  
  public boolean isValid()
  {
    return hasAnesthesiaMachine() || hasAnesthesiaMachineFile();
  }
  
  public static void load(AnesthesiaMachineConfigurationData src, SEAnesthesiaMachineConfiguration dst, SESubstanceManager subMgr)
  {
    SEAnesthesiaMachineAction.load(src.getAnesthesiaMachineAction(),dst);
    switch(src.getOptionCase())
    {
    case ANESTHESIAMACHINEFILE:
      dst.anesthesiaMachineFile = src.getAnesthesiaMachineFile();
      break;
    case ANESTHESIAMACHINE:
      SEAnesthesiaMachine.load(src.getAnesthesiaMachine(),dst.getAnesthesiaMachine(),subMgr);
      break;
    }
  }
  public static AnesthesiaMachineConfigurationData unload(SEAnesthesiaMachineConfiguration src)
  {
    AnesthesiaMachineConfigurationData.Builder dst = AnesthesiaMachineConfigurationData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(SEAnesthesiaMachineConfiguration src, AnesthesiaMachineConfigurationData.Builder dst)
  {
    SEAnesthesiaMachineAction.unload(src, dst.getAnesthesiaMachineActionBuilder());
    if(src.hasAnesthesiaMachine())
      dst.setAnesthesiaMachine(SEAnesthesiaMachine.unload(src.anesthesiaMachine));
    else if(src.hasAnesthesiaMachineFile())
      dst.setAnesthesiaMachineFile(src.anesthesiaMachineFile);
  }
  
  public boolean hasAnesthesiaMachine()
  {
    return this.anesthesiaMachine!=null;
  }
  public SEAnesthesiaMachine getAnesthesiaMachine()
  {
    if(this.anesthesiaMachine==null)
      this.anesthesiaMachine=new SEAnesthesiaMachine();
    return this.anesthesiaMachine;
  }
  
  public boolean hasAnesthesiaMachineFile()
  {
    return this.anesthesiaMachineFile!=null&&!this.anesthesiaMachineFile.isEmpty();
  }
  public String getAnesthesiaMachineFile()
  {
    return this.anesthesiaMachineFile;
  }
  public void setAnesthesiaMachineFile(String s)
  {
    this.anesthesiaMachineFile = s;
  }
  
  public String toString()
  {
    String str = "Anesthesia Machine Configuration";
    if(hasAnesthesiaMachine())
    {
      str += anesthesiaMachine.toString();
    }
    if(this.hasAnesthesiaMachineFile())
      str +="\n\tAnesthesia Machine File: "+this.anesthesiaMachineFile;
    return str;
  }
}