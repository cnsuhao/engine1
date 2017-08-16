/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "system/physiology/SERenalSystem.h"
#include "substance/SESubstanceManager.h"
#include "properties/SEScalarArea.h"
#include "properties/SEScalar0To1.h"
#include "properties/SEScalarVolumePerTimePressure.h"
#include "properties/SEScalarVolumePerTimeArea.h"
#include "properties/SEScalarVolumePerTimePressureArea.h"
#include "properties/SEScalarOsmolality.h"
#include "properties/SEScalarOsmolarity.h"
#include "properties/SEScalarPressure.h"
#include "properties/SEScalarVolume.h"
#include "properties/SEScalarVolumePerTime.h"
#include "properties/SEScalarMassPerTime.h"
#include "properties/SEScalarMassPerVolume.h"
#include "properties/SEScalarAmountPerVolume.h"
#include "properties/SEScalarFlowResistance.h"

SERenalSystem::SERenalSystem(Logger* logger) : SESystem(logger)
{
  m_GlomerularFiltrationRate = nullptr;
  m_FiltrationFraction = nullptr;

  m_LeftAfferentArterioleResistance = nullptr;
  m_LeftBowmansCapsulesHydrostaticPressure = nullptr;
  m_LeftBowmansCapsulesOsmoticPressure = nullptr;
  m_LeftEfferentArterioleResistance = nullptr;
  m_LeftGlomerularCapillariesHydrostaticPressure = nullptr;
  m_LeftGlomerularCapillariesOsmoticPressure = nullptr;
  m_LeftGlomerularFiltrationCoefficient = nullptr;
  m_LeftGlomerularFiltrationRate = nullptr;
  m_LeftGlomerularFiltrationSurfaceArea = nullptr;
  m_LeftGlomerularFluidPermeability = nullptr;
  m_LeftFiltrationFraction = nullptr;
  m_LeftNetFiltrationPressure = nullptr;
  m_LeftNetReabsorptionPressure = nullptr;
  m_LeftPeritubularCapillariesHydrostaticPressure = nullptr;
  m_LeftPeritubularCapillariesOsmoticPressure = nullptr;
  m_LeftReabsorptionFiltrationCoefficient = nullptr;
  m_LeftReabsorptionRate = nullptr;
  m_LeftTubularReabsorptionFiltrationSurfaceArea = nullptr;
  m_LeftTubularReabsorptionFluidPermeability = nullptr;
  m_LeftTubularHydrostaticPressure = nullptr;
  m_LeftTubularOsmoticPressure = nullptr;

  m_RenalBloodFlow = nullptr;
  m_RenalPlasmaFlow = nullptr;
  m_RenalVascularResistance = nullptr;

  m_RightAfferentArterioleResistance = nullptr;
  m_RightBowmansCapsulesHydrostaticPressure = nullptr;
  m_RightBowmansCapsulesOsmoticPressure = nullptr;
  m_RightEfferentArterioleResistance = nullptr;
  m_RightGlomerularCapillariesHydrostaticPressure = nullptr;
  m_RightGlomerularCapillariesOsmoticPressure = nullptr;
  m_RightGlomerularFiltrationCoefficient = nullptr;
  m_RightGlomerularFiltrationRate = nullptr;
  m_RightGlomerularFiltrationSurfaceArea = nullptr;
  m_RightGlomerularFluidPermeability = nullptr;
  m_RightFiltrationFraction = nullptr;
  m_RightNetFiltrationPressure = nullptr;
  m_RightNetReabsorptionPressure = nullptr;
  m_RightPeritubularCapillariesHydrostaticPressure = nullptr;
  m_RightPeritubularCapillariesOsmoticPressure = nullptr;
  m_RightReabsorptionFiltrationCoefficient = nullptr;
  m_RightReabsorptionRate = nullptr;
  m_RightTubularReabsorptionFiltrationSurfaceArea = nullptr;
  m_RightTubularReabsorptionFluidPermeability = nullptr;
  m_RightTubularHydrostaticPressure = nullptr;
  m_RightTubularOsmoticPressure = nullptr;
  
  m_UrinationRate = nullptr;
  m_UrineOsmolality = nullptr;
  m_UrineOsmolarity = nullptr;
  m_UrineProductionRate = nullptr;
  m_UrineSpecificGravity = nullptr;
  m_UrineVolume = nullptr;
  m_UrineUreaNitrogenConcentration = nullptr;
  
}

SERenalSystem::~SERenalSystem()
{
  Clear();  
}

void SERenalSystem::Clear()
{
  SESystem::Clear();

  SAFE_DELETE(m_GlomerularFiltrationRate);
  SAFE_DELETE(m_FiltrationFraction);

  SAFE_DELETE(m_LeftAfferentArterioleResistance);
  SAFE_DELETE(m_LeftBowmansCapsulesHydrostaticPressure);
  SAFE_DELETE(m_LeftBowmansCapsulesOsmoticPressure);
  SAFE_DELETE(m_LeftEfferentArterioleResistance);
  SAFE_DELETE(m_LeftGlomerularCapillariesHydrostaticPressure);
  SAFE_DELETE(m_LeftGlomerularCapillariesOsmoticPressure);
  SAFE_DELETE(m_LeftGlomerularFiltrationCoefficient);
  SAFE_DELETE(m_LeftGlomerularFiltrationRate);
  SAFE_DELETE(m_LeftGlomerularFiltrationSurfaceArea);
  SAFE_DELETE(m_LeftGlomerularFluidPermeability);
  SAFE_DELETE(m_LeftFiltrationFraction);
  SAFE_DELETE(m_LeftNetFiltrationPressure);
  SAFE_DELETE(m_LeftNetReabsorptionPressure);
  SAFE_DELETE(m_LeftPeritubularCapillariesHydrostaticPressure);
  SAFE_DELETE(m_LeftPeritubularCapillariesOsmoticPressure);
  SAFE_DELETE(m_LeftReabsorptionFiltrationCoefficient);
  SAFE_DELETE(m_LeftReabsorptionRate);
  SAFE_DELETE(m_LeftTubularReabsorptionFiltrationSurfaceArea);
  SAFE_DELETE(m_LeftTubularReabsorptionFluidPermeability);
  SAFE_DELETE(m_LeftTubularHydrostaticPressure);
  SAFE_DELETE(m_LeftTubularOsmoticPressure);

  SAFE_DELETE(m_RenalBloodFlow);
  SAFE_DELETE(m_RenalPlasmaFlow);
  SAFE_DELETE(m_RenalVascularResistance);

  SAFE_DELETE(m_RightAfferentArterioleResistance);
  SAFE_DELETE(m_RightBowmansCapsulesHydrostaticPressure);
  SAFE_DELETE(m_RightBowmansCapsulesOsmoticPressure);
  SAFE_DELETE(m_RightEfferentArterioleResistance);
  SAFE_DELETE(m_RightGlomerularCapillariesHydrostaticPressure);
  SAFE_DELETE(m_RightGlomerularCapillariesOsmoticPressure);
  SAFE_DELETE(m_RightGlomerularFiltrationCoefficient);
  SAFE_DELETE(m_RightGlomerularFiltrationRate);
  SAFE_DELETE(m_RightGlomerularFiltrationSurfaceArea);
  SAFE_DELETE(m_RightGlomerularFluidPermeability);
  SAFE_DELETE(m_RightFiltrationFraction);
  SAFE_DELETE(m_RightNetFiltrationPressure);
  SAFE_DELETE(m_RightNetReabsorptionPressure);
  SAFE_DELETE(m_RightPeritubularCapillariesHydrostaticPressure);
  SAFE_DELETE(m_RightPeritubularCapillariesOsmoticPressure);
  SAFE_DELETE(m_RightReabsorptionFiltrationCoefficient);
  SAFE_DELETE(m_RightReabsorptionRate);
  SAFE_DELETE(m_RightTubularReabsorptionFiltrationSurfaceArea);
  SAFE_DELETE(m_RightTubularReabsorptionFluidPermeability);
  SAFE_DELETE(m_RightTubularHydrostaticPressure);
  SAFE_DELETE(m_RightTubularOsmoticPressure);

  SAFE_DELETE(m_UrinationRate);
  SAFE_DELETE(m_UrineOsmolality);
  SAFE_DELETE(m_UrineOsmolarity);
  SAFE_DELETE(m_UrineProductionRate);
  SAFE_DELETE(m_UrineSpecificGravity);
  SAFE_DELETE(m_UrineVolume);
  SAFE_DELETE(m_UrineUreaNitrogenConcentration);
}

const SEScalar* SERenalSystem::GetScalar(const std::string& name)
{
  if (name.compare("GlomerularFiltrationRate") == 0)
    return &GetGlomerularFiltrationRate();
  if (name.compare("FiltrationFraction") == 0)
    return &GetFiltrationFraction();

  if (name.compare("LeftAfferentArterioleResistance") == 0)
    return &GetLeftAfferentArterioleResistance();
  if (name.compare("LeftBowmansCapsulesHydrostaticPressure") == 0)
    return &GetLeftBowmansCapsulesHydrostaticPressure();
  if (name.compare("LeftBowmansCapsulesOsmoticPressure") == 0)
    return &GetLeftBowmansCapsulesOsmoticPressure();
  if (name.compare("LeftEfferentArterioleResistance") == 0)
    return &GetLeftEfferentArterioleResistance();
  if (name.compare("LeftGlomerularCapillariesHydrostaticPressure") == 0)
    return &GetLeftGlomerularCapillariesHydrostaticPressure();
  if (name.compare("LeftGlomerularCapillariesOsmoticPressure") == 0)
    return &GetLeftGlomerularCapillariesOsmoticPressure();
  if (name.compare("LeftGlomerularFiltrationCoefficient") == 0)
    return &GetLeftGlomerularFiltrationCoefficient();
  if (name.compare("LeftGlomerularFiltrationRate") == 0)
    return &GetLeftGlomerularFiltrationRate();
  if (name.compare("LeftGlomerularFiltrationSurfaceArea") == 0)
    return &GetLeftGlomerularFiltrationSurfaceArea();
  if (name.compare("LeftGlomerularFluidPermeability") == 0)
    return &GetLeftGlomerularFluidPermeability();
  if (name.compare("LeftFiltrationFraction") == 0)
    return &GetLeftFiltrationFraction();
  if (name.compare("LeftNetFiltrationPressure") == 0)
    return &GetLeftNetFiltrationPressure();
  if (name.compare("LeftNetReabsorptionPressure") == 0)
    return &GetLeftNetReabsorptionPressure();
  if (name.compare("LeftPeritubularCapillariesHydrostaticPressure") == 0)
    return &GetLeftPeritubularCapillariesHydrostaticPressure();
  if (name.compare("LeftPeritubularCapillariesOsmoticPressure") == 0)
    return &GetLeftPeritubularCapillariesOsmoticPressure();
  if (name.compare("LeftReabsorptionFiltrationCoefficient") == 0)
    return &GetLeftReabsorptionFiltrationCoefficient();
  if (name.compare("LeftReabsorptionRate") == 0)
    return &GetLeftReabsorptionRate();
  if (name.compare("LeftTubularReabsorptionFiltrationSurfaceArea") == 0)
    return &GetLeftTubularReabsorptionFiltrationSurfaceArea();
  if (name.compare("LeftTubularReabsorptionFluidPermeability") == 0)
    return &GetLeftTubularReabsorptionFluidPermeability();
  if (name.compare("LeftTubularHydrostaticPressure") == 0)
    return &GetLeftTubularHydrostaticPressure();
  if (name.compare("LeftTubularOsmoticPressure") == 0)
    return &GetLeftTubularOsmoticPressure();
  
  if (name.compare("RenalBloodFlow") == 0)
    return &GetRenalBloodFlow();
  if (name.compare("RenalPlasmaFlow") == 0)
    return &GetRenalPlasmaFlow();
  if (name.compare("RenalVascularResistance") == 0)
    return &GetRenalVascularResistance();

  if (name.compare("RightAfferentArterioleResistance") == 0)
    return &GetRightAfferentArterioleResistance();
  if (name.compare("RightBowmansCapsulesHydrostaticPressure") == 0)
    return &GetRightBowmansCapsulesHydrostaticPressure();
  if (name.compare("RightBowmansCapsulesOsmoticPressure") == 0)
    return &GetRightBowmansCapsulesOsmoticPressure();
  if (name.compare("RightEfferentArterioleResistance") == 0)
    return &GetRightEfferentArterioleResistance();
  if (name.compare("RightGlomerularCapillariesHydrostaticPressure") == 0)
    return &GetRightGlomerularCapillariesHydrostaticPressure();
  if (name.compare("RightGlomerularCapillariesOsmoticPressure") == 0)
    return &GetRightGlomerularCapillariesOsmoticPressure();
  if (name.compare("RightGlomerularFiltrationCoefficient") == 0)
    return &GetRightGlomerularFiltrationCoefficient();
  if (name.compare("RightGlomerularFiltrationRate") == 0)
    return &GetRightGlomerularFiltrationRate();
  if (name.compare("RightGlomerularFiltrationSurfaceArea") == 0)
    return &GetRightGlomerularFiltrationSurfaceArea();
  if (name.compare("RightGlomerularFluidPermeability") == 0)
    return &GetRightGlomerularFluidPermeability();
  if (name.compare("RightFiltrationFraction") == 0)
    return &GetRightFiltrationFraction();
  if (name.compare("RightNetFiltrationPressure") == 0)
    return &GetRightNetFiltrationPressure();
  if (name.compare("RightNetReabsorptionPressure") == 0)
    return &GetRightNetReabsorptionPressure();
  if (name.compare("RightPeritubularCapillariesHydrostaticPressure") == 0)
    return &GetRightPeritubularCapillariesHydrostaticPressure();
  if (name.compare("RightPeritubularCapillariesOsmoticPressure") == 0)
    return &GetRightPeritubularCapillariesOsmoticPressure();
  if (name.compare("RightReabsorptionFiltrationCoefficient") == 0)
    return &GetRightReabsorptionFiltrationCoefficient();
  if (name.compare("RightReabsorptionRate") == 0)
    return &GetRightReabsorptionRate();
  if (name.compare("RightTubularReabsorptionFiltrationSurfaceArea") == 0)
    return &GetRightTubularReabsorptionFiltrationSurfaceArea();
  if (name.compare("RightTubularReabsorptionFluidPermeability") == 0)
    return &GetRightTubularReabsorptionFluidPermeability();
  if (name.compare("RightTubularHydrostaticPressure") == 0)
    return &GetRightTubularHydrostaticPressure();
  if (name.compare("RightTubularOsmoticPressure") == 0)
    return &GetRightTubularOsmoticPressure();
  
  if (name.compare("UrinationRate") == 0)
    return &GetUrinationRate();
  if (name.compare("UrineOsmolality") == 0)
    return &GetUrineOsmolality();
  if (name.compare("UrineOsmolarity") == 0)
    return &GetUrineOsmolarity();
  if (name.compare("UrineProductionRate") == 0)
    return &GetUrineProductionRate();
  if (name.compare("UrineSpecificGravity") == 0)
    return &GetUrineSpecificGravity();
  if (name.compare("UrineVolume") == 0)
    return &GetUrineVolume();
  if (name.compare("UrineUreaNitrogenConcentration") == 0)
    return &GetUrineUreaNitrogenConcentration();
  
  return nullptr;
}

void SERenalSystem::Load(const cdm::RenalSystemData& src, SERenalSystem& dst)
{
  SERenalSystem::Serialize(src, dst);
}
void SERenalSystem::Serialize(const cdm::RenalSystemData& src, SERenalSystem& dst)
{
  dst.Clear();
  if (src.has_glomerularfiltrationrate())
    SEScalarVolumePerTime::Load(src.glomerularfiltrationrate(), dst.GetGlomerularFiltrationRate());
  if (src.has_filtrationfraction())
    SEScalar0To1::Load(src.filtrationfraction(), dst.GetFiltrationFraction());

  if (src.has_leftafferentarterioleresistance())
    SEScalarFlowResistance::Load(src.leftafferentarterioleresistance(), dst.GetLeftAfferentArterioleResistance());
  if (src.has_leftbowmanscapsuleshydrostaticpressure())
    SEScalarPressure::Load(src.leftbowmanscapsuleshydrostaticpressure(), dst.GetLeftBowmansCapsulesHydrostaticPressure());
  if (src.has_leftbowmanscapsulesosmoticpressure())
    SEScalarPressure::Load(src.leftbowmanscapsulesosmoticpressure(), dst.GetLeftBowmansCapsulesOsmoticPressure());
  if (src.has_leftefferentarterioleresistance())
    SEScalarFlowResistance::Load(src.leftefferentarterioleresistance(), dst.GetLeftEfferentArterioleResistance());
  if (src.has_leftglomerularcapillarieshydrostaticpressure())
    SEScalarPressure::Load(src.leftglomerularcapillarieshydrostaticpressure(), dst.GetLeftGlomerularCapillariesHydrostaticPressure());
  if (src.has_leftglomerularcapillariesosmoticpressure())
    SEScalarPressure::Load(src.leftglomerularcapillariesosmoticpressure(), dst.GetLeftGlomerularCapillariesOsmoticPressure());
  if (src.has_leftglomerularfiltrationcoefficient())
    SEScalarVolumePerTimePressure::Load(src.leftglomerularfiltrationcoefficient(), dst.GetLeftGlomerularFiltrationCoefficient());
  if (src.has_leftglomerularfiltrationrate())
    SEScalarVolumePerTime::Load(src.leftglomerularfiltrationrate(), dst.GetLeftGlomerularFiltrationRate());
  if (src.has_leftglomerularfiltrationsurfacearea())
    SEScalarArea::Load(src.leftglomerularfiltrationsurfacearea(), dst.GetLeftGlomerularFiltrationSurfaceArea());
  if (src.has_leftglomerularfluidpermeability())
    SEScalarVolumePerTimePressureArea::Load(src.leftglomerularfluidpermeability(), dst.GetLeftGlomerularFluidPermeability());
  if (src.has_leftfiltrationfraction())
    SEScalar0To1::Load(src.leftfiltrationfraction(), dst.GetLeftFiltrationFraction());
  if (src.has_leftnetfiltrationpressure())
    SEScalarPressure::Load(src.leftnetfiltrationpressure(), dst.GetLeftNetFiltrationPressure());
  if (src.has_leftnetreabsorptionpressure())
    SEScalarPressure::Load(src.leftnetreabsorptionpressure(), dst.GetLeftNetReabsorptionPressure());
  if (src.has_leftperitubularcapillarieshydrostaticpressure())
    SEScalarPressure::Load(src.leftperitubularcapillarieshydrostaticpressure(), dst.GetLeftPeritubularCapillariesHydrostaticPressure());
  if (src.has_leftperitubularcapillariesosmoticpressure())
    SEScalarPressure::Load(src.leftperitubularcapillariesosmoticpressure(), dst.GetLeftPeritubularCapillariesOsmoticPressure());
  if (src.has_leftreabsorptionfiltrationcoefficient())
    SEScalarVolumePerTimePressure::Load(src.leftreabsorptionfiltrationcoefficient(), dst.GetLeftReabsorptionFiltrationCoefficient());
  if (src.has_leftreabsorptionrate())
    SEScalarVolumePerTime::Load(src.leftreabsorptionrate(), dst.GetLeftReabsorptionRate());
  if (src.has_lefttubularreabsorptionfiltrationsurfacearea())
    SEScalarArea::Load(src.lefttubularreabsorptionfiltrationsurfacearea(), dst.GetLeftTubularReabsorptionFiltrationSurfaceArea());
  if (src.has_lefttubularreabsorptionfluidpermeability())
    SEScalarVolumePerTimePressureArea::Load(src.lefttubularreabsorptionfluidpermeability(), dst.GetLeftTubularReabsorptionFluidPermeability());
  if (src.has_lefttubularhydrostaticpressure())
    SEScalarPressure::Load(src.lefttubularhydrostaticpressure(), dst.GetLeftTubularHydrostaticPressure());
  if (src.has_lefttubularosmoticpressure())
    SEScalarPressure::Load(src.lefttubularosmoticpressure(), dst.GetLeftTubularOsmoticPressure());

  if (src.has_renalbloodflow())
    SEScalarVolumePerTime::Load(src.renalbloodflow(), dst.GetRenalBloodFlow());
  if (src.has_renalplasmaflow())
    SEScalarVolumePerTime::Load(src.renalplasmaflow(), dst.GetRenalPlasmaFlow());
  if (src.has_renalvascularresistance())
    SEScalarFlowResistance::Load(src.renalvascularresistance(), dst.GetRenalVascularResistance());

  if (src.has_rightafferentarterioleresistance())
    SEScalarFlowResistance::Load(src.rightafferentarterioleresistance(), dst.GetRightAfferentArterioleResistance());
  if (src.has_rightbowmanscapsuleshydrostaticpressure())
    SEScalarPressure::Load(src.rightbowmanscapsuleshydrostaticpressure(), dst.GetRightBowmansCapsulesHydrostaticPressure());
  if (src.has_rightbowmanscapsulesosmoticpressure())
    SEScalarPressure::Load(src.rightbowmanscapsulesosmoticpressure(), dst.GetRightBowmansCapsulesOsmoticPressure());
  if (src.has_rightefferentarterioleresistance())
    SEScalarFlowResistance::Load(src.rightefferentarterioleresistance(), dst.GetRightEfferentArterioleResistance());
  if (src.has_rightglomerularcapillarieshydrostaticpressure())
    SEScalarPressure::Load(src.rightglomerularcapillarieshydrostaticpressure(), dst.GetRightGlomerularCapillariesHydrostaticPressure());
  if (src.has_rightglomerularcapillariesosmoticpressure())
    SEScalarPressure::Load(src.rightglomerularcapillariesosmoticpressure(), dst.GetRightGlomerularCapillariesOsmoticPressure());
  if (src.has_rightglomerularfiltrationcoefficient())
    SEScalarVolumePerTimePressure::Load(src.rightglomerularfiltrationcoefficient(), dst.GetRightGlomerularFiltrationCoefficient());
  if (src.has_rightglomerularfiltrationrate())
    SEScalarVolumePerTime::Load(src.rightglomerularfiltrationrate(), dst.GetRightGlomerularFiltrationRate());
  if (src.has_rightglomerularfiltrationsurfacearea())
    SEScalarArea::Load(src.rightglomerularfiltrationsurfacearea(), dst.GetRightGlomerularFiltrationSurfaceArea());
  if (src.has_rightglomerularfluidpermeability())
    SEScalarVolumePerTimePressureArea::Load(src.rightglomerularfluidpermeability(), dst.GetRightGlomerularFluidPermeability());
  if (src.has_rightfiltrationfraction())
    SEScalar0To1::Load(src.rightfiltrationfraction(), dst.GetRightFiltrationFraction());
  if (src.has_rightnetfiltrationpressure())
    SEScalarPressure::Load(src.rightnetfiltrationpressure(), dst.GetRightNetFiltrationPressure());
  if (src.has_rightnetreabsorptionpressure())
    SEScalarPressure::Load(src.rightnetreabsorptionpressure(), dst.GetRightNetReabsorptionPressure());
  if (src.has_rightperitubularcapillarieshydrostaticpressure())
    SEScalarPressure::Load(src.rightperitubularcapillarieshydrostaticpressure(), dst.GetRightPeritubularCapillariesHydrostaticPressure());
  if (src.has_rightperitubularcapillariesosmoticpressure())
    SEScalarPressure::Load(src.rightperitubularcapillariesosmoticpressure(), dst.GetRightPeritubularCapillariesOsmoticPressure());
  if (src.has_rightreabsorptionfiltrationcoefficient())
    SEScalarVolumePerTimePressure::Load(src.rightreabsorptionfiltrationcoefficient(), dst.GetRightReabsorptionFiltrationCoefficient());
  if (src.has_rightreabsorptionrate())
    SEScalarVolumePerTime::Load(src.rightreabsorptionrate(), dst.GetRightReabsorptionRate());
  if (src.has_righttubularreabsorptionfiltrationsurfacearea())
    SEScalarArea::Load(src.righttubularreabsorptionfiltrationsurfacearea(), dst.GetRightTubularReabsorptionFiltrationSurfaceArea());
  if (src.has_righttubularreabsorptionfluidpermeability())
    SEScalarVolumePerTimePressureArea::Load(src.righttubularreabsorptionfluidpermeability(), dst.GetRightTubularReabsorptionFluidPermeability());
  if (src.has_righttubularhydrostaticpressure())
    SEScalarPressure::Load(src.righttubularhydrostaticpressure(), dst.GetRightTubularHydrostaticPressure());
  if (src.has_righttubularosmoticpressure())
    SEScalarPressure::Load(src.righttubularosmoticpressure(), dst.GetRightTubularOsmoticPressure());

  if (src.has_urinationrate())
    SEScalarVolumePerTime::Load(src.urinationrate(), dst.GetUrinationRate());
  if (src.has_urineosmolality())
    SEScalarOsmolality::Load(src.urineosmolality(), dst.GetUrineOsmolality());
  if (src.has_urineosmolarity())
    SEScalarOsmolarity::Load(src.urineosmolarity(), dst.GetUrineOsmolarity());
  if (src.has_urineproductionrate())
    SEScalarVolumePerTime::Load(src.urineproductionrate(), dst.GetUrineProductionRate());
  if (src.has_urinespecificgravity())
    SEScalar::Load(src.urinespecificgravity(), dst.GetUrineSpecificGravity());
  if (src.has_urinevolume())
    SEScalarVolume::Load(src.urinevolume(), dst.GetUrineVolume());
  if (src.has_urineureanitrogenconcentration())
    SEScalarMassPerVolume::Load(src.urineureanitrogenconcentration(), dst.GetUrineUreaNitrogenConcentration());
}

cdm::RenalSystemData* SERenalSystem::Unload(const SERenalSystem& src)
{
  cdm::RenalSystemData* dst = new cdm::RenalSystemData();
  SERenalSystem::Serialize(src, *dst);
  return dst;
}
void SERenalSystem::Serialize(const SERenalSystem& src, cdm::RenalSystemData& dst)
{
  if (src.HasGlomerularFiltrationRate())
    dst.set_allocated_glomerularfiltrationrate(SEScalarVolumePerTime::Unload(*src.m_GlomerularFiltrationRate));
  if (src.HasFiltrationFraction())
    dst.set_allocated_filtrationfraction(SEScalar0To1::Unload(*src.m_FiltrationFraction));

  if (src.HasLeftAfferentArterioleResistance())
    dst.set_allocated_leftafferentarterioleresistance(SEScalarFlowResistance::Unload(*src.m_LeftAfferentArterioleResistance));
  if (src.HasLeftBowmansCapsulesHydrostaticPressure())
    dst.set_allocated_leftbowmanscapsuleshydrostaticpressure(SEScalarPressure::Unload(*src.m_LeftBowmansCapsulesHydrostaticPressure));
  if (src.HasLeftBowmansCapsulesOsmoticPressure())
    dst.set_allocated_leftbowmanscapsulesosmoticpressure(SEScalarPressure::Unload(*src.m_LeftBowmansCapsulesOsmoticPressure));
  if (src.HasLeftEfferentArterioleResistance())
    dst.set_allocated_leftefferentarterioleresistance(SEScalarFlowResistance::Unload(*src.m_LeftEfferentArterioleResistance));
  if (src.HasLeftGlomerularCapillariesHydrostaticPressure())
    dst.set_allocated_leftglomerularcapillarieshydrostaticpressure(SEScalarPressure::Unload(*src.m_LeftGlomerularCapillariesHydrostaticPressure));
  if (src.HasLeftGlomerularCapillariesOsmoticPressure())
    dst.set_allocated_leftglomerularcapillariesosmoticpressure(SEScalarPressure::Unload(*src.m_LeftGlomerularCapillariesOsmoticPressure));
  if (src.HasLeftGlomerularFiltrationCoefficient())
    dst.set_allocated_leftglomerularfiltrationcoefficient(SEScalarVolumePerTimePressure::Unload(*src.m_LeftGlomerularFiltrationCoefficient));
  if (src.HasLeftGlomerularFiltrationRate())
    dst.set_allocated_leftglomerularfiltrationrate(SEScalarVolumePerTime::Unload(*src.m_LeftGlomerularFiltrationRate));
  if (src.HasLeftGlomerularFiltrationSurfaceArea())
    dst.set_allocated_leftglomerularfiltrationsurfacearea(SEScalarArea::Unload(*src.m_LeftGlomerularFiltrationSurfaceArea));
  if (src.HasLeftGlomerularFluidPermeability())
    dst.set_allocated_leftglomerularfluidpermeability(SEScalarVolumePerTimePressureArea::Unload(*src.m_LeftGlomerularFluidPermeability));
  if (src.HasLeftFiltrationFraction())
    dst.set_allocated_leftfiltrationfraction(SEScalar0To1::Unload(*src.m_LeftFiltrationFraction));
  if (src.HasLeftNetFiltrationPressure())
    dst.set_allocated_leftnetfiltrationpressure(SEScalarPressure::Unload(*src.m_LeftNetFiltrationPressure));
  if (src.HasLeftNetReabsorptionPressure())
    dst.set_allocated_leftnetreabsorptionpressure(SEScalarPressure::Unload(*src.m_LeftNetReabsorptionPressure));
  if (src.HasLeftPeritubularCapillariesHydrostaticPressure())
    dst.set_allocated_leftperitubularcapillarieshydrostaticpressure(SEScalarPressure::Unload(*src.m_LeftPeritubularCapillariesHydrostaticPressure));
  if (src.HasLeftPeritubularCapillariesOsmoticPressure())
    dst.set_allocated_leftperitubularcapillariesosmoticpressure(SEScalarPressure::Unload(*src.m_LeftPeritubularCapillariesOsmoticPressure));
  if (src.HasLeftReabsorptionFiltrationCoefficient())
    dst.set_allocated_leftreabsorptionfiltrationcoefficient(SEScalarVolumePerTimePressure::Unload(*src.m_LeftReabsorptionFiltrationCoefficient));
  if (src.HasLeftReabsorptionRate())
    dst.set_allocated_leftreabsorptionrate(SEScalarVolumePerTime::Unload(*src.m_LeftReabsorptionRate));
  if (src.HasLeftTubularReabsorptionFiltrationSurfaceArea())
    dst.set_allocated_lefttubularreabsorptionfiltrationsurfacearea(SEScalarArea::Unload(*src.m_LeftTubularReabsorptionFiltrationSurfaceArea));
  if (src.HasLeftTubularReabsorptionFluidPermeability())
    dst.set_allocated_lefttubularreabsorptionfluidpermeability(SEScalarVolumePerTimePressureArea::Unload(*src.m_LeftTubularReabsorptionFluidPermeability));
  if (src.HasLeftTubularHydrostaticPressure())
    dst.set_allocated_lefttubularhydrostaticpressure(SEScalarPressure::Unload(*src.m_LeftTubularHydrostaticPressure));
  if (src.HasLeftTubularOsmoticPressure())
    dst.set_allocated_lefttubularosmoticpressure(SEScalarPressure::Unload(*src.m_LeftTubularOsmoticPressure));

  if (src.HasRenalBloodFlow())
    dst.set_allocated_renalbloodflow(SEScalarVolumePerTime::Unload(*src.m_RenalBloodFlow));
  if (src.HasRenalPlasmaFlow())
    dst.set_allocated_renalplasmaflow(SEScalarVolumePerTime::Unload(*src.m_RenalPlasmaFlow));
  if (src.HasRenalVascularResistance())
    dst.set_allocated_renalvascularresistance(SEScalarFlowResistance::Unload(*src.m_RenalVascularResistance));

  if (src.HasRightAfferentArterioleResistance())
    dst.set_allocated_rightafferentarterioleresistance(SEScalarFlowResistance::Unload(*src.m_RightAfferentArterioleResistance));
  if (src.HasRightBowmansCapsulesHydrostaticPressure())
    dst.set_allocated_rightbowmanscapsuleshydrostaticpressure(SEScalarPressure::Unload(*src.m_RightBowmansCapsulesHydrostaticPressure));
  if (src.HasRightBowmansCapsulesOsmoticPressure())
    dst.set_allocated_rightbowmanscapsulesosmoticpressure(SEScalarPressure::Unload(*src.m_RightBowmansCapsulesOsmoticPressure));
  if (src.HasRightEfferentArterioleResistance())
    dst.set_allocated_rightefferentarterioleresistance(SEScalarFlowResistance::Unload(*src.m_RightEfferentArterioleResistance));
  if (src.HasRightGlomerularCapillariesHydrostaticPressure())
    dst.set_allocated_rightglomerularcapillarieshydrostaticpressure(SEScalarPressure::Unload(*src.m_RightGlomerularCapillariesHydrostaticPressure));
  if (src.HasRightGlomerularCapillariesOsmoticPressure())
    dst.set_allocated_rightglomerularcapillariesosmoticpressure(SEScalarPressure::Unload(*src.m_RightGlomerularCapillariesOsmoticPressure));
  if (src.HasRightGlomerularFiltrationCoefficient())
    dst.set_allocated_rightglomerularfiltrationcoefficient(SEScalarVolumePerTimePressure::Unload(*src.m_RightGlomerularFiltrationCoefficient));
  if (src.HasRightGlomerularFiltrationRate())
    dst.set_allocated_rightglomerularfiltrationrate(SEScalarVolumePerTime::Unload(*src.m_RightGlomerularFiltrationRate));
  if (src.HasRightGlomerularFiltrationSurfaceArea())
    dst.set_allocated_rightglomerularfiltrationsurfacearea(SEScalarArea::Unload(*src.m_RightGlomerularFiltrationSurfaceArea));
  if (src.HasRightGlomerularFluidPermeability())
    dst.set_allocated_rightglomerularfluidpermeability(SEScalarVolumePerTimePressureArea::Unload(*src.m_RightGlomerularFluidPermeability));
  if (src.HasRightFiltrationFraction())
    dst.set_allocated_rightfiltrationfraction(SEScalar0To1::Unload(*src.m_RightFiltrationFraction));
  if (src.HasRightNetFiltrationPressure())
    dst.set_allocated_rightnetfiltrationpressure(SEScalarPressure::Unload(*src.m_RightNetFiltrationPressure));
  if (src.HasRightNetReabsorptionPressure())
    dst.set_allocated_rightnetreabsorptionpressure(SEScalarPressure::Unload(*src.m_RightNetReabsorptionPressure));
  if (src.HasRightPeritubularCapillariesHydrostaticPressure())
    dst.set_allocated_rightperitubularcapillarieshydrostaticpressure(SEScalarPressure::Unload(*src.m_RightPeritubularCapillariesHydrostaticPressure));
  if (src.HasRightPeritubularCapillariesOsmoticPressure())
    dst.set_allocated_rightperitubularcapillariesosmoticpressure(SEScalarPressure::Unload(*src.m_RightPeritubularCapillariesOsmoticPressure));
  if (src.HasRightReabsorptionFiltrationCoefficient())
    dst.set_allocated_rightreabsorptionfiltrationcoefficient(SEScalarVolumePerTimePressure::Unload(*src.m_RightReabsorptionFiltrationCoefficient));
  if (src.HasRightReabsorptionRate())
    dst.set_allocated_rightreabsorptionrate(SEScalarVolumePerTime::Unload(*src.m_RightReabsorptionRate));
  if (src.HasRightTubularReabsorptionFiltrationSurfaceArea())
    dst.set_allocated_righttubularreabsorptionfiltrationsurfacearea(SEScalarArea::Unload(*src.m_RightTubularReabsorptionFiltrationSurfaceArea));
  if (src.HasRightTubularReabsorptionFluidPermeability())
    dst.set_allocated_righttubularreabsorptionfluidpermeability(SEScalarVolumePerTimePressureArea::Unload(*src.m_RightTubularReabsorptionFluidPermeability));
  if (src.HasRightTubularHydrostaticPressure())
    dst.set_allocated_righttubularhydrostaticpressure(SEScalarPressure::Unload(*src.m_RightTubularHydrostaticPressure));
  if (src.HasRightTubularOsmoticPressure())
    dst.set_allocated_righttubularosmoticpressure(SEScalarPressure::Unload(*src.m_RightTubularOsmoticPressure));

  if (src.HasUrinationRate())
    dst.set_allocated_urinationrate(SEScalarVolumePerTime::Unload(*src.m_UrinationRate));
  if (src.HasUrineOsmolality())
    dst.set_allocated_urineosmolality(SEScalarOsmolality::Unload(*src.m_UrineOsmolality));
  if (src.HasUrineOsmolarity())
    dst.set_allocated_urineosmolarity(SEScalarOsmolarity::Unload(*src.m_UrineOsmolarity));
  if (src.HasUrineProductionRate())
    dst.set_allocated_urineproductionrate(SEScalarVolumePerTime::Unload(*src.m_UrineProductionRate));
  if (src.HasUrineSpecificGravity())
    dst.set_allocated_urinespecificgravity(SEScalar::Unload(*src.m_UrineSpecificGravity));
  if (src.HasUrineVolume())
    dst.set_allocated_urinevolume(SEScalarVolume::Unload(*src.m_UrineVolume));
  if (src.HasUrineUreaNitrogenConcentration())
    dst.set_allocated_urineureanitrogenconcentration(SEScalarMassPerVolume::Unload(*src.m_UrineUreaNitrogenConcentration));
}

bool SERenalSystem::HasGlomerularFiltrationRate() const
{
  return m_GlomerularFiltrationRate == nullptr ? false : m_GlomerularFiltrationRate->IsValid();
}
SEScalarVolumePerTime& SERenalSystem::GetGlomerularFiltrationRate()
{
  if (m_GlomerularFiltrationRate == nullptr)
    m_GlomerularFiltrationRate = new SEScalarVolumePerTime();
  return *m_GlomerularFiltrationRate;
}
double SERenalSystem::GetGlomerularFiltrationRate(const VolumePerTimeUnit& unit) const
{
  if (m_GlomerularFiltrationRate == nullptr)
    return SEScalar::dNaN();
  return m_GlomerularFiltrationRate->GetValue(unit);
}

bool SERenalSystem::HasFiltrationFraction() const
{
  return m_FiltrationFraction == nullptr ? false : m_FiltrationFraction->IsValid();
}
SEScalar0To1& SERenalSystem::GetFiltrationFraction()
{
  if (m_FiltrationFraction == nullptr)
    m_FiltrationFraction = new SEScalar0To1();
  return *m_FiltrationFraction;
}
double SERenalSystem::GetFiltrationFraction() const
{
  if (m_FiltrationFraction == nullptr)
    return SEScalar::dNaN();
  return m_FiltrationFraction->GetValue();
}

bool SERenalSystem::HasLeftAfferentArterioleResistance() const
{
  return m_LeftAfferentArterioleResistance == nullptr ? false : m_LeftAfferentArterioleResistance->IsValid();
}
SEScalarFlowResistance& SERenalSystem::GetLeftAfferentArterioleResistance()
{
  if (m_LeftAfferentArterioleResistance == nullptr)
    m_LeftAfferentArterioleResistance = new SEScalarFlowResistance();
  return *m_LeftAfferentArterioleResistance;
}
double SERenalSystem::GetLeftAfferentArterioleResistance(const FlowResistanceUnit& unit) const
{
  if (m_LeftAfferentArterioleResistance == nullptr)
    return SEScalar::dNaN();
  return m_LeftAfferentArterioleResistance->GetValue(unit);
}

bool SERenalSystem::HasLeftBowmansCapsulesHydrostaticPressure() const
{
  return m_LeftBowmansCapsulesHydrostaticPressure == nullptr ? false : m_LeftBowmansCapsulesHydrostaticPressure->IsValid();
}
SEScalarPressure& SERenalSystem::GetLeftBowmansCapsulesHydrostaticPressure()
{
  if (m_LeftBowmansCapsulesHydrostaticPressure == nullptr)
    m_LeftBowmansCapsulesHydrostaticPressure = new SEScalarPressure();
  return *m_LeftBowmansCapsulesHydrostaticPressure;
}
double SERenalSystem::GetLeftBowmansCapsulesHydrostaticPressure(const PressureUnit& unit) const
{
  if (m_LeftBowmansCapsulesHydrostaticPressure == nullptr)
    return SEScalar::dNaN();
  return m_LeftBowmansCapsulesHydrostaticPressure->GetValue(unit);
}

bool SERenalSystem::HasLeftBowmansCapsulesOsmoticPressure() const
{
  return m_LeftBowmansCapsulesOsmoticPressure == nullptr ? false : m_LeftBowmansCapsulesOsmoticPressure->IsValid();
}
SEScalarPressure& SERenalSystem::GetLeftBowmansCapsulesOsmoticPressure()
{
  if (m_LeftBowmansCapsulesOsmoticPressure == nullptr)
    m_LeftBowmansCapsulesOsmoticPressure = new SEScalarPressure();
  return *m_LeftBowmansCapsulesOsmoticPressure;
}
double SERenalSystem::GetLeftBowmansCapsulesOsmoticPressure(const PressureUnit& unit) const
{
  if (m_LeftBowmansCapsulesOsmoticPressure == nullptr)
    return SEScalar::dNaN();
  return m_LeftBowmansCapsulesOsmoticPressure->GetValue(unit);
}

bool SERenalSystem::HasLeftEfferentArterioleResistance() const
{
  return m_LeftEfferentArterioleResistance == nullptr ? false : m_LeftEfferentArterioleResistance->IsValid();
}
SEScalarFlowResistance& SERenalSystem::GetLeftEfferentArterioleResistance()
{
  if (m_LeftEfferentArterioleResistance == nullptr)
    m_LeftEfferentArterioleResistance = new SEScalarFlowResistance();
  return *m_LeftEfferentArterioleResistance;
}
double SERenalSystem::GetLeftEfferentArterioleResistance(const FlowResistanceUnit& unit) const
{
  if (m_LeftEfferentArterioleResistance == nullptr)
    return SEScalar::dNaN();
  return m_LeftEfferentArterioleResistance->GetValue(unit);
}

bool SERenalSystem::HasLeftGlomerularCapillariesHydrostaticPressure() const
{
  return m_LeftGlomerularCapillariesHydrostaticPressure == nullptr ? false : m_LeftGlomerularCapillariesHydrostaticPressure->IsValid();
}
SEScalarPressure& SERenalSystem::GetLeftGlomerularCapillariesHydrostaticPressure()
{
  if (m_LeftGlomerularCapillariesHydrostaticPressure == nullptr)
    m_LeftGlomerularCapillariesHydrostaticPressure = new SEScalarPressure();
  return *m_LeftGlomerularCapillariesHydrostaticPressure;
}
double SERenalSystem::GetLeftGlomerularCapillariesHydrostaticPressure(const PressureUnit& unit) const
{
  if (m_LeftGlomerularCapillariesHydrostaticPressure == nullptr)
    return SEScalar::dNaN();
  return m_LeftGlomerularCapillariesHydrostaticPressure->GetValue(unit);
}

bool SERenalSystem::HasLeftGlomerularCapillariesOsmoticPressure() const
{
  return m_LeftGlomerularCapillariesOsmoticPressure == nullptr ? false : m_LeftGlomerularCapillariesOsmoticPressure->IsValid();
}
SEScalarPressure& SERenalSystem::GetLeftGlomerularCapillariesOsmoticPressure()
{
  if (m_LeftGlomerularCapillariesOsmoticPressure == nullptr)
    m_LeftGlomerularCapillariesOsmoticPressure = new SEScalarPressure();
  return *m_LeftGlomerularCapillariesOsmoticPressure;
}
double SERenalSystem::GetLeftGlomerularCapillariesOsmoticPressure(const PressureUnit& unit) const
{
  if (m_LeftGlomerularCapillariesOsmoticPressure == nullptr)
    return SEScalar::dNaN();
  return m_LeftGlomerularCapillariesOsmoticPressure->GetValue(unit);
}

bool SERenalSystem::HasLeftGlomerularFiltrationCoefficient() const
{
  return m_LeftGlomerularFiltrationCoefficient == nullptr ? false : m_LeftGlomerularFiltrationCoefficient->IsValid();
}
SEScalarVolumePerTimePressure& SERenalSystem::GetLeftGlomerularFiltrationCoefficient()
{
  if (m_LeftGlomerularFiltrationCoefficient == nullptr)
    m_LeftGlomerularFiltrationCoefficient = new SEScalarVolumePerTimePressure();
  return *m_LeftGlomerularFiltrationCoefficient;
}
double SERenalSystem::GetLeftGlomerularFiltrationCoefficient(const VolumePerTimePressureUnit& unit) const
{
  if (m_LeftGlomerularFiltrationCoefficient == nullptr)
    return SEScalar::dNaN();
  return m_LeftGlomerularFiltrationCoefficient->GetValue(unit);
}

bool SERenalSystem::HasLeftGlomerularFiltrationRate() const
{
  return m_LeftGlomerularFiltrationRate == nullptr ? false : m_LeftGlomerularFiltrationRate->IsValid();
}
SEScalarVolumePerTime& SERenalSystem::GetLeftGlomerularFiltrationRate()
{
  if (m_LeftGlomerularFiltrationRate == nullptr)
    m_LeftGlomerularFiltrationRate = new SEScalarVolumePerTime();
  return *m_LeftGlomerularFiltrationRate;
}
double SERenalSystem::GetLeftGlomerularFiltrationRate(const VolumePerTimeUnit& unit) const
{
  if (m_LeftGlomerularFiltrationRate == nullptr)
    return SEScalar::dNaN();
  return m_LeftGlomerularFiltrationRate->GetValue(unit);
}

bool SERenalSystem::HasLeftGlomerularFiltrationSurfaceArea() const
{
  return m_LeftGlomerularFiltrationSurfaceArea == nullptr ? false : m_LeftGlomerularFiltrationSurfaceArea->IsValid();
}
SEScalarArea& SERenalSystem::GetLeftGlomerularFiltrationSurfaceArea()
{
  if (m_LeftGlomerularFiltrationSurfaceArea == nullptr)
    m_LeftGlomerularFiltrationSurfaceArea = new SEScalarArea();
  return *m_LeftGlomerularFiltrationSurfaceArea;
}
double SERenalSystem::GetLeftGlomerularFiltrationSurfaceArea(const AreaUnit& unit) const
{
  if (m_LeftGlomerularFiltrationSurfaceArea == nullptr)
    return SEScalar::dNaN();
  return m_LeftGlomerularFiltrationSurfaceArea->GetValue(unit);
}

bool SERenalSystem::HasLeftGlomerularFluidPermeability() const
{
  return m_LeftGlomerularFluidPermeability == nullptr ? false : m_LeftGlomerularFluidPermeability->IsValid();
}
SEScalarVolumePerTimePressureArea& SERenalSystem::GetLeftGlomerularFluidPermeability()
{
  if (m_LeftGlomerularFluidPermeability == nullptr)
    m_LeftGlomerularFluidPermeability = new SEScalarVolumePerTimePressureArea();
  return *m_LeftGlomerularFluidPermeability;
}
double SERenalSystem::GetLeftGlomerularFluidPermeability(const VolumePerTimePressureAreaUnit& unit) const
{
  if (m_LeftGlomerularFluidPermeability == nullptr)
    return SEScalar::dNaN();
  return m_LeftGlomerularFluidPermeability->GetValue(unit);
}

bool SERenalSystem::HasLeftFiltrationFraction() const
{
  return m_LeftFiltrationFraction == nullptr ? false : m_LeftFiltrationFraction->IsValid();
}
SEScalar0To1& SERenalSystem::GetLeftFiltrationFraction()
{
  if (m_LeftFiltrationFraction == nullptr)
    m_LeftFiltrationFraction = new SEScalar0To1();
  return *m_LeftFiltrationFraction;
}
double SERenalSystem::GetLeftFiltrationFraction() const
{
  if (m_LeftFiltrationFraction == nullptr)
    return SEScalar::dNaN();
  return m_LeftFiltrationFraction->GetValue();
}

bool SERenalSystem::HasLeftNetFiltrationPressure() const
{
  return m_LeftNetFiltrationPressure == nullptr ? false : m_LeftNetFiltrationPressure->IsValid();
}
SEScalarPressure& SERenalSystem::GetLeftNetFiltrationPressure()
{
  if (m_LeftNetFiltrationPressure == nullptr)
    m_LeftNetFiltrationPressure = new SEScalarPressure();
  return *m_LeftNetFiltrationPressure;
}
double SERenalSystem::GetLeftNetFiltrationPressure(const PressureUnit& unit) const
{
  if (m_LeftNetFiltrationPressure == nullptr)
    return SEScalar::dNaN();
  return m_LeftNetFiltrationPressure->GetValue(unit);
}

bool SERenalSystem::HasLeftNetReabsorptionPressure() const
{
  return m_LeftNetReabsorptionPressure == nullptr ? false : m_LeftNetReabsorptionPressure->IsValid();
}
SEScalarPressure& SERenalSystem::GetLeftNetReabsorptionPressure()
{
  if (m_LeftNetReabsorptionPressure == nullptr)
    m_LeftNetReabsorptionPressure = new SEScalarPressure();
  return *m_LeftNetReabsorptionPressure;
}
double SERenalSystem::GetLeftNetReabsorptionPressure(const PressureUnit& unit) const
{
  if (m_LeftNetReabsorptionPressure == nullptr)
    return SEScalar::dNaN();
  return m_LeftNetReabsorptionPressure->GetValue(unit);
}

bool SERenalSystem::HasLeftPeritubularCapillariesHydrostaticPressure() const
{
  return m_LeftPeritubularCapillariesHydrostaticPressure == nullptr ? false : m_LeftPeritubularCapillariesHydrostaticPressure->IsValid();
}
SEScalarPressure& SERenalSystem::GetLeftPeritubularCapillariesHydrostaticPressure()
{
  if (m_LeftPeritubularCapillariesHydrostaticPressure == nullptr)
    m_LeftPeritubularCapillariesHydrostaticPressure = new SEScalarPressure();
  return *m_LeftPeritubularCapillariesHydrostaticPressure;
}
double SERenalSystem::GetLeftPeritubularCapillariesHydrostaticPressure(const PressureUnit& unit) const
{
  if (m_LeftPeritubularCapillariesHydrostaticPressure == nullptr)
    return SEScalar::dNaN();
  return m_LeftPeritubularCapillariesHydrostaticPressure->GetValue(unit);
}

bool SERenalSystem::HasLeftPeritubularCapillariesOsmoticPressure() const
{
  return m_LeftPeritubularCapillariesOsmoticPressure == nullptr ? false : m_LeftPeritubularCapillariesOsmoticPressure->IsValid();
}
SEScalarPressure& SERenalSystem::GetLeftPeritubularCapillariesOsmoticPressure()
{
  if (m_LeftPeritubularCapillariesOsmoticPressure == nullptr)
    m_LeftPeritubularCapillariesOsmoticPressure = new SEScalarPressure();
  return *m_LeftPeritubularCapillariesOsmoticPressure;
}
double SERenalSystem::GetLeftPeritubularCapillariesOsmoticPressure(const PressureUnit& unit) const
{
  if (m_LeftPeritubularCapillariesOsmoticPressure == nullptr)
    return SEScalar::dNaN();
  return m_LeftPeritubularCapillariesOsmoticPressure->GetValue(unit);
}

bool SERenalSystem::HasLeftReabsorptionFiltrationCoefficient() const
{
  return m_LeftReabsorptionFiltrationCoefficient == nullptr ? false : m_LeftReabsorptionFiltrationCoefficient->IsValid();
}
SEScalarVolumePerTimePressure& SERenalSystem::GetLeftReabsorptionFiltrationCoefficient()
{
  if (m_LeftReabsorptionFiltrationCoefficient == nullptr)
    m_LeftReabsorptionFiltrationCoefficient = new SEScalarVolumePerTimePressure();
  return *m_LeftReabsorptionFiltrationCoefficient;
}
double SERenalSystem::GetLeftReabsorptionFiltrationCoefficient(const VolumePerTimePressureUnit& unit) const
{
  if (m_LeftReabsorptionFiltrationCoefficient == nullptr)
    return SEScalar::dNaN();
  return m_LeftReabsorptionFiltrationCoefficient->GetValue(unit);
}

bool SERenalSystem::HasLeftReabsorptionRate() const
{
  return m_LeftReabsorptionRate == nullptr ? false : m_LeftReabsorptionRate->IsValid();
}
SEScalarVolumePerTime& SERenalSystem::GetLeftReabsorptionRate()
{
  if (m_LeftReabsorptionRate == nullptr)
    m_LeftReabsorptionRate = new SEScalarVolumePerTime();
  return *m_LeftReabsorptionRate;
}
double SERenalSystem::GetLeftReabsorptionRate(const VolumePerTimeUnit& unit) const
{
  if (m_LeftReabsorptionRate == nullptr)
    return SEScalar::dNaN();
  return m_LeftReabsorptionRate->GetValue(unit);
}

bool SERenalSystem::HasLeftTubularReabsorptionFiltrationSurfaceArea() const
{
  return m_LeftTubularReabsorptionFiltrationSurfaceArea == nullptr ? false : m_LeftTubularReabsorptionFiltrationSurfaceArea->IsValid();
}
SEScalarArea& SERenalSystem::GetLeftTubularReabsorptionFiltrationSurfaceArea()
{
  if (m_LeftTubularReabsorptionFiltrationSurfaceArea == nullptr)
    m_LeftTubularReabsorptionFiltrationSurfaceArea = new SEScalarArea();
  return *m_LeftTubularReabsorptionFiltrationSurfaceArea;
}
double SERenalSystem::GetLeftTubularReabsorptionFiltrationSurfaceArea(const AreaUnit& unit) const
{
  if (m_LeftTubularReabsorptionFiltrationSurfaceArea == nullptr)
    return SEScalar::dNaN();
  return m_LeftTubularReabsorptionFiltrationSurfaceArea->GetValue(unit);
}

bool SERenalSystem::HasLeftTubularReabsorptionFluidPermeability() const
{
  return m_LeftTubularReabsorptionFluidPermeability == nullptr ? false : m_LeftTubularReabsorptionFluidPermeability->IsValid();
}
SEScalarVolumePerTimePressureArea& SERenalSystem::GetLeftTubularReabsorptionFluidPermeability()
{
  if (m_LeftTubularReabsorptionFluidPermeability == nullptr)
    m_LeftTubularReabsorptionFluidPermeability = new SEScalarVolumePerTimePressureArea();
  return *m_LeftTubularReabsorptionFluidPermeability;
}
double SERenalSystem::GetLeftTubularReabsorptionFluidPermeability(const VolumePerTimePressureAreaUnit& unit) const
{
  if (m_LeftTubularReabsorptionFluidPermeability == nullptr)
    return SEScalar::dNaN();
  return m_LeftTubularReabsorptionFluidPermeability->GetValue(unit);
}

bool SERenalSystem::HasLeftTubularHydrostaticPressure() const
{
  return m_LeftTubularHydrostaticPressure == nullptr ? false : m_LeftTubularHydrostaticPressure->IsValid();
}
SEScalarPressure& SERenalSystem::GetLeftTubularHydrostaticPressure()
{
  if (m_LeftTubularHydrostaticPressure == nullptr)
    m_LeftTubularHydrostaticPressure = new SEScalarPressure();
  return *m_LeftTubularHydrostaticPressure;
}
double SERenalSystem::GetLeftTubularHydrostaticPressure(const PressureUnit& unit) const
{
  if (m_LeftTubularHydrostaticPressure == nullptr)
    return SEScalar::dNaN();
  return m_LeftTubularHydrostaticPressure->GetValue(unit);
}

bool SERenalSystem::HasLeftTubularOsmoticPressure() const
{
  return m_LeftTubularOsmoticPressure == nullptr ? false : m_LeftTubularOsmoticPressure->IsValid();
}
SEScalarPressure& SERenalSystem::GetLeftTubularOsmoticPressure()
{
  if (m_LeftTubularOsmoticPressure == nullptr)
    m_LeftTubularOsmoticPressure = new SEScalarPressure();
  return *m_LeftTubularOsmoticPressure;
}
double SERenalSystem::GetLeftTubularOsmoticPressure(const PressureUnit& unit) const
{
  if (m_LeftTubularOsmoticPressure == nullptr)
    return SEScalar::dNaN();
  return m_LeftTubularOsmoticPressure->GetValue(unit);
}

bool SERenalSystem::HasRenalBloodFlow() const
{
  return m_RenalBloodFlow == nullptr ? false : m_RenalBloodFlow->IsValid();
}
SEScalarVolumePerTime& SERenalSystem::GetRenalBloodFlow()
{
  if (m_RenalBloodFlow == nullptr)
    m_RenalBloodFlow = new SEScalarVolumePerTime();
  return *m_RenalBloodFlow;
}
double SERenalSystem::GetRenalBloodFlow(const VolumePerTimeUnit& unit) const
{
  if (m_RenalBloodFlow == nullptr)
    return SEScalar::dNaN();
  return m_RenalBloodFlow->GetValue(unit);
}

bool SERenalSystem::HasRenalPlasmaFlow() const
{
  return m_RenalPlasmaFlow == nullptr ? false : m_RenalPlasmaFlow->IsValid();
}
SEScalarVolumePerTime& SERenalSystem::GetRenalPlasmaFlow()
{
  if (m_RenalPlasmaFlow == nullptr)
    m_RenalPlasmaFlow = new SEScalarVolumePerTime();
  return *m_RenalPlasmaFlow;
}
double SERenalSystem::GetRenalPlasmaFlow(const VolumePerTimeUnit& unit) const
{
  if (m_RenalPlasmaFlow == nullptr)
    return SEScalar::dNaN();
  return m_RenalPlasmaFlow->GetValue(unit);
}

bool SERenalSystem::HasRenalVascularResistance() const
{
  return m_RenalVascularResistance == nullptr ? false : m_RenalVascularResistance->IsValid();
}
SEScalarFlowResistance& SERenalSystem::GetRenalVascularResistance()
{
  if (m_RenalVascularResistance == nullptr)
    m_RenalVascularResistance = new SEScalarFlowResistance();
  return *m_RenalVascularResistance;
}
double SERenalSystem::GetRenalVascularResistance(const FlowResistanceUnit& unit) const
{
  if (m_RenalVascularResistance == nullptr)
    return SEScalar::dNaN();
  return m_RenalVascularResistance->GetValue(unit);
}

bool SERenalSystem::HasRightAfferentArterioleResistance() const
{
  return m_RightAfferentArterioleResistance == nullptr ? false : m_RightAfferentArterioleResistance->IsValid();
}
SEScalarFlowResistance& SERenalSystem::GetRightAfferentArterioleResistance()
{
  if (m_RightAfferentArterioleResistance == nullptr)
    m_RightAfferentArterioleResistance = new SEScalarFlowResistance();
  return *m_RightAfferentArterioleResistance;
}
double SERenalSystem::GetRightAfferentArterioleResistance(const FlowResistanceUnit& unit) const
{
  if (m_RightAfferentArterioleResistance == nullptr)
    return SEScalar::dNaN();
  return m_RightAfferentArterioleResistance->GetValue(unit);
}

bool SERenalSystem::HasRightBowmansCapsulesHydrostaticPressure() const
{
  return m_RightBowmansCapsulesHydrostaticPressure == nullptr ? false : m_RightBowmansCapsulesHydrostaticPressure->IsValid();
}
SEScalarPressure& SERenalSystem::GetRightBowmansCapsulesHydrostaticPressure()
{
  if (m_RightBowmansCapsulesHydrostaticPressure == nullptr)
    m_RightBowmansCapsulesHydrostaticPressure = new SEScalarPressure();
  return *m_RightBowmansCapsulesHydrostaticPressure;
}
double SERenalSystem::GetRightBowmansCapsulesHydrostaticPressure(const PressureUnit& unit) const
{
  if (m_RightBowmansCapsulesHydrostaticPressure == nullptr)
    return SEScalar::dNaN();
  return m_RightBowmansCapsulesHydrostaticPressure->GetValue(unit);
}

bool SERenalSystem::HasRightBowmansCapsulesOsmoticPressure() const
{
  return m_RightBowmansCapsulesOsmoticPressure == nullptr ? false : m_RightBowmansCapsulesOsmoticPressure->IsValid();
}
SEScalarPressure& SERenalSystem::GetRightBowmansCapsulesOsmoticPressure()
{
  if (m_RightBowmansCapsulesOsmoticPressure == nullptr)
    m_RightBowmansCapsulesOsmoticPressure = new SEScalarPressure();
  return *m_RightBowmansCapsulesOsmoticPressure;
}
double SERenalSystem::GetRightBowmansCapsulesOsmoticPressure(const PressureUnit& unit) const
{
  if (m_RightBowmansCapsulesOsmoticPressure == nullptr)
    return SEScalar::dNaN();
  return m_RightBowmansCapsulesOsmoticPressure->GetValue(unit);
}

bool SERenalSystem::HasRightEfferentArterioleResistance() const
{
  return m_RightEfferentArterioleResistance == nullptr ? false : m_RightEfferentArterioleResistance->IsValid();
}
SEScalarFlowResistance& SERenalSystem::GetRightEfferentArterioleResistance()
{
  if (m_RightEfferentArterioleResistance == nullptr)
    m_RightEfferentArterioleResistance = new SEScalarFlowResistance();
  return *m_RightEfferentArterioleResistance;
}
double SERenalSystem::GetRightEfferentArterioleResistance(const FlowResistanceUnit& unit) const
{
  if (m_RightEfferentArterioleResistance == nullptr)
    return SEScalar::dNaN();
  return m_RightEfferentArterioleResistance->GetValue(unit);
}

bool SERenalSystem::HasRightGlomerularCapillariesHydrostaticPressure() const
{
  return m_RightGlomerularCapillariesHydrostaticPressure == nullptr ? false : m_RightGlomerularCapillariesHydrostaticPressure->IsValid();
}
SEScalarPressure& SERenalSystem::GetRightGlomerularCapillariesHydrostaticPressure()
{
  if (m_RightGlomerularCapillariesHydrostaticPressure == nullptr)
    m_RightGlomerularCapillariesHydrostaticPressure = new SEScalarPressure();
  return *m_RightGlomerularCapillariesHydrostaticPressure;
}
double SERenalSystem::GetRightGlomerularCapillariesHydrostaticPressure(const PressureUnit& unit) const
{
  if (m_RightGlomerularCapillariesHydrostaticPressure == nullptr)
    return SEScalar::dNaN();
  return m_RightGlomerularCapillariesHydrostaticPressure->GetValue(unit);
}

bool SERenalSystem::HasRightGlomerularCapillariesOsmoticPressure() const
{
  return m_RightGlomerularCapillariesOsmoticPressure == nullptr ? false : m_RightGlomerularCapillariesOsmoticPressure->IsValid();
}
SEScalarPressure& SERenalSystem::GetRightGlomerularCapillariesOsmoticPressure()
{
  if (m_RightGlomerularCapillariesOsmoticPressure == nullptr)
    m_RightGlomerularCapillariesOsmoticPressure = new SEScalarPressure();
  return *m_RightGlomerularCapillariesOsmoticPressure;
}
double SERenalSystem::GetRightGlomerularCapillariesOsmoticPressure(const PressureUnit& unit) const
{
  if (m_RightGlomerularCapillariesOsmoticPressure == nullptr)
    return SEScalar::dNaN();
  return m_RightGlomerularCapillariesOsmoticPressure->GetValue(unit);
}

bool SERenalSystem::HasRightGlomerularFiltrationCoefficient() const
{
  return m_RightGlomerularFiltrationCoefficient == nullptr ? false : m_RightGlomerularFiltrationCoefficient->IsValid();
}
SEScalarVolumePerTimePressure& SERenalSystem::GetRightGlomerularFiltrationCoefficient()
{
  if (m_RightGlomerularFiltrationCoefficient == nullptr)
    m_RightGlomerularFiltrationCoefficient = new SEScalarVolumePerTimePressure();
  return *m_RightGlomerularFiltrationCoefficient;
}
double SERenalSystem::GetRightGlomerularFiltrationCoefficient(const VolumePerTimePressureUnit& unit) const
{
  if (m_RightGlomerularFiltrationCoefficient == nullptr)
    return SEScalar::dNaN();
  return m_RightGlomerularFiltrationCoefficient->GetValue(unit);
}

bool SERenalSystem::HasRightGlomerularFiltrationRate() const
{
  return m_RightGlomerularFiltrationRate == nullptr ? false : m_RightGlomerularFiltrationRate->IsValid();
}
SEScalarVolumePerTime& SERenalSystem::GetRightGlomerularFiltrationRate()
{
  if (m_RightGlomerularFiltrationRate == nullptr)
    m_RightGlomerularFiltrationRate = new SEScalarVolumePerTime();
  return *m_RightGlomerularFiltrationRate;
}
double SERenalSystem::GetRightGlomerularFiltrationRate(const VolumePerTimeUnit& unit) const
{
  if (m_RightGlomerularFiltrationRate == nullptr)
    return SEScalar::dNaN();
  return m_RightGlomerularFiltrationRate->GetValue(unit);
}

bool SERenalSystem::HasRightGlomerularFiltrationSurfaceArea() const
{
  return m_RightGlomerularFiltrationSurfaceArea == nullptr ? false : m_RightGlomerularFiltrationSurfaceArea->IsValid();
}
SEScalarArea& SERenalSystem::GetRightGlomerularFiltrationSurfaceArea()
{
  if (m_RightGlomerularFiltrationSurfaceArea == nullptr)
    m_RightGlomerularFiltrationSurfaceArea = new SEScalarArea();
  return *m_RightGlomerularFiltrationSurfaceArea;
}
double SERenalSystem::GetRightGlomerularFiltrationSurfaceArea(const AreaUnit& unit) const
{
  if (m_RightGlomerularFiltrationSurfaceArea == nullptr)
    return SEScalar::dNaN();
  return m_RightGlomerularFiltrationSurfaceArea->GetValue(unit);
}

bool SERenalSystem::HasRightGlomerularFluidPermeability() const
{
  return m_RightGlomerularFluidPermeability == nullptr ? false : m_RightGlomerularFluidPermeability->IsValid();
}
SEScalarVolumePerTimePressureArea& SERenalSystem::GetRightGlomerularFluidPermeability()
{
  if (m_RightGlomerularFluidPermeability == nullptr)
    m_RightGlomerularFluidPermeability = new SEScalarVolumePerTimePressureArea();
  return *m_RightGlomerularFluidPermeability;
}
double SERenalSystem::GetRightGlomerularFluidPermeability(const VolumePerTimePressureAreaUnit& unit) const
{
  if (m_RightGlomerularFluidPermeability == nullptr)
    return SEScalar::dNaN();
  return m_RightGlomerularFluidPermeability->GetValue(unit);
}

bool SERenalSystem::HasRightFiltrationFraction() const
{
  return m_RightFiltrationFraction == nullptr ? false : m_RightFiltrationFraction->IsValid();
}
SEScalar0To1& SERenalSystem::GetRightFiltrationFraction()
{
  if (m_RightFiltrationFraction == nullptr)
    m_RightFiltrationFraction = new SEScalar0To1();
  return *m_RightFiltrationFraction;
}
double SERenalSystem::GetRightFiltrationFraction() const
{
  if (m_RightFiltrationFraction == nullptr)
    return SEScalar::dNaN();
  return m_RightFiltrationFraction->GetValue();
}

bool SERenalSystem::HasRightNetFiltrationPressure() const
{
  return m_RightNetFiltrationPressure == nullptr ? false : m_RightNetFiltrationPressure->IsValid();
}
SEScalarPressure& SERenalSystem::GetRightNetFiltrationPressure()
{
  if (m_RightNetFiltrationPressure == nullptr)
    m_RightNetFiltrationPressure = new SEScalarPressure();
  return *m_RightNetFiltrationPressure;
}
double SERenalSystem::GetRightNetFiltrationPressure(const PressureUnit& unit) const
{
  if (m_RightNetFiltrationPressure == nullptr)
    return SEScalar::dNaN();
  return m_RightNetFiltrationPressure->GetValue(unit);
}

bool SERenalSystem::HasRightNetReabsorptionPressure() const
{
  return m_RightNetReabsorptionPressure == nullptr ? false : m_RightNetReabsorptionPressure->IsValid();
}
SEScalarPressure& SERenalSystem::GetRightNetReabsorptionPressure()
{
  if (m_RightNetReabsorptionPressure == nullptr)
    m_RightNetReabsorptionPressure = new SEScalarPressure();
  return *m_RightNetReabsorptionPressure;
}
double SERenalSystem::GetRightNetReabsorptionPressure(const PressureUnit& unit) const
{
  if (m_RightNetReabsorptionPressure == nullptr)
    return SEScalar::dNaN();
  return m_RightNetReabsorptionPressure->GetValue(unit);
}

bool SERenalSystem::HasRightPeritubularCapillariesHydrostaticPressure() const
{
  return m_RightPeritubularCapillariesHydrostaticPressure == nullptr ? false : m_RightPeritubularCapillariesHydrostaticPressure->IsValid();
}
SEScalarPressure& SERenalSystem::GetRightPeritubularCapillariesHydrostaticPressure()
{
  if (m_RightPeritubularCapillariesHydrostaticPressure == nullptr)
    m_RightPeritubularCapillariesHydrostaticPressure = new SEScalarPressure();
  return *m_RightPeritubularCapillariesHydrostaticPressure;
}
double SERenalSystem::GetRightPeritubularCapillariesHydrostaticPressure(const PressureUnit& unit) const
{
  if (m_RightPeritubularCapillariesHydrostaticPressure == nullptr)
    return SEScalar::dNaN();
  return m_RightPeritubularCapillariesHydrostaticPressure->GetValue(unit);
}

bool SERenalSystem::HasRightPeritubularCapillariesOsmoticPressure() const
{
  return m_RightPeritubularCapillariesOsmoticPressure == nullptr ? false : m_RightPeritubularCapillariesOsmoticPressure->IsValid();
}
SEScalarPressure& SERenalSystem::GetRightPeritubularCapillariesOsmoticPressure()
{
  if (m_RightPeritubularCapillariesOsmoticPressure == nullptr)
    m_RightPeritubularCapillariesOsmoticPressure = new SEScalarPressure();
  return *m_RightPeritubularCapillariesOsmoticPressure;
}
double SERenalSystem::GetRightPeritubularCapillariesOsmoticPressure(const PressureUnit& unit) const
{
  if (m_RightPeritubularCapillariesOsmoticPressure == nullptr)
    return SEScalar::dNaN();
  return m_RightPeritubularCapillariesOsmoticPressure->GetValue(unit);
}

bool SERenalSystem::HasRightReabsorptionFiltrationCoefficient() const
{
  return m_RightReabsorptionFiltrationCoefficient == nullptr ? false : m_RightReabsorptionFiltrationCoefficient->IsValid();
}
SEScalarVolumePerTimePressure& SERenalSystem::GetRightReabsorptionFiltrationCoefficient()
{
  if (m_RightReabsorptionFiltrationCoefficient == nullptr)
    m_RightReabsorptionFiltrationCoefficient = new SEScalarVolumePerTimePressure();
  return *m_RightReabsorptionFiltrationCoefficient;
}
double SERenalSystem::GetRightReabsorptionFiltrationCoefficient(const VolumePerTimePressureUnit& unit) const
{
  if (m_RightReabsorptionFiltrationCoefficient == nullptr)
    return SEScalar::dNaN();
  return m_RightReabsorptionFiltrationCoefficient->GetValue(unit);
}

bool SERenalSystem::HasRightReabsorptionRate() const
{
  return m_RightReabsorptionRate == nullptr ? false : m_RightReabsorptionRate->IsValid();
}
SEScalarVolumePerTime& SERenalSystem::GetRightReabsorptionRate()
{
  if (m_RightReabsorptionRate == nullptr)
    m_RightReabsorptionRate = new SEScalarVolumePerTime();
  return *m_RightReabsorptionRate;
}
double SERenalSystem::GetRightReabsorptionRate(const VolumePerTimeUnit& unit) const
{
  if (m_RightReabsorptionRate == nullptr)
    return SEScalar::dNaN();
  return m_RightReabsorptionRate->GetValue(unit);
}

bool SERenalSystem::HasRightTubularReabsorptionFiltrationSurfaceArea() const
{
  return m_RightTubularReabsorptionFiltrationSurfaceArea == nullptr ? false : m_RightTubularReabsorptionFiltrationSurfaceArea->IsValid();
}
SEScalarArea& SERenalSystem::GetRightTubularReabsorptionFiltrationSurfaceArea()
{
  if (m_RightTubularReabsorptionFiltrationSurfaceArea == nullptr)
    m_RightTubularReabsorptionFiltrationSurfaceArea = new SEScalarArea();
  return *m_RightTubularReabsorptionFiltrationSurfaceArea;
}
double SERenalSystem::GetRightTubularReabsorptionFiltrationSurfaceArea(const AreaUnit& unit) const
{
  if (m_RightTubularReabsorptionFiltrationSurfaceArea == nullptr)
    return SEScalar::dNaN();
  return m_RightTubularReabsorptionFiltrationSurfaceArea->GetValue(unit);
}

bool SERenalSystem::HasRightTubularReabsorptionFluidPermeability() const
{
  return m_RightTubularReabsorptionFluidPermeability == nullptr ? false : m_RightTubularReabsorptionFluidPermeability->IsValid();
}
SEScalarVolumePerTimePressureArea& SERenalSystem::GetRightTubularReabsorptionFluidPermeability()
{
  if (m_RightTubularReabsorptionFluidPermeability == nullptr)
    m_RightTubularReabsorptionFluidPermeability = new SEScalarVolumePerTimePressureArea();
  return *m_RightTubularReabsorptionFluidPermeability;
}
double SERenalSystem::GetRightTubularReabsorptionFluidPermeability(const VolumePerTimePressureAreaUnit& unit) const
{
  if (m_RightTubularReabsorptionFluidPermeability == nullptr)
    return SEScalar::dNaN();
  return m_RightTubularReabsorptionFluidPermeability->GetValue(unit);
}

bool SERenalSystem::HasRightTubularHydrostaticPressure() const
{
  return m_RightTubularHydrostaticPressure == nullptr ? false : m_RightTubularHydrostaticPressure->IsValid();
}
SEScalarPressure& SERenalSystem::GetRightTubularHydrostaticPressure()
{
  if (m_RightTubularHydrostaticPressure == nullptr)
    m_RightTubularHydrostaticPressure = new SEScalarPressure();
  return *m_RightTubularHydrostaticPressure;
}
double SERenalSystem::GetRightTubularHydrostaticPressure(const PressureUnit& unit) const
{
  if (m_RightTubularHydrostaticPressure == nullptr)
    return SEScalar::dNaN();
  return m_RightTubularHydrostaticPressure->GetValue(unit);
}

bool SERenalSystem::HasRightTubularOsmoticPressure() const
{
  return m_RightTubularOsmoticPressure == nullptr ? false : m_RightTubularOsmoticPressure->IsValid();
}
SEScalarPressure& SERenalSystem::GetRightTubularOsmoticPressure()
{
  if (m_RightTubularOsmoticPressure == nullptr)
    m_RightTubularOsmoticPressure = new SEScalarPressure();
  return *m_RightTubularOsmoticPressure;
}
double SERenalSystem::GetRightTubularOsmoticPressure(const PressureUnit& unit) const
{
  if (m_RightTubularOsmoticPressure == nullptr)
    return SEScalar::dNaN();
  return m_RightTubularOsmoticPressure->GetValue(unit);
}

bool SERenalSystem::HasUrinationRate() const
{
  return m_UrinationRate == nullptr ? false : m_UrinationRate->IsValid();
}
SEScalarVolumePerTime& SERenalSystem::GetUrinationRate()
{
  if (m_UrinationRate == nullptr)
    m_UrinationRate = new SEScalarVolumePerTime();
  return *m_UrinationRate;
}
double SERenalSystem::GetUrinationRate(const VolumePerTimeUnit& unit) const
{
  if (m_UrinationRate == nullptr)
    return SEScalar::dNaN();
  return m_UrinationRate->GetValue(unit);
}

bool SERenalSystem::HasUrineOsmolality() const
{
  return m_UrineOsmolality == nullptr ? false : m_UrineOsmolality->IsValid();
}
SEScalarOsmolality& SERenalSystem::GetUrineOsmolality()
{
  if (m_UrineOsmolality == nullptr)
    m_UrineOsmolality = new SEScalarOsmolality();
  return *m_UrineOsmolality;
}
double SERenalSystem::GetUrineOsmolality(const OsmolalityUnit& unit) const
{
  if (m_UrineOsmolality == nullptr)
    return SEScalar::dNaN();
  return m_UrineOsmolality->GetValue(unit);
}

bool SERenalSystem::HasUrineOsmolarity() const
{
  return m_UrineOsmolarity == nullptr ? false : m_UrineOsmolarity->IsValid();
}
SEScalarOsmolarity& SERenalSystem::GetUrineOsmolarity()
{
  if (m_UrineOsmolarity == nullptr)
    m_UrineOsmolarity = new SEScalarOsmolarity();
  return *m_UrineOsmolarity;
}
double SERenalSystem::GetUrineOsmolarity(const OsmolarityUnit& unit) const
{
  if (m_UrineOsmolarity == nullptr)
    return SEScalar::dNaN();
  return m_UrineOsmolarity->GetValue(unit);
}

bool SERenalSystem::HasUrineProductionRate() const
{
  return m_UrineProductionRate == nullptr ? false : m_UrineProductionRate->IsValid();
}
SEScalarVolumePerTime& SERenalSystem::GetUrineProductionRate()
{
  if (m_UrineProductionRate == nullptr)
    m_UrineProductionRate = new SEScalarVolumePerTime();
  return *m_UrineProductionRate;
}
double SERenalSystem::GetUrineProductionRate(const VolumePerTimeUnit& unit) const
{
  if (m_UrineProductionRate == nullptr)
    return SEScalar::dNaN();
  return m_UrineProductionRate->GetValue(unit);
}

bool SERenalSystem::HasUrineSpecificGravity() const
{
  return m_UrineSpecificGravity == nullptr ? false : m_UrineSpecificGravity->IsValid();
}
SEScalar& SERenalSystem::GetUrineSpecificGravity()
{
  if (m_UrineSpecificGravity == nullptr)
    m_UrineSpecificGravity = new SEScalar();
  return *m_UrineSpecificGravity;
}
double SERenalSystem::GetUrineSpecificGravity() const
{
  if (m_UrineSpecificGravity == nullptr)
    return SEScalar::dNaN();
  return m_UrineSpecificGravity->GetValue();
}

bool SERenalSystem::HasUrineVolume() const
{
  return m_UrineVolume == nullptr ? false : m_UrineVolume->IsValid();
}
SEScalarVolume& SERenalSystem::GetUrineVolume()
{
  if (m_UrineVolume == nullptr)
    m_UrineVolume = new SEScalarVolume();
  return *m_UrineVolume;
}
double SERenalSystem::GetUrineVolume(const VolumeUnit& unit) const
{
  if (m_UrineVolume == nullptr)
    return SEScalar::dNaN();
  return m_UrineVolume->GetValue(unit);
}

bool SERenalSystem::HasUrineUreaNitrogenConcentration() const
{
  return m_UrineUreaNitrogenConcentration == nullptr ? false : m_UrineUreaNitrogenConcentration->IsValid();
}
SEScalarMassPerVolume& SERenalSystem::GetUrineUreaNitrogenConcentration()
{
  if (m_UrineUreaNitrogenConcentration == nullptr)
    m_UrineUreaNitrogenConcentration = new SEScalarMassPerVolume();
  return *m_UrineUreaNitrogenConcentration;
}
double SERenalSystem::GetUrineUreaNitrogenConcentration(const MassPerVolumeUnit& unit) const
{
  if (m_UrineUreaNitrogenConcentration == nullptr)
    return SEScalar::dNaN();
  return m_UrineUreaNitrogenConcentration->GetValue(unit);
}




