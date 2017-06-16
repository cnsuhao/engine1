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

import com.kitware.physiology.cdm.AnesthesiaMachineActions.OxygenTankPressureLossData;
import com.kitware.physiology.cdm.Properties.eSwitch;

public class SEOxygenTankPressureLoss extends SEAnesthesiaMachineAction
{
  protected eSwitch state;

  public SEOxygenTankPressureLoss()
  {
    state = eSwitch.On;
  }

  public void reset()
  {
    super.reset();
    state = eSwitch.On;
  }

  public boolean isValid()
  {
    return hasState();
  }

  public static void load(OxygenTankPressureLossData src, SEOxygenTankPressureLoss dst)
  {
    SEAnesthesiaMachineAction.load(src.getAnesthesiaMachineAction(),dst);
    if (src.getState()!=eSwitch.UNRECOGNIZED)
      dst.setState(src.getState());
  }
  public static OxygenTankPressureLossData unload(SEOxygenTankPressureLoss src)
  {
    OxygenTankPressureLossData.Builder dst = OxygenTankPressureLossData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(SEOxygenTankPressureLoss src, OxygenTankPressureLossData.Builder dst)
  {
    SEAnesthesiaMachineAction.unload(src, dst.getAnesthesiaMachineActionBuilder());
    if (src.hasState())
      dst.setState(src.state);
  }

  /*
   * State
   */
  public eSwitch getState()
  {
    return state;
  }
  public void setState(eSwitch state)
  {
    this.state = state;
  }
  public boolean hasState()
  {
    return state == null ? false : true;
  }
  public void invalidateState()
  {
    state = null;
  }

  public String toString()
  {
    return "Oxygen Tank Pressure Loss"
        + "\n\tState: " + getState();
  }
}
