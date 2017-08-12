Source Code {#SourceCode}
===========

The code base consists of:
- Engine - A C++ based lumped parameter model
- @ref CDM - A set of generalized data classes for defining the data interfaces of a @ref physeng
-	@ref Toolkit - Various tools for execution and data manipulation, primarily written in Java 

The source is structured as follows:
- bin - Contains all data and configuration files needed for execution of the engine
- data  - Contains the Microsoft Excel spreadsheets for all data sets
- lib - Contains third party libraries used by this project (see @ref Credits for more details)
- src
	- cdm - Code associated with the @ref CDM and @ref physeng 
  - cmake - The directory where cmake will create build files
	- engine - Code associated with the lumped parameter models 
    - PulseConfiguration - @copybrief PulseConfiguration
    - PulseScenario - @copybrief PulseScenario
    - controller - These classes hold data necessary by the model, control the advancement of time
      - Controller - @copybrief %PulseController
      - Circuits - @copybrief PulseCircuits
      - Compartments - @copybrief PulseCompartments
      - Engine - @copybrief PulseEngine
      - ScenarioExec - @copybrief PulseScenarioExec
      - Substances - @copybrief PulseSubstances
      - System - @copybrief PulseSystem
    - systems - These classes implement the methodology for modeling and simulating
      - BloodChemistry - @copybrief BloodChemistry
      - Cardiovascular - @copybrief Cardiovascular
      - Drugs - @copybrief Drugs
      - Endocrine - @copybrief Endocrine
      - Energy - @copybrief Energy
      - Environment - @copybrief Environment
      - Gastrointestinal - @copybrief Gastrointestinal
      - Nervous - @copybrief Nervous
      - Renal - @copybrief Renal
      - Respiratory - @copybrief Respiratory		
      - SaturationCalculator - @copybrief SaturationCalculator	
      - Tissue - @copybrief Tissue
    - equipment
      - AnesthesiaMachine - @copybrief AnesthesiaMachineData
      - ECG - @copybrief ElectrocardiogramData
      - Inhaler - @copybrief InhalerData    
	- gui - Code associated with the @ref Toolkit GUI
  - schema - The xsd data definitions used by the CDM
	- sdk - Example code and scripts for the @ref Toolkit and @ref SDK
	- utils - Various utilities used in validation
	- verification - Extract the verification files into this directory. You can get more detail @link VV here. @endlink
	
## Building

Refer to the <a href="https://gitlab.kitware.com/physiology/engine">repository</a> for build instructions