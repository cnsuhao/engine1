/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

//----------------------------------------------------------------------------
/// @file PScalar.cpp
/// @author Chris Volpe
///
/// PScalar is short for Physics Scalar. It is an encapsulation of a 
/// double precision floating point value and a CompoundUnit object. 
/// It allows all the expected arithmetic operations, as well as the 
/// functions pow() for raising to a power, and sqrt() for computing the
/// square root.
//----------------------------------------------------------------------------

#include "stdafx.h"
#include "utils/unitconversion/UCCommon.h"

// We need one translation unit that processes the header file in
// this DLL or else the methods won't be available in the Debug build, 
// since inline function optimization isn't done

// Technically, we don't need any more than this, but let's insert some 
// dummy code here to exercise some of the functionality at compile time. 
// I've run into a few situations where enhancements I've made to the API, 
// particularly for PScalars, resulted in overload-resolution issues when
// clients attempt to use them. So let's try to catch those issues here so that
// we don't have a situation where this library builds, but a client won't.

/*
static void TestMyAPI()
{
  CPScalar s1("g"), s2(s1);
  s1.ConvertTo(s2);
}
*/