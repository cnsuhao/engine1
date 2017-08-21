/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "Hepatic.h"

Hepatic::Hepatic(PulseController& data) : SEHepaticSystem(data.GetLogger()), m_data(data)
{
  Clear();
}

Hepatic::~Hepatic()
{
  Clear();
}

void Hepatic::Clear()
{
  SEHepaticSystem::Clear();
}

//--------------------------------------------------------------------------------------------------
/// \brief
/// Initializes system properties to valid homeostatic values.
//--------------------------------------------------------------------------------------------------
void Hepatic::Initialize()
{
  PulseSystem::Initialize();

}

void Hepatic::Load(const pulse::HepaticSystemData& src, Hepatic& dst)
{
  Hepatic::Serialize(src, dst);
  dst.SetUp();
}
void Hepatic::Serialize(const pulse::HepaticSystemData& src, Hepatic& dst)
{
  SEHepaticSystem::Serialize(src.common(), dst);
}

pulse::HepaticSystemData* Hepatic::Unload(const Hepatic& src)
{
  pulse::HepaticSystemData* dst = new pulse::HepaticSystemData();
  Hepatic::Serialize(src, *dst);
  return dst;
}
void Hepatic::Serialize(const Hepatic& src, pulse::HepaticSystemData& dst)
{
  SEHepaticSystem::Serialize(src, *dst.mutable_common());
}

//--------------------------------------------------------------------------------------------------
/// \brief
/// Initializes parameters for the Hepatic Class
///
///  \details
///   Initializes member variables and system level values on the common data model.
//--------------------------------------------------------------------------------------------------
void Hepatic::SetUp()
{
 
}

//--------------------------------------------------------------------------------------------------
/// \brief
/// Determines if the engine is stable.
///
/// \details
/// When the engine is stable, the CDM makes this call to update the member variable.
//--------------------------------------------------------------------------------------------------
void Hepatic::AtSteadyState()
{

}

//--------------------------------------------------------------------------------------------------
/// \brief
/// Preprocess function
///
/// \details
//--------------------------------------------------------------------------------------------------
void Hepatic::PreProcess()
{

}

//--------------------------------------------------------------------------------------------------
/// \brief
/// Process function
///
/// \details
//--------------------------------------------------------------------------------------------------
void Hepatic::Process()
{  
  
}

//--------------------------------------------------------------------------------------------------
/// \brief
/// PostProcess function
///
/// \details
//--------------------------------------------------------------------------------------------------
void Hepatic::PostProcess()
{

}