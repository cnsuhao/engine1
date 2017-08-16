/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
package mil.tatrc.physiology.datamodel.patient.actions;

import java.util.ArrayList;
import java.util.List;

import com.kitware.physiology.cdm.PatientActions.MechanicalVentilationData;
import com.kitware.physiology.cdm.Properties.eSwitch;
import com.kitware.physiology.cdm.Substance.SubstanceData;

import mil.tatrc.physiology.utilities.Log;
import mil.tatrc.physiology.datamodel.properties.*;
import mil.tatrc.physiology.datamodel.substance.SESubstance;
import mil.tatrc.physiology.datamodel.substance.SESubstanceFractionAmount;
import mil.tatrc.physiology.datamodel.substance.SESubstanceManager;
import mil.tatrc.physiology.datamodel.system.SESystem;
import mil.tatrc.physiology.utilities.DoubleUtils;

public class SEMechanicalVentilation extends SEPatientAction
{
  protected SEScalarVolumePerTime flow;
  protected SEScalarPressure      pressure;
  protected eSwitch               state;

  protected List<SESubstanceFractionAmount>  gasFractions;

  public SEMechanicalVentilation()
  {
    clear();
  }
  
  public void clear()
  {
    flow = null;
    pressure = null;
    state = null;
    this.gasFractions=new ArrayList<SESubstanceFractionAmount>();
  }

  public void reset()
  {
    state = null;
    if (flow != null)
      flow.invalidate();
    if (pressure != null)
      pressure.invalidate();
    this.gasFractions.clear();
  }

  public void copy(SEMechanicalVentilation from)
  {
    reset();

    setState(from.getState());
    if(from.hasFlow())
      getFlow().set(from.getFlow());
    if(from.hasPressure())
      getPressure().set(from.getPressure());    
    
    if(from.gasFractions!=null)
    {
      SESubstanceFractionAmount mine;
      for(SESubstanceFractionAmount sf : from.gasFractions)
      {
        mine=this.createGasFraction(sf.getSubstance());
        if(sf.hasAmount())
          mine.getAmount().set(sf.getAmount());
      }
    }    
  }
  
  public boolean isValid()
  {
    if (!hasState())
    {
      Log.error("Mechanical Ventilation must have state.");
      return false;
    }
    if (getState() == eSwitch.Off)
      return true;
    if (!hasGasFraction())
    {
      Log.error("Mechanical Ventilation must have gas fractions.");
      return false;
    }
    else
    {
      double total = 0;
      for (SESubstanceFractionAmount sf : gasFractions)
      {
        total += sf.getAmount().getValue();
      }
      if (!DoubleUtils.equals(1.0, total))
      {
        Log.error("Mechanical Ventilation Gas fractions do not sum to 1");
        return false;
      }
    }
    if (!hasPressure() && !hasFlow())
    {
      Log.error("Mechanical Ventilation must have pressure and/or flow");
      return false;
    }
    return true;
  }

  public static void load(MechanicalVentilationData src, SEMechanicalVentilation dst, SESubstanceManager substances)
  {
    SEPatientAction.load(src.getPatientAction(), dst);   
    if(src.getState()!=eSwitch.UNRECOGNIZED)
    	dst.setState(src.getState());
    if (src.hasFlow())
      SEScalarVolumePerTime.load(src.getFlow(),dst.getFlow());
    if (src.hasPressure())
      SEScalarPressure.load(src.getPressure(),dst.getPressure());
    
    SESubstance sub;
    for(SubstanceData.FractionAmountData subData : src.getGasFractionList())
    {
      sub = substances.getSubstance(subData.getName());
      if(sub == null)
      {
        Log.error("Substance does not exist : "+subData.getName());
      }
      if(sub.getState() != SubstanceData.eState.Gas)
      {
        Log.error("Gas Fraction substance must be a gas, "+subData.getName()+" is not a gas...");
      }
      SEScalar0To1.load(subData.getAmount(),dst.createGasFraction(sub).getAmount());
    }
  }

  public static MechanicalVentilationData unload(SEMechanicalVentilation src)
  {
    MechanicalVentilationData.Builder dst = MechanicalVentilationData.newBuilder();
    unload(src,dst);
    return dst.build();
  }

  protected static void unload(SEMechanicalVentilation src, MechanicalVentilationData.Builder dst)
  {
    if (src.hasState())
      dst.setState(src.state);
    if (src.hasFlow())
      dst.setFlow(SEScalarVolumePerTime.unload(src.flow));
    if (src.hasPressure())
      dst.setPressure(SEScalarPressure.unload(src.pressure));
    
    for(SESubstanceFractionAmount gf : src.gasFractions)
      dst.addGasFraction(SESubstanceFractionAmount.unload(gf));
  }

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

  public boolean hasFlow()
  {
    return flow == null ? false : flow.isValid();
  }
  public SEScalarVolumePerTime getFlow()
  {
    if (flow == null)
      flow = new SEScalarVolumePerTime();
    return flow;
  }

  public boolean hasPressure()
  {
    return pressure == null ? false : pressure.isValid();
  }
  public SEScalarPressure getPressure()
  {
    if (pressure == null)
      pressure = new SEScalarPressure();
    return pressure;
  }
  
  public SESubstanceFractionAmount createGasFraction(SESubstance substance)
  {
    return getGasFraction(substance);
  }
  public SESubstanceFractionAmount getGasFraction(SESubstance substance)
  {
    for(SESubstanceFractionAmount sf : this.gasFractions)
    {
      if(sf.getSubstance().getName().equals(substance.getName()))
      {        
        return sf;
      }
    }    
    SESubstanceFractionAmount sf = new SESubstanceFractionAmount(substance);    
    this.gasFractions.add(sf);
    return sf;
  }
  public boolean hasGasFraction()
  {
    return !this.gasFractions.isEmpty();
  }
  public boolean hasGasFraction(SESubstance substance)
  {
    for(SESubstanceFractionAmount sf : this.gasFractions)
    {
      if(sf.getSubstance()==substance)
      {        
        return true;
      }
    }
    return false;
  }
  public List<SESubstanceFractionAmount> getGasFraction()
  {
    return this.gasFractions;
  }
  public void removeGasFraction(SESubstance substance)
  {
    for(SESubstanceFractionAmount sf : this.gasFractions)
    {
      if(sf.getSubstance()==substance)
      {
        this.gasFractions.remove(sf);
        return;
      }
    }  
  }

  public String toString()
  {
    String cnts = "Mechanical Ventilation"
        + "\n\tState: " + getState()
        + "\n\tFlow: " + (hasFlow() ? getFlow() : "Not Provided")
        + "\n\tPressure: " + (hasPressure() ? getPressure() : "Not Provided");
    for(SESubstanceFractionAmount sf : this.gasFractions)
      cnts += "\n\tSubstanceFraction: " + sf.getSubstance().getName() + " : " + sf.getAmount();
    
    return cnts;
  }
}