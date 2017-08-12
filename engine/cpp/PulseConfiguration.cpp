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
#include "properties/SEScalarMass.h"
#include "properties/SEScalarMassPerVolume.h"
#include "properties/SEScalarHeatCapacitancePerAmount.h"
#include "properties/SEScalarHeatCapacitancePerMass.h"
#include "properties/SEScalarHeatConductance.h"
#include "properties/SEScalarEnergyPerMass.h"
#include "properties/SEScalar0To1.h"
#include "properties/SEScalarVolume.h"
#include "properties/SEScalarArea.h"
#include "properties/SEScalarLength.h"
#include "properties/SEScalarAreaPerTimePressure.h"
#include "properties/SEScalarPressure.h"
#include "properties/SEScalarMassPerAmount.h"
#include "properties/SEScalarFlowResistance.h"
#include "properties/SEScalarFlowElastance.h"
#include "properties/SEScalarHeatResistance.h"
#include "properties/SEScalarElectricResistance.h"
#include "properties/SEScalarMassPerAmount.h"
#include "properties/SEScalarTemperature.h"
#include "properties/SEScalarEnergyPerAmount.h"
#include "properties/SEScalarTime.h"
#include "properties/SEScalarMassPerTime.h"
#include "properties/SEScalarVolumePerTimeArea.h"
#include "properties/SEScalarVolumePerTimePressureArea.h"
#include "properties/SEScalarVolumePerTime.h"
#include "properties/SEScalarInverseVolume.h"
#include "properties/SEScalarPowerPerAreaTemperatureToTheFourth.h"
#include "patient/SENutrition.h"
#include "engine/SEDynamicStabilization.h"
#include "engine/SETimedStabilization.h"
#include "engine/SEAutoSerialization.h"
#include "system/equipment/ElectroCardioGram/SEElectroCardioGramWaveformInterpolator.h"
#include <google/protobuf/text_format.h>


PulseConfiguration::PulseConfiguration(SESubstanceManager& substances) : SEEngineConfiguration(substances.GetLogger()), m_Substances(substances)
{
  m_Merge = false;
  m_TimeStep = nullptr;
  m_TimedStabilization = nullptr;
  m_DynamicStabilization = nullptr;
  m_AutoSerialization = nullptr;
  m_WritePatientBaselineFile = cdm::eSwitch::Off;

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
  m_PDEnabled = cdm::eSwitch::On;

  // ECG
  m_ECGInterpolator = nullptr;

  // Energy
  m_BodySpecificHeat = nullptr;
  m_CarbonDioxideProductionFromOxygenConsumptionConstant = nullptr;
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
  m_RenalEnabled = cdm::eSwitch::On;
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
  m_TissueEnabled = cdm::eSwitch::On;
}

PulseConfiguration::~PulseConfiguration()
{
  Clear();
}

void PulseConfiguration::Clear()
{
  SAFE_DELETE(m_TimeStep);
  RemoveStabilization();
  SAFE_DELETE(m_AutoSerialization);
  m_WritePatientBaselineFile = cdm::eSwitch::Off;

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
  m_PDEnabled = cdm::eSwitch::On;

  //  ECG
  SAFE_DELETE(m_ECGInterpolator);

  // Energy
  SAFE_DELETE(m_BodySpecificHeat);
  SAFE_DELETE(m_CarbonDioxideProductionFromOxygenConsumptionConstant);
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
  m_RenalEnabled = cdm::eSwitch::On;
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
  m_TissueEnabled = cdm::eSwitch::On;
}


void PulseConfiguration::Initialize()
{
  Clear();
  m_WritePatientBaselineFile = cdm::eSwitch::Off;

  // Reset to default values
  GetTimeStep().SetValue(1.0 / 50.0, TimeUnit::s);
  GetECGInterpolator().LoadFile("./ecg/StandardECG.pba",&GetTimeStep());
  GetDynamicStabilization().LoadFile("./config/DynamicStabilization.pba");
  //GetTimedStabilization().LoadFile("./config/TimedStabilization.pba");
  //GetDynamicStabilization().TrackStabilization(cdm::eSwitch::On);// Hard coded override for debugging
  
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
  GetCarbonDioxideProductionFromOxygenConsumptionConstant().SetValue(0.8);
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
  GetInitialEnvironmentalConditions().LoadFile("./environments/Standard.pba");
  GetWaterDensity().SetValue(1000, MassPerVolumeUnit::kg_Per_m3);

  // Gastrointestinal
  GetCalciumAbsorbtionFraction().SetValue(0.25);// Net fractional calcium absorption is 24.9 ± 12.4% (Hunt and Johnson 2007)
  GetCalciumDigestionRate().SetValue(2.7, MassPerTimeUnit::mg_Per_min);// Wasserman1992Intestinal
  GetCarbohydrateAbsorbtionFraction().SetValue(0.80);// Guyton p790
  GetDefaultCarbohydrateDigestionRate().SetValue(0.5, MassPerTimeUnit::g_Per_min);// Guyton (About 4.25hr to digest the carbs in default meal)
  GetDefaultFatDigestionRate().SetValue(0.055, MassPerTimeUnit::g_Per_min);// Guyton (About 8hr to digest the fat in the default meal)
  GetDefaultProteinDigestionRate().SetValue(0.071, MassPerTimeUnit::g_Per_min);// Dangin2001Digestion (About 5hr to digest the protein in the default meal)
  GetDefaultStomachContents().LoadFile("./nutrition/Standard.pba");// Refs are in the data spreadsheet
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

void PulseConfiguration::Merge(const PulseConfiguration& from)
{
    m_Merge = true;
    pulse::ConfigurationData* data = PulseConfiguration::Unload(from);
    PulseConfiguration::Load(*data, *this);
    delete data;
    m_Merge = false;
}

bool PulseConfiguration::LoadFile(const std::string& file)
{
  pulse::ConfigurationData src;
  std::ifstream file_stream(file, std::ios::in);
  std::string fmsg((std::istreambuf_iterator<char>(file_stream)), std::istreambuf_iterator<char>());
  if (!google::protobuf::TextFormat::ParseFromString(fmsg, &src))
    return false;
  PulseConfiguration::Load(src, *this);
  return true;

  // If its a binary string in the file...
  //std::ifstream binary_istream(patientFile, std::ios::in | std::ios::binary);
  //src.ParseFromIstream(&binary_istream);
}

void PulseConfiguration::Load(const pulse::ConfigurationData& src, PulseConfiguration& dst)
{
  PulseConfiguration::Serialize(src, dst);
}
void PulseConfiguration::Serialize(const pulse::ConfigurationData& src, PulseConfiguration& dst)
{
  if (!dst.m_Merge)
    dst.Clear();

  if (src.has_timestep())
    SEScalarTime::Load(src.timestep(), dst.GetTimeStep());
  if (src.has_timedstabilization())
    SETimedStabilization::Load(src.timedstabilization(), dst.GetTimedStabilization());
  else if (src.has_dynamicstabilization())
    SEDynamicStabilization::Load(src.dynamicstabilization(), dst.GetDynamicStabilization());
  else if (!src.stabilizationfilename().empty())
  {
    if (!dst.GetTimedStabilization().LoadFile(src.stabilizationfilename()))
      if (!dst.GetDynamicStabilization().LoadFile(src.stabilizationfilename()))
      {
        dst.Error("Unable to load stabilization file");
        dst.RemoveStabilization();
      }
  }
  if (src.has_autoserialization())
    SEAutoSerialization::Load(src.autoserialization(), dst.GetAutoSerialization());
  dst.EnableWritePatientBaselineFile(src.writepatientbaselinefile());

  //Barorecptors
  if (src.has_baroreceptorconfiguration())
  {
    const pulse::ConfigurationData_BaroreceptorConfigurationData& config = src.baroreceptorconfiguration();
    if (config.has_responseslope())
      SEScalar::Load(config.responseslope(),dst.GetResponseSlope());
    if (config.has_heartratedistributedtimedelay())
      SEScalarTime::Load(config.heartratedistributedtimedelay(),dst.GetHeartRateDistributedTimeDelay());
    if (config.has_heartelastancedistributedtimedelay())
      SEScalarTime::Load(config.heartelastancedistributedtimedelay(),dst.GetHeartElastanceDistributedTimeDelay());
    if (config.has_systemicresistancedistributedtimedelay())
      SEScalarTime::Load(config.systemicresistancedistributedtimedelay(),dst.GetSystemicResistanceDistributedTimeDelay());
    if (config.has_venouscompliancedistributedtimedelay())
      SEScalarTime::Load(config.venouscompliancedistributedtimedelay(),dst.GetVenousComplianceDistributedTimeDelay());
    if (config.has_normalizedheartrateintercept())
      SEScalar::Load(config.normalizedheartrateintercept(),dst.GetNormalizedHeartRateIntercept());
    if (config.has_normalizedheartratesympatheticslope())
      SEScalar::Load(config.normalizedheartratesympatheticslope(),dst.GetNormalizedHeartRateSympatheticSlope());
    if (config.has_normalizedheartrateparasympatheticslope())
      SEScalar::Load(config.normalizedheartrateparasympatheticslope(),dst.GetNormalizedHeartRateParasympatheticSlope());
    if (config.has_normalizedheartelastanceintercept())
      SEScalar::Load(config.normalizedheartelastanceintercept(),dst.GetNormalizedHeartElastanceIntercept());
    if (config.has_normalizedheartelastancesympatheticslope())
      SEScalar::Load(config.normalizedheartelastancesympatheticslope(),dst.GetNormalizedHeartElastanceSympatheticSlope());
    if (config.has_normalizedresistanceintercept())
      SEScalar::Load(config.normalizedresistanceintercept(),dst.GetNormalizedResistanceIntercept());
    if (config.has_normalizedresistancesympatheticslope())
      SEScalar::Load(config.normalizedresistancesympatheticslope(),dst.GetNormalizedResistanceSympatheticSlope());
    if (config.has_normalizedcomplianceintercept())
      SEScalar::Load(config.normalizedcomplianceintercept(),dst.GetNormalizedComplianceIntercept());
    if (config.has_normalizedcomplianceparasympatheticslope())
      SEScalar::Load(config.normalizedcomplianceparasympatheticslope(),dst.GetNormalizedComplianceParasympatheticSlope());
  }

  // Blood Chemistry
  if (src.has_bloodchemistryconfiguration())
  {
    const pulse::ConfigurationData_BloodChemistryConfigurationData& config = src.bloodchemistryconfiguration();
    if (config.has_meancorpuscularvolume())
      SEScalarVolume::Load(config.meancorpuscularvolume(),dst.GetMeanCorpuscularVolume());
    if (config.has_meancorpuscularhemoglobin())
      SEScalarMassPerAmount::Load(config.meancorpuscularhemoglobin(),dst.GetMeanCorpuscularHemoglobin());
    if (config.has_standarddiffusiondistance())
      SEScalarLength::Load(config.standarddiffusiondistance(),dst.GetStandardDiffusionDistance());
    if (config.has_standardoxygendiffusioncoefficient())
      SEScalarAreaPerTimePressure::Load(config.standardoxygendiffusioncoefficient(),dst.GetStandardOxygenDiffusionCoefficient());
  }

  // Cardiovascular
  if (src.has_cardiovascularconfiguration())
  {
    const pulse::ConfigurationData_CardiovascularConfigurationData& config = src.cardiovascularconfiguration();
    if (config.has_leftheartelastancemaximum())
      SEScalarFlowElastance::Load(config.leftheartelastancemaximum(),dst.GetLeftHeartElastanceMaximum());
    if (config.has_leftheartelastanceminimum())
      SEScalarFlowElastance::Load(config.leftheartelastanceminimum(),dst.GetLeftHeartElastanceMinimum());
    if (config.has_minimumbloodvolumefraction())
      SEScalar0To1::Load(config.minimumbloodvolumefraction(),dst.GetMinimumBloodVolumeFraction());
    if (config.has_rightheartelastancemaximum())
      SEScalarFlowElastance::Load(config.rightheartelastancemaximum(),dst.GetRightHeartElastanceMaximum());
    if (config.has_rightheartelastanceminimum())
      SEScalarFlowElastance::Load(config.rightheartelastanceminimum(),dst.GetRightHeartElastanceMinimum());
    if (config.has_standardpulmonarycapillarycoverage())
      SEScalar::Load(config.standardpulmonarycapillarycoverage(),dst.GetStandardPulmonaryCapillaryCoverage());
  }

  // Circuit
  if (src.has_circuitconfiguration())
  {
    const pulse::ConfigurationData_CircuitConfigurationData& config = src.circuitconfiguration();
    if (config.has_cardiovascularopenresistance())
      SEScalarFlowResistance::Load(config.cardiovascularopenresistance(),dst.GetCardiovascularOpenResistance());
    if (config.has_defaultopenelectricresistance())
      SEScalarElectricResistance::Load(config.defaultopenelectricresistance(),dst.GetDefaultOpenElectricResistance());
    if (config.has_defaultopenflowresistance())
      SEScalarFlowResistance::Load(config.defaultopenflowresistance(),dst.GetDefaultOpenFlowResistance());
    if (config.has_defaultopenheatresistance())
      SEScalarHeatResistance::Load(config.defaultopenheatresistance(),dst.GetDefaultOpenHeatResistance());
    if (config.has_defaultclosedelectricresistance())
      SEScalarElectricResistance::Load(config.defaultclosedelectricresistance(),dst.GetDefaultClosedElectricResistance());
    if (config.has_defaultclosedflowresistance())
      SEScalarFlowResistance::Load(config.defaultclosedflowresistance(),dst.GetDefaultClosedFlowResistance());
    if (config.has_defaultclosedheatresistance())
      SEScalarHeatResistance::Load(config.defaultclosedheatresistance(),dst.GetDefaultClosedHeatResistance());
    if (config.has_machineclosedresistance())
      SEScalarFlowResistance::Load(config.machineclosedresistance(),dst.GetMachineClosedResistance());
    if (config.has_machineopenresistance())
      SEScalarFlowResistance::Load(config.machineopenresistance(),dst.GetMachineOpenResistance());
    if (config.has_respiratoryclosedresistance())
      SEScalarFlowResistance::Load(config.respiratoryclosedresistance(),dst.GetRespiratoryClosedResistance());
    if (config.has_respiratoryopenresistance())
      SEScalarFlowResistance::Load(config.respiratoryopenresistance(),dst.GetRespiratoryOpenResistance());
  }

  // Constants
  if (src.has_constantsconfiguration())
  {
    const pulse::ConfigurationData_ConstantsConfigurationData& config = src.constantsconfiguration();
    if (config.has_oxygenmetabolicconstant())
      SEScalar::Load(config.oxygenmetabolicconstant(),dst.GetOxygenMetabolicConstant());
    if (config.has_stefanboltzmann())
      SEScalarPowerPerAreaTemperatureToTheFourth::Load(config.stefanboltzmann(),dst.GetStefanBoltzmann());
    if (config.has_universalgasconstant())
      SEScalarHeatCapacitancePerAmount::Load(config.universalgasconstant(),dst.GetUniversalGasConstant());
  }

  // Drugs
  if (src.has_drugsconfiguration())
  {
    const pulse::ConfigurationData_DrugsConfigurationData& config = src.drugsconfiguration();
    dst.m_PDEnabled = config.pdmodel();
  }
  
  // Energy
  if (src.has_energyconfiguration())
  {
    const pulse::ConfigurationData_EnergyConfigurationData& config = src.energyconfiguration();
    if (config.has_bodyspecificheat())
      SEScalarHeatCapacitancePerMass::Load(config.bodyspecificheat(),dst.GetBodySpecificHeat());
    if (config.has_carbondioxideproductionfromoxygenconsumptionconstant())
      SEScalar::Load(config.carbondioxideproductionfromoxygenconsumptionconstant(),dst.GetCarbonDioxideProductionFromOxygenConsumptionConstant());
    if (config.has_coretemperaturelow())
      SEScalarTemperature::Load(config.coretemperaturelow(),dst.GetCoreTemperatureLow());
    if (config.has_coretemperaturehigh())
      SEScalarTemperature::Load(config.coretemperaturehigh(),dst.GetCoreTemperatureHigh());
    if (config.has_deltacoretemperaturelow())
      SEScalarTemperature::Load(config.deltacoretemperaturelow(),dst.GetDeltaCoreTemperatureLow());
    if (config.has_energyperatp())
      SEScalarEnergyPerAmount::Load(config.energyperatp(),dst.GetEnergyPerATP());
    if (config.has_sweatheattransfer())
      SEScalarHeatConductance::Load(config.sweatheattransfer(),dst.GetSweatHeatTransfer());
    if (config.has_vaporizationenergy())
      SEScalarEnergyPerMass::Load(config.vaporizationenergy(),dst.GetVaporizationEnergy());
    if (config.has_vaporspecificheat())
      SEScalarHeatCapacitancePerMass::Load(config.vaporspecificheat(),dst.GetVaporSpecificHeat());
  }

  // Environment
  if (src.has_environmentconfiguration())
  {
    const pulse::ConfigurationData_EnvironmentConfigurationData& config = src.environmentconfiguration();
    if (config.has_airdensity())
      SEScalarMassPerVolume::Load(config.airdensity(),dst.GetAirDensity());
    if (config.has_airspecificheat())
      SEScalarHeatCapacitancePerMass::Load(config.airspecificheat(),dst.GetAirSpecificHeat());
    if (config.has_molarmassofdryair())
      SEScalarMassPerAmount::Load(config.molarmassofdryair(),dst.GetMolarMassOfDryAir());
    if (config.has_molarmassofwatervapor())
      SEScalarMassPerAmount::Load(config.molarmassofwatervapor(),dst.GetMolarMassOfWaterVapor());
    if (!config.initialconditionsfile().empty())
    {
      if (!dst.GetInitialEnvironmentalConditions().LoadFile(config.initialconditionsfile()))
      {
        dst.Error("Unable to load InitialEnvironmentalConditions file");
      }
    }
    else if (config.has_initialconditions())
    {
      SEEnvironmentalConditions::Load(config.initialconditions(), dst.GetInitialEnvironmentalConditions());
    }
    if (config.has_waterdensity())
      SEScalarMassPerVolume::Load(config.waterdensity(),dst.GetWaterDensity());
  }

  // Gastrointestinal
  if (src.has_gastrointestinalconfiguration())
  {
    const pulse::ConfigurationData_GastrointestinalConfigurationData& config = src.gastrointestinalconfiguration();
    if (config.has_calciumabsorbtionfraction())
      SEScalar0To1::Load(config.calciumabsorbtionfraction(),dst.GetCalciumAbsorbtionFraction());
    if (config.has_calciumdigestionrate())
      SEScalarMassPerTime::Load(config.calciumdigestionrate(),dst.GetCalciumDigestionRate());
    if (config.has_carbohydrateabsorbtionfraction())
      SEScalar0To1::Load(config.carbohydrateabsorbtionfraction(),dst.GetCarbohydrateAbsorbtionFraction());
    if (config.has_defaultcarbohydratedigestionrate())
      SEScalarMassPerTime::Load(config.defaultcarbohydratedigestionrate(),dst.GetDefaultCarbohydrateDigestionRate());
    if (config.has_defaultfatdigestionrate())
      SEScalarMassPerTime::Load(config.defaultfatdigestionrate(),dst.GetDefaultFatDigestionRate());
    if (config.has_defaultproteindigestionrate())
      SEScalarMassPerTime::Load(config.defaultproteindigestionrate(),dst.GetDefaultProteinDigestionRate());
    if (!config.initialstomachcontentsfile().empty())
    {
      if(!dst.GetDefaultStomachContents().LoadFile(config.initialstomachcontentsfile()))
      {
        dst.Error("Unable to load Standard Stomach Contents file");
      }
    }
    else if (config.has_initialstomachcontents())
    {
      SENutrition::Load(config.initialstomachcontents(), dst.GetDefaultStomachContents());
    }
    // Use default rate if they are not set
    {
      if (dst.m_DefaultStomachContents->HasCarbohydrate() && !dst.m_DefaultStomachContents->HasCarbohydrateDigestionRate())
        dst.m_DefaultStomachContents->GetCarbohydrateDigestionRate().Set(dst.GetDefaultCarbohydrateDigestionRate());
      if (dst.m_DefaultStomachContents->HasFat() && !dst.m_DefaultStomachContents->HasFatDigestionRate())
        dst.m_DefaultStomachContents->GetFatDigestionRate().Set(dst.GetDefaultFatDigestionRate());
      if (dst.m_DefaultStomachContents->HasProtein() && !dst.m_DefaultStomachContents->HasProteinDigestionRate())
        dst.m_DefaultStomachContents->GetProteinDigestionRate().Set(dst.GetDefaultProteinDigestionRate());
    }
    if (config.has_fatabsorbtionfraction())
      SEScalar0To1::Load(config.fatabsorbtionfraction(),dst.GetFatAbsorbtionFraction());
    if (config.has_proteintoureafraction())
      SEScalar0To1::Load(config.proteintoureafraction(),dst.GetProteinToUreaFraction());
    if (config.has_waterdigestionrate())
      SEScalarVolumePerTime::Load(config.waterdigestionrate(),dst.GetWaterDigestionRate());
  }

  // Nervous
  if (src.has_nervousconfiguration())
  {
    const pulse::ConfigurationData_NervousConfigurationData& config = src.nervousconfiguration();
    if (config.has_pupildiameterbaseline())
      SEScalarLength::Load(config.pupildiameterbaseline(),dst.GetPupilDiameterBaseline());
  }

  // Renal
  if (src.has_renalconfiguration())
  {
    const pulse::ConfigurationData_RenalConfigurationData& config = src.renalconfiguration();

    dst.EnableRenal(config.enablerenal());

    if (config.has_plasmasodiumconcentrationsetpoint())
      SEScalarMassPerVolume::Load(config.plasmasodiumconcentrationsetpoint(),dst.GetPlasmaSodiumConcentrationSetPoint());

    if (config.has_leftglomerularfluidpermeabilitybaseline())
      SEScalarVolumePerTimePressureArea::Load(config.leftglomerularfluidpermeabilitybaseline(),dst.GetLeftGlomerularFluidPermeabilityBaseline());
    if (config.has_leftglomerularfilteringsurfaceareabaseline())
      SEScalarArea::Load(config.leftglomerularfilteringsurfaceareabaseline(),dst.GetLeftGlomerularFilteringSurfaceAreaBaseline());
    if (config.has_lefttubularreabsorptionfluidpermeabilitybaseline())
      SEScalarVolumePerTimePressureArea::Load(config.lefttubularreabsorptionfluidpermeabilitybaseline(),dst.GetLeftTubularReabsorptionFluidPermeabilityBaseline());
    if (config.has_lefttubularreabsorptionfilteringsurfaceareabaseline())
      SEScalarArea::Load(config.lefttubularreabsorptionfilteringsurfaceareabaseline(),dst.GetLeftTubularReabsorptionFilteringSurfaceAreaBaseline());
    
    if (config.has_maximumafferentresistance())
      SEScalarFlowResistance::Load(config.maximumafferentresistance(),dst.GetMaximumAfferentResistance());
    if (config.has_minimumafferentresistance())
      SEScalarFlowResistance::Load(config.minimumafferentresistance(),dst.GetMinimumAfferentResistance());
      
    if (config.has_rightglomerularfluidpermeabilitybaseline())
      SEScalarVolumePerTimePressureArea::Load(config.rightglomerularfluidpermeabilitybaseline(),dst.GetRightGlomerularFluidPermeabilityBaseline());
    if (config.has_rightglomerularfilteringsurfaceareabaseline())
      SEScalarArea::Load(config.rightglomerularfilteringsurfaceareabaseline(),dst.GetRightGlomerularFilteringSurfaceAreaBaseline());
    if (config.has_righttubularreabsorptionfluidpermeabilitybaseline())
      SEScalarVolumePerTimePressureArea::Load(config.righttubularreabsorptionfluidpermeabilitybaseline(),dst.GetRightTubularReabsorptionFluidPermeabilityBaseline());
    if (config.has_righttubularreabsorptionfilteringsurfaceareabaseline())
      SEScalarArea::Load(config.righttubularreabsorptionfilteringsurfaceareabaseline(),dst.GetRightTubularReabsorptionFilteringSurfaceAreaBaseline());

    if (config.has_targetsodiumdelivery())
      SEScalarMassPerTime::Load(config.targetsodiumdelivery(), dst.GetTargetSodiumDelivery());
  }
  
  // Respiratory
  if (src.has_respiratoryconfiguration())
  {
    const pulse::ConfigurationData_RespiratoryConfigurationData& config = src.respiratoryconfiguration();
    if (config.has_centralcontrollerco2pressuresetpoint())
      SEScalarPressure::Load(config.centralcontrollerco2pressuresetpoint(),dst.GetCentralControllerCO2PressureSetPoint());
    if (config.has_centralventilatorycontrollergain())
      SEScalar::Load(config.centralventilatorycontrollergain(),dst.GetCentralVentilatoryControllerGain());
    if (config.has_peripheralcontrollerco2pressuresetpoint())
      SEScalarPressure::Load(config.peripheralcontrollerco2pressuresetpoint(),dst.GetPeripheralControllerCO2PressureSetPoint());
    if (config.has_peripheralventilatorycontrollergain())
      SEScalar::Load(config.peripheralventilatorycontrollergain(),dst.GetPeripheralVentilatoryControllerGain());
    if (config.has_pleuralcompliancesensitivity())
      SEScalarInverseVolume::Load(config.pleuralcompliancesensitivity(),dst.GetPleuralComplianceSensitivity());
    if (config.has_pulmonaryventilationratemaximum())
      SEScalarVolumePerTime::Load(config.pulmonaryventilationratemaximum(),dst.GetPulmonaryVentilationRateMaximum());
    if (config.has_ventilationtidalvolumeintercept())
      SEScalarVolume::Load(config.ventilationtidalvolumeintercept(),dst.GetVentilationTidalVolumeIntercept());
    if (config.has_ventilatoryocclusionpressure())
      SEScalarPressure::Load(config.ventilatoryocclusionpressure(),dst.GetVentilatoryOcclusionPressure());
  }

  // Tissue
  if (src.has_tissueconfiguration())
  {
    const pulse::ConfigurationData_TissueConfigurationData& config = src.tissueconfiguration();
    dst.EnableTissue(config.enabletissue());
  }
}

pulse::ConfigurationData* PulseConfiguration::Unload(const PulseConfiguration& src)
{
  pulse::ConfigurationData* dst = new pulse::ConfigurationData();
  PulseConfiguration::Serialize(src, *dst);
  return dst;
}
void PulseConfiguration::Serialize(const PulseConfiguration& src, pulse::ConfigurationData& dst)
{
  if (src.HasTimedStabilization())
    dst.set_allocated_timedstabilization(SETimedStabilization::Unload(*src.m_TimedStabilization));
  else if (src.HasDynamicStabilization())
    dst.set_allocated_dynamicstabilization(SEDynamicStabilization::Unload(*src.m_DynamicStabilization));
  if (src.HasTimeStep())
    dst.set_allocated_timestep(SEScalarTime::Unload(*src.m_TimeStep));
  if (src.HasAutoSerialization())
    dst.set_allocated_autoserialization(SEAutoSerialization::Unload(*src.m_AutoSerialization));
  dst.set_writepatientbaselinefile(src.m_WritePatientBaselineFile);

  // Barorecptor
  pulse::ConfigurationData_BaroreceptorConfigurationData* baro = dst.mutable_baroreceptorconfiguration();
  if (src.HasResponseSlope())
    baro->set_allocated_responseslope(SEScalar::Unload(*src.m_ResponseSlope));
  if (src.HasHeartRateDistributedTimeDelay())
    baro->set_allocated_heartratedistributedtimedelay(SEScalarTime::Unload(*src.m_HeartRateDistributedTimeDelay));
  if (src.HasHeartElastanceDistributedTimeDelay())
    baro->set_allocated_heartelastancedistributedtimedelay(SEScalarTime::Unload(*src.m_HeartElastanceDistributedTimeDelay));
  if (src.HasSystemicResistanceDistributedTimeDelay())
    baro->set_allocated_systemicresistancedistributedtimedelay(SEScalarTime::Unload(*src.m_SystemicResistanceDistributedTimeDelay));
  if (src.HasVenousComplianceDistributedTimeDelay())
    baro->set_allocated_venouscompliancedistributedtimedelay(SEScalarTime::Unload(*src.m_VenousComplianceDistributedTimeDelay));
  if (src.HasNormalizedHeartRateIntercept())
    baro->set_allocated_normalizedheartrateintercept(SEScalar::Unload(*src.m_NormalizedHeartRateIntercept));
  if (src.HasNormalizedHeartRateSympatheticSlope())
    baro->set_allocated_normalizedheartratesympatheticslope(SEScalar::Unload(*src.m_NormalizedHeartRateSympatheticSlope));
  if (src.HasNormalizedHeartRateParasympatheticSlope())
    baro->set_allocated_normalizedheartrateparasympatheticslope(SEScalar::Unload(*src.m_NormalizedHeartRateParasympatheticSlope));
  if (src.HasNormalizedHeartElastanceIntercept())
    baro->set_allocated_normalizedheartelastanceintercept(SEScalar::Unload(*src.m_NormalizedHeartElastanceIntercept));
  if (src.HasNormalizedHeartElastanceSympatheticSlope())
    baro->set_allocated_normalizedheartelastancesympatheticslope(SEScalar::Unload(*src.m_NormalizedHeartElastanceSympatheticSlope));
  if (src.HasNormalizedResistanceIntercept())
    baro->set_allocated_normalizedresistanceintercept(SEScalar::Unload(*src.m_NormalizedResistanceIntercept));
  if (src.HasNormalizedResistanceSympatheticSlope())
    baro->set_allocated_normalizedresistancesympatheticslope(SEScalar::Unload(*src.m_NormalizedResistanceSympatheticSlope));
  if (src.HasNormalizedComplianceIntercept())
    baro->set_allocated_normalizedcomplianceintercept(SEScalar::Unload(*src.m_NormalizedComplianceIntercept));
  if (src.HasNormalizedComplianceParasympatheticSlope())
    baro->set_allocated_normalizedcomplianceparasympatheticslope(SEScalar::Unload(*src.m_NormalizedComplianceParasympatheticSlope));

  // Blood Chemistry
  pulse::ConfigurationData_BloodChemistryConfigurationData* bc = dst.mutable_bloodchemistryconfiguration();
  if (src.HasMeanCorpuscularHemoglobin())
    bc->set_allocated_meancorpuscularhemoglobin(SEScalarMassPerAmount::Unload(*src.m_MeanCorpuscularHemoglobin));
  if (src.HasMeanCorpuscularVolume())
    bc->set_allocated_meancorpuscularvolume(SEScalarVolume::Unload(*src.m_MeanCorpuscularVolume));
  if (src.HasStandardDiffusionDistance())
    bc->set_allocated_standarddiffusiondistance(SEScalarLength::Unload(*src.m_StandardDiffusionDistance));
  if (src.HasStandardOxygenDiffusionCoefficient())
    bc->set_allocated_standardoxygendiffusioncoefficient(SEScalarAreaPerTimePressure::Unload(*src.m_StandardOxygenDiffusionCoefficient));

  // Cardiovascular
  pulse::ConfigurationData_CardiovascularConfigurationData* cv = dst.mutable_cardiovascularconfiguration();
  if (src.HasLeftHeartElastanceMaximum())
    cv->set_allocated_leftheartelastancemaximum(SEScalarFlowElastance::Unload(*src.m_LeftHeartElastanceMaximum));
  if (src.HasLeftHeartElastanceMinimum())
    cv->set_allocated_leftheartelastanceminimum(SEScalarFlowElastance::Unload(*src.m_LeftHeartElastanceMinimum));
  if (src.HasMinimumBloodVolumeFraction())
    cv->set_allocated_minimumbloodvolumefraction(SEScalar0To1::Unload(*src.m_MinimumBloodVolumeFraction));
  if (src.HasRightHeartElastanceMaximum())
    cv->set_allocated_rightheartelastancemaximum(SEScalarFlowElastance::Unload(*src.m_RightHeartElastanceMaximum));
  if (src.HasRightHeartElastanceMinimum())
    cv->set_allocated_rightheartelastanceminimum(SEScalarFlowElastance::Unload(*src.m_RightHeartElastanceMinimum));
  if (src.HasStandardPulmonaryCapillaryCoverage())
    cv->set_allocated_standardpulmonarycapillarycoverage(SEScalar::Unload(*src.m_StandardPulmonaryCapillaryCoverage));

  // Circuits
  pulse::ConfigurationData_CircuitConfigurationData* circuit = dst.mutable_circuitconfiguration();
  if (src.HasCardiovascularOpenResistance())
    circuit->set_allocated_cardiovascularopenresistance(SEScalarFlowResistance::Unload(*src.m_CardiovascularOpenResistance));
  if (src.HasDefaultClosedElectricResistance())
    circuit->set_allocated_defaultclosedelectricresistance(SEScalarElectricResistance::Unload(*src.m_DefaultClosedElectricResistance));
  if (src.HasDefaultClosedFlowResistance())
    circuit->set_allocated_defaultclosedflowresistance(SEScalarFlowResistance::Unload(*src.m_DefaultClosedFlowResistance));
  if (src.HasDefaultClosedHeatResistance())
    circuit->set_allocated_defaultclosedheatresistance(SEScalarHeatResistance::Unload(*src.m_DefaultClosedHeatResistance));
  if (src.HasDefaultOpenElectricResistance())
    circuit->set_allocated_defaultopenelectricresistance(SEScalarElectricResistance::Unload(*src.m_DefaultOpenElectricResistance));
  if (src.HasDefaultOpenFlowResistance())
    circuit->set_allocated_defaultopenflowresistance(SEScalarFlowResistance::Unload(*src.m_DefaultOpenFlowResistance));
  if (src.HasDefaultOpenHeatResistance())
    circuit->set_allocated_defaultopenheatresistance(SEScalarHeatResistance::Unload(*src.m_DefaultOpenHeatResistance));
  if (src.HasMachineClosedResistance())
    circuit->set_allocated_machineclosedresistance(SEScalarFlowResistance::Unload(*src.m_MachineClosedResistance));
  if (src.HasMachineOpenResistance())
    circuit->set_allocated_machineopenresistance(SEScalarFlowResistance::Unload(*src.m_MachineOpenResistance));
  if (src.HasRespiratoryClosedResistance())
    circuit->set_allocated_respiratoryclosedresistance(SEScalarFlowResistance::Unload(*src.m_RespiratoryClosedResistance));
  if (src.HasRespiratoryOpenResistance())
    circuit->set_allocated_respiratoryopenresistance(SEScalarFlowResistance::Unload(*src.m_RespiratoryOpenResistance));

  // Constants
  pulse::ConfigurationData_ConstantsConfigurationData* consts = dst.mutable_constantsconfiguration();
  if (src.HasOxygenMetabolicConstant())
    consts->set_allocated_oxygenmetabolicconstant(SEScalar::Unload(*src.m_OxygenMetabolicConstant));
  if (src.HasStefanBoltzmann())
    consts->set_allocated_stefanboltzmann(SEScalarPowerPerAreaTemperatureToTheFourth::Unload(*src.m_StefanBoltzmann));
  if (src.HasUniversalGasConstant())
    consts->set_allocated_universalgasconstant(SEScalarHeatCapacitancePerAmount::Unload(*src.m_UniversalGasConstant));

  // Drugs
  pulse::ConfigurationData_DrugsConfigurationData* drugs = dst.mutable_drugsconfiguration();
  if(src.IsPDEnabled())
    drugs->set_pdmodel(src.m_PDEnabled);

  // Energy
  pulse::ConfigurationData_EnergyConfigurationData* energy = dst.mutable_energyconfiguration();
  if (src.HasBodySpecificHeat())
    energy->set_allocated_bodyspecificheat(SEScalarHeatCapacitancePerMass::Unload(*src.m_BodySpecificHeat));
  if (src.HasCarbonDioxideProductionFromOxygenConsumptionConstant())
    energy->set_allocated_carbondioxideproductionfromoxygenconsumptionconstant(SEScalar::Unload(*src.m_CarbonDioxideProductionFromOxygenConsumptionConstant));
  if (src.HasCoreTemperatureLow())
    energy->set_allocated_coretemperaturelow(SEScalarTemperature::Unload(*src.m_CoreTemperatureLow));
  if (src.HasCoreTemperatureHigh())
    energy->set_allocated_coretemperaturehigh(SEScalarTemperature::Unload(*src.m_CoreTemperatureHigh));
  if (src.HasDeltaCoreTemperatureLow())
    energy->set_allocated_deltacoretemperaturelow(SEScalarTemperature::Unload(*src.m_DeltaCoreTemperatureLow));
  if (src.HasEnergyPerATP())
    energy->set_allocated_energyperatp(SEScalarEnergyPerAmount::Unload(*src.m_EnergyPerATP));
  if (src.HasSweatHeatTransfer())
    energy->set_allocated_sweatheattransfer(SEScalarHeatConductance::Unload(*src.m_SweatHeatTransfer));
  if (src.HasVaporSpecificHeat())
    energy->set_allocated_vaporspecificheat(SEScalarHeatCapacitancePerMass::Unload(*src.m_VaporSpecificHeat));
  if (src.HasVaporizationEnergy())
    energy->set_allocated_vaporizationenergy(SEScalarEnergyPerMass::Unload(*src.m_VaporizationEnergy));

  // Environment
  pulse::ConfigurationData_EnvironmentConfigurationData* env = dst.mutable_environmentconfiguration();
  if (src.HasAirDensity())
    env->set_allocated_airdensity(SEScalarMassPerVolume::Unload(*src.m_AirDensity));
  if (src.HasAirSpecificHeat())
    env->set_allocated_airspecificheat(SEScalarHeatCapacitancePerMass::Unload(*src.m_AirSpecificHeat));
  if (src.HasMolarMassOfDryAir())
    env->set_allocated_molarmassofdryair(SEScalarMassPerAmount::Unload(*src.m_MolarMassOfDryAir));
  if (src.HasMolarMassOfWaterVapor())
    env->set_allocated_molarmassofwatervapor(SEScalarMassPerAmount::Unload(*src.m_MolarMassOfWaterVapor));
  if (src.HasInitialEnvironmentalConditions())
    env->set_allocated_initialconditions(SEEnvironmentalConditions::Unload(*src.m_InitialEnvironmentalConditions));
  if (src.HasWaterDensity())
    env->set_allocated_waterdensity(SEScalarMassPerVolume::Unload(*src.m_WaterDensity));

  // Gastrointestinal
  pulse::ConfigurationData_GastrointestinalConfigurationData* gi = dst.mutable_gastrointestinalconfiguration();
  if (src.HasCalciumAbsorbtionFraction())
    gi->set_allocated_calciumabsorbtionfraction(SEScalar0To1::Unload(*src.m_CalciumAbsorbtionFraction));
  if (src.HasCalciumDigestionRate())
    gi->set_allocated_calciumdigestionrate(SEScalarMassPerTime::Unload(*src.m_CalciumDigestionRate));
  if (src.HasCarbohydrateAbsorbtionFraction())
    gi->set_allocated_carbohydrateabsorbtionfraction(SEScalar0To1::Unload(*src.m_CarbohydrateAbsorbtionFraction));
  if (src.HasDefaultCarbohydrateDigestionRate())
    gi->set_allocated_defaultcarbohydratedigestionrate(SEScalarMassPerTime::Unload(*src.m_DefaultCarbohydrateDigestionRate));
  if (src.HasDefaultFatDigestionRate())
    gi->set_allocated_defaultfatdigestionrate(SEScalarMassPerTime::Unload(*src.m_DefaultFatDigestionRate));
  if (src.HasDefaultProteinDigestionRate())
    gi->set_allocated_defaultproteindigestionrate(SEScalarMassPerTime::Unload(*src.m_DefaultProteinDigestionRate));
  if (src.HasDefaultStomachContents())
    gi->set_allocated_initialstomachcontents(SENutrition::Unload(*src.m_DefaultStomachContents));
  if (src.HasFatAbsorbtionFraction())
    gi->set_allocated_fatabsorbtionfraction(SEScalar0To1::Unload(*src.m_FatAbsorbtionFraction));
  if (src.HasProteinToUreaFraction())
    gi->set_allocated_proteintoureafraction(SEScalar0To1::Unload(*src.m_ProteinToUreaFraction));
  if (src.HasWaterDigestionRate())
    gi->set_allocated_waterdigestionrate(SEScalarVolumePerTime::Unload(*src.m_WaterDigestionRate));

  // Nervous
  pulse::ConfigurationData_NervousConfigurationData* n = dst.mutable_nervousconfiguration();
  if (src.HasPupilDiameterBaseline())
    n->set_allocated_pupildiameterbaseline(SEScalarLength::Unload(*src.m_PupilDiameterBaseline));

  // Renal
  pulse::ConfigurationData_RenalConfigurationData* renal = dst.mutable_renalconfiguration();
  if (src.IsRenalEnabled())
    renal->set_enablerenal(src.m_RenalEnabled);
  if (src.HasPlasmaSodiumConcentrationSetPoint())
    renal->set_allocated_plasmasodiumconcentrationsetpoint(SEScalarMassPerVolume::Unload(*src.m_PlasmaSodiumConcentrationSetPoint));
  if (src.HasLeftGlomerularFilteringSurfaceAreaBaseline())
    renal->set_allocated_leftglomerularfilteringsurfaceareabaseline(SEScalarArea::Unload(*src.m_LeftGlomerularFilteringSurfaceAreaBaseline));
  if (src.HasLeftGlomerularFluidPermeabilityBaseline())
    renal->set_allocated_leftglomerularfluidpermeabilitybaseline(SEScalarVolumePerTimePressureArea::Unload(*src.m_LeftGlomerularFluidPermeabilityBaseline));
  if (src.HasLeftTubularReabsorptionFilteringSurfaceAreaBaseline())
    renal->set_allocated_lefttubularreabsorptionfilteringsurfaceareabaseline(SEScalarArea::Unload(*src.m_LeftTubularReabsorptionFilteringSurfaceAreaBaseline));
  if (src.HasLeftTubularReabsorptionFluidPermeabilityBaseline())
    renal->set_allocated_lefttubularreabsorptionfluidpermeabilitybaseline(SEScalarVolumePerTimePressureArea::Unload(*src.m_LeftTubularReabsorptionFluidPermeabilityBaseline));

  if (src.HasMaximumAfferentResistance())
    renal->set_allocated_maximumafferentresistance(SEScalarFlowResistance::Unload(*src.m_MaximumAfferentResistance));
  if (src.HasMinimumAfferentResistance())
    renal->set_allocated_minimumafferentresistance(SEScalarFlowResistance::Unload(*src.m_MinimumAfferentResistance));
  
  if (src.HasRightGlomerularFilteringSurfaceAreaBaseline())
    renal->set_allocated_rightglomerularfilteringsurfaceareabaseline(SEScalarArea::Unload(*src.m_RightGlomerularFilteringSurfaceAreaBaseline));
  if (src.HasRightGlomerularFluidPermeabilityBaseline())
    renal->set_allocated_rightglomerularfluidpermeabilitybaseline(SEScalarVolumePerTimePressureArea::Unload(*src.m_RightGlomerularFluidPermeabilityBaseline));
  if (src.HasRightTubularReabsorptionFilteringSurfaceAreaBaseline())
    renal->set_allocated_righttubularreabsorptionfilteringsurfaceareabaseline(SEScalarArea::Unload(*src.m_RightTubularReabsorptionFilteringSurfaceAreaBaseline));
  if (src.HasRightTubularReabsorptionFluidPermeabilityBaseline())
    renal->set_allocated_righttubularreabsorptionfluidpermeabilitybaseline(SEScalarVolumePerTimePressureArea::Unload(*src.m_RightTubularReabsorptionFluidPermeabilityBaseline));

  // Respiratory
  pulse::ConfigurationData_RespiratoryConfigurationData* resp = new pulse::ConfigurationData_RespiratoryConfigurationData();
  if (src.HasCentralControllerCO2PressureSetPoint())
    resp->set_allocated_centralcontrollerco2pressuresetpoint(SEScalarPressure::Unload(*src.m_CentralControllerCO2PressureSetPoint));
  if (src.HasCentralVentilatoryControllerGain())
    resp->set_allocated_centralventilatorycontrollergain(SEScalar::Unload(*src.m_CentralVentilatoryControllerGain));
  if (src.HasPeripheralControllerCO2PressureSetPoint())
    resp->set_allocated_peripheralcontrollerco2pressuresetpoint(SEScalarPressure::Unload(*src.m_PeripheralControllerCO2PressureSetPoint));
  if (src.HasPeripheralVentilatoryControllerGain())
    resp->set_allocated_peripheralventilatorycontrollergain(SEScalar::Unload(*src.m_PeripheralVentilatoryControllerGain));
  if (src.HasPleuralComplianceSensitivity())
    resp->set_allocated_pleuralcompliancesensitivity(SEScalarInverseVolume::Unload(*src.m_PleuralComplianceSensitivity));
  if (src.HasPulmonaryVentilationRateMaximum())
    resp->set_allocated_pulmonaryventilationratemaximum(SEScalarVolumePerTime::Unload(*src.m_PulmonaryVentilationRateMaximum));
  if (src.HasVentilationTidalVolumeIntercept())
    resp->set_allocated_ventilationtidalvolumeintercept(SEScalarVolume::Unload(*src.m_VentilationTidalVolumeIntercept));
  if (src.HasVentilatoryOcclusionPressure())
    resp->set_allocated_ventilatoryocclusionpressure(SEScalarPressure::Unload(*src.m_VentilatoryOcclusionPressure));

  // Tissue
  pulse::ConfigurationData_TissueConfigurationData* tissue = dst.mutable_tissueconfiguration();
  if (src.IsTissueEnabled())
    tissue->set_enabletissue(src.m_TissueEnabled);
}


bool PulseConfiguration::HasTimeStep() const
{
  return m_TimeStep == nullptr ? false : m_TimeStep->IsValid();
}
SEScalarTime& PulseConfiguration::GetTimeStep()
{
  if (m_TimeStep == nullptr)
    m_TimeStep = new SEScalarTime();
  return *m_TimeStep;
}
double PulseConfiguration::GetTimeStep(const TimeUnit& unit) const
{
  if (m_TimeStep == nullptr)
    return SEScalar::dNaN();
  return m_TimeStep->GetValue(unit);
}

bool PulseConfiguration::HasStabilization() const
{
  return m_TimedStabilization != nullptr || m_DynamicStabilization != nullptr;
}
SEEngineStabilization* PulseConfiguration::GetStabilization()
{
  if (m_TimedStabilization != nullptr)
    return m_TimedStabilization;
  if (m_DynamicStabilization != nullptr)
    return m_DynamicStabilization;
  return nullptr;
}
void PulseConfiguration::RemoveStabilization()
{
  SAFE_DELETE(m_TimedStabilization);
  SAFE_DELETE(m_DynamicStabilization);
}
bool PulseConfiguration::HasTimedStabilization() const
{
  return m_TimedStabilization != nullptr;
}
SETimedStabilization& PulseConfiguration::GetTimedStabilization()
{
  RemoveDynamicStabilization();
  if (m_TimedStabilization == nullptr)
    m_TimedStabilization = new SETimedStabilization(GetLogger());
  return *m_TimedStabilization;
}
const SETimedStabilization* PulseConfiguration::GetTimedStabilization() const
{
  return m_TimedStabilization;
}
void PulseConfiguration::RemoveTimedStabilization()
{
  SAFE_DELETE(m_TimedStabilization);
}
bool PulseConfiguration::HasDynamicStabilization() const
{
  return m_DynamicStabilization != nullptr;
}
SEDynamicStabilization& PulseConfiguration::GetDynamicStabilization()
{
  RemoveTimedStabilization();
  if (m_DynamicStabilization == nullptr)
    m_DynamicStabilization = new SEDynamicStabilization(GetLogger());
  return *m_DynamicStabilization;
}
const SEDynamicStabilization* PulseConfiguration::GetDynamicStabilization() const
{
  return m_DynamicStabilization;
}
void PulseConfiguration::RemoveDynamicStabilization()
{
  SAFE_DELETE(m_DynamicStabilization);
}


bool PulseConfiguration::HasAutoSerialization() const
{
  return m_AutoSerialization == nullptr ? false : m_AutoSerialization->IsValid();
}
SEAutoSerialization& PulseConfiguration::GetAutoSerialization()
{
  if (m_AutoSerialization == nullptr)
    m_AutoSerialization = new SEAutoSerialization(GetLogger());
  return *m_AutoSerialization;
}
const SEAutoSerialization* PulseConfiguration::GetAutoSerialization() const
{
  return m_AutoSerialization;
}
void PulseConfiguration::RemoveAutoSerialization()
{
  SAFE_DELETE(m_AutoSerialization);
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

/////////
// ECG //
/////////
bool PulseConfiguration::HasECGInterpolator() const
{
  return m_ECGInterpolator != nullptr;
}
SEElectroCardioGramWaveformInterpolator& PulseConfiguration::GetECGInterpolator()
{
  if (m_ECGInterpolator == nullptr)
    m_ECGInterpolator = new SEElectroCardioGramWaveformInterpolator(GetLogger());
  return *m_ECGInterpolator;
}
const SEElectroCardioGramWaveformInterpolator* PulseConfiguration::GetECGInterpolator() const
{
  return m_ECGInterpolator;
}
void PulseConfiguration::RemoveECGInterpolator()
{
  SAFE_DELETE(m_ECGInterpolator);
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

bool PulseConfiguration::HasCarbonDioxideProductionFromOxygenConsumptionConstant() const
{
  return m_CarbonDioxideProductionFromOxygenConsumptionConstant == nullptr ? false : m_CarbonDioxideProductionFromOxygenConsumptionConstant->IsValid();
}
SEScalar& PulseConfiguration::GetCarbonDioxideProductionFromOxygenConsumptionConstant()
{
  if (m_CarbonDioxideProductionFromOxygenConsumptionConstant == nullptr)
    m_CarbonDioxideProductionFromOxygenConsumptionConstant = new SEScalar();
  return *m_CarbonDioxideProductionFromOxygenConsumptionConstant;
}
double PulseConfiguration::GetCarbonDioxideProductionFromOxygenConsumptionConstant() const
{
  if (m_CarbonDioxideProductionFromOxygenConsumptionConstant == nullptr)
    return SEScalar::dNaN();
  return m_CarbonDioxideProductionFromOxygenConsumptionConstant->GetValue();
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