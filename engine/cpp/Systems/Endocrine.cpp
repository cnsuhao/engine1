/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "Endocrine.h"
#include "system/physiology/SEDrugSystem.h"
#include "system/physiology/SECardiovascularSystem.h"
#include "system/physiology/SEEnergySystem.h"

#include "patient/SEMeal.h"
#include "patient/SENutrition.h"
#include "patient/conditions/SEConsumeMeal.h"

#include "properties/SEScalarPower.h"
#include "properties/SEScalarPressure.h"
#include "properties/SEScalarMass.h"
#include "properties/SEScalarMassPerVolume.h"
#include "properties/SEScalarAmountPerTime.h"
#include "properties/SEScalarMassPerAmount.h"
#include "properties/SEScalarVolume.h"
#include "properties/SEScalarTemperature.h"
#include "properties/SEScalar0To1.h"


Endocrine::Endocrine(PulseController& data) : SEEndocrineSystem(data.GetLogger()), m_data(data)
{
  Clear();
}

Endocrine::~Endocrine()
{
  Clear();
}

void Endocrine::Clear()
{
  SEEndocrineSystem::Clear();
  m_aortaGlucose = nullptr;
  m_aortaEpinephrine = nullptr;
  m_splanchnicInsulin = nullptr;  
}

//--------------------------------------------------------------------------------------------------
/// \brief
/// Initializes system properties to valid homeostatic values.
//--------------------------------------------------------------------------------------------------
void Endocrine::Initialize()
{
  PulseSystem::Initialize();
}

void Endocrine::Load(const pulse::EndocrineSystemData& src, Endocrine& dst)
{
  Endocrine::Serialize(src, dst);
  dst.SetUp();
}
void Endocrine::Serialize(const pulse::EndocrineSystemData& src, Endocrine& dst)
{
  SEEndocrineSystem::Serialize(src.common(), dst);
}

pulse::EndocrineSystemData* Endocrine::Unload(const Endocrine& src)
{

  pulse::EndocrineSystemData* dst = new pulse::EndocrineSystemData();
  Endocrine::Serialize(src, *dst);
  return dst;
}
void Endocrine::Serialize(const Endocrine& src, pulse::EndocrineSystemData& dst)
{
  SEEndocrineSystem::Serialize(src, *dst.mutable_common());
}

void Endocrine::SetUp()
{
  m_dt_s = m_data.GetTimeStep().GetValue(TimeUnit::s);
  SELiquidCompartment* aorta = m_data.GetCompartments().GetLiquidCompartment(pulse::VascularCompartment::Aorta);
  SELiquidCompartment* rkidney = m_data.GetCompartments().GetLiquidCompartment(pulse::VascularCompartment::RightEfferentArteriole);
  SELiquidCompartment* lkidney = m_data.GetCompartments().GetLiquidCompartment(pulse::VascularCompartment::LeftEfferentArteriole);
  m_aortaEpinephrine = aorta->GetSubstanceQuantity(m_data.GetSubstances().GetEpi());
  m_rKidneyEpinephrine = rkidney->GetSubstanceQuantity(m_data.GetSubstances().GetEpi());
  m_lKidneyEpinephrine = lkidney->GetSubstanceQuantity(m_data.GetSubstances().GetEpi());
  m_aortaGlucose = aorta->GetSubstanceQuantity(m_data.GetSubstances().GetGlucose());
  SESubstance* insulin = &m_data.GetSubstances().GetInsulin();
  m_insulinMolarMass_g_Per_mol = insulin->GetMolarMass(MassPerAmountUnit::g_Per_mol);
  m_splanchnicInsulin = m_data.GetCompartments().GetLiquidCompartment(pulse::VascularCompartment::Splanchnic)->GetSubstanceQuantity(*insulin);
}

void Endocrine::AtSteadyState()
{

}

//--------------------------------------------------------------------------------------------------
/// \brief
/// Endocrine process function
///
/// \details
/// Currently, only two hormones exists in the Pulse system: epinephrine and insulin. If the metabolic rate 
/// rises above the basal rate, epinephrine is released. This is meant to simulate a sympathetic 
/// nervous system response. The masses of the hormones are increased in the kidneys' efferent arterioles. 
/// The hormones will then circulate using the transport and substances methodology.
//--------------------------------------------------------------------------------------------------
void Endocrine::Process()
{
  ReleaseEpinephrine();
  SynthesizeInsulin();
}

//--------------------------------------------------------------------------------------------------
/// \brief
/// Calculate the rate of insulin production 
///
/// \details
/// The insulin production rate is calculated based on the relevant range of glucose and instantaneous concentration of glucose in the aorta
/// (representative of the body). The equation for insulin production is from \cite tolic2000insulin
//--------------------------------------------------------------------------------------------------
void Endocrine::SynthesizeInsulin()
{  
  double bloodGlucoseConcentration_g_Per_L = m_aortaGlucose->GetConcentration(MassPerVolumeUnit::g_Per_L);
  // 2.0 = upperConcentration_g_Per_L
  // 0.3 = lowerConcentration_g_Per_l
  // 65.421 = amplitudeRate_mU_Per_min

  double insulinSynthesisRate_pmol_Per_min = 65.421
                                    / (1.0 + exp((2.0 - 2.0*bloodGlucoseConcentration_g_Per_L) / 0.3))
                                    * 6.67;// = insulinConversionToAmount_pmol_Per_mU (Figure out where to put this units of pmol/mU)

  GetInsulinSynthesisRate().SetValue(insulinSynthesisRate_pmol_Per_min, AmountPerTimeUnit::pmol_Per_min);
  
  double insulinMassDelta_g = Convert(insulinSynthesisRate_pmol_Per_min, AmountPerTimeUnit::pmol_Per_min, AmountPerTimeUnit::mol_Per_s);
  insulinMassDelta_g *= m_insulinMolarMass_g_Per_mol*m_dt_s;
  
  m_splanchnicInsulin->GetMass().IncrementValue(insulinMassDelta_g, MassUnit::g);
  m_splanchnicInsulin->Balance(BalanceLiquidBy::Mass);
}

//--------------------------------------------------------------------------------------------------
/// \brief
/// Release epinephrine into the bloodstream and handle sympathetic responses
///
/// \details
/// Epinephrine is released at a basal rate of .18 ug/min \cite best1982release from the kidneys. During
/// certain events, the release rate of epinephrine increases. This is sympathetic response.
//--------------------------------------------------------------------------------------------------
void Endocrine::ReleaseEpinephrine()
{
  SEPatient& Patient = m_data.GetPatient();
  double patientWeight_kg = Patient.GetWeight(MassUnit::kg);
  double epinephrineBasalReleaseRate_ug_Per_min = .00229393 * patientWeight_kg; //We want it to be ~.18 ug/min for our StandardMale
  double epinephrineRelease_ug = (epinephrineBasalReleaseRate_ug_Per_min / 60) * m_dt_s;  //amount released per timestep

  double currentMetabolicRate_W = m_data.GetEnergy().GetTotalMetabolicRate(PowerUnit::W);
  double basalMetabolicRate_W = Patient.GetBasalMetabolicRate(PowerUnit::W);
  double releaseMultiplier = 1.0;

  // If we have exercise, release more epi. Release multiplier is a sigmoid based on the total metabolic rate
  // with the maximum multiplier adapted from concentration data presented in @cite tidgren1991renal and @cite stratton1985hemodynamic
  // and the shape adjusted to match data in @cite tidgren1991renal.
  if (currentMetabolicRate_W > basalMetabolicRate_W)
  {
    double exercise_W = (currentMetabolicRate_W - basalMetabolicRate_W);
    double e50_W = 190;
    double eta = 0.035;
    double maxMultiplier = 18.75; 
    releaseMultiplier = 1.0 + GeneralMath::LogisticFunction(maxMultiplier, e50_W, eta, exercise_W);
  }

  // If we have a stress/anxiety response, release more epi
  if (m_data.GetActions().GetPatientActions().HasAcuteStress())
  {
    SEAcuteStress* s = m_data.GetActions().GetPatientActions().GetAcuteStress();
    double severity = s->GetSeverity().GetValue();

    //The highest stress multiplier we currently support is 30
    releaseMultiplier += GeneralMath::LinearInterpolator(0, 1, 0, 30, severity);
  }

  epinephrineRelease_ug *= releaseMultiplier;

  m_rKidneyEpinephrine->GetMass().IncrementValue(0.5*epinephrineRelease_ug, MassUnit::ug);
  m_lKidneyEpinephrine->GetMass().IncrementValue(0.5*epinephrineRelease_ug, MassUnit::ug);
}