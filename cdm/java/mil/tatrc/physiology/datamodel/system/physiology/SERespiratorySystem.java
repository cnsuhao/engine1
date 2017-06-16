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

package mil.tatrc.physiology.datamodel.system.physiology;

import com.kitware.physiology.cdm.Physiology.RespiratorySystemData;

import mil.tatrc.physiology.datamodel.properties.*;
import mil.tatrc.physiology.datamodel.system.SESystem;

public class SERespiratorySystem extends SEPhysiologySystem implements SESystem
{
  protected SEScalarPressure        alveolarArterialGradient;
  protected SEScalarPressure        carricoIndex;
  protected SEScalar0To1            endTidalCarbonDioxideFraction;
  protected SEScalarPressure        endTidalCarbonDioxidePressure;
  protected SEScalarVolumePerTime   expiratoryFlow;
  protected SEScalar                inspiratoryExpiratoryRatio;
  protected SEScalarVolumePerTime   inspiratoryFlow;
  protected SEScalarFlowCompliance  pulmonaryCompliance;
  protected SEScalarFlowResistance  pulmonaryResistance;
  protected SEScalarPressure        respirationDriverPressure;
  protected SEScalarPressure        respirationMusclePressure;
  protected SEScalarFrequency       respirationRate;
  protected SEScalar                specificVentilation;
  protected SEScalarVolume          tidalVolume;
  protected SEScalarVolumePerTime   totalAlveolarVentilation;
  protected SEScalarVolumePerTime   totalDeadSpaceVentilation;
  protected SEScalarVolume          totalLungVolume;
  protected SEScalarVolumePerTime   totalPulmonaryVentilation;
  protected SEScalarPressure        transpulmonaryPressure;
  
  
  public SERespiratorySystem()
  {    
    alveolarArterialGradient = null;
    carricoIndex = null;  
    endTidalCarbonDioxideFraction = null;
    endTidalCarbonDioxidePressure = null;
    expiratoryFlow = null;
    inspiratoryExpiratoryRatio = null;
    inspiratoryFlow = null;
    pulmonaryCompliance = null;
    pulmonaryResistance = null;
    respirationDriverPressure = null;
    respirationMusclePressure = null;
    respirationRate = null;
    specificVentilation = null;
    tidalVolume = null;
    totalAlveolarVentilation = null;
    totalDeadSpaceVentilation = null;
    totalLungVolume = null;
    totalPulmonaryVentilation = null;
    transpulmonaryPressure = null;
  }
  
  public void reset()
  {
    if (alveolarArterialGradient != null)
      alveolarArterialGradient.invalidate();
    if (carricoIndex != null)
      carricoIndex.invalidate();
    if (endTidalCarbonDioxideFraction != null)
      endTidalCarbonDioxideFraction.invalidate();
    if (endTidalCarbonDioxidePressure != null)
      endTidalCarbonDioxidePressure.invalidate();
    if (expiratoryFlow != null)
      expiratoryFlow.invalidate();    
    if (inspiratoryExpiratoryRatio != null)
      inspiratoryExpiratoryRatio.invalidate();
    if (inspiratoryFlow != null)
      inspiratoryFlow.invalidate();
    if (pulmonaryCompliance != null)
      pulmonaryCompliance.invalidate();
    if (pulmonaryResistance != null)
      pulmonaryResistance.invalidate();
    if (respirationDriverPressure != null)
      respirationDriverPressure.invalidate();
    if (respirationMusclePressure != null)
      respirationMusclePressure.invalidate();
    if (respirationRate != null)
      respirationRate.invalidate();
    if (specificVentilation != null)
      specificVentilation.invalidate();
    if (tidalVolume != null)
      tidalVolume.invalidate();
    if (totalAlveolarVentilation != null)
      totalAlveolarVentilation.invalidate();
    if (totalDeadSpaceVentilation != null)
      totalDeadSpaceVentilation.invalidate();
    if (totalLungVolume != null)
      totalLungVolume.invalidate();
    if (totalPulmonaryVentilation != null)
      totalPulmonaryVentilation.invalidate();
    if (transpulmonaryPressure != null)
      transpulmonaryPressure.invalidate();
  }
  
  public static void load(RespiratorySystemData src, SERespiratorySystem dst)
  {
    if (src.hasAlveolarArterialGradient())
      SEScalarPressure.load(src.getAlveolarArterialGradient(),dst.getAlveolarArterialGradient());
    if (src.hasCarricoIndex())
      SEScalarPressure.load(src.getCarricoIndex(),dst.getCarricoIndex());
    if (src.hasEndTidalCarbonDioxideFraction())
      SEScalar0To1.load(src.getEndTidalCarbonDioxideFraction(),dst.getEndTidalCarbonDioxideFraction());
    if (src.hasEndTidalCarbonDioxidePressure())
      SEScalarPressure.load(src.getEndTidalCarbonDioxidePressure(),dst.getEndTidalCarbonDioxidePressure());
    if (src.hasExpiratoryFlow())
      SEScalarVolumePerTime.load(src.getExpiratoryFlow(),dst.getExpiratoryFlow());
    if (src.hasInspiratoryExpiratoryRatio())
      SEScalar.load(src.getInspiratoryExpiratoryRatio(),dst.getInspiratoryExpiratoryRatio()); 
    if (src.hasInspiratoryFlow())
      SEScalarVolumePerTime.load(src.getInspiratoryFlow(),dst.getInspiratoryFlow()); 
    if (src.hasPulmonaryCompliance())
      SEScalarFlowCompliance.load(src.getPulmonaryCompliance(),dst.getPulmonaryCompliance()); 
    if (src.hasPulmonaryResistance())
      SEScalarFlowResistance.load(src.getPulmonaryResistance(),dst.getPulmonaryResistance()); 
    if (src.hasRespirationDriverPressure())
      SEScalarPressure.load(src.getRespirationDriverPressure(),dst.getRespirationDriverPressure());
    if (src.hasRespirationMusclePressure())
      SEScalarPressure.load(src.getRespirationMusclePressure(),dst.getRespirationMusclePressure());
    if (src.hasRespirationRate())
      SEScalarFrequency.load(src.getRespirationRate(),dst.getRespirationRate());
    if (src.hasSpecificVentilation())
      SEScalar.load(src.getSpecificVentilation(),dst.getSpecificVentilation());
    if (src.hasTidalVolume())
      SEScalarVolume.load(src.getTidalVolume(),dst.getTidalVolume()); 
    if (src.hasTotalAlveolarVentilation())
      SEScalarVolumePerTime.load(src.getTotalAlveolarVentilation(),dst.getTotalAlveolarVentilation());
    if (src.hasTotalDeadSpaceVentilation())
      SEScalarVolumePerTime.load(src.getTotalDeadSpaceVentilation(),dst.getTotalDeadSpaceVentilation());
    if (src.hasTotalLungVolume())
      SEScalarVolume.load(src.getTotalLungVolume(),dst.getTotalLungVolume());
    if (src.hasTotalPulmonaryVentilation())
      SEScalarVolumePerTime.load(src.getTotalPulmonaryVentilation(),dst.getTotalPulmonaryVentilation()); 
    if (src.hasTranspulmonaryPressure())
      SEScalarPressure.load(src.getTranspulmonaryPressure(),dst.getTranspulmonaryPressure());    
  }
  
  public static RespiratorySystemData unload(SERespiratorySystem src)
  {
    RespiratorySystemData.Builder dst = RespiratorySystemData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  
  protected static void unload(SERespiratorySystem src, RespiratorySystemData.Builder dst)
  {
    if (src.hasAlveolarArterialGradient())
      dst.setAlveolarArterialGradient(SEScalarPressure.unload(src.getAlveolarArterialGradient()));    
    if (src.hasCarricoIndex())
      dst.setCarricoIndex(SEScalarPressure.unload(src.getCarricoIndex()));    
    if (src.hasEndTidalCarbonDioxideFraction())
      dst.setEndTidalCarbonDioxideFraction(SEScalar0To1.unload(src.getEndTidalCarbonDioxideFraction()));    
    if (src.hasEndTidalCarbonDioxidePressure())
      dst.setEndTidalCarbonDioxidePressure(SEScalarPressure.unload(src.getEndTidalCarbonDioxidePressure()));    
    if (src.hasExpiratoryFlow())
      dst.setExpiratoryFlow(SEScalarVolumePerTime.unload(src.getExpiratoryFlow()));    
    if (src.hasInspiratoryExpiratoryRatio())
      dst.setInspiratoryExpiratoryRatio(SEScalar.unload(src.getInspiratoryExpiratoryRatio()));    
    if (src.hasInspiratoryFlow())
      dst.setInspiratoryFlow(SEScalarVolumePerTime.unload(src.getInspiratoryFlow()));    
    if (src.hasPulmonaryCompliance())
      dst.setPulmonaryCompliance(SEScalarFlowCompliance.unload(src.getPulmonaryCompliance()));
    if (src.hasPulmonaryResistance())
      dst.setPulmonaryResistance(SEScalarFlowResistance.unload(src.getPulmonaryResistance()));  
    if (src.hasRespirationDriverPressure())
      dst.setRespirationDriverPressure(SEScalarPressure.unload(src.getRespirationDriverPressure()));
    if (src.hasRespirationMusclePressure())
      dst.setRespirationMusclePressure(SEScalarPressure.unload(src.getRespirationMusclePressure()));
    if (src.hasRespirationRate())
      dst.setRespirationRate(SEScalarFrequency.unload(src.getRespirationRate()));
    if (src.hasSpecificVentilation())
      dst.setSpecificVentilation(SEScalar.unload(src.getSpecificVentilation()));    
    if (src.hasTidalVolume())
      dst.setTidalVolume(SEScalarVolume.unload(src.getTidalVolume()));
    if (src.hasTotalAlveolarVentilation())
      dst.setTotalAlveolarVentilation(SEScalarVolumePerTime.unload(src.getTotalAlveolarVentilation()));
    if (src.hasTotalDeadSpaceVentilation())
      dst.setTotalDeadSpaceVentilation(SEScalarVolumePerTime.unload(src.getTotalDeadSpaceVentilation()));
    if (src.hasTotalLungVolume())
      dst.setTotalLungVolume(SEScalarVolume.unload(src.getTotalLungVolume()));    
    if (src.hasTotalPulmonaryVentilation())
      dst.setTotalPulmonaryVentilation(SEScalarVolumePerTime.unload(src.getTotalPulmonaryVentilation()));
    if (src.hasTranspulmonaryPressure())
      dst.setTranspulmonaryPressure(SEScalarPressure.unload(src.getTranspulmonaryPressure()));
  }
  
  public boolean hasAlveolarArterialGradient()
  {
    return alveolarArterialGradient == null ? false : alveolarArterialGradient.isValid();
  }
  public SEScalarPressure getAlveolarArterialGradient()
  {
    if (alveolarArterialGradient == null)
      alveolarArterialGradient = new SEScalarPressure();
    return alveolarArterialGradient;
  }
  
  public boolean hasCarricoIndex()
  {
    return carricoIndex == null ? false : carricoIndex.isValid();
  }
  public SEScalarPressure getCarricoIndex()
  {
    if (carricoIndex == null)
      carricoIndex = new SEScalarPressure();
    return carricoIndex;
  }
  
  /*
   * End Tidal Carbon Dioxide Fraction
   */
  public boolean hasEndTidalCarbonDioxideFraction()
  {
    return endTidalCarbonDioxideFraction == null ? false : endTidalCarbonDioxideFraction.isValid();
  }
  public SEScalar0To1 getEndTidalCarbonDioxideFraction()
  {
    if (endTidalCarbonDioxideFraction == null)
      endTidalCarbonDioxideFraction = new SEScalar0To1();
    return endTidalCarbonDioxideFraction;
  }
  
  public boolean hasEndTidalCarbonDioxidePressure()
  {
    return endTidalCarbonDioxidePressure == null ? false : endTidalCarbonDioxidePressure.isValid();
  }
  public SEScalarPressure getEndTidalCarbonDioxidePressure()
  {
    if (endTidalCarbonDioxidePressure == null)
      endTidalCarbonDioxidePressure = new SEScalarPressure();
    return endTidalCarbonDioxidePressure;
  }
  
  public boolean hasExpiratoryFlow()
  {
    return expiratoryFlow == null ? false : expiratoryFlow.isValid();
  }
  public SEScalarVolumePerTime getExpiratoryFlow()
  {
    if (expiratoryFlow == null)
      expiratoryFlow = new SEScalarVolumePerTime();
    return expiratoryFlow;
  }
  
  /*
   * Inspiratory Expiratory Ratio
   */
  public boolean hasInspiratoryExpiratoryRatio()
  {
    return inspiratoryExpiratoryRatio == null ? false : inspiratoryExpiratoryRatio.isValid();
  }
  public SEScalar getInspiratoryExpiratoryRatio()
  {
    if (inspiratoryExpiratoryRatio == null)
      inspiratoryExpiratoryRatio = new SEScalar();
    return inspiratoryExpiratoryRatio;
  }
  
  public boolean hasInspiratoryFlow()
  {
    return inspiratoryFlow == null ? false : inspiratoryFlow.isValid();
  }
  public SEScalarVolumePerTime getInspiratoryFlow()
  {
    if (inspiratoryFlow == null)
      inspiratoryFlow = new SEScalarVolumePerTime();
    return inspiratoryFlow;
  }
  
  /*
   * Pulmonary Compliance
   */
  public boolean hasPulmonaryCompliance()
  {
    return pulmonaryCompliance == null ? false : pulmonaryCompliance.isValid();
  }
  public SEScalarFlowCompliance getPulmonaryCompliance()
  {
    if (pulmonaryCompliance == null)
      pulmonaryCompliance = new SEScalarFlowCompliance();
    return pulmonaryCompliance;
  }
  
  /*
   * Pulmonary Resistance
   */
  public boolean hasPulmonaryResistance()
  {
    return pulmonaryResistance == null ? false : pulmonaryResistance.isValid();
  }
  public SEScalarFlowResistance getPulmonaryResistance()
  {
    if (pulmonaryResistance == null)
      pulmonaryResistance = new SEScalarFlowResistance();
    return pulmonaryResistance;
  }
  
  /*
   * Respiration Rate
   */
  public boolean hasRespirationDriverPressure()
  {
    return respirationDriverPressure == null ? false : respirationDriverPressure.isValid();
  }
  public SEScalarPressure getRespirationDriverPressure()
  {
    if (respirationDriverPressure == null)
      respirationDriverPressure = new SEScalarPressure();
    return respirationDriverPressure;
  }
  
  public boolean hasRespirationMusclePressure()
  {
    return respirationMusclePressure == null ? false : respirationMusclePressure.isValid();
  }
  public SEScalarPressure getRespirationMusclePressure()
  {
    if (respirationMusclePressure == null)
      respirationMusclePressure = new SEScalarPressure();
    return respirationMusclePressure;
  }
  
  public boolean hasRespirationRate()
  {
    return respirationRate == null ? false : respirationRate.isValid();
  }
  public SEScalarFrequency getRespirationRate()
  {
    if (respirationRate == null)
      respirationRate = new SEScalarFrequency();
    return respirationRate;
  }
  
  /*
   * Specific Ventilation
   */
  public boolean hasSpecificVentilation()
  {
    return specificVentilation == null ? false : specificVentilation.isValid();
  }
  public SEScalar getSpecificVentilation()
  {
    if (specificVentilation == null)
      specificVentilation = new SEScalar();
    return specificVentilation;
  }
  
  /*
   * Tidal Volume
   */
  public boolean hasTidalVolume()
  {
    return tidalVolume == null ? false : tidalVolume.isValid();
  }
  public SEScalarVolume getTidalVolume()
  {
    if (tidalVolume == null)
      tidalVolume = new SEScalarVolume();
    return tidalVolume;
  }
  
  /*
   * Total Alveolar Ventilation
   */
  public boolean hasTotalAlveolarVentilation()
  {
    return totalAlveolarVentilation == null ? false : totalAlveolarVentilation.isValid();
  }
  public SEScalarVolumePerTime getTotalAlveolarVentilation()
  {
    if (totalAlveolarVentilation == null)
      totalAlveolarVentilation = new SEScalarVolumePerTime();
    return totalAlveolarVentilation;
  }
  
  /*
   * Total Dead Space Ventilation
   */
  public boolean hasTotalDeadSpaceVentilation()
  {
    return totalDeadSpaceVentilation == null ? false : totalDeadSpaceVentilation.isValid();
  }
  public SEScalarVolumePerTime getTotalDeadSpaceVentilation()
  {
    if (totalDeadSpaceVentilation == null)
      totalDeadSpaceVentilation = new SEScalarVolumePerTime();
    return totalDeadSpaceVentilation;
  }
  
  /*
   * Total Lung Volume
   */
  public boolean hasTotalLungVolume()
  {
    return totalLungVolume == null ? false : totalLungVolume.isValid();
  }
  public SEScalarVolume getTotalLungVolume()
  {
    if (totalLungVolume == null)
      totalLungVolume = new SEScalarVolume();
    return totalLungVolume;
  }
  
  /*
   * Total Pulmonary Ventilation
   */
  public boolean hasTotalPulmonaryVentilation()
  {
    return totalPulmonaryVentilation == null ? false : totalPulmonaryVentilation.isValid();
  }
  public SEScalarVolumePerTime getTotalPulmonaryVentilation()
  {
    if (totalPulmonaryVentilation == null)
      totalPulmonaryVentilation = new SEScalarVolumePerTime();
    return totalPulmonaryVentilation;
  }
  
  /*
   * Transpulmonary Pressure
   */
  public boolean hasTranspulmonaryPressure()
  {
    return transpulmonaryPressure == null ? false : transpulmonaryPressure.isValid();
  }
  public SEScalarPressure getTranspulmonaryPressure()
  {
    if (transpulmonaryPressure == null)
      transpulmonaryPressure = new SEScalarPressure();
    return transpulmonaryPressure;
  }
}
