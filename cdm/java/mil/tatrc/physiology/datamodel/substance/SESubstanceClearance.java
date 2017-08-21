/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.substance;
import com.kitware.physiology.cdm.Properties.eCharge;
import com.kitware.physiology.cdm.Substance.SubstanceData;
import com.kitware.physiology.cdm.Substance.SubstanceData.RenalClearanceData.DynamicsCase;

import mil.tatrc.physiology.datamodel.properties.*;
import mil.tatrc.physiology.utilities.Log;

public class SESubstanceClearance
{
  protected SEScalar0To1                 fractionExcretedInFeces;
  protected SEScalar0To1                 fractionExcretedInUrine;
  protected SEScalar0To1                 fractionMetabolizedInGut;
  protected SEScalar0To1                 fractionUnboundInPlasma;
  protected SEScalarVolumePerTimeMass    intrinsicClearance;
  protected SEScalarVolumePerTimeMass    renalClearance;
  protected eCharge                      chargeInBlood;
  protected SEScalar                     renalReabsorptionRatio;
  protected SEScalarMassPerTime          renalTransportMaximum;
  protected SEScalarMassPerTime          renalFiltrationRate;
  protected SEScalarMassPerTime          renalReabsorptionRate;
  protected SEScalarMassPerTime          renalExcretionRate;
  protected SEScalar                     glomerularFilterability;
  protected SEScalarVolumePerTimeMass    systemicClearance;
  
  public SESubstanceClearance()
  {
    
  }
  
  public void reset()
  {
    if(this.fractionExcretedInFeces!=null)
      this.fractionExcretedInFeces.invalidate();
    if(this.fractionExcretedInUrine!=null)
      this.fractionExcretedInUrine.invalidate();
    if(this.fractionMetabolizedInGut!=null)
      this.fractionMetabolizedInGut.invalidate();
    if(this.fractionUnboundInPlasma!=null)
      this.fractionUnboundInPlasma.invalidate();
    if(this.intrinsicClearance!=null)
      this.intrinsicClearance.invalidate();
    if(this.renalClearance!=null)
      this.renalClearance.invalidate();
    this.chargeInBlood = null;
    if(this.renalReabsorptionRatio!=null)
      this.renalReabsorptionRatio.invalidate();
    if(this.renalTransportMaximum!=null)
      this.renalTransportMaximum.invalidate();
    if(this.renalFiltrationRate!=null)
      this.renalFiltrationRate.invalidate();
    if(this.renalReabsorptionRate!=null)
      this.renalReabsorptionRate.invalidate();
    if(this.renalExcretionRate!=null)
      this.renalExcretionRate.invalidate();
    if(this.glomerularFilterability!=null)
      this.glomerularFilterability.invalidate();
    if(this.systemicClearance!=null)
      this.systemicClearance.invalidate();
  }
  
  public boolean isValid()
  {
   return (hasSystemic() || hasRenalClearance() || hasRenalRegulation());    
  }
  
  public boolean hasSystemic()
  {
    if(  !hasFractionExcretedInFeces() ||
         !hasFractionUnboundInPlasma() ||
         !hasIntrinsicClearance() ||
         !hasRenalClearance() ||
         !hasSystemicClearance())
        return false;
    return true;
  }  
  public boolean hasRenalRegulation()
  {
    if(  !hasChargeInBlood() ||
         !hasFractionUnboundInPlasma() ||
         !hasRenalReabsorptionRatio() ||
         !hasRenalTransportMaximum())
        return false;
    return true;
  }
  
  public static void load(SubstanceData.ClearanceData src, SESubstanceClearance dst)
  {
    dst.reset();
    
    double sys_rc = Double.NaN;
    double fuip = Double.NaN;
    
    if(src.hasSystemicClearance())
    {
      SubstanceData.SystemicClearanceData sys = src.getSystemicClearance();
      if(sys.hasFractionExcretedInFeces())
        SEScalar0To1.load(sys.getFractionExcretedInFeces(),dst.getFractionExcretedInFeces());
      if(sys.hasFractionExcretedInUrine())
        SEScalar0To1.load(sys.getFractionExcretedInUrine(),dst.getFractionExcretedInUrine());
      if(sys.hasFractionMetabolizedInGut())
        SEScalar0To1.load(sys.getFractionMetabolizedInGut(),dst.getFractionMetabolizedInGut());
      if(sys.hasFractionUnboundInPlasma())
      {
        fuip = sys.getFractionUnboundInPlasma().getScalar0To1().getValue();
        SEScalar0To1.load(sys.getFractionUnboundInPlasma(),dst.getFractionUnboundInPlasma());
      }
      if(sys.hasIntrinsicClearance())
        SEScalarVolumePerTimeMass.load(sys.getIntrinsicClearance(),dst.getIntrinsicClearance());
      if(sys.hasRenalClearance())
      {
        sys_rc = sys.getRenalClearance().getScalarVolumePerTimeMass().getValue();
        SEScalarVolumePerTimeMass.load(sys.getRenalClearance(),dst.getRenalClearance());
      }
      if(sys.hasSystemicClearance())
        SEScalarVolumePerTimeMass.load(sys.getSystemicClearance(),dst.getSystemicClearance());
    }
    if(src.hasRenalClearance())
    {
      SubstanceData.RenalClearanceData rc = src.getRenalClearance();
      if(rc.getDynamicsCase() == DynamicsCase.CLEARANCE)
      {
        if(!Double.isNaN(sys_rc) && rc.getClearance().getScalarVolumePerTimeMass().getValue()!=sys_rc)
          Log.error("Different RenalClearance values between Systemic and RenalDynamic, using RenalDynamic");
        SEScalarVolumePerTimeMass.load(rc.getClearance(),dst.getRenalClearance());
      }
      else if(rc.getDynamicsCase() == DynamicsCase.REGULATION)
      {
        SubstanceData.RenalRegulationData rr = rc.getRegulation();
        dst.chargeInBlood = rr.getChargeInBlood();
        if(rr.hasReabsorptionRatio())
          SEScalar.load(rr.getReabsorptionRatio(),dst.getRenalReabsorptionRatio());
        if(rr.hasTransportMaximum())
          SEScalarMassPerTime.load(rr.getTransportMaximum(),dst.getRenalTransportMaximum());
        if(rr.hasFractionUnboundInPlasma())
        {
          if(!Double.isNaN(fuip) && rr.getFractionUnboundInPlasma().getScalar0To1().getValue()!=fuip)
            Log.error("Different FractionUnboundInPlasma values between Systemic and RenalDynamic, using RenalDynamic");
          SEScalar0To1.load(rr.getFractionUnboundInPlasma(),dst.getFractionUnboundInPlasma());
        }
      }
      if(rc.hasFiltrationRate())
        SEScalarMassPerTime.load(rc.getFiltrationRate(),dst.getRenalFiltrationRate());
      if(rc.hasReabsorptionRate())
        SEScalarMassPerTime.load(rc.getReabsorptionRate(),dst.getRenalReabsorptionRate());
      if(rc.hasExcretionRate())
        SEScalarMassPerTime.load(rc.getExcretionRate(),dst.getRenalExcretionRate());
      if(rc.hasGlomerularFilterability())
        SEScalar.load(rc.getGlomerularFilterability(),dst.getGlomerularFilterability());           
    }
  }  
  public static SubstanceData.ClearanceData unload(SESubstanceClearance src)
  {
    if(!src.isValid())
      return null;
    SubstanceData.ClearanceData.Builder dst = SubstanceData.ClearanceData.newBuilder();
    SESubstanceClearance.unload(src,dst);
    return dst.build();
  }
  protected static void unload(SESubstanceClearance src, SubstanceData.ClearanceData.Builder dst)
  {    
    if(src.hasSystemic())
    {
      SubstanceData.SystemicClearanceData.Builder sys = dst.getSystemicClearanceBuilder();
      if(src.hasFractionExcretedInFeces())
        sys.setFractionExcretedInFeces(SEScalar0To1.unload(src.fractionExcretedInFeces));
      if(src.hasFractionExcretedInUrine())
        sys.setFractionExcretedInUrine(SEScalar0To1.unload(src.fractionExcretedInUrine));
      if(src.hasFractionMetabolizedInGut())
        sys.setFractionMetabolizedInGut(SEScalar0To1.unload(src.fractionMetabolizedInGut));
      if(src.hasFractionUnboundInPlasma())
        sys.setFractionUnboundInPlasma(SEScalar0To1.unload(src.fractionUnboundInPlasma));
      if(src.hasIntrinsicClearance())
        sys.setIntrinsicClearance(SEScalarVolumePerTimeMass.unload(src.intrinsicClearance));
      if(src.hasRenalClearance())
        sys.setRenalClearance(SEScalarVolumePerTimeMass.unload(src.renalClearance));
      if(src.hasSystemicClearance())
        sys.setSystemicClearance(SEScalarVolumePerTimeMass.unload(src.systemicClearance));
      dst.setSystemicClearance(sys.build());
    }
    
    if(src.hasRenalClearance() || src.hasRenalRegulation())
    {  
      // Renal Dynamics
      SubstanceData.RenalClearanceData.Builder rcd = dst.getRenalClearanceBuilder();
      
      if(src.hasRenalRegulation())
      {
        SubstanceData.RenalRegulationData.Builder rrd = rcd.getRegulationBuilder();
        rrd.setChargeInBlood(src.chargeInBlood);
        if(src.hasRenalReabsorptionRatio())
          rrd.setReabsorptionRatio(SEScalar.unload(src.renalReabsorptionRatio));
        if(src.hasRenalTransportMaximum())
          rrd.setTransportMaximum(SEScalarMassPerTime.unload(src.renalTransportMaximum));
        if(src.hasFractionUnboundInPlasma())
          rrd.setFractionUnboundInPlasma(SEScalar0To1.unload(src.fractionUnboundInPlasma));     
      }        
      else
      {
        rcd.setClearance(SEScalarVolumePerTimeMass.unload(src.renalClearance)); 
      }    
      if(src.hasRenalFiltrationRate())
        rcd.setFiltrationRate(SEScalarMassPerTime.unload(src.renalFiltrationRate));
      if(src.hasRenalReabsorptionRate())
        rcd.setReabsorptionRate(SEScalarMassPerTime.unload(src.renalReabsorptionRate));
      if(src.hasRenalExcretionRate())
        rcd.setExcretionRate(SEScalarMassPerTime.unload(src.renalExcretionRate));
      if(src.hasGlomerularFilterability())
        rcd.setGlomerularFilterability(SEScalar.unload(src.glomerularFilterability));
    }
        
  }
  
  public SEScalar0To1 getFractionExcretedInFeces() 
  { 
    if(this.fractionExcretedInFeces==null)
      this.fractionExcretedInFeces=new SEScalar0To1();
    return this.fractionExcretedInFeces;
  }
  public boolean hasFractionExcretedInFeces() {return this.fractionExcretedInFeces==null?false:this.fractionExcretedInFeces.isValid();}
  
  public SEScalar0To1 getFractionExcretedInUrine() 
  { 
    if(this.fractionExcretedInUrine==null)
      this.fractionExcretedInUrine=new SEScalar0To1();
    return this.fractionExcretedInUrine;
  }
  public boolean hasFractionExcretedInUrine() {return this.fractionExcretedInUrine==null?false:this.fractionExcretedInUrine.isValid();}
  
  public SEScalar0To1 getFractionMetabolizedInGut() 
  { 
    if(this.fractionMetabolizedInGut==null)
      this.fractionMetabolizedInGut=new SEScalar0To1();
    return this.fractionMetabolizedInGut;
  }
  public boolean hasFractionMetabolizedInGut() {return this.fractionMetabolizedInGut==null?false:this.fractionMetabolizedInGut.isValid();}
  
  public SEScalar0To1 getFractionUnboundInPlasma() 
  { 
    if(this.fractionUnboundInPlasma==null)
      this.fractionUnboundInPlasma=new SEScalar0To1();
    return this.fractionUnboundInPlasma;
  }
  public boolean hasFractionUnboundInPlasma() {return this.fractionUnboundInPlasma==null?false:this.fractionUnboundInPlasma.isValid();}
  
  public SEScalarVolumePerTimeMass getIntrinsicClearance() 
  { 
    if(this.intrinsicClearance==null)
      this.intrinsicClearance=new SEScalarVolumePerTimeMass();
    return this.intrinsicClearance;
  }
  public boolean hasIntrinsicClearance() {return this.intrinsicClearance==null?false:this.intrinsicClearance.isValid();}
  
  public SEScalarVolumePerTimeMass getRenalClearance() 
  { 
    if(this.renalClearance==null)
      this.renalClearance=new SEScalarVolumePerTimeMass();
    return this.renalClearance;
  }
  public boolean hasRenalClearance() {return this.renalClearance==null?false:this.renalClearance.isValid();}
  
  public eCharge    getChargeInBlood() { return this.chargeInBlood;}
  public void       setChargeInBlood(eCharge charge){this.chargeInBlood=charge;}
  public boolean    hasChargeInBlood(){return this.chargeInBlood==null?false:true;}

  public SEScalar getRenalReabsorptionRatio() 
  { 
    if(this.renalReabsorptionRatio==null)
      this.renalReabsorptionRatio=new SEScalar();
    return this.renalReabsorptionRatio;
  }
  public boolean hasRenalReabsorptionRatio() {return this.renalReabsorptionRatio==null?false:this.renalReabsorptionRatio.isValid();}
  
  public SEScalarMassPerTime getRenalTransportMaximum() 
  { 
    if(this.renalTransportMaximum==null)
      this.renalTransportMaximum=new SEScalarMassPerTime();
    return this.renalTransportMaximum;
  }
  public boolean hasRenalTransportMaximum() {return this.renalTransportMaximum==null?false:this.renalTransportMaximum.isValid();}
  
  public SEScalarMassPerTime getRenalFiltrationRate() 
  { 
    if(this.renalFiltrationRate==null)
      this.renalFiltrationRate=new SEScalarMassPerTime();
    return this.renalFiltrationRate;
  }
  public boolean hasRenalFiltrationRate() {return this.renalFiltrationRate==null?false:this.renalFiltrationRate.isValid();}
  
  public SEScalarMassPerTime getRenalReabsorptionRate() 
  { 
    if(this.renalReabsorptionRate==null)
      this.renalReabsorptionRate=new SEScalarMassPerTime();
    return this.renalReabsorptionRate;
  }
  public boolean hasRenalReabsorptionRate() {return this.renalReabsorptionRate==null?false:this.renalReabsorptionRate.isValid();}
  
  public SEScalarMassPerTime getRenalExcretionRate() 
  { 
    if(this.renalExcretionRate==null)
      this.renalExcretionRate=new SEScalarMassPerTime();
    return this.renalExcretionRate;
  }
  public boolean hasRenalExcretionRate() {return this.renalExcretionRate==null?false:this.renalExcretionRate.isValid();}
  
  public SEScalar getGlomerularFilterability() 
  { 
    if(this.glomerularFilterability==null)
      this.glomerularFilterability=new SEScalar();
    return this.glomerularFilterability;
  }
  public boolean hasGlomerularFilterability() {return this.glomerularFilterability==null?false:this.glomerularFilterability.isValid();}
 
  public SEScalarVolumePerTimeMass getSystemicClearance() 
  { 
    if(this.systemicClearance==null)
      this.systemicClearance=new SEScalarVolumePerTimeMass();
    return this.systemicClearance;
  }
  public boolean hasSystemicClearance() {return this.systemicClearance==null?false:this.systemicClearance.isValid();}
  
}
