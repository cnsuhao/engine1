ExtraFAQ {#ExtraFAQ}
============

## Why does it take so long to initialize the physiology engine?
The engine represents a single, @ref PatientMethodology "variable patient". 
Patient variability requires that the engine analyze the provided patient baseline values and stabilize the physiology to those values. 
This initialization can take several minutes, but once complete, the engine state can be saved to an xml file.
You can then load this state and instantaneously start execution of the simulation without any initialization time.
Please consult the example in the SDK for how to take advantage of this feature and eliminate any initialization time in your application.

## What is the fidelity of the physilogy engine?
One definition of fidelity is "The degree to which a model or simulation represents the state and 
behavior of a real world object or the perception of a real world object, feature, condition, or chosen 
standard in a measurable or perceivable manner; a measure of the realism of a model or simulation @cite msco . " 
The validation documentation (in the @ref SystemMethodology reports) describes how well the engine 
reproduces physiology at the system level. Like the human body, the engine is a self-compensating system of 
physiological systems with outcomes based on interventions @cite pettitt2009task , and therefore can be considered high-fidelity.

Sometimes the word fidelity is used to refer to the spatial (anatomical) level of resolution of a model. 
The engine is a closed loop 
total body physiology model that combines physics-based lumped parameter models 
and control system feedback mechanisms to model real-time system-level 
physiologic behaviors. Spatial resolution is limited by the lumped-parameter approach 
to sections of organs (what may arguably be referred to as the tissue level). However, the engine
uses an extensible architecture to promote integration with external models with varying levels of 
fidelity (resolution or granularity). For more details, please see the recorded [Committee on Credible Practice of Modeling & Simulation 
in Healthcare](https://simtk.org/projects/cpms/ "CPMS") webinar.

## Are there any publications related to the models that you have developed and choose to implement in the engine.
A list of publications and presentations about the engine can be found on the @ref published "Publications" page. 
Many of the physiology models in the engine are adapted or implemented directly from models described in literature. 
The implementation methodology is described in detail in the @ref SystemMethodology and sub-system documentation, and 
all of the source publications are cited in the methodology reports and listed in the Bibliography.

## What kind of uncertainty quantification do you do perform in your physiology model?
We have not performed a systematic forward propagation or inverse quantification of model uncertainty, 
nor do we have the resources to conduct a formal sensitivity analysis. However, we can quantify the numerical 
uncertainty introduced in solving the lumped-parameter fluid dynamics of the two foundation sub-models 
(@ref CardiovascularMethodology "Cardiovascular" and @ref RespiratoryMethodology "Respiratory"). The engine currently uses a bi-conjugate 
gradient method specific for sparse square systems (using the Eigen third party packages). This is an 
iterative method and we use the default tolerance for their solver, which is as close to zero as reasonable (around 1e-16). 

## Who is developing the physiology engine?
The community at large is contributing to the advancement of this version of the code, with oversight being provided by <a href="https://www.kitware.com/">Kitware, Inc.</a>.  

## Can I contact the physiology team to work on my current or upcoming project?
Absolutely. We always welcome new and challenging opportunities to 
work with research partners and sponsors. Please email us at physiology@kitware.com.

## What is the long-term plan for the physiology engine?
Our team's goal is to first and foremost develop the most advanced, 
open source, whole-body engine created to date. Following this,
our team plans to work with the user community and stakeholders to ensure 
the engine becomes the standard in physiology modeling.

During the first year of the project, our team made many important decisions 
regarding system architecture and the open source @ref License structure to ensure 
long-term use. Our system architecture was developed in a way that will make 
the system easy to extend for new models and external interfaces. The license 
structure allows for both open-source and proprietary applications to promote 
widespread use across government, military, academic, and commercial markets.

The engine team as a whole is very passionate about the use of simulated 
physiology for medical training and education. As such, we intend to develop 
and maintain a useful, high quality, open source application that will be 
extended and improved by our team and the community over time.

## Is the physiology engine a game?
No, it is a engine that can power immersive 
learning and serious games for medical training. The 
engine can provide a realistic training experience by producing real-time 
results to trauma and treatment. A physiology engine can enhance the user experience of applications 
by providing a comprehensive physiological response to insults and interventions.

## What are some possible physiology engine applications?
There is a wide range of potential applications, a few include:
- Powering serious games for medical education and training
- Producing responsive physiology in real time for manikin training
- Integrating a single-system model into the engine to understand full-body physiologic response
- Providing inputs and outputs for sensor systems
- Teaching and education
	
## Where do I log a bug for the physiology engine?
Logging bugs helps us improve the engine and we appreciate your 
feedback. You can report issues in <a href="https://gitlab.kitware.com/physiology/engine/issues">gitlab</a>.

## What is a Showcase Scenario?
A Showcase Scenario is a hypothetical patient scenario our team uses to 
demonstrate the Engine's patient customization, insult, intervention, 
and assessment capabilities. We have created four of these scenarios to provide a 
framework for discussion about the engine and serve as a catalyst for 
community-initiated improvements for the duration of the project.

These Showcase Scenarios are driven by the original goals of the project. 
It is important to note that Showcase Scenarios are not being used only as 
validation use cases, but also as examples to demonstrate the capabilities 
of the physics-based engine.

To see the scenario outputs from the engine, check out our interactive graphing 
tool on our website.

## What is your relationship with the Virtual Physiological Human (VPH) project.
The Virtual Physiological Human is a European initiative with the eventual goal of producing a complete 
mechanistic model of the entire human body. With the engine, we are trying to simulate whole-body physiology 
with reasonable accuracy for a target population. In other words, we are attempting to model a generic 
individual within a reference population to provide reasonable physiology for a variety of applications. 
In contrast, the eventual goal of the VPH project is individualized 
medical simulation. Individualized simulation is not within the initial scope of the project, 
but we have gained insight and generated knowledge of development processes, and we presented our findings 
to the VPH community at the 2016 conference @cite metoyer2016framework.

## What is the advantage of the Common Data Model (CDM)?
For details about the Common Data Model, please see our @ref CDM documentation.

## How fast does the physiology engine run? How can I make it faster?
The engine currently runs at about 5 to 10 times real time, depending on your machine's specifications. The functionality requirements of the multi-purpose physiology 
engine are driven by the goals of the project. If your application does not require all of the existing functionality, 
then you could strip features by modifying the source code in the same way that you would integrate a new model.

## Do you plan to provide support for interpreter-level model input, for example with the Python language?
We do not have any immediate plans to provide support for those languages. 
We do have support for Java. We are working towards creating a C# interface on top of our C++ interface.

