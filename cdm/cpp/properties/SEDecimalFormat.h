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
#include "bind/cdm/Properties.pb.h"

class CDM_DECL SEDecimalFormat
{
public:
  SEDecimalFormat(const SEDecimalFormat* dfault = nullptr);
  virtual ~SEDecimalFormat();

  virtual void Clear();
  virtual void Set(const SEDecimalFormat& f);

  static void Load(const cdm::DecimalFormatData& src, SEDecimalFormat& dst);
  static cdm::DecimalFormatData* Unload(const SEDecimalFormat& src);
protected:
  static void Serialize(const cdm::DecimalFormatData& src, SEDecimalFormat& dst);
  static void Serialize(const SEDecimalFormat& src, cdm::DecimalFormatData& dst);
public:

  void SetPrecision(std::streamsize p);
  std::streamsize GetPrecision();

  void SetNotation(cdm::DecimalFormatData::eType n);
  cdm::DecimalFormatData::eType GetNotation();

  void SetStream(std::ofstream& s);

protected:
  std::streamsize               m_Precision;
  cdm::DecimalFormatData::eType m_Notation;

};