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


import com.kitware.physiology.cdm.Engine.AutoSerializationData;
import com.kitware.physiology.cdm.Properties.eSwitch;

import mil.tatrc.physiology.datamodel.properties.SEScalarTime;

public class SEAutoSerialization 
{
  protected SEScalarTime period;
  protected eSwitch      periodTimeStamps;
  protected eSwitch      afterActions;
  protected eSwitch      reloadState;
  protected String       directory;
  protected String       filename;
  
  public SEAutoSerialization()
  {
    reset();
  }
  
  public void reset() 
  {
    this.period = null;
    this.periodTimeStamps = null;
    this.afterActions = null;
    this.reloadState = null;
    this.directory = null;
    this.filename = null;
  }
  
  public static void load(AutoSerializationData src, SEAutoSerialization dst)
  {
    dst.reset();

    dst.setDirectory(src.getDirectory());
    dst.setFilename(src.getFilename());
    if(src.getAfterActions()!=eSwitch.UNRECOGNIZED)
    	dst.setAfterActions(src.getAfterActions());
    if(src.hasPeriod())
      SEScalarTime.load(src.getPeriod(), dst.getPeriod());
    if(src.getPeriodTimeStamps()!=eSwitch.UNRECOGNIZED)
    	dst.setPeriodTimeStamps(src.getPeriodTimeStamps());
    if(src.getReloadState()!=eSwitch.UNRECOGNIZED)
    	dst.setReloadState(src.getReloadState());
  }
  
  public static AutoSerializationData unload(SEAutoSerialization src)
  {
    AutoSerializationData.Builder dst = AutoSerializationData.newBuilder();
    unload(src,dst);
    return dst.build();
  }  
  protected static void unload(SEAutoSerialization src, AutoSerializationData.Builder dst)
  {
    if (src.hasDirectory())
      dst.setDirectory(src.directory);
    if (src.hasFilename())
      dst.setFilename(src.filename);
    if (src.hasAfterActions())
      dst.setAfterActions(src.afterActions);    
    if (src.hasPeriod())
      dst.setPeriod(SEScalarTime.unload(src.period));
    if (src.hasPeriodTimeStamps())
      dst.setPeriodTimeStamps(src.periodTimeStamps);
    if (src.hasReloadState())
      dst.setReloadState(src.reloadState);    
  }
  
  public boolean isValid()
  {
    if (!hasPeriod())
      return false;
    if (period.getValue()<=0)
      return false;
    if (!hasPeriodTimeStamps())
      return false;
    if (!hasAfterActions())
      return false;
    if (!hasReloadState())
      return false;
    if (!hasDirectory())
      return false;
    if (!hasFilename())
      return false;
    return true;
  }

  public boolean hasPeriod()
  {
    return period == null ? false : period.isValid();
  }
  public SEScalarTime getPeriod()
  {
    if (period == null)
      period = new SEScalarTime();
    return period;
  }
  
  public eSwitch getPeriodTimeStamps()
  {
    return periodTimeStamps;
  }
  public void setPeriodTimeStamps(eSwitch v)
  {
    this.periodTimeStamps = v;
  }
  public boolean hasPeriodTimeStamps()
  {
    return (periodTimeStamps==null) ? false : true;
  }
  public void invalidatePeriodTimeStamps()
  {
    periodTimeStamps = null;
  }
  
  public eSwitch getAfterActions()
  {
    return afterActions;
  }
  public void setAfterActions(eSwitch v)
  {
    this.afterActions = v;
  }
  public boolean hasAfterActions()
  {
    return (afterActions==null) ? false : true;
  }
  public void invalidateAfterActions()
  {
    afterActions = null;
  }
  
  public eSwitch getReloadState()
  {
    return reloadState;
  }
  public void setReloadState(eSwitch v)
  {
    this.reloadState = v;
  }
  public boolean hasReloadState()
  {
    return (reloadState==null) ? false : true;
  }
  public void invalidateReloadState()
  {
    reloadState = null;
  }

  public String getDirectory()
  {
    return directory;
  }
  public void setDirectory(String dir)
  {
    this.directory = dir;
  }
  public boolean hasDirectory()
  {
    return (directory==null || directory.isEmpty()) ? false : true;
  }
  public void invalidateDirectory()
  {
    directory = "";
  }
 
  public String getFilename()
  {
    return filename;
  }
  public void setFilename(String name)
  {
    this.filename = name;
  }
  public boolean hasFilename()
  {
    return (filename==null || filename.isEmpty()) ? false : true;
  }
  public void invalidateFilename()
  {
    filename = "";
  }
}
