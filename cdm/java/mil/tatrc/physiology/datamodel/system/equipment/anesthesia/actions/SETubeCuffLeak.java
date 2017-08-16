/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.system.equipment.anesthesia.actions;

import com.kitware.physiology.cdm.AnesthesiaMachineActions.TubeCuffLeakData;

import mil.tatrc.physiology.datamodel.properties.SEScalar0To1;

public class SETubeCuffLeak extends SEAnesthesiaMachineAction
{
  protected SEScalar0To1 severity;
  
  public SETubeCuffLeak()
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
  
  public static void load(TubeCuffLeakData src, SETubeCuffLeak dst)
  {
    SEAnesthesiaMachineAction.load(src.getAnesthesiaMachineAction(),dst);
    if(src.hasSeverity())
      SEScalar0To1.load(src.getSeverity(),dst.getSeverity());
  }
  public static TubeCuffLeakData unload(SETubeCuffLeak src)
  {
    TubeCuffLeakData.Builder dst = TubeCuffLeakData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(SETubeCuffLeak src, TubeCuffLeakData.Builder dst)
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
      return "Tube Cuff Leak"
          + "\n\tSeverity: " + getSeverity();
    else
      return "Action not specified properly";
  }
}
