%Energy Methodology {#EnergyMethodology}
==========================

Overview
========

@anchor energy-abstract
Abstract
--------
The %Energy system provides a methodology for both thermal and metabolic regulation within the body. Heat transfer is modeled by a body thermal [circuit](@ref CircuitMethodology) that is connected to the [environment](@ref EnvironmentMethodology) circuit. A heat source at the core of the body circuit represents the metabolic heat production. In addition to generating heat, the dynamic metabolic rate is also used to compute the metabolic production and consumption rates of gases and other substances in the body. This system has been [validated](@ref energy-results) both under resting and dynamic conditions, such as exercise and external environment changes.

Introduction
------------
The %Energy system is responsible for simulating metabolism and regulating internal temperature. Metabolism is simulated through the consumption of nutrients in the tissues. Glucose and fat are the nutrients most readily used as an energy source for the human body. Oxygen is used to metabolize these nutrients during aerobic metabolism. After entering the pulmonary capillaries, oxygen is transported via the circulatory system and diffuses into the tissue where it is used in the aerobic reaction. The resulting by-product, carbon dioxide, diffuses out of tissue, traveling through the circulation before exiting the body through the pulmonary capillaries @cite guyton2006medical. Glucose can also be used to produce energy under anaerobic conditions, and lactate (lactic acid) is the resulting by-product. The lactate enters the circulation and can be reconverted to glucose via gluconeogenesis in the liver and kidneys. During periods of prolonged starvation, the liver produces ketoacids. Acetoacetate is the predominant ketone synthesized. After it is produced, acetoacetate may be used as an energy source for the brain, myocardium, and muscle @cite gropper2013nutrition. 

The body's temperature is well-regulated. Core temperature regulation can be achieved by varying heat production (e.g. shivering) or heat exchange (e.g. sweating). In the engine, variations in the external environment or physical activity can lead to changes in the core temperature, triggering thermal feedback. Examples of thermal feedback during shifts in core temperature are sweating and shivering. Sweating is initiated if the core temperature is too high @cite herman2007physics. The increased evaporation of water from the surface of the skin leads to an increase in heat transferred out of the body. Changes in core temperature directly affect other systems. For example, a low core temperature causes blood flow to be shunted away from the skin, resulting in less heat transfer from the core to the skin @cite guyton2006medical. These feedback mechanisms are used to maintain thermal homeostasis in a variety of environmental conditions.

@anchor energy-system-design
System Design
=============

Background and Scope
--------------------

### Requirements
The energy system is required to simulate the effects of exercise and elevated physical activity as well as react to temperature and pressure changes in the environment.

### Approach
The %Energy system is a physical model of heat transfer combined with a collection of empirical equations for heat production and exchange obtained from literature. Additional equations are derived from stoichiometric relationships and empirical data found in the literature, particularly the governing equations for the metabolic [production and consumption](@ref tissue-metabolic-production) of substances. It uses a thermal circuit to simulate heat transfer through the body, with the body circuit connected to the [environment](@ref EnvironmentMethodology) circuit. The body thermal circuit consists of a core node, representing core temperature, and a skin node, which represents the lumped peripheral temperature. The body thermal circuit is shown in Figure 1.

<img src="./Images/Energy/internalThermal.png" width="400">
<center>
*Figure 1. The body thermal circuit consists of two nodes and four paths. Two additional paths exist, connecting to the environment thermal circuit. The circuit is used to model the dynamic core and skin temperatures.*
</center><br>

The path elements consist of an internal heat flow source, a core heat capacitance, a skin heat capacitance, and a variable resistor from the core to skin. These four elements represent metabolic heat generation, the discretized heat capacity of the human body, and the convective heat transfer due to blood flow. The heat capacities of the core and skin are computed by proportioning the mass-averaged heat capacity found in literature based on the mass fraction of the skin @cite herman2007physics. The variable core to skin resistance is computed dynamically during simulation, and is inversely proportional to the skin blood flow. A decrease in blood flow leads to an increase in heat transfer resistance, and vice versa. When connected to the [environment](@ref EnvironmentMethodology) thermal circuit, the core and skin temperatures dynamically react to the environmental conditions (e.g. temperature, pressure, and humidity).

The [metabolic production and consumption](@ref tissue-metabolic-production) of the %Energy system is a set of calculations that determine the rate of change of substances (nutrients, ions, gases) in the tissue, relying on [advective](@ref CircuitMethodology) and [diffusive](@ref TissueMethodology) transport methodologies.

### Thermal Regulation
Thermal regulation in the %Energy system occurs through manipulation of the metabolic rate or through external losses (sweating). The thermal feedback mechanisms are a direct implementation from those discussed by Herman @cite herman2007physics. For high core temperature, a control equation specifies the sweat rate as a function of the difference between the current core temperature and the set-point (Equation 1). Sweat is removed from the body via a path connected between the skin and the environment (Figure 2). Note that sweat is currently composed of water only, a known limitation which will be addressed in the [future](@ref energy-future).

<img src="./Images/Energy/sweat.png" width="400">
<center>
*Figure 2. Sweat is removed from the body via a flow source path connected to ground. The flow source rate is computed using Equation 1.*
</center><br>

\f[ \dot{m}_{sweat} = \frac{h_{sweat} \left(T_{core} - T_{core,setpoint} \right)}{\rho_{sweat}} \f]
<center>
*Equation 1.*
</center><br>

For severe increases in core temperature (hyperthermia), the rate of chemical reactions can increase, leading to a subsequent rise in metabolic rate. This value was quantified from Pate et al. @cite pate2001thermal as an eleven percent increase in metabolic rate for every degree increase in core temperature. This is described from the power relationship between metabolic rate and core temperature, shown in Equation 2.

\f[ \dot{Q}^{n+1}_{metabolic} = \dot{Q}^{n}_{metabolic} * \left(1.11 \right)^{T_{core}-T_{core,high}} \f]
<center>
*Equation 2.*
</center><br>

For low core temperatures, the maximum metabolic rate achievable through shivering is defined from the summit metabolism. This value is given by Herman as:

\f[ \dot{Q}_{metabolic} = 21.0m^{0.75}_{b} \f]
<center>
*Equation 3.*
</center><br>

If the summit metabolism is not enough to adequately maintain internal temperature, then the metabolic rate will begin to decrease at a rate of six percent for every degree drop @cite mallet2002hypothermia. The power relationship in Equation 4 is used to describe this phenomenon.

\f[ \dot{Q}^{n+1}_{metabolic} = \dot{Q}^{n}_{metabolic} * \left(0.96 \right)^{T_{core,low}-T_{core}} \f]
<center>
*Equation 4.*
</center><br>

Under resting conditions, the metabolic rate is determined from the Harris-Benedict formula. This formula gives the metabolic requirements in kilo-calories per day as a function of weight, height, age, and sex @cite roza1984metabolic . This empirical formula is shown in Equation 5.

<center>
<table border="0">
<tr>
<td> Men: </td> <td> \f[ \dot{Q}_{metabolic} = 88.632 + 13.397*m_{b} + 4.799*H - 5.677*A \f] </td>
</tr>
<tr>
<td> Women: </td> <td> \f[ \dot{Q}_{metabolic} = 447.593 + 9.247*m_{b} + 3.098*H - 4.330*A \f] </td>
</tr>
</table>
</center>
<center>
*Equation 5.*
</center><br>

@anchor energy-data-flow
Data Flow
---------
The %Energy System determines its state at every timestep through a three-step process: Preprocess, Process, and Postprocess. In general, Preprocess determines the circuit element values based on feedback mechanisms and engine settings/actions. Process uses the generic circuit calculator to compute the entire state of the circuit and fill in all pertinent values. Postprocess is used to advance time.

### Preprocess
#### Calculate Metabolic Heat Generation
The metabolic rate is dictated by the current state of the core temperature. This function includes states of increased metabolic rate due to shivering or severe hyperthermia. Additionally, an extreme drop in core temperature leads to decreasing metabolic rate. If the core temperature does not meet any of the criteria for increases/decreases, the metabolic rate will be calculated as the basal metabolic rate.

#### Calculate Sweat Rate
The sweat rate is calculated from a core temperature control function. The mass lost due to sweating is accounted for, and a flow source from the skin extravascular to ground path is updated to ensure fluid loss.

#### Update Heat Resistance 
The variable core to skin heat transfer resistance is updated according to the inverse of the skin blood flow. 

#### Exercise
The exercise function adds to the body&rsquo;s basal metabolic rate a value that is specified by the exercise action. The metabolic rate set-point is specified by the action but limited by the amount of energy available. The energy limit is computed, and the actual metabolic rate is ramped to the limited set-point. The body's actual work rate as a fraction of the total possible work rate and the body's actual work rate as a fraction of the action-requested work rate are set in this method.

### Process

#### Process Temperature Circuit
The generic circuit methodology developed for the engine is used to solve for the temperature and heat transfer rate at each node or path. For more details, see @ref CircuitMethodology.

#### Calculate Vital Signs
The core and skin temperatures are recorded in this function. In addition, the current metabolic state of the patient may trigger the following [events](@ref energy-events): hypothermia, hyperthermia, dehydration, fasciculation, or fatigue. These events are only triggered if the current state falls within the criteria of the specific event.

### Postprocess
The Postprocess step moves everything calculated in Process from the next timestep calculation to the current timestep calculation. This allows all other systems access to the information when completing their preprocess analysis for the next timestep.

<br>
<img src="./Images/Energy/EnergyDataFlow.png" width="900">
<center>
<i>Figure 3. The data flow for the %Energy System consists of Preprocess, Process, and Postprocess. Preprocess determines the circuit element values based on feedback mechanisms engine actions. Process uses the generic @ref CircuitMethodology to solve the temperature circuit for temperatures and heat transfer rates. Postprocess updates these quantities to the next time step and then begins advancing time, which causes the loop to repeat.</i>
</center><br>

@anchor energy-features
Features, Capabilities, and Dependencies
----------------------------------------
The %Energy system is connected with every other system. %Energy directly affects the %Cardiovascular System through modification of vascular tone, heart rate, and heart contractility. This leads to modifications in the cardiac output and flow distribution in the cardiovascular circuit. In addition, there is indirect feedback through the modification of oxygen consumption and carbon dioxide production. Increased carbon dioxide production can lead to higher arterial carbon dioxide, which, in the case of severe hypercapnia, causes an %Endocrine response in the form of epinephrine and norepinephrine release. There is direct feedback on the %Respiratory system via modification of the ventilation frequency and driver pressure. The previously mentioned oxygen consumption and carbon dioxide production changes indirectly based on feedback to %Respiratory driver, which is dependent on the arterial carbon dioxide and arterial oxygen. There is a dependence on the %Gastrointestinal and %Renal systems since they are the methods by which nutrients enter the body and metabolic wastes are cleared from the body.

The %Environment circuit is directly connected to the energy&rsquo;s internal temperature circuit to form the total temperature circuit. Modifications on the metabolic rate will therefore have a direct feedback on the environment temperature circuit, while changes in the ambient environment temperature will have a direct feedback on the metabolic rate.

Additional dependence on the cardiovascular system comes from the extravascular to vascular connection. The cardiovascular circuit is connected to the extravascular circuit via singular paths from the tissue-equivalent vascular node to the tissue node. These singular paths are formed by a flow resistance and contain a compliance which stores the extravascular volume.

@anchor energy-variability
### Patient Variability
The basal metabolic rate is computed from the sex, height, weight, and age of the patient using the Harris-Benedict formula and will be directly affected by patient variability. Other indirect effects, such as fluid compositional changes due to sweating, may be observed. As with all of the systems, the energy system is validated using the Standard Male patient. A detailed discussion of patient variability is available in the @ref PatientMethodology report.

@anchor energy-assumptions
Assumptions and Limitations
---------------------------
The %Energy system assumes a bulk representation of all of its metabolic substances to avoid tracking all possible biochemical reactants and products. It assumes that all carbohydrates are stored in the tissue as glucose. Glycogen stores are not considered since the bulk representation of carbohydrates is glucose. A similar assumption is made for lipids. The bulk representation of all lipids is tristearin. It is not converted into its fatty acid constituents in the blood stream. This assumption is carried through to ketones. All ketones are assumed to be acetoacetate. It is assumed that all of these substances move with the flow into and out of the extravascular space.

@anchor energy-actions
Actions
-------
@anchor energy-exercise
### Exercise
The exercise action is initiated by specifying the exercise intensity. The exercise intensity is a number between 0 and 1 that defines the requested fraction of the body's maximal work rate. For instance, the average adult male has a maximal work rate of approximately 1200 Watts @cite hall2011guyton; therefore, a user-specified exercise intensity of 0.5 would request a work rate of 600 Watts from the body. Table 1 shows the approximate exercise intensity for some common activities executed by an average adult male. The approximate mechanical power produced by an adult male is also included in the table.

<br><center>
*Table 1. The approximate exercise intensity for some common activities and the corresponding approximate mechanical power. Note that the values in the table correspond to a body with a 1200 Watt maximum work rate capability.*
</center>
|Activity |Exerise Intensity | Mechanical Power (W) |
|-------- |----------------- |--------------------- |
|All muscles in the body working all-out @cite hall2011guyton                                |1.0  |1200 |
|All-out cycling with resistance, sustainable for approx. 8 seconds @cite billaut2003maximal |0.8  |1000 |
|Rowing 6.1 m/s on an ergometer @cite concept2016concept                                     |0.54 |650  |
|Running at about 7.1 m/s (16 mph) @cite johnson2000exercise                                 |0.36 |430  |
|'Typical' Level Cycling @cite herman2007physics                                             |0.1  |120  |
|Jogging at about 2.2 m/s (5 mph) @cite johnson2000exercise                                  |0.06 |70   |
|Rest  |0.0 |0 |

The exercise capacity of the body is physiologically and psychologically limited @cite noakes2012fatigue. The amount of work produced by the exercise action is limited by the fatigue model; however, this limitation is purely physiologic. Fatigue is modeled as a system of interconnected energy storage compartments, as shown in Figure 4.

<center>
@image html fatigue.png
*Figure 4. The fatigue compartment model. The energy stores are represented by the blue buckets. The solid lines  show the energy flow pathways, and flow directions are indicated by the arrowheads. The dashed line is a future information pathway to control the endurance energy store fill rate. The amount of energy in each store is computed using equations 7 and 8. The energy flow rates through each path, labeled %Energy Path 1 through 7 in the figure, are  computed using equations 9 to 18. The refill rate of the endurance energy store is computed using equation 19. The outflow of energy from the usable energy store is only non-zero when the activity level of the body is above zero, and it is computed directly from the total work rate.*
</center><br>

The energy available for work is found/stored in the
usable energy compartment. There are two anaerobic compartments and one aerobic compartment that replenish the usable energy compartment. The peak power
compartment is analogous to the phosphagen system, the medium power compartment is analogous to the glygogen-lactic acid system, and 
the endurance compartment can be though of as the aerobic energy system. The amount of energy in each compartment is calculated by adding the change in energy 
to the current energy level at each timestep, as shown in Equation 7, where *E* is the level of energy in the store. 
The compartment energy levels are bounded between zero and the maximum capacity.

\f[E(t + \Delta t) = E(t) + \frac{dE}{dt} \Delta t \f]
<center>
<i>Equation 7.</i>
</center><br>

The change in energy is computed by summing the energy flow rates, as shown in Equation 8, where *F<sub>E,in</sub>* and *F<sub>E,out</sub>* are 
the energy flow through the paths leading into and out of the stores, respectively.

\f[ \frac{dE}{dt} = \Sigma \left(F_{E,in} \right) - \Sigma \left(F_{E,out} \right) \f]
<center>
<i>Equation 8.</i>
</center><br>

With the exception of the usable energy store, all of the outflow rates are proportional to the energy deficit in the downstream compartment. The usable compartment outflow rate is the work rate. The peak and medium power compartment inflow rates are determined by two split factors. The first split factor determines the amount of endurance energy that is being directed to usable energy, and the second determines how much of the remaining energy goes to filling the peak and medium stores. The split factors are computed from the deficits in the energy compartments. In other words, all energy replenishment is based on the current needs. The energy flow rate governing equations are shown in Equations 9 to 18, where *F<sub>i</sub>* is the energy flow rate through energy path i, *S* is a split fraction between 0 and 1, *N<sub>store</sub>* is the deficit in a store normalized to the maximum level in that store, and *M<sub>store</sub>* is a piecewise linear map for the store deficit normalizations. The purpose of the piecewise function is to allow purely aerobic energy use at low exercise rates. The energy paths are labeled in Figure 4, and the direction of energy flow is indicated by the arrows. The rates are bound at the upper limit by a proportion of the maximum work rate where the maximum work rate is 1 times the maximum endurance rate  plus 2.5 times the maximum endurance rate (the maximum medium power rate) plus 4 times the maximum endurance rate (the maximum peak power rate). These limits are chosen to mimic the maximum aerobic, glycogen-lactic acid, and phosphogen to ATP conversion rates @cite hall2011guyton. Rates are bound at the lower limit by zero.

<center>
\f[ F_{1} = \left(N_{Usable} + N_{Peak} + N_{Medium} \right) F_{1,max} \f]
<i>Equation 9.</i>

\f[ F_{2} = S_{1} F_{1} \f]
<i>Equation 10.</i>

\f[ F_{3} = (1-S_{1}) F_{1} \f]
<i>Equation 11.</i>

\f[ S_{1} = \frac{N_{Usable}}{N_{Usable} + 0.5 * \left(N_{Medium} + N_{Peak} \right)} \f]
<i>Equation 12.</i>

\f[ F_{4} = S_{2} F_{3} \f]
<i>Equation 13.</i>

\f[ F_{5} = (1-S_{2}) F_{3} \f]
<i>Equation 14.</i>

\f[ S_{2} = \frac{N_{Peak}}{N_{Peak} + N_{Medium}} \f]
<i>Equation 15.</i>

\f[ F_{6} = M_{Usable} N_{Usable} F_{6,max} \f]
<i>Equation 16.</i>

\f[ F_{7} = M_{Usable} N_{Usable} F_{7,max} \f]
<i>Equation 17.</i>

\f[ M_{Usable} = \left\{ \begin{array}{ll} N_{Usable} \leq 0.8333 & 0 \\ N_{Usable} > 0.8333 & 6*N_{Usable} - 5 \\ \end{array} \right. \f]
<i>Equation 18.</i>
</center><br>

The energy flow rate into the endurance energy store, indicated by the large orange arrow in Figure 4, is independent of bloodborne substances in the current release; however, this rate will be coupled to the nutrient substance concentrations in the blood in a future release. Equation 19 shows the endurance fill rate, where *k<sub>endurance</sub>* is a constant and *N<sub>Total</sub>* is the sum of the normalized store deficits.

<center>
\f[ F_{Endurance} = k_{Endurance} * N_{Total} \f]
<i>Equation 19.</i>
</center><br>

There are three output parameters associated with the exercise action: the achieved exercise level, the fatigue level, and the total work rate level.
- **Achieved exercise level**: This is the fraction of requested work that the body is able to achieve. For instance, if a work rate of 300 Watts is requested and the body is able to deliver 300 Watts, then the achieved exercise level will be 1.0. After some time, the body's energy levels will be depleted, and it will only be able to produce a fraction of the requested work rate, so the achieved exercise level will be less than 1.0.
- **Fatigue level**: This is the exhaustion level of the body. A fatigue level of 1.0 indicates that the body has no energy available to do work. At low work rates the fatigue level increases slowly, and the rate of fatigue increase is related to type of metabolism producing the energy (i.e. aerobic or anaerobic).
- **Total work rate level**: This is the fraction of the full work rate capacity of the body at which the body is currently working. For example, if the rested body is capable of producing a maximum of 1200 Watts of power for some amount of time, then that body working a rate of 600 Watts would have a work rate level of 0.5. This output is similar to the exercise intensity input.

@anchor energy-conditions
Conditions
----------
** Please note that the Starvation and Dehydration conditions are temporarily disabled.**

### Starvation
**The starvation condition is disabled in the current release. An improved starvation condition will be included with the next release.**
The starvation functionality simulates an extended time period without nutrient intake. This is accomplished by assuming a coarse timestep over which numerous mechanisms lead to the decay of nutrients in the body. With regards to the %Energy system, metabolic consumption calculations are carried out over the interval of the coarse timestep. This leads to a large decrement of vital nutrients in the tissues and increment of waste by-products at the beginning of condition stabilization. Other systems handle starvation in a similar manner. %Renal and systemic clearance volumes are calculated over the coarse timestep, and the resulting decrement in substances is distributed based on volume across all vascular and tissue compartments. For more information on renal and systemic clearance, see @ref RenalMethodology and @ref DrugsMethodology.

### Dehydration
**The dehydration condition is disabled in the current release. An improved dehydration condition will be included with the next release.**
Dehydration functionality is simulated completely in the %Energy system. Similar to starvation, dehydration assumes a coarse timestep over which the fluid loss would occur. According to the Journal of Sports Medicine and Physical Fitness @cite shirreffs2000hydration , the average loss rate on the first day without liquid intake is 2600 milliliters. This rate decreases to 1600 milliliters for each subsequent day. The %Energy system uses these average rates and the time since last liquid consumption to calculate volume lost. The volume decrement is distributed via volume weighting instantaneously to all vascular and tissue compartments. 

@anchor energy-events
Events
------
### Hypothermia
Hypothermia is defined as a decrease in core temperature below 35 degrees Celsius @cite mallet2002hypothermia. In the engine, this is triggered due to changes in the external environment, leading to increased heat transfer off the skin surface.

### Hyperthermia
Hyperthermia is defined as an increase in core temperature above 38.8 degrees Celsius @cite mallet2002hypothermia . This may result from vigorous exercise, harsh environments, or infection. In the engine, this event is achievable through the exercise action or by specifying a high-temperature environment.

### Dehydration
Dehydration is classified by the World Health Organization as a three percent decrease in patient body mass due to fluid loss @cite who2005dehydration. This is tested by summing the total fluid mass on the cardiovascular and extravascular circuits at each timestep. Currently, this event can be triggered during a hemorrhage action or through prolonged exercise.

### Fatigue
The fatigue event is triggered by any depletion of the energy stores, and it is removed when the energy stores are at capacity. Note that fatigue is only triggered by above-basal metabolic energy production. A fatigue event indicates that the skeletal muscle of the body has been active.

### Fasciculation
Fasciculation is involuntary twitching of the skeletal muscle. This can be caused from a variety of conditions, such as mineral deficiency or stimulant use. In the engine, the criteria for the fasciculation event is calcium deficiency. If the patient&rsquo;s arterial calcium concentration falls below one milligram per deciliter, then fasciculation is triggered @cite gropper2013nutrition. 

@anchor energy-results
Results and Conclusions
=======================

Validation - Resting Physiologic State
--------------------------------------
<br><center>
*Table 2. The %Energy system properties consist of core and skin temperature, as well as metabolic production rates. The properties show good agreement with the validation values.*
</center>
@insert ./test_results/tables/EnergyValidationTable.md

The resting system properties for the energy system are temperatures and metabolic production rates. From Table 2, it is shown that the temperatures meet the validation criteria extremely well for resting conditions. The production rates show reasonable agreement with the validation data. Gas consumption and production yield the largest disparity. This is due to accurate resting physiology being achieved for the displayed consumption and production rates. Additional refinement of the gas consumption and production rates can occur, but the change would propagate through the other systems. In order to preserve accurate resting physiology all other systems would need to be adjusted for this change. This is currently planned for a future release. The remaining metabolic production rates show good agreement with the validation data.

Validation - Actions and Conditions
--------------------
The %Energy and %Environment systems were validated for four scenarios encompassing four different actions. These include: exercise, cold water submersion (including active heating), and a high altitude environment change. These scenarios were meant to test the dynamic feedback of the energy environment systems on both thermal regulation and internal physiology. There is good agreement with the expected results.

<center>
*Table 3. The dynamic response from the %Energy and %Environment systems were validated for four scenarios: Two Exercise scenarios, Cold Water Submersion, and High Altitude. The scenarios demonstrate a good response to exercise and environmental conditions.*
</center>
|	Scenario 	|	Description	|	Good	|	Decent	|	Bad	|
|	---	|	---	|	---	|	---	|	---	|
|	ColdWaterSubmersion	|	Patient is submerged in 10 C water for 1 hour. Removed for 10 minutes, and then actively heated for 20 minutes	|<span class="success">	11	</span>|<span class="warning">	12	</span>|<span class="danger">	1	</span>|
|	HighAltitude	|	Patient enters 4000 m elevation environment for 15 minutes	|<span class="success">	1	</span>|<span class="warning">	0	</span>|<span class="danger">	5	</span>|
|	ExerciseStages	|	Exercise for six minutes at increasing intensity with 2 minutes of rest in between stages.	|<span class="success">	76	</span>|<span class="warning">	3	</span>|<span class="danger">	33	</span>|
|	ExerciseVO2max	|	Exercise at high intensity (430 watts) to exhaustion.	|<span class="success">	1	</span>|<span class="warning">	0	</span>|<span class="danger">	0	</span>|
|		|	Total	|<span class="success">	89	</span>|<span class="warning">	15	</span>|<span class="danger">	39	</span>|

@anchor energy-exercise-validation
### Exercise
There are two scenarios for validation of the exercise action. The first scenario qualitatively validates that a work rate threshold exists. The scenario is based on the assertion by @cite johnson2000exercise that a body working around the threshold for maximal oxygen uptake (approximately 430 watts) will only be able to perform at the desired level for about three minutes before reaching physiological limits. The second scenario takes advantage of the abundance of experiments using variations of the Bruce protocol to study exercise physiology. In the second scenario, the exercise intensity is periodically increased, with short breaks in between each exercise period. The quantitative validation results are shown in the table below.

<center><br>
*Table 4a. The dynamic response to exercise. 15 measures are compared to data reported in literature at 8 different times during increasing exercise intensity with intermittent rest, for a total of 120 points of comparison. Of those, 86 were within 10 percent of the reported value, 8 were within 30 percent, and 26 deviated from the expected value by more than 30 percent. The first intensity/rest period is shown in Table 4a.*
</center>
|	Segment	|	Notes	|	Occurrence Time (s)	|	Sampled Scenario Time (s)	|	Core Temperature (Celsius)	|	Peripheral Temperature (Celsius)	|	Heart Rate (beats/min)	|	Systolic Pressure (mmHg)	|	Diastolic Pressure (mmHg)	|	Mean Arterial Pressure (mmHg)	|	Stroke Volume (mL)	|	Cardiac Output (L/min)	|	Gut Blood Flow (L/min)	|	Systemic Vascular Resistance (mmHg-min/L)	|	Respiration Rate (breaths/min)	|	Tidal Volume (L)	|	Respiratory Exchange Ratio	|	Oxygen Consumption (L/min)	|	Urine Production Rate (mL/min)	|
|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|
|	Exercise Severity 0.0375	|	45 watts	|	30	|	389	|<span class="success">	Increase @cite christie1987cardiac, @cite byrne2007ingestible	</span>|<span class="success">	No change or decrease @cite griffin1993temperature	</span>|<span class="danger">	156% of baseline @cite christie1987cardiac	</span>|<span class="danger">	Increase 18.4% @cite christie1987cardiac	</span>|<span class="danger">	No change @cite christie1987cardiac	</span>|<span class="success">	1% increase  @cite christie1987cardiac	</span>|<span class="danger">	41.6% increase  @cite christie1987cardiac	</span>|<span class="danger">	225% of base  @cite christie1987cardiac	</span>|<span class="danger">	reduced  @cite perko1998gutflow	</span>|<span class="success">	decrease  @cite perko1998gutflow	</span>|<span class="success">	Increase  @cite guenette2007respiratory	</span>|<span class="success">	increase  @cite guenette2007respiratory	</span>|<span class="success">	increase, maximum  ~1.21  @cite koutlianos2013indirect	</span>|<span class="danger">	1.33  @cite christie1987cardiac	</span>|<span class="danger">	decrease  @cite melin2001comparison	</span>|
|	Exercise Severity 0	|	rest 2 minutes	|	390	|	509	|<span class="success">	Increase @cite christie1987cardiac or no change @cite byrne2007ingestible	</span>|<span class="success">	No change or decrease @cite griffin1993temperature	</span>|<span class="success">	Decreasing [Sensus Communis]	</span>|<span class="success">	Toward baseline @cite christie1987cardiac	</span>|<span class="success">	No change @cite christie1987cardiac	</span>|<span class="success">	Toward baseline @cite christie1987cardiac	</span>|<span class="success">	Toward baseline @cite christie1987cardiac	</span>|<span class="success">	Toward baseline @cite christie1987cardiac	</span>|<span class="success">	Toward baseline @cite christie1987cardiac	</span>|<span class="success">	Toward baseline @cite christie1987cardiac	</span>|<span class="success">	Toward baseline @cite christie1987cardiac	</span>|<span class="success">	Toward baseline @cite christie1987cardiac	</span>|	No Data	|<span class="success">	Toward baseline @cite christie1987cardiac	</span>|	No Data	|
<center><br>

*Table 4b. The second intensity/rest period.*
</center>
|	Segment	|	Notes	|	Occurrence Time (s)	|	Sampled Scenario Time (s)	|	Core Temperature (Celsius)	|	Peripheral Temperature (Celsius)	|	Heart Rate (beats/min)	|	Systolic Pressure (mmHg)	|	Diastolic Pressure (mmHg)	|	Mean Arterial Pressure (mmHg)	|	Stroke Volume (mL)	|	Cardiac Output (L/min)	|	Gut Blood Flow (L/min)	|	Systemic Vascular Resistance (mmHg-min/L)	|	Respiration Rate (breaths/min)	|	Tidal Volume (L)	|	Exchange Ratio (Or Respiratory Quotient)	|	Oxygen Consumption (L/min)	|	Urine Production Rate (mL/min)	|
|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|
|	Exercise Severity 0.075	|	90 watts	|	510	|	869	|<span class="success">	Increase @cite christie1987cardiac, @cite byrne2007ingestible	</span>|<span class="success">	No change or decrease @cite griffin1993temperature	</span>|<span class="danger">	197% of baseline @cite christie1987cardiac	</span>|<span class="danger">	34.4% increase @cite christie1987cardiac	</span>|<span class="danger">	No change @cite christie1987cardiac	</span>|<span class="success">	8.38% increase  @cite christie1987cardiac	</span>|<span class="danger">	29.9% increase  @cite christie1987cardiac	</span>|<span class="danger">	267% of base  @cite christie1987cardiac	</span>|<span class="danger">	reduced  @cite perko1998gutflow	</span>|<span class="success">	decrease  @cite perko1998gutflow	</span>|<span class="success">	Increase  @cite guenette2007respiratory	</span>|<span class="success">	increase  @cite guenette2007respiratory	</span>|<span class="success">	increase, maximum  ~1.21  @cite koutlianos2013indirect	</span>|<span class="danger">	2.05  @cite christie1987cardiac	</span>|<span class="danger">	decrease  @cite melin2001comparison	</span>|
|	Exercise Severity 0	|	rest 2 minutes	|	870	|	989	|<span class="success">	Increase @cite christie1987cardiac or no change @cite byrne2007ingestible	</span>|<span class="success">	No change or decrease @cite griffin1993temperature	</span>|<span class="success">	Decreasing [Sensus Communis]	</span>|<span class="success">	Toward baseline @cite christie1987cardiac	</span>|<span class="success">	No change @cite christie1987cardiac	</span>|<span class="success">	Toward baseline @cite christie1987cardiac	</span>|<span class="success">	Toward baseline @cite christie1987cardiac	</span>|<span class="success">	Toward baseline @cite christie1987cardiac	</span>|<span class="success">	Toward baseline @cite christie1987cardiac	</span>|<span class="success">	Toward baseline @cite christie1987cardiac	</span>|<span class="success">	Toward baseline @cite christie1987cardiac	</span>|<span class="success">	Toward baseline @cite christie1987cardiac	</span>|	No Data	|<span class="success">	Toward baseline @cite christie1987cardiac	</span>|	No Data	|
<center><br>

*Table 4c. The third intensity/rest period.*
</center>
|	Segment	|	Notes	|	Occurrence Time (s)	|	Sampled Scenario Time (s)	|	Core Temperature (Celsius)	|	Peripheral Temperature (Celsius)	|	Heart Rate (beats/min)	|	Systolic Pressure (mmHg)	|	Diastolic Pressure (mmHg)	|	Mean Arterial Pressure (mmHg)	|	Stroke Volume (mL)	|	Cardiac Output (L/min)	|	Gut Blood Flow (L/min)	|	Systemic Vascular Resistance (mmHg-min/L)	|	Respiration Rate (breaths/min)	|	Tidal Volume (L)	|	Exchange Ratio (Or Respiratory Quotient)	|	Oxygen Consumption (L/min)	|	Urine Production Rate (mL/min)	|
|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|
|	Exercise Severity 0.1583	|	190 W	|	990	|	1349	|<span class="success">	Increase @cite christie1987cardiac, @cite byrne2007ingestible	</span>|<span class="success">	No change or decrease @cite griffin1993temperature	</span>|<span class="warning">	237% of baseline @cite christie1987cardiac	</span>|<span class="danger">	46.4% increase @cite christie1987cardiac	</span>|<span class="danger">	No change @cite christie1987cardiac	</span>|<span class="warning">	14.1% increase  @cite christie1987cardiac	</span>|<span class="danger">	36.4% increase  @cite christie1987cardiac	</span>|<span class="danger">	336% of base  @cite christie1987cardiac	</span>|<span class="danger">	reduced 25-50%  @cite perko1998gutflow	</span>|<span class="success">	decrease  @cite perko1998gutflow	</span>|<span class="success">	Increase  @cite guenette2007respiratory	</span>|<span class="success">	increase  @cite guenette2007respiratory	</span>|<span class="success">	increase, maximum  ~1.21  @cite koutlianos2013indirect	</span>|<span class="danger">	2.75  @cite christie1987cardiac	</span>|<span class="danger">	decrease  @cite melin2001comparison	</span>|
|	Exercise Severity 0	|	rest 2 minutes	|	1350	|	1469	|<span class="success">	Increase @cite christie1987cardiac or no change @cite byrne2007ingestible	</span>|<span class="success">	No change or decrease @cite griffin1993temperature	</span>|<span class="success">	Decreasing [Sensus Communis]	</span>|<span class="success">	Toward baseline @cite christie1987cardiac	</span>|<span class="success">	No change @cite christie1987cardiac	</span>|<span class="success">	Toward baseline @cite christie1987cardiac	</span>|<span class="success">	Toward baseline @cite christie1987cardiac	</span>|<span class="success">	Toward baseline @cite christie1987cardiac	</span>|<span class="success">	Toward baseline @cite christie1987cardiac	</span>|<span class="success">	Toward baseline @cite christie1987cardiac	</span>|<span class="success">	Toward baseline @cite christie1987cardiac	</span>|<span class="success">	Toward baseline @cite christie1987cardiac	</span>|	No Data	|<span class="success">	Toward baseline @cite christie1987cardiac	</span>|	No Data	|
<center><br>

*Table 4d. The fourth intensity/rest period.*
</center>
|	Segment	|	Notes	|	Occurrence Time (s)	|	Sampled Scenario Time (s)	|	Core Temperature (Celsius)	|	Peripheral Temperature (Celsius)	|	Heart Rate (beats/min)	|	Systolic Pressure (mmHg)	|	Diastolic Pressure (mmHg)	|	Mean Arterial Pressure (mmHg)	|	Stroke Volume (mL)	|	Cardiac Output (L/min)	|	Gut Blood Flow (L/min)	|	Systemic Vascular Resistance (mmHg-min/L)	|	Respiration Rate (breaths/min)	|	Tidal Volume (L)	|	Exchange Ratio (Or Respiratory Quotient)	|	Oxygen Consumption (L/min)	|	Urine Production Rate (mL/min)	|
|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|
|	Exercise Severity 0.3583	|	430 W	|	1470	|	1829	|<span class="success">	Increase @cite christie1987cardiac, @cite byrne2007ingestible	</span>|<span class="success">	No change or decrease @cite griffin1993temperature	</span>|<span class="success">	257% of baseline @cite christie1987cardiac	</span>|<span class="danger">	56.8% increase @cite christie1987cardiac	</span>|<span class="danger">	No change @cite christie1987cardiac	</span>|<span class="danger">	117.9% increase  @cite christie1987cardiac	</span>|<span class="danger">	31.2% increase  @cite christie1987cardiac	</span>|<span class="danger">	350% of base  @cite christie1987cardiac	</span>|<span class="danger">	reduced 25-50%  @cite perko1998gutflow	</span>|<span class="success">	decrease  @cite perko1998gutflow	</span>|<span class="danger">	59 +/- 9  @cite guenette2007respiratory	</span>|<span class="warning">	3.1 +/- 0.4  @cite guenette2007respiratory	</span>|<span class="danger">	increase, maximum  ~1.21  @cite koutlianos2013indirect	</span>|<span class="danger">	3.36  @cite christie1987cardiac	</span>|<span class="danger">	decrease  @cite melin2001comparison	</span>|
|	Exercise Severity 0	|	rest 2 minutes	|	1830	|	1950	|<span class="success">	Increase @cite christie1987cardiac or no change @cite byrne2007ingestible	</span>|<span class="success">	No change or decrease @cite griffin1993temperature	</span>|<span class="success">	Decreasing [Sensus Communis]	</span>|<span class="success">	Toward baseline @cite christie1987cardiac	</span>|<span class="success">	No change @cite christie1987cardiac	</span>|<span class="success">	Toward baseline @cite christie1987cardiac	</span>|<span class="success">	Toward baseline @cite christie1987cardiac	</span>|<span class="success">	Toward baseline @cite christie1987cardiac	</span>|<span class="success">	Toward baseline @cite christie1987cardiac	</span>|<span class="success">	Toward baseline @cite christie1987cardiac	</span>|<span class="success">	Toward baseline @cite christie1987cardiac	</span>|<span class="success">	Toward baseline @cite christie1987cardiac	</span>|	No Data	|<span class="success">	Toward baseline @cite christie1987cardiac	</span>|	No Data	|
<center><br>

*Table 5. The fatigue scenario validation results.*
</center>
|	Segment	|	Notes	|	Occurrence Time (s)	|	Duration of Full Exercise	|
|	---	|	---	|	---	|	---	|
|	Exercise Severity 0.3583	|	Exercise intensity of 0.3583 is a requested work rate of 430 watts.	|	N/A	|<span class="success">	~ 3 min @cite johnson2000exercise	</span>|

There are several physiological measures that are failing validation for the exercise action. However, most of the failing measures will be addressed by the chemoreceptor model currently in development as a part of the nervous system. The oxygen consumption and urine production measures may still fail validation during exercise after the nervous system is fully implemented. The development team is currently making plans to address those failures.

### Cold Water Submersion

<center>
<img src="./plots/Energy/ColdWaterSubmersion_TotalMetabolicRate.jpg" width="1100">
<img src="./plots/Energy/ColdWaterSubmersion_CoreTemp.jpg" width="1100">
<img src="./plots/Energy/ColdWaterSubmersion_SkinTemp.jpg" width="1100">
<img src="./plots/Energy/ColdWaterSubmersionLegend.jpg" width="1100">
</center>
<center>
*Figure 5. The cold water submersion begins by submerging the patient in water that has a temperature of 10 degrees Celsius. A direct result of this is a drop in skin temperature due to an increased heat loss from the skin surface. The patient remains in the water for one hour, during which the metabolic rate increases via shivering. This rise in metabolic rate allows for the core temperature to stabilize just above 35 degrees Celsius. After one hour, the patient is removed and then active heating begins ten minutes later. The result of active heating is an increase in core and skin temperature, and a decline in the patient&rsquo;s metabolic rate.*
</center><br>
<center>
*Table 6. The cold water submersion scenario results.*
</center>
|	Action	|	Notes	|	Occurrence Time (s)	|	Sampled Scenario Time (s)	|	Core Temperature (Celsius)	|	Peripheral Temperature (Celsius)	|	Metabolic Rate	|	Heart Rate (beats/min)	|	Systolic Pressure (mmHg)	|	Diastolic Pressure (mmHg)	|	Mean Arterial Pressure (mmHg)	|	Cardiac Output (L/min)	|
|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|
|	Environment File Change: Submerged in 5 C water	|	Patient is submerged in cold for 60 minutes	|	50	|	3650	|<span class="success">	Decrease to 35 degC @cite williams2005rewarming	</span>|<span class="success">	Decrease [Sensus Communis]	</span>|<span class="success">	Increase to between 300 and 350 W @cite williams2005rewarming	</span>|<span class="danger">	Decrease @cite garrioch2004body	</span>|<span class="success">	No change @cite christie1987cardiac	</span>|<span class="success">	If mild hypothermia (Core Temp 32-35 C) Increase @cite mallet2002hypothermia	</span>|<span class="success">	If mild hypothermia (Core Temp 32-35 C) Increase @cite mallet2002hypothermia	</span>|<span class="danger">	If mild hypothermia (Core Temp 32-35 C) Increase If moderate or severe (Core Temp < 32 C) Decrease @cite mallet2002hypothermia	</span>|
|	Environment File Change to Standard Environment	|		|	3650	|	4250	|<span class="warning">	Decrease below 35 @cite williams2005rewarming	</span>|<span class="success">	Increase [Sensus Communis]	</span>|<span class="success">	Increase above 350 W @cite williams2005rewarming	</span>|<span class="danger">	Decrease @cite talebipour2006sauna	</span>|<span class="danger">	Decrease @cite talebipour2006sauna	</span>|<span class="danger">	Decrease @cite talebipour2006sauna	</span>|<span class="danger">	Decrease @cite talebipour2006sauna	</span>|<span class="danger">	Decrease @cite talebipour2006sauna	</span>|
|	Active Heating at 1000 btu/hr	|		|	480	|	5450	|<span class="success">	Increase to between 36 and 38 degC @cite williams2005rewarming	</span>|<span class="success">	Increase [Sensus Communis]	</span>|<span class="success">	Decreasing to below 80 W @cite williams2005rewarming	</span>|<span class="danger">	Decrease @cite talebipour2006sauna	</span>|<span class="danger">	Decrease@cite talebipour2006sauna	</span>|<span class="danger">	Decrease @cite talebipour2006sauna	</span>|<span class="danger">	Decrease @cite talebipour2006sauna	</span>|<span class="danger">	Decrease @cite talebipour2006sauna	</span>|

At a scenario time of 50 seconds, the patient is submerged in water with a temperature of 10 degrees Celsius. The patient remains submerged for one hour, and then is removed from the water. The patient remains in the ambient environment for 10 minutes before active heating is applied. The power output of the heating device is 340 btu/hr. Active heating continues for 20 minutes, and then the scenario ends. The immediate response to cold water submersion is a drop in skin temperature. This occurs due to a dramatic increase in the skin convective heat transfer due to a shift from air convection to water convection. The core temperature declines due to increased heat transfer from core to skin. The drop in core temperature initiates a shivering response, leading to a rise in metabolic rate. Additional feedback comes in the form of vasoconstriction of the skin blood vessels. This helps to reduce the heat transferred from the core to skin. These two forms of feedback allow the core temperature to stabilize around 35 degrees Celsius. There is an increase in heart rate and respiration rate, initially due to a nervous response to the exposure to cold water. The increase in respiration rate and heart rate are maintained to accommodate the increased oxygen consumption and carbon dioxide production at the elevated metabolic rate. Following the return to the ambient environment, there is an immediate rise in skin temperature, with the core temperature following. The core temperature rise is not expected during this time period according to validation data. A continued decline in core temperature is expected. The observed increase in core temperature is due to a low heat capacitance used in the model and not accounting for residual water remaining on the skin surface after being removed from the water. The capacitance can be adjusted to a higher value, which would lead to the core temperature responding more slowly to changes in heat transfer over time. In addition, the %Environment heat transfer methodology could be updated to account for additional heat transfer due to water remaining on the skin surface after exiting submersion. At the onset of active heating, the skin temperature and core temperature continue to rise. This coincides with the expected validation outcome. 

### High Altitude Change
<table border="0">
<tr>
    <td><img src="./plots/Energy/HighAltitude_HR.jpg" width="550"></td>
    <td><img src="./plots/Energy/HighAltitude_O2PP.jpg" width="550"></td>
</tr>
<tr>
    <td><img src="./plots/Energy/HighAltitude_O2Sat.jpg" width="550"></td>
    <td><img src="./plots/Energy/HighAltitude_RR.jpg" width="550"></td>
</tr>
<tr>
    <td colspan="2"><img src="./plots/Energy/HighAltitudeLegend.jpg" width="1100"></td>
</tr>
</table>
<center>
*Figure 6. The patient is placed at a high altitude with an atmospheric pressure of 525 mmHg. The immediate result is a drop in arterial oxygen due to the decreased environment oxygen partial pressure. This leads to a drop in oxygen saturation and an increase in the patient heart rate. The patient stabilizes, acquiring a new resting physiologic state at the reduced pressure. The exaggerated increase in heart rate is due to a catecholamine release secondary to  hypoxia, a [known issue](@ref known-issues) in the engine*
</center><br>

This scenario is used to simulate the effects of low oxygen due to high altitude. At 30 seconds, the surrounding environment is changed to an equivalent elevation of 4000 meters, resulting in a drop in atmospheric pressure from 760 mmHg to 525 mmHg. The patient remains in the reduced pressure environment for 15 minutes. The immediate response is a decrease in arterial oxygen due to the reduced partial pressure in the environment. This leads to a decrease in the blood oxygen saturation, which is in line with the expected validation data. The reduced arterial oxygen causes an increase in the heart rate. This increase is currently determined from epinephrine release due to a hypoxia event being triggered. Another expected result of the epinephrine release is a respiration rate increase. This effect is nullified from the reduction in atmospheric carbon dioxide, which allows for larger quantities of carbon dioxide to diffuse out of the alveoli. The increased diffusion leads to lower arterial carbon dioxide partial pressures, which is used to drive the respiratory frequency. This counter balances the effect of epinephrine in the system, thus causing a slight decrease in respiration rate.

### Starvation and Dehydration
The starvation and dehydration conditions are currently disabled while we make improvements.

Conclusions
-----------
The %%Energy system has provided a method for handling metabolic consumption and production and heat transfer in the human body. This system is fundamentally connected to all of the other systems, and provides dynamic feedback according to changes in the external environment. In its current state, the energy system accurately calculates resting thermal physiology and nutrient consumption and production. The energy system can be used by developers who wish to model thermal changes due to the environment or through strenuous activity. This may be a simple simulation, or connection with a mannequin for real-time interfacing.

@anchor energy-future
Future Work
===========

Coming Soon
-----------
- The starvation condition will be integrated into exercise and the fatigue calculations, and replenishment of the aerobic energy store will be coupled to blood concentrations of nutrient substances.
- The fatigue model energy store maximums and maximum refill rates will scale with physical conditioning, fed/starvation levels, and body composition.
- The maximum work rate will scale with physical conditioning, fed/starvation levels, and body composition.
- The fatigue model endurance energy store refill rate will be coupled to blood nutrient substance concentrations.
- The nervous system will contain numerous chemoreceptor-related feedback mechanisms that will correct many of the exercise validation failures such as heart rate and blood pressure.
- The response of body core temperature to exercise will be improved.
- Sweat composition will include more than just water.

Recommended Improvements
------------------------
-	Increased discretization of the temperature circuit: This would allow for increased fidelity of the temperature solution and prediction of varying levels of water submersion.
-	Full biochemical model of metabolism: The current implementation of the metabolic calculations is a low fidelity approach. Increased fidelity could be used to provide more feedback on nutrient requirements and performance.
- Include psychological effects. For example, incorporate psychology into fatigue using a 'mettle' parameter.
- Switch exercise accounting from physical work rate to metabolic heat production.
- A true basal metabolic rate with differentiation from resting metabolic rate.

@anchor energy-appendices
Appendices
==========

Acronyms
--------
RQ - %Respiratory Quotient
BMR - Basal Metabolic Rate

Data Model Implementation
-------------------------
@ref EnergySystemTable "Energy"

@anchor energy-compartments
Compartments
------------
- InternalCore
- InternalSkin
- InternalGround