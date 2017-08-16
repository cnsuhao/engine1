/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "compartment/substances/SESubstanceQuantity.h"
#include "substance/SESubstanceTransport.h"
class SEGasCompartment;

class CDM_DECL SEGasSubstanceQuantity : public SESubstanceQuantity, public SEGasTransportSubstance
{
  friend class SEGasCompartment;
protected:
  SEGasSubstanceQuantity(SESubstance& sub, SEGasCompartment& compartment);
public:
  virtual ~SEGasSubstanceQuantity();

  virtual void Clear();
  virtual void Invalidate();

  static void Load(const cdm::GasSubstanceQuantityData& src, SEGasSubstanceQuantity& dst);
  static cdm::GasSubstanceQuantityData* Unload(const SEGasSubstanceQuantity& src);
protected:
  static void Serialize(const cdm::GasSubstanceQuantityData& src, SEGasSubstanceQuantity& dst);
  static void Serialize(const SEGasSubstanceQuantity& src, cdm::GasSubstanceQuantityData& dst);

public:
  virtual void SetToZero();
  virtual const SEScalar* GetScalar(const std::string& name);

  virtual bool HasPartialPressure() const;
  virtual SEScalarPressure& GetPartialPressure();
  virtual double GetPartialPressure(const PressureUnit& unit) const;
  
  virtual bool HasVolume() const;
  virtual SEScalarVolume& GetVolume();
  virtual double GetVolume(const VolumeUnit& unit) const;

  virtual bool HasVolumeFraction() const;
  virtual SEScalar0To1& GetVolumeFraction();
  virtual double GetVolumeFraction() const;

protected:
  virtual void AddChild(SEGasSubstanceQuantity& subQ);

  virtual bool HasExtensive() const { return HasVolume(); }
  virtual SEScalarVolume& GetExtensive() { return GetVolume(); }

  virtual bool HasIntensive() const { return HasVolumeFraction(); }
  virtual SEScalar0To1& GetIntensive() { return GetVolumeFraction(); }

  SEScalarPressure* m_PartialPressure;
  SEScalarVolume*   m_Volume;
  SEScalar0To1* m_VolumeFraction;

  SEGasCompartment&        m_Compartment;
  std::vector<SEGasSubstanceQuantity*> m_Children;
};