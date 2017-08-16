/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "scenario/SEAction.h"

class CDM_DECL SESerializeState : public SEAction
{
public:

  SESerializeState();
  virtual ~SESerializeState();

  virtual void Clear(); //clear memory

  virtual bool IsValid() const;

  static void Load(const cdm::SerializeStateData& src, SESerializeState& dst);
  static cdm::SerializeStateData* Unload(const SESerializeState& src);
protected:
  static void Serialize(const cdm::SerializeStateData& src, SESerializeState& dst);
  static void Serialize(const SESerializeState& src, cdm::SerializeStateData& dst);

public:

  virtual void ToString(std::ostream &str) const;

  virtual cdm::SerializeStateData_eSerializationType GetType() const;
  virtual void SetType(cdm::SerializeStateData_eSerializationType t);

  virtual bool HasFilename() const;
  virtual std::string GetFilename() const;
  virtual void SetFilename(const std::string& filename);
  virtual void InvalidateFilename();

protected:

  std::string                       m_Filename;
  cdm::SerializeStateData_eSerializationType m_Type;
};                  