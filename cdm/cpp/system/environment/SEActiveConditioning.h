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
#include "bind/cdm/Environment.pb.h"

class DLL_DECL SEActiveConditioning : public Loggable
{
public:

  SEActiveConditioning(Logger* logger);
  virtual ~SEActiveConditioning();

  virtual void Clear();
  virtual void Reset();

  static void Load(const cdm::EnvironmentData_ActiveConditioningData& src, SEActiveConditioning& dst);
  static cdm::EnvironmentData_ActiveConditioningData* Unload(const SEActiveConditioning& src);
protected:
  static void Serialize(const cdm::EnvironmentData_ActiveConditioningData& src, SEActiveConditioning& dst);
  static void Serialize(const SEActiveConditioning& src, cdm::EnvironmentData_ActiveConditioningData& dst);

public:

  virtual const SEScalar* GetScalar(const std::string& name);

  virtual bool HasPower() const;
  virtual SEScalarPower& GetPower();
  virtual double GetPower(const PowerUnit& unit) const;

  virtual bool HasSurfaceArea() const;
  virtual SEScalarArea& GetSurfaceArea();
  virtual double GetSurfaceArea(const AreaUnit& unit) const;

  virtual bool HasSurfaceAreaFraction() const;
  virtual SEScalar0To1& GetSurfaceAreaFraction();
  virtual double GetSurfaceAreaFraction() const;

  virtual void ToString(std::ostream &str) const;

protected:
  SEScalarPower*     m_Power;
  SEScalarArea*      m_SurfaceArea;
  SEScalar0To1*      m_SurfaceAreaFraction;
};