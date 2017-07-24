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

class DLL_DECL SEChestOcclusiveDressing : public SEPatientAction
{
public:

  SEChestOcclusiveDressing();
  virtual ~SEChestOcclusiveDressing();

  virtual void Clear(); //clear memory

  virtual bool IsValid() const;
  virtual bool IsActive() const;
  virtual void SetActive(bool b);

  static void Load(const cdm::ChestOcclusiveDressingData& src, SEChestOcclusiveDressing& dst);
  static cdm::ChestOcclusiveDressingData* Unload(const SEChestOcclusiveDressing& src);
protected:
  static void Serialize(const cdm::ChestOcclusiveDressingData& src, SEChestOcclusiveDressing& dst);
  static void Serialize(const SEChestOcclusiveDressing& src, cdm::ChestOcclusiveDressingData& dst);

public:

  virtual cdm::eSide GetSide() const;
  virtual void SetSide(cdm::eSide LeftOrRight);
  virtual bool HasSide() const;
  virtual void InvalidateSide();

  virtual void ToString(std::ostream &str) const;

protected:
  cdm::eSide m_Side;
  cdm::eSwitch m_State;
 
};   