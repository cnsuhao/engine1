     

# Welcome to the Kitware Physiology Engine

The Kitware Physiology Engine is a fork of the <p>BioGears<sup>&reg;</sup></p> project began at Applied Research Associates, Inc.  Therefore, you will see the Physiology Engine referred to as "BioGears" throughout the Apache 2.0 licenses documentation.

- - -

@insert ./docs/markdown/MainPageFAQ.md

## Have more questions?

See the @ref ExtraFAQ for any other questions you may have.

- - -

## Programmatics

The Kitware Physiology Engine is a fork of the BioGears project began at Applied Research Associates, Inc. with oversight from the Telemedicine and Advanced Technology Research Center (TATRC) under award W81XWH-13-2-0068.

Both the BioGears and Kitware Physiology Engines are released under this @ref License.

There are @ref published papers and abstracts on several systems and clinical scenarios. 

- - -

## Updates Since Forking

The latest deployment includes the following notable updates:
- Fixed multiplatform compiling bugs
- Moved from an in-source to out-of-source build
	- src tree is treated as read only
	- See a description <a href="https://cmake.org/Wiki/CMake_FAQ#What_is_an_.22out-of-source.22_build.3F">here</a>
- Full CMake Builds
	- Replaced all ant and scripts (.sh and .bat) with CMake
		- Improves build support across all target platforms (requested by AMM)
		- Will enable other future features
	- Created a superbuild
		- Build scripts will download and build all dependent 3rd party libraries - removes the libs from source pool
		- Turnkey build process
- Converted reporting from emailing to write html reports to the test directory
	- Removes SMTP server requirement
	- Will help with external automated testing
- Removed verification data set (very large) from source repository

(Interested in a previous @ref version?)

- - -

## Planned Improvements

Near Term:
- Updates to ensure no 3rd party software license compliance issues for certain commercial applications
- C# interface support
- More multi-platform/compiler compliance
	- Currently only have MSVC and GCC compliance
	- Add Clang, Ninja, other flavors of UNIX
- Utilize external data configurations to pull the large verification data set

Long Term:
- Public Continuous Build Server and CDash Server for improved verification and validation
- Pull/Merge request process for methodology changes
- Modularity improvements for model swapping

- - -
@anchor known-issues
## Known Physiology Model Issues and Limitations
The following are known issues with the current version of the software:
- Lack of a full sympathetic/parasympathetic nervous system
- Extravascular fluid exchange model is incomplete
- Peripheral resistance currently does not scale with core temperature
- Only tested a simulation up to 12 hours in length (No sleep model)
- Limited Consumption model
	- Limited number of macronutrients available
	- Limited conversion and use within the engine
- Oxygen saturation drops too sharply


@page errors Errors

@page events Events

