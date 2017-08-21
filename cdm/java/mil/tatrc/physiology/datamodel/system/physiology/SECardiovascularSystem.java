/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
package mil.tatrc.physiology.datamodel.system.physiology;

import com.kitware.physiology.cdm.Physiology.CardiovascularSystemData;
import com.kitware.physiology.cdm.Physiology.eHeartRhythm;

import mil.tatrc.physiology.datamodel.properties.*;
import mil.tatrc.physiology.datamodel.system.SESystem;

public class SECardiovascularSystem extends SEPhysiologySystem implements SESystem
{
  protected SEScalarPressure                  arterialPressure;
  protected SEScalarVolume                    bloodVolume;
  protected SEScalarVolumePerTimeArea         cardiacIndex;
  protected SEScalarVolumePerTime             cardiacOutput;
  protected SEScalarPressure                  centralVenousPressure;
  protected SEScalarVolumePerTime             cerebralBloodFlow;
  protected SEScalarPressure                  cerebralPerfusionPressure;
  protected SEScalarPressure                  diastolicArterialPressure;
  protected SEScalar0To1                      heartEjectionFraction;
  protected SEScalarFrequency                 heartRate;
  protected eHeartRhythm                      heartRhythm;
  protected SEScalarVolume                    heartStrokeVolume;
  protected SEScalarPressure                  intracranialPressure;
  protected SEScalarPressure                  meanArterialPressure;
  protected SEScalarPressure                  meanArterialCarbonDioxidePartialPressure;
  protected SEScalarPressure                  meanArterialCarbonDioxidePartialPressureDelta;
  protected SEScalarPressure                  meanCentralVenousPressure;
  protected SEScalarVolumePerTime             meanSkinFlow;
  protected SEScalarPressure                  pulmonaryArterialPressure;
  protected SEScalarPressure                  pulmonaryCapillariesWedgePressure;
  protected SEScalarPressure                  pulmonaryDiastolicArterialPressure;
  protected SEScalarPressure                  pulmonaryMeanArterialPressure;
  protected SEScalarVolumePerTime             pulmonaryMeanCapillaryFlow;
  protected SEScalarVolumePerTime             pulmonaryMeanShuntFlow;
  protected SEScalarPressure                  pulmonarySystolicArterialPressure;
  protected SEScalarFlowResistance            pulmonaryVascularResistance;
  protected SEScalarPressureTimePerVolumeArea pulmonaryVascularResistanceIndex;
  protected SEScalarPressure                  pulsePressure;
  protected SEScalarFlowResistance            systemicVascularResistance;
  protected SEScalarPressure                  systolicArterialPressure;

  public SECardiovascularSystem()
  {
    arterialPressure = null;
    meanArterialPressure = null;
    bloodVolume = null;
    cardiacIndex = null;
    cardiacOutput = null;
    centralVenousPressure = null;
    cerebralBloodFlow = null;
    cerebralPerfusionPressure = null;
    meanCentralVenousPressure = null;
    diastolicArterialPressure = null;  
    heartEjectionFraction = null;
    heartRate = null;
    heartRhythm = null;
    heartStrokeVolume = null;
    intracranialPressure = null;
    pulmonaryArterialPressure = null;
    pulmonaryCapillariesWedgePressure = null;
    pulmonaryDiastolicArterialPressure = null;
    pulmonaryMeanArterialPressure = null;
    pulmonaryMeanCapillaryFlow = null;
    pulmonaryMeanShuntFlow = null;
    pulmonarySystolicArterialPressure = null;
    pulmonaryVascularResistance = null;
    pulmonaryVascularResistanceIndex = null;
    pulsePressure = null;
    systemicVascularResistance = null;
    systolicArterialPressure = null;
  }

  public void reset()
  {
    if (arterialPressure != null)
      arterialPressure.invalidate();
    if (meanArterialPressure != null)
      meanArterialPressure.invalidate();
    if (bloodVolume != null)
      bloodVolume.invalidate();
    if (cardiacIndex != null)
      cardiacIndex.invalidate();
    if (cardiacOutput != null)
      cardiacOutput.invalidate();
    if (centralVenousPressure != null)
      centralVenousPressure.invalidate();
    if (cerebralBloodFlow != null)
      cerebralBloodFlow.invalidate();
    if (cerebralPerfusionPressure != null)
      cerebralPerfusionPressure.invalidate();
    if (meanCentralVenousPressure != null)
      meanCentralVenousPressure.invalidate();
    if (diastolicArterialPressure != null)
      diastolicArterialPressure.invalidate();  
    if (heartEjectionFraction != null)
      heartEjectionFraction.invalidate();
    if (intracranialPressure != null)
      intracranialPressure.invalidate();
    this.heartRhythm = null;
    if (heartStrokeVolume != null)
      heartStrokeVolume.invalidate();
    if (pulmonaryArterialPressure != null)
      pulmonaryArterialPressure.invalidate();
    if (pulmonaryCapillariesWedgePressure != null)
      pulmonaryCapillariesWedgePressure.invalidate();
    if (pulmonaryDiastolicArterialPressure != null)
      pulmonaryDiastolicArterialPressure.invalidate();
    if (pulmonaryMeanArterialPressure != null)
      pulmonaryMeanArterialPressure.invalidate();    
    if (pulmonaryMeanCapillaryFlow != null)
      pulmonaryMeanCapillaryFlow.invalidate();
    if (pulmonaryMeanShuntFlow != null)
      pulmonaryMeanShuntFlow.invalidate();
    if (pulmonarySystolicArterialPressure != null)
      pulmonarySystolicArterialPressure.invalidate();    
    if (pulmonaryVascularResistance != null)
      pulmonaryVascularResistance.invalidate();    
    if (pulmonaryVascularResistanceIndex != null)
      pulmonaryVascularResistanceIndex.invalidate();    
    if (pulsePressure != null)
      pulsePressure.invalidate();
    if (systemicVascularResistance != null)
      systemicVascularResistance.invalidate();    
    if (systolicArterialPressure != null)
      systolicArterialPressure.invalidate();
    if (meanArterialCarbonDioxidePartialPressure != null)
      meanArterialCarbonDioxidePartialPressure.invalidate();
    if (meanArterialCarbonDioxidePartialPressureDelta != null)
      meanArterialCarbonDioxidePartialPressureDelta.invalidate();
    if (meanSkinFlow != null)
      meanSkinFlow.invalidate();
  }

  public static void load(CardiovascularSystemData src, SECardiovascularSystem dst)
  {
    if (src.hasArterialPressure())
      SEScalarPressure.load(src.getArterialPressure(),dst.getArterialPressure());
    if (src.hasMeanArterialPressure())
      SEScalarPressure.load(src.getMeanArterialPressure(),dst.getMeanArterialPressure());
    if (src.hasBloodVolume())
      SEScalarVolume.load(src.getBloodVolume(),dst.getBloodVolume());
    if (src.hasCardiacIndex())
      SEScalarVolumePerTimeArea.load(src.getCardiacIndex(),dst.getCardiacIndex());
    if (src.hasCardiacOutput())
      SEScalarVolumePerTime.load(src.getCardiacOutput(),dst.getCardiacOutput());
    if (src.hasCentralVenousPressure())
      SEScalarPressure.load(src.getCentralVenousPressure(),dst.getCentralVenousPressure());
    if (src.hasCerebralBloodFlow())
      SEScalarVolumePerTime.load(src.getCerebralBloodFlow(),dst.getCerebralBloodFlow());
    if (src.hasCerebralPerfusionPressure())
      SEScalarPressure.load(src.getCerebralPerfusionPressure(),dst.getCerebralPerfusionPressure());
    if (src.hasMeanCentralVenousPressure())
      SEScalarPressure.load(src.getMeanCentralVenousPressure(),dst.getMeanCentralVenousPressure());
    if (src.hasDiastolicArterialPressure())
      SEScalarPressure.load(src.getDiastolicArterialPressure(),dst.getDiastolicArterialPressure());  
    if (src.hasHeartEjectionFraction())
      SEScalar0To1.load(src.getHeartEjectionFraction(),dst.getHeartEjectionFraction());
    if (src.hasHeartRate())
      SEScalarFrequency.load(src.getHeartRate(),dst.getHeartRate());    
    if(src.getHeartRhythm()!=eHeartRhythm.UNRECOGNIZED)
      dst.setHeartRhythm(src.getHeartRhythm());
    if (src.hasHeartStrokeVolume())
      SEScalarVolume.load(src.getHeartStrokeVolume(),dst.getHeartStrokeVolume());
    if (src.hasIntracranialPressure())
      SEScalarPressure.load(src.getIntracranialPressure(),dst.getIntracranialPressure());
    if (src.hasPulmonaryArterialPressure())
      SEScalarPressure.load(src.getPulmonaryArterialPressure(),dst.getPulmonaryArterialPressure());
    if (src.hasPulmonaryCapillariesWedgePressure())
      SEScalarPressure.load(src.getPulmonaryCapillariesWedgePressure(),dst.getPulmonaryCapillariesWedgePressure());
    if (src.hasPulmonaryDiastolicArterialPressure())
      SEScalarPressure.load(src.getPulmonaryDiastolicArterialPressure(),dst.getPulmonaryDiastolicArterialPressure());
    if (src.hasPulmonaryMeanArterialPressure())
      SEScalarPressure.load(src.getPulmonaryMeanArterialPressure(),dst.getPulmonaryMeanArterialPressure());
    if (src.hasPulmonaryMeanCapillaryFlow())
      SEScalarVolumePerTime.load(src.getPulmonaryMeanCapillaryFlow(),dst.getPulmonaryMeanCapillaryFlow());
    if (src.hasPulmonaryMeanShuntFlow())
      SEScalarVolumePerTime.load(src.getPulmonaryMeanShuntFlow(),dst.getPulmonaryMeanShuntFlow());
    if (src.hasPulmonarySystolicArterialPressure())
      SEScalarPressure.load(src.getPulmonarySystolicArterialPressure(),dst.getPulmonarySystolicArterialPressure());
    if (src.hasPulmonaryVascularResistance())
      SEScalarFlowResistance.load(src.getPulmonaryVascularResistance(),dst.getPulmonaryVascularResistance());
    if (src.hasPulmonaryVascularResistanceIndex())
      SEScalarPressureTimePerVolumeArea.load(src.getPulmonaryVascularResistanceIndex(),dst.getPulmonaryVascularResistanceIndex());
    if (src.hasPulsePressure())
      SEScalarPressure.load(src.getPulsePressure(),dst.getPulsePressure());
    if (src.hasSystemicVascularResistance())
      SEScalarFlowResistance.load(src.getSystemicVascularResistance(),dst.getSystemicVascularResistance());
    if (src.hasSystolicArterialPressure())
      SEScalarPressure.load(src.getSystolicArterialPressure(),dst.getSystolicArterialPressure());
    if (src.hasMeanArterialCarbonDioxidePartialPressure())
      SEScalarPressure.load(src.getMeanArterialCarbonDioxidePartialPressure(),dst.getMeanArterialCarbonDioxidePartialPressure());
    if (src.hasMeanArterialCarbonDioxidePartialPressureDelta())
      SEScalarPressure.load(src.getMeanArterialCarbonDioxidePartialPressureDelta(),dst.getMeanArterialCarbonDioxidePartialPressureDelta());
    if (src.hasMeanSkinFlow())
      SEScalarVolumePerTime.load(src.getMeanSkinFlow(),dst.getMeanSkinFlow());
  }

  public static CardiovascularSystemData unload(SECardiovascularSystem src)
  {
    CardiovascularSystemData.Builder dst = CardiovascularSystemData.newBuilder();
    unload(src,dst);
    return dst.build();
  }

  protected static void unload(SECardiovascularSystem src, CardiovascularSystemData.Builder dst)
  {
    if (src.hasArterialPressure())
      dst.setArterialPressure(SEScalarPressure.unload(src.getArterialPressure())); 
    if (src.hasMeanArterialPressure())
      dst.setMeanArterialPressure(SEScalarPressure.unload(src.getMeanArterialPressure())); 
    if (src.hasBloodVolume())
      dst.setBloodVolume(SEScalarVolume.unload(src.getBloodVolume())); 
    if (src.hasCardiacIndex())
      dst.setCardiacIndex(SEScalarVolumePerTimeArea.unload(src.getCardiacIndex())); 
    if (src.hasCardiacOutput())
      dst.setCardiacOutput(SEScalarVolumePerTime.unload(src.getCardiacOutput())); 
    if (src.hasCentralVenousPressure())
      dst.setCentralVenousPressure(SEScalarPressure.unload(src.getCentralVenousPressure())); 
    if (src.hasCerebralBloodFlow())
      dst.setCerebralBloodFlow(SEScalarVolumePerTime.unload(src.getCerebralBloodFlow())); 
    if (src.hasCerebralPerfusionPressure())
      dst.setCerebralPerfusionPressure(SEScalarPressure.unload(src.getCerebralPerfusionPressure())); 
    if (src.hasMeanCentralVenousPressure())
      dst.setMeanCentralVenousPressure(SEScalarPressure.unload(src.getMeanCentralVenousPressure())); 
    if (src.hasDiastolicArterialPressure())
      dst.setDiastolicArterialPressure(SEScalarPressure.unload(src.getDiastolicArterialPressure())); 
    if (src.hasHeartEjectionFraction())
      dst.setHeartEjectionFraction(SEScalar0To1.unload(src.getHeartEjectionFraction())); 
    if (src.hasHeartRate())
      dst.setHeartRate(SEScalarFrequency.unload(src.getHeartRate())); 
    if(src.hasHeartRhythm())
      dst.setHeartRhythm(src.heartRhythm);
    if (src.hasHeartStrokeVolume())
      dst.setHeartStrokeVolume(SEScalarVolume.unload(src.getHeartStrokeVolume()));
    if (src.hasIntracranialPressure())
      dst.setIntracranialPressure(SEScalarPressure.unload(src.getIntracranialPressure()));
    if (src.hasPulmonaryArterialPressure())
      dst.setPulmonaryArterialPressure(SEScalarPressure.unload(src.getPulmonaryArterialPressure()));
    if (src.hasPulmonaryCapillariesWedgePressure())
      dst.setPulmonaryCapillariesWedgePressure(SEScalarPressure.unload(src.getPulmonaryCapillariesWedgePressure())); 
    if (src.hasPulmonaryDiastolicArterialPressure())
      dst.setPulmonaryDiastolicArterialPressure(SEScalarPressure.unload(src.getPulmonaryDiastolicArterialPressure())); 
    if (src.hasPulmonaryMeanArterialPressure())
      dst.setPulmonaryMeanArterialPressure(SEScalarPressure.unload(src.getPulmonaryMeanArterialPressure())); 
    if (src.hasPulmonaryMeanCapillaryFlow())
      dst.setPulmonaryMeanCapillaryFlow(SEScalarVolumePerTime.unload(src.getPulmonaryMeanCapillaryFlow())); 
    if (src.hasPulmonaryMeanShuntFlow())
      dst.setPulmonaryMeanShuntFlow(SEScalarVolumePerTime.unload(src.getPulmonaryMeanShuntFlow())); 
    if (src.hasPulmonarySystolicArterialPressure())
      dst.setPulmonarySystolicArterialPressure(SEScalarPressure.unload(src.getPulmonarySystolicArterialPressure())); 
    if (src.hasPulmonaryVascularResistance())
      dst.setPulmonaryVascularResistance(SEScalarFlowResistance.unload(src.getPulmonaryVascularResistance())); 
    if (src.hasPulmonaryVascularResistanceIndex())
      dst.setPulmonaryVascularResistanceIndex(SEScalarPressureTimePerVolumeArea.unload(src.getPulmonaryVascularResistanceIndex())); 
    if (src.hasPulsePressure())
      dst.setPulsePressure(SEScalarPressure.unload(src.getPulsePressure()));
    if (src.hasSystemicVascularResistance())
      dst.setSystemicVascularResistance(SEScalarFlowResistance.unload(src.getSystemicVascularResistance()));    
    if (src.hasSystolicArterialPressure())
      dst.setSystolicArterialPressure(SEScalarPressure.unload(src.getSystolicArterialPressure()));
    if (src.hasMeanArterialCarbonDioxidePartialPressure())
      dst.setMeanArterialCarbonDioxidePartialPressure(SEScalarPressure.unload(src.getMeanArterialCarbonDioxidePartialPressure()));
    if (src.hasMeanArterialCarbonDioxidePartialPressureDelta())
      dst.setMeanArterialCarbonDioxidePartialPressureDelta(SEScalarPressure.unload(src.getMeanArterialCarbonDioxidePartialPressureDelta()));
    if (src.hasMeanSkinFlow())
      dst.setMeanSkinFlow(SEScalarVolumePerTime.unload(src.getMeanSkinFlow()));
  }

  /*
   * Arterial Pressure
   */
  public boolean hasArterialPressure()
  {
    return arterialPressure == null ? false : arterialPressure.isValid();
  }
  public SEScalarPressure getArterialPressure()
  {
    if (arterialPressure == null)
      arterialPressure = new SEScalarPressure();
    return arterialPressure;
  }

  /*
   * Mean Arterial Pressure
   */
  public boolean hasMeanArterialPressure()
  {
    return meanArterialPressure == null ? false : meanArterialPressure.isValid();
  }
  public SEScalarPressure getMeanArterialPressure()
  {
    if (meanArterialPressure == null)
      meanArterialPressure = new SEScalarPressure();
    return meanArterialPressure;
  }

  /*
   * Blood Volume
   */
  public boolean hasBloodVolume()
  {
    return bloodVolume == null ? false : bloodVolume.isValid();
  }
  public SEScalarVolume getBloodVolume()
  {
    if (bloodVolume == null)
      bloodVolume = new SEScalarVolume();
    return bloodVolume;
  }
  
  public boolean hasCardiacIndex()
  {
    return cardiacIndex == null ? false : cardiacIndex.isValid();
  }
  public SEScalarVolumePerTimeArea getCardiacIndex()
  {
    if (cardiacIndex == null)
      cardiacIndex = new SEScalarVolumePerTimeArea();
    return cardiacIndex;
  }

  /*
   * Cardiac Output
   */
  public boolean hasCardiacOutput()
  {
    return cardiacOutput == null ? false : cardiacOutput.isValid();
  }
  public SEScalarVolumePerTime getCardiacOutput()
  {
    if (cardiacOutput == null)
      cardiacOutput = new SEScalarVolumePerTime();
    return cardiacOutput;
  }

  /*
   * Central Venous Pressure
   */
  public boolean hasCentralVenousPressure()
  {
    return centralVenousPressure == null ? false : centralVenousPressure.isValid();
  }
  public SEScalarPressure getCentralVenousPressure()
  {
    if (centralVenousPressure == null)
      centralVenousPressure = new SEScalarPressure();
    return centralVenousPressure;
  }

  public boolean hasCerebralBloodFlow()
  {
    return cerebralBloodFlow == null ? false : cerebralBloodFlow.isValid();
  }
  public SEScalarVolumePerTime getCerebralBloodFlow()
  {
    if (cerebralBloodFlow == null)
      cerebralBloodFlow = new SEScalarVolumePerTime();
    return cerebralBloodFlow;
  }

  public boolean hasCerebralPerfusionPressure()
  {
    return cerebralPerfusionPressure == null ? false : cerebralPerfusionPressure.isValid();
  }
  public SEScalarPressure getCerebralPerfusionPressure()
  {
    if (cerebralPerfusionPressure == null)
      cerebralPerfusionPressure = new SEScalarPressure();
    return cerebralPerfusionPressure;
  }

  /*
   * Mean Central Venous Pressure
   */
  public boolean hasMeanCentralVenousPressure()
  {
    return meanCentralVenousPressure == null ? false : meanCentralVenousPressure.isValid();
  }
  public SEScalarPressure getMeanCentralVenousPressure()
  {
    if (meanCentralVenousPressure == null)
      meanCentralVenousPressure = new SEScalarPressure();
    return meanCentralVenousPressure;
  }

  /*
   * Diastolic Arterial Pressure
   */
  public boolean hasDiastolicArterialPressure()
  {
    return diastolicArterialPressure == null ? false : diastolicArterialPressure.isValid();
  }
  public SEScalarPressure getDiastolicArterialPressure()
  {
    if (diastolicArterialPressure == null)
      diastolicArterialPressure = new SEScalarPressure();
    return diastolicArterialPressure;
  }

  /*
   * Heart Ejection Fraction
   */
  public boolean hasHeartEjectionFraction()
  {
    return heartEjectionFraction == null ? false : heartEjectionFraction.isValid();
  }
  public SEScalar0To1 getHeartEjectionFraction()
  {
    if (heartEjectionFraction == null)
      heartEjectionFraction = new SEScalar0To1();
    return heartEjectionFraction;
  }

  /*
   * Heart Rate
   */
  public boolean hasHeartRate()
  {
    return heartRate == null ? false : heartRate.isValid();
  }
  public SEScalarFrequency getHeartRate()
  {
    if (heartRate == null)
      heartRate = new SEScalarFrequency();
    return heartRate;
  }

  /*
   * Heart Rhythm
   */
  public eHeartRhythm    getHeartRhythm() { return this.heartRhythm;}
  public void            setHeartRhythm(eHeartRhythm heartRhythm){this.heartRhythm=heartRhythm;}
  public boolean         hasHeartRhythm(){return this.heartRhythm==null?false:true;}

  /*
   * Heart Stroke Volume
   */
  public boolean hasHeartStrokeVolume()
  {
    return heartStrokeVolume == null ? false : heartStrokeVolume.isValid();
  }
  public SEScalarVolume getHeartStrokeVolume()
  {
    if (heartStrokeVolume == null)
      heartStrokeVolume = new SEScalarVolume();
    return heartStrokeVolume;
  }

  public boolean hasIntracranialPressure()
  {
    return intracranialPressure == null ? false : intracranialPressure.isValid();
  }
  public SEScalarPressure getIntracranialPressure()
  {
    if (intracranialPressure == null)
      intracranialPressure = new SEScalarPressure();
    return intracranialPressure;
  }

  /*
   * Pulmonary Arterial Pressure
   */
  public boolean hasPulmonaryArterialPressure()
  {
    return pulmonaryArterialPressure == null ? false : pulmonaryArterialPressure.isValid();
  }
  public SEScalarPressure getPulmonaryArterialPressure()
  {
    if (pulmonaryArterialPressure == null)
      pulmonaryArterialPressure = new SEScalarPressure();
    return pulmonaryArterialPressure;
  }

  /*
   * Pulmonary Capillaries Wedge Pressure
   */
  public boolean hasPulmonaryCapillariesWedgePressure()
  {
    return pulmonaryCapillariesWedgePressure == null ? false : pulmonaryCapillariesWedgePressure.isValid();
  }
  public SEScalarPressure getPulmonaryCapillariesWedgePressure()
  {
    if (pulmonaryCapillariesWedgePressure == null)
      pulmonaryCapillariesWedgePressure = new SEScalarPressure();
    return pulmonaryCapillariesWedgePressure;
  }

  /*
   * Pulmonary Diastolic Arterial Pressure
   */
  public boolean hasPulmonaryDiastolicArterialPressure()
  {
    return pulmonaryDiastolicArterialPressure == null ? false : pulmonaryDiastolicArterialPressure.isValid();
  }
  public SEScalarPressure getPulmonaryDiastolicArterialPressure()
  {
    if (pulmonaryDiastolicArterialPressure == null)
      pulmonaryDiastolicArterialPressure = new SEScalarPressure();
    return pulmonaryDiastolicArterialPressure;
  }

  /*
   * Pulmonary Mean Arterial Pressure
   */
  public boolean hasPulmonaryMeanArterialPressure()
  {
    return pulmonaryMeanArterialPressure == null ? false : pulmonaryMeanArterialPressure.isValid();
  }
  public SEScalarPressure getPulmonaryMeanArterialPressure()
  {
    if (pulmonaryMeanArterialPressure == null)
      pulmonaryMeanArterialPressure = new SEScalarPressure();
    return pulmonaryMeanArterialPressure;
  }

  /*
   * Pulmonary Mean Capillary Flow
   */
  public boolean hasPulmonaryMeanCapillaryFlow()
  {
    return pulmonaryMeanCapillaryFlow == null ? false : pulmonaryMeanCapillaryFlow.isValid();
  }
  public SEScalarVolumePerTime getPulmonaryMeanCapillaryFlow()
  {
    if (pulmonaryMeanCapillaryFlow == null)
      pulmonaryMeanCapillaryFlow = new SEScalarVolumePerTime();
    return pulmonaryMeanCapillaryFlow;
  }

  /*
   * Pulmonary Mean Shunt Flow
   */
  public boolean hasPulmonaryMeanShuntFlow()
  {
    return pulmonaryMeanShuntFlow == null ? false : pulmonaryMeanShuntFlow.isValid();
  }
  public SEScalarVolumePerTime getPulmonaryMeanShuntFlow()
  {
    if (pulmonaryMeanShuntFlow == null)
      pulmonaryMeanShuntFlow = new SEScalarVolumePerTime();
    return pulmonaryMeanShuntFlow;
  }

  /*
   * Pulmonary Systolic Arterial Pressure
   */
  public boolean hasPulmonarySystolicArterialPressure()
  {
    return pulmonarySystolicArterialPressure == null ? false : pulmonarySystolicArterialPressure.isValid();
  }
  public SEScalarPressure getPulmonarySystolicArterialPressure()
  {
    if (pulmonarySystolicArterialPressure == null)
      pulmonarySystolicArterialPressure = new SEScalarPressure();
    return pulmonarySystolicArterialPressure;
  }
  
  public boolean hasPulmonaryVascularResistance()
  {
    return pulmonaryVascularResistance == null ? false : pulmonaryVascularResistance.isValid();
  }
  public SEScalarFlowResistance getPulmonaryVascularResistance()
  {
    if (pulmonaryVascularResistance == null)
      pulmonaryVascularResistance = new SEScalarFlowResistance();
    return pulmonaryVascularResistance;
  }
  
  public boolean hasPulmonaryVascularResistanceIndex()
  {
    return pulmonaryVascularResistanceIndex == null ? false : pulmonaryVascularResistanceIndex.isValid();
  }
  public SEScalarPressureTimePerVolumeArea getPulmonaryVascularResistanceIndex()
  {
    if (pulmonaryVascularResistanceIndex == null)
      pulmonaryVascularResistanceIndex = new SEScalarPressureTimePerVolumeArea();
    return pulmonaryVascularResistanceIndex;
  }

  /*
   * Pulse Pressure
   */
  public boolean hasPulsePressure()
  {
    return pulsePressure == null ? false : pulsePressure.isValid();
  }
  public SEScalarPressure getPulsePressure()
  {
    if (pulsePressure == null)
      pulsePressure = new SEScalarPressure();
    return pulsePressure;
  }

  /*
   * Systemic Vascular Resistance
   */
  public boolean hasSystemicVascularResistance()
  {
    return systemicVascularResistance == null ? false : systemicVascularResistance.isValid();
  }
  public SEScalarFlowResistance getSystemicVascularResistance()
  {
    if (systemicVascularResistance == null)
      systemicVascularResistance = new SEScalarFlowResistance();
    return systemicVascularResistance;
  }

  /*
   * Systolic Arterial Pressure
   */
  public boolean hasSystolicArterialPressure()
  {
    return systolicArterialPressure == null ? false : systolicArterialPressure.isValid();
  }
  public SEScalarPressure getSystolicArterialPressure()
  {
    if (systolicArterialPressure == null)
      systolicArterialPressure = new SEScalarPressure();
    return systolicArterialPressure;
  }

  /*
   * Mean Arterial Carbon Dioxide Partial Pressure
   */
  public boolean hasMeanArterialCarbonDioxidePartialPressure()
  {
    return meanArterialCarbonDioxidePartialPressure == null ? false : meanArterialCarbonDioxidePartialPressure.isValid();
  }
  public SEScalarPressure getMeanArterialCarbonDioxidePartialPressure()
  {
    if (meanArterialCarbonDioxidePartialPressure == null)
      meanArterialCarbonDioxidePartialPressure = new SEScalarPressure();
    return meanArterialCarbonDioxidePartialPressure;
  }

  /*
   * Mean Arterial Carbon Dioxide Partial Pressure Delta
   */
  public boolean hasMeanArterialCarbonDioxidePartialPressureDelta()
  {
    return meanArterialCarbonDioxidePartialPressureDelta == null ? false : meanArterialCarbonDioxidePartialPressureDelta.isValid();
  }
  public SEScalarPressure getMeanArterialCarbonDioxidePartialPressureDelta()
  {
    if (meanArterialCarbonDioxidePartialPressureDelta == null)
      meanArterialCarbonDioxidePartialPressureDelta = new SEScalarPressure();
    return meanArterialCarbonDioxidePartialPressureDelta;
  }

  /*
   * Mean Skin Flow
   */
  public boolean hasMeanSkinFlow()
  {
    return meanSkinFlow == null ? false : meanSkinFlow.isValid();
  }
  public SEScalarVolumePerTime getMeanSkinFlow()
  {
    if (meanSkinFlow == null)
      meanSkinFlow = new SEScalarVolumePerTime();
    return meanSkinFlow;
  }
}
