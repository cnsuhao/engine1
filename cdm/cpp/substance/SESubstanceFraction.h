/**************************************************************************************
Copyright 2015 Applied Research Associates, Inc.
Licensed under the Apache License, Version 2.0 (the "License"); you may not use
this file except in compliance with the License. You may obtain a copy of the License
at:
http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software distributed under
the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License..
**************************************************************************************/

#pragma once
class SESubstance;
class SESubstanceManager;
class SEEnvironmentalConditions;
#include "bind/cdm/Substance.pb.h"

class DLL_DECL SESubstanceFraction : public Loggable
{
protected:
  friend SEEnvironmentalConditions;// So it can add substances to the manager
public:

  SESubstanceFraction(SESubstance&);
  virtual ~SESubstanceFraction();

  virtual void Clear();

  static void Load(const cdm::SubstanceData_FractionAmountData& src, SESubstanceFraction& dst);
  static cdm::SubstanceData_FractionAmountData* Unload(const SESubstanceFraction& src);
protected:
  static void Serialize(const cdm::SubstanceData_FractionAmountData& src, SESubstanceFraction& dst);
  static void Serialize(const SESubstanceFraction& src, cdm::SubstanceData_FractionAmountData& dst);

public:

  virtual bool HasFractionAmount() const;
  virtual SEScalar0To1& GetFractionAmount();
  virtual double GetFractionAmount() const;

  virtual SESubstance& GetSubstance() const;

protected:

  SESubstance&       m_Substance;
  SEScalar0To1*  m_FractionAmount;
};  