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

#include "stdafx.h"
#include "system/physiology/SEPupillaryResponse.h"
#include "properties/SEScalarNegative1To1.h"

SEPupillaryResponse::SEPupillaryResponse(Logger* logger)
{
  m_ReactivityModifier = nullptr;
  m_ShapeModifier = nullptr;
  m_SizeModifier = nullptr;
}

SEPupillaryResponse::~SEPupillaryResponse()
{
  Clear();
}

void SEPupillaryResponse::Clear()
{
  SAFE_DELETE(m_ReactivityModifier);
  SAFE_DELETE(m_ShapeModifier);
  SAFE_DELETE(m_SizeModifier);
}

const SEScalar* SEPupillaryResponse::GetScalar(const std::string& name)
{
  if (name.compare("ReactivityModifier") == 0)
    return &GetReactivityModifier();
  if (name.compare("ShapeModifier") == 0)
    return &GetShapeModifier();
  if (name.compare("SizeModifier") == 0)
    return &GetSizeModifier();
  return nullptr;
}

void SEPupillaryResponse::Load(const cdm::PupillaryResponseData& src, SEPupillaryResponse& dst)
{
  SEPupillaryResponse::Serialize(src, dst);
}
void SEPupillaryResponse::Serialize(const cdm::PupillaryResponseData& src, SEPupillaryResponse& dst)
{
  dst.Clear();
  if (src.has_reactivitymodifier())
    SEScalarNegative1To1::Load(src.reactivitymodifier(), dst.GetReactivityModifier());
  if (src.has_shapemodifier())
    SEScalarNegative1To1::Load(src.shapemodifier(), dst.GetShapeModifier());
  if (src.has_sizemodifier())
    SEScalarNegative1To1::Load(src.sizemodifier(), dst.GetSizeModifier());
}

cdm::PupillaryResponseData* SEPupillaryResponse::Unload(const SEPupillaryResponse& src)
{
  cdm::PupillaryResponseData* dst = new cdm::PupillaryResponseData();
  SEPupillaryResponse::Serialize(src, *dst);
  return dst;
}
void SEPupillaryResponse::Serialize(const SEPupillaryResponse& src, cdm::PupillaryResponseData& dst)
{
  if (src.HasReactivityModifier())
    dst.set_allocated_reactivitymodifier(SEScalarNegative1To1::Unload(*src.m_ReactivityModifier));
  if (src.HasShapeModifier())
    dst.set_allocated_shapemodifier(SEScalarNegative1To1::Unload(*src.m_ShapeModifier));
  if (src.HasSizeModifier())
    dst.set_allocated_sizemodifier(SEScalarNegative1To1::Unload(*src.m_SizeModifier));
}

bool SEPupillaryResponse::HasReactivityModifier() const
{
  return m_ReactivityModifier == nullptr ? false : m_ReactivityModifier->IsValid();
}
SEScalarNegative1To1& SEPupillaryResponse::GetReactivityModifier()
{
  if (m_ReactivityModifier == nullptr)
    m_ReactivityModifier = new SEScalarNegative1To1();
  return *m_ReactivityModifier;
}
double SEPupillaryResponse::GetReactivityModifier() const
{
  if (m_ReactivityModifier == nullptr)
    return SEScalar::dNaN();
  return m_ReactivityModifier->GetValue();
}

bool SEPupillaryResponse::HasShapeModifier() const
{
  return m_ShapeModifier == nullptr ? false : m_ShapeModifier->IsValid();
}
SEScalarNegative1To1& SEPupillaryResponse::GetShapeModifier()
{
  if (m_ShapeModifier == nullptr)
    m_ShapeModifier = new SEScalarNegative1To1();
  return *m_ShapeModifier;
}
double SEPupillaryResponse::GetShapeModifier() const
{
  if (m_ShapeModifier == nullptr)
    return SEScalar::dNaN();
  return m_ShapeModifier->GetValue();
}

bool SEPupillaryResponse::HasSizeModifier() const
{
  return m_SizeModifier == nullptr ? false : m_SizeModifier->IsValid();
}
SEScalarNegative1To1& SEPupillaryResponse::GetSizeModifier()
{
  if (m_SizeModifier == nullptr)
    m_SizeModifier = new SEScalarNegative1To1();
  return *m_SizeModifier;
}
double SEPupillaryResponse::GetSizeModifier() const
{
  if (m_SizeModifier == nullptr)
    return SEScalar::dNaN();
  return m_SizeModifier->GetValue();
}


