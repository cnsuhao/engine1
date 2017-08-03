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
#include "bind/cdm/Inhaler.pb.h"
class Serializer; 
class SESubstance;
class SESubstanceManager;
class SEInhalerConfiguration;

class DLL_DECL SEInhaler : public SESystem
{
protected:

public:

  SEInhaler(SESubstanceManager& substances);
  virtual ~SEInhaler();

  virtual void Clear();

  /** @name GetScalar
  *   @brief - A reflextion type call that will return the Scalar associated
  *            with the string. ex. GetScalar("Hematocrit") will return the
  *            SEScalarPercent object associated with Hematocrit
  *   @details - Note this is an expensive call as it will string compare many times
  *              This is best used, and intended for, you to dynamically prepopulate
  *              a mapping data structure that will help access what you need
  */
  virtual const SEScalar* GetScalar(const std::string& name);

  static void Load(const cdm::InhalerData& src, SEInhaler& dst);
  static cdm::InhalerData* Unload(const SEInhaler& src);
protected:
  static void Serialize(const cdm::InhalerData& src, SEInhaler& dst);
  static void Serialize(const SEInhaler& src, cdm::InhalerData& dst);

  /** @name StateChange
  *   @brief - This method is called when ever there is a state change
  *            Specically a new file has been loaded, configuration action, or the system reset
  *            Engine specific methodology can then update their logic.
  */
  virtual void StateChange(){};
  virtual void Merge(const SEInhaler& from);
  virtual void ProcessConfiguration(const SEInhalerConfiguration& config);

public:

  bool LoadFile(const std::string& inhalerFile);

  virtual cdm::eSwitch GetState() const;
  virtual void SetState(cdm::eSwitch name);
  virtual bool HasState() const;
  virtual void InvalidateState();

  virtual bool HasMeteredDose() const;
  virtual SEScalarMass& GetMeteredDose();
  virtual double GetMeteredDose(const MassUnit& unit) const;

  virtual bool HasNozzleLoss() const;
  virtual SEScalar0To1& GetNozzleLoss();
  virtual double GetNozzleLoss() const;

  virtual bool HasSpacerVolume() const;
  virtual SEScalarVolume& GetSpacerVolume();
  virtual double GetSpacerVolume(const VolumeUnit& unit) const;

  virtual bool HasSubstance() const;
  virtual void SetSubstance(const SESubstance* sub);
  virtual SESubstance* GetSubstance() const;

protected:

  cdm::eSwitch          m_State;
  SEScalarMass*         m_MeteredDose;
  SEScalar0To1*         m_NozzleLoss;
  SEScalarVolume*       m_SpacerVolume;
  const SESubstance*    m_Substance;

  SESubstanceManager&   m_Substances;
};
