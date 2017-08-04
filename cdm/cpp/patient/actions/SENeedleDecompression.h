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
#include "patient/actions/SEPatientAction.h"

class DLL_DECL SENeedleDecompression : public SEPatientAction
{
public:

  SENeedleDecompression();
  virtual ~SENeedleDecompression();

  virtual void Clear(); //clear memory

  virtual bool IsValid() const;
  virtual bool IsActive() const;
  virtual void SetActive(bool b);

  static void Load(const cdm::NeedleDecompressionData& src, SENeedleDecompression& dst);
  static cdm::NeedleDecompressionData* Unload(const SENeedleDecompression& src);
protected:
  static void Serialize(const cdm::NeedleDecompressionData& src, SENeedleDecompression& dst);
  static void Serialize(const SENeedleDecompression& src, cdm::NeedleDecompressionData& dst);

public:

  virtual cdm::eSwitch GetState() const;
  virtual void SetState(cdm::eSwitch name);

  virtual cdm::eSide GetSide() const;
  virtual void SetSide(cdm::eSide LeftOrRight);
  virtual bool HasSide() const;
  virtual void InvalidateSide();
  
  virtual void ToString(std::ostream &str) const;

protected:
  cdm::eSide m_Side;
  cdm::eSwitch m_State;
};    