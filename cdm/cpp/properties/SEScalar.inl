/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "utils/GeneralMath.h"

template<typename Unit>
SEScalarQuantity<Unit>::SEScalarQuantity() : SEUnitScalar()
{

}

template<typename Unit>
SEScalarQuantity<Unit>::~SEScalarQuantity()
{
  this->Clear();
}

template<typename Unit>
void SEScalarQuantity<Unit>::Clear()
{
  SEScalar::Clear();
  m_unit = nullptr;
}

template<typename Unit>
void SEScalarQuantity<Unit>::Invalidate()
{
  SEScalar::Invalidate();
  m_unit = nullptr;
}

template<typename Unit>
bool SEScalarQuantity<Unit>::IsValid() const
{
  if (!SEScalar::IsValid())
    return false;
  if (m_unit == nullptr)
    return false;
  return true;
}

template<typename Unit>
void SEScalarQuantity<Unit>::Serialize(const cdm::ScalarData& src, SEScalarQuantity<Unit>& dst)
{
  dst.Clear();
  if (!src.unit().empty())
    dst.SetValue(src.value(), Unit::GetCompoundUnit(src.unit()));
  else
    throw CommonDataModelException("ScalarQuantity attempted to load a ScalarData with no unit, must have a unit.");  
  dst.m_readOnly = src.readonly();
}

template<typename Unit>
void SEScalarQuantity<Unit>::Serialize(const SEScalarQuantity<Unit>& src, cdm::ScalarData& dst)
{
  dst.set_value(src.m_value);
  if(src.m_unit!=nullptr)
    dst.set_unit(src.m_unit->GetString()); 
  else
    throw CommonDataModelException("ScalarQuantity attempted to unload a ScalarData with no unit, must have a unit.");
  dst.set_readonly(src.m_readOnly);
}

template<typename Unit>
bool SEScalarQuantity<Unit>::Set(const SEScalar& s)
{
  const SEScalarQuantity<Unit>* q = dynamic_cast<const SEScalarQuantity<Unit>*>(&s);
  if (q == nullptr)
    throw CommonDataModelException("Set method called with differnt scalar quantity type");
  return this->Set(*q);
}

template<typename Unit>
bool SEScalarQuantity<Unit>::Set(const SEScalarQuantity<Unit>& s)
{
  if (m_readOnly)
    throw CommonDataModelException("Scalar is marked read-only");
  if (!s.IsValid())
    return false;
  m_value = s.m_value;
  m_isnan = (std::isnan(m_value)) ? true : false;
  m_isinf = (std::isinf(m_value)) ? true : false;
  m_unit = s.m_unit;
  return true;
}

template<typename Unit>
void SEScalarQuantity<Unit>::Copy(const SEScalar& s)
{
  const SEScalarQuantity<Unit>* q = dynamic_cast<const SEScalarQuantity<Unit>*>(&s);
  if (q == nullptr)
    throw CommonDataModelException("Set method called with differnt scalar quantity type");
  this->Copy(*q);
}

template<typename Unit>
void SEScalarQuantity<Unit>::Copy(const SEScalarQuantity<Unit>& s)
{
  SEScalar::Copy(s);
  m_unit = s.m_unit;
}

template<typename Unit>
double SEScalarQuantity<Unit>::GetValue(const Unit& unit) const
{
  if (m_isnan)
    throw CommonDataModelException("Value is NaN");
  if (m_isinf)
    return m_value;
  if (m_value == 0)
    return m_value;
  if (m_unit == &unit)
    return m_value;
  return Convert(m_value, *m_unit, unit);
}

template<typename Unit>
double SEScalarQuantity<Unit>::GetValue(const CCompoundUnit& unit) const
{
  const Unit* u = dynamic_cast<const Unit*>(&unit);
  if (u == nullptr)
    throw CommonDataModelException("Provided unit is not of proper quantity type");
  return this->GetValue(*u);
}

template<typename Unit>
const Unit* SEScalarQuantity<Unit>::GetUnit() const
{
  return m_unit;
}

template<typename Unit>
void SEScalarQuantity<Unit>::SetValue(double d, const Unit& unit)
{
  if (m_readOnly)
    throw CommonDataModelException("Scalar is marked read-only");
  m_value = d;
  m_isnan = (std::isnan(m_value)) ? true : false;
  m_isinf = (std::isinf(m_value)) ? true : false;
  m_unit = &unit;
}
template<typename Unit>
void SEScalarQuantity<Unit>::ForceValue(double d, const Unit& unit)
{
  if (m_readOnly)
    throw CommonDataModelException("Scalar is marked read-only");
  m_value = d;
  m_isnan = (std::isnan(m_value)) ? true : false;
  m_isinf = (std::isinf(m_value)) ? true : false;
  m_unit = &unit;
}

template<typename Unit>
void SEScalarQuantity<Unit>::SetValue(double d, const CCompoundUnit& unit)
{
  const Unit* u = dynamic_cast<const Unit*>(&unit);
  if (u == nullptr)
    throw CommonDataModelException("Provided unit is not of proper quantity type");
  this->SetValue(d, *u);
}
template<typename Unit>
void SEScalarQuantity<Unit>::ForceValue(double d, const CCompoundUnit& unit)
{
  const Unit* u = dynamic_cast<const Unit*>(&unit);
  if (u == nullptr)
    throw CommonDataModelException("Provided unit is not of proper quantity type");
  this->SetValue(d, *u);
}

template<typename Unit>
double SEScalarQuantity<Unit>::Increment(const SEScalarQuantity<Unit>& s)
{
  if (!s.IsValid())
    this->Invalidate();
  else
    return this->IncrementValue(s.m_value, *s.m_unit);
  return m_value;
}

template<typename Unit>
double SEScalarQuantity<Unit>::IncrementValue(double d, const Unit& unit)
{
  if (!IsValid())
  {
    this->SetValue(d, unit);
    return d;
  }
  this->SetValue(m_value + Convert(d, unit, *m_unit), *m_unit);
  return Convert(m_value, *m_unit, unit);
}

template<typename Unit>
double SEScalarQuantity<Unit>::IncrementValue(double d, const CCompoundUnit& unit)
{
  const Unit* u = dynamic_cast<const Unit*>(&unit);
  if (u == nullptr)
    throw CommonDataModelException("Provided unit is not of proper quantity type");
  return this->IncrementValue(d, *u);
}

template<typename Unit>
bool SEScalarQuantity<Unit>::Equals(const SEScalarQuantity<Unit>& to) const
{
  if (m_unit == nullptr)
    return false;
  if (m_isnan && to.m_isnan)
    return true;
  if (m_isnan || to.m_isnan)
    return false;
  if (m_isinf&&to.m_isinf)
    return true;
  if (m_isinf || to.m_isinf)
    return false;
  double t = to.GetValue(*m_unit);
  return std::abs(GeneralMath::PercentDifference(m_value, t)) <= 1e-15;
}

template<typename Unit>
const CCompoundUnit* SEScalarQuantity<Unit>::GetCompoundUnit(const std::string& unit) const
{
  return &Unit::GetCompoundUnit(unit);
}

template<typename Unit>
void SEScalarQuantity<Unit>::ToString(std::ostream &str) const
{
  if(m_isnan || m_isinf)
    str << m_value << std::flush;
  else
    str << m_value << "(" << *m_unit << ")" << std::flush;
}
