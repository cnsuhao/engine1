## What is the Pulse Physiology Engine?

The Pulse Physiology Engine is a C++ based, open source, multi-platform (Windows, Mac, and Linux), comprehensive human physiology
simulator that will drive medical education, research, and training technologies. 
The engine enables accurate and consistent physiology simulation across the medical community. 
The engine can be used as a standalone application or integrated with simulators, sensor interfaces, and models of all fidelities.
We plan to further advance the engine and explore new avenues of research, such as pediatrics, patient-specific modeling and virtual surgery planning/rehearsal. 

<img src="./Images/PulseRunner.png" width="550">

The Pulse Physiology Engine is a fork of the BioGears Physiology Engine.
This fork was driven by several community needs, including:

#### 1. Active, Publicly Available Repository
The <a href="https://gitlab.kitware.com/physiology/engine">Pulse git repository</a> was created with the BioGears 6.1.1 code archive. 
The Pulse team actively develops on this repository with contributions from other community members. 
The public repository  provides a central location for the community to view and test active development, 
report issues and contribute to the Pulse Physiology Engine. This is a truly open and community-driven project.


#### 2. Cross-Platform Build Process Improvements
Pulse has refactored the build process to require only <a href="https://cmake.org/">CMake</a>, a cross-platform family of tools designed to build, test and package software. 
This removes the need for any platform and compiler customized build scripts, which has greatly simplified the process for 3rd party users
 to build and integrate Pulse into their applications. 
With this change, Pulse can easily be built with the GCC, Clang, MSVC, and Ninja compilers on any of our supported platforms (Windows, Mac, Linux, and AArch64).


#### 3. License Updates
The licensing goal of the engine is to maintain a permissive Apache 2.0 license (free to use with no restrictions) 
to encourage use of the open-source software in academic, government and commercial products. 
Several open-source libraries are used by the engine and have permissive licenses that do not affect the use of the engine in future products and applications. 
However, the Code Synthesis XSD <a href="http://www.codesynthesis.com/licenses/gpl-2.txt">GNU General Public License</a> with <a href="http://www.codesynthesis.com/projects/xsd/FLOSSE">FLOSS exception</a>
 created a significant open-source licensing limitation, which restricts any proprietary extensions of the physiology engine.

Any use of the engine, without modification, is exempt from the GPL license and does not need to be made public (open-source). 
Any extensions to the engine must be made publicly available without cost, or a Proprietary License for Code Synthesis
 must be <a href="http://www.codesynthesis.com/contact/">purchased</a> for the product/application using the modified engine to comply with the license terms for Code Synthesis.

To resolve this license issue, Pulse has replaced the Xerces and Code Synthesis libraries with the <a href="https://developers.google.com/protocol-buffers/">Google Protocol Buffer</a> library. 
This library is licensed under <a href="https://opensource.org/licenses/BSD-3-Clause">BSD 3-clause</a> and allows anyone to modify the Pulse Physiology Engine in anyway without any requirement
 to make their project code base publicly available.

#### 4. Improved Data Management and Test Suite Reporting
The provided test suite executes scenarios and compares the generated results file to the "gold standard" data file for the same scenario. 
Pulse removed the SMTP requirement for viewing the test report, and instead generates a summary on disk that can be viewed by a user. 
This change reduces the required infrastructure needed to perform unit, verification and validation testing. 
The set of "gold standard" data files  for the physiology engine is very large (~500MB). 
Keeping these files in the git repository can easily bloat the repository. 
Pulse has addressed this issue by hosting all verification sets in <a href="https://data.kitware.com/#collection/59849c788d777f7d33e9c084/folder/598c95d88d777f7d33e9c1fa">a publicly available data server</a>, 
associating different versions to the git repository history though a collection of hash files in the git repository. 
CMake is then used to provide management between the data server and the specific code version from the git repository. 
This separation provides a repository with a small footprint to allow for quick pulling and branching, 
while maintaining a historical associations with the large data set needed for testing.

## What are some possible physiology engine applications?
<center>
<table border="0">
<tr>
    <td><center><b>Virtual Environments</b></center></td>
    <td><center><b>Manikin-Based Simulations</b></center></td>
	<td><center><b>Clinical Explorations</b></center></td>
</tr>
<tr>
    <td><img src="./Images/PulseVR.png" width="365"></td>
    <td><img src="./Images/PulseClinician.png" width="365"></td>
	<td><img src="./Images/PulseProgrammer.png" width="365"></td>
</tr>
</table>
</center>

There is a wide range of potential applications, a few include:
- Powering serious games for medical education and training
- Producing responsive physiology in real time for manikin training
- Integrating a single-system model into the engine to understand full-body physiologic response
- Providing inputs and outputs for sensor systems
- Teaching and education
- Pairing with virtual surgery planning/rehearsal

## What can the physiology engine do?
<img src="./Images/PulseMontage.png" width="365">

An instance of an engine models a single patient's physiology.
- The patient is defined by parameters, such as height, weight, systolic and diastolic pressure.
- You can initialize the patient with specific chronic and/or disease states via conditions.
- You can modify the patients external environmental conditions (weather, submerge in water, etc.)
- You can apply various actions (acute insults/injuries, interventions, conscious breathing, exercise, etc.) to be applied to the patient.
- The patient can also interact with equipment models, such as an Anesthesia and/or an %ECG Machine as well as an %Inhaler via actions.
- You can integrate the engine into your applications.

### Pulse Physiology Explorer

The Pulse Physiology Engine is a powerful tool in computing the physiological responses to acute injury and treatment.
However, without a visualization tool the information is difficult to understand.
As part of the Kitware physiology repository, we have developed a new visualization tool built on Qt and ParaView to provide a visualization tool to use and display the data generated by the physiology engine.

<img src="./Images/PulseExplorer-ParaView.png" width="365">
<center><em>
For more information on getting and using this tool, visit the Explorer [Wiki](https://gitlab.kitware.com/physiology/explorer/wikis/home)
</em></center>


## What kind of data can I get from the physiology engine?

Available data is defined within the engine in three major ways:
-	System data, such as %Cardiovascular, %Respiratory, etc.
	-	Analogous to system vitals
	  -	Examples: heart rate, oxygen consumption, mean arterial pressure, etc.
-	Compartment data
	-	Flow, pressure, and volume related to specific region of the body or component of equipment
	  - Examples: Cerebral Blood Flow, Right Lung Volume, Right Heart Pressure
	- Substance specific data related to a specific part of the body or component of equipment
	  -	Examples: The Extracellular concentration of succinylcholine in the brain tissue, anesthesia machine gas inlet oxygen volume fraction
-	Assessments
	-	Formed at the level of a clinician's report, Intended to mimic test results
	  -	Example: Pulmonary Function Test
    
## What are your models and how did you validate them?

The engine is a closed-loop whole body physiology model that combines physics-based lumped-parameter models 
and control system feedback mechanisms to model real-time system level 
physiologic behaviors. Lumped-parameter models use electrical circuit analogs 
to represent the major physiologic systems. 

Models/results are validated using a combination of peer-reviewed publications 
and subject matter expertise. The validation process includes:
- Defining key parameters for system validation
- Performing literature reviews to gather published data in the form of waveforms, and max, min, and mean values
- Using custom developed tools to compare data, perform analysis, and generate plots and tables of results

The primary purpose of model validation is to ensure that the model has an appropriate domain of validity 
given the goals of the modeling process. In the future, we plan to investigate sensitivity and uncertainty analyses to further quantify the validity of our models.
We would welcome and support, in as much as we are able, any validation or uncertainty quantification effort by the community.

We provide reports for each @ref SystemMethodology included in the physiology engine.
<br>  
These documents cover the design, implementation, assumptions, limitations, and validation of each model. 

#### Physiology Systems
@secreflist
 @refitem BloodChemistryMethodology "Blood Chemistry"
 @refitem CardiovascularMethodology "Cardiovascular"
 @refitem DrugsMethodology "Drugs"
 @refitem EndocrineMethodology "Endocrine"
 @refitem EnergyMethodology "Energy"
 @refitem EnvironmentMethodology "Environment"
 @refitem GastrointestinalMethodology "Gastrointestinal"
 @refitem NervousMethodology "Nervous"
 @refitem RenalMethodology "Renal"
 @refitem RespiratoryMethodology "Respiratory"
 @refitem TissueMethodology "Tissue"
@endsecreflist 
#### Equipment
@secreflist
 @refitem AnesthesiaMachineMethodology "Anesthesia Machine"
 @refitem InhalerMethodology "Inhaler"
@endsecreflist  
#### Modeling Support
@secreflist
 @refitem PatientMethodology "Patient Variability"
 @refitem CircuitMethodology "Circuits"
 @refitem SubstanceTransportMethodology "Substance Transport"
@endsecreflist 

## How do I work integrate the physiology engine into my application?

The engine has a modular architecture to reduce costs for applications that need a physiology engine and want to develop or extend a physiology model.

This architecture contains :
- A @ref CDM containing a library of classes and generic algorithms for lumped parameter physiology modeling 
- A standard @ref physeng for controlling a physiology engine via these CDM objects

We created a @ref SDK (SDK) to help developers integrate
the engine into software applications. This SDK provides
pre-built libraries and headers, as well as examples of how to programmatically
using the provided interfaces. The provided application programming
interfaces (APIs) provide full control over the engine to execute
various actions and retrieve a range of calculated physiological
outputs.

## How can I modify or extend the models in the physiology engine?

The engine uses an extensible architecture to promote integration with external
models with varying levels of fidelity. System-level model fidelity can be 
increased or decreased by adding or removing nodes and sub-circuits.

All integration/extension will require a custom build of our @ref SourceCode.
The @ref CDM provides a standard for data interchange between models. 
The deliberate identification of data requirements must precede any model modification or addition to determine 
if an extension of the Common Data Model is required. If the existing data model is sufficient to meet your modeling needs, 
you may be able to implement changes satisfactorily just by modifying the source code for the physiologic system 
of interest. If a Common Data Model extension is necessary, modification of the source code becomes more complicated. The 
quickest and easiest way to modify the engine to meet your needs is to work with Kitware - email: kitware@kitware.com.

We can help with requirements definition, provide development support, and/or make modifications for you.

#### How do I ensure my changes/model are good?

We include scenarios and their results for verification and validation. 
These results provide a baseline we can use to measure deviations to results when the code is modified.
As changes are implemented in the code base, we rerun all scenarios and compare the new results with baseline results to see how the implemented changes manifest in system data. 
Any new result that is over 2% error is marked as a failure. 
This data is used extensively to validate each system individually, as well as the combined effects of insults and interventions. See the Methodology Reports for more details.  
The scenarios output requests match the columns in the results file; we recommend that these scenarios remain unmodified.

## How can I contribute to the physiology engine?

Take a look at our <a href="https://gitlab.kitware.com/physiology/engine/blob/master/CONTRIBUTING.md">Contribution Guide</a>.
