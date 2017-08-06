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

#include "stdafx.h"
#include "bind/PulseConfigurationData.hxx"
#include "bind/BaroreceptorConfigurationData.hxx"
#include "bind/BloodChemistryConfigurationData.hxx"
#include "bind/CardiovascularConfigurationData.hxx"
#include "bind/CircuitConfigurationData.hxx"
#include "bind/ConstantsConfigurationData.hxx"
#include "bind/DrugsConfigurationData.hxx"
#include "bind/EnergyConfigurationData.hxx"
#include "bind/EnvironmentConfigurationData.hxx"
#include "bind/EnvironmentalConditionsData.hxx"
#include "bind/EnergyConfigurationData.hxx"
#include "bind/GastrointestinalConfigurationData.hxx"
#include "bind/NervousConfigurationData.hxx"
#include "bind/RenalConfigurationData.hxx"
#include "bind/RespiratoryConfigurationData.hxx"
#include "bind/TissueConfigurationData.hxx"
#include "properties/SEScalarMass.h"
#include "bind/ScalarMassData.hxx"
#include "properties/SEScalarMassPerVolume.h"
#include "bind/ScalarMassPerVolumeData.hxx"
#include "properties/SEScalarHeatCapacitancePerAmount.h"
#include "bind/ScalarHeatCapacitancePerAmountData.hxx"
#include "properties/SEScalarHeatCapacitancePerMass.h"
#include "bind/ScalarHeatCapacitancePerMassData.hxx"
#include "properties/SEScalarHeatConductance.h"
#include "bind/ScalarHeatConductanceData.hxx"
#include "properties/SEScalarEnergyPerMass.h"
#include "bind/ScalarEnergyPerMassData.hxx"
#include "properties/SEScalar0To1.h"
#include "bind/ScalarFractionData.hxx"
#include "properties/SEScalarVolume.h"
#include "bind/ScalarVolumeData.hxx"
#include "properties/SEScalarArea.h"
#include "bind/ScalarAreaData.hxx"
#include "properties/SEScalarLength.h"
#include "bind/ScalarLengthData.hxx"
#include "properties/SEScalarAreaPerTimePressure.h"
#include "bind/ScalarAreaPerTimePressureData.hxx"
#include "properties/SEScalarPressure.h"
#include "bind/ScalarPressureData.hxx"
#include "properties/SEScalarMassPerAmount.h"
#include "bind/ScalarMassPerAmountData.hxx"
#include "properties/SEScalarFlowResistance.h"
#include "bind/ScalarFlowResistanceData.hxx"
#include "properties/SEScalarFlowElastance.h"
#include "bind/ScalarFlowElastanceData.hxx"
#include "properties/SEScalarHeatResistance.h"
#include "bind/ScalarHeatResistanceData.hxx"
#include "properties/SEScalarElectricResistance.h"
#include "bind/ScalarElectricResistanceData.hxx"
#include "properties/SEScalarMassPerAmount.h"
#include "bind/ScalarMassPerAmountData.hxx"
#include "properties/SEScalarTemperature.h"
#include "bind/ScalarTemperatureData.hxx"
#include "properties/SEScalarEnergyPerAmount.h"
#include "bind/ScalarEnergyPerAmountData.hxx"
#include "properties/SEScalarTime.h"
#include "bind/ScalarTimeData.hxx"
#include "properties/SEScalarMassPerTime.h"
#include "bind/ScalarMassPerTimeData.hxx"
#include "properties/SEScalarVolumePerTimeArea.h"
#include "bind/ScalarVolumePerTimeAreaData.hxx"
#include "properties/SEScalarVolumePerTimePressureArea.h"
#include "bind/ScalarVolumePerTimePressureAreaData.hxx"
#include "properties/SEScalarVolumePerTime.h"
#include "bind/ScalarVolumePerTimeData.hxx"
#include "properties/SEScalarInverseVolume.h"
#include "properties/SEScalarPowerPerAreaTemperatureToTheFourth.h"
#include "bind/ScalarPowerPerAreaTemperatureToTheFourthData.hxx"
#include "patient/SENutrition.h"
#include "bind/PatientNutrition.hxx"
#include "engine/PhysiologyEngineDynamicStabilization.h"
#include "engine/PhysiologyEngineTimedStabilization.h"
#include "Serializer.h"



PulseConfiguration::PulseConfiguration(SESubstanceManager& substances) : PhysiologyEngineConfiguration(substances.GetLogger()), m_Substances(substances)
{
  // Barorecptors
  m_ResponseSlope = nullptr;
  m_HeartRateDistributedTimeDelay = nullptr;
  m_HeartElastanceDistributedTimeDelay = nullptr;
  m_SystemicResistanceDistributedTimeDelay = nullptr;
  m_VenousComplianceDistributedTimeDelay = nullptr;
  m_NormalizedHeartRateIntercept = nullptr;
  m_NormalizedHeartRateSympatheticSlope = nullptr;
  m_NormalizedHeartRateParasympatheticSlope = nullptr;
  m_NormalizedHeartElastanceIntercept = nullptr;
  m_NormalizedHeartElastanceSympatheticSlope = nullptr;
  m_NormalizedResistanceIntercept = nullptr;
  m_NormalizedResistanceSympatheticSlope = nullptr;
  m_NormalizedComplianceIntercept = nullptr;
  m_NormalizedComplianceParasympatheticSlope = nullptr;

  // Blood Chemistry
  m_MeanCorpuscularHemoglobin = nullptr;
  m_MeanCorpuscularVolume = nullptr;
  m_StandardDiffusionDistance = nullptr;
  m_StandardOxygenDiffusionCoefficient = nullptr;

  // Cardiovascular
  m_LeftHeartElastanceMaximum = nullptr;
  m_LeftHeartElastanceMinimum = nullptr;
  m_MinimumBloodVolumeFraction = nullptr;
  m_RightHeartElastanceMaximum = nullptr;
  m_RightHeartElastanceMinimum = nullptr;
  m_StandardPulmonaryCapillaryCoverage = nullptr;

  // Circuit
  m_CardiovascularOpenResistance = nullptr;
  m_DefaultClosedElectricResistance = nullptr;
  m_DefaultClosedFlowResistance = nullptr;
  m_DefaultClosedHeatResistance = nullptr;
  m_DefaultOpenElectricResistance = nullptr;
  m_DefaultOpenFlowResistance = nullptr;
  m_DefaultOpenHeatResistance = nullptr;
  m_MachineClosedResistance = nullptr;
  m_MachineOpenResistance = nullptr;
  m_RespiratoryClosedResistance = nullptr;
  m_RespiratoryOpenResistance = nullptr;

  // Constants
  m_OxygenMetabolicConstant = nullptr;
  m_StefanBoltzmann = nullptr;
  m_UniversalGasConstant = nullptr;

  // Drugs 
  m_PDEnabled = cdm::eSwitch(-1);

  // Energy
  m_BodySpecificHeat = nullptr;
  m_CarbondDioxideProductionFromOxygenConsumptionConstant = nullptr;
  m_CoreTemperatureLow = nullptr;
  m_CoreTemperatureHigh = nullptr;
  m_DeltaCoreTemperatureLow = nullptr;
  m_EnergyPerATP = nullptr;
  m_SweatHeatTransfer = nullptr;
  m_VaporizationEnergy = nullptr;
  m_VaporSpecificHeat = nullptr;

  // Environment
  m_AirDensity = nullptr;
  m_AirSpecificHeat = nullptr;
  m_MolarMassOfDryAir = nullptr;
  m_MolarMassOfWaterVapor = nullptr;
  m_InitialEnvironmentalConditions = nullptr;
  m_WaterDensity = nullptr;

  // Gastrointestinal
  m_CalciumDigestionRate = nullptr;
  m_CalciumAbsorbtionFraction = nullptr;
  m_CarbohydrateAbsorbtionFraction = nullptr;
  m_DefaultCarbohydrateDigestionRate = nullptr;
  m_DefaultFatDigestionRate = nullptr;
  m_DefaultProteinDigestionRate = nullptr;
  m_DefaultStomachContents = nullptr;
  m_FatAbsorbtionFraction = nullptr;
  m_ProteinToUreaFraction = nullptr;
  m_WaterDigestionRate = nullptr;

  // Nervous
  m_PupilDiameterBaseline = nullptr;
  
  // Renal
  m_RenalEnabled = cdm::eSwitch(-1);
  m_PlasmaSodiumConcentrationSetPoint = nullptr;
  m_PeritubularPotassiumConcentrationSetPoint = nullptr;
  m_LeftGlomerularFluidPermeabilityBaseline = nullptr;
  m_LeftGlomerularFilteringSurfaceAreaBaseline = nullptr;
  m_LeftTubularReabsorptionFluidPermeabilityBaseline = nullptr;
  m_LeftTubularReabsorptionFilteringSurfaceAreaBaseline = nullptr;
  m_MaximumAfferentResistance = nullptr;
  m_MinimumAfferentResistance = nullptr;
  m_RightGlomerularFluidPermeabilityBaseline = nullptr;
  m_RightGlomerularFilteringSurfaceAreaBaseline = nullptr;
  m_RightTubularReabsorptionFluidPermeabilityBaseline = nullptr;
  m_RightTubularReabsorptionFilteringSurfaceAreaBaseline = nullptr;
  m_TargetSodiumDelivery = nullptr;
  

  // Respiratory
  m_CentralControllerCO2PressureSetPoint = nullptr;
  m_CentralVentilatoryControllerGain = nullptr;
  m_PeripheralControllerCO2PressureSetPoint = nullptr;
  m_PeripheralVentilatoryControllerGain = nullptr;
  m_PleuralComplianceSensitivity = nullptr;
  m_PulmonaryVentilationRateMaximum = nullptr;
  m_VentilationTidalVolumeIntercept = nullptr;
  m_VentilatoryOcclusionPressure = nullptr;

  // Tissue
  m_TissueEnabled = cdm::eSwitch(-1);
}

PulseConfiguration::~PulseConfiguration()
{
  Clear();
}

void PulseConfiguration::Clear()
{
  PhysiologyEngineConfiguration::Clear();

  // Barorecptors
  SAFE_DELETE(m_ResponseSlope);
  SAFE_DELETE(m_HeartRateDistributedTimeDelay);
  SAFE_DELETE(m_HeartElastanceDistributedTimeDelay);
  SAFE_DELETE(m_SystemicResistanceDistributedTimeDelay);
  SAFE_DELETE(m_VenousComplianceDistributedTimeDelay);
  SAFE_DELETE(m_NormalizedHeartRateIntercept);
  SAFE_DELETE(m_NormalizedHeartRateSympatheticSlope);
  SAFE_DELETE(m_NormalizedHeartRateParasympatheticSlope);
  SAFE_DELETE(m_NormalizedHeartElastanceIntercept);
  SAFE_DELETE(m_NormalizedHeartElastanceSympatheticSlope);
  SAFE_DELETE(m_NormalizedResistanceIntercept);
  SAFE_DELETE(m_NormalizedResistanceSympatheticSlope);
  SAFE_DELETE(m_NormalizedComplianceIntercept);
  SAFE_DELETE(m_NormalizedComplianceParasympatheticSlope);
  
  // Blood Chemistry
  SAFE_DELETE(m_MeanCorpuscularHemoglobin);
  SAFE_DELETE(m_MeanCorpuscularVolume);
  SAFE_DELETE(m_StandardDiffusionDistance);
  SAFE_DELETE(m_StandardOxygenDiffusionCoefficient);

  // Cardiovascular
  SAFE_DELETE(m_LeftHeartElastanceMaximum);
  SAFE_DELETE(m_LeftHeartElastanceMinimum);
  SAFE_DELETE(m_MinimumBloodVolumeFraction);
  SAFE_DELETE(m_RightHeartElastanceMaximum);
  SAFE_DELETE(m_RightHeartElastanceMinimum);
  SAFE_DELETE(m_StandardPulmonaryCapillaryCoverage);

  // Circuit
  SAFE_DELETE(m_CardiovascularOpenResistance);
  SAFE_DELETE(m_DefaultClosedElectricResistance);
  SAFE_DELETE(m_DefaultClosedFlowResistance);
  SAFE_DELETE(m_DefaultClosedHeatResistance);
  SAFE_DELETE(m_DefaultOpenElectricResistance);
  SAFE_DELETE(m_DefaultOpenFlowResistance);
  SAFE_DELETE(m_DefaultOpenHeatResistance);
  SAFE_DELETE(m_MachineClosedResistance);
  SAFE_DELETE(m_MachineOpenResistance);
  SAFE_DELETE(m_RespiratoryClosedResistance);
  SAFE_DELETE(m_RespiratoryOpenResistance);

  // Constants
  SAFE_DELETE(m_OxygenMetabolicConstant);
  SAFE_DELETE(m_StefanBoltzmann);
  SAFE_DELETE(m_UniversalGasConstant);

  // Drugs
  m_PDEnabled = cdm::eSwitch(-1);

  // Energy
  SAFE_DELETE(m_BodySpecificHeat);
  SAFE_DELETE(m_CarbondDioxideProductionFromOxygenConsumptionConstant);
  SAFE_DELETE(m_CoreTemperatureLow);
  SAFE_DELETE(m_CoreTemperatureHigh);
  SAFE_DELETE(m_DeltaCoreTemperatureLow);
  SAFE_DELETE(m_EnergyPerATP);
  SAFE_DELETE(m_SweatHeatTransfer);
  SAFE_DELETE(m_VaporizationEnergy);
  SAFE_DELETE(m_VaporSpecificHeat);

  // Environment
  SAFE_DELETE(m_AirDensity);
  SAFE_DELETE(m_AirSpecificHeat);
  SAFE_DELETE(m_MolarMassOfDryAir);
  SAFE_DELETE(m_MolarMassOfWaterVapor);
  SAFE_DELETE(m_InitialEnvironmentalConditions);
  SAFE_DELETE(m_WaterDensity);

  // Gastrointestinal
  SAFE_DELETE(m_CalciumDigestionRate);
  SAFE_DELETE(m_CalciumAbsorbtionFraction); 
  SAFE_DELETE(m_CarbohydrateAbsorbtionFraction);
  SAFE_DELETE(m_DefaultCarbohydrateDigestionRate);
  SAFE_DELETE(m_DefaultFatDigestionRate);
  SAFE_DELETE(m_DefaultProteinDigestionRate);
  SAFE_DELETE(m_DefaultStomachContents);
  SAFE_DELETE(m_FatAbsorbtionFraction);
  SAFE_DELETE(m_ProteinToUreaFraction);
  SAFE_DELETE(m_WaterDigestionRate);

  // Nervous
  SAFE_DELETE(m_PupilDiameterBaseline);

  // Renal
  m_RenalEnabled = cdm::eSwitch(-1);
  SAFE_DELETE(m_PlasmaSodiumConcentrationSetPoint);
  SAFE_DELETE(m_PeritubularPotassiumConcentrationSetPoint);
  SAFE_DELETE(m_LeftGlomerularFluidPermeabilityBaseline);
  SAFE_DELETE(m_LeftGlomerularFilteringSurfaceAreaBaseline);
  SAFE_DELETE(m_LeftTubularReabsorptionFluidPermeabilityBaseline);
  SAFE_DELETE(m_LeftTubularReabsorptionFilteringSurfaceAreaBaseline);
  SAFE_DELETE(m_MaximumAfferentResistance);
  SAFE_DELETE(m_MinimumAfferentResistance);
  SAFE_DELETE(m_RightGlomerularFluidPermeabilityBaseline);
  SAFE_DELETE(m_RightGlomerularFilteringSurfaceAreaBaseline);
  SAFE_DELETE(m_RightTubularReabsorptionFluidPermeabilityBaseline);
  SAFE_DELETE(m_RightTubularReabsorptionFilteringSurfaceAreaBaseline);
  SAFE_DELETE(m_TargetSodiumDelivery);

  // Respiratory
  SAFE_DELETE(m_CentralControllerCO2PressureSetPoint);
  SAFE_DELETE(m_CentralVentilatoryControllerGain);
  SAFE_DELETE(m_PeripheralControllerCO2PressureSetPoint);
  SAFE_DELETE(m_PeripheralVentilatoryControllerGain);
  SAFE_DELETE(m_PleuralComplianceSensitivity);
  SAFE_DELETE(m_PulmonaryVentilationRateMaximum);
  SAFE_DELETE(m_VentilationTidalVolumeIntercept);
  SAFE_DELETE(m_VentilatoryOcclusionPressure);

  //Tissue
  m_TissueEnabled = cdm::eSwitch(-1);
}


void PulseConfiguration::Initialize()
{
  Clear();
  m_WritePatientBaselineFile = cdm::eSwitch::Off;

  // Reset to default values
  GetECGInterpolator().LoadWaveforms("./ecg/StandardECG.xml");
  GetTimeStep().SetValue(1.0 / 50.0, TimeUnit::s);
  GetDynamicStabilizationCriteria().LoadFile("./config/DynamicStabilization.xml");
  //GetTimedStabilizationCriteria().LoadFile("./config/TimedStabilization.xml");
  //m_StabilizationCriteria->TrackStabilization(true);// Hard coded override for debugging
  
  // Baroreceptors
  GetResponseSlope().SetValue(12.0); //nu
  GetHeartRateDistributedTimeDelay().SetValue(20.0, TimeUnit::s);
  GetHeartElastanceDistributedTimeDelay().SetValue(20.0, TimeUnit::s);
  GetSystemicResistanceDistributedTimeDelay().SetValue(30.0, TimeUnit::s);
  GetVenousComplianceDistributedTimeDelay().SetValue(60.0, TimeUnit::s);
  GetNormalizedHeartRateIntercept().SetValue(0.26); //Gamma Heart Rate
  GetNormalizedHeartRateSympatheticSlope().SetValue(1.73); //Alpha Heart Rate
  GetNormalizedHeartRateParasympatheticSlope().SetValue(0.25); //Beta Heart Rate
  GetNormalizedHeartElastanceIntercept().SetValue(0.95); //Gamma Heart Elastance
  GetNormalizedHeartElastanceSympatheticSlope().SetValue(0.1); //Alpha Elastance
  GetNormalizedResistanceIntercept().SetValue(0.4); //Gamma Resistance
  GetNormalizedResistanceSympatheticSlope().SetValue(1.2); //Alpha Resistance
  GetNormalizedComplianceIntercept().SetValue(0.7); //Gamma Compliance
  GetNormalizedComplianceParasympatheticSlope().SetValue(0.6); //Alpha Compliance

  //Blood Chemistry
  GetMeanCorpuscularVolume().SetValue(9.e-8, VolumeUnit::uL);// Guyton p419
  GetMeanCorpuscularHemoglobin().SetValue(29, MassPerAmountUnit::pg_Per_ct);
  GetStandardDiffusionDistance().SetValue(0.0006, LengthUnit::mm);
  GetStandardOxygenDiffusionCoefficient().SetValue(0.00000000246, AreaPerTimePressureUnit::cm2_Per_min_mmHg);

  // Cardiovascular
  GetLeftHeartElastanceMaximum().SetValue(2.49, FlowElastanceUnit::mmHg_Per_mL);
  GetLeftHeartElastanceMinimum().SetValue(0.049, FlowElastanceUnit::mmHg_Per_mL);
  GetMinimumBloodVolumeFraction().SetValue(0.65); // \cite Guyton 11th ed p.279
  GetRightHeartElastanceMaximum().SetValue(0.523, FlowElastanceUnit::mmHg_Per_mL);
  GetRightHeartElastanceMinimum().SetValue(0.0243, FlowElastanceUnit::mmHg_Per_mL);
  GetStandardPulmonaryCapillaryCoverage().SetValue(0.70);

  // Circuits
  GetCardiovascularOpenResistance().SetValue(100.0, FlowResistanceUnit::mmHg_s_Per_mL);
  GetDefaultOpenElectricResistance().SetValue(1E100, ElectricResistanceUnit::Ohm);
  GetDefaultOpenFlowResistance().SetValue(1E100, FlowResistanceUnit::Pa_s_Per_m3);
  GetDefaultOpenHeatResistance().SetValue(1E100, HeatResistanceUnit::K_Per_W);
  GetDefaultClosedElectricResistance().SetValue(1E-100, ElectricResistanceUnit::Ohm);
  GetDefaultClosedFlowResistance().SetValue(1E-100, FlowResistanceUnit::Pa_s_Per_m3);
  GetDefaultClosedHeatResistance().SetValue(1E-100, HeatResistanceUnit::K_Per_W);
  GetMachineClosedResistance().SetValue(1E-3, FlowResistanceUnit::cmH2O_s_Per_L);
  GetMachineOpenResistance().SetValue(1E3, FlowResistanceUnit::cmH2O_s_Per_L);
  GetRespiratoryClosedResistance().SetValue(1E-3, FlowResistanceUnit::cmH2O_s_Per_L);
  GetRespiratoryOpenResistance().SetValue(1E3, FlowResistanceUnit::cmH2O_s_Per_L);

  // Constants
  GetOxygenMetabolicConstant().SetValue(9.0);
  GetStefanBoltzmann().SetValue(5.670367E-8, PowerPerAreaTemperatureToTheFourthUnit::W_Per_m2_K4);//http://physics.nist.gov/cuu/Constants/
  GetUniversalGasConstant().SetValue(8.3144621, HeatCapacitancePerAmountUnit::J_Per_K_mol); //http://physics.nist.gov/cuu/Constants/

  // Drugs 
  m_PDEnabled = cdm::eSwitch::On;

  // Energy
  GetBodySpecificHeat().SetValue(0.83, HeatCapacitancePerMassUnit::kcal_Per_K_kg);
  GetCarbondDioxideProductionFromOxygenConsumptionConstant().SetValue(0.8);
  GetCoreTemperatureLow().SetValue(36.8, TemperatureUnit::C);
  GetCoreTemperatureHigh().SetValue(37.1, TemperatureUnit::C);
  GetDeltaCoreTemperatureLow().SetValue(1.8, TemperatureUnit::C);
  GetEnergyPerATP().SetValue(7, EnergyPerAmountUnit::kcal_Per_mol);
  GetSweatHeatTransfer().SetValue(0.20833, HeatConductanceUnit::kcal_Per_K_s);
  GetVaporizationEnergy().SetValue(2260.0, EnergyPerMassUnit::kJ_Per_kg);
  GetVaporSpecificHeat().SetValue(1.890, HeatCapacitancePerMassUnit::kJ_Per_K_kg);

  // Environment
  GetAirDensity().SetValue(1.225, MassPerVolumeUnit::kg_Per_m3);
  GetAirSpecificHeat().SetValue(1.0035, HeatCapacitancePerMassUnit::kJ_Per_K_kg);
  GetMolarMassOfDryAir().SetValue(0.028964, MassPerAmountUnit::kg_Per_mol);
  GetMolarMassOfWaterVapor().SetValue(0.018016, MassPerAmountUnit::kg_Per_mol);
  GetInitialEnvironmentalConditions().LoadFile("./environments/Standard.xml");
  GetWaterDensity().SetValue(1000, MassPerVolumeUnit::kg_Per_m3);

  // Gastrointestinal
  GetCalciumAbsorbtionFraction().SetValue(0.25);// Net fractional calcium absorption is 24.9 ± 12.4% (Hunt and Johnson 2007)
  GetCalciumDigestionRate().SetValue(2.7, MassPerTimeUnit::mg_Per_min);// Wasserman1992Intestinal
  GetCarbohydrateAbsorbtionFraction().SetValue(0.80);// Guyton p790
  GetDefaultCarbohydrateDigestionRate().SetValue(0.5, MassPerTimeUnit::g_Per_min);// Guyton (About 4.25hr to digest the carbs in default meal)
  GetDefaultFatDigestionRate().SetValue(0.055, MassPerTimeUnit::g_Per_min);// Guyton (About 8hr to digest the fat in the default meal)
  GetDefaultProteinDigestionRate().SetValue(0.071, MassPerTimeUnit::g_Per_min);// Dangin2001Digestion (About 5hr to digest the protein in the default meal)
  GetDefaultStomachContents().LoadFile("./nutrition/Standard.xml");// Refs are in the data spreadsheet
  GetFatAbsorbtionFraction().SetValue(0.248);// Guyton p797 and the recommended daily value for saturated fat intake according to the AHA //TODO: Add this reference
  // We should be making 30 grams of urea per 100 grams of protein haussinger1990nitrogen
  GetProteinToUreaFraction().SetValue(0.405);// BUT, We should excrete 24.3 g/day on average. Guyton p 328. With an average intake of 60 g/day, that works out to approximately 40%. 
  GetWaterDigestionRate().SetValue(0.417, VolumePerTimeUnit::mL_Per_s);// Peronnet2012Pharmacokinetic, Estimated from 300mL H20 being absorbed in 9.5-12m
  
  // Nervous
  GetPupilDiameterBaseline().SetValue(4, LengthUnit::mm);

  // Renal
  m_RenalEnabled = cdm::eSwitch::On;
  GetPlasmaSodiumConcentrationSetPoint().SetValue(3.23, MassPerVolumeUnit::mg_Per_mL);
  GetPeritubularPotassiumConcentrationSetPoint().SetValue(0.0185, MassPerVolumeUnit::g_Per_dL);
  GetLeftGlomerularFluidPermeabilityBaseline().SetValue(3.67647, VolumePerTimePressureAreaUnit::mL_Per_min_mmHg_m2);
  GetLeftGlomerularFilteringSurfaceAreaBaseline().SetValue(2.0, AreaUnit::m2);
  GetLeftTubularReabsorptionFluidPermeabilityBaseline().SetValue(2.91747, VolumePerTimePressureAreaUnit::mL_Per_min_mmHg_m2);
  GetLeftTubularReabsorptionFilteringSurfaceAreaBaseline().SetValue(2.5, AreaUnit::m2);
  GetMaximumAfferentResistance().SetValue(11.2, FlowResistanceUnit::mmHg_s_Per_mL);  //11.2
  GetMinimumAfferentResistance().SetValue(2.2, FlowResistanceUnit::mmHg_s_Per_mL);  //2.1 
  GetRightGlomerularFluidPermeabilityBaseline().SetValue(3.67647, VolumePerTimePressureAreaUnit::mL_Per_min_mmHg_m2);
  GetRightGlomerularFilteringSurfaceAreaBaseline().SetValue(2.0, AreaUnit::m2);
  GetRightTubularReabsorptionFluidPermeabilityBaseline().SetValue(2.91747, VolumePerTimePressureAreaUnit::mL_Per_min_mmHg_m2);
  //GetRightTubularReabsorptionFluidPermeabilityBaseline().SetValue(1.0, VolumePerTimePressureAreaUnit::mL_Per_min_Per_mmHg_Per_m2);
  GetRightTubularReabsorptionFilteringSurfaceAreaBaseline().SetValue(2.5, AreaUnit::m2);
  GetTargetSodiumDelivery().SetValue(0.201, MassPerTimeUnit::g_Per_min);

  // Respiratory
  GetCentralControllerCO2PressureSetPoint().SetValue(35.5, PressureUnit::mmHg);
  GetCentralVentilatoryControllerGain().SetValue(1.44); //How much to add to the amplitude when the CO2 is off
  GetPeripheralControllerCO2PressureSetPoint().SetValue(35.5, PressureUnit::mmHg);
  GetPeripheralVentilatoryControllerGain().SetValue(30.24); //How much to add to the amplitude when the CO2 is off
  GetPleuralComplianceSensitivity().SetValue(5.0, InverseVolumeUnit::Inverse_L);
  GetPulmonaryVentilationRateMaximum().SetValue(150.0, VolumePerTimeUnit::L_Per_min);
  GetVentilationTidalVolumeIntercept().SetValue(0.3, VolumeUnit::L);
  GetVentilatoryOcclusionPressure().SetValue(0.75, PressureUnit::cmH2O); //This increases the absolute max driver pressure

  // Tissue
  m_TissueEnabled = cdm::eSwitch::On;
}

void PulseConfiguration::Merge(const PhysiologyEngineConfiguration& from)
{
  const PulseConfiguration* bgConfig = dynamic_cast<const PulseConfiguration*>(&from);
  if (bgConfig != nullptr)
    Merge(*bgConfig);
  else
    PhysiologyEngineConfiguration::Merge(from);
}

void PulseConfiguration::Merge(const PulseConfiguration& from)
{
    m_Merge = true;
    CDM_COPY((&from), this);
    m_Merge = false;
}

bool PulseConfiguration::LoadFile(const std::string& file)
{
  // if file does not exist, we stick with defaults

  CDM::PulseConfigurationData* pData;
  std::unique_ptr<CDM::ObjectData> data;

  data = Serializer::ReadFile(file,GetLogger());
  pData = dynamic_cast<CDM::PulseConfigurationData*>(data.get());
  if (pData == nullptr)
  {
    std::stringstream ss;
    ss << "Configuration file : " << file << " not found, using default configuration" << std::endl;
    Info(ss);
    return true;
  }
  return Load(*pData);
}

bool PulseConfiguration::Load(const CDM::PhysiologyEngineConfigurationData& from)
{
  const CDM::PulseConfigurationData* bgConfig = dynamic_cast<const CDM::PulseConfigurationData*>(&from);
  if (bgConfig != nullptr)
    return Load(*bgConfig);
  else
    return PhysiologyEngineConfiguration::Load(from);
}

bool PulseConfiguration::Load(const CDM::PulseConfigurationData& in)
{
  PhysiologyEngineConfiguration::Load(in);

  //Barorecptors
  if (in.BaroreceptorConfiguration().present())
  {
    const CDM::BaroreceptorConfigurationData& config = in.BaroreceptorConfiguration().get();
    if (config.ResponseSlope().present())
      GetResponseSlope().Load(config.ResponseSlope().get());
    if (config.HeartRateDistributedTimeDelay().present())
      GetHeartRateDistributedTimeDelay().Load(config.HeartRateDistributedTimeDelay().get());
    if (config.HeartElastanceDistributedTimeDelay().present())
      GetHeartElastanceDistributedTimeDelay().Load(config.HeartElastanceDistributedTimeDelay().get());
    if (config.SystemicResistanceDistributedTimeDelay().present())
      GetSystemicResistanceDistributedTimeDelay().Load(config.SystemicResistanceDistributedTimeDelay().get());
    if (config.VenousComplianceDistributedTimeDelay().present())
      GetVenousComplianceDistributedTimeDelay().Load(config.VenousComplianceDistributedTimeDelay().get());
    if (config.NormalizedHeartRateIntercept().present())
      GetNormalizedHeartRateIntercept().Load(config.NormalizedHeartRateIntercept().get());
    if (config.NormalizedHeartRateSympatheticSlope().present())
      GetNormalizedHeartRateSympatheticSlope().Load(config.NormalizedHeartRateSympatheticSlope().get());
    if (config.NormalizedHeartRateParasympatheticSlope().present())
      GetNormalizedHeartRateParasympatheticSlope().Load(config.NormalizedHeartRateParasympatheticSlope().get());
    if (config.NormalizedHeartElastanceIntercept().present())
      GetNormalizedHeartElastanceIntercept().Load(config.NormalizedHeartElastanceIntercept().get());
    if (config.NormalizedHeartElastanceSympatheticSlope().present())
      GetNormalizedHeartElastanceSympatheticSlope().Load(config.NormalizedHeartElastanceSympatheticSlope().get());
    if (config.NormalizedResistanceIntercept().present())
      GetNormalizedResistanceIntercept().Load(config.NormalizedResistanceIntercept().get());
    if (config.NormalizedResistanceSympatheticSlope().present())
      GetNormalizedResistanceSympatheticSlope().Load(config.NormalizedResistanceSympatheticSlope().get());
    if (config.NormalizedComplianceIntercept().present())
      GetNormalizedComplianceIntercept().Load(config.NormalizedComplianceIntercept().get());
    if (config.NormalizedComplianceParasympatheticSlope().present())
      GetNormalizedComplianceParasympatheticSlope().Load(config.NormalizedComplianceParasympatheticSlope().get());
  }

  // Blood Chemistry
  if (in.BloodChemistryConfiguration().present())
  {
    const CDM::BloodChemistryConfigurationData& config = in.BloodChemistryConfiguration().get();
    if (config.MeanCorpuscularVolume().present())
      GetMeanCorpuscularVolume().Load(config.MeanCorpuscularVolume().get());
    if (config.MeanCorpuscularHemoglobin().present())
      GetMeanCorpuscularHemoglobin().Load(config.MeanCorpuscularHemoglobin().get());
    if (config.StandardDiffusionDistance().present())
      GetStandardDiffusionDistance().Load(config.StandardDiffusionDistance().get());
    if (config.StandardOxygenDiffusionCoefficient().present())
      GetStandardOxygenDiffusionCoefficient().Load(config.StandardOxygenDiffusionCoefficient().get());
  }

  // Cardiovascular
  if (in.CardiovascularConfiguration().present())
  {
    const CDM::CardiovascularConfigurationData& config = in.CardiovascularConfiguration().get();
    if (config.LeftHeartElastanceMaximum().present())
      GetLeftHeartElastanceMaximum().Load(config.LeftHeartElastanceMaximum().get());
    if (config.LeftHeartElastanceMinimum().present())
      GetLeftHeartElastanceMinimum().Load(config.LeftHeartElastanceMinimum().get());
    if (config.MinimumBloodVolumeFraction().present())
      GetMinimumBloodVolumeFraction().Load(config.MinimumBloodVolumeFraction().get());
    if (config.RightHeartElastanceMaximum().present())
      GetRightHeartElastanceMaximum().Load(config.RightHeartElastanceMaximum().get());
    if (config.RightHeartElastanceMinimum().present())
      GetRightHeartElastanceMinimum().Load(config.RightHeartElastanceMinimum().get());
    if (config.StandardPulmonaryCapillaryCoverage().present())
      GetStandardPulmonaryCapillaryCoverage().Load(config.StandardPulmonaryCapillaryCoverage().get());
  }

  // Circuit
  if (in.CircuitConfiguration().present())
  {
    const CDM::CircuitConfigurationData& config = in.CircuitConfiguration().get();
    if (config.CardiovascularOpenResistance().present())
      GetCardiovascularOpenResistance().Load(config.CardiovascularOpenResistance().get());
    if (config.DefaultOpenElectricResistance().present())
      GetDefaultOpenElectricResistance().Load(config.DefaultOpenElectricResistance().get());
    if (config.DefaultOpenFlowResistance().present())
      GetDefaultOpenFlowResistance().Load(config.DefaultOpenFlowResistance().get());
    if (config.DefaultOpenHeatResistance().present())
      GetDefaultOpenHeatResistance().Load(config.DefaultOpenHeatResistance().get());
    if (config.DefaultClosedElectricResistance().present())
      GetDefaultClosedElectricResistance().Load(config.DefaultClosedElectricResistance().get());
    if (config.DefaultClosedFlowResistance().present())
      GetDefaultClosedFlowResistance().Load(config.DefaultClosedFlowResistance().get());
    if (config.DefaultClosedHeatResistance().present())
      GetDefaultClosedHeatResistance().Load(config.DefaultClosedHeatResistance().get());
    if (config.MachineClosedResistance().present())
      GetMachineClosedResistance().Load(config.MachineClosedResistance().get());
    if (config.MachineOpenResistance().present())
      GetMachineOpenResistance().Load(config.MachineOpenResistance().get());
    if (config.RespiratoryClosedResistance().present())
      GetRespiratoryClosedResistance().Load(config.RespiratoryClosedResistance().get());
    if (config.RespiratoryOpenResistance().present())
      GetRespiratoryOpenResistance().Load(config.RespiratoryOpenResistance().get());
  }

  // Constants
  if (in.ConstantsConfiguration().present())
  {
    const CDM::ConstantsConfigurationData& config = in.ConstantsConfiguration().get();
    if (config.OxygenMetabolicConstant().present())
      GetOxygenMetabolicConstant().Load(config.OxygenMetabolicConstant().get());
    if (config.StefanBoltzmann().present())
      GetStefanBoltzmann().Load(config.StefanBoltzmann().get());
    if (config.UniversalGasConstant().present())
      GetUniversalGasConstant().Load(config.UniversalGasConstant().get());
  }

  // Drugs
  if (in.DrugsConfiguration().present())
  {
    const CDM::DrugsConfigurationData& config = in.DrugsConfiguration().get();
    if(config.PDModel().present())
      UsePDModel(config.PDModel().get());
  }
  
  // Energy
  if (in.EnergyConfiguration().present())
  {
    const CDM::EnergyConfigurationData& config = in.EnergyConfiguration().get();
    if (config.BodySpecificHeat().present())
      GetBodySpecificHeat().Load(config.BodySpecificHeat().get());
    if (config.CarbonDioxideProductionFromOxygenConsumptionConstant().present())
      GetCarbondDioxideProductionFromOxygenConsumptionConstant().Load(config.CarbonDioxideProductionFromOxygenConsumptionConstant().get());
    if (config.CoreTemperatureLow().present())
      GetCoreTemperatureLow().Load(config.CoreTemperatureLow().get());
    if (config.CoreTemperatureHigh().present())
      GetCoreTemperatureHigh().Load(config.CoreTemperatureHigh().get());
    if (config.DeltaCoreTemperatureLow().present())
      GetDeltaCoreTemperatureLow().Load(config.DeltaCoreTemperatureLow().get());
    if (config.EnergyPerATP().present())
      GetEnergyPerATP().Load(config.EnergyPerATP().get());
    if (config.SweatHeatTransfer().present())
      GetSweatHeatTransfer().Load(config.SweatHeatTransfer().get());
    if (config.VaporizationEnergy().present())
      GetVaporizationEnergy().Load(config.VaporizationEnergy().get());
    if (config.VaporSpecificHeat().present())
      GetVaporSpecificHeat().Load(config.VaporSpecificHeat().get());
  }

  // Environment
  if (in.EnvironmentConfiguration().present())
  {
    const CDM::EnvironmentConfigurationData& config = in.EnvironmentConfiguration().get();
    if (config.AirDensity().present())
      GetAirDensity().Load(config.AirDensity().get());
    if (config.AirSpecificHeat().present())
      GetAirSpecificHeat().Load(config.AirSpecificHeat().get());
    if (config.MolarMassOfDryAir().present())
      GetMolarMassOfDryAir().Load(config.MolarMassOfDryAir().get());
    if (config.MolarMassOfWaterVapor().present())
      GetMolarMassOfWaterVapor().Load(config.MolarMassOfWaterVapor().get());
    if (config.InitialEnvironmentalConditionsFile().present())
    {
      if (!GetInitialEnvironmentalConditions().LoadFile(config.InitialEnvironmentalConditionsFile().get()))
      {
        Error("Unable to load InitialEnvironmentalConditions file");
        return false;
      }
    }
    else if (config.InitialEnvironmentalConditions().present())
    {
      if (!GetInitialEnvironmentalConditions().Load(config.InitialEnvironmentalConditions().get()))
      {
        Error("Unable to load InitialEnvironmentalConditions");
        return false;
      }
    }
    if (config.WaterDensity().present())
      GetWaterDensity().Load(config.WaterDensity().get());
  }

  // Gastrointestinal
  if (in.GastrointestinalConfiguration().present())
  {
    const CDM::GastrointestinalConfigurationData& config = in.GastrointestinalConfiguration().get();
    if (config.CalciumAbsorbtionFraction().present())
      GetCalciumAbsorbtionFraction().Load(config.CalciumAbsorbtionFraction().get());
    if (config.CalciumDigestionRate().present())
      GetCalciumDigestionRate().Load(config.CalciumDigestionRate().get());
    if (config.CarbohydrateAbsorbtionFraction().present())
      GetCarbohydrateAbsorbtionFraction().Load(config.CarbohydrateAbsorbtionFraction().get());
    if (config.DefaultCarbohydrateDigestionRate().present())
      GetDefaultCarbohydrateDigestionRate().Load(config.DefaultCarbohydrateDigestionRate().get());
    if (config.DefaultFatDigestionRate().present())
      GetDefaultFatDigestionRate().Load(config.DefaultFatDigestionRate().get());
    if (config.DefaultProteinDigestionRate().present())
      GetDefaultProteinDigestionRate().Load(config.DefaultProteinDigestionRate().get());
    if (config.DefaultStomachContentsFile().present())
    {
      if(!GetDefaultStomachContents().LoadFile(config.DefaultStomachContentsFile().get()))
      {
        Error("Unable to load Standard Stomach Contents file");
        return false;
      }
    }
    else if (config.DefaultStomachContents().present())
    {
      if(!GetDefaultStomachContents().Load(config.DefaultStomachContents().get()))
      {
        Error("Unable to load Standard Stomach Contents");
        return false;
      }
    }
    // Use default rate if they are not set
    {
      if (m_DefaultStomachContents->HasCarbohydrate() && !m_DefaultStomachContents->HasCarbohydrateDigestionRate())
        m_DefaultStomachContents->GetCarbohydrateDigestionRate().Set(GetDefaultCarbohydrateDigestionRate());
      if (m_DefaultStomachContents->HasFat() && !m_DefaultStomachContents->HasFatDigestionRate())
        m_DefaultStomachContents->GetFatDigestionRate().Set(GetDefaultFatDigestionRate());
      if (m_DefaultStomachContents->HasProtein() && !m_DefaultStomachContents->HasProteinDigestionRate())
        m_DefaultStomachContents->GetProteinDigestionRate().Set(GetDefaultProteinDigestionRate());
    }
    if (config.FatAbsorbtionFraction().present())
      GetFatAbsorbtionFraction().Load(config.FatAbsorbtionFraction().get());
    if (config.ProteinToUreaFraction().present())
      GetProteinToUreaFraction().Load(config.ProteinToUreaFraction().get());
    if (config.WaterDigestionRate().present())
      GetWaterDigestionRate().Load(config.WaterDigestionRate().get());
  }

  // Nervous
  if (in.NervousConfiguration().present())
  {
    const CDM::NervousConfigurationData& config = in.NervousConfiguration().get();
    if (config.PupilDiameterBaseline().present())
      GetPupilDiameterBaseline().Load(config.PupilDiameterBaseline().get());
  }

  // Renal
  if (in.RenalConfiguration().present())
  {
    const CDM::RenalConfigurationData& config = in.RenalConfiguration().get();

    if (config.EnableRenal().present())
      EnableRenal(config.EnableRenal().get());    

    if (config.PlasmaSodiumConcentrationSetPoint().present())
      GetPlasmaSodiumConcentrationSetPoint().Load(config.PlasmaSodiumConcentrationSetPoint().get());

    if (config.LeftGlomerularFluidPermeabilityBaseline().present())
      GetLeftGlomerularFluidPermeabilityBaseline().Load(config.LeftGlomerularFluidPermeabilityBaseline().get());
    if (config.LeftGlomerularFilteringSurfaceAreaBaseline().present())
      GetLeftGlomerularFilteringSurfaceAreaBaseline().Load(config.LeftGlomerularFilteringSurfaceAreaBaseline().get());
    if (config.LeftTubularReabsorptionFluidPermeabilityBaseline().present())
      GetLeftTubularReabsorptionFluidPermeabilityBaseline().Load(config.LeftTubularReabsorptionFluidPermeabilityBaseline().get());
    if (config.LeftTubularReabsorptionFilteringSurfaceAreaBaseline().present())
      GetLeftTubularReabsorptionFilteringSurfaceAreaBaseline().Load(config.LeftTubularReabsorptionFilteringSurfaceAreaBaseline().get());
    
    if (config.MaximumAfferentResistance().present())
      GetMaximumAfferentResistance().Load(config.MaximumAfferentResistance().get());
    if (config.MinimumAfferentResistance().present())
      GetMinimumAfferentResistance().Load(config.MinimumAfferentResistance().get());
      
    if (config.RightGlomerularFluidPermeabilityBaseline().present())
      GetRightGlomerularFluidPermeabilityBaseline().Load(config.RightGlomerularFluidPermeabilityBaseline().get());
    if (config.RightGlomerularFilteringSurfaceAreaBaseline().present())
      GetRightGlomerularFilteringSurfaceAreaBaseline().Load(config.RightGlomerularFilteringSurfaceAreaBaseline().get());
    if (config.RightTubularReabsorptionFluidPermeabilityBaseline().present())
      GetRightTubularReabsorptionFluidPermeabilityBaseline().Load(config.RightTubularReabsorptionFluidPermeabilityBaseline().get());
    if (config.RightTubularReabsorptionFilteringSurfaceAreaBaseline().present())
      GetRightTubularReabsorptionFilteringSurfaceAreaBaseline().Load(config.RightTubularReabsorptionFilteringSurfaceAreaBaseline().get());
    if (config.TargetSodiumDelivery().present())
      GetTargetSodiumDelivery().Load(config.TargetSodiumDelivery().get());

  }
  
  // Respiratory
  if (in.RespiratoryConfiguration().present())
  {
    const CDM::RespiratoryConfigurationData& config = in.RespiratoryConfiguration().get();
    if (config.CentralControllerCO2PressureSetPoint().present())
      GetCentralControllerCO2PressureSetPoint().Load(config.CentralControllerCO2PressureSetPoint().get());
    if (config.CentralVentilatoryControllerGain().present())
      GetCentralVentilatoryControllerGain().Load(config.CentralVentilatoryControllerGain().get());
    if (config.PeripheralControllerCO2PressureSetPoint().present())
      GetPeripheralControllerCO2PressureSetPoint().Load(config.PeripheralControllerCO2PressureSetPoint().get());
    if (config.PeripheralVentilatoryControllerGain().present())
      GetPeripheralVentilatoryControllerGain().Load(config.PeripheralVentilatoryControllerGain().get());
    if (config.PleuralComplianceSensitivity().present())
      GetPleuralComplianceSensitivity().Load(config.PleuralComplianceSensitivity().get());
    if (config.PulmonaryVentilationRateMaximum().present())
      GetPulmonaryVentilationRateMaximum().Load(config.PulmonaryVentilationRateMaximum().get());
    if (config.VentilationTidalVolumeIntercept().present())
      GetVentilationTidalVolumeIntercept().Load(config.VentilationTidalVolumeIntercept().get());
    if (config.VentilatoryOcclusionPressure().present())
      GetVentilatoryOcclusionPressure().Load(config.VentilatoryOcclusionPressure().get());
  }

  // Tissue
  if (in.TissueConfiguration().present())
  {
    const CDM::TissueConfigurationData& config = in.TissueConfiguration().get();

    if (config.EnableTissue().present())
      EnableTissue(config.EnableTissue().get());
  }

  return true;
}

CDM::PulseConfigurationData* PulseConfiguration::Unload() const
{
  CDM::PulseConfigurationData* data(new CDM::PulseConfigurationData());
  Unload(*data);
  return data;
}

void PulseConfiguration::Unload(CDM::PulseConfigurationData& data) const
{
  PhysiologyEngineConfiguration::Unload(data);

  // Barorecptor
  CDM::BaroreceptorConfigurationData* baro(new CDM::BaroreceptorConfigurationData());
  if (HasResponseSlope())
    baro->ResponseSlope(std::unique_ptr<CDM::ScalarData>(m_ResponseSlope->Unload()));
  if (HasHeartRateDistributedTimeDelay())
    baro->HeartRateDistributedTimeDelay(std::unique_ptr<CDM::ScalarTimeData>(m_HeartRateDistributedTimeDelay->Unload()));
  if (HasHeartElastanceDistributedTimeDelay())
    baro->HeartElastanceDistributedTimeDelay(std::unique_ptr<CDM::ScalarTimeData>(m_HeartElastanceDistributedTimeDelay->Unload()));
  if (HasSystemicResistanceDistributedTimeDelay())
    baro->SystemicResistanceDistributedTimeDelay(std::unique_ptr<CDM::ScalarTimeData>(m_SystemicResistanceDistributedTimeDelay->Unload()));
  if (HasVenousComplianceDistributedTimeDelay())
    baro->VenousComplianceDistributedTimeDelay(std::unique_ptr<CDM::ScalarTimeData>(m_VenousComplianceDistributedTimeDelay->Unload()));
  if (HasNormalizedHeartRateIntercept())
    baro->NormalizedHeartRateIntercept(std::unique_ptr<CDM::ScalarData>(m_NormalizedHeartRateIntercept->Unload()));
  if (HasNormalizedHeartRateSympatheticSlope())
    baro->NormalizedHeartRateSympatheticSlope(std::unique_ptr<CDM::ScalarData>(m_NormalizedHeartRateSympatheticSlope->Unload()));
  if (HasNormalizedHeartRateParasympatheticSlope())
    baro->NormalizedHeartRateParasympatheticSlope(std::unique_ptr<CDM::ScalarData>(m_NormalizedHeartRateParasympatheticSlope->Unload()));
  if (HasNormalizedHeartElastanceIntercept())
    baro->NormalizedHeartElastanceIntercept(std::unique_ptr<CDM::ScalarData>(m_NormalizedHeartElastanceIntercept->Unload()));
  if (HasNormalizedHeartElastanceSympatheticSlope())
    baro->NormalizedHeartElastanceSympatheticSlope(std::unique_ptr<CDM::ScalarData>(m_NormalizedHeartElastanceSympatheticSlope->Unload()));
  if (HasNormalizedResistanceIntercept())
    baro->NormalizedResistanceIntercept(std::unique_ptr<CDM::ScalarData>(m_NormalizedResistanceIntercept->Unload()));
  if (HasNormalizedResistanceSympatheticSlope())
    baro->NormalizedResistanceSympatheticSlope(std::unique_ptr<CDM::ScalarData>(m_NormalizedResistanceSympatheticSlope->Unload()));
  if (HasNormalizedComplianceIntercept())
    baro->NormalizedComplianceIntercept(std::unique_ptr<CDM::ScalarData>(m_NormalizedComplianceIntercept->Unload()));
  if (HasNormalizedComplianceParasympatheticSlope())
    baro->NormalizedComplianceParasympatheticSlope(std::unique_ptr<CDM::ScalarData>(m_NormalizedComplianceParasympatheticSlope->Unload()));  
  data.BaroreceptorConfiguration(std::unique_ptr<CDM::BaroreceptorConfigurationData>(baro));

  // Blood Chemistry
  CDM::BloodChemistryConfigurationData* bc(new CDM::BloodChemistryConfigurationData());
  if (HasMeanCorpuscularHemoglobin())
    bc->MeanCorpuscularHemoglobin(std::unique_ptr<CDM::ScalarMassPerAmountData>(m_MeanCorpuscularHemoglobin->Unload()));
  if (HasMeanCorpuscularVolume())
    bc->MeanCorpuscularVolume(std::unique_ptr<CDM::ScalarVolumeData>(m_MeanCorpuscularVolume->Unload()));
  if (HasStandardDiffusionDistance())
    bc->StandardDiffusionDistance(std::unique_ptr<CDM::ScalarLengthData>(m_StandardDiffusionDistance->Unload()));
  if (HasStandardOxygenDiffusionCoefficient())
    bc->StandardOxygenDiffusionCoefficient(std::unique_ptr<CDM::ScalarAreaPerTimePressureData>(m_StandardOxygenDiffusionCoefficient->Unload()));
  data.BloodChemistryConfiguration(std::unique_ptr<CDM::BloodChemistryConfigurationData>(bc));

  // Cardiovascular
  CDM::CardiovascularConfigurationData* cv(new CDM::CardiovascularConfigurationData());
  if (m_LeftHeartElastanceMaximum != nullptr)
    cv->LeftHeartElastanceMaximum(std::unique_ptr<CDM::ScalarFlowElastanceData>(m_LeftHeartElastanceMaximum->Unload()));
  if (m_LeftHeartElastanceMinimum != nullptr)
    cv->LeftHeartElastanceMinimum(std::unique_ptr<CDM::ScalarFlowElastanceData>(m_LeftHeartElastanceMinimum->Unload()));
  if (HasMinimumBloodVolumeFraction())
    cv->MinimumBloodVolumeFraction(std::unique_ptr<CDM::ScalarFractionData>(m_MinimumBloodVolumeFraction->Unload()));
  if (m_RightHeartElastanceMaximum != nullptr)
    cv->RightHeartElastanceMaximum(std::unique_ptr<CDM::ScalarFlowElastanceData>(m_RightHeartElastanceMaximum->Unload()));
  if (m_RightHeartElastanceMinimum != nullptr)
    cv->RightHeartElastanceMinimum(std::unique_ptr<CDM::ScalarFlowElastanceData>(m_RightHeartElastanceMinimum->Unload()));
  if (HasStandardPulmonaryCapillaryCoverage())
    cv->StandardPulmonaryCapillaryCoverage(std::unique_ptr<CDM::ScalarData>(m_StandardPulmonaryCapillaryCoverage->Unload()));
  data.CardiovascularConfiguration(std::unique_ptr<CDM::CardiovascularConfigurationData>(cv));

  // Circuits
  CDM::CircuitConfigurationData* circuit(new CDM::CircuitConfigurationData());
  if (HasCardiovascularOpenResistance())
    circuit->CardiovascularOpenResistance(std::unique_ptr<CDM::ScalarFlowResistanceData>(m_CardiovascularOpenResistance->Unload()));
  if (HasDefaultClosedElectricResistance())
    circuit->DefaultClosedElectricResistance(std::unique_ptr<CDM::ScalarElectricResistanceData>(m_DefaultClosedElectricResistance->Unload()));
  if (HasDefaultClosedFlowResistance())
    circuit->DefaultClosedFlowResistance(std::unique_ptr<CDM::ScalarFlowResistanceData>(m_DefaultClosedFlowResistance->Unload()));
  if (HasDefaultClosedHeatResistance())
    circuit->DefaultClosedHeatResistance(std::unique_ptr<CDM::ScalarHeatResistanceData>(m_DefaultClosedHeatResistance->Unload()));
  if (HasDefaultOpenElectricResistance())
    circuit->DefaultOpenElectricResistance(std::unique_ptr<CDM::ScalarElectricResistanceData>(m_DefaultOpenElectricResistance->Unload()));
  if (HasDefaultOpenFlowResistance())
    circuit->DefaultOpenFlowResistance(std::unique_ptr<CDM::ScalarFlowResistanceData>(m_DefaultOpenFlowResistance->Unload()));
  if (HasDefaultOpenHeatResistance())
    circuit->DefaultOpenHeatResistance(std::unique_ptr<CDM::ScalarHeatResistanceData>(m_DefaultOpenHeatResistance->Unload()));
  if (HasMachineClosedResistance())
    circuit->MachineClosedResistance(std::unique_ptr<CDM::ScalarFlowResistanceData>(m_MachineClosedResistance->Unload()));
  if (HasMachineOpenResistance())
    circuit->MachineOpenResistance(std::unique_ptr<CDM::ScalarFlowResistanceData>(m_MachineOpenResistance->Unload()));
  if (HasRespiratoryClosedResistance())
    circuit->RespiratoryClosedResistance(std::unique_ptr<CDM::ScalarFlowResistanceData>(m_RespiratoryClosedResistance->Unload()));
  if (HasRespiratoryOpenResistance())
    circuit->RespiratoryOpenResistance(std::unique_ptr<CDM::ScalarFlowResistanceData>(m_RespiratoryOpenResistance->Unload()));
  data.CircuitConfiguration(std::unique_ptr<CDM::CircuitConfigurationData>(circuit));

  // Constants
  CDM::ConstantsConfigurationData* consts(new CDM::ConstantsConfigurationData());
  if (HasOxygenMetabolicConstant())
    consts->OxygenMetabolicConstant(std::unique_ptr<CDM::ScalarData>(m_OxygenMetabolicConstant->Unload()));
  if (HasStefanBoltzmann())
    consts->StefanBoltzmann(std::unique_ptr<CDM::ScalarPowerPerAreaTemperatureToTheFourthData>(m_StefanBoltzmann->Unload()));
  if (HasUniversalGasConstant())
    consts->UniversalGasConstant(std::unique_ptr<CDM::ScalarHeatCapacitancePerAmountData>(m_UniversalGasConstant->Unload()));
  data.ConstantsConfiguration(std::unique_ptr<CDM::ConstantsConfigurationData>(consts));

  // Drugs
  CDM::DrugsConfigurationData* drugs(new CDM::DrugsConfigurationData());
  if(HasUsePDModel())
    drugs->PDModel(m_PDEnabled);
  data.DrugsConfiguration(std::unique_ptr<CDM::DrugsConfigurationData>(drugs));

  // Energy
  CDM::EnergyConfigurationData* energy(new CDM::EnergyConfigurationData());
  if (HasBodySpecificHeat())
    energy->BodySpecificHeat(std::unique_ptr<CDM::ScalarHeatCapacitancePerMassData>(m_BodySpecificHeat->Unload()));
  if (HasCarbondDioxideProductionFromOxygenConsumptionConstant())
    energy->CarbonDioxideProductionFromOxygenConsumptionConstant(std::unique_ptr<CDM::ScalarData>(m_CarbondDioxideProductionFromOxygenConsumptionConstant->Unload()));
  if (HasCoreTemperatureLow())
    energy->CoreTemperatureLow(std::unique_ptr<CDM::ScalarTemperatureData>(m_CoreTemperatureLow->Unload()));
  if (HasCoreTemperatureHigh())
    energy->CoreTemperatureHigh(std::unique_ptr<CDM::ScalarTemperatureData>(m_CoreTemperatureHigh->Unload()));
  if (HasDeltaCoreTemperatureLow())
    energy->DeltaCoreTemperatureLow(std::unique_ptr<CDM::ScalarTemperatureData>(m_DeltaCoreTemperatureLow->Unload()));
  if (HasEnergyPerATP())
    energy->EnergyPerATP(std::unique_ptr<CDM::ScalarEnergyPerAmountData>(m_EnergyPerATP->Unload()));
  if (HasSweatHeatTransfer())
    energy->SweatHeatTransfer(std::unique_ptr<CDM::ScalarHeatConductanceData>(m_SweatHeatTransfer->Unload()));
  if (HasVaporSpecificHeat())
    energy->VaporSpecificHeat(std::unique_ptr<CDM::ScalarHeatCapacitancePerMassData>(m_VaporSpecificHeat->Unload()));
  if (HasVaporizationEnergy())
    energy->VaporizationEnergy(std::unique_ptr<CDM::ScalarEnergyPerMassData>(m_VaporizationEnergy->Unload()));
  data.EnergyConfiguration(std::unique_ptr<CDM::EnergyConfigurationData>(energy));

  // Environment
  CDM::EnvironmentConfigurationData* env(new CDM::EnvironmentConfigurationData());
  if (HasAirDensity())
    env->AirDensity(std::unique_ptr<CDM::ScalarMassPerVolumeData>(m_AirDensity->Unload()));
  if (HasAirSpecificHeat())
    env->AirSpecificHeat(std::unique_ptr<CDM::ScalarHeatCapacitancePerMassData>(m_AirSpecificHeat->Unload()));
  if (HasMolarMassOfDryAir())
    env->MolarMassOfDryAir(std::unique_ptr<CDM::ScalarMassPerAmountData>(m_MolarMassOfDryAir->Unload()));
  if (HasMolarMassOfWaterVapor())
    env->MolarMassOfWaterVapor(std::unique_ptr<CDM::ScalarMassPerAmountData>(m_MolarMassOfWaterVapor->Unload()));
  if (HasInitialEnvironmentalConditions())
    env->InitialEnvironmentalConditions(std::unique_ptr<CDM::EnvironmentalConditionsData>(m_InitialEnvironmentalConditions->Unload()));
  if (HasWaterDensity())
    env->WaterDensity(std::unique_ptr<CDM::ScalarMassPerVolumeData>(m_WaterDensity->Unload()));
  data.EnvironmentConfiguration(std::unique_ptr<CDM::EnvironmentConfigurationData>(env));

  // Gastrointestinal
  CDM::GastrointestinalConfigurationData* gi(new CDM::GastrointestinalConfigurationData());
  if (HasCalciumAbsorbtionFraction())
    gi->CalciumAbsorbtionFraction(std::unique_ptr<CDM::ScalarFractionData>(m_CalciumAbsorbtionFraction->Unload()));
  if (HasCalciumDigestionRate())
    gi->CalciumDigestionRate(std::unique_ptr<CDM::ScalarMassPerTimeData>(m_CalciumDigestionRate->Unload()));
  if (HasCarbohydrateAbsorbtionFraction())
    gi->CarbohydrateAbsorbtionFraction(std::unique_ptr<CDM::ScalarFractionData>(m_CarbohydrateAbsorbtionFraction->Unload()));
  if (HasDefaultCarbohydrateDigestionRate())
    gi->DefaultCarbohydrateDigestionRate(std::unique_ptr<CDM::ScalarMassPerTimeData>(m_DefaultCarbohydrateDigestionRate->Unload()));
  if (HasDefaultFatDigestionRate())
    gi->DefaultFatDigestionRate(std::unique_ptr<CDM::ScalarMassPerTimeData>(m_DefaultFatDigestionRate->Unload()));
  if (HasDefaultProteinDigestionRate())
    gi->DefaultProteinDigestionRate(std::unique_ptr<CDM::ScalarMassPerTimeData>(m_DefaultProteinDigestionRate->Unload()));
  if (HasDefaultStomachContents())
    gi->DefaultStomachContents(std::unique_ptr<CDM::NutritionData>(m_DefaultStomachContents->Unload()));
  if (HasFatAbsorbtionFraction())
    gi->FatAbsorbtionFraction(std::unique_ptr<CDM::ScalarFractionData>(m_FatAbsorbtionFraction->Unload()));
  if (HasProteinToUreaFraction())
    gi->ProteinToUreaFraction(std::unique_ptr<CDM::ScalarFractionData>(m_ProteinToUreaFraction->Unload()));
  if (HasWaterDigestionRate())
    gi->WaterDigestionRate(std::unique_ptr<CDM::ScalarVolumePerTimeData>(m_WaterDigestionRate->Unload()));
  data.GastrointestinalConfiguration(std::unique_ptr<CDM::GastrointestinalConfigurationData>(gi));

  // Nervous
  CDM::NervousConfigurationData* n(new CDM::NervousConfigurationData());
  if (HasPupilDiameterBaseline())
    n->PupilDiameterBaseline(std::unique_ptr<CDM::ScalarLengthData>(m_PupilDiameterBaseline->Unload()));
  data.NervousConfiguration(std::unique_ptr<CDM::NervousConfigurationData>(n));

  // Renal
  CDM::RenalConfigurationData* renal(new CDM::RenalConfigurationData());
  if (HasEnableRenal())
    renal->EnableRenal(m_RenalEnabled);
  if (HasPlasmaSodiumConcentrationSetPoint())
    renal->PlasmaSodiumConcentrationSetPoint(std::unique_ptr<CDM::ScalarMassPerVolumeData>(m_PlasmaSodiumConcentrationSetPoint->Unload()));
  if (HasLeftGlomerularFilteringSurfaceAreaBaseline())
    renal->LeftGlomerularFilteringSurfaceAreaBaseline(std::unique_ptr<CDM::ScalarAreaData>(m_LeftGlomerularFilteringSurfaceAreaBaseline->Unload()));
  if (HasLeftGlomerularFluidPermeabilityBaseline())
    renal->LeftGlomerularFluidPermeabilityBaseline(std::unique_ptr<CDM::ScalarData>(m_LeftGlomerularFluidPermeabilityBaseline->Unload()));
  if (HasLeftTubularReabsorptionFilteringSurfaceAreaBaseline())
    renal->LeftTubularReabsorptionFilteringSurfaceAreaBaseline(std::unique_ptr<CDM::ScalarAreaData>(m_LeftTubularReabsorptionFilteringSurfaceAreaBaseline->Unload()));
  if (HasLeftTubularReabsorptionFluidPermeabilityBaseline())
    renal->LeftTubularReabsorptionFluidPermeabilityBaseline(std::unique_ptr<CDM::ScalarData>(m_LeftTubularReabsorptionFluidPermeabilityBaseline->Unload()));

  if (HasMaximumAfferentResistance())
    renal->MaximumAfferentResistance(std::unique_ptr<CDM::ScalarFlowResistanceData>(m_MaximumAfferentResistance->Unload()));
  if (HasMinimumAfferentResistance())
    renal->MinimumAfferentResistance(std::unique_ptr<CDM::ScalarFlowResistanceData>(m_MinimumAfferentResistance->Unload()));
  
  if (HasRightGlomerularFilteringSurfaceAreaBaseline())
    renal->RightGlomerularFilteringSurfaceAreaBaseline(std::unique_ptr<CDM::ScalarAreaData>(m_RightGlomerularFilteringSurfaceAreaBaseline->Unload()));
  if (HasRightGlomerularFluidPermeabilityBaseline())
    renal->RightGlomerularFluidPermeabilityBaseline(std::unique_ptr<CDM::ScalarData>(m_RightGlomerularFluidPermeabilityBaseline->Unload()));
  if (HasRightTubularReabsorptionFilteringSurfaceAreaBaseline())
    renal->RightTubularReabsorptionFilteringSurfaceAreaBaseline(std::unique_ptr<CDM::ScalarAreaData>(m_RightTubularReabsorptionFilteringSurfaceAreaBaseline->Unload()));
  if (HasRightTubularReabsorptionFluidPermeabilityBaseline())
    renal->RightTubularReabsorptionFluidPermeabilityBaseline(std::unique_ptr<CDM::ScalarData>(m_RightTubularReabsorptionFluidPermeabilityBaseline->Unload()));
  data.RenalConfiguration(std::unique_ptr<CDM::RenalConfigurationData>(renal));

  // Respiratory
  CDM::RespiratoryConfigurationData* resp(new CDM::RespiratoryConfigurationData());
  if (m_CentralControllerCO2PressureSetPoint != nullptr)
    resp->CentralControllerCO2PressureSetPoint(std::unique_ptr<CDM::ScalarPressureData>(m_CentralControllerCO2PressureSetPoint->Unload()));
  if (HasCentralVentilatoryControllerGain())
    resp->CentralVentilatoryControllerGain(std::unique_ptr<CDM::ScalarData>(m_CentralVentilatoryControllerGain->Unload()));
  if (m_PeripheralControllerCO2PressureSetPoint != nullptr)
    resp->PeripheralControllerCO2PressureSetPoint(std::unique_ptr<CDM::ScalarPressureData>(m_PeripheralControllerCO2PressureSetPoint->Unload()));
  if (HasPeripheralVentilatoryControllerGain())
    resp->PeripheralVentilatoryControllerGain(std::unique_ptr<CDM::ScalarData>(m_PeripheralVentilatoryControllerGain->Unload()));
  if (HasPleuralComplianceSensitivity())
    resp->PleuralComplianceSensitivity(std::unique_ptr<CDM::ScalarInverseVolumeData>(m_PleuralComplianceSensitivity->Unload()));
  if (m_PulmonaryVentilationRateMaximum != nullptr)
    resp->PulmonaryVentilationRateMaximum(std::unique_ptr<CDM::ScalarVolumePerTimeData>(m_PulmonaryVentilationRateMaximum->Unload()));
  if (HasVentilationTidalVolumeIntercept())
    resp->VentilationTidalVolumeIntercept(std::unique_ptr<CDM::ScalarVolumeData>(m_VentilationTidalVolumeIntercept->Unload()));
  if (HasVentilatoryOcclusionPressure())
    resp->VentilatoryOcclusionPressure(std::unique_ptr<CDM::ScalarPressureData>(m_VentilatoryOcclusionPressure->Unload()));
  data.RespiratoryConfiguration(std::unique_ptr<CDM::RespiratoryConfigurationData>(resp));

  // Tissue
  CDM::TissueConfigurationData* tissue(new CDM::TissueConfigurationData());
  if (HasEnableTissue())
    tissue->EnableTissue(m_TissueEnabled);
  data.TissueConfiguration(std::unique_ptr<CDM::TissueConfigurationData>(tissue));
}


bool PhysiologyEngineConfiguration::HasECGInterpolator() const
{
  return m_ECGInterpolator != nullptr;
}
SEElectroCardioGramInterpolator& PhysiologyEngineConfiguration::GetECGInterpolator()
{
  if (m_ECGInterpolator == nullptr)
    m_ECGInterpolator = new SEElectroCardioGramInterpolator(GetLogger());
  return *m_ECGInterpolator;
}
const SEElectroCardioGramInterpolator* PhysiologyEngineConfiguration::GetECGInterpolator() const
{
  return m_ECGInterpolator;
}
void PhysiologyEngineConfiguration::RemoveECGInterpolator()
{
  SAFE_DELETE(m_ECGInterpolator);
}

////////////////////
/** Baroreceptors */
////////////////////
bool PulseConfiguration::HasResponseSlope() const
{
  return m_ResponseSlope == nullptr ? false : m_ResponseSlope->IsValid();
}
SEScalar& PulseConfiguration::GetResponseSlope()
{
  if (m_ResponseSlope == nullptr)
    m_ResponseSlope = new SEScalar();
  return *m_ResponseSlope;
}
double PulseConfiguration::GetResponseSlope() const
{
  if (m_ResponseSlope == nullptr)
    return SEScalar::dNaN();
  return m_ResponseSlope->GetValue();
}

bool PulseConfiguration::HasHeartRateDistributedTimeDelay() const
{
  return m_HeartRateDistributedTimeDelay == nullptr ? false : m_HeartRateDistributedTimeDelay->IsValid();
}
SEScalarTime& PulseConfiguration::GetHeartRateDistributedTimeDelay()
{
  if (m_HeartRateDistributedTimeDelay == nullptr)
    m_HeartRateDistributedTimeDelay = new SEScalarTime();
  return *m_HeartRateDistributedTimeDelay;
}
double PulseConfiguration::GetHeartRateDistributedTimeDelay(const TimeUnit& unit) const
{
  if (m_HeartRateDistributedTimeDelay == nullptr)
    return SEScalar::dNaN();    
  return m_HeartRateDistributedTimeDelay->GetValue(unit);
}

bool PulseConfiguration::HasHeartElastanceDistributedTimeDelay() const
{
  return m_HeartElastanceDistributedTimeDelay == nullptr ? false : m_HeartElastanceDistributedTimeDelay->IsValid();
}
SEScalarTime& PulseConfiguration::GetHeartElastanceDistributedTimeDelay()
{
  if (m_HeartElastanceDistributedTimeDelay == nullptr)
    m_HeartElastanceDistributedTimeDelay = new SEScalarTime();
  return *m_HeartElastanceDistributedTimeDelay;
}
double PulseConfiguration::GetHeartElastanceDistributedTimeDelay(const TimeUnit& unit) const
{
  if (m_HeartElastanceDistributedTimeDelay == nullptr)
    return SEScalar::dNaN();
  return m_HeartElastanceDistributedTimeDelay->GetValue(unit);
}

bool PulseConfiguration::HasSystemicResistanceDistributedTimeDelay() const
{
  return m_SystemicResistanceDistributedTimeDelay == nullptr ? false : m_SystemicResistanceDistributedTimeDelay->IsValid();
}
SEScalarTime& PulseConfiguration::GetSystemicResistanceDistributedTimeDelay()
{
  if (m_SystemicResistanceDistributedTimeDelay == nullptr)
    m_SystemicResistanceDistributedTimeDelay = new SEScalarTime();
  return *m_SystemicResistanceDistributedTimeDelay;
}
double PulseConfiguration::GetSystemicResistanceDistributedTimeDelay(const TimeUnit& unit) const
{
  if (m_SystemicResistanceDistributedTimeDelay == nullptr)
    return SEScalar::dNaN();
  return m_SystemicResistanceDistributedTimeDelay->GetValue(unit);
}


bool PulseConfiguration::HasVenousComplianceDistributedTimeDelay() const
{
  return m_VenousComplianceDistributedTimeDelay == nullptr ? false : m_VenousComplianceDistributedTimeDelay->IsValid();
}
SEScalarTime& PulseConfiguration::GetVenousComplianceDistributedTimeDelay()
{
  if (m_VenousComplianceDistributedTimeDelay == nullptr)
    m_VenousComplianceDistributedTimeDelay = new SEScalarTime();
  return *m_VenousComplianceDistributedTimeDelay;
}
double PulseConfiguration::GetVenousComplianceDistributedTimeDelay(const TimeUnit& unit) const
{
  if (m_VenousComplianceDistributedTimeDelay == nullptr)
    return SEScalar::dNaN();
  return m_VenousComplianceDistributedTimeDelay->GetValue(unit);
}

bool PulseConfiguration::HasNormalizedHeartRateIntercept() const
{
  return m_NormalizedHeartRateIntercept == nullptr ? false : m_NormalizedHeartRateIntercept->IsValid();
}
SEScalar& PulseConfiguration::GetNormalizedHeartRateIntercept()
{
  if (m_NormalizedHeartRateIntercept == nullptr)
    m_NormalizedHeartRateIntercept = new SEScalar();
  return *m_NormalizedHeartRateIntercept;
}
double PulseConfiguration::GetNormalizedHeartRateIntercept() const
{
  if (m_NormalizedHeartRateIntercept == nullptr)
    return SEScalar::dNaN();
  return m_NormalizedHeartRateIntercept->GetValue();
}

bool PulseConfiguration::HasNormalizedHeartRateSympatheticSlope() const
{
  return m_NormalizedHeartRateSympatheticSlope == nullptr ? false : m_NormalizedHeartRateSympatheticSlope->IsValid();
}
SEScalar& PulseConfiguration::GetNormalizedHeartRateSympatheticSlope()
{
  if (m_NormalizedHeartRateSympatheticSlope == nullptr)
    m_NormalizedHeartRateSympatheticSlope = new SEScalar();
  return *m_NormalizedHeartRateSympatheticSlope;
}
double PulseConfiguration::GetNormalizedHeartRateSympatheticSlope() const
{
  if (m_NormalizedHeartRateSympatheticSlope == nullptr)
    return SEScalar::dNaN();
  return m_NormalizedHeartRateSympatheticSlope->GetValue();
}

bool PulseConfiguration::HasNormalizedHeartRateParasympatheticSlope() const
{
  return m_NormalizedHeartRateParasympatheticSlope == nullptr ? false : m_NormalizedHeartRateParasympatheticSlope->IsValid();
}
SEScalar& PulseConfiguration::GetNormalizedHeartRateParasympatheticSlope()
{
  if (m_NormalizedHeartRateParasympatheticSlope == nullptr)
    m_NormalizedHeartRateParasympatheticSlope = new SEScalar();
  return *m_NormalizedHeartRateParasympatheticSlope;
}
double PulseConfiguration::GetNormalizedHeartRateParasympatheticSlope() const
{
  if (m_NormalizedHeartRateParasympatheticSlope == nullptr)
    return SEScalar::dNaN();
  return m_NormalizedHeartRateParasympatheticSlope->GetValue();
}

bool PulseConfiguration::HasNormalizedHeartElastanceIntercept() const
{
  return m_NormalizedHeartElastanceIntercept == nullptr ? false : m_NormalizedHeartElastanceIntercept->IsValid();
}
SEScalar& PulseConfiguration::GetNormalizedHeartElastanceIntercept()
{
  if (m_NormalizedHeartElastanceIntercept == nullptr)
    m_NormalizedHeartElastanceIntercept = new SEScalar();
  return *m_NormalizedHeartElastanceIntercept;
}
double PulseConfiguration::GetNormalizedHeartElastanceIntercept() const
{
  if (m_NormalizedHeartElastanceIntercept == nullptr)
    return SEScalar::dNaN();
  return m_NormalizedHeartElastanceIntercept->GetValue();
}

bool PulseConfiguration::HasNormalizedHeartElastanceSympatheticSlope() const
{
  return m_NormalizedHeartElastanceSympatheticSlope == nullptr ? false : m_NormalizedHeartElastanceSympatheticSlope->IsValid();
}
SEScalar& PulseConfiguration::GetNormalizedHeartElastanceSympatheticSlope()
{
  if (m_NormalizedHeartElastanceSympatheticSlope == nullptr)
    m_NormalizedHeartElastanceSympatheticSlope = new SEScalar();
  return *m_NormalizedHeartElastanceSympatheticSlope;
}
double PulseConfiguration::GetNormalizedHeartElastanceSympatheticSlope() const
{
  if (m_NormalizedHeartElastanceSympatheticSlope == nullptr)
    return SEScalar::dNaN();
  return m_NormalizedHeartElastanceSympatheticSlope->GetValue();
}

bool PulseConfiguration::HasNormalizedResistanceIntercept() const
{
  return m_NormalizedResistanceIntercept == nullptr ? false : m_NormalizedResistanceIntercept->IsValid();
}
SEScalar& PulseConfiguration::GetNormalizedResistanceIntercept()
{
  if (m_NormalizedResistanceIntercept == nullptr)
    m_NormalizedResistanceIntercept = new SEScalar();
  return *m_NormalizedResistanceIntercept;
}
double PulseConfiguration::GetNormalizedResistanceIntercept() const
{
  if (m_NormalizedResistanceIntercept == nullptr)
    return SEScalar::dNaN();
  return m_NormalizedResistanceIntercept->GetValue();
}

bool PulseConfiguration::HasNormalizedResistanceSympatheticSlope() const
{
  return m_NormalizedResistanceSympatheticSlope == nullptr ? false : m_NormalizedResistanceSympatheticSlope->IsValid();
}
SEScalar& PulseConfiguration::GetNormalizedResistanceSympatheticSlope()
{
  if (m_NormalizedResistanceSympatheticSlope == nullptr)
    m_NormalizedResistanceSympatheticSlope = new SEScalar();
  return *m_NormalizedResistanceSympatheticSlope;
}
double PulseConfiguration::GetNormalizedResistanceSympatheticSlope() const
{
  if (m_NormalizedResistanceSympatheticSlope == nullptr)
    return SEScalar::dNaN();
  return m_NormalizedResistanceSympatheticSlope->GetValue();
}

bool PulseConfiguration::HasNormalizedComplianceIntercept() const
{
  return m_NormalizedComplianceIntercept == nullptr ? false : m_NormalizedComplianceIntercept->IsValid();
}
SEScalar& PulseConfiguration::GetNormalizedComplianceIntercept()
{
  if (m_NormalizedComplianceIntercept == nullptr)
    m_NormalizedComplianceIntercept = new SEScalar();
  return *m_NormalizedComplianceIntercept;
}
double PulseConfiguration::GetNormalizedComplianceIntercept() const
{
  if (m_NormalizedComplianceIntercept == nullptr)
    return SEScalar::dNaN();
  return m_NormalizedComplianceIntercept->GetValue();
}

bool PulseConfiguration::HasNormalizedComplianceParasympatheticSlope() const
{
  return m_NormalizedComplianceParasympatheticSlope == nullptr ? false : m_NormalizedComplianceParasympatheticSlope->IsValid();
}
SEScalar& PulseConfiguration::GetNormalizedComplianceParasympatheticSlope()
{
  if (m_NormalizedComplianceParasympatheticSlope == nullptr)
    m_NormalizedComplianceParasympatheticSlope = new SEScalar();
  return *m_NormalizedComplianceParasympatheticSlope;
}
double PulseConfiguration::GetNormalizedComplianceParasympatheticSlope() const
{
  if (m_NormalizedComplianceParasympatheticSlope == nullptr)
    return SEScalar::dNaN();
  return m_NormalizedComplianceParasympatheticSlope->GetValue();
}

//////////////////////
/** Blood Chemistry */
//////////////////////

bool PulseConfiguration::HasMeanCorpuscularHemoglobin() const
{
  return m_MeanCorpuscularHemoglobin == nullptr ? false : m_MeanCorpuscularHemoglobin->IsValid();
}
SEScalarMassPerAmount& PulseConfiguration::GetMeanCorpuscularHemoglobin()
{
  if (m_MeanCorpuscularHemoglobin == nullptr)
    m_MeanCorpuscularHemoglobin = new SEScalarMassPerAmount();
  return *m_MeanCorpuscularHemoglobin;
}
double PulseConfiguration::GetMeanCorpuscularHemoglobin(const MassPerAmountUnit& unit) const
{
  if (m_MeanCorpuscularHemoglobin == nullptr)
    return SEScalar::dNaN();
  return m_MeanCorpuscularHemoglobin->GetValue(unit);
}

bool PulseConfiguration::HasMeanCorpuscularVolume() const
{
  return m_MeanCorpuscularVolume == nullptr ? false : m_MeanCorpuscularVolume->IsValid();
}
SEScalarVolume& PulseConfiguration::GetMeanCorpuscularVolume()
{
  if (m_MeanCorpuscularVolume == nullptr)
    m_MeanCorpuscularVolume = new SEScalarVolume();
  return *m_MeanCorpuscularVolume;
}
double PulseConfiguration::GetMeanCorpuscularVolume(const VolumeUnit& unit) const
{
  if (m_MeanCorpuscularVolume == nullptr)
    return SEScalar::dNaN();
  return m_MeanCorpuscularVolume->GetValue(unit);
}

bool PulseConfiguration::HasStandardDiffusionDistance() const
{
  return m_StandardDiffusionDistance == nullptr ? false : m_StandardDiffusionDistance->IsValid();
}
SEScalarLength& PulseConfiguration::GetStandardDiffusionDistance()
{
  if (m_StandardDiffusionDistance == nullptr)
    m_StandardDiffusionDistance = new SEScalarLength();
  return *m_StandardDiffusionDistance;
}
double PulseConfiguration::GetStandardDiffusionDistance(const LengthUnit& unit) const
{
  if (m_StandardDiffusionDistance == nullptr)
    return SEScalar::dNaN();
  return m_StandardDiffusionDistance->GetValue(unit);
}

bool PulseConfiguration::HasStandardOxygenDiffusionCoefficient() const
{
  return m_StandardOxygenDiffusionCoefficient == nullptr ? false : m_StandardOxygenDiffusionCoefficient->IsValid();
}
SEScalarAreaPerTimePressure& PulseConfiguration::GetStandardOxygenDiffusionCoefficient()
{
  if (m_StandardOxygenDiffusionCoefficient == nullptr)
    m_StandardOxygenDiffusionCoefficient = new SEScalarAreaPerTimePressure();
  return *m_StandardOxygenDiffusionCoefficient;
}
double PulseConfiguration::GetStandardOxygenDiffusionCoefficient(const AreaPerTimePressureUnit& unit) const
{
  if (m_StandardOxygenDiffusionCoefficient == nullptr)
    return SEScalar::dNaN();
  return m_StandardOxygenDiffusionCoefficient->GetValue(unit);
}

/////////////////////
/** Cardiovascular */
/////////////////////
bool PulseConfiguration::HasLeftHeartElastanceMaximum() const
{
  return m_LeftHeartElastanceMaximum == nullptr ? false : m_LeftHeartElastanceMaximum->IsValid();
}
SEScalarFlowElastance& PulseConfiguration::GetLeftHeartElastanceMaximum()
{
  if (m_LeftHeartElastanceMaximum == nullptr)
    m_LeftHeartElastanceMaximum = new SEScalarFlowElastance();
  return *m_LeftHeartElastanceMaximum;
}
double PulseConfiguration::GetLeftHeartElastanceMaximum(const FlowElastanceUnit& unit) const
{
  if (m_LeftHeartElastanceMaximum == nullptr)
    return SEScalar::dNaN();
  return m_LeftHeartElastanceMaximum->GetValue(unit);
}

bool PulseConfiguration::HasLeftHeartElastanceMinimum() const
{
  return m_LeftHeartElastanceMinimum == nullptr ? false : m_LeftHeartElastanceMinimum->IsValid();
}
SEScalarFlowElastance& PulseConfiguration::GetLeftHeartElastanceMinimum()
{
  if (m_LeftHeartElastanceMinimum == nullptr)
    m_LeftHeartElastanceMinimum = new SEScalarFlowElastance();
  return *m_LeftHeartElastanceMinimum;
}
double PulseConfiguration::GetLeftHeartElastanceMinimum(const FlowElastanceUnit& unit) const
{
  if (m_LeftHeartElastanceMinimum == nullptr)
    return SEScalar::dNaN();
  return m_LeftHeartElastanceMinimum->GetValue(unit);
}

bool PulseConfiguration::HasMinimumBloodVolumeFraction() const
{
  return m_MinimumBloodVolumeFraction == nullptr ? false : m_MinimumBloodVolumeFraction->IsValid();
}
SEScalar0To1& PulseConfiguration::GetMinimumBloodVolumeFraction()
{
  if (m_MinimumBloodVolumeFraction == nullptr)
    m_MinimumBloodVolumeFraction = new SEScalar0To1();
  return *m_MinimumBloodVolumeFraction;
}
double PulseConfiguration::GetMinimumBloodVolumeFraction() const
{
  if (m_MinimumBloodVolumeFraction == nullptr)
    return SEScalar::dNaN();
  return m_MinimumBloodVolumeFraction->GetValue();
}

bool PulseConfiguration::HasRightHeartElastanceMaximum() const
{
  return m_RightHeartElastanceMaximum == nullptr ? false : m_RightHeartElastanceMaximum->IsValid();
}
SEScalarFlowElastance& PulseConfiguration::GetRightHeartElastanceMaximum()
{
  if (m_RightHeartElastanceMaximum == nullptr)
    m_RightHeartElastanceMaximum = new SEScalarFlowElastance();
  return *m_RightHeartElastanceMaximum;
}
double PulseConfiguration::GetRightHeartElastanceMaximum(const FlowElastanceUnit& unit) const
{
  if (m_RightHeartElastanceMaximum == nullptr)
    return SEScalar::dNaN();
  return m_RightHeartElastanceMaximum->GetValue(unit);
}

bool PulseConfiguration::HasRightHeartElastanceMinimum() const
{
  return m_RightHeartElastanceMinimum == nullptr ? false : m_RightHeartElastanceMinimum->IsValid();
}
SEScalarFlowElastance& PulseConfiguration::GetRightHeartElastanceMinimum()
{
  if (m_RightHeartElastanceMinimum == nullptr)
    m_RightHeartElastanceMinimum = new SEScalarFlowElastance();
  return *m_RightHeartElastanceMinimum;
}
double PulseConfiguration::GetRightHeartElastanceMinimum(const FlowElastanceUnit& unit) const
{
  if (m_RightHeartElastanceMinimum == nullptr)
    return SEScalar::dNaN();
  return m_RightHeartElastanceMinimum->GetValue(unit);
}

bool PulseConfiguration::HasStandardPulmonaryCapillaryCoverage() const
{
  return m_StandardPulmonaryCapillaryCoverage == nullptr ? false : m_StandardPulmonaryCapillaryCoverage->IsValid();
}
SEScalar& PulseConfiguration::GetStandardPulmonaryCapillaryCoverage()
{
  if (m_StandardPulmonaryCapillaryCoverage == nullptr)
    m_StandardPulmonaryCapillaryCoverage = new SEScalar();
  return *m_StandardPulmonaryCapillaryCoverage;
}
double PulseConfiguration::GetStandardPulmonaryCapillaryCoverage() const
{
  if (m_StandardPulmonaryCapillaryCoverage == nullptr)
    return SEScalar::dNaN();
  return m_StandardPulmonaryCapillaryCoverage->GetValue();
}

//////////////
/** Circuit */
//////////////

bool PulseConfiguration::HasCardiovascularOpenResistance() const
{
  return m_CardiovascularOpenResistance == nullptr ? false : m_CardiovascularOpenResistance->IsValid();
}
SEScalarFlowResistance& PulseConfiguration::GetCardiovascularOpenResistance()
{
  if (m_CardiovascularOpenResistance == nullptr)
    m_CardiovascularOpenResistance = new SEScalarFlowResistance();
  return *m_CardiovascularOpenResistance;
}
double PulseConfiguration::GetCardiovascularOpenResistance(const FlowResistanceUnit& unit) const
{
  if (m_CardiovascularOpenResistance == nullptr)
    return SEScalar::dNaN();
  return m_CardiovascularOpenResistance->GetValue(unit);
}

bool PulseConfiguration::HasDefaultClosedElectricResistance() const
{
  return m_DefaultClosedElectricResistance == nullptr ? false : m_DefaultClosedElectricResistance->IsValid();
}
SEScalarElectricResistance& PulseConfiguration::GetDefaultClosedElectricResistance()
{
  if (m_DefaultClosedElectricResistance == nullptr)
    m_DefaultClosedElectricResistance = new SEScalarElectricResistance();
  return *m_DefaultClosedElectricResistance;
}
double PulseConfiguration::GetDefaultClosedElectricResistance(const ElectricResistanceUnit& unit) const
{
  if (m_DefaultClosedElectricResistance == nullptr)
    return SEScalar::dNaN();
  return m_DefaultClosedElectricResistance->GetValue(unit);
}

bool PulseConfiguration::HasDefaultClosedFlowResistance() const
{
  return m_DefaultClosedFlowResistance == nullptr ? false : m_DefaultClosedFlowResistance->IsValid();
}
SEScalarFlowResistance& PulseConfiguration::GetDefaultClosedFlowResistance()
{
  if (m_DefaultClosedFlowResistance == nullptr)
    m_DefaultClosedFlowResistance = new SEScalarFlowResistance();
  return *m_DefaultClosedFlowResistance;
}
double PulseConfiguration::GetDefaultClosedFlowResistance(const FlowResistanceUnit& unit) const
{
  if (m_DefaultClosedFlowResistance == nullptr)
    return SEScalar::dNaN();
  return m_DefaultClosedFlowResistance->GetValue(unit);
}

bool PulseConfiguration::HasDefaultClosedHeatResistance() const
{
  return m_DefaultClosedHeatResistance == nullptr ? false : m_DefaultClosedHeatResistance->IsValid();
}
SEScalarHeatResistance& PulseConfiguration::GetDefaultClosedHeatResistance()
{
  if (m_DefaultClosedHeatResistance == nullptr)
    m_DefaultClosedHeatResistance = new SEScalarHeatResistance();
  return *m_DefaultClosedHeatResistance;
}
double PulseConfiguration::GetDefaultClosedHeatResistance(const HeatResistanceUnit& unit) const
{
  if (m_DefaultClosedHeatResistance == nullptr)
    return SEScalar::dNaN();
  return m_DefaultClosedHeatResistance->GetValue(unit);
}

bool PulseConfiguration::HasDefaultOpenElectricResistance() const
{
  return m_DefaultOpenElectricResistance == nullptr ? false : m_DefaultOpenElectricResistance->IsValid();
}
SEScalarElectricResistance& PulseConfiguration::GetDefaultOpenElectricResistance()
{
  if (m_DefaultOpenElectricResistance == nullptr)
    m_DefaultOpenElectricResistance = new SEScalarElectricResistance();
  return *m_DefaultOpenElectricResistance;
}
double PulseConfiguration::GetDefaultOpenElectricResistance(const ElectricResistanceUnit& unit) const
{
  if (m_DefaultOpenElectricResistance == nullptr)
    return SEScalar::dNaN();
  return m_DefaultOpenElectricResistance->GetValue(unit);
}

bool PulseConfiguration::HasDefaultOpenFlowResistance() const
{
  return m_DefaultOpenFlowResistance == nullptr ? false : m_DefaultOpenFlowResistance->IsValid();
}
SEScalarFlowResistance& PulseConfiguration::GetDefaultOpenFlowResistance()
{
  if (m_DefaultOpenFlowResistance == nullptr)
    m_DefaultOpenFlowResistance = new SEScalarFlowResistance();
  return *m_DefaultOpenFlowResistance;
}
double PulseConfiguration::GetDefaultOpenFlowResistance(const FlowResistanceUnit& unit) const
{
  if (m_DefaultOpenFlowResistance == nullptr)
    return SEScalar::dNaN();
  return m_DefaultOpenFlowResistance->GetValue(unit);
}

bool PulseConfiguration::HasDefaultOpenHeatResistance() const
{
  return m_DefaultOpenHeatResistance == nullptr ? false : m_DefaultOpenHeatResistance->IsValid();
}
SEScalarHeatResistance& PulseConfiguration::GetDefaultOpenHeatResistance()
{
  if (m_DefaultOpenHeatResistance == nullptr)
    m_DefaultOpenHeatResistance = new SEScalarHeatResistance();
  return *m_DefaultOpenHeatResistance;
}
double PulseConfiguration::GetDefaultOpenHeatResistance(const HeatResistanceUnit& unit) const
{
  if (m_DefaultOpenHeatResistance == nullptr)
    return SEScalar::dNaN();
  return m_DefaultOpenHeatResistance->GetValue(unit);
}

bool PulseConfiguration::HasMachineClosedResistance() const
{
  return m_MachineClosedResistance == nullptr ? false : m_MachineClosedResistance->IsValid();
}
SEScalarFlowResistance& PulseConfiguration::GetMachineClosedResistance()
{
  if (m_MachineClosedResistance == nullptr)
    m_MachineClosedResistance = new SEScalarFlowResistance();
  return *m_MachineClosedResistance;
}
double PulseConfiguration::GetMachineClosedResistance(const FlowResistanceUnit& unit) const
{
  if (m_MachineClosedResistance == nullptr)
    return SEScalar::dNaN();
  return m_MachineClosedResistance->GetValue(unit);
}

bool PulseConfiguration::HasMachineOpenResistance() const
{
  return m_MachineOpenResistance == nullptr ? false : m_MachineOpenResistance->IsValid();
}
SEScalarFlowResistance& PulseConfiguration::GetMachineOpenResistance()
{
  if (m_MachineOpenResistance == nullptr)
    m_MachineOpenResistance = new SEScalarFlowResistance();
  return *m_MachineOpenResistance;
}
double PulseConfiguration::GetMachineOpenResistance(const FlowResistanceUnit& unit) const
{
  if (m_MachineOpenResistance == nullptr)
    return SEScalar::dNaN();
  return m_MachineOpenResistance->GetValue(unit);
}

bool PulseConfiguration::HasRespiratoryClosedResistance() const
{
  return m_RespiratoryClosedResistance == nullptr ? false : m_RespiratoryClosedResistance->IsValid();
}
SEScalarFlowResistance& PulseConfiguration::GetRespiratoryClosedResistance()
{
  if (m_RespiratoryClosedResistance == nullptr)
    m_RespiratoryClosedResistance = new SEScalarFlowResistance();
  return *m_RespiratoryClosedResistance;
}
double PulseConfiguration::GetRespiratoryClosedResistance(const FlowResistanceUnit& unit) const
{
  if (m_RespiratoryClosedResistance == nullptr)
    return SEScalar::dNaN();
  return m_RespiratoryClosedResistance->GetValue(unit);
}

bool PulseConfiguration::HasRespiratoryOpenResistance() const
{
  return m_RespiratoryOpenResistance == nullptr ? false : m_RespiratoryOpenResistance->IsValid();
}
SEScalarFlowResistance& PulseConfiguration::GetRespiratoryOpenResistance()
{
  if (m_RespiratoryOpenResistance == nullptr)
    m_RespiratoryOpenResistance = new SEScalarFlowResistance();
  return *m_RespiratoryOpenResistance;
}
double PulseConfiguration::GetRespiratoryOpenResistance(const FlowResistanceUnit& unit) const
{
  if (m_RespiratoryOpenResistance == nullptr)
    return SEScalar::dNaN();
  return m_RespiratoryOpenResistance->GetValue(unit);
}

////////////////
/** Constants */
////////////////
bool PulseConfiguration::HasOxygenMetabolicConstant() const
{
  return m_OxygenMetabolicConstant == nullptr ? false : m_OxygenMetabolicConstant->IsValid();
}
SEScalar& PulseConfiguration::GetOxygenMetabolicConstant()
{
  if (m_OxygenMetabolicConstant == nullptr)
    m_OxygenMetabolicConstant = new SEScalar();
  return *m_OxygenMetabolicConstant;
}
double PulseConfiguration::GetOxygenMetabolicConstant() const
{
  if (m_OxygenMetabolicConstant == nullptr)
    return SEScalar::dNaN();
  return m_OxygenMetabolicConstant->GetValue();
}

bool PulseConfiguration::HasStefanBoltzmann() const
{
  return m_StefanBoltzmann == nullptr ? false : m_StefanBoltzmann->IsValid();
}
SEScalarPowerPerAreaTemperatureToTheFourth& PulseConfiguration::GetStefanBoltzmann()
{
  if (m_StefanBoltzmann == nullptr)
    m_StefanBoltzmann = new SEScalarPowerPerAreaTemperatureToTheFourth();
  return *m_StefanBoltzmann;
}
double PulseConfiguration::GetStefanBoltzmann(const PowerPerAreaTemperatureToTheFourthUnit& unit) const
{
  if (m_StefanBoltzmann == nullptr)
    return SEScalar::dNaN();
  return m_StefanBoltzmann->GetValue(unit);
}

bool PulseConfiguration::HasUniversalGasConstant() const
{
  return m_UniversalGasConstant == nullptr ? false : m_UniversalGasConstant->IsValid();
}
SEScalarHeatCapacitancePerAmount& PulseConfiguration::GetUniversalGasConstant()
{
  if (m_UniversalGasConstant == nullptr)
    m_UniversalGasConstant = new SEScalarHeatCapacitancePerAmount();
  return *m_UniversalGasConstant;
}
double PulseConfiguration::GetUniversalGasConstant(const HeatCapacitancePerAmountUnit& unit) const
{
  if (m_UniversalGasConstant == nullptr)
    return SEScalar::dNaN();
  return m_UniversalGasConstant->GetValue(unit);
}

/////////////
/** Energy */
/////////////
bool PulseConfiguration::HasBodySpecificHeat() const
{
  return m_BodySpecificHeat == nullptr ? false : m_BodySpecificHeat->IsValid();
}
SEScalarHeatCapacitancePerMass& PulseConfiguration::GetBodySpecificHeat()
{
  if (m_BodySpecificHeat == nullptr)
    m_BodySpecificHeat = new SEScalarHeatCapacitancePerMass();
  return *m_BodySpecificHeat;
}
double PulseConfiguration::GetBodySpecificHeat(const HeatCapacitancePerMassUnit& unit) const
{
  if (m_BodySpecificHeat == nullptr)
    return SEScalar::dNaN();
  return m_BodySpecificHeat->GetValue(unit);
}

bool PulseConfiguration::HasCarbondDioxideProductionFromOxygenConsumptionConstant() const
{
  return m_CarbondDioxideProductionFromOxygenConsumptionConstant == nullptr ? false : m_CarbondDioxideProductionFromOxygenConsumptionConstant->IsValid();
}
SEScalar& PulseConfiguration::GetCarbondDioxideProductionFromOxygenConsumptionConstant()
{
  if (m_CarbondDioxideProductionFromOxygenConsumptionConstant == nullptr)
    m_CarbondDioxideProductionFromOxygenConsumptionConstant = new SEScalar();
  return *m_CarbondDioxideProductionFromOxygenConsumptionConstant;
}
double PulseConfiguration::GetCarbondDioxideProductionFromOxygenConsumptionConstant() const
{
  if (m_CarbondDioxideProductionFromOxygenConsumptionConstant == nullptr)
    return SEScalar::dNaN();
  return m_CarbondDioxideProductionFromOxygenConsumptionConstant->GetValue();
}

bool PulseConfiguration::HasCoreTemperatureHigh() const
{
  return m_CoreTemperatureHigh == nullptr ? false : m_CoreTemperatureHigh->IsValid();
}
SEScalarTemperature& PulseConfiguration::GetCoreTemperatureHigh()
{
  if (m_CoreTemperatureHigh == nullptr)
    m_CoreTemperatureHigh = new SEScalarTemperature();
  return *m_CoreTemperatureHigh;
}
double PulseConfiguration::GetCoreTemperatureHigh(const TemperatureUnit& unit) const
{
  if (m_CoreTemperatureHigh == nullptr)
    return SEScalar::dNaN();
  return m_CoreTemperatureHigh->GetValue(unit);
}

bool PulseConfiguration::HasCoreTemperatureLow() const
{
  return m_CoreTemperatureLow == nullptr ? false : m_CoreTemperatureLow->IsValid();
}
SEScalarTemperature& PulseConfiguration::GetCoreTemperatureLow()
{
  if (m_CoreTemperatureLow == nullptr)
    m_CoreTemperatureLow = new SEScalarTemperature();
  return *m_CoreTemperatureLow;
}
double PulseConfiguration::GetCoreTemperatureLow(const TemperatureUnit& unit) const
{
  if (m_CoreTemperatureLow == nullptr)
    return SEScalar::dNaN();
  return m_CoreTemperatureLow->GetValue(unit);
}

bool PulseConfiguration::HasDeltaCoreTemperatureLow() const
{
  return m_DeltaCoreTemperatureLow == nullptr ? false : m_DeltaCoreTemperatureLow->IsValid();
}
SEScalarTemperature& PulseConfiguration::GetDeltaCoreTemperatureLow()
{
  if (m_DeltaCoreTemperatureLow == nullptr)
    m_DeltaCoreTemperatureLow = new SEScalarTemperature();
  return *m_DeltaCoreTemperatureLow;
}
double PulseConfiguration::GetDeltaCoreTemperatureLow(const TemperatureUnit& unit) const
{
  if (m_DeltaCoreTemperatureLow == nullptr)
    return SEScalar::dNaN();
  return m_DeltaCoreTemperatureLow->GetValue(unit);
}

bool PulseConfiguration::HasEnergyPerATP() const
{
  return m_EnergyPerATP == nullptr ? false : m_EnergyPerATP->IsValid();
}
SEScalarEnergyPerAmount& PulseConfiguration::GetEnergyPerATP()
{
  if (m_EnergyPerATP == nullptr)
    m_EnergyPerATP = new SEScalarEnergyPerAmount();
  return *m_EnergyPerATP;
}
double PulseConfiguration::GetEnergyPerATP(const EnergyPerAmountUnit& unit) const
{
  if (m_EnergyPerATP == nullptr)
    return SEScalar::dNaN();
  return m_EnergyPerATP->GetValue(unit);
}

bool PulseConfiguration::HasSweatHeatTransfer() const
{
  return m_SweatHeatTransfer == nullptr ? false : m_SweatHeatTransfer->IsValid();
}
SEScalarHeatConductance& PulseConfiguration::GetSweatHeatTransfer()
{
  if (m_SweatHeatTransfer == nullptr)
    m_SweatHeatTransfer = new SEScalarHeatConductance();
  return *m_SweatHeatTransfer;
}
double PulseConfiguration::GetSweatHeatTransfer(const HeatConductanceUnit& unit) const
{
  if (m_SweatHeatTransfer == nullptr)
    return SEScalar::dNaN();
  return m_SweatHeatTransfer->GetValue(unit);
}

bool PulseConfiguration::HasVaporizationEnergy() const
{
  return m_VaporizationEnergy == nullptr ? false : m_VaporizationEnergy->IsValid();
}
SEScalarEnergyPerMass& PulseConfiguration::GetVaporizationEnergy()
{
  if (m_VaporizationEnergy == nullptr)
    m_VaporizationEnergy = new SEScalarEnergyPerMass();
  return *m_VaporizationEnergy;
}
double PulseConfiguration::GetVaporizationEnergy(const EnergyPerMassUnit& unit) const
{
  if (m_VaporizationEnergy == nullptr)
    return SEScalar::dNaN();
  return m_VaporizationEnergy->GetValue(unit);
}

bool PulseConfiguration::HasVaporSpecificHeat() const
{
  return m_VaporSpecificHeat == nullptr ? false : m_VaporSpecificHeat->IsValid();
}
SEScalarHeatCapacitancePerMass& PulseConfiguration::GetVaporSpecificHeat()
{
  if (m_VaporSpecificHeat == nullptr)
    m_VaporSpecificHeat = new SEScalarHeatCapacitancePerMass();
  return *m_VaporSpecificHeat;
}
double PulseConfiguration::GetVaporSpecificHeat(const HeatCapacitancePerMassUnit& unit) const
{
  if (m_VaporSpecificHeat == nullptr)
    return SEScalar::dNaN();
  return m_VaporSpecificHeat->GetValue(unit);
}

//////////////////
/** Environment */
//////////////////
bool PulseConfiguration::HasAirDensity() const
{
  return m_AirDensity == nullptr ? false : m_AirDensity->IsValid();
}
SEScalarMassPerVolume& PulseConfiguration::GetAirDensity()
{
  if (m_AirDensity == nullptr)
    m_AirDensity = new SEScalarMassPerVolume();
  return *m_AirDensity;
}
double PulseConfiguration::GetAirDensity(const MassPerVolumeUnit& unit) const
{
  if (m_AirDensity == nullptr)
    return SEScalar::dNaN();
  return m_AirDensity->GetValue(unit);
}

bool PulseConfiguration::HasAirSpecificHeat() const
{
  return m_AirSpecificHeat == nullptr ? false : m_AirSpecificHeat->IsValid();
}
SEScalarHeatCapacitancePerMass& PulseConfiguration::GetAirSpecificHeat()
{
  if (m_AirSpecificHeat == nullptr)
    m_AirSpecificHeat = new SEScalarHeatCapacitancePerMass();
  return *m_AirSpecificHeat;
}
double PulseConfiguration::GetAirSpecificHeat(const HeatCapacitancePerMassUnit& unit) const
{
  if (m_AirSpecificHeat == nullptr)
    return SEScalar::dNaN();
  return m_AirSpecificHeat->GetValue(unit);
}

bool PulseConfiguration::HasMolarMassOfDryAir() const
{
  return m_MolarMassOfDryAir == nullptr ? false : m_MolarMassOfDryAir->IsValid();
}
SEScalarMassPerAmount& PulseConfiguration::GetMolarMassOfDryAir()
{
  if (m_MolarMassOfDryAir == nullptr)
    m_MolarMassOfDryAir = new SEScalarMassPerAmount();
  return *m_MolarMassOfDryAir;
}
double PulseConfiguration::GetMolarMassOfDryAir(const MassPerAmountUnit& unit) const
{
  if (m_MolarMassOfDryAir == nullptr)
    return SEScalar::dNaN();
  return m_MolarMassOfDryAir->GetValue(unit);
}

bool PulseConfiguration::HasMolarMassOfWaterVapor() const
{
  return m_MolarMassOfWaterVapor == nullptr ? false : m_MolarMassOfWaterVapor->IsValid();
}
SEScalarMassPerAmount& PulseConfiguration::GetMolarMassOfWaterVapor()
{
  if (m_MolarMassOfWaterVapor == nullptr)
    m_MolarMassOfWaterVapor = new SEScalarMassPerAmount();
  return *m_MolarMassOfWaterVapor;
}
double PulseConfiguration::GetMolarMassOfWaterVapor(const MassPerAmountUnit& unit) const
{
  if (m_MolarMassOfWaterVapor == nullptr)
    return SEScalar::dNaN();
  return m_MolarMassOfWaterVapor->GetValue(unit);
}

bool PulseConfiguration::HasInitialEnvironmentalConditions() const
{
  return m_InitialEnvironmentalConditions != nullptr;
}
SEEnvironmentalConditions& PulseConfiguration::GetInitialEnvironmentalConditions()
{
  if (m_InitialEnvironmentalConditions == nullptr)
    m_InitialEnvironmentalConditions = new SEEnvironmentalConditions(m_Substances);
  return *m_InitialEnvironmentalConditions;
}
const SEEnvironmentalConditions* PulseConfiguration::GetInitialEnvironmentalConditions() const
{
  return m_InitialEnvironmentalConditions;
}

bool PulseConfiguration::HasWaterDensity() const
{
  return m_WaterDensity == nullptr ? false : m_WaterDensity->IsValid();
}
SEScalarMassPerVolume& PulseConfiguration::GetWaterDensity()
{
  if (m_WaterDensity == nullptr)
    m_WaterDensity = new SEScalarMassPerVolume();
  return *m_WaterDensity;
}
double PulseConfiguration::GetWaterDensity(const MassPerVolumeUnit& unit) const
{
  if (m_WaterDensity == nullptr)
    return SEScalar::dNaN();
  return m_WaterDensity->GetValue(unit);
}

///////////////////////
/** Gastrointestinal */
///////////////////////

bool PulseConfiguration::HasCalciumDigestionRate() const
{
  return m_CalciumDigestionRate == nullptr ? false : m_CalciumDigestionRate->IsValid();
}
SEScalarMassPerTime& PulseConfiguration::GetCalciumDigestionRate()
{
  if (m_CalciumDigestionRate == nullptr)
    m_CalciumDigestionRate = new SEScalarMassPerTime();
  return *m_CalciumDigestionRate;
}
double PulseConfiguration::GetCalciumDigestionRate(const MassPerTimeUnit& unit) const
{
  if (m_CalciumDigestionRate == nullptr)
    return SEScalar::dNaN();
  return m_CalciumDigestionRate->GetValue(unit);
}

bool PulseConfiguration::HasCalciumAbsorbtionFraction() const
{
  return m_CalciumAbsorbtionFraction == nullptr ? false : m_CalciumAbsorbtionFraction->IsValid();
}
SEScalar0To1& PulseConfiguration::GetCalciumAbsorbtionFraction()
{
  if (m_CalciumAbsorbtionFraction == nullptr)
    m_CalciumAbsorbtionFraction = new SEScalar0To1();
  return *m_CalciumAbsorbtionFraction;
}
double PulseConfiguration::GetCalciumAbsorbtionFraction() const
{
  if (m_CalciumAbsorbtionFraction == nullptr)
    return SEScalar::dNaN();
  return m_CalciumAbsorbtionFraction->GetValue();
}

bool PulseConfiguration::HasCarbohydrateAbsorbtionFraction() const
{
  return m_CarbohydrateAbsorbtionFraction == nullptr ? false : m_CarbohydrateAbsorbtionFraction->IsValid();
}
SEScalar0To1& PulseConfiguration::GetCarbohydrateAbsorbtionFraction()
{
  if (m_CarbohydrateAbsorbtionFraction == nullptr)
    m_CarbohydrateAbsorbtionFraction = new SEScalar0To1();
  return *m_CarbohydrateAbsorbtionFraction;
}
double PulseConfiguration::GetCarbohydrateAbsorbtionFraction() const
{
  if (m_CarbohydrateAbsorbtionFraction == nullptr)
    return SEScalar::dNaN();
  return m_CarbohydrateAbsorbtionFraction->GetValue();
}

bool PulseConfiguration::HasDefaultCarbohydrateDigestionRate() const
{
  return m_DefaultCarbohydrateDigestionRate == nullptr ? false : m_DefaultCarbohydrateDigestionRate->IsValid();
}
SEScalarMassPerTime& PulseConfiguration::GetDefaultCarbohydrateDigestionRate()
{
  if (m_DefaultCarbohydrateDigestionRate == nullptr)
    m_DefaultCarbohydrateDigestionRate = new SEScalarMassPerTime();
  return *m_DefaultCarbohydrateDigestionRate;
}
double PulseConfiguration::GetDefaultCarbohydrateDigestionRate(const MassPerTimeUnit& unit) const
{
  if (m_DefaultCarbohydrateDigestionRate == nullptr)
    return SEScalar::dNaN();
  return m_DefaultCarbohydrateDigestionRate->GetValue(unit);
}

bool PulseConfiguration::HasDefaultFatDigestionRate() const
{
  return m_DefaultFatDigestionRate == nullptr ? false : m_DefaultFatDigestionRate->IsValid();
}
SEScalarMassPerTime& PulseConfiguration::GetDefaultFatDigestionRate()
{
  if (m_DefaultFatDigestionRate == nullptr)
    m_DefaultFatDigestionRate = new SEScalarMassPerTime();
  return *m_DefaultFatDigestionRate;
}
double PulseConfiguration::GetDefaultFatDigestionRate(const MassPerTimeUnit& unit) const
{
  if (m_DefaultFatDigestionRate == nullptr)
    return SEScalar::dNaN();
  return m_DefaultFatDigestionRate->GetValue(unit);
}

bool PulseConfiguration::HasDefaultProteinDigestionRate() const
{
  return m_DefaultProteinDigestionRate == nullptr ? false : m_DefaultProteinDigestionRate->IsValid();
}
SEScalarMassPerTime& PulseConfiguration::GetDefaultProteinDigestionRate()
{
  if (m_DefaultProteinDigestionRate == nullptr)
    m_DefaultProteinDigestionRate = new SEScalarMassPerTime();
  return *m_DefaultProteinDigestionRate;
}
double PulseConfiguration::GetDefaultProteinDigestionRate(const MassPerTimeUnit& unit) const
{
  if (m_DefaultProteinDigestionRate == nullptr)
    return SEScalar::dNaN();
  return m_DefaultProteinDigestionRate->GetValue(unit);
}

bool PulseConfiguration::HasDefaultStomachContents() const
{
  return m_DefaultStomachContents != nullptr;
}
SENutrition& PulseConfiguration::GetDefaultStomachContents()
{
  if (m_DefaultStomachContents == nullptr)
    m_DefaultStomachContents = new SENutrition(GetLogger());
  return *m_DefaultStomachContents;
}
const SENutrition* PulseConfiguration::GetDefaultStomachContents() const
{
  return m_DefaultStomachContents;
}

bool PulseConfiguration::HasFatAbsorbtionFraction() const
{
  return m_FatAbsorbtionFraction == nullptr ? false : m_FatAbsorbtionFraction->IsValid();
}
SEScalar0To1& PulseConfiguration::GetFatAbsorbtionFraction()
{
  if (m_FatAbsorbtionFraction == nullptr)
    m_FatAbsorbtionFraction = new SEScalar0To1();
  return *m_FatAbsorbtionFraction;
}
double PulseConfiguration::GetFatAbsorbtionFraction() const
{
  if (m_FatAbsorbtionFraction == nullptr)
    return SEScalar::dNaN();
  return m_FatAbsorbtionFraction->GetValue();
}

bool PulseConfiguration::HasProteinToUreaFraction() const
{
  return m_ProteinToUreaFraction == nullptr ? false : m_ProteinToUreaFraction->IsValid();
}
SEScalar0To1& PulseConfiguration::GetProteinToUreaFraction()
{
  if (m_ProteinToUreaFraction == nullptr)
    m_ProteinToUreaFraction = new SEScalar0To1();
  return *m_ProteinToUreaFraction;
}
double PulseConfiguration::GetProteinToUreaFraction() const
{
  if (m_ProteinToUreaFraction == nullptr)
    return SEScalar::dNaN();
  return m_ProteinToUreaFraction->GetValue();
}

bool PulseConfiguration::HasWaterDigestionRate() const
{
  return m_WaterDigestionRate == nullptr ? false : m_WaterDigestionRate->IsValid();
}
SEScalarVolumePerTime& PulseConfiguration::GetWaterDigestionRate()
{
  if (m_WaterDigestionRate == nullptr)
    m_WaterDigestionRate = new SEScalarVolumePerTime();
  return *m_WaterDigestionRate;
}
double PulseConfiguration::GetWaterDigestionRate(const VolumePerTimeUnit& unit) const
{
  if (m_WaterDigestionRate == nullptr)
    return SEScalar::dNaN();
  return m_WaterDigestionRate->GetValue(unit);
}

///////////////
/** Nervous */
/////////////

bool PulseConfiguration::HasPupilDiameterBaseline() const
{
  return m_PupilDiameterBaseline == nullptr ? false : m_PupilDiameterBaseline->IsValid();
}
SEScalarLength& PulseConfiguration::GetPupilDiameterBaseline()
{
  if (m_PupilDiameterBaseline == nullptr)
    m_PupilDiameterBaseline = new SEScalarLength();
  return *m_PupilDiameterBaseline;
}
double PulseConfiguration::GetPupilDiameterBaseline(const LengthUnit& unit) const
{
  if (m_PupilDiameterBaseline == nullptr)
    return SEScalar::dNaN();
  return m_PupilDiameterBaseline->GetValue(unit);
}

////////////
/** Renal */
////////////

bool PulseConfiguration::HasPlasmaSodiumConcentrationSetPoint() const
{
  return m_PlasmaSodiumConcentrationSetPoint == nullptr ? false : m_PlasmaSodiumConcentrationSetPoint->IsValid();
}
SEScalarMassPerVolume& PulseConfiguration::GetPlasmaSodiumConcentrationSetPoint()
{
  if (m_PlasmaSodiumConcentrationSetPoint == nullptr)
    m_PlasmaSodiumConcentrationSetPoint = new SEScalarMassPerVolume();
  return *m_PlasmaSodiumConcentrationSetPoint;
}
double PulseConfiguration::GetPlasmaSodiumConcentrationSetPoint(const MassPerVolumeUnit& unit) const
{
  if (m_PlasmaSodiumConcentrationSetPoint == nullptr)
    return SEScalar::dNaN();
  return m_PlasmaSodiumConcentrationSetPoint->GetValue(unit);
}

bool PulseConfiguration::HasPeritubularPotassiumConcentrationSetPoint() const
{
  return m_PeritubularPotassiumConcentrationSetPoint == nullptr ? false : m_PeritubularPotassiumConcentrationSetPoint->IsValid();
}
SEScalarMassPerVolume& PulseConfiguration::GetPeritubularPotassiumConcentrationSetPoint()
{
  if (m_PeritubularPotassiumConcentrationSetPoint == nullptr)
    m_PeritubularPotassiumConcentrationSetPoint = new SEScalarMassPerVolume();
  return *m_PeritubularPotassiumConcentrationSetPoint;
}
double PulseConfiguration::GetPeritubularPotassiumConcentrationSetPoint(const MassPerVolumeUnit& unit) const
{
  if (m_PeritubularPotassiumConcentrationSetPoint == nullptr)
    return SEScalar::dNaN();
  return m_PeritubularPotassiumConcentrationSetPoint->GetValue(unit);
}

bool PulseConfiguration::HasLeftGlomerularFluidPermeabilityBaseline() const
{
  return m_LeftGlomerularFluidPermeabilityBaseline == nullptr ? false : m_LeftGlomerularFluidPermeabilityBaseline->IsValid();
}
SEScalarVolumePerTimePressureArea& PulseConfiguration::GetLeftGlomerularFluidPermeabilityBaseline()
{
  if (m_LeftGlomerularFluidPermeabilityBaseline == nullptr)
    m_LeftGlomerularFluidPermeabilityBaseline = new SEScalarVolumePerTimePressureArea();
  return *m_LeftGlomerularFluidPermeabilityBaseline;
}
double PulseConfiguration::GetLeftGlomerularFluidPermeabilityBaseline(const VolumePerTimePressureAreaUnit& unit) const
{
  if (m_LeftGlomerularFluidPermeabilityBaseline == nullptr)
    return SEScalar::dNaN();
  return m_LeftGlomerularFluidPermeabilityBaseline->GetValue(unit);
}

bool PulseConfiguration::HasLeftGlomerularFilteringSurfaceAreaBaseline() const
{
  return m_LeftGlomerularFilteringSurfaceAreaBaseline == nullptr ? false : m_LeftGlomerularFilteringSurfaceAreaBaseline->IsValid();
}
SEScalarArea& PulseConfiguration::GetLeftGlomerularFilteringSurfaceAreaBaseline()
{
  if (m_LeftGlomerularFilteringSurfaceAreaBaseline == nullptr)
    m_LeftGlomerularFilteringSurfaceAreaBaseline = new SEScalarArea();
  return *m_LeftGlomerularFilteringSurfaceAreaBaseline;
}
double PulseConfiguration::GetLeftGlomerularFilteringSurfaceAreaBaseline(const AreaUnit& unit) const
{
  if (m_LeftGlomerularFilteringSurfaceAreaBaseline == nullptr)
    return SEScalar::dNaN();
  return m_LeftGlomerularFilteringSurfaceAreaBaseline->GetValue(unit);
}

bool PulseConfiguration::HasLeftTubularReabsorptionFluidPermeabilityBaseline() const
{
  return m_LeftTubularReabsorptionFluidPermeabilityBaseline == nullptr ? false : m_LeftTubularReabsorptionFluidPermeabilityBaseline->IsValid();
}
SEScalarVolumePerTimePressureArea& PulseConfiguration::GetLeftTubularReabsorptionFluidPermeabilityBaseline()
{
  if (m_LeftTubularReabsorptionFluidPermeabilityBaseline == nullptr)
    m_LeftTubularReabsorptionFluidPermeabilityBaseline = new SEScalarVolumePerTimePressureArea();
  return *m_LeftTubularReabsorptionFluidPermeabilityBaseline;
}
double PulseConfiguration::GetLeftTubularReabsorptionFluidPermeabilityBaseline(const VolumePerTimePressureAreaUnit& unit) const
{
  if (m_LeftTubularReabsorptionFluidPermeabilityBaseline == nullptr)
    return SEScalar::dNaN();
  return m_LeftTubularReabsorptionFluidPermeabilityBaseline->GetValue(unit);
}

bool PulseConfiguration::HasLeftTubularReabsorptionFilteringSurfaceAreaBaseline() const
{
  return m_LeftTubularReabsorptionFilteringSurfaceAreaBaseline == nullptr ? false : m_LeftTubularReabsorptionFilteringSurfaceAreaBaseline->IsValid();
}
SEScalarArea& PulseConfiguration::GetLeftTubularReabsorptionFilteringSurfaceAreaBaseline()
{
  if (m_LeftTubularReabsorptionFilteringSurfaceAreaBaseline == nullptr)
    m_LeftTubularReabsorptionFilteringSurfaceAreaBaseline = new SEScalarArea();
  return *m_LeftTubularReabsorptionFilteringSurfaceAreaBaseline;
}
double PulseConfiguration::GetLeftTubularReabsorptionFilteringSurfaceAreaBaseline(const AreaUnit& unit) const
{
  if (m_LeftTubularReabsorptionFilteringSurfaceAreaBaseline == nullptr)
    return SEScalar::dNaN();
  return m_LeftTubularReabsorptionFilteringSurfaceAreaBaseline->GetValue(unit);
}

bool PulseConfiguration::HasMaximumAfferentResistance() const
{
  return m_MaximumAfferentResistance == nullptr ? false : m_MaximumAfferentResistance->IsValid();
}
SEScalarFlowResistance& PulseConfiguration::GetMaximumAfferentResistance()
{
  if (m_MaximumAfferentResistance == nullptr)
    m_MaximumAfferentResistance = new SEScalarFlowResistance();
  return *m_MaximumAfferentResistance;
}
double PulseConfiguration::GetMaximumAfferentResistance(const FlowResistanceUnit& unit) const
{
  if (m_MaximumAfferentResistance == nullptr)
    return SEScalar::dNaN();
  return m_MaximumAfferentResistance->GetValue(unit);
}

bool PulseConfiguration::HasMinimumAfferentResistance() const
{
  return m_MinimumAfferentResistance == nullptr ? false : m_MinimumAfferentResistance->IsValid();
}
SEScalarFlowResistance& PulseConfiguration::GetMinimumAfferentResistance()
{
  if (m_MinimumAfferentResistance == nullptr)
    m_MinimumAfferentResistance = new SEScalarFlowResistance();
  return *m_MinimumAfferentResistance;
}
double PulseConfiguration::GetMinimumAfferentResistance(const FlowResistanceUnit& unit) const
{
  if (m_MinimumAfferentResistance == nullptr)
    return SEScalar::dNaN();
  return m_MinimumAfferentResistance->GetValue(unit);
}

bool PulseConfiguration::HasRightGlomerularFluidPermeabilityBaseline() const
{
  return m_RightGlomerularFluidPermeabilityBaseline == nullptr ? false : m_RightGlomerularFluidPermeabilityBaseline->IsValid();
}
SEScalarVolumePerTimePressureArea& PulseConfiguration::GetRightGlomerularFluidPermeabilityBaseline()
{
  if (m_RightGlomerularFluidPermeabilityBaseline == nullptr)
    m_RightGlomerularFluidPermeabilityBaseline = new SEScalarVolumePerTimePressureArea();
  return *m_RightGlomerularFluidPermeabilityBaseline;
}
double PulseConfiguration::GetRightGlomerularFluidPermeabilityBaseline(const VolumePerTimePressureAreaUnit& unit) const
{
  if (m_RightGlomerularFluidPermeabilityBaseline == nullptr)
    return SEScalar::dNaN();
  return m_RightGlomerularFluidPermeabilityBaseline->GetValue(unit);
}

bool PulseConfiguration::HasRightGlomerularFilteringSurfaceAreaBaseline() const
{
  return m_RightGlomerularFilteringSurfaceAreaBaseline == nullptr ? false : m_RightGlomerularFilteringSurfaceAreaBaseline->IsValid();
}
SEScalarArea& PulseConfiguration::GetRightGlomerularFilteringSurfaceAreaBaseline()
{
  if (m_RightGlomerularFilteringSurfaceAreaBaseline == nullptr)
    m_RightGlomerularFilteringSurfaceAreaBaseline = new SEScalarArea();
  return *m_RightGlomerularFilteringSurfaceAreaBaseline;
}
double PulseConfiguration::GetRightGlomerularFilteringSurfaceAreaBaseline(const AreaUnit& unit) const
{
  if (m_RightGlomerularFilteringSurfaceAreaBaseline == nullptr)
    return SEScalar::dNaN();
  return m_RightGlomerularFilteringSurfaceAreaBaseline->GetValue(unit);
}

bool PulseConfiguration::HasRightTubularReabsorptionFluidPermeabilityBaseline() const
{
  return m_RightTubularReabsorptionFluidPermeabilityBaseline == nullptr ? false : m_RightTubularReabsorptionFluidPermeabilityBaseline->IsValid();
}
SEScalarVolumePerTimePressureArea& PulseConfiguration::GetRightTubularReabsorptionFluidPermeabilityBaseline()
{
  if (m_RightTubularReabsorptionFluidPermeabilityBaseline == nullptr)
    m_RightTubularReabsorptionFluidPermeabilityBaseline = new SEScalarVolumePerTimePressureArea();
  return *m_RightTubularReabsorptionFluidPermeabilityBaseline;
}
double PulseConfiguration::GetRightTubularReabsorptionFluidPermeabilityBaseline(const VolumePerTimePressureAreaUnit& unit) const
{
  if (m_RightTubularReabsorptionFluidPermeabilityBaseline == nullptr)
    return SEScalar::dNaN();
  return m_RightTubularReabsorptionFluidPermeabilityBaseline->GetValue(unit);
}

bool PulseConfiguration::HasRightTubularReabsorptionFilteringSurfaceAreaBaseline() const
{
  return m_RightTubularReabsorptionFilteringSurfaceAreaBaseline == nullptr ? false : m_RightTubularReabsorptionFilteringSurfaceAreaBaseline->IsValid();
}
SEScalarArea& PulseConfiguration::GetRightTubularReabsorptionFilteringSurfaceAreaBaseline()
{
  if (m_RightTubularReabsorptionFilteringSurfaceAreaBaseline == nullptr)
    m_RightTubularReabsorptionFilteringSurfaceAreaBaseline = new SEScalarArea();
  return *m_RightTubularReabsorptionFilteringSurfaceAreaBaseline;
}
double PulseConfiguration::GetRightTubularReabsorptionFilteringSurfaceAreaBaseline(const AreaUnit& unit) const
{
  if (m_RightTubularReabsorptionFilteringSurfaceAreaBaseline == nullptr)
    return SEScalar::dNaN();
  return m_RightTubularReabsorptionFilteringSurfaceAreaBaseline->GetValue(unit);
}

bool PulseConfiguration::HasTargetSodiumDelivery()
{
  return m_TargetSodiumDelivery == nullptr ? false : m_TargetSodiumDelivery->IsValid();
}
SEScalarMassPerTime& PulseConfiguration::GetTargetSodiumDelivery()
{
  if (m_TargetSodiumDelivery == nullptr)
    m_TargetSodiumDelivery = new SEScalarMassPerTime();
  return *m_TargetSodiumDelivery;
}

//////////////////
/** Respiratory */
//////////////////
bool PulseConfiguration::HasCentralControllerCO2PressureSetPoint() const
{
  return m_CentralControllerCO2PressureSetPoint == nullptr ? false : m_CentralControllerCO2PressureSetPoint->IsValid();
}
SEScalarPressure& PulseConfiguration::GetCentralControllerCO2PressureSetPoint()
{
  if (m_CentralControllerCO2PressureSetPoint == nullptr)
    m_CentralControllerCO2PressureSetPoint = new SEScalarPressure();
  return *m_CentralControllerCO2PressureSetPoint;
}
double PulseConfiguration::GetCentralControllerCO2PressureSetPoint(const PressureUnit& unit) const
{
  if (m_CentralControllerCO2PressureSetPoint == nullptr)
    return SEScalar::dNaN();
  return m_CentralControllerCO2PressureSetPoint->GetValue(unit);
}

bool PulseConfiguration::HasCentralVentilatoryControllerGain() const
{
  return m_CentralVentilatoryControllerGain == nullptr ? false : m_CentralVentilatoryControllerGain->IsValid();
}
SEScalar& PulseConfiguration::GetCentralVentilatoryControllerGain()
{
  if (m_CentralVentilatoryControllerGain == nullptr)
    m_CentralVentilatoryControllerGain = new SEScalar();
  return *m_CentralVentilatoryControllerGain;
}
double PulseConfiguration::GetCentralVentilatoryControllerGain() const
{
  if (m_CentralVentilatoryControllerGain == nullptr)
    return SEScalar::dNaN();
  return m_CentralVentilatoryControllerGain->GetValue();
}

bool PulseConfiguration::HasPeripheralControllerCO2PressureSetPoint() const
{
  return m_PeripheralControllerCO2PressureSetPoint == nullptr ? false : m_PeripheralControllerCO2PressureSetPoint->IsValid();
}
SEScalarPressure& PulseConfiguration::GetPeripheralControllerCO2PressureSetPoint()
{
  if (m_PeripheralControllerCO2PressureSetPoint == nullptr)
    m_PeripheralControllerCO2PressureSetPoint = new SEScalarPressure();
  return *m_PeripheralControllerCO2PressureSetPoint;
}
double PulseConfiguration::GetPeripheralControllerCO2PressureSetPoint(const PressureUnit& unit) const
{
  if (m_PeripheralControllerCO2PressureSetPoint == nullptr)
    return SEScalar::dNaN();
  return m_PeripheralControllerCO2PressureSetPoint->GetValue(unit);
}

bool PulseConfiguration::HasPeripheralVentilatoryControllerGain() const
{
  return m_PeripheralVentilatoryControllerGain == nullptr ? false : m_PeripheralVentilatoryControllerGain->IsValid();
}
SEScalar& PulseConfiguration::GetPeripheralVentilatoryControllerGain()
{
  if (m_PeripheralVentilatoryControllerGain == nullptr)
    m_PeripheralVentilatoryControllerGain = new SEScalar();
  return *m_PeripheralVentilatoryControllerGain;
}
double PulseConfiguration::GetPeripheralVentilatoryControllerGain() const
{
  if (m_PeripheralVentilatoryControllerGain == nullptr)
    return SEScalar::dNaN();
  return m_PeripheralVentilatoryControllerGain->GetValue();
}

bool PulseConfiguration::HasPleuralComplianceSensitivity() const
{
  return m_PleuralComplianceSensitivity == nullptr ? false : m_PleuralComplianceSensitivity->IsValid();
}
SEScalarInverseVolume& PulseConfiguration::GetPleuralComplianceSensitivity()
{
  if (m_PleuralComplianceSensitivity == nullptr)
    m_PleuralComplianceSensitivity = new SEScalarInverseVolume();
  return *m_PleuralComplianceSensitivity;
}
double PulseConfiguration::GetPleuralComplianceSensitivity(const InverseVolumeUnit& unit) const
{
  if (m_PleuralComplianceSensitivity == nullptr)
    return SEScalar::dNaN();
  return m_PleuralComplianceSensitivity->GetValue(unit);
}

bool PulseConfiguration::HasPulmonaryVentilationRateMaximum() const
{
  return m_PulmonaryVentilationRateMaximum == nullptr ? false : m_PulmonaryVentilationRateMaximum->IsValid();
}
SEScalarVolumePerTime& PulseConfiguration::GetPulmonaryVentilationRateMaximum()
{
  if (m_PulmonaryVentilationRateMaximum == nullptr)
    m_PulmonaryVentilationRateMaximum = new SEScalarVolumePerTime();
  return *m_PulmonaryVentilationRateMaximum;
}
double PulseConfiguration::GetPulmonaryVentilationRateMaximum(const VolumePerTimeUnit& unit) const
{
  if (m_PulmonaryVentilationRateMaximum == nullptr)
    return SEScalar::dNaN();
  return m_PulmonaryVentilationRateMaximum->GetValue(unit);
}

bool PulseConfiguration::HasVentilatoryOcclusionPressure() const
{
  return m_VentilatoryOcclusionPressure == nullptr ? false : m_VentilatoryOcclusionPressure->IsValid();
}
SEScalarPressure& PulseConfiguration::GetVentilatoryOcclusionPressure()
{
  if (m_VentilatoryOcclusionPressure == nullptr)
    m_VentilatoryOcclusionPressure = new SEScalarPressure();
  return *m_VentilatoryOcclusionPressure;
}
double PulseConfiguration::GetVentilatoryOcclusionPressure(const PressureUnit& unit) const
{
  if (m_VentilatoryOcclusionPressure == nullptr)
    return SEScalar::dNaN();
  return m_VentilatoryOcclusionPressure->GetValue(unit);
}

bool PulseConfiguration::HasVentilationTidalVolumeIntercept() const
{
  return m_VentilationTidalVolumeIntercept == nullptr ? false : m_VentilationTidalVolumeIntercept->IsValid();
}
SEScalarVolume& PulseConfiguration::GetVentilationTidalVolumeIntercept()
{
  if (m_VentilationTidalVolumeIntercept == nullptr)
    m_VentilationTidalVolumeIntercept = new SEScalarVolume();
  return *m_VentilationTidalVolumeIntercept;
}
double PulseConfiguration::GetVentilationTidalVolumeIntercept(const VolumeUnit& unit) const
{
  if (m_VentilationTidalVolumeIntercept == nullptr)
    return SEScalar::dNaN();
  return m_VentilationTidalVolumeIntercept->GetValue(unit);
}