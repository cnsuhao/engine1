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
#include "properties/SEProperty.h"
#include "utils/unitconversion/UCCommon.h"
#include "bind/cdm/Properties.pb.h"

class DLL_DECL SEFunction : public SEProperty
{
public:

  SEFunction();
  virtual ~SEFunction();

  virtual void Clear(); //clear memory

  static void Load(const cdm::FunctionData& src, SEFunction& dst);
  static cdm::FunctionData* Unload(const SEFunction& src);
protected:
  static void Serialize(const cdm::FunctionData& src, SEFunction& dst);
  static void Serialize(const SEFunction& src, cdm::FunctionData& dst);

public:
  virtual bool                          IsValid() const;
  virtual void                          Invalidate();

  virtual unsigned int                  Length();
  
  double                                GetDependentValue(unsigned int index);
  std::vector<double>&                  GetDependent();      

  double                                GetIndependentValue(unsigned int index);
  std::vector<double>&                  GetIndependent();
  
protected:

  std::vector<double> m_Dependent;
  std::vector<double> m_Independent;
};