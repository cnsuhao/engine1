/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.actions;

import java.io.Serializable;

import com.kitware.physiology.cdm.Actions.ActionData;
import com.kitware.physiology.cdm.Scenario.AnyActionData;

import mil.tatrc.physiology.datamodel.patient.actions.SEPatientAction;
import mil.tatrc.physiology.datamodel.properties.SEScalarTime;
import mil.tatrc.physiology.datamodel.substance.SESubstanceManager;
import mil.tatrc.physiology.datamodel.system.environment.actions.SEEnvironmentAction;
import mil.tatrc.physiology.datamodel.system.equipment.anesthesia.actions.SEAnesthesiaMachineAction;
import mil.tatrc.physiology.datamodel.system.equipment.inhaler.actions.SEInhalerAction;
import mil.tatrc.physiology.utilities.Log;

public abstract class SEAction implements Serializable
{
  protected String comment;
  protected SEScalarTime scenarioTime;
  
  
  public SEAction() 
  {
    comment = null;
    scenarioTime = null;
  }
  
  public void copy(SEAction other) 
  {
    reset();
    comment = other.comment;
  }
  
  public void reset() 
  {
    comment = null;
  }
  
  public static void load(ActionData src, SEAction dst) 
  {
    dst.reset();
    if(!src.getComment().isEmpty())
      dst.setComment(src.getComment());
  }
  protected static void unload(SEAction src, ActionData.Builder dst)
  {
    if (src.hasComment())
      dst.setComment(src.comment);
  }
  
  public boolean hasComment()
  {
    return this.comment != null && !this.comment.isEmpty();
  }  
  public String getComment()
  {
    return this.comment;
  }
  public void setComment(String comment)
  {
    this.comment = comment;
  }
  public void invalidateComment()
  {
    this.comment = null;
  }
  
  public boolean hasScenarioTime()
  {
    return this.scenarioTime == null ? false : this.scenarioTime.isValid();
  }  
  public SEScalarTime getScenarioTime()
  {
    if(this.scenarioTime == null)
      this.scenarioTime = new SEScalarTime();
    return this.scenarioTime;
  }
  
  public static SEAction ANY2CDM(AnyActionData any, SESubstanceManager subMgr)
  {
    switch(any.getActionCase())
    {
      case ADVANCETIME:
      {
        SEAdvanceTime dst = new SEAdvanceTime();
        SEAdvanceTime.load(any.getAdvanceTime(), dst);
        return dst;
      }
      case PATIENTACTION:
        return SEPatientAction.ANY2CDM(any.getPatientAction(), subMgr);
      case ENVIRONMENTACTION:
        return SEEnvironmentAction.ANY2CDM(any.getEnvironmentAction(), subMgr);
      case ANESTHESIAMACHINEACTION:
        return SEAnesthesiaMachineAction.ANY2CDM(any.getAnesthesiaMachineAction(), subMgr);
      case INHALERACTION:
        return SEInhalerAction.ANY2CDM(any.getInhalerAction(), subMgr);      
      case SERIALIZE:
      {
        SESerializeState dst = new SESerializeState();
        SESerializeState.load(any.getSerialize(), dst);
        return dst;
      }
      case ACTION_NOT_SET:
        Log.warn("AnyActionData is empty...was that intended?");
      default:
        Log.error("Unsupported AnyActionData Type "+any.getActionCase());
    }
    return null;
  }
  
  public static AnyActionData CDM2ANY(SEAction a)
  {
    AnyActionData.Builder dst = AnyActionData.newBuilder();
    if(a instanceof SEAdvanceTime)
    {
      dst.setAdvanceTime(SEAdvanceTime.unload((SEAdvanceTime)a));
      return dst.build();
    }
    if(a instanceof SEPatientAction)
    {
      dst.setPatientAction(SEPatientAction.CDM2ANY((SEPatientAction)a));
      return dst.build();
    }
    if(a instanceof SEEnvironmentAction)
    {
      dst.setEnvironmentAction(SEEnvironmentAction.CDM2ANY((SEEnvironmentAction)a));
      return dst.build();
    }
    if(a instanceof SEAnesthesiaMachineAction)
    {
      dst.setAnesthesiaMachineAction(SEAnesthesiaMachineAction.CDM2ANY((SEAnesthesiaMachineAction)a));
      return dst.build();
    }
    if(a instanceof SEInhalerAction)
    {
      dst.setInhalerAction(SEInhalerAction.CDM2ANY((SEInhalerAction)a));
      return dst.build();
    }
    if(a instanceof SESerializeState)
    {
      dst.setSerialize(SESerializeState.unload((SESerializeState)a));
      return dst.build();
    }
    Log.error("Unsupported AnyActionData Type "+a.toString());
    return dst.build();
  }
  
  public abstract boolean isValid();
  public abstract String toString();
}
