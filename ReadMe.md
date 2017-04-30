BioGears 
===========

BioGears is a C++ based human physiology simulation library.
It is intended to provide accurate and consistent physiology data to medical education, research, and training technologies. 
The libraries built (*.dll/*.so) can be integrated wil standalone application, hardware simulators, sensor interfaces, and other simulation models of all fidelities.

BioGears high-level objectives include:
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

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
mkdir BioGears
cd BioGears
mkdir src
cd src
git clone https://gitlab.kitware.com/BioGears/engine
cd ..
mkdir builds
cd builds


~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

## Running and Testing

Once you have build the code base, you must generate the data required by the BioGears engine.
Execute the following script from the bin directory:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
cmake -DTYPE:STRING=genData -P ../cmake/Scripts.cmake
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

BioGears provides a few driver programs to execute the physiology libraries built.

### BioGears Scenario Driver

### Java Based Testing Suite

BioGears provides a test harnes, written in Java, that will :
- Drive the BioGearsScenarioDrive
- Compare the generated csv results to a baseline csv file and report any differences
- Generate an plot image file for each data column of the csv file over the time of the scenario

To run the test driver change directory in your cmd/bash shell to the bin directory and execute the Scripts.cmake in the following way :
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
cmake -DTYPE:STRING=genStates -P ../cmake/Scripts.cmake
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Now you can generate the SDK by calling CPack as follows :

