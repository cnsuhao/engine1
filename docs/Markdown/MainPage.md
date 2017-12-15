
# The Pulse Physiology Engine

Distributed under the <a href="https://www.apache.org/licenses/LICENSE-2.0">Apache License, Version 2.0.</a>
See accompanying <a href="https://gitlab.kitware.com/physiology/engine/blob/master/NOTICE">NOTICE</a> file for details.

For the latest new visit our <a href="https://blog.kitware.com/tag/pulse/">blog</a>

There are @ref published papers and abstracts on several systems and clinical scenarios. 

You can get Pulse from this <a href="https://gitlab.kitware.com/physiology/engine">GitLab repository</a>.

Use this <a href="https://discourse.kitware.com/c/pulse-physiology-engine">discourse channel</a> 
to ask or share anything and everything about building, using, or understanding the Pulse engine.

Visit and post an <a href="https://gitlab.kitware.com/physiology/engine/issues">issue</a> at the repository if you have any problems with the codebase.

If you have any other questions or concerns email: kitware@kitware.com

And welcome to our community!!


@insert ./docs/markdown/MainPageFAQ.md

## Have more questions?

Check out the @ref ExtraFAQ for more insight.


- - -

## What's new in Pulse v1.0 (September 1st, 2017)

The latest code base includes the following notable updates:
- Fixed multiplatform compiling bugs
- Moved from an in-source to out-of-source build
  - src tree is treated as read only
  - See a description <a href="https://cmake.org/Wiki/CMake_FAQ#What_is_an_.22out-of-source.22_build.3F">here</a>
- Full CMake Builds
  - Replaced all ant and scripts (.sh and .bat) with CMake
    - Improves build support across all target platforms
      - Currently supporting Windows, Mac, UNIX (including AArch64) devices
    - More multi-platform/compiler compliance
      - Currently supporting MSVC (2015+), GCC (4.8.1+), and Clang (3.3+)
      - Supports the Ninja build system 
  - Created a superbuild
    - Build scripts will download and build all dependent 3rd party libraries - removes the libs from source pool
    - Turnkey build process
- Converted reporting from emailing to write html reports to the test directory
  - Removes SMTP server requirement
- Moved the verification data sets (very large) from source repository to a data server integrated with CMake
- Updates to ensure no 3rd party software license compliance issues for certain commercial applications
- Conversion of the data model from XML to Google Protocol Buffers

(Interested in a previous @ref version?)

- - -

## Planned Software Improvements

- C# interface support
- Integration with CTest
- Public Continuous Integration Server and CDash Server for improved verification and validation
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

