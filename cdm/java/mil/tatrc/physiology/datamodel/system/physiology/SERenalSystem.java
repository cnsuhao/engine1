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

import com.kitware.physiology.cdm.Physiology.RenalSystemData;

import mil.tatrc.physiology.datamodel.properties.*;
import mil.tatrc.physiology.datamodel.system.SESystem;

public class SERenalSystem extends SEPhysiologySystem implements SESystem
{
  protected SEScalarVolumePerTime glomerularFiltrationRate;
  protected SEScalar0To1 filtrationFraction;
  protected SEScalarFlowResistance leftAfferentArterioleResistance;
  protected SEScalarPressure leftBowmansCapsulesHydrostaticPressure;
  protected SEScalarPressure leftBowmansCapsulesOsmoticPressure;
  protected SEScalarFlowResistance leftEfferentArterioleResistance;
  protected SEScalarPressure leftGlomerularCapillariesHydrostaticPressure;
  protected SEScalarPressure leftGlomerularCapillariesOsmoticPressure;
  protected SEScalarVolumePerTimePressure leftGlomerularFiltrationCoefficient;
  protected SEScalarVolumePerTime leftGlomerularFiltrationRate;
  protected SEScalarArea leftGlomerularFiltrationSurfaceArea;
  protected SEScalarVolumePerTimePressureArea leftGlomerularFluidPermeability;
  protected SEScalar0To1 leftFiltrationFraction;
  protected SEScalarPressure leftNetFiltrationPressure;
  protected SEScalarPressure leftNetReabsorptionPressure;
  protected SEScalarPressure leftPeritubularCapillariesHydrostaticPressure;
  protected SEScalarPressure leftPeritubularCapillariesOsmoticPressure;
  protected SEScalarVolumePerTimePressure leftReabsorptionFiltrationCoefficient;
  protected SEScalarVolumePerTime leftReabsorptionRate;
  protected SEScalarPressure leftTubularOsmoticPressure;
  protected SEScalarPressure leftTubularHydrostaticPressure;
  protected SEScalarArea leftTubularReabsorptionFiltrationSurfaceArea;
  protected SEScalarVolumePerTimePressureArea leftTubularReabsorptionFluidPermeability;
  protected SEScalarVolumePerTime renalBloodFlow;
  protected SEScalarVolumePerTime renalPlasmaFlow;
  protected SEScalarFlowResistance renalVascularResistance;
  protected SEScalarFlowResistance rightAfferentArterioleResistance;
  protected SEScalarPressure rightBowmansCapsulesHydrostaticPressure;
  protected SEScalarPressure rightBowmansCapsulesOsmoticPressure;
  protected SEScalarFlowResistance rightEfferentArterioleResistance;
  protected SEScalarPressure rightGlomerularCapillariesHydrostaticPressure;
  protected SEScalarPressure rightGlomerularCapillariesOsmoticPressure;
  protected SEScalarVolumePerTimePressure rightGlomerularFiltrationCoefficient;
  protected SEScalarVolumePerTime rightGlomerularFiltrationRate;
  protected SEScalarArea rightGlomerularFiltrationSurfaceArea;
  protected SEScalarVolumePerTimePressureArea rightGlomerularFluidPermeability;
  protected SEScalar0To1 rightFiltrationFraction;
  protected SEScalarPressure rightNetFiltrationPressure;
  protected SEScalarPressure rightNetReabsorptionPressure;
  protected SEScalarPressure rightPeritubularCapillariesHydrostaticPressure;
  protected SEScalarPressure rightPeritubularCapillariesOsmoticPressure;
  protected SEScalarVolumePerTimePressure rightReabsorptionFiltrationCoefficient;
  protected SEScalarVolumePerTime rightReabsorptionRate;
  protected SEScalarPressure rightTubularOsmoticPressure;
  protected SEScalarPressure rightTubularHydrostaticPressure;
  protected SEScalarArea rightTubularReabsorptionFiltrationSurfaceArea;
  protected SEScalarVolumePerTimePressureArea rightTubularReabsorptionFluidPermeability;
  protected SEScalarVolumePerTime urinationRate;
  protected SEScalarOsmolality urineOsmolality;
  protected SEScalarOsmolarity urineOsmolarity;
  protected SEScalarVolumePerTime urineProductionRate;
  protected SEScalar urineSpecificGravity;
  protected SEScalarVolume urineVolume;
  protected SEScalarMassPerVolume urineUreaNitrogenConcentration;

  public SERenalSystem()
  {
    glomerularFiltrationRate = null;
    filtrationFraction = null;
    leftAfferentArterioleResistance = null;
    leftBowmansCapsulesHydrostaticPressure = null;
    leftBowmansCapsulesOsmoticPressure = null;
    leftEfferentArterioleResistance = null;
    leftGlomerularCapillariesHydrostaticPressure = null;
    leftGlomerularCapillariesOsmoticPressure = null;
    leftGlomerularFiltrationCoefficient = null;
    leftGlomerularFiltrationRate = null;
    leftGlomerularFiltrationSurfaceArea = null;
    leftGlomerularFluidPermeability = null;
    leftFiltrationFraction = null;
    leftNetFiltrationPressure = null;
    leftNetReabsorptionPressure = null;
    leftPeritubularCapillariesHydrostaticPressure = null;
    leftPeritubularCapillariesOsmoticPressure = null;
    leftReabsorptionFiltrationCoefficient = null;
    leftReabsorptionRate = null;
    leftTubularOsmoticPressure = null;
    leftTubularHydrostaticPressure = null;
    leftTubularReabsorptionFiltrationSurfaceArea = null;
    leftTubularReabsorptionFluidPermeability = null;
    renalBloodFlow = null;
    renalPlasmaFlow = null;
    renalVascularResistance = null;
    rightAfferentArterioleResistance = null;
    rightBowmansCapsulesHydrostaticPressure = null;
    rightBowmansCapsulesOsmoticPressure = null;
    rightEfferentArterioleResistance = null;
    rightGlomerularCapillariesHydrostaticPressure = null;
    rightGlomerularCapillariesOsmoticPressure = null;
    rightGlomerularFiltrationCoefficient = null;
    rightGlomerularFiltrationRate = null;
    rightGlomerularFiltrationSurfaceArea = null;
    rightGlomerularFluidPermeability = null;
    rightFiltrationFraction = null;
    rightNetFiltrationPressure = null;
    rightNetReabsorptionPressure = null;
    rightPeritubularCapillariesHydrostaticPressure = null;
    rightPeritubularCapillariesOsmoticPressure = null;
    rightReabsorptionFiltrationCoefficient = null;
    rightReabsorptionRate = null;
    rightTubularOsmoticPressure = null;
    rightTubularHydrostaticPressure = null;
    rightTubularReabsorptionFiltrationSurfaceArea = null;
    rightTubularReabsorptionFluidPermeability = null;
    urinationRate = null;
    urineOsmolality = null;
    urineOsmolarity = null;
    urineProductionRate = null;
    urineSpecificGravity = null;
    urineVolume = null;
    urineUreaNitrogenConcentration = null;
  }

  public void reset()
  {
    if (glomerularFiltrationRate != null)
      glomerularFiltrationRate.invalidate();
    if (filtrationFraction != null)
      filtrationFraction.invalidate();
    if (leftAfferentArterioleResistance != null)
      leftAfferentArterioleResistance.invalidate();
    if (leftBowmansCapsulesHydrostaticPressure != null)
      leftBowmansCapsulesHydrostaticPressure.invalidate();
    if (leftBowmansCapsulesOsmoticPressure != null)
      leftBowmansCapsulesOsmoticPressure.invalidate();
    if (leftEfferentArterioleResistance != null)
      leftEfferentArterioleResistance.invalidate();
    if (leftGlomerularCapillariesHydrostaticPressure != null)
      leftGlomerularCapillariesHydrostaticPressure.invalidate();
    if (leftGlomerularCapillariesOsmoticPressure != null)
      leftGlomerularCapillariesOsmoticPressure.invalidate();
    if (leftGlomerularFiltrationCoefficient != null)
      leftGlomerularFiltrationCoefficient.invalidate();
    if (leftGlomerularFiltrationRate != null)
      leftGlomerularFiltrationRate.invalidate();
    if (leftGlomerularFiltrationSurfaceArea != null)
      leftGlomerularFiltrationSurfaceArea.invalidate();
    if (leftGlomerularFluidPermeability != null)
      leftGlomerularFluidPermeability.invalidate();
    if (leftFiltrationFraction != null)
      leftFiltrationFraction.invalidate();
    if (leftNetFiltrationPressure != null)
      leftNetFiltrationPressure.invalidate();
    if (leftNetReabsorptionPressure != null)
      leftNetReabsorptionPressure.invalidate();
    if (leftPeritubularCapillariesHydrostaticPressure != null)
      leftPeritubularCapillariesHydrostaticPressure.invalidate();
    if (leftPeritubularCapillariesOsmoticPressure != null)
      leftPeritubularCapillariesOsmoticPressure.invalidate();
    if (leftReabsorptionFiltrationCoefficient != null)
      leftReabsorptionFiltrationCoefficient.invalidate();
    if (leftReabsorptionRate != null)
      leftReabsorptionRate.invalidate();
    if (leftTubularOsmoticPressure != null)
      leftTubularOsmoticPressure.invalidate();
    if (leftTubularHydrostaticPressure != null)
      leftTubularHydrostaticPressure.invalidate();
    if (leftTubularReabsorptionFiltrationSurfaceArea != null)
      leftTubularReabsorptionFiltrationSurfaceArea.invalidate();
    if (leftTubularReabsorptionFluidPermeability != null)
      leftTubularReabsorptionFluidPermeability.invalidate();
    if (renalBloodFlow != null)
      renalBloodFlow.invalidate();
    if (renalPlasmaFlow != null)
      renalPlasmaFlow.invalidate();
    if (renalVascularResistance != null)
      renalVascularResistance.invalidate();
    if (rightAfferentArterioleResistance != null)
      rightAfferentArterioleResistance.invalidate();
    if (rightBowmansCapsulesHydrostaticPressure != null)
      rightBowmansCapsulesHydrostaticPressure.invalidate();
    if (rightBowmansCapsulesOsmoticPressure != null)
      rightBowmansCapsulesOsmoticPressure.invalidate();
    if (rightEfferentArterioleResistance != null)
      rightEfferentArterioleResistance.invalidate();
    if (rightGlomerularCapillariesHydrostaticPressure != null)
      rightGlomerularCapillariesHydrostaticPressure.invalidate();
    if (rightGlomerularCapillariesOsmoticPressure != null)
      rightGlomerularCapillariesOsmoticPressure.invalidate();
    if (rightGlomerularFiltrationCoefficient != null)
      rightGlomerularFiltrationCoefficient.invalidate();
    if (rightGlomerularFiltrationRate != null)
      rightGlomerularFiltrationRate.invalidate();
    if (rightGlomerularFiltrationSurfaceArea != null)
      rightGlomerularFiltrationSurfaceArea.invalidate();
    if (rightGlomerularFluidPermeability != null)
      rightGlomerularFluidPermeability.invalidate();
    if (rightFiltrationFraction != null)
      rightFiltrationFraction.invalidate();
    if (rightNetFiltrationPressure != null)
      rightNetFiltrationPressure.invalidate();
    if (rightNetReabsorptionPressure != null)
      rightNetReabsorptionPressure.invalidate();
    if (rightPeritubularCapillariesHydrostaticPressure != null)
      rightPeritubularCapillariesHydrostaticPressure.invalidate();
    if (rightPeritubularCapillariesOsmoticPressure != null)
      rightPeritubularCapillariesOsmoticPressure.invalidate();
    if (rightReabsorptionFiltrationCoefficient != null)
      rightReabsorptionFiltrationCoefficient.invalidate();
    if (rightReabsorptionRate != null)
      rightReabsorptionRate.invalidate();
    if (rightTubularOsmoticPressure != null)
      rightTubularOsmoticPressure.invalidate();
    if (rightTubularHydrostaticPressure != null)
      rightTubularHydrostaticPressure.invalidate();
    if (rightTubularReabsorptionFiltrationSurfaceArea != null)
      rightTubularReabsorptionFiltrationSurfaceArea.invalidate();
    if (rightTubularReabsorptionFluidPermeability != null)
      rightTubularReabsorptionFluidPermeability.invalidate();
    if (urinationRate != null)
      urinationRate.invalidate();
    if (urineOsmolality != null)
      urineOsmolality.invalidate();
    if (urineOsmolarity != null)
      urineOsmolarity.invalidate();
    if (urineProductionRate != null)
      urineProductionRate.invalidate();
    if (urineSpecificGravity != null)
      urineSpecificGravity.invalidate();
    if (urineVolume != null)
      urineVolume.invalidate();
    if (urineUreaNitrogenConcentration != null)
      urineUreaNitrogenConcentration.invalidate();
  }

  public static void load(RenalSystemData src, SERenalSystem dst)
  {
    if (src.hasGlomerularFiltrationRate())
      SEScalarVolumePerTime.load(src.getGlomerularFiltrationRate(),dst.getGlomerularFiltrationRate());
    if (src.hasFiltrationFraction())
      SEScalar0To1.load(src.getFiltrationFraction(),dst.getFiltrationFraction());
    if (src.hasLeftAfferentArterioleResistance())
      SEScalarFlowResistance.load(src.getLeftAfferentArterioleResistance(),dst.getLeftAfferentArterioleResistance());
    if (src.hasLeftBowmansCapsulesHydrostaticPressure())
      SEScalarPressure.load(src.getLeftBowmansCapsulesHydrostaticPressure(),dst.getLeftBowmansCapsulesHydrostaticPressure());
    if (src.hasLeftBowmansCapsulesOsmoticPressure())
      SEScalarPressure.load(src.getLeftBowmansCapsulesOsmoticPressure(),dst.getLeftBowmansCapsulesOsmoticPressure());
    if (src.hasLeftEfferentArterioleResistance())
      SEScalarFlowResistance.load(src.getLeftEfferentArterioleResistance(),dst.getLeftEfferentArterioleResistance());
    if (src.hasLeftGlomerularCapillariesHydrostaticPressure())
      SEScalarPressure.load(src.getLeftGlomerularCapillariesHydrostaticPressure(),dst.getLeftGlomerularCapillariesHydrostaticPressure());
    if (src.hasLeftGlomerularCapillariesOsmoticPressure())
      SEScalarPressure.load(src.getLeftGlomerularCapillariesOsmoticPressure(),dst.getLeftGlomerularCapillariesOsmoticPressure());
    if (src.hasLeftGlomerularFiltrationCoefficient())
      SEScalarVolumePerTimePressure.load(src.getLeftGlomerularFiltrationCoefficient(),dst.getLeftGlomerularFiltrationCoefficient());
    if (src.hasLeftGlomerularFiltrationRate())
      SEScalarVolumePerTime.load(src.getLeftGlomerularFiltrationRate(),dst.getLeftGlomerularFiltrationRate());
    if (src.hasLeftGlomerularFiltrationSurfaceArea())
      SEScalarArea.load(src.getLeftGlomerularFiltrationSurfaceArea(),dst.getLeftGlomerularFiltrationSurfaceArea());
    if (src.hasLeftGlomerularFluidPermeability())
      SEScalarVolumePerTimePressureArea.load(src.getLeftGlomerularFluidPermeability(),dst.getLeftGlomerularFluidPermeability());
    if (src.hasLeftFiltrationFraction())
      SEScalar0To1.load(src.getLeftFiltrationFraction(),dst.getLeftFiltrationFraction());
    if (src.hasLeftNetFiltrationPressure())
      SEScalarPressure.load(src.getLeftNetFiltrationPressure(),dst.getLeftNetFiltrationPressure());
    if (src.hasLeftNetReabsorptionPressure())
      SEScalarPressure.load(src.getLeftNetReabsorptionPressure(),dst.getLeftNetReabsorptionPressure());
    if (src.hasLeftPeritubularCapillariesHydrostaticPressure())
      SEScalarPressure.load(src.getLeftPeritubularCapillariesHydrostaticPressure(),dst.getLeftPeritubularCapillariesHydrostaticPressure());
    if (src.hasLeftPeritubularCapillariesOsmoticPressure())
      SEScalarPressure.load(src.getLeftPeritubularCapillariesOsmoticPressure(),dst.getLeftPeritubularCapillariesOsmoticPressure());
    if (src.hasLeftReabsorptionFiltrationCoefficient())
      SEScalarVolumePerTimePressure.load(src.getLeftReabsorptionFiltrationCoefficient(),dst.getLeftReabsorptionFiltrationCoefficient());
    if (src.hasLeftReabsorptionRate())
      SEScalarVolumePerTime.load(src.getLeftReabsorptionRate(),dst.getLeftReabsorptionRate());
    if (src.hasLeftTubularOsmoticPressure())
      SEScalarPressure.load(src.getLeftTubularOsmoticPressure(),dst.getLeftTubularOsmoticPressure());
    if (src.hasLeftTubularHydrostaticPressure())
      SEScalarPressure.load(src.getLeftTubularHydrostaticPressure(),dst.getLeftTubularHydrostaticPressure());
    if (src.hasLeftTubularReabsorptionFiltrationSurfaceArea())
      SEScalarArea.load(src.getLeftTubularReabsorptionFiltrationSurfaceArea(),dst.getLeftTubularReabsorptionFiltrationSurfaceArea());
    if (src.hasLeftTubularReabsorptionFluidPermeability())
      SEScalarVolumePerTimePressureArea.load(src.getLeftTubularReabsorptionFluidPermeability(),dst.getLeftTubularReabsorptionFluidPermeability());
    if (src.hasRenalBloodFlow())
      SEScalarVolumePerTime.load(src.getRenalBloodFlow(),dst.getRenalBloodFlow());
    if (src.hasRenalPlasmaFlow())
      SEScalarVolumePerTime.load(src.getRenalPlasmaFlow(),dst.getRenalPlasmaFlow());
    if (src.hasRenalVascularResistance())
      SEScalarFlowResistance.load(src.getRenalVascularResistance(),dst.getRenalVascularResistance());
    if (src.hasRightAfferentArterioleResistance())
      SEScalarFlowResistance.load(src.getRightAfferentArterioleResistance(),dst.getRightAfferentArterioleResistance());
    if (src.hasRightBowmansCapsulesHydrostaticPressure())
      SEScalarPressure.load(src.getRightBowmansCapsulesHydrostaticPressure(),dst.getRightBowmansCapsulesHydrostaticPressure());
    if (src.hasRightBowmansCapsulesOsmoticPressure())
      SEScalarPressure.load(src.getRightBowmansCapsulesOsmoticPressure(),dst.getRightBowmansCapsulesOsmoticPressure());
    if (src.hasRightEfferentArterioleResistance())
      SEScalarFlowResistance.load(src.getRightEfferentArterioleResistance(),dst.getRightEfferentArterioleResistance());
    if (src.hasRightGlomerularCapillariesHydrostaticPressure())
      SEScalarPressure.load(src.getRightGlomerularCapillariesHydrostaticPressure(),dst.getRightGlomerularCapillariesHydrostaticPressure());
    if (src.hasRightGlomerularCapillariesOsmoticPressure())
      SEScalarPressure.load(src.getRightGlomerularCapillariesOsmoticPressure(),dst.getRightGlomerularCapillariesOsmoticPressure());
    if (src.hasRightGlomerularFiltrationCoefficient())
      SEScalarVolumePerTimePressure.load(src.getRightGlomerularFiltrationCoefficient(),dst.getRightGlomerularFiltrationCoefficient());
    if (src.hasRightGlomerularFiltrationRate())
      SEScalarVolumePerTime.load(src.getRightGlomerularFiltrationRate(),dst.getRightGlomerularFiltrationRate());
    if (src.hasRightGlomerularFiltrationSurfaceArea())
      SEScalarArea.load(src.getRightGlomerularFiltrationSurfaceArea(),dst.getRightGlomerularFiltrationSurfaceArea());
    if (src.hasRightGlomerularFluidPermeability())
      SEScalarVolumePerTimePressureArea.load(src.getRightGlomerularFluidPermeability(),dst.getRightGlomerularFluidPermeability());
    if (src.hasRightFiltrationFraction())
      SEScalar0To1.load(src.getRightFiltrationFraction(),dst.getRightFiltrationFraction());
    if (src.hasRightNetFiltrationPressure())
      SEScalarPressure.load(src.getRightNetFiltrationPressure(),dst.getRightNetFiltrationPressure());
    if (src.hasRightNetReabsorptionPressure())
      SEScalarPressure.load(src.getRightNetReabsorptionPressure(),dst.getRightNetReabsorptionPressure());
    if (src.hasRightPeritubularCapillariesHydrostaticPressure())
      SEScalarPressure.load(src.getRightPeritubularCapillariesHydrostaticPressure(),dst.getRightPeritubularCapillariesHydrostaticPressure());
    if (src.hasRightPeritubularCapillariesOsmoticPressure())
      SEScalarPressure.load(src.getRightPeritubularCapillariesOsmoticPressure(),dst.getRightPeritubularCapillariesOsmoticPressure());
    if (src.hasRightReabsorptionFiltrationCoefficient())
      SEScalarVolumePerTimePressure.load(src.getRightReabsorptionFiltrationCoefficient(),dst.getRightReabsorptionFiltrationCoefficient());
    if (src.hasRightReabsorptionRate())
      SEScalarVolumePerTime.load(src.getRightReabsorptionRate(),dst.getRightReabsorptionRate());
    if (src.hasRightTubularOsmoticPressure())
      SEScalarPressure.load(src.getRightTubularOsmoticPressure(),dst.getRightTubularOsmoticPressure());
    if (src.hasRightTubularHydrostaticPressure())
      SEScalarPressure.load(src.getRightTubularHydrostaticPressure(),dst.getRightTubularHydrostaticPressure());
    if (src.hasRightTubularReabsorptionFiltrationSurfaceArea())
      SEScalarArea.load(src.getRightTubularReabsorptionFiltrationSurfaceArea(),dst.getRightTubularReabsorptionFiltrationSurfaceArea());
    if (src.hasRightTubularReabsorptionFluidPermeability())
      SEScalarVolumePerTimePressureArea.load(src.getRightTubularReabsorptionFluidPermeability(),dst.getRightTubularReabsorptionFluidPermeability());
    if (src.hasUrinationRate())
      SEScalarVolumePerTime.load(src.getUrinationRate(),dst.getUrinationRate());
    if (src.hasUrineOsmolality())
      SEScalarOsmolality.load(src.getUrineOsmolality(),dst.getUrineOsmolality());
    if (src.hasUrineOsmolarity())
      SEScalarOsmolarity.load(src.getUrineOsmolarity(),dst.getUrineOsmolarity());
    if (src.hasUrineProductionRate())
      SEScalarVolumePerTime.load(src.getUrineProductionRate(),dst.getUrineProductionRate());
    if (src.hasUrineSpecificGravity())
      SEScalar.load(src.getUrineSpecificGravity(),dst.getUrineSpecificGravity());
    if (src.hasUrineVolume())
      SEScalarVolume.load(src.getUrineVolume(),dst.getUrineVolume());
    if (src.hasUrineUreaNitrogenConcentration())
      SEScalarMassPerVolume.load(src.getUrineUreaNitrogenConcentration(),dst.getUrineUreaNitrogenConcentration());
  }

  public static RenalSystemData unload(SERenalSystem src)
  {
    RenalSystemData.Builder dst = RenalSystemData.newBuilder();
    unload(src,dst);
    return dst.build();
  }

  protected static void unload(SERenalSystem src, RenalSystemData.Builder dst)
  {
    if (src.hasGlomerularFiltrationRate())
      dst.setGlomerularFiltrationRate(SEScalarVolumePerTime.unload(src.getGlomerularFiltrationRate()));
    if (src.hasFiltrationFraction())
      dst.setFiltrationFraction(SEScalar0To1.unload(src.getFiltrationFraction()));
    if (src.hasLeftAfferentArterioleResistance())
      dst.setLeftAfferentArterioleResistance(SEScalarFlowResistance.unload(src.getLeftAfferentArterioleResistance()));
    if (src.hasLeftBowmansCapsulesHydrostaticPressure())
      dst.setLeftBowmansCapsulesHydrostaticPressure(SEScalarPressure.unload(src.getLeftBowmansCapsulesHydrostaticPressure()));
    if (src.hasLeftBowmansCapsulesOsmoticPressure())
      dst.setLeftBowmansCapsulesOsmoticPressure(SEScalarPressure.unload(src.getLeftBowmansCapsulesOsmoticPressure()));
    if (src.hasLeftBowmansCapsulesHydrostaticPressure())
      dst.setLeftEfferentArterioleResistance(SEScalarFlowResistance.unload(src.getLeftEfferentArterioleResistance()));
    if (src.hasLeftEfferentArterioleResistance())
      dst.setLeftGlomerularCapillariesHydrostaticPressure(SEScalarPressure.unload(src.getLeftGlomerularCapillariesHydrostaticPressure()));
    if (src.hasLeftGlomerularCapillariesOsmoticPressure())
      dst.setLeftGlomerularCapillariesOsmoticPressure(SEScalarPressure.unload(src.getLeftGlomerularCapillariesOsmoticPressure()));
    if (src.hasLeftGlomerularFiltrationCoefficient())
      dst.setLeftGlomerularFiltrationCoefficient(SEScalarVolumePerTimePressure.unload(src.getLeftGlomerularFiltrationCoefficient()));
    if (src.hasLeftGlomerularFiltrationRate())
      dst.setLeftGlomerularFiltrationRate(SEScalarVolumePerTime.unload(src.getLeftGlomerularFiltrationRate()));
    if (src.hasLeftGlomerularFiltrationSurfaceArea())
      dst.setLeftGlomerularFiltrationSurfaceArea(SEScalarArea.unload(src.getLeftGlomerularFiltrationSurfaceArea()));
    if (src.hasLeftGlomerularFluidPermeability())
      dst.setLeftGlomerularFluidPermeability(SEScalarVolumePerTimePressureArea.unload(src.getLeftGlomerularFluidPermeability()));
    if (src.hasLeftFiltrationFraction())
      dst.setLeftFiltrationFraction(SEScalar0To1.unload(src.getLeftFiltrationFraction()));
    if (src.hasLeftNetFiltrationPressure())
      dst.setLeftNetFiltrationPressure(SEScalarPressure.unload(src.getLeftNetFiltrationPressure()));
    if (src.hasLeftNetReabsorptionPressure())
      dst.setLeftNetReabsorptionPressure(SEScalarPressure.unload(src.getLeftNetReabsorptionPressure()));
    if (src.hasLeftPeritubularCapillariesHydrostaticPressure())
      dst.setLeftPeritubularCapillariesHydrostaticPressure(SEScalarPressure.unload(src.getLeftPeritubularCapillariesHydrostaticPressure()));
    if (src.hasLeftPeritubularCapillariesOsmoticPressure())
      dst.setLeftPeritubularCapillariesOsmoticPressure(SEScalarPressure.unload(src.getLeftPeritubularCapillariesOsmoticPressure()));
    if (src.hasLeftReabsorptionFiltrationCoefficient())
      dst.setLeftReabsorptionFiltrationCoefficient(SEScalarVolumePerTimePressure.unload(src.getLeftReabsorptionFiltrationCoefficient()));
    if (src.hasLeftReabsorptionRate())
      dst.setLeftReabsorptionRate(SEScalarVolumePerTime.unload(src.getLeftReabsorptionRate()));
    if (src.hasLeftTubularOsmoticPressure())
      dst.setLeftTubularOsmoticPressure(SEScalarPressure.unload(src.getLeftTubularOsmoticPressure()));
    if (src.hasLeftTubularHydrostaticPressure())
      dst.setLeftTubularHydrostaticPressure(SEScalarPressure.unload(src.getLeftTubularHydrostaticPressure()));
    if (src.hasLeftTubularReabsorptionFiltrationSurfaceArea())
      dst.setLeftTubularReabsorptionFiltrationSurfaceArea(SEScalarArea.unload(src.getLeftTubularReabsorptionFiltrationSurfaceArea()));
    if (src.hasLeftTubularReabsorptionFluidPermeability())
      dst.setLeftTubularReabsorptionFluidPermeability(SEScalarVolumePerTimePressureArea.unload(src.getLeftTubularReabsorptionFluidPermeability()));
    if (src.hasRenalBloodFlow())
      dst.setRenalBloodFlow(SEScalarVolumePerTime.unload(src.getRenalBloodFlow()));
    if (src.hasRenalPlasmaFlow())
      dst.setRenalPlasmaFlow(SEScalarVolumePerTime.unload(src.getRenalPlasmaFlow()));
    if (src.hasRenalVascularResistance())
      dst.setRenalVascularResistance(SEScalarFlowResistance.unload(src.getRenalVascularResistance()));
    if (src.hasRightAfferentArterioleResistance())
      dst.setRightAfferentArterioleResistance(SEScalarFlowResistance.unload(src.getRightAfferentArterioleResistance()));
    if (src.hasRightBowmansCapsulesHydrostaticPressure())
      dst.setRightBowmansCapsulesHydrostaticPressure(SEScalarPressure.unload(src.getRightBowmansCapsulesHydrostaticPressure()));
    if (src.hasRightBowmansCapsulesOsmoticPressure())
      dst.setRightEfferentArterioleResistance(SEScalarFlowResistance.unload(src.getRightEfferentArterioleResistance()));
    if (src.hasRightEfferentArterioleResistance())
      dst.setRightBowmansCapsulesHydrostaticPressure(SEScalarPressure.unload(src.getRightBowmansCapsulesHydrostaticPressure()));
    if (src.hasRightGlomerularCapillariesHydrostaticPressure())
      dst.setRightGlomerularCapillariesHydrostaticPressure(SEScalarPressure.unload(src.getRightGlomerularCapillariesHydrostaticPressure()));
    if (src.hasRightGlomerularCapillariesOsmoticPressure())
      dst.setRightGlomerularCapillariesOsmoticPressure(SEScalarPressure.unload(src.getRightGlomerularCapillariesOsmoticPressure()));
    if (src.hasRightGlomerularFiltrationCoefficient())
      dst.setRightGlomerularFiltrationCoefficient(SEScalarVolumePerTimePressure.unload(src.getRightGlomerularFiltrationCoefficient()));
    if (src.hasRightGlomerularFiltrationRate())
      dst.setRightGlomerularFiltrationRate(SEScalarVolumePerTime.unload(src.getRightGlomerularFiltrationRate()));
    if (src.hasRightGlomerularFiltrationSurfaceArea())
      dst.setRightGlomerularFiltrationSurfaceArea(SEScalarArea.unload(src.getRightGlomerularFiltrationSurfaceArea()));
    if (src.hasRightGlomerularFluidPermeability())
      dst.setRightGlomerularFluidPermeability(SEScalarVolumePerTimePressureArea.unload(src.getRightGlomerularFluidPermeability()));
    if (src.hasRightFiltrationFraction())
      dst.setRightFiltrationFraction(SEScalar0To1.unload(src.getRightFiltrationFraction()));
    if (src.hasRightNetFiltrationPressure())
      dst.setRightNetFiltrationPressure(SEScalarPressure.unload(src.getRightNetFiltrationPressure()));
    if (src.hasRightNetReabsorptionPressure())
      dst.setRightNetReabsorptionPressure(SEScalarPressure.unload(src.getRightNetReabsorptionPressure()));
    if (src.hasRightPeritubularCapillariesHydrostaticPressure())
      dst.setRightPeritubularCapillariesHydrostaticPressure(SEScalarPressure.unload(src.getRightPeritubularCapillariesHydrostaticPressure()));
    if (src.hasRightPeritubularCapillariesOsmoticPressure())
      dst.setRightPeritubularCapillariesOsmoticPressure(SEScalarPressure.unload(src.getRightPeritubularCapillariesOsmoticPressure()));
    if (src.hasRightReabsorptionFiltrationCoefficient())
      dst.setRightReabsorptionFiltrationCoefficient(SEScalarVolumePerTimePressure.unload(src.getRightReabsorptionFiltrationCoefficient()));
    if (src.hasRightReabsorptionRate())
      dst.setRightReabsorptionRate(SEScalarVolumePerTime.unload(src.getRightReabsorptionRate()));
    if (src.hasRightTubularOsmoticPressure())
      dst.setRightTubularOsmoticPressure(SEScalarPressure.unload(src.getRightTubularOsmoticPressure()));
    if (src.hasRightTubularHydrostaticPressure())
      dst.setRightTubularHydrostaticPressure(SEScalarPressure.unload(src.getRightTubularHydrostaticPressure()));
    if (src.hasRightTubularReabsorptionFiltrationSurfaceArea())
      dst.setRightTubularReabsorptionFiltrationSurfaceArea(SEScalarArea.unload(src.getRightTubularReabsorptionFiltrationSurfaceArea()));
    if (src.hasRightTubularReabsorptionFluidPermeability())
      dst.setRightTubularReabsorptionFluidPermeability(SEScalarVolumePerTimePressureArea.unload(src.getRightTubularReabsorptionFluidPermeability()));
    if (src.hasUrinationRate())
      dst.setUrinationRate(SEScalarVolumePerTime.unload(src.getUrinationRate()));
    if (src.hasUrineOsmolality())
      dst.setUrineOsmolality(SEScalarOsmolality.unload(src.getUrineOsmolality()));
    if (src.hasUrineOsmolarity())
      dst.setUrineOsmolarity(SEScalarOsmolarity.unload(src.getUrineOsmolarity()));
    if (src.hasUrineProductionRate())
      dst.setUrineProductionRate(SEScalarVolumePerTime.unload(src.getUrineProductionRate()));
    if (src.hasUrineSpecificGravity())
      dst.setUrineSpecificGravity(SEScalar.unload(src.getUrineSpecificGravity()));
    if (src.hasUrineVolume())
      dst.setUrineVolume(SEScalarVolume.unload(src.getUrineVolume()));
    if (src.hasUrineUreaNitrogenConcentration())
      dst.setUrineUreaNitrogenConcentration(SEScalarMassPerVolume.unload(src.getUrineUreaNitrogenConcentration()));
  }

  public boolean hasGlomerularFiltrationRate()
  {
    return glomerularFiltrationRate == null ? false : glomerularFiltrationRate.isValid();
  }
  public SEScalarVolumePerTime getGlomerularFiltrationRate()
  {
    if (glomerularFiltrationRate == null)
      glomerularFiltrationRate = new SEScalarVolumePerTime();
    return glomerularFiltrationRate;
  }

  public boolean hasFiltrationFraction()
  {
    return filtrationFraction == null ? false : filtrationFraction.isValid();
  }
  public SEScalar0To1 getFiltrationFraction()
  {
    if (filtrationFraction == null)
      filtrationFraction = new SEScalar0To1();
    return filtrationFraction;
  }
  
  public boolean hasLeftAfferentArterioleResistance()
  {
    return leftAfferentArterioleResistance == null ? false : leftAfferentArterioleResistance.isValid();
  }
  public SEScalarFlowResistance getLeftAfferentArterioleResistance()
  {
    if (leftAfferentArterioleResistance == null)
      leftAfferentArterioleResistance = new SEScalarFlowResistance();
    return leftAfferentArterioleResistance;
  }

  public boolean hasLeftBowmansCapsulesHydrostaticPressure()
  {
    return leftBowmansCapsulesHydrostaticPressure == null ? false : leftBowmansCapsulesHydrostaticPressure.isValid();
  }
  public SEScalarPressure getLeftBowmansCapsulesHydrostaticPressure()
  {
    if (leftBowmansCapsulesHydrostaticPressure == null)
      leftBowmansCapsulesHydrostaticPressure = new SEScalarPressure();
    return leftBowmansCapsulesHydrostaticPressure;
  }

  public boolean hasLeftBowmansCapsulesOsmoticPressure()
  {
    return leftBowmansCapsulesOsmoticPressure == null ? false : leftBowmansCapsulesOsmoticPressure.isValid();
  }
  public SEScalarPressure getLeftBowmansCapsulesOsmoticPressure()
  {
    if (leftBowmansCapsulesOsmoticPressure == null)
      leftBowmansCapsulesOsmoticPressure = new SEScalarPressure();
    return leftBowmansCapsulesOsmoticPressure;
  }
  
  public boolean hasLeftEfferentArterioleResistance()
  {
    return leftEfferentArterioleResistance == null ? false : leftEfferentArterioleResistance.isValid();
  }
  public SEScalarFlowResistance getLeftEfferentArterioleResistance()
  {
    if (leftEfferentArterioleResistance == null)
      leftEfferentArterioleResistance = new SEScalarFlowResistance();
    return leftEfferentArterioleResistance;
  }

  public boolean hasLeftGlomerularCapillariesHydrostaticPressure()
  {
    return leftGlomerularCapillariesHydrostaticPressure == null ? false : leftGlomerularCapillariesHydrostaticPressure.isValid();
  }
  public SEScalarPressure getLeftGlomerularCapillariesHydrostaticPressure()
  {
    if (leftGlomerularCapillariesHydrostaticPressure == null)
      leftGlomerularCapillariesHydrostaticPressure = new SEScalarPressure();
    return leftGlomerularCapillariesHydrostaticPressure;
  }

  public boolean hasLeftGlomerularCapillariesOsmoticPressure()
  {
    return leftGlomerularCapillariesOsmoticPressure == null ? false : leftGlomerularCapillariesOsmoticPressure.isValid();
  }
  public SEScalarPressure getLeftGlomerularCapillariesOsmoticPressure()
  {
    if (leftGlomerularCapillariesOsmoticPressure == null)
      leftGlomerularCapillariesOsmoticPressure = new SEScalarPressure();
    return leftGlomerularCapillariesOsmoticPressure;
  }

  public boolean hasLeftGlomerularFiltrationCoefficient()
  {
    return leftGlomerularFiltrationCoefficient == null ? false : leftGlomerularFiltrationCoefficient.isValid();
  }
  public SEScalarVolumePerTimePressure getLeftGlomerularFiltrationCoefficient()
  {
    if (leftGlomerularFiltrationCoefficient == null)
      leftGlomerularFiltrationCoefficient = new SEScalarVolumePerTimePressure();
    return leftGlomerularFiltrationCoefficient;
  }

  public boolean hasLeftGlomerularFiltrationRate()
  {
    return leftGlomerularFiltrationRate == null ? false : leftGlomerularFiltrationRate.isValid();
  }
  public SEScalarVolumePerTime getLeftGlomerularFiltrationRate()
  {
    if (leftGlomerularFiltrationRate == null)
      leftGlomerularFiltrationRate = new SEScalarVolumePerTime();
    return leftGlomerularFiltrationRate;
  }

  public boolean hasLeftGlomerularFiltrationSurfaceArea()
  {
    return leftGlomerularFiltrationSurfaceArea == null ? false : leftGlomerularFiltrationSurfaceArea.isValid();
  }
  public SEScalarArea getLeftGlomerularFiltrationSurfaceArea()
  {
    if (leftGlomerularFiltrationSurfaceArea == null)
      leftGlomerularFiltrationSurfaceArea = new SEScalarArea();
    return leftGlomerularFiltrationSurfaceArea;
  }

  public boolean hasLeftGlomerularFluidPermeability()
  {
    return leftGlomerularFluidPermeability == null ? false : leftGlomerularFluidPermeability.isValid();
  }
  public SEScalarVolumePerTimePressureArea getLeftGlomerularFluidPermeability()
  {
    if (leftGlomerularFluidPermeability == null)
      leftGlomerularFluidPermeability = new SEScalarVolumePerTimePressureArea();
    return leftGlomerularFluidPermeability;
  }

  public boolean hasLeftFiltrationFraction()
  {
    return leftFiltrationFraction == null ? false : leftFiltrationFraction.isValid();
  }
  public SEScalar0To1 getLeftFiltrationFraction()
  {
    if (leftFiltrationFraction == null)
      leftFiltrationFraction = new SEScalar0To1();
    return leftFiltrationFraction;
  }

  public boolean hasLeftNetFiltrationPressure()
  {
    return leftNetFiltrationPressure == null ? false : leftNetFiltrationPressure.isValid();
  }
  public SEScalarPressure getLeftNetFiltrationPressure()
  {
    if (leftNetFiltrationPressure == null)
      leftNetFiltrationPressure = new SEScalarPressure();
    return leftNetFiltrationPressure;
  }

  public boolean hasLeftNetReabsorptionPressure()
  {
    return leftNetReabsorptionPressure == null ? false : leftNetReabsorptionPressure.isValid();
  }
  public SEScalarPressure getLeftNetReabsorptionPressure()
  {
    if (leftNetReabsorptionPressure == null)
      leftNetReabsorptionPressure = new SEScalarPressure();
    return leftNetReabsorptionPressure;
  }

  public boolean hasLeftPeritubularCapillariesHydrostaticPressure()
  {
    return leftPeritubularCapillariesHydrostaticPressure == null ? false : leftPeritubularCapillariesHydrostaticPressure.isValid();
  }
  public SEScalarPressure getLeftPeritubularCapillariesHydrostaticPressure()
  {
    if (leftPeritubularCapillariesHydrostaticPressure == null)
      leftPeritubularCapillariesHydrostaticPressure = new SEScalarPressure();
    return leftPeritubularCapillariesHydrostaticPressure;
  }

  public boolean hasLeftPeritubularCapillariesOsmoticPressure()
  {
    return leftPeritubularCapillariesOsmoticPressure == null ? false : leftPeritubularCapillariesOsmoticPressure.isValid();
  }
  public SEScalarPressure getLeftPeritubularCapillariesOsmoticPressure()
  {
    if (leftPeritubularCapillariesOsmoticPressure == null)
      leftPeritubularCapillariesOsmoticPressure = new SEScalarPressure();
    return leftPeritubularCapillariesOsmoticPressure;
  }

  public boolean hasLeftReabsorptionFiltrationCoefficient()
  {
    return leftReabsorptionFiltrationCoefficient == null ? false : leftReabsorptionFiltrationCoefficient.isValid();
  }
  public SEScalarVolumePerTimePressure getLeftReabsorptionFiltrationCoefficient()
  {
    if (leftReabsorptionFiltrationCoefficient == null)
      leftReabsorptionFiltrationCoefficient = new SEScalarVolumePerTimePressure();
    return leftReabsorptionFiltrationCoefficient;
  }

  public boolean hasLeftReabsorptionRate()
  {
    return leftReabsorptionRate == null ? false : leftReabsorptionRate.isValid();
  }
  public SEScalarVolumePerTime getLeftReabsorptionRate()
  {
    if (leftReabsorptionRate == null)
      leftReabsorptionRate = new SEScalarVolumePerTime();
    return leftReabsorptionRate;
  }

  public boolean hasLeftTubularOsmoticPressure()
  {
    return leftTubularOsmoticPressure == null ? false : leftTubularOsmoticPressure.isValid();
  }
  public SEScalarPressure getLeftTubularOsmoticPressure()
  {
    if (leftTubularOsmoticPressure == null)
      leftTubularOsmoticPressure = new SEScalarPressure();
    return leftTubularOsmoticPressure;
  }

  public boolean hasLeftTubularHydrostaticPressure()
  {
    return leftTubularHydrostaticPressure == null ? false : leftTubularHydrostaticPressure.isValid();
  }
  public SEScalarPressure getLeftTubularHydrostaticPressure()
  {
    if (leftTubularHydrostaticPressure == null)
      leftTubularHydrostaticPressure = new SEScalarPressure();
    return leftTubularHydrostaticPressure;
  }

  public boolean hasLeftTubularReabsorptionFiltrationSurfaceArea()
  {
    return leftTubularReabsorptionFiltrationSurfaceArea == null ? false : leftTubularReabsorptionFiltrationSurfaceArea.isValid();
  }
  public SEScalarArea getLeftTubularReabsorptionFiltrationSurfaceArea()
  {
    if (leftTubularReabsorptionFiltrationSurfaceArea == null)
      leftTubularReabsorptionFiltrationSurfaceArea = new SEScalarArea();
    return leftTubularReabsorptionFiltrationSurfaceArea;
  }

  public boolean hasLeftTubularReabsorptionFluidPermeability()
  {
    return leftTubularReabsorptionFluidPermeability == null ? false : leftTubularReabsorptionFluidPermeability.isValid();
  }
  public SEScalarVolumePerTimePressureArea getLeftTubularReabsorptionFluidPermeability()
  {
    if (leftTubularReabsorptionFluidPermeability == null)
      leftTubularReabsorptionFluidPermeability = new SEScalarVolumePerTimePressureArea();
    return leftTubularReabsorptionFluidPermeability;
  }

  public boolean hasRenalBloodFlow()
  {
    return renalBloodFlow == null ? false : renalBloodFlow.isValid();
  }
  public SEScalarVolumePerTime getRenalBloodFlow()
  {
    if (renalBloodFlow == null)
      renalBloodFlow = new SEScalarVolumePerTime();
    return renalBloodFlow;
  }

  public boolean hasRenalPlasmaFlow()
  {
    return renalPlasmaFlow == null ? false : renalPlasmaFlow.isValid();
  }
  public SEScalarVolumePerTime getRenalPlasmaFlow()
  {
    if (renalPlasmaFlow == null)
      renalPlasmaFlow = new SEScalarVolumePerTime();
    return renalPlasmaFlow;
  }

  public boolean hasRenalVascularResistance()
  {
    return renalVascularResistance == null ? false : renalVascularResistance.isValid();
  }
  public SEScalarFlowResistance getRenalVascularResistance()
  {
    if (renalVascularResistance == null)
      renalVascularResistance = new SEScalarFlowResistance();
    return renalVascularResistance;
  }
  
  public boolean hasRightAfferentArterioleResistance()
  {
    return rightAfferentArterioleResistance == null ? false : rightAfferentArterioleResistance.isValid();
  }
  public SEScalarFlowResistance getRightAfferentArterioleResistance()
  {
    if (rightAfferentArterioleResistance == null)
      rightAfferentArterioleResistance = new SEScalarFlowResistance();
    return rightAfferentArterioleResistance;
  }

  public boolean hasRightBowmansCapsulesHydrostaticPressure()
  {
    return rightBowmansCapsulesHydrostaticPressure == null ? false : rightBowmansCapsulesHydrostaticPressure.isValid();
  }
  public SEScalarPressure getRightBowmansCapsulesHydrostaticPressure()
  {
    if (rightBowmansCapsulesHydrostaticPressure == null)
      rightBowmansCapsulesHydrostaticPressure = new SEScalarPressure();
    return rightBowmansCapsulesHydrostaticPressure;
  }

  public boolean hasRightBowmansCapsulesOsmoticPressure()
  {
    return rightBowmansCapsulesOsmoticPressure == null ? false : rightBowmansCapsulesOsmoticPressure.isValid();
  }
  public SEScalarPressure getRightBowmansCapsulesOsmoticPressure()
  {
    if (rightBowmansCapsulesOsmoticPressure == null)
      rightBowmansCapsulesOsmoticPressure = new SEScalarPressure();
    return rightBowmansCapsulesOsmoticPressure;
  }
  
  public boolean hasRightEfferentArterioleResistance()
  {
    return rightEfferentArterioleResistance == null ? false : rightEfferentArterioleResistance.isValid();
  }
  public SEScalarFlowResistance getRightEfferentArterioleResistance()
  {
    if (rightEfferentArterioleResistance == null)
      rightEfferentArterioleResistance = new SEScalarFlowResistance();
    return rightEfferentArterioleResistance;
  }

  public boolean hasRightGlomerularCapillariesHydrostaticPressure()
  {
    return rightGlomerularCapillariesHydrostaticPressure == null ? false : rightGlomerularCapillariesHydrostaticPressure.isValid();
  }
  public SEScalarPressure getRightGlomerularCapillariesHydrostaticPressure()
  {
    if (rightGlomerularCapillariesHydrostaticPressure == null)
      rightGlomerularCapillariesHydrostaticPressure = new SEScalarPressure();
    return rightGlomerularCapillariesHydrostaticPressure;
  }

  public boolean hasRightGlomerularCapillariesOsmoticPressure()
  {
    return rightGlomerularCapillariesOsmoticPressure == null ? false : rightGlomerularCapillariesOsmoticPressure.isValid();
  }
  public SEScalarPressure getRightGlomerularCapillariesOsmoticPressure()
  {
    if (rightGlomerularCapillariesOsmoticPressure == null)
      rightGlomerularCapillariesOsmoticPressure = new SEScalarPressure();
    return rightGlomerularCapillariesOsmoticPressure;
  }

  public boolean hasRightGlomerularFiltrationCoefficient()
  {
    return rightGlomerularFiltrationCoefficient == null ? false : rightGlomerularFiltrationCoefficient.isValid();
  }
  public SEScalarVolumePerTimePressure getRightGlomerularFiltrationCoefficient()
  {
    if (rightGlomerularFiltrationCoefficient == null)
      rightGlomerularFiltrationCoefficient = new SEScalarVolumePerTimePressure();
    return rightGlomerularFiltrationCoefficient;
  }

  public boolean hasRightGlomerularFiltrationRate()
  {
    return rightGlomerularFiltrationRate == null ? false : rightGlomerularFiltrationRate.isValid();
  }
  public SEScalarVolumePerTime getRightGlomerularFiltrationRate()
  {
    if (rightGlomerularFiltrationRate == null)
      rightGlomerularFiltrationRate = new SEScalarVolumePerTime();
    return rightGlomerularFiltrationRate;
  }

  public boolean hasRightGlomerularFiltrationSurfaceArea()
  {
    return rightGlomerularFiltrationSurfaceArea == null ? false : rightGlomerularFiltrationSurfaceArea.isValid();
  }
  public SEScalarArea getRightGlomerularFiltrationSurfaceArea()
  {
    if (rightGlomerularFiltrationSurfaceArea == null)
      rightGlomerularFiltrationSurfaceArea = new SEScalarArea();
    return rightGlomerularFiltrationSurfaceArea;
  }

  public boolean hasRightGlomerularFluidPermeability()
  {
    return rightGlomerularFluidPermeability == null ? false : rightGlomerularFluidPermeability.isValid();
  }
  public SEScalarVolumePerTimePressureArea getRightGlomerularFluidPermeability()
  {
    if (rightGlomerularFluidPermeability == null)
      rightGlomerularFluidPermeability = new SEScalarVolumePerTimePressureArea();
    return rightGlomerularFluidPermeability;
  }

  public boolean hasRightFiltrationFraction()
  {
    return rightFiltrationFraction == null ? false : rightFiltrationFraction.isValid();
  }
  public SEScalar0To1 getRightFiltrationFraction()
  {
    if (rightFiltrationFraction == null)
      rightFiltrationFraction = new SEScalar0To1();
    return rightFiltrationFraction;
  }

  public boolean hasRightNetFiltrationPressure()
  {
    return rightNetFiltrationPressure == null ? false : rightNetFiltrationPressure.isValid();
  }
  public SEScalarPressure getRightNetFiltrationPressure()
  {
    if (rightNetFiltrationPressure == null)
      rightNetFiltrationPressure = new SEScalarPressure();
    return rightNetFiltrationPressure;
  }

  public boolean hasRightNetReabsorptionPressure()
  {
    return rightNetReabsorptionPressure == null ? false : rightNetReabsorptionPressure.isValid();
  }
  public SEScalarPressure getRightNetReabsorptionPressure()
  {
    if (rightNetReabsorptionPressure == null)
      rightNetReabsorptionPressure = new SEScalarPressure();
    return rightNetReabsorptionPressure;
  }

  public boolean hasRightPeritubularCapillariesHydrostaticPressure()
  {
    return rightPeritubularCapillariesHydrostaticPressure == null ? false : rightPeritubularCapillariesHydrostaticPressure.isValid();
  }
  public SEScalarPressure getRightPeritubularCapillariesHydrostaticPressure()
  {
    if (rightPeritubularCapillariesHydrostaticPressure == null)
      rightPeritubularCapillariesHydrostaticPressure = new SEScalarPressure();
    return rightPeritubularCapillariesHydrostaticPressure;
  }

  public boolean hasRightPeritubularCapillariesOsmoticPressure()
  {
    return rightPeritubularCapillariesOsmoticPressure == null ? false : rightPeritubularCapillariesOsmoticPressure.isValid();
  }
  public SEScalarPressure getRightPeritubularCapillariesOsmoticPressure()
  {
    if (rightPeritubularCapillariesOsmoticPressure == null)
      rightPeritubularCapillariesOsmoticPressure = new SEScalarPressure();
    return rightPeritubularCapillariesOsmoticPressure;
  }

  public boolean hasRightReabsorptionFiltrationCoefficient()
  {
    return rightReabsorptionFiltrationCoefficient == null ? false : rightReabsorptionFiltrationCoefficient.isValid();
  }
  public SEScalarVolumePerTimePressure getRightReabsorptionFiltrationCoefficient()
  {
    if (rightReabsorptionFiltrationCoefficient == null)
      rightReabsorptionFiltrationCoefficient = new SEScalarVolumePerTimePressure();
    return rightReabsorptionFiltrationCoefficient;
  }

  public boolean hasRightReabsorptionRate()
  {
    return rightReabsorptionRate == null ? false : rightReabsorptionRate.isValid();
  }
  public SEScalarVolumePerTime getRightReabsorptionRate()
  {
    if (rightReabsorptionRate == null)
      rightReabsorptionRate = new SEScalarVolumePerTime();
    return rightReabsorptionRate;
  }

  public boolean hasRightTubularOsmoticPressure()
  {
    return rightTubularOsmoticPressure == null ? false : rightTubularOsmoticPressure.isValid();
  }
  public SEScalarPressure getRightTubularOsmoticPressure()
  {
    if (rightTubularOsmoticPressure == null)
      rightTubularOsmoticPressure = new SEScalarPressure();
    return rightTubularOsmoticPressure;
  }

  public boolean hasRightTubularHydrostaticPressure()
  {
    return rightTubularHydrostaticPressure == null ? false : rightTubularHydrostaticPressure.isValid();
  }
  public SEScalarPressure getRightTubularHydrostaticPressure()
  {
    if (rightTubularHydrostaticPressure == null)
      rightTubularHydrostaticPressure = new SEScalarPressure();
    return rightTubularHydrostaticPressure;
  }

  public boolean hasRightTubularReabsorptionFiltrationSurfaceArea()
  {
    return rightTubularReabsorptionFiltrationSurfaceArea == null ? false : rightTubularReabsorptionFiltrationSurfaceArea.isValid();
  }
  public SEScalarArea getRightTubularReabsorptionFiltrationSurfaceArea()
  {
    if (rightTubularReabsorptionFiltrationSurfaceArea == null)
      rightTubularReabsorptionFiltrationSurfaceArea = new SEScalarArea();
    return rightTubularReabsorptionFiltrationSurfaceArea;
  }

  public boolean hasRightTubularReabsorptionFluidPermeability()
  {
    return rightTubularReabsorptionFluidPermeability == null ? false : rightTubularReabsorptionFluidPermeability.isValid();
  }
  public SEScalarVolumePerTimePressureArea getRightTubularReabsorptionFluidPermeability()
  {
    if (rightTubularReabsorptionFluidPermeability == null)
      rightTubularReabsorptionFluidPermeability = new SEScalarVolumePerTimePressureArea();
    return rightTubularReabsorptionFluidPermeability;
  }

  public boolean hasUrinationRate()
  {
    return urinationRate == null ? false : urinationRate.isValid();
  }
  public SEScalarVolumePerTime getUrinationRate()
  {
    if (urinationRate == null)
      urinationRate = new SEScalarVolumePerTime();
    return urinationRate;
  }

  public boolean hasUrineOsmolality()
  {
    return urineOsmolality == null ? false : urineOsmolality.isValid();
  }
  public SEScalarOsmolality getUrineOsmolality()
  {
    if (urineOsmolality == null)
      urineOsmolality = new SEScalarOsmolality();
    return urineOsmolality;
  }

  public boolean hasUrineOsmolarity()
  {
    return urineOsmolarity == null ? false : urineOsmolarity.isValid();
  }
  public SEScalarOsmolarity getUrineOsmolarity()
  {
    if (urineOsmolarity == null)
      urineOsmolarity = new SEScalarOsmolarity();
    return urineOsmolarity;
  }

  public boolean hasUrineProductionRate()
  {
    return urineProductionRate == null ? false : urineProductionRate.isValid();
  }
  public SEScalarVolumePerTime getUrineProductionRate()
  {
    if (urineProductionRate == null)
      urineProductionRate = new SEScalarVolumePerTime();
    return urineProductionRate;
  }

  public boolean hasUrineSpecificGravity()
  {
    return urineSpecificGravity == null ? false : urineSpecificGravity.isValid();
  }
  public SEScalar getUrineSpecificGravity()
  {
    if (urineSpecificGravity == null)
      urineSpecificGravity = new SEScalar();
    return urineSpecificGravity;
  }

  public boolean hasUrineVolume()
  {
    return urineVolume == null ? false : urineVolume.isValid();
  }
  public SEScalarVolume getUrineVolume()
  {
    if (urineVolume == null)
      urineVolume = new SEScalarVolume();
    return urineVolume;
  }

  public boolean hasUrineUreaNitrogenConcentration()
  {
    return urineUreaNitrogenConcentration == null ? false : urineUreaNitrogenConcentration.isValid();
  }
  public SEScalarMassPerVolume getUrineUreaNitrogenConcentration()
  {
    if (urineUreaNitrogenConcentration == null)
      urineUreaNitrogenConcentration = new SEScalarMassPerVolume();
    return urineUreaNitrogenConcentration;
  }
}
