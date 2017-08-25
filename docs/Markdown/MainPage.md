
# The Pulse Physiology Engine

Distributed under the <a href="https://www.apache.org/licenses/LICENSE-2.0">Apache License, Version 2.0.</a>
See accompanying <a href="https://gitlab.kitware.com/physiology/engine/blob/master/NOTICE">NOTICE</a> file for details.

## Latest News

### Events

Pulse team members will be attending the (<a href="https://mhsrs.amedd.army.mil/SitePages/Home.aspx">Military Health System Research Symposium (MHSRS)</a>) in Kissimmee, FL 27-30 August. Please email physiology@kitware.com if you are interested in meeting.

### Blog Posts

<a href="https://blog.kitware.com/visualizing-an-anaphylaxis-physiology-simulation-using-paraview/">Visualizing an Anaphylaxis Physiology Simulation Using ParaView</a>
<a href="https://blog.kitware.com/kitware-team-attending-military-health-services-research-symposium/">Kitware Team Attending Military Health System Research Symposium</a>
<a href="https://blog.kitware.com/toward-patient-specific-surgical-planning-including-individualized-physiology-modeling/">Toward Patient-Specific Surgical Planning Including Individualized Physiology Modeling</a>

@insert ./docs/markdown/MainPageFAQ.md

## Have more questions?

Check out the @ref ExtraFAQ for more insight.

There are @ref published papers and abstracts on several systems and clinical scenarios. 

If you have any questions or concerns email: physiology@kitware.com

Visit and post an <a href="https://gitlab.kitware.com/physiology/engine/issues">issue</a> at the repository if you have any trouble or other questions.

- - -

## Updates

The latest code base includes the following notable updates:
- Fixed multiplatform compiling bugs
- Moved from an in-source to out-of-source build
  - src tree is treated as read only
  - See a description <a href="https://cmake.org/Wiki/CMake_FAQ#What_is_an_.22out-of-source.22_build.3F">here</a>
- Full CMake Builds
  - Replaced all ant and scripts (.sh and .bat) with CMake
    - Improves build support across all target platforms
      - Currently supporting Windows, Mac, UNIX (including aarch64) devices
    - More multi-platform/compiler compliance
      - Currently supporting MSVC (2015+), GCC (4.8.1+), and Clang (3.3+)
      - Supports the Ninja build system 
  - Created a superbuild
    - Build scripts will download and build all dependent 3rd party libraries - removes the libs from source pool
    - Turnkey build process
- Converted reporting from emailing to write html reports to the test directory
  - Removes SMTP server requirement
  - Will help with external automated testing
- Moved the verification data set (very large) from source repository to a data server integrated with CMake
- Updates to ensure no 3rd party software license compliance issues for certain commercial applications
- Conversion of the data model from XML to google protocol buffers

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

