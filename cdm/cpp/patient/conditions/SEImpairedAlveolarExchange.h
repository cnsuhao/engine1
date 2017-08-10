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
#include "patient/conditions/SEPatientCondition.h"

class CDM_DECL SEImpairedAlveolarExchange : public SEPatientCondition
{
public:

  SEImpairedAlveolarExchange();
  virtual ~SEImpairedAlveolarExchange();
  
  virtual void Clear();

  virtual bool IsValid() const;

  static void Load(const cdm::ImpairedAlveolarExchangeData& src, SEImpairedAlveolarExchange& dst);
  static cdm::ImpairedAlveolarExchangeData* Unload(const SEImpairedAlveolarExchange& src);
protected:
  static void Serialize(const cdm::ImpairedAlveolarExchangeData& src, SEImpairedAlveolarExchange& dst);
  static void Serialize(const SEImpairedAlveolarExchange& src, cdm::ImpairedAlveolarExchangeData& dst);

public:
  virtual std::string GetName() const { return "ImpairedAlveolarExchange"; }

  virtual bool HasImpairedSurfaceArea() const;
  virtual SEScalarArea& GetImpairedSurfaceArea();
  virtual double GetImpairedSurfaceArea(const AreaUnit& unit) const;

  virtual bool HasImpairedFraction() const;
  virtual SEScalar0To1& GetImpairedFraction();
  virtual double GetImpairedFraction() const;

  virtual void ToString(std::ostream &str) const;

protected:
  
  SEScalarArea*       m_ImpairedSurfaceArea;
  SEScalar0To1*      m_ImpairedFraction;  
};