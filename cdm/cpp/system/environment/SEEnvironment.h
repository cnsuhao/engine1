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
#include "system/SESystem.h"
#include "bind/cdm/Environment.pb.h"
#include "system/environment/SEActiveConditioning.h"
#include "system/environment/SEAppliedTemperature.h"
#include "system/environment/SEEnvironmentalConditions.h"
#include "system/environment/actions/SEChangeEnvironmentConditions.h"
#include "system/environment/conditions/SEInitialEnvironmentConditions.h"

class CDM_DECL SEEnvironment : public SESystem
{
public:

  SEEnvironment(SESubstanceManager& substances);
  virtual ~SEEnvironment();

  virtual void Clear();

  static void Load(const cdm::EnvironmentData& src, SEEnvironment& dst);
  static cdm::EnvironmentData* Unload(const SEEnvironment& src);
protected:
  static void Serialize(const cdm::EnvironmentData& src, SEEnvironment& dst);
  static void Serialize(const SEEnvironment& src, cdm::EnvironmentData& dst);

  /** @name ProcessChange
  * @brief - Will change this class as directed by the Action
  */
  virtual bool ProcessChange(const SEChangeEnvironmentConditions& action);

  /** @name ProcessChange
  * @brief - Will change this class as directed by the Condition
  */
  virtual bool ProcessChange(const SEInitialEnvironmentConditions& change);

  /** @name StateChange
  *   @brief - This method is called when ever there is a state change
  *            Specically a new file has been loaded, configuration action, or the system reset
  *            Engine specific methodology can then update their logic.
  */
  virtual void StateChange() {};

public:

  virtual const SEScalar* GetScalar(const std::string& name);

  virtual bool HasActiveHeating() const;
  virtual SEActiveConditioning& GetActiveHeating();
  virtual const SEActiveConditioning* GetActiveHeating() const;
  virtual void RemoveActiveHeating();

  virtual bool HasActiveCooling() const;
  virtual SEActiveConditioning& GetActiveCooling();
  virtual const SEActiveConditioning* GetActiveCooling() const;
  virtual void RemoveActiveCooling();

  virtual bool HasAppliedTemperature() const;
  virtual SEAppliedTemperature& GetAppliedTemperature();
  virtual const SEAppliedTemperature* GetAppliedTemperature() const;
  virtual void RemoveAppliedTemperature();

  virtual bool HasConditions() const;
  virtual SEEnvironmentalConditions& GetConditions();
  virtual const SEEnvironmentalConditions* GetConditions() const;
  virtual void RemoveConditions();

  virtual bool HasConvectiveHeatLoss() const;
  virtual SEScalarPower& GetConvectiveHeatLoss();
  virtual double GetConvectiveHeatLoss(const PowerUnit& unit) const;

  virtual bool HasConvectiveHeatTranferCoefficient() const;
  virtual SEScalarHeatConductancePerArea& GetConvectiveHeatTranferCoefficient();
  virtual double GetConvectiveHeatTranferCoefficient(const HeatConductancePerAreaUnit& unit) const;

  virtual bool HasEvaporativeHeatLoss() const;
  virtual SEScalarPower& GetEvaporativeHeatLoss();
  virtual double GetEvaporativeHeatLoss(const PowerUnit& unit) const;

  virtual bool HasEvaporativeHeatTranferCoefficient() const;
  virtual SEScalarHeatConductancePerArea& GetEvaporativeHeatTranferCoefficient();
  virtual double GetEvaporativeHeatTranferCoefficient(const HeatConductancePerAreaUnit& unit) const;

  virtual bool HasRadiativeHeatLoss() const;
  virtual SEScalarPower& GetRadiativeHeatLoss();
  virtual double GetRadiativeHeatLoss(const PowerUnit& unit) const;

  virtual bool HasRadiativeHeatTranferCoefficient() const;
  virtual SEScalarHeatConductancePerArea& GetRadiativeHeatTranferCoefficient();
  virtual double GetRadiativeHeatTranferCoefficient(const HeatConductancePerAreaUnit& unit) const;

  virtual bool HasRespirationHeatLoss() const;
  virtual SEScalarPower& GetRespirationHeatLoss();
  virtual double GetRespirationHeatLoss(const PowerUnit& unit) const;

  virtual bool HasSkinHeatLoss() const;
  virtual SEScalarPower& GetSkinHeatLoss();
  virtual double GetSkinHeatLoss(const PowerUnit& unit) const;

protected:

  SEScalarPower*                    m_ConvectiveHeatLoss;
  SEScalarHeatConductancePerArea*   m_ConvectiveHeatTranferCoefficient;
  SEScalarPower*                    m_EvaporativeHeatLoss;
  SEScalarHeatConductancePerArea*   m_EvaporativeHeatTranferCoefficient;
  SEScalarPower*                    m_RadiativeHeatLoss;
  SEScalarHeatConductancePerArea*   m_RadiativeHeatTranferCoefficient;
  SEScalarPower*                    m_RespirationHeatLoss;
  SEScalarPower*                    m_SkinHeatLoss;

  SEActiveConditioning*             m_ActiveHeating;
  SEActiveConditioning*             m_ActiveCooling;
  SEAppliedTemperature*             m_AppliedTemperature;
  SEEnvironmentalConditions*        m_Conditions;

  SESubstanceManager&               m_Substances;
};
