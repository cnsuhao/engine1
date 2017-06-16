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

package mil.tatrc.physiology.datamodel.actions;

import com.kitware.physiology.cdm.Actions.AdvanceTimeData;

import mil.tatrc.physiology.datamodel.properties.SEScalarTime;

public class SEAdvanceTime extends SEAction 
{
  protected SEScalarTime time;
  
  public SEAdvanceTime() 
  {
    time = null;
  }
  
  public void copy(SEAdvanceTime other)
  {
    if(this==other)
      return;
    super.copy(other);
  }
  
  public void reset() 
  {
    super.reset();
    if (hasTime())
      time.invalidate();
  }
  
  public boolean isValid()
  {
    return hasTime();
  }

  public static void load(AdvanceTimeData src, SEAdvanceTime dst) 
  {
    SEAction.load(src.getAction(), dst);
    if(src.hasTime())
      SEScalarTime.load(src.getTime(),dst.getTime());
  }
  public static AdvanceTimeData unload(SEAdvanceTime src)
  {
    AdvanceTimeData.Builder dst = AdvanceTimeData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(SEAdvanceTime src, AdvanceTimeData.Builder dst)
  {
    SEAction.unload(src, dst.getActionBuilder());
    if (src.hasTime())
      dst.setTime(SEScalarTime.unload(src.time));
  }
  
  public boolean hasTime()
  {
    return time == null ? false : time.isValid();
  }
  public SEScalarTime getTime() 
  {
    if (time == null)
      time = new SEScalarTime();
    return time;
  }
  
  public String toString() 
  {
    return "Advance Time" 
        + "\n\tTime: " + getTime();
  }
}
