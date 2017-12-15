Common Data Model and Software Framework {#CDM}
========================================

In order to support the many aspects of adding medical training content to simulation systems, we needed a dynamic architecture to help in the design, development, and use of physiologic models. 
A common architecture was designed to reduce model development time and increase usability by creating a modular, extensible platform for of physiologic models. 
Both the Common Data Model (CDM) and framework were designed to support computational physiology models in general by providing a standardized architecture and data interchange between physiology models and users.

##Common Data Model

The CDM is a specification of all the data and relationships associated with writing physiology simulation software.
It provides a well-defined data interchange format that disparate models can use for standardizing inputs and outputs, 
making it easy for physiology models and engines to be extended and operate jointly.
You can view @ref CDM Tables associated with some of key objects associated with the @ref physeng . 

In creating the CDM, we started by creating a conceptual data model to define and scope all of the definitions and relationships needed to simulate physiology. 
Next, we implemented logical data structures by iterating on the conceptual model with object oriented designs concepts in mind. 
This implementation was done in the Google Protocol Buffers specification. 
Protobufs provides a small, platform-neutral mechanism for efficient serialization of structured data and supports a wide range of languages, including C++, Java, Python, C# and JSON. 
Multi-language communication is necessary for communicating data between applications that use different languages. 
This was deemed a critical requirement for encouraging wide user adoption. 
Protobufs also support object oriented design style concepts, such as encapsulation, nesting, and packages. 
Protobufs inherently provide a way of defining lightweight data structures that are easily adapted to many common communication messaging protocols. 
By using protobufs, the CDM can easily be leveraged by a simulation in both a local and distributed data system (DDS) environment. 
The CDM provides a means of data interchange between models within a physiology engine, 
as well as between any application and a physiology engine; promoting a modular and extensible design of both physiology engines and their client applications.

The CDM is I/O indifferent; it provides the ability to hold all data associated regardless of the data being an input or an output to a specific model. 
These structures provide discrete properties for specific definitions and the flexibility to be easily expandable when incorporating new models. 
The CDM classes are small, lightweight property-bag objects intended to only contain data for simple I/O and message passing.
The property-bag design pattern consists of defining 'properties' an organizing them in 'bags'. 
The CDM has a base property class for defining properties and the bags are the simulation modeling objects themselves.

These classes are prefixed with SE, which stands for Synthetic %Environment. 

### Properties

An %SEProperty is an object that represents a basic data type in the CDM that stores the actual data. <br>
There are several Property data types:
- %SEScalar - A combination of a double and a unit. The CDM does not require a property in a specific unit of measure (for example, the height of a patient does not have to be in meters). 
Rather, the CDM requires each data type to retain a unit of measure of the Property's quantity and the class will translate the value to a requested unit. 
One example is a Distance Property that holds data in any distance-associated unit: meters, feet, inches, etc. 
- %Strings - We use the inherent language type for string
- %Enumeration - Where applicable, instead of strings, we use enumerations for code clarity and speed.
- %SEFunction - A combination of an abscissa and an ordinate paired together. 

### Modeling Objects

Modeling objects are hierarchically organized data containers based on the needs of physiology modeling and simulation. 
These objects contain data by holding specifically named property objects. 
They can also hold other modeling types to achieve the proper hierarchy of data organization. 
Since these objects do not contain the actual data values (they contain Properties) and optionally other modeling objects, their interface is based on a get/has style. 
When you call a get method (e.g., getVolume or getRightHeart) on an object, the requested object or property is returned (created on demand if it did not previously exist) (e.g., %SEScalarVolume or %SEHeart). 
The complementing has method (e.g., hasVolume or hasRightHeart) is a test to show if the object already exists or not. 

Modeling objects define the scope and data required for physiologic simulation with the following concepts:

#### Patient
The @ref PatientCreation "patient" data object contains the parameters used to define a patient, including age, sex, weight, height, and baseline heart rate and blood pressure. 
The majority of these parameters can be user-defined to provide patient variability across medical simulations. 
The patent data is then accessed by the physiologic models to accurately represent a specific patient. 

#### Conditions
@ref ConditionsInterface "Conditions" are persistent or recurring chronic conditions. 
They cause the body to enter an altered stabilized state, a level of homeostasis, that will alter the continual feedback mechanisms that take place in a healthy body. 
These condition types are typically defined by a severity scale in the CDM and physiologic systems alter their models accordingly. 
A few examples of chronic conditions are, anemia, chronic obstructive pulmonary disease, and renal stenosis.   

#### Actions
@ref ProcessActions "Actions" are the only means to introduce input into an initialized engine. 
Actions generally apply an acute traumatic event (e.g., hemorrhage or pneumothorax) or a treatment step (e.g., intravenous fluid and/or drug administration or needle decompression.) 
On introduction of an Action, a physiology engine can dynamically apply any changes to its models during its execution for real-time, dynamic physiologic responses.

#### Substances
A @ref SubstanceTable "substance" object is defined by a number of chemical and physical properties, including molar mass, density, and relative diffusion coefficient. 
Substances circulating in the system can include basic gases, such as oxygen, defined by a minimum number of parameters, and complex drug substances, such as succinylcholine that are defined with PK/PD properties. 
A list of active substances is maintained and the calculated substance parameters, such as plasma and tissue concentrations are stored on the substance object.

#### Systems
@ref SystemsInterface "System" objects contain the calculated output of a physiology engine. 
A system encapsulates the data needed to describe a specific physiology system, piece of medical equipment, or external environmental condition. 
They are also intended to be used as a means of data interchange between models within a physiology engine.

#### Compartments
A @ref CompartmentsInterface "compartment" is another way to get output from a physiology engine. 

A compartment can represent various fidelities of data; it can be:
  - An anatomical space, such as the body's skin
  - An organ, such as the liver
  - An organ substructure, such as the Left Heart
  - A component of a piece of equipment, such as an anesthesia machine ventilator
  
Compartments are intended to be a generic data exchange interface between systems for the physics-based dynamics data of the body, such as volumes, pressures, and flows.
In addition to the physics-based dynamics, compartments also contain a substance quality for each substance in the compartment. 
For example, a vascular compartment includes the masses and concentrations of all substances in that compartment, 
whereas a pulmonary compartment will contain the volumes and volume fractions of all substances in that compartment. 
This generic implementation allows any system to access and modify the parameters for the fluid dynamics calculations regardless of the model type. 

We have a implemented a compartment interface to integrate directly with the circuit CDM classes to easily access the circuit-based fluid dynamics data. 
These circuit compartments are assigned nodes and paths and combine that data to provide an accurate fluid dynamics data set for a specified compartment. 

The circuit compartment fluid dynamics data is combined in the following manner:
  - Volume : Sum of the volume of all nodes in the compartment.
  - Pressure : Pulled from a single node of a compartment that was explicitly identified during setup.
  - Flow : The sum of inflows; if the inflow equals zero, it is the sum of the outflows.
  - Vascular Substance Quantities
    - Mass - The sum of all the masses for each node in the compartment for a particular substance
    - Concentration - The compartment's substance mass divided by the compartment volume
  - Pulmonary Substance Quantities
    - Volume - The sum of all the volumes for each node in the compartment for a particular substance
    - Volume Fraction - The compartment's substance volume mass divided by the compartment volume

##Common Framework

The CDM is implemented as a set of classes built to reflect the organization of the data dictionary. 
These classes also leverage various other classes for data validation, manipulation, and translation algorithms provided by the framework.  
This library of algorithms provides application developers with low-level infrastructure (serialization, translation, data reuse, etc.) already complete so they can concentrate on creating end-user content-driven applications.

The following sections describe some of these algorithms.

### Unit Conversion

The Common Data Model has a unit conversion library built into the %SEScalar class that will convert double data to whatever unit you specify. 
There is an %SEScalar class for various quantity types along with commonly used unit definitions in those classes (such as SEScalarLength has units : m, cm, in, etc.) 
You may use strings or a %CCompoundUnit to define your unit if you do not find a unit predefined, but strings have a runtime cost to them. 
Units are defined in the standard abbreviation, as described at: http://www.bipm.org/en/si/. 
Along with SI units, English units and medical units are supported. 
You can check to see if a unit is valid by calling the IsValidUnit method on a particular quantity scalar class. 

### Serialization

All CDM classes have the ability serialize as defined by the Google Protobuf Specification.
This allows an engine to be able to serialize its entire state to disk and load it back at any time.
This ability is key in helping support diverse medical scenarios to create preconfigured engine states to support a wide variety of training options.

### Logging

The Data Model has a logging capability that each SE class uses to log any info to a log file.
This logger has different levels of logging an event:
- Debug - Extremely low level information, intended for the developer to assess any questions in functionality
- Info - A general level of information where the engine wants to inform a user of something
- Warning - Something was not inputted properly or an assumption was made in the underlying methodology
- Error - A recoverable error occurred and the engine is still able to proceed, but results should be inspected for correctness
- Fatal - A unrecoverable error occurred and the engine will stop calculating

The logger allows a user to programmatically add an object to the logging class that is called when 
a log event occurs. This allows a calling program to be notified so that they may react to these logs. (e.g., error handling)

### Data Track

A Data Track class is used for debugging purposes. 
Usually in debugging, one likes to print values of variables to the screen. 
This class allows a developer to write those values to a comma-delimited, time-ordered file. 
Developers can add any number of variables to track (only limited to machine memory) and they will be added to the output file for each time step.
  
### Circuit Solver

The @ref Circuit objects have algorithms for solving any closed-loop circuits as described in the @ref CircuitMethodology.

### Substance Transport

Substances are contained on compartments and are transported around the body based on volumes, pressures, and flows, which is handled via a generic @ref SubstanceTransportMethodology.

