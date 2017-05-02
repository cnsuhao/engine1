BioGears Engine 
===============

The BioGears engine is a C++ library for human physiology simulation.
It is intended to provide accurate and consistent physiology data to medical education, research, and training technologies. 
The libraries built (*.dll/*.so) can be integrated with standalone applications, hardware simulators and sensor interfaces, and other physiology models of all fidelities.

The BioGears engine high-level objectives include:
-   Create a publicly available physiology research platform that
    enables accurate and consistent simulated physiology across training
    applications
-   Lower the barrier to create medical training content
-   Engage the community to develop and extend physiology models
-   Meet the training needs of the military
-   Expand the body of knowledge regarding the use of simulated
    physiology for medical education


## Setup Build Environment

While BioGears automatically pulls many libraries it needs to compile, 
you will still need to have the following tools installed (along with your choice of C++ compiler) :

### CMake
Go to the cmake website, `https://cmake.org/download`, and download the appropriate distribution.
Ensure that cmake is on your PATH and available in your cmd/bash shell.

### Java JDK

The test suite and data generate tools used by BioGears is written in Java.
While there is no dependency on Java when integrating BioGears with your application, it is currently required to build/develop BioGears.
You can get the JDK <a href="http://www.oracle.com/technetwork/java/javase/downloads/index.html">here.</a> 

Add a JAVA_HOME environment variable to point to the Java installation and add it to the system PATH. 

## Building BioGears

BioGears builds out of source, meaning the code base is seperated from the build files.
This means you will need two folders for BioGears, one for the source code and one for the build files.
Generally, I create a single directory to house these two folders.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~bash
mkdir BioGears
cd BioGears
mkdir src
cd src
git clone https://gitlab.kitware.com/BioGears/engine
cd ..
mkdir builds
cd builds
# Feel free to make subfolders here, like msvc2017x64 or something
# Generate a make file/msvc solution for the external dependencies
# Note you need to provide cmake the source directory at the end (relative or absolute)
cmake -DCMAKE_BUILD_TYPE:String=Release -DSUPERBUILD:BOOL=ON ../src
# Build the makefile or solution
make # if you are using visual studio, open the ExternalDependencies.sln and build the Release configuration
# MAKE SURE YOU BUILD THE INSTALL TARGET/PROJECT
# With the dependencies built, run cmake again to generate the engine solution/makefile
cmake -DCMAKE_BUILD_TYPE:String=Release -DSUPERBUILD:BOOL=OFF ../src
# Build the makefile or solution
make # if you are using visual studio, open the BioGears.sln and build the Release configuration
# Make sure to run the INSTALL target to set up the SDK if you want to use it
# You are ready to code and Run Tests
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

## Running and Testing

Once you have build the code base, you must generate the data required by the BioGears engine.
Execute the following script from the bin directory:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~bash
cmake -DTYPE:STRING=genData -P ../cmake/Scripts.cmake
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

BioGears provides a few driver programs to execute the physiology libraries built.

### BioGears Scenario Driver

The BioGears Scenario Driver is a simple C++ driver that reads a scenario XML file and creates a CSV file with results.
See <a href="https://biogearsengine.com/documentation/_scenario_x_m_l_file.html">here</a> for more info.

You will need to download the latest scenario/verification zip <a href="https://github.com/BioGearsEngine/Engine/releases/download/6.1.1-beta/BioGears_6.1.1-beta-verification-all.zip">here</a> and put the verification directory at the root of your source tree.
In the near future, we will link the verification data to this repository, so it will be downloaded automatically.

To run the driver, change directory in your cmd/bash shell to the bin directory and execute the following :
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~bash
# First ensure the release directory (or debug if that is what you are running) is on your path
PATH=%PATH%;./release # for windows
PATH=$PATH:./release # for linux
BioGearsScenarioDriver ../verification/Scenarios/Patient/BasicStandard.xml 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

If you are going to run the BioGearsSceanrioDriver through visual studio follow these steps
- Right-click the BioGearsScenarioDriver project and select 'Set as Startup Project'
- Right-click the Project and select settings
- Make sure you are on the appropriate configuration in the Configuration drop down. The one you intend to run
  - You probably want to do this for all configuration in the solution
- Click on 'Configuration Options->Debugging' on the left tree in the properties dialog
- Put the directory to your bin directory as the 'Working Directory'
- Enter the relative path to the associated directory containing the dlls for your selected configuration into the 'Envirionment' field.
  - For example, this is what you would enter to run against the 64bit release dll's: PATH=PATH;./release64
  
<b> You will also want to do this for the UnitTestDriver if you want to run that through visual studio as well </b>

### Java Based Testing Suite

BioGears provides a test harnes, written in Java, that will :
- Drive the BioGearsScenarioDrive
- Compare the generated csv results to a baseline csv file and report any differences
- Generate an plot image file for each data column of the csv file over the time of the scenario

To run the test driver change directory in your cmd/bash shell to the bin directory and execute the Scripts.cmake in the following way :
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~bash
cmake -DTYPE:STRING=<option> -P ../cmake/Scripts.cmake 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Where <option> can be one of the following :
- genData - Generate xml files from data in the ../data/BioGears.xlxs file (Patients, Substances, etc.)
- genStates - Generate BioGears state file for every patient at the point where the patient completed stabilization (Simulation time 0s)
- Any of the testing configurations found in ../test/config without the suffix
  - For Example : DebugRun, CDMUnitTests, ValidationSystems, VerificationScenarios, etc.
  - With exception of the Characterize.config, this is a legacy testing configuration that will not work  
- SystemValidation - Will run the ../test/config/ValidationSystems configuration plus create validation tables from comparing results to ../test/validation
- PatientValidation - Will run the ../test/config/ValidationPatients configuration plus create validation tables from comparing results to ../test/validation

<b>Results will be place in the bin/test_results directory </b>

#### Configuration Files

The configuration files, referenced above, provied the testing suite direction on how to execute BioGears and what to do with the results.


## Creating the Sofware Developmenet Kit (SDK)

BioGears provides an SDK that contains all the files needed to integrate its libraries into your application.
The SDK contains the following folders
- bin - binaries and xml datafiles
- include - headers files needed for code integration
- lib - libraries needed for code integration
- howto - a set of simple drivers (in both C++ and Java) showing how to use BioGears

The SDK requires both the data generated from the genData script option, as well as patient state data generated from the genStates script option.
To generate these patient states, exeute the following option :

Once you have build the code base, you must generate the data required by the BioGears engine.
Execute the following script from the bin directory:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~bash
cmake -DTYPE:STRING=genStates -P ../cmake/Scripts.cmake
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Run the INSTALL target to copy the header files and libraries required to integrate BioGears into your application.
Headers will be copied to the sdk/include directory
Libraries will be copied to the sdk/lib directory
And your bin directory is still your valid working directory.
There is a CMake file in the sdk folder that will build an executable with a collection of howto
files that demostraight how to use the BioGears API. Choose the examples to run in the BioGearsEngineHowTo.cpp file.
There is also an example of using a Java based BioGears interface with an eclipse project you can explore as well.

## Programmatics

BioGears began at Applied Research Associates, Inc. (ARA) with oversight from 
the Telemedicine and Advanced Technology Research Center (TATRC) under award W81XWH-13-2-0068

All files are released under the Apache 2.0 license
