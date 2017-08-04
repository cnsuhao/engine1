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

package mil.tatrc.physiology.datamodel.patient.actions;

import com.kitware.physiology.cdm.PatientActions.CardiacArrestData;
import com.kitware.physiology.cdm.Properties.eSwitch;

public class SECardiacArrest extends SEPatientAction
{
  protected eSwitch state;
  
  public SECardiacArrest()
  {
    state = null;
  }
  
  public void copy(SECardiacArrest other)
  {
    if(this==other)
      return;
    super.copy(other);
    state = other.state;
  }
  
  public void reset()
  {
    super.reset();
    state = null;
  }
  
  public boolean isValid()
  {
    return hasState();
  }
  
  public static void load(CardiacArrestData src, SECardiacArrest dst)
  {
    SEPatientAction.load(src.getPatientAction(), dst);
    if(src.getState()!=eSwitch.UNRECOGNIZED)
    	dst.state = src.getState();
  }
  
  public static CardiacArrestData unload(SECardiacArrest src)
  {
    CardiacArrestData.Builder dst = CardiacArrestData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  
  protected static void unload(SECardiacArrest src, CardiacArrestData.Builder dst)
  {
    SEPatientAction.unload(src,dst.getPatientActionBuilder());
    if (src.hasState())
      dst.setState(src.state);
  }
  
  public eSwitch getState()
  {
    return state;
  }
  
  public void setState(eSwitch onOrOff)
  {
    state = onOrOff;
  }
  
  public boolean hasState()
  {
    return state==null||state==eSwitch.UNRECOGNIZED ? false : true;
  }
  
  public String toString()
  {
    return "Cardiac Arrest"
        + "\n\tState: " + getState();
  }
}
