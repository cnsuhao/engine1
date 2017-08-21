/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
package mil.tatrc.physiology.datamodel.system.physiology;

import com.kitware.physiology.cdm.Physiology.TissueSystemData;

import mil.tatrc.physiology.datamodel.properties.*;
import mil.tatrc.physiology.datamodel.system.SESystem;

public class SETissueSystem extends SEPhysiologySystem implements SESystem
{
  protected SEScalarVolumePerTime carbonDioxideProductionRate;
  protected SEScalarVolume        extracellularFluidVolume;
  protected SEScalarVolume        extravascularFluidVolume;
  protected SEScalarVolume        intracellularFluidVolume;
  protected SEScalar              intracellularFluidPH;  
  protected SEScalarVolumePerTime oxygenConsumptionRate;
  protected SEScalar              respiratoryExchangeRatio;

  public SETissueSystem()
  {
    carbonDioxideProductionRate = null;
    extracellularFluidVolume = null;
    extravascularFluidVolume = null;
    intracellularFluidVolume = null;
    intracellularFluidPH = null;
    oxygenConsumptionRate = null;
    respiratoryExchangeRatio = null;
  }

  public void reset()
  {    
    if (carbonDioxideProductionRate != null)
      carbonDioxideProductionRate.invalidate();
    if (extracellularFluidVolume != null)
      extracellularFluidVolume.invalidate();
    if (extravascularFluidVolume != null)
      extravascularFluidVolume.invalidate();
    if (intracellularFluidVolume != null)
      intracellularFluidVolume.invalidate(); 
    if (intracellularFluidPH != null)
        intracellularFluidPH.invalidate();
    if (oxygenConsumptionRate != null)
      oxygenConsumptionRate.invalidate();
    if (respiratoryExchangeRatio != null)
      respiratoryExchangeRatio.invalidate();
  }

  public static void load(TissueSystemData src, SETissueSystem dst)
  {    
    if (src.hasCarbonDioxideProductionRate())
      SEScalarVolumePerTime.load(src.getCarbonDioxideProductionRate(),dst.getCarbonDioxideProductionRate());   
    if (src.hasExtracellularFluidVolume())
      SEScalarVolume.load(src.getExtracellularFluidVolume(),dst.getExtracellularFluidVolume());
    if (src.hasExtravascularFluidVolume())
      SEScalarVolume.load(src.getExtravascularFluidVolume(),dst.getExtravascularFluidVolume());
    if (src.hasIntracellularFluidVolume())
      SEScalarVolume.load(src.getIntracellularFluidVolume(),dst.getIntracellularFluidVolume());
    if (src.hasIntracellularFluidPH())
      SEScalar.load(src.getIntracellularFluidPH(),dst.getIntracellularFluidPH());
    if (src.hasOxygenConsumptionRate())
      SEScalarVolumePerTime.load(src.getOxygenConsumptionRate(),dst.getOxygenConsumptionRate());
    if (src.hasRespiratoryExchangeRatio())
      SEScalar.load(src.getRespiratoryExchangeRatio(),dst.getRespiratoryExchangeRatio());
  }

  public static TissueSystemData unload(SETissueSystem src)
  {
    TissueSystemData.Builder dst = TissueSystemData.newBuilder();
    unload(src,dst);
    return dst.build();
  }

  protected static void unload(SETissueSystem src, TissueSystemData.Builder dst)
  {    
    if (src.hasCarbonDioxideProductionRate())
      dst.setCarbonDioxideProductionRate(SEScalarVolumePerTime.unload(src.getCarbonDioxideProductionRate()));    
    if (src.extracellularFluidVolume != null)
      dst.setExtracellularFluidVolume(SEScalarVolume.unload(src.getExtracellularFluidVolume()));
    if (src.extravascularFluidVolume != null)
      dst.setExtravascularFluidVolume(SEScalarVolume.unload(src.getExtravascularFluidVolume()));
    if (src.intracellularFluidVolume != null)
      dst.setIntracellularFluidVolume(SEScalarVolume.unload(src.getIntracellularFluidVolume()));
    if (src.intracellularFluidPH != null)
      dst.setIntracellularFluidPH(SEScalar.unload(src.getIntracellularFluidPH()));
    if (src.hasOxygenConsumptionRate())
      dst.setOxygenConsumptionRate(SEScalarVolumePerTime.unload(src.getOxygenConsumptionRate()));
    if (src.hasRespiratoryExchangeRatio())
      dst.setRespiratoryExchangeRatio(SEScalar.unload(src.getRespiratoryExchangeRatio()));    
  }

  public boolean hasCarbonDioxideProductionRate()
  {
    return carbonDioxideProductionRate == null ? false : carbonDioxideProductionRate.isValid();
  }
  public SEScalarVolumePerTime getCarbonDioxideProductionRate()
  {
    if (carbonDioxideProductionRate == null)
      carbonDioxideProductionRate = new SEScalarVolumePerTime();
    return carbonDioxideProductionRate;
  }
  
  public boolean hasExtracellularFluidVolume()
  {
    return extracellularFluidVolume == null ? false : extracellularFluidVolume.isValid();
  }
  public SEScalarVolume getExtracellularFluidVolume()
  {
    if (extracellularFluidVolume == null)
      extracellularFluidVolume = new SEScalarVolume();
    return extracellularFluidVolume;
  }

  public boolean hasExtravascularFluidVolume()
  {
    return extravascularFluidVolume == null ? false : extravascularFluidVolume.isValid();
  }
  public SEScalarVolume getExtravascularFluidVolume()
  {
    if (extravascularFluidVolume == null)
      extravascularFluidVolume = new SEScalarVolume();
    return extravascularFluidVolume;
  }

  public boolean hasIntracellularFluidVolume()
  {
    return intracellularFluidVolume == null ? false : intracellularFluidVolume.isValid();
  }
  public SEScalarVolume getIntracellularFluidVolume()
  {
    if (intracellularFluidVolume == null)
      intracellularFluidVolume = new SEScalarVolume();
    return intracellularFluidVolume;
  }

  public boolean hasIntracellularFluidPH()
  {
    return intracellularFluidPH == null ? false : intracellularFluidPH.isValid();
  }
  public SEScalar getIntracellularFluidPH()
  {
    if (intracellularFluidPH == null)
      intracellularFluidPH = new SEScalar();
    return intracellularFluidPH;
  }

  public boolean hasOxygenConsumptionRate()
  {
    return oxygenConsumptionRate == null ? false : oxygenConsumptionRate.isValid();
  }
  public SEScalarVolumePerTime getOxygenConsumptionRate()
  {
    if (oxygenConsumptionRate == null)
      oxygenConsumptionRate = new SEScalarVolumePerTime();
    return oxygenConsumptionRate;
  }
  
  public boolean hasRespiratoryExchangeRatio()
  {
    return respiratoryExchangeRatio == null ? false : respiratoryExchangeRatio.isValid();
  }
  public SEScalar getRespiratoryExchangeRatio()
  {
    if (respiratoryExchangeRatio == null)
      respiratoryExchangeRatio = new SEScalar();
    return respiratoryExchangeRatio;
  }
}
