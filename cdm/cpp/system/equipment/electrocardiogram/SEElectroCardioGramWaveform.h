/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "bind/cdm/ElectroCardioGram.pb.h"

class CDM_DECL SEElectroCardioGramWaveform : public Loggable
{
public:

  SEElectroCardioGramWaveform(Logger* logger);
  virtual ~SEElectroCardioGramWaveform();

  virtual void Clear();// Deletes all members

  static void Load(const cdm::ElectroCardioGramWaveformData& src, SEElectroCardioGramWaveform& dst);
  static cdm::ElectroCardioGramWaveformData* Unload(const SEElectroCardioGramWaveform& src);
protected:
  static void Serialize(const cdm::ElectroCardioGramWaveformData& src, SEElectroCardioGramWaveform& dst);
  static void Serialize(const SEElectroCardioGramWaveform& src, cdm::ElectroCardioGramWaveformData& dst);

public:  
  virtual bool HasLeadNumber() const;
  virtual cdm::ElectroCardioGramWaveformData_eLead  GetLeadNumber() const;
  virtual void SetLeadNumber(cdm::ElectroCardioGramWaveformData_eLead n);
  virtual void InvalidateLeadNumber();

  virtual cdm::eHeartRhythm GetRhythm() const;
  virtual void SetRhythm(cdm::eHeartRhythm name);

  virtual bool HasData() const;
  virtual SEFunctionElectricPotentialVsTime& GetData();
  virtual const SEFunctionElectricPotentialVsTime* GetData() const;

  virtual bool HasTimeStep() const;
  virtual SEScalarTime& GetTimeStep();
  virtual double GetTimeStep(const TimeUnit& unit) const;

  virtual std::vector<unsigned int>& GetActiveIndicies() { return m_ActiveIndicies; }

protected:

  cdm::ElectroCardioGramWaveformData_eLead m_LeadNumber;
  cdm::eHeartRhythm                        m_Rhythm;
  SEScalarTime*                            m_TimeStep;
  SEFunctionElectricPotentialVsTime*       m_Data;
  std::vector<unsigned int>                m_ActiveIndicies;
};