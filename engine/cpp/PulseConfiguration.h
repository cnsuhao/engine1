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

#pragma once
class SENutrition;
class SEAutoSerialization;
class SEEngineStabilization;
class SEDynamicStabilization;
class SETimedStabilization;
class SEEnvironmentalConditions;
class SEElectroCardioGramWaveformInterpolator;
#include "engine/SEEngineConfiguration.h"
PULSE_BIND_DECL(ConfigurationData)
#include "bind/engine/Engine.pb.h"
#include "bind/cdm/Properties.pb.h"

/**
* @brief %Pulse specific configuration parameters for all systems/equipment
*/
class PULSE_DECL PulseConfiguration : public SEEngineConfiguration
{
public:

  PulseConfiguration(SESubstanceManager& substances);
  virtual ~PulseConfiguration();
  
  virtual void Clear();
  virtual void Initialize();

  virtual void Merge(const PulseConfiguration& from);

  bool LoadFile(const std::string& file);

  static void Load(const pulse::ConfigurationData& src, PulseConfiguration& dst);
  static pulse::ConfigurationData* Unload(const PulseConfiguration& src);
protected:
  static void Serialize(const pulse::ConfigurationData& src, PulseConfiguration& dst);
  static void Serialize(const PulseConfiguration& src, pulse::ConfigurationData& dst);

  SESubstanceManager& m_Substances;

public:
  virtual bool HasTimeStep() const;
  virtual SEScalarTime& GetTimeStep();
  virtual double GetTimeStep(const TimeUnit& unit) const;

  // You can have either a timed or dynamic stabilization object (cannot have both)
  virtual bool HasStabilization() const;
  virtual SEEngineStabilization* GetStabilization();
  virtual void RemoveStabilization();
  // Timed Methods, If you have dynamic, calling GetTimedStabilization will remove the dynamic object
  virtual bool HasTimedStabilization() const;
  virtual SETimedStabilization& GetTimedStabilization();
  virtual const SETimedStabilization* GetTimedStabilization() const;
  virtual void RemoveTimedStabilization();
  // Dynamic Methods, If you have timed, calling GetDynamicStabilization will remove the timed object
  virtual bool HasDynamicStabilization() const;
  virtual SEDynamicStabilization& GetDynamicStabilization();
  virtual const SEDynamicStabilization* GetDynamicStabilization() const;
  virtual void RemoveDynamicStabilization();

  virtual bool IsWritingPatientBaselineFile() const { return m_WritePatientBaselineFile == cdm::eSwitch::On; }
  virtual void EnableWritePatientBaselineFile(cdm::eSwitch s) { m_WritePatientBaselineFile = s; }

  virtual bool HasAutoSerialization() const;
  virtual SEAutoSerialization& GetAutoSerialization();
  virtual const SEAutoSerialization* GetAutoSerialization() const;
  virtual void RemoveAutoSerialization();

protected:

  bool                       m_Merge;
  SEScalarTime*              m_TimeStep;
  SETimedStabilization*      m_TimedStabilization;
  SEDynamicStabilization*    m_DynamicStabilization;
  SEAutoSerialization*       m_AutoSerialization;
  cdm::eSwitch               m_WritePatientBaselineFile;

  ////////////////////
  /** Baroreceptors */
  ////////////////////
public:
  virtual bool HasResponseSlope() const;
  virtual SEScalar& GetResponseSlope();
  virtual double GetResponseSlope() const;

  virtual bool HasHeartRateDistributedTimeDelay() const;
  virtual SEScalarTime& GetHeartRateDistributedTimeDelay();
  virtual double GetHeartRateDistributedTimeDelay(const TimeUnit& unit) const;

  virtual bool HasHeartElastanceDistributedTimeDelay() const;
  virtual SEScalarTime& GetHeartElastanceDistributedTimeDelay();
  virtual double GetHeartElastanceDistributedTimeDelay(const TimeUnit& unit) const;

  virtual bool HasSystemicResistanceDistributedTimeDelay() const;
  virtual SEScalarTime& GetSystemicResistanceDistributedTimeDelay();
  virtual double GetSystemicResistanceDistributedTimeDelay(const TimeUnit& unit) const;

  virtual bool HasVenousComplianceDistributedTimeDelay() const;
  virtual SEScalarTime& GetVenousComplianceDistributedTimeDelay();
  virtual double GetVenousComplianceDistributedTimeDelay(const TimeUnit& unit) const;

  virtual bool HasNormalizedHeartRateIntercept() const;
  virtual SEScalar& GetNormalizedHeartRateIntercept();
  virtual double GetNormalizedHeartRateIntercept() const;

  virtual bool HasNormalizedHeartRateSympatheticSlope() const;
  virtual SEScalar& GetNormalizedHeartRateSympatheticSlope();
  virtual double GetNormalizedHeartRateSympatheticSlope() const;

  virtual bool HasNormalizedHeartRateParasympatheticSlope() const;
  virtual SEScalar& GetNormalizedHeartRateParasympatheticSlope();
  virtual double GetNormalizedHeartRateParasympatheticSlope() const;

  virtual bool HasNormalizedHeartElastanceIntercept() const;
  virtual SEScalar& GetNormalizedHeartElastanceIntercept();
  virtual double GetNormalizedHeartElastanceIntercept() const;

  virtual bool HasNormalizedHeartElastanceSympatheticSlope() const;
  virtual SEScalar& GetNormalizedHeartElastanceSympatheticSlope();
  virtual double GetNormalizedHeartElastanceSympatheticSlope() const;

  virtual bool HasNormalizedResistanceIntercept() const;
  virtual SEScalar& GetNormalizedResistanceIntercept();
  virtual double GetNormalizedResistanceIntercept() const;

  virtual bool HasNormalizedResistanceSympatheticSlope() const;
  virtual SEScalar& GetNormalizedResistanceSympatheticSlope();
  virtual double GetNormalizedResistanceSympatheticSlope() const;

  virtual bool HasNormalizedComplianceIntercept() const;
  virtual SEScalar& GetNormalizedComplianceIntercept();
  virtual double GetNormalizedComplianceIntercept() const;

  virtual bool HasNormalizedComplianceParasympatheticSlope() const;
  virtual SEScalar& GetNormalizedComplianceParasympatheticSlope();
  virtual double GetNormalizedComplianceParasympatheticSlope() const;

protected:
  SEScalar*             m_ResponseSlope;
  SEScalarTime*         m_HeartRateDistributedTimeDelay;
  SEScalarTime*         m_HeartElastanceDistributedTimeDelay;
  SEScalarTime*         m_SystemicResistanceDistributedTimeDelay;
  SEScalarTime*         m_VenousComplianceDistributedTimeDelay;
  SEScalar*             m_NormalizedHeartRateIntercept;
  SEScalar*             m_NormalizedHeartRateSympatheticSlope;
  SEScalar*             m_NormalizedHeartRateParasympatheticSlope;
  SEScalar*             m_NormalizedHeartElastanceIntercept;
  SEScalar*             m_NormalizedHeartElastanceSympatheticSlope;
  SEScalar*             m_NormalizedResistanceIntercept;
  SEScalar*             m_NormalizedResistanceSympatheticSlope;
  SEScalar*             m_NormalizedComplianceIntercept;
  SEScalar*             m_NormalizedComplianceParasympatheticSlope;

  //////////////////////
  /** Blood Chemistry */
  //////////////////////
public:
  virtual bool HasMeanCorpuscularHemoglobin() const;
  virtual SEScalarMassPerAmount& GetMeanCorpuscularHemoglobin();
  virtual double GetMeanCorpuscularHemoglobin(const MassPerAmountUnit& unit) const;
  
  virtual bool HasMeanCorpuscularVolume() const;
  virtual SEScalarVolume& GetMeanCorpuscularVolume();
  virtual double GetMeanCorpuscularVolume(const VolumeUnit& unit) const;

  virtual bool HasStandardDiffusionDistance() const;
  virtual SEScalarLength& GetStandardDiffusionDistance();
  virtual double GetStandardDiffusionDistance(const LengthUnit& unit) const;

  virtual bool HasStandardOxygenDiffusionCoefficient() const;
  virtual SEScalarAreaPerTimePressure& GetStandardOxygenDiffusionCoefficient();
  virtual double GetStandardOxygenDiffusionCoefficient(const AreaPerTimePressureUnit& unit) const;
protected:
  SEScalarMassPerAmount*           m_MeanCorpuscularHemoglobin;
  SEScalarVolume*                  m_MeanCorpuscularVolume;
  SEScalarLength*                  m_StandardDiffusionDistance;
  SEScalarAreaPerTimePressure*     m_StandardOxygenDiffusionCoefficient;

  /////////////////////
  /** Cardiovascular */
  /////////////////////
public:
  virtual bool HasLeftHeartElastanceMaximum() const;
  virtual SEScalarFlowElastance& GetLeftHeartElastanceMaximum();
  virtual double GetLeftHeartElastanceMaximum(const FlowElastanceUnit& unit) const;

  virtual bool HasLeftHeartElastanceMinimum() const;
  virtual SEScalarFlowElastance& GetLeftHeartElastanceMinimum();
  virtual double GetLeftHeartElastanceMinimum(const FlowElastanceUnit& unit) const;

  virtual bool HasMinimumBloodVolumeFraction() const;
  virtual SEScalar0To1& GetMinimumBloodVolumeFraction();
  virtual double GetMinimumBloodVolumeFraction() const;

  virtual bool HasRightHeartElastanceMaximum() const;
  virtual SEScalarFlowElastance& GetRightHeartElastanceMaximum();
  virtual double GetRightHeartElastanceMaximum(const FlowElastanceUnit& unit) const;

  virtual bool HasRightHeartElastanceMinimum() const;
  virtual SEScalarFlowElastance& GetRightHeartElastanceMinimum();
  virtual double GetRightHeartElastanceMinimum(const FlowElastanceUnit& unit) const;

  virtual bool HasStandardPulmonaryCapillaryCoverage() const;
  virtual SEScalar& GetStandardPulmonaryCapillaryCoverage();
  virtual double GetStandardPulmonaryCapillaryCoverage() const;
protected:
  SEScalarFlowElastance* m_LeftHeartElastanceMaximum; 
  SEScalarFlowElastance* m_LeftHeartElastanceMinimum; 
  SEScalar0To1*          m_MinimumBloodVolumeFraction;
  SEScalarFlowElastance* m_RightHeartElastanceMaximum; 
  SEScalarFlowElastance* m_RightHeartElastanceMinimum;
  SEScalar*              m_StandardPulmonaryCapillaryCoverage;

  //////////////
  /** Circuit */
  //////////////
public:

  virtual bool HasCardiovascularOpenResistance() const;
  virtual SEScalarFlowResistance& GetCardiovascularOpenResistance();
  virtual double GetCardiovascularOpenResistance(const FlowResistanceUnit& unit) const;

  virtual bool HasDefaultClosedElectricResistance() const;
  virtual SEScalarElectricResistance& GetDefaultClosedElectricResistance();
  virtual double GetDefaultClosedElectricResistance(const ElectricResistanceUnit& unit) const;

  virtual bool HasDefaultClosedFlowResistance() const;
  virtual SEScalarFlowResistance& GetDefaultClosedFlowResistance();
  virtual double GetDefaultClosedFlowResistance(const FlowResistanceUnit& unit) const;

  virtual bool HasDefaultClosedHeatResistance() const;
  virtual SEScalarHeatResistance& GetDefaultClosedHeatResistance();
  virtual double GetDefaultClosedHeatResistance(const HeatResistanceUnit& unit) const;

  virtual bool HasDefaultOpenElectricResistance() const;
  virtual SEScalarElectricResistance& GetDefaultOpenElectricResistance();
  virtual double GetDefaultOpenElectricResistance(const ElectricResistanceUnit& unit) const;

  virtual bool HasDefaultOpenFlowResistance() const;
  virtual SEScalarFlowResistance& GetDefaultOpenFlowResistance();
  virtual double GetDefaultOpenFlowResistance(const FlowResistanceUnit& unit) const;

  virtual bool HasDefaultOpenHeatResistance() const;
  virtual SEScalarHeatResistance& GetDefaultOpenHeatResistance();
  virtual double GetDefaultOpenHeatResistance(const HeatResistanceUnit& unit) const;

  virtual bool HasMachineClosedResistance() const;
  virtual SEScalarFlowResistance& GetMachineClosedResistance();
  virtual double GetMachineClosedResistance(const FlowResistanceUnit& unit) const;

  virtual bool HasMachineOpenResistance() const;
  virtual SEScalarFlowResistance& GetMachineOpenResistance();
  virtual double GetMachineOpenResistance(const FlowResistanceUnit& unit) const;

  virtual bool HasRespiratoryClosedResistance() const;
  virtual SEScalarFlowResistance& GetRespiratoryClosedResistance();
  virtual double GetRespiratoryClosedResistance(const FlowResistanceUnit& unit) const;

  virtual bool HasRespiratoryOpenResistance() const;
  virtual SEScalarFlowResistance& GetRespiratoryOpenResistance();
  virtual double GetRespiratoryOpenResistance(const FlowResistanceUnit& unit) const;

protected:
  SEScalarFlowResistance*      m_CardiovascularOpenResistance;
  SEScalarElectricResistance*  m_DefaultClosedElectricResistance;
  SEScalarFlowResistance*      m_DefaultClosedFlowResistance;
  SEScalarHeatResistance*      m_DefaultClosedHeatResistance;
  SEScalarElectricResistance*  m_DefaultOpenElectricResistance;
  SEScalarFlowResistance*      m_DefaultOpenFlowResistance;
  SEScalarHeatResistance*      m_DefaultOpenHeatResistance;
  SEScalarFlowResistance*      m_MachineClosedResistance;
  SEScalarFlowResistance*      m_MachineOpenResistance;
  SEScalarFlowResistance*      m_RespiratoryClosedResistance;
  SEScalarFlowResistance*      m_RespiratoryOpenResistance;

  ////////////////
  /** Constants */
  ////////////////
public:
  virtual bool HasOxygenMetabolicConstant() const;
  virtual SEScalar& GetOxygenMetabolicConstant();
  virtual double GetOxygenMetabolicConstant() const;

  virtual bool HasStefanBoltzmann() const;
  virtual SEScalarPowerPerAreaTemperatureToTheFourth& GetStefanBoltzmann();
  virtual double GetStefanBoltzmann(const PowerPerAreaTemperatureToTheFourthUnit& unit) const;

  virtual bool HasUniversalGasConstant() const;
  virtual SEScalarHeatCapacitancePerAmount& GetUniversalGasConstant();
  virtual double GetUniversalGasConstant(const HeatCapacitancePerAmountUnit& unit) const;
protected:
  SEScalar*                                    m_OxygenMetabolicConstant;
  SEScalarPowerPerAreaTemperatureToTheFourth*  m_StefanBoltzmann;
  SEScalarHeatCapacitancePerAmount*            m_UniversalGasConstant;

  ////////////
  /** Drugs */
  ////////////
public:
  virtual bool IsPDEnabled() const { return m_PDEnabled==cdm::eSwitch::On; }
  virtual void UsePDModel(cdm::eSwitch s) { m_PDEnabled = s; }
protected:
  cdm::eSwitch m_PDEnabled;

  ///////////
  /** ECG */
  //////////
public:
  virtual bool HasECGInterpolator() const;
  virtual SEElectroCardioGramWaveformInterpolator& GetECGInterpolator();
  virtual const SEElectroCardioGramWaveformInterpolator* GetECGInterpolator() const;
  virtual void RemoveECGInterpolator();
//protected:
  SEElectroCardioGramWaveformInterpolator*         m_ECGInterpolator;

  /////////////
  /** Energy */
  /////////////
public:
  virtual bool HasBodySpecificHeat() const;
  virtual SEScalarHeatCapacitancePerMass& GetBodySpecificHeat();
  virtual double GetBodySpecificHeat(const HeatCapacitancePerMassUnit& unit) const;

  virtual bool HasCarbonDioxideProductionFromOxygenConsumptionConstant() const;
  virtual SEScalar& GetCarbonDioxideProductionFromOxygenConsumptionConstant();
  virtual double GetCarbonDioxideProductionFromOxygenConsumptionConstant() const;

  virtual bool HasCoreTemperatureHigh() const;
  virtual SEScalarTemperature& GetCoreTemperatureHigh();
  virtual double GetCoreTemperatureHigh(const TemperatureUnit& unit) const;

  virtual bool HasCoreTemperatureLow() const;
  virtual SEScalarTemperature& GetCoreTemperatureLow();
  virtual double GetCoreTemperatureLow(const TemperatureUnit& unit) const;

  virtual bool HasDeltaCoreTemperatureLow() const;
  virtual SEScalarTemperature& GetDeltaCoreTemperatureLow();
  virtual double GetDeltaCoreTemperatureLow(const TemperatureUnit& unit) const;

  virtual bool HasEnergyPerATP() const;
  virtual SEScalarEnergyPerAmount& GetEnergyPerATP();
  virtual double GetEnergyPerATP(const EnergyPerAmountUnit& unit) const;

  virtual bool HasSweatHeatTransfer() const;
  virtual SEScalarHeatConductance& GetSweatHeatTransfer();
  virtual double GetSweatHeatTransfer(const HeatConductanceUnit& unit) const;

  virtual bool HasVaporizationEnergy() const;
  virtual SEScalarEnergyPerMass& GetVaporizationEnergy();
  virtual double GetVaporizationEnergy(const EnergyPerMassUnit& unit) const;

  virtual bool HasVaporSpecificHeat() const;
  virtual SEScalarHeatCapacitancePerMass& GetVaporSpecificHeat();
  virtual double GetVaporSpecificHeat(const HeatCapacitancePerMassUnit& unit) const;
protected:
  SEScalarHeatCapacitancePerMass* m_BodySpecificHeat;
  SEScalar*                       m_CarbonDioxideProductionFromOxygenConsumptionConstant;
  SEScalarTemperature*            m_CoreTemperatureLow;
  SEScalarTemperature*            m_CoreTemperatureHigh;
  SEScalarTemperature*            m_DeltaCoreTemperatureLow;
  SEScalarEnergyPerAmount*        m_EnergyPerATP;
  SEScalarHeatConductance*        m_SweatHeatTransfer;
  SEScalarEnergyPerMass*          m_VaporizationEnergy;
  SEScalarHeatCapacitancePerMass* m_VaporSpecificHeat;

  //////////////////
  /** Environment */
  //////////////////
public:
  virtual bool HasAirDensity() const;
  virtual SEScalarMassPerVolume& GetAirDensity();
  virtual double GetAirDensity(const MassPerVolumeUnit& unit) const;

  virtual bool HasAirSpecificHeat() const;
  virtual SEScalarHeatCapacitancePerMass& GetAirSpecificHeat();
  virtual double GetAirSpecificHeat(const HeatCapacitancePerMassUnit& unit) const;

  virtual bool HasMolarMassOfDryAir() const;
  virtual SEScalarMassPerAmount& GetMolarMassOfDryAir();
  virtual double GetMolarMassOfDryAir(const MassPerAmountUnit& unit) const;

  virtual bool HasMolarMassOfWaterVapor() const;
  virtual SEScalarMassPerAmount& GetMolarMassOfWaterVapor();
  virtual double GetMolarMassOfWaterVapor(const MassPerAmountUnit& unit) const;

  virtual bool HasInitialEnvironmentalConditions() const;
  virtual SEEnvironmentalConditions& GetInitialEnvironmentalConditions();
  virtual const SEEnvironmentalConditions* GetInitialEnvironmentalConditions() const;

  virtual bool HasWaterDensity() const;
  virtual SEScalarMassPerVolume& GetWaterDensity();
  virtual double GetWaterDensity(const MassPerVolumeUnit& unit) const;
protected:
  SEScalarMassPerVolume*          m_AirDensity;
  SEScalarHeatCapacitancePerMass* m_AirSpecificHeat;
  SEScalarMassPerAmount*          m_MolarMassOfDryAir;
  SEScalarMassPerAmount*          m_MolarMassOfWaterVapor;
  SEEnvironmentalConditions*      m_InitialEnvironmentalConditions;
  SEScalarMassPerVolume*          m_WaterDensity;

  ///////////////////////
  /** Gastrointestinal */
  ///////////////////////
public:
  virtual bool HasCalciumDigestionRate() const;
  virtual SEScalarMassPerTime& GetCalciumDigestionRate();
  virtual double GetCalciumDigestionRate(const MassPerTimeUnit& unit) const;

  virtual bool HasCalciumAbsorbtionFraction() const;
  virtual SEScalar0To1& GetCalciumAbsorbtionFraction();
  virtual double GetCalciumAbsorbtionFraction() const;

  virtual bool HasCarbohydrateAbsorbtionFraction() const;
  virtual SEScalar0To1& GetCarbohydrateAbsorbtionFraction();
  virtual double GetCarbohydrateAbsorbtionFraction() const;

  virtual bool HasDefaultCarbohydrateDigestionRate() const;
  virtual SEScalarMassPerTime& GetDefaultCarbohydrateDigestionRate();
  virtual double GetDefaultCarbohydrateDigestionRate(const MassPerTimeUnit& unit) const;

  virtual bool HasDefaultFatDigestionRate() const;
  virtual SEScalarMassPerTime& GetDefaultFatDigestionRate();
  virtual double GetDefaultFatDigestionRate(const MassPerTimeUnit& unit) const;

  virtual bool HasDefaultProteinDigestionRate() const;
  virtual SEScalarMassPerTime& GetDefaultProteinDigestionRate();
  virtual double GetDefaultProteinDigestionRate(const MassPerTimeUnit& unit) const;

  virtual bool HasDefaultStomachContents() const;
  virtual SENutrition& GetDefaultStomachContents();
  virtual const SENutrition* GetDefaultStomachContents() const;

  virtual bool HasFatAbsorbtionFraction() const;
  virtual SEScalar0To1& GetFatAbsorbtionFraction();
  virtual double GetFatAbsorbtionFraction() const;

  virtual bool HasProteinToUreaFraction() const;
  virtual SEScalar0To1& GetProteinToUreaFraction();
  virtual double GetProteinToUreaFraction() const;

  virtual bool HasWaterDigestionRate() const;
  virtual SEScalarVolumePerTime& GetWaterDigestionRate();
  virtual double GetWaterDigestionRate(const VolumePerTimeUnit& unit) const;
  
protected:

  SEScalarMassPerTime*      m_CalciumDigestionRate;
  SEScalar0To1*             m_CalciumAbsorbtionFraction;
  SEScalar0To1*             m_CarbohydrateAbsorbtionFraction;
  SEScalarMassPerTime*      m_DefaultCarbohydrateDigestionRate;
  SEScalarMassPerTime*      m_DefaultFatDigestionRate;
  SEScalarMassPerTime*      m_DefaultProteinDigestionRate;
  SENutrition*              m_DefaultStomachContents;
  SEScalar0To1*             m_FatAbsorbtionFraction;
  SEScalar0To1*             m_ProteinToUreaFraction;
  SEScalarVolumePerTime*    m_WaterDigestionRate;

  ///////////////
  /** Nervous */
  /////////////
public:
  virtual bool HasPupilDiameterBaseline() const;
  virtual SEScalarLength& GetPupilDiameterBaseline();
  virtual double GetPupilDiameterBaseline(const LengthUnit& unit) const;
protected:
  SEScalarLength*           m_PupilDiameterBaseline;

  ////////////
  /** Renal */
  ////////////
public:
  virtual bool IsRenalEnabled() const { return m_RenalEnabled==cdm::eSwitch::On; }
  virtual void EnableRenal(cdm::eSwitch s) { m_RenalEnabled = s; } 

  virtual bool HasPlasmaSodiumConcentrationSetPoint() const;
  virtual SEScalarMassPerVolume& GetPlasmaSodiumConcentrationSetPoint();
  virtual double GetPlasmaSodiumConcentrationSetPoint(const MassPerVolumeUnit& unit) const;

  virtual bool HasPeritubularPotassiumConcentrationSetPoint() const;
  virtual SEScalarMassPerVolume& GetPeritubularPotassiumConcentrationSetPoint();
  virtual double GetPeritubularPotassiumConcentrationSetPoint(const MassPerVolumeUnit& unit) const;

  virtual bool HasLeftGlomerularFilteringSurfaceAreaBaseline() const;
  virtual SEScalarArea& GetLeftGlomerularFilteringSurfaceAreaBaseline();
  virtual double GetLeftGlomerularFilteringSurfaceAreaBaseline(const AreaUnit& unit) const;

  virtual bool HasLeftGlomerularFluidPermeabilityBaseline() const;
  virtual SEScalarVolumePerTimePressureArea& GetLeftGlomerularFluidPermeabilityBaseline();
  virtual double GetLeftGlomerularFluidPermeabilityBaseline(const VolumePerTimePressureAreaUnit& unit) const;

  virtual bool HasLeftTubularReabsorptionFilteringSurfaceAreaBaseline() const;
  virtual SEScalarArea& GetLeftTubularReabsorptionFilteringSurfaceAreaBaseline();
  virtual double GetLeftTubularReabsorptionFilteringSurfaceAreaBaseline(const AreaUnit& unit) const;

  virtual bool HasLeftTubularReabsorptionFluidPermeabilityBaseline() const;
  virtual SEScalarVolumePerTimePressureArea& GetLeftTubularReabsorptionFluidPermeabilityBaseline();
  virtual double GetLeftTubularReabsorptionFluidPermeabilityBaseline(const VolumePerTimePressureAreaUnit& unit) const;

  virtual bool HasMaximumAfferentResistance() const;
  virtual SEScalarFlowResistance& GetMaximumAfferentResistance();
  virtual double GetMaximumAfferentResistance(const FlowResistanceUnit& unit) const;

  virtual bool HasMinimumAfferentResistance() const;
  virtual SEScalarFlowResistance& GetMinimumAfferentResistance();
  virtual double GetMinimumAfferentResistance(const FlowResistanceUnit& unit) const;

  virtual bool HasRightGlomerularFilteringSurfaceAreaBaseline() const;
  virtual SEScalarArea& GetRightGlomerularFilteringSurfaceAreaBaseline();
  virtual double GetRightGlomerularFilteringSurfaceAreaBaseline(const AreaUnit& unit) const;
  
  virtual bool HasRightGlomerularFluidPermeabilityBaseline() const;
  virtual SEScalarVolumePerTimePressureArea& GetRightGlomerularFluidPermeabilityBaseline();
  virtual double GetRightGlomerularFluidPermeabilityBaseline(const VolumePerTimePressureAreaUnit& unit) const;
  
  virtual bool HasRightTubularReabsorptionFilteringSurfaceAreaBaseline() const;
  virtual SEScalarArea& GetRightTubularReabsorptionFilteringSurfaceAreaBaseline();
  virtual double GetRightTubularReabsorptionFilteringSurfaceAreaBaseline(const AreaUnit& unit) const;
  
  virtual bool HasRightTubularReabsorptionFluidPermeabilityBaseline() const;
  virtual SEScalarVolumePerTimePressureArea& GetRightTubularReabsorptionFluidPermeabilityBaseline();
  virtual double GetRightTubularReabsorptionFluidPermeabilityBaseline(const VolumePerTimePressureAreaUnit& unit) const;

  virtual bool HasTargetSodiumDelivery();
  virtual SEScalarMassPerTime& GetTargetSodiumDelivery();
protected:
  cdm::eSwitch                         m_RenalEnabled;

  SEScalarMassPerVolume*               m_PlasmaSodiumConcentrationSetPoint;
  SEScalarMassPerVolume*               m_PeritubularPotassiumConcentrationSetPoint;

  SEScalarArea*                        m_LeftGlomerularFilteringSurfaceAreaBaseline;
  SEScalarVolumePerTimePressureArea*   m_LeftGlomerularFluidPermeabilityBaseline;
  SEScalarArea*                        m_LeftTubularReabsorptionFilteringSurfaceAreaBaseline;
  SEScalarVolumePerTimePressureArea*   m_LeftTubularReabsorptionFluidPermeabilityBaseline;
  
  SEScalarArea*                        m_RightGlomerularFilteringSurfaceAreaBaseline;
  SEScalarVolumePerTimePressureArea*   m_RightGlomerularFluidPermeabilityBaseline;
  SEScalarArea*                        m_RightTubularReabsorptionFilteringSurfaceAreaBaseline;
  SEScalarVolumePerTimePressureArea*   m_RightTubularReabsorptionFluidPermeabilityBaseline;
   
  SEScalarFlowResistance*              m_MaximumAfferentResistance;
  SEScalarFlowResistance*              m_MinimumAfferentResistance;
  
  SEScalarMassPerTime*                 m_TargetSodiumDelivery;


  //////////////////
  /** Respiratory */
  //////////////////
public:
  virtual bool HasCentralControllerCO2PressureSetPoint() const;
  virtual SEScalarPressure& GetCentralControllerCO2PressureSetPoint();
  virtual double GetCentralControllerCO2PressureSetPoint(const PressureUnit& unit) const;

  virtual bool HasCentralVentilatoryControllerGain() const;
  virtual SEScalar& GetCentralVentilatoryControllerGain();
  virtual double GetCentralVentilatoryControllerGain() const;

  virtual bool HasPeripheralControllerCO2PressureSetPoint() const;
  virtual SEScalarPressure& GetPeripheralControllerCO2PressureSetPoint();
  virtual double GetPeripheralControllerCO2PressureSetPoint(const PressureUnit& unit) const;
  
  virtual bool HasPeripheralVentilatoryControllerGain() const;
  virtual SEScalar& GetPeripheralVentilatoryControllerGain();
  virtual double GetPeripheralVentilatoryControllerGain() const;

  virtual bool HasPleuralComplianceSensitivity() const;
  virtual SEScalarInverseVolume& GetPleuralComplianceSensitivity();
  virtual double GetPleuralComplianceSensitivity(const InverseVolumeUnit& unit) const;

  virtual bool HasPulmonaryVentilationRateMaximum() const;
  virtual SEScalarVolumePerTime& GetPulmonaryVentilationRateMaximum();
  virtual double GetPulmonaryVentilationRateMaximum(const VolumePerTimeUnit& unit) const;
  
  virtual bool HasVentilationTidalVolumeIntercept() const;
  virtual SEScalarVolume& GetVentilationTidalVolumeIntercept();
  virtual double GetVentilationTidalVolumeIntercept(const VolumeUnit& unit) const;

  virtual bool HasVentilatoryOcclusionPressure() const;
  virtual SEScalarPressure& GetVentilatoryOcclusionPressure();
  virtual double GetVentilatoryOcclusionPressure(const PressureUnit& unit) const;
protected:
  SEScalarPressure*        m_CentralControllerCO2PressureSetPoint;
  SEScalar*                m_CentralVentilatoryControllerGain;
  SEScalarPressure*        m_PeripheralControllerCO2PressureSetPoint;
  SEScalar*                m_PeripheralVentilatoryControllerGain;
  SEScalarInverseVolume*   m_PleuralComplianceSensitivity;
  SEScalarVolumePerTime*   m_PulmonaryVentilationRateMaximum;
  SEScalarVolume*          m_VentilationTidalVolumeIntercept;
  SEScalarPressure*        m_VentilatoryOcclusionPressure;

  /////////////
  /** Tissue */
  /////////////
public:
  virtual bool IsTissueEnabled() const { return m_TissueEnabled==cdm::eSwitch::On; }
  virtual void EnableTissue(cdm::eSwitch s) { m_TissueEnabled = s; }
protected:
  cdm::eSwitch m_TissueEnabled;
};