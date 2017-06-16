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

import com.kitware.physiology.cdm.Physiology.BloodChemistrySystemData;

import mil.tatrc.physiology.datamodel.properties.*;
import mil.tatrc.physiology.datamodel.system.SESystem;

public class SEBloodChemistrySystem extends SEPhysiologySystem implements SESystem
{
  protected SEScalarMassPerVolume          bloodDensity;
  protected SEScalar                       bloodPH;
  protected SEScalarHeatCapacitancePerMass bloodSpecificHeat;
  protected SEScalarMassPerVolume          bloodUreaNitrogenConcentration;
  protected SEScalar0To1                   carbonDioxideSaturation;
  protected SEScalar0To1                   carbonMonoxideSaturation;
  protected SEScalar0To1                   hematocrit;
  protected SEScalarMass                   hemoglobinContent;
  protected SEScalar0To1                   oxygenSaturation;
  protected SEScalarVolume                 plasmaVolume;
  protected SEScalarAmountPerVolume        phosphate;
  protected SEScalar0To1                   pulseOximetry;
  protected SEScalarAmountPerVolume        redBloodCellCount;
  protected SEScalar0To1                   shuntFraction;
  protected SEScalarAmountPerVolume        strongIonDifference;
  protected SEScalarMassPerVolume          totalProteinConcentration;
  protected SEScalar0To1                   volumeFractionNeutralLipidInPlasma;
  protected SEScalar0To1                   volumeFractionNeutralPhospholipidInPlasma;
  protected SEScalarAmountPerVolume        whiteBloodCellCount;

  protected SEScalarPressure               arterialCarbonDioxidePressure;
  protected SEScalarPressure               arterialOxygenPressure;
  protected SEScalarPressure               pulmonaryArterialOxygenPressure;
  protected SEScalarPressure               pulmonaryArterialCarbonDioxidePressure;
  protected SEScalarPressure               pulmonaryVenousOxygenPressure;
  protected SEScalarPressure               pulmonaryVenousCarbonDioxidePressure;
  protected SEScalarPressure               venousOxygenPressure;
  protected SEScalarPressure               venousCarbonDioxidePressure;

  public SEBloodChemistrySystem()
  {
    bloodDensity = null;
    bloodPH = null;
    bloodSpecificHeat = null;
    bloodUreaNitrogenConcentration = null;
    carbonDioxideSaturation = null;
    carbonMonoxideSaturation = null;
    hematocrit = null;
    hemoglobinContent = null;
    oxygenSaturation = null;
    phosphate = null;
    plasmaVolume = null;
    pulseOximetry = null;
    redBloodCellCount = null;
    shuntFraction = null;
    strongIonDifference = null;
    totalProteinConcentration = null;
    volumeFractionNeutralLipidInPlasma = null;
    volumeFractionNeutralPhospholipidInPlasma = null;
    whiteBloodCellCount = null;

    arterialCarbonDioxidePressure = null;
    arterialOxygenPressure = null;
    pulmonaryArterialOxygenPressure = null;
    pulmonaryArterialCarbonDioxidePressure = null;
    pulmonaryVenousOxygenPressure = null;
    pulmonaryVenousCarbonDioxidePressure = null;
    venousOxygenPressure = null;
    venousCarbonDioxidePressure = null;
  }

  public void reset()
  {
    if (bloodDensity != null)
      bloodDensity.invalidate();
    if (bloodPH != null)
      bloodPH.invalidate();
    if (bloodSpecificHeat != null)
      bloodSpecificHeat.invalidate();
    if (bloodUreaNitrogenConcentration != null)
      bloodUreaNitrogenConcentration.invalidate();
    if (carbonDioxideSaturation != null)
      carbonDioxideSaturation.invalidate();
    if (carbonMonoxideSaturation != null)
      carbonMonoxideSaturation.invalidate();
    if (hematocrit != null)
      hematocrit.invalidate();
    if (hemoglobinContent != null)
      hemoglobinContent.invalidate();
    if (oxygenSaturation != null)
      oxygenSaturation.invalidate();
    if (phosphate != null)
      phosphate.invalidate();
    if (plasmaVolume != null)
      plasmaVolume.invalidate();
    if (pulseOximetry != null)
      pulseOximetry.invalidate();
    if (redBloodCellCount != null)
      redBloodCellCount.invalidate();
    if (shuntFraction != null)
      shuntFraction.invalidate();
    if (strongIonDifference != null)
      strongIonDifference.invalidate();
    if (totalProteinConcentration != null)
      totalProteinConcentration.invalidate();
    if (volumeFractionNeutralLipidInPlasma != null)
      volumeFractionNeutralLipidInPlasma.invalidate();
    if (volumeFractionNeutralPhospholipidInPlasma != null)
      volumeFractionNeutralPhospholipidInPlasma.invalidate();
    if (whiteBloodCellCount != null)
      whiteBloodCellCount.invalidate();

    if (arterialCarbonDioxidePressure != null)
      arterialCarbonDioxidePressure.invalidate();
    if (arterialOxygenPressure != null)
      arterialOxygenPressure.invalidate();
    if (pulmonaryArterialOxygenPressure != null)
      pulmonaryArterialOxygenPressure.invalidate();
    if (pulmonaryArterialCarbonDioxidePressure != null)
      pulmonaryArterialCarbonDioxidePressure.invalidate();
    if (pulmonaryVenousOxygenPressure != null)
      pulmonaryVenousOxygenPressure.invalidate();
    if (pulmonaryVenousCarbonDioxidePressure != null)
      pulmonaryVenousCarbonDioxidePressure.invalidate();
    if (venousOxygenPressure != null)
      venousOxygenPressure.invalidate();
    if (venousCarbonDioxidePressure != null)
      venousCarbonDioxidePressure.invalidate();
  }

  public static void load(BloodChemistrySystemData src, SEBloodChemistrySystem dst)
  {
    if (src.hasBloodDensity())
      SEScalarMassPerVolume.load(src.getBloodDensity(),dst.getBloodDensity());
    if (src.hasBloodPH())
      SEScalar.load(src.getBloodPH(),dst.getBloodPH());
    if (src.hasBloodSpecificHeat())
      SEScalarHeatCapacitancePerMass.load(src.getBloodSpecificHeat(),dst.getBloodSpecificHeat());
    if (src.hasBloodUreaNitrogenConcentration())
      SEScalarMassPerVolume.load(src.getBloodUreaNitrogenConcentration(),dst.getBloodUreaNitrogenConcentration());
    if (src.hasCarbonDioxideSaturation())
      SEScalar0To1.load(src.getCarbonDioxideSaturation(),dst.getCarbonDioxideSaturation());
    if (src.hasCarbonMonoxideSaturation())
      SEScalar0To1.load(src.getCarbonMonoxideSaturation(),dst.getCarbonMonoxideSaturation());
    if (src.hasHematocrit())
      SEScalar0To1.load(src.getHematocrit(),dst.getHematocrit());
    if (src.hasHemoglobinContent())
      SEScalarMass.load(src.getHemoglobinContent(),dst.getHemoglobinContent());
    if (src.hasOxygenSaturation())
      SEScalar0To1.load(src.getOxygenSaturation(),dst.getOxygenSaturation());
    if (src.hasPhosphate())
      SEScalarAmountPerVolume.load(src.getPhosphate(),dst.getPhosphate());  
    if (src.hasPlasmaVolume())
      SEScalarVolume.load(src.getPlasmaVolume(),dst.getPlasmaVolume());  
    if (src.hasPulseOximetry())
      SEScalar0To1.load(src.getPulseOximetry(),dst.getPulseOximetry());  
    if (src.hasRedBloodCellCount())
      SEScalarAmountPerVolume.load(src.getRedBloodCellCount(),dst.getRedBloodCellCount());
    if (src.hasShuntFraction())
      SEScalar0To1.load(src.getShuntFraction(),dst.getShuntFraction());
    if (src.hasStrongIonDifference())
      SEScalarAmountPerVolume.load(src.getStrongIonDifference(),dst.getStrongIonDifference());
    if (src.hasTotalProteinConcentration())
      SEScalarMassPerVolume.load(src.getTotalProteinConcentration(),dst.getTotalProteinConcentration());
    if (src.hasVolumeFractionNeutralLipidInPlasma())
      SEScalar0To1.load(src.getVolumeFractionNeutralLipidInPlasma(),dst.getVolumeFractionNeutralLipidInPlasma());
    if (src.hasVolumeFractionNeutralPhospholipidInPlasma())
      SEScalar0To1.load(src.getVolumeFractionNeutralPhospholipidInPlasma(),dst.getVolumeFractionNeutralPhospholipidInPlasma());
    if (src.hasWhiteBloodCellCount())
      SEScalarAmountPerVolume.load(src.getWhiteBloodCellCount(),dst.getWhiteBloodCellCount());

    if (src.hasArterialCarbonDioxidePressure())
      SEScalarPressure.load(src.getArterialCarbonDioxidePressure(),dst.getArterialCarbonDioxidePressure());
    if (src.hasArterialOxygenPressure())
      SEScalarPressure.load(src.getArterialOxygenPressure(),dst.getArterialOxygenPressure());
    if (src.hasPulmonaryArterialCarbonDioxidePressure())
      SEScalarPressure.load(src.getPulmonaryArterialCarbonDioxidePressure(),dst.getPulmonaryArterialCarbonDioxidePressure());
    if (src.hasPulmonaryArterialOxygenPressure())
      SEScalarPressure.load(src.getPulmonaryArterialOxygenPressure(),dst.getPulmonaryArterialOxygenPressure());   
    if (src.hasPulmonaryVenousCarbonDioxidePressure())
      SEScalarPressure.load(src.getPulmonaryVenousCarbonDioxidePressure(),dst.getPulmonaryVenousCarbonDioxidePressure());  
    if (src.hasPulmonaryVenousOxygenPressure())
      SEScalarPressure.load(src.getPulmonaryVenousOxygenPressure(),dst.getPulmonaryVenousOxygenPressure());
    if (src.hasVenousOxygenPressure())
      SEScalarPressure.load(src.getVenousOxygenPressure(),dst.getVenousOxygenPressure());
    if (src.hasVenousCarbonDioxidePressure())
      SEScalarPressure.load(src.getVenousCarbonDioxidePressure(),dst.getVenousCarbonDioxidePressure());
  }

  public static BloodChemistrySystemData unload(SEBloodChemistrySystem src)
  {
    BloodChemistrySystemData.Builder dst = BloodChemistrySystemData.newBuilder();
    unload(src,dst);
    return dst.build();
  }

  protected static void unload(SEBloodChemistrySystem src, BloodChemistrySystemData.Builder dst)
  {
    if (src.hasBloodDensity())
      dst.setBloodDensity(SEScalarMassPerVolume.unload(src.getBloodDensity()));
    if (src.hasBloodPH())
      dst.setBloodPH(SEScalar.unload(src.getBloodPH()));
    if (src.hasBloodSpecificHeat())
      dst.setBloodSpecificHeat(SEScalarHeatCapacitancePerMass.unload(src.getBloodSpecificHeat()));
    if (src.hasBloodUreaNitrogenConcentration())
      dst.setBloodUreaNitrogenConcentration(SEScalarMassPerVolume.unload(src.getBloodUreaNitrogenConcentration()));
    if (src.hasCarbonDioxideSaturation())
      dst.setCarbonDioxideSaturation(SEScalar0To1.unload(src.getCarbonDioxideSaturation()));
    if (src.hasCarbonMonoxideSaturation())
      dst.setCarbonMonoxideSaturation(SEScalar0To1.unload(src.getCarbonMonoxideSaturation()));
    if (src.hasHematocrit())
      dst.setHematocrit(SEScalar0To1.unload(src.getHematocrit()));
    if (src.hasHemoglobinContent())
      dst.setHemoglobinContent(SEScalarMass.unload(src.getHemoglobinContent()));
    if (src.hasOxygenSaturation())
      dst.setOxygenSaturation(SEScalar0To1.unload(src.getOxygenSaturation()));
    if (src.hasPhosphate())
      dst.setPhosphate(SEScalarAmountPerVolume.unload(src.getPhosphate()));
    if (src.hasPlasmaVolume())
      dst.setPlasmaVolume(SEScalarVolume.unload(src.getPlasmaVolume()));
    if (src.hasPulseOximetry())
      dst.setPulseOximetry(SEScalar0To1.unload(src.getPulseOximetry()));
    if (src.hasRedBloodCellCount())
      dst.setRedBloodCellCount(SEScalarAmountPerVolume.unload(src.getRedBloodCellCount()));
    if (src.hasShuntFraction())
      dst.setShuntFraction(SEScalar0To1.unload(src.getShuntFraction()));
    if (src.hasStrongIonDifference())
      dst.setStrongIonDifference(SEScalarAmountPerVolume.unload(src.getStrongIonDifference()));
    if (src.hasTotalProteinConcentration())
      dst.setTotalProteinConcentration(SEScalarMassPerVolume.unload(src.getTotalProteinConcentration()));
    if (src.hasVolumeFractionNeutralLipidInPlasma())
      dst.setVolumeFractionNeutralLipidInPlasma(SEScalar0To1.unload(src.getVolumeFractionNeutralLipidInPlasma()));
    if (src.hasVolumeFractionNeutralPhospholipidInPlasma())
      dst.setVolumeFractionNeutralPhospholipidInPlasma(SEScalar0To1.unload(src.getVolumeFractionNeutralPhospholipidInPlasma()));
    if (src.hasWhiteBloodCellCount())
      dst.setWhiteBloodCellCount(SEScalarAmountPerVolume.unload(src.getWhiteBloodCellCount()));

    if (src.hasArterialCarbonDioxidePressure())
      dst.setArterialCarbonDioxidePressure(SEScalarPressure.unload(src.getArterialCarbonDioxidePressure()));
    if (src.hasArterialOxygenPressure())
      dst.setArterialOxygenPressure(SEScalarPressure.unload(src.getArterialOxygenPressure()));
    if (src.hasPulmonaryArterialOxygenPressure())
      dst.setPulmonaryArterialOxygenPressure(SEScalarPressure.unload(src.getPulmonaryArterialOxygenPressure()));
    if (src.hasPulmonaryArterialCarbonDioxidePressure())
      dst.setPulmonaryArterialCarbonDioxidePressure(SEScalarPressure.unload(src.getPulmonaryArterialCarbonDioxidePressure()));
    if (src.hasPulmonaryVenousOxygenPressure())
      dst.setPulmonaryVenousOxygenPressure(SEScalarPressure.unload(src.getPulmonaryVenousOxygenPressure()));
    if (src.hasPulmonaryVenousCarbonDioxidePressure())
      dst.setPulmonaryVenousCarbonDioxidePressure(SEScalarPressure.unload(src.getPulmonaryVenousCarbonDioxidePressure()));
    if (src.hasVenousOxygenPressure())
      dst.setVenousOxygenPressure(SEScalarPressure.unload(src.getVenousOxygenPressure()));
    if (src.hasVenousCarbonDioxidePressure())
      dst.setVenousCarbonDioxidePressure(SEScalarPressure.unload(src.getVenousCarbonDioxidePressure()));
  }

  public boolean hasBloodDensity()
  {
    return bloodDensity == null ? false : bloodDensity.isValid();
  }
  public SEScalarMassPerVolume getBloodDensity()
  {
    if (bloodDensity == null)
      bloodDensity = new SEScalarMassPerVolume();
    return bloodDensity;
  }

  public boolean hasBloodPH()
  {
    return bloodPH == null ? false : bloodPH.isValid();
  }
  public SEScalar getBloodPH()
  {
    if (bloodPH == null)
      bloodPH = new SEScalar();
    return bloodPH;  }

  public boolean hasBloodSpecificHeat()
  {
    return bloodSpecificHeat == null ? false : bloodSpecificHeat.isValid();
  }
  public SEScalarHeatCapacitancePerMass getBloodSpecificHeat()
  {
    if (bloodSpecificHeat == null)
      bloodSpecificHeat = new SEScalarHeatCapacitancePerMass();
    return bloodSpecificHeat;
  }
  
  public boolean hasBloodUreaNitrogenConcentration()
  {
    return bloodUreaNitrogenConcentration == null ? false : bloodUreaNitrogenConcentration.isValid();
  }
  public SEScalarMassPerVolume getBloodUreaNitrogenConcentration()
  {
    if (bloodUreaNitrogenConcentration == null)
      bloodUreaNitrogenConcentration = new SEScalarMassPerVolume();
    return bloodUreaNitrogenConcentration;
  }

  public boolean hasCarbonDioxideSaturation()
  {
    return carbonDioxideSaturation == null ? false : carbonDioxideSaturation.isValid();
  }
  public SEScalar0To1 getCarbonDioxideSaturation()
  {
    if (carbonDioxideSaturation == null)
      carbonDioxideSaturation = new SEScalar0To1();
    return carbonDioxideSaturation;
  }
  
  public boolean hasCarbonMonoxideSaturation()
  {
    return carbonMonoxideSaturation == null ? false : carbonMonoxideSaturation.isValid();
  }
  public SEScalar0To1 getCarbonMonoxideSaturation()
  {
    if (carbonMonoxideSaturation == null)
      carbonMonoxideSaturation = new SEScalar0To1();
    return carbonMonoxideSaturation;
  }

  public boolean hasHematocrit()
  {
    return hematocrit == null ? false : hematocrit.isValid();
  }
  public SEScalar0To1 getHematocrit()
  {
    if (hematocrit == null)
      hematocrit = new SEScalar0To1();
    return hematocrit;  }

  public boolean hasHemoglobinContent()
  {
    return hemoglobinContent == null ? false : hemoglobinContent.isValid();
  }
  public SEScalarMass getHemoglobinContent()
  {
    if (hemoglobinContent == null)
      hemoglobinContent = new SEScalarMass();
    return hemoglobinContent;  }

  public boolean hasOxygenSaturation()
  {
    return oxygenSaturation == null ? false : oxygenSaturation.isValid();
  }
  public SEScalar0To1 getOxygenSaturation()
  {
    if (oxygenSaturation == null)
      oxygenSaturation = new SEScalar0To1();
    return oxygenSaturation;  }

  public boolean hasPhosphate()
  {
    return phosphate == null ? false : phosphate.isValid();
  }
  public SEScalarAmountPerVolume getPhosphate()
  {
    if (phosphate == null)
      phosphate = new SEScalarAmountPerVolume();
    return phosphate;
  }
  
  public boolean hasPlasmaVolume()
  {
    return plasmaVolume == null ? false : plasmaVolume.isValid();
  }
  public SEScalarVolume getPlasmaVolume()
  {
    if (plasmaVolume == null)
      plasmaVolume = new SEScalarVolume();
    return plasmaVolume;
  }
  
  public boolean hasPulseOximetry()
  {
    return pulseOximetry == null ? false : pulseOximetry.isValid();
  }
  public SEScalar0To1 getPulseOximetry()
  {
    if (pulseOximetry == null)
      pulseOximetry = new SEScalar0To1();
    return pulseOximetry;
  }

  public boolean hasRedBloodCellCount()
  {
    return redBloodCellCount == null ? false : redBloodCellCount.isValid();
  }
  public SEScalarAmountPerVolume getRedBloodCellCount()
  {
    if (redBloodCellCount == null)
      redBloodCellCount = new SEScalarAmountPerVolume();
    return redBloodCellCount;  }

  public boolean hasShuntFraction()
  {
    return shuntFraction == null ? false : shuntFraction.isValid();
  }
  public SEScalar0To1 getShuntFraction()
  {
    if (shuntFraction == null)
      shuntFraction = new SEScalar0To1();
    return shuntFraction;  }
  
  public boolean hasStrongIonDifference()
  {
    return strongIonDifference == null ? false : strongIonDifference.isValid();
  }
  public SEScalarAmountPerVolume getStrongIonDifference()
  {
    if (strongIonDifference == null)
      strongIonDifference = new SEScalarAmountPerVolume();
    return strongIonDifference;
  }
  
  public boolean hasTotalProteinConcentration()
  {
    return totalProteinConcentration == null ? false : totalProteinConcentration.isValid();
  }
  public SEScalarMassPerVolume getTotalProteinConcentration()
  {
    if (totalProteinConcentration == null)
      totalProteinConcentration = new SEScalarMassPerVolume();
    return totalProteinConcentration;
  }

  public boolean hasVolumeFractionNeutralLipidInPlasma()
  {
    return volumeFractionNeutralLipidInPlasma == null ? false : volumeFractionNeutralLipidInPlasma.isValid();
  }
  public SEScalar0To1 getVolumeFractionNeutralLipidInPlasma()
  {
    if (volumeFractionNeutralLipidInPlasma == null)
      volumeFractionNeutralLipidInPlasma = new SEScalar0To1();
    return volumeFractionNeutralLipidInPlasma;
  }

  public boolean hasVolumeFractionNeutralPhospholipidInPlasma()
  {
    return volumeFractionNeutralPhospholipidInPlasma == null ? false : volumeFractionNeutralPhospholipidInPlasma.isValid();
  }
  public SEScalar0To1 getVolumeFractionNeutralPhospholipidInPlasma()
  {
    if (volumeFractionNeutralPhospholipidInPlasma == null)
      volumeFractionNeutralPhospholipidInPlasma = new SEScalar0To1();
    return volumeFractionNeutralPhospholipidInPlasma;
  }

  public boolean hasWhiteBloodCellCount()
  {
    return whiteBloodCellCount == null ? false : whiteBloodCellCount.isValid();
  }
  public SEScalarAmountPerVolume getWhiteBloodCellCount()
  {
    if (whiteBloodCellCount == null)
      whiteBloodCellCount = new SEScalarAmountPerVolume();
    return whiteBloodCellCount;
  }
  

  public boolean hasArterialCarbonDioxidePressure()
  {
    return arterialCarbonDioxidePressure == null ? false : arterialCarbonDioxidePressure.isValid();
  }
  public SEScalarPressure getArterialCarbonDioxidePressure()
  {
    if (arterialCarbonDioxidePressure == null)
      arterialCarbonDioxidePressure = new SEScalarPressure();
    return arterialCarbonDioxidePressure;
  }

  public boolean hasArterialOxygenPressure()
  {
    return arterialOxygenPressure == null ? false : arterialOxygenPressure.isValid();
  }
  public SEScalarPressure getArterialOxygenPressure()
  {
    if (arterialOxygenPressure == null)
      arterialOxygenPressure = new SEScalarPressure();
    return arterialOxygenPressure;
  }

  public boolean hasPulmonaryArterialCarbonDioxidePressure()
  {
    return pulmonaryArterialCarbonDioxidePressure == null ? false : pulmonaryArterialCarbonDioxidePressure.isValid();
  }
  public SEScalarPressure getPulmonaryArterialCarbonDioxidePressure()
  {
    if (pulmonaryArterialCarbonDioxidePressure == null)
      pulmonaryArterialCarbonDioxidePressure = new SEScalarPressure();
    return pulmonaryArterialCarbonDioxidePressure;
  }

  public boolean hasPulmonaryArterialOxygenPressure()
  {
    return pulmonaryArterialOxygenPressure == null ? false : pulmonaryArterialOxygenPressure.isValid();
  }
  public SEScalarPressure getPulmonaryArterialOxygenPressure()
  {
    if (pulmonaryArterialOxygenPressure == null)
      pulmonaryArterialOxygenPressure = new SEScalarPressure();
    return pulmonaryArterialOxygenPressure;
  }

  public boolean hasPulmonaryVenousCarbonDioxidePressure()
  {
    return pulmonaryVenousCarbonDioxidePressure == null ? false : pulmonaryVenousCarbonDioxidePressure.isValid();
  }
  public SEScalarPressure getPulmonaryVenousCarbonDioxidePressure()
  {
    if (pulmonaryVenousCarbonDioxidePressure == null)
      pulmonaryVenousCarbonDioxidePressure = new SEScalarPressure();
    return pulmonaryVenousCarbonDioxidePressure;
  }

  public boolean hasPulmonaryVenousOxygenPressure()
  {
    return pulmonaryVenousOxygenPressure == null ? false : pulmonaryVenousOxygenPressure.isValid();
  }
  public SEScalarPressure getPulmonaryVenousOxygenPressure()
  {
    if (pulmonaryVenousOxygenPressure == null)
      pulmonaryVenousOxygenPressure = new SEScalarPressure();
    return pulmonaryVenousOxygenPressure;  }

  public boolean hasVenousCarbonDioxidePressure()
  {
    return venousCarbonDioxidePressure == null ? false : venousCarbonDioxidePressure.isValid();
  }
  public SEScalarPressure getVenousCarbonDioxidePressure()
  {
    if (venousCarbonDioxidePressure == null)
      venousCarbonDioxidePressure = new SEScalarPressure();
    return venousCarbonDioxidePressure;
  }

  public boolean hasVenousOxygenPressure()
  {
    return venousOxygenPressure == null ? false : venousOxygenPressure.isValid();
  }
  public SEScalarPressure getVenousOxygenPressure()
  {
    if (venousOxygenPressure == null)
      venousOxygenPressure = new SEScalarPressure();
    return venousOxygenPressure;  }
}
