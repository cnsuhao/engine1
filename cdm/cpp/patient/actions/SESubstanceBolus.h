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
#include "patient/actions/SESubstanceAdministration.h"
class SESubstance;
#include "properties/SEScalarVolume.h"
#include "properties/SEScalarTime.h"

class DLL_DECL SESubstanceBolus : public SESubstanceAdministration
{
public:

  SESubstanceBolus(const SESubstance& substance);
  virtual ~SESubstanceBolus();

  virtual void Clear(); //clear memory

  virtual bool IsValid() const;
  virtual bool IsActive() const;

  static void Load(const cdm::SubstanceBolusData& src, SESubstanceBolus& dst);
  static cdm::SubstanceBolusData* Unload(const SESubstanceBolus& src);
protected:
  static void Serialize(const cdm::SubstanceBolusData& src, SESubstanceBolus& dst);
  static void Serialize(const SESubstanceBolus& src, cdm::SubstanceBolusData& dst);

public:

  virtual cdm::SubstanceBolusData_eAdministrationRoute GetAdminRoute() const;
  virtual void SetAdminRoute(cdm::SubstanceBolusData_eAdministrationRoute name);
  virtual bool HasAdminRoute() const;
  virtual void InvalidateAdminRoute();

  virtual bool HasConcentration() const;
  virtual SEScalarMassPerVolume& GetConcentration();

  virtual bool HasDose() const;
  virtual SEScalarVolume& GetDose();  

  virtual SESubstance& GetSubstance() const;

  virtual void ToString(std::ostream &str) const;

protected:
  cdm::SubstanceBolusData_eAdministrationRoute m_AdminRoute;
  SEScalarMassPerVolume*              m_Concentration;
  SEScalarVolume*                     m_Dose;
  const SESubstance&                  m_Substance;
  
};        

class DLL_DECL SESubstanceBolusState
{
public:
  SESubstanceBolusState(const SESubstance& sub);
  ~SESubstanceBolusState();

  static void Load(const cdm::SubstanceBolusData_StateData& src, SESubstanceBolusState& dst);
  static cdm::SubstanceBolusData_StateData* Unload(const SESubstanceBolusState& src);
protected:
  static void Serialize(const cdm::SubstanceBolusData_StateData& src, SESubstanceBolusState& dst);
  static void Serialize(const SESubstanceBolusState& src, cdm::SubstanceBolusData_StateData& dst);

public:
  SEScalarTime& GetElapsedTime() { return m_ElapsedTime; }
  SEScalarVolume& GetAdministeredDose() { return m_AdministeredDose; }

protected:
  const SESubstance&   m_Substance;
  SEScalarTime         m_ElapsedTime;
  SEScalarVolume       m_AdministeredDose;
};