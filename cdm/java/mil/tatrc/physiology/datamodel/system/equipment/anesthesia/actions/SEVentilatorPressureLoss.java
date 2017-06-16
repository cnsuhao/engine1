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

import com.kitware.physiology.cdm.AnesthesiaMachineActions.VentilatorPressureLossData;

import mil.tatrc.physiology.datamodel.properties.SEScalar0To1;

public class SEVentilatorPressureLoss extends SEAnesthesiaMachineAction
{
  protected SEScalar0To1 severity;
  
  public SEVentilatorPressureLoss()
  {
    severity = null;
  }
  
  public void reset()
  {
    super.reset();
    if (severity != null)
      severity.invalidate();
  }
  
  public boolean isValid()
  {
    return hasSeverity();
  }
  
  public static void load(VentilatorPressureLossData src, SEVentilatorPressureLoss dst)
  {
    SEAnesthesiaMachineAction.load(src.getAnesthesiaMachineAction(),dst);
    if(src.hasSeverity())
      SEScalar0To1.load(src.getSeverity(),dst.getSeverity());
  }
  public static VentilatorPressureLossData unload(SEVentilatorPressureLoss src)
  {
    VentilatorPressureLossData.Builder dst = VentilatorPressureLossData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(SEVentilatorPressureLoss src, VentilatorPressureLossData.Builder dst)
  {
    SEAnesthesiaMachineAction.unload(src, dst.getAnesthesiaMachineActionBuilder());
    if (src.hasSeverity())
      dst.setSeverity(SEScalar0To1.unload(src.severity));
  }
  
  /*
   * Severity
   */
  public boolean hasSeverity()
  {
    return severity == null ? false : severity.isValid();
  }
  public SEScalar0To1 getSeverity()
  {
    if (severity == null)
      severity = new SEScalar0To1();
    return severity;
  }
  
  public String toString()
  {
    if (severity != null)
      return "Ventilator Pressure Loss"
          + "\n\tSeverity: " + getSeverity();
    else
      return "Action not specified properly";
  }
}
