## What is the Pulse Physiology Engine?

The Pulse Physiology Engine is a C++ based, open source, multi-platform (Windows, Mac, and Linux), comprehensive human physiology
simulator that will drive medical education, research, and training technologies. 
The engine enables accurate and consistent physiology simulation across the medical community. 
The engine can be used as a standalone application or integrated with simulators, sensor interfaces, and models of all fidelities.

High-level objectives include:
-   Create a publicly available physiology research platform that
    enables accurate and consistent simulated physiology across training
    applications
-   Lower the barrier to create medical training content
-   Engage the community to develop and extend physiology models
-   Expand the body of knowledge regarding the use of simulated
    physiology for medical education
-   Meet the training needs of the military

## What is your relationship with %BioGears?
This physiology engine is a fork of the %BioGears project, version 6.1.1, began at Applied Research Associates, Inc. (ARA) 
with oversight from the Telemedicine and Advanced Technology Research Center (TATRC) under award W81XWH-13-2-0068. 

With the Pulse Physiology Engine we are addressing several limitations we uncovered with the BioGears Engine. We have established an public repository and issue tracker to encourage community collaboration and contribution, fixed licensing issues that ensure an Aphache 2.0 license, added complete cross-platform builds and support, increased our compiler support, added built in support for our verification test suite, and improved/streamlined the build process. 

The %BioGears original core technical team is now at Kitware and is leveraging the company's expertise in medical computing
and its history of maintaining and caring for open-source projects to further advance the engine and explore new avenues of research, such as pediatrics, patient-specific modeling and virtual surgery planning/rehearsal. We are working to create a stable environment for the engine
to encourage community collaboration and contribution through the public repository. The code base has diverged quickly from the %BioGears codebase to support these needs; however, we hope to continue collaborating with %BioGears to benefit both projects in the future.

## How do I get the physiology engine?

The physiology engine lives in a GitLab public repository <a href="https://gitlab.kitware.com/physiology/engine">here</a>.
	
## What can the physiology engine do?

An instance of an engine models a single patient's physiology.
- The patient is defined by parameters, such as height, weight, systolic and diastolic pressure.
- You can initialize the patient with specific chronic and/or disease states via conditions.
- You can modify the patients external environmental conditions (weather, submerge in water, etc.)
- You can apply various actions (acute insults/injuries, interventions, conscious breathing, exercise, etc.) to be applied to the patient.
- The patient can also interact with equipment models, such as an Anesthesia and/or an %ECG Machine as well as an %Inhaler via actions.
- You can integrate the engine into your applications.

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
- A @ref CDM containing set of classes and generic algorithms for lumped parameter physiology modeling 
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
quickest and easiest way to modify the engine to meet your needs is to work with Kitware - email: physiology@kitware.com.

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
