/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.system.equipment.anesthesia.actions;
import org.jfree.util.Log;

import com.kitware.physiology.cdm.AnesthesiaMachine.AnesthesiaMachineData;
import com.kitware.physiology.cdm.AnesthesiaMachineActions.AnesthesiaMachineConfigurationData;

import mil.tatrc.physiology.datamodel.substance.SESubstanceManager;
import mil.tatrc.physiology.datamodel.system.environment.SEEnvironmentalConditions;
import mil.tatrc.physiology.datamodel.system.equipment.anesthesia.SEAnesthesiaMachine;

public class SEAnesthesiaMachineConfiguration extends SEAnesthesiaMachineAction
{
  protected SEAnesthesiaMachine configuration;
  protected String              configurationFile;
  
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
  
  public static void load(AnesthesiaMachineConfigurationData src, SEAnesthesiaMachineConfiguration dst, SESubstanceManager subMgr)
  {
    SEAnesthesiaMachineAction.load(src.getAnesthesiaMachineAction(),dst);
    switch(src.getOptionCase())
    {
    case CONFIGURATIONFILE:
      dst.configurationFile = src.getConfigurationFile();
      break;
    case CONFIGURATION:
      SEAnesthesiaMachine.load(src.getConfiguration(),dst.getConfiguration(),subMgr);
      break;
    default:
    	Log.error("Unknown AnesthesiaMachineConfigurationData Option");
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
    if(src.hasConfiguration())
      dst.setConfiguration(SEAnesthesiaMachine.unload(src.configuration));
    else if(src.hasConfigurationFile())
      dst.setConfigurationFile(src.configurationFile);
  }
  
  public boolean hasConfiguration()
  {
    return this.configuration!=null;
  }
  public SEAnesthesiaMachine getConfiguration()
  {
    if(this.configuration==null)
      this.configuration=new SEAnesthesiaMachine();
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
    String str = "Anesthesia Machine Configuration";
    if(hasConfiguration())
    {
      str += configuration.toString();
    }
    if(this.hasConfigurationFile())
      str +="\n\tAnesthesia Machine File: "+this.configurationFile;
    return str;
  }
}