%Drugs Methodology {#DrugsMethodology}
=====================

@anchor drugs-overview
Overview
========

@anchor drugs-abstract
Abstract
--------
%Substances, including drugs, gases, and hormones, are transported through the body within the bloodstream and airflow in the %Cardiovascular and %Respiratory Systems, respectively. This provides important nutrients and waste removal for normal physiologic function. The %BioGears&reg; engine models advection in both fluid systems (see @ref SubstanceTransportMethodology). Transvascular transport is simulated using one of several diffusion models (see @ref TissueMethodology) for substances generically. Drug transvascular transport is modeled with a physiologically-based pharmacokinetic (PBPK) model, and the physiologic effects on the body are modeled with a low-fidelity pharmacodynamic (PD) model.

@anchor drugs-introduction
Introduction
------------
One major category of substances transported through the body is drugs. %Drugs influence the body by moving it out of homeostasis for a specific purpose, such as sedation for surgical intervention, or to address a patient condition, such as analgesic intervention. After a drug enters the patient&rsquo;s body (through intravenous administration, absorption through the gastrointestinal system, or inhalation of an agent), the substance ultimately is transported through the bloodstream for uptake by the tissues and organs. The process of clearing a drug from the system is accomplished in a combination of three methods: renal clearance, hepatic clearance, and systemic clearance. Depending on the drug, it may be processed by either the kidney, the liver, or both for removal from the system as a waste product. Additionally, drugs are metabolized by the body and removed from the bloodstream. These methods all reduce the amount of drugs in the system. The drug transport and clearance methodologies in %BioGears are described below.

@anchor drugs-system-design
System Design
=============

Background and Scope
--------------------
*Pharmacokinetics* is the study of the relationship between the dose of a drug and the time-evolution of the concentration of the drug throughout the body. The relationship between the concentration of a drug and the physiological response is described by the *pharmacodynamics* @cite rosenbaum2012basic. %BioGears has both pharmacokinetic and pharmacodynamic models. Because it is physiologically-based, the pharmacokinetic model has resolution at the same scale as the cardiovascular and respiratory systems. Physiologically-based pharmacokinetic (PBPK) modeling is a technique that mathematically models the distribution, uptake, metabolism, and clearance of a drug with consideration of the relevant physiological processes @cite khalil2011physiologically. The PBPK model provides more resolution than the classic one and two compartment models. The PBPK model also provides a base on which to build a receptor-based pharmacodynamic (PD) model, although the %BioGears PD model is currently a lower-fidelity phenomenological model based solely on the concentration of a drug in the blood. %Drugs impact body-level physiologic behavior such as heart rate, respiration rate, and blood pressure as result of cellular-level interactions caused by a drug that changes the behavior of physiologic entities, such as blood vessels and electrical activity in the heart. The cellular-level processes are not modeled in %BioGears, and instead the PD model is a direct relationship between concentration and maximum effect for a body-level response.

@anchor drugs-data-flow
Data Flow
---------
### Preprocess
#### Administer %Substances and Administer IV %Substances
All substances added or removed from the %BioGears body are incremented or decremented from the appropriate compartment during the Preprocess step. For example, if substances are administered via a bolus injection or through intravenous administration, the substance mass is increased in the vena cava compartment.

### Process
The generic substance methodology developed for the %BioGears Engine is used to solve for the mass, concentration, substance volume, and volume fraction in each compartment. After the masses and concentrations have been updated, the system-level effects of any circulating drugs are calculated using the [pharmacodynamic](@ref drugs-pharmacodynamics) model.

### Post Process
The Post Process step moves everything calculated in Process from the next time step calculation to the current time step calculation. %Substances have no specific Post Process functionality. Each system post processes their circuit and moves the mass, concentration, substance volume, and volume fraction from next to current.

<img src="./images/Drugs/DrugsDataFlow.png" width="900">
<center>
<i>Figure 1. The data flow begins with a Preprocess step where substances entering or exiting the %BioGears body are incremented or decremented. During the Process step, the mass and concentration (blood) or substance volume and volume fraction (air/gas) are calculated for each compartment in a system. During Process, the effects of any drugs in the system are calculated. There is no specific Post Process functionality in substances. However, as other systems post process their circuits, the substance values are moved from the next time step to the current time step calculation.</i>
</center><br>

Features, Capabilities, and Dependencies
----------------------------------------
Pharmacokinetic models quantify the time evolution of drug distribution from the administration of a dose. Pharmacodynamic models, on the other hand, characterize the events from the arrival of the drug at the site of action to the “onset, magnitude and duration of the biological response @cite rosenbaum2012basic.” The %BioGears %Drug system contains both pharmacokinetic and pharmacodynamic models.

@anchor pharmacokinetics
### Pharmacokinetics
The pharmacokinetic (PK) methodology provides a means for simulating the time-evolution of the distribution of a drug throughout the body. This is accomplished by using the administration actions discussed in the [Actions](@ref drugs-Actions) section below, the [transport methodology](@ref CircuitMethodology), the [perfusion limited diffusion](@ref tissue-perfusionLimitedDiffusion) methodology, and the substance files discussed in the [Common Data Model](@ref SubstanceTable) documentation. Once a drug is administered, it either enters the %Cardiovascular System (liquid) or the %Respiratory System (inhaled). If it is an inhaled drug, modeled in %BioGears as a gas, the drug will move into the alveoli through advection then diffuse into the %Cardiovascular System through alveoli transfer. Drug effects, described below in the @ref drugs-pharmacodynamics section, are then computed based on the concentration of the drug in the plasma. Note that the plasma concentration calculation is currently incorrect. The concentration of a drug is currently computed by dividing the mass of the drug in a compartment by the volume of plasma, as computed from the hematocrit. Implicit in the plasma concentration calculation is the assumption that all of the drug is in the extracellular space. In actuality, some of the drug will cross blood-cell membranes, and the concentration of drug in the plasma and in the blood is a function of many factors, including the lipophilicity. We will address this error in the [future](@ref drugs-future).

#### Partition Coefficient
The drugs circulate around the cardiovascular circuit via the generic transport methodology described in the @ref CircuitMethodology. However, drugs diffuse from the %Cardiovascular System into the tissues via [perfusion limited diffusion](@ref tissue-perfusionLimitedDiffusion). For each drug, the physicochemical properties are used to calculate the partition coefficient. This partition coefficient describes the affinity for the particular drug to diffuse across the barrier between the cardiovascular and tissue spaces. Each drug has its individual physicochemical properties described in the substance file with a calculated partition coefficient for each tissue compartment. For a very weak base, an acid, or a neutral, Equation 1 is used to calculate the partition coefficient.

\f[{K}_{pu} = f_{EW} + \frac{X * f_{IW}}{Y} + \frac{P * f_{NL} + (0.3 * P + 0.7) * f_{NP}}{Y} + \left[\left(\frac{1}{f_{u}} - 1 - \left(\frac{P * f_{NL} + (0.3 * P + 0.7) * f_{NP}}{Y}\right)\right) * \frac{PR_{T}}{PR_{B}}\right] \f] 
<center>
<i>Equation 1.</i>
</center><br>

For moderate to strong bases, Equation 2 is used to calculate the partition coefficient.

\f[{K}_{pu} = f_{EW} + \frac{1 + 10^{pK_{a}-pH_{IW}} * f_{IW}}{1 + 10^{pK_{a}-pH_{p}}} + \frac{K_{a}*AP_T*10^{pK_{a}-pH_{IW}}}{1+10^{pK_{a}-pH_{p}}} + \frac{P * f_{NL} + (0.3 * P + 0.7) * f_{NP}}{1+10^{pK_{a}-pH_{p}}}\f] 
<center>
<i>Equation 2.</i>
</center><br>

Where *X* and *Y* are the different relationships for pH, as shown in Table 1, *f<sub>IW</sub>* is the fraction of intracellular water, *f<sub>EW</sub>* is the fraction of extracellular water,  *f<sub>NP</sub>* is the fraction of neutral phospholipids in the tissue, *f<sub>NL</sub>* is the fraction of lipids in the tissue, *P* is the octanol:water partition coefficient for the drug, *f<sub>u</sub>* is the fraction of the drug unbound in plasma,  *f<sub>NL,P</sub>* is the fraction of neutral lipids in plasma, *f<sub>NP,P</sub>* is the fraction of phospholipids in plasma,  and *PR<sub>T</sub>* / *PR<sub>B</sub>* is the tissue to plasma ratio of the binding protein. 

<center>
<i>Table 1. The pH effects on the partition coefficient are described based on the drug type, i.e., very weak base, acid, or neutral. X relates the drug property pK<sub>a</sub> to the pH<sub>IW</sub>, intracellular water pH, while Y relates the pK<sub>a</sub> to the pH of the plasma.</i> </center>
| Ionic State    |    X    |    Y    |
| -------------- | :-----: | :-----: |
| Acid           | \f[1 + 10^{pH_{IW}-pK_{a}}\f] | \f[1 + 10^{pH_{p}-pK_{a}}\f] |
| Very Weak Base | \f[1 + 10^{pK_{a}-pH_{IW}}\f] | \f[1 + 10^{pK_{a}-pH_{p}}\f] |
| Neutral        | 1 | 1 |
<br>

A number of these values are drug parameters found in the substance file definitions. However, many of them are organ/compartment dependent as shown in Tables 2 and 3. 

<center>
<i>Table 2. The volume fractions for neutral lipids and phospholipids vary by compartment. These values are specified for each compartment as outlined below and used to calculate the partition coefficient of each drug for each tissue compartment in the %BioGears engine. These values were found in @cite rodgers2005physiologically.</i>
</center>

|	%Tissue Compartment	|	Extracellular Water (*f<sub>EW</sub>*) 	|   Intracellular Water (*f<sub>IW</sub>*)  |    Neutral Lipd (*f<sub>NL</sub>*)  |  Neutral Phospholipid (*f<sub>NP</sub>*)   |
| :---- | :---- | :---- |  :---- | :---- |
|	Adipose (Fat)	|  0.135  |  0.017  |  0.853  |  0.0016  |
|	Bone	        |  0.1    |  0.346  |  0.017  |  0.0017  |
|	Brain           |  0.162  |  0.620  |  0.039  |  0.0015  |
|   Gut             |  0.282  |  0.475  |  0.038  |  0.0125  |
|   Kidney          |  0.273  |  0.483  |  0.012  |  0.2420  |
|   Liver           |  0.161  |  0.573  |  0.014  |  0.2400  |
|   Lung            |  0.336  |  0.446  |  0.022  |  0.0128  |
|   Muscle          |  0.118  |  0.630  |  0.010  |  0.0072  |
|   Myocardium      |  0.320  |  0.456  |  0.014  |  0.0111  |
|   Skin            |  0.382  |  0.291  |  0.060  |  0.0044  |
|   Spleen          |  0.207  |  0.579  |  0.0077 |  0.0113  |


<center>
<i>Table 3. The tissue to plasma protein binding ratios are shown for each tissue compartment in the %BioGears Engine. Two proteins are available for drug binding, albumin and lipoprotein. The binding protein for each drug is specified in the substance file. These values were found in @cite rodgers2005physiologically.</i>
</center>

|	%Tissue Compartment	|	%Tissue to Plasma Albumin Ratio	|   %Tissue to Plasma Lipoprotein Ratio  |
| :---- | :---- | :---- |
|	Adipose (Fat)	|  0.049  |  0.068  |
|	Bone	        |  0.100  |  0.050  | 
|	Brain           |  0.048  |  0.041  |
|   Gut             |  0.158  |  0.0141 |
|   Kidney          |  0.130  |  0.137  |
|   Liver           |  0.086  |  0.161  |
|   Lung            |  0.212  |  0.168  |
|   Muscle          |  0.064  |  0.059  |
|   Myocardium      |  0.157  |  0.160  |
|   Skin            |  0.277  |  0.096  |
|   Spleen          |  0.097  |  0.207  |

The %BioGears implementation of the partition coefficients calculation and all values shown in the tables are derived from the literature @cite rodgers2005physiologically @cite rodgers2006physiologically @cite khalil2011physiologically @cite huisinga2012modeling @cite valentin2002icrp.

If it is not possible to obtain the information required to compute the partition coefficient for a drug, or if the calculation is not valid for a particular drug for any reason, it is possible to override the computation by directly inputting a constant partition coefficient in the drug file. Note that, to use this functionality, it is best to input a coefficient for every tissue compartment in the model. %BioGears currently uses the coefficient-computation override methodology for Albuterol, Ketamine, and Naloxone. The parameters used to calculate each partition coefficient were found in published data and/or tuned to get the desired kinetic response.

@anchor drugs-diffusion
#### Diffusion
The above partition coefficients are used to calculate the diffusion of a drug across the tissue-vascular barrier. All current drugs in the %BioGears Engine use perfusion limited diffusion as found in @cite khalil2011physiologically @cite huisinga2012modeling. For details on perfusion-limited and other diffusion modalities, see the @ref TissueMethodology.

In the current version of %BioGears, all drugs diffuse by the perfusion-limited model described above. An alternative means for modeling drug kinetics would be to leverage the other diffusion methods described in the @ref TissueMethodology report. The other diffusion models were developed primarily for the transmembrane transport of ions and a few specific organic molecules (e.g. glucose), and they have not been tested for drugs.

@anchor drugs-clearance
#### Clearance
The PBPK model represents renal, hepatic, and systemic clearance. The renal clearance rate, intrinsic clearance rate, and the systemic clearance rate are specified in the substance file in units of milliliter-blood per second per kilogram. The intrinsic clearance rate is used to calculate the hepatic clearance, as shown in Equation 3.

\f[Cl_{H} = \frac{Q_{H}*f_{u}*Cl_{I}*BW}{Q_{H} + f_{u}*Cl_{I}*BW} \f]
<center>
<i>Equation 3.</i>
</center><br>

Where *Cl<sub>H</sub>* is the hepatic clearance, *f<sub>u</sub>* is the fraction of the drug unbound in plasma, *Cl<sub>I</sub>* is the intrinsic clearance, and *BW* is the patient body weight.

The amount of drug removed (cleared) from the system is found by calculating the amount of fluid volume that can be cleared by a healthy organ. The volume is calculated, as shown in Equation 4. This process is completed for the renal and hepatic clearance. 

\f[V_{Cl} = Cl_{H}*BW*dt \f]
<center>
<i>Equation 4.</i>
</center><br>

Where *V<sub>cl</sub>* is the volume cleared, *Cl<sub>H</sub>* is the organ clearance rate, *BW* is the body weight, and *dt* is the time step. The actual mass of the substance removed during this process is found by determining the amount of the drug in the volume cleared, as shown in Equation 5.

\f[M_{Cl} = V_{Cl}*C \f]
<center>
<i>Equation 5.</i>
</center><br>

Where *M<sub>cl</sub>* is the mass cleared, *V<sub>cl</sub>* is the volume cleared, and *C* is the concentration in the tissue. The systemic clearance represents the total clearance for the body, including the renal and hepatic clearance. Therefore, the total volume cleared is calculated, then the renal and hepatic clearance volumes are removed, as shown in Equation 6. The &ldquo;remaining&rdquo; systemic mass cleared is calculated as shown in Equation 5. Half of the mass cleared from renal clearance is removed from each of the kidney tissue compartments, the mass cleared from hepatic clearance is removed from the liver tissue compartment, and the mass removed from the &ldquo;remaining&rdquo; systemic clearance is removed from the vena cava compartment. This is assumed to be from various metabolic processes in the plasma.

\f[V_{Cl} = \left(Cl_{s}*BW*dt\right) - V_{ClR} - V_{ClH} \f]
<center>
<i>Equation 6.</i>
</center><br>

Where *V<sub>cl</sub>* is the remaining systemic volume cleared, *Cl<sub>s</sub>* is the systemic clearance rate, *BW* is the patient body weight, *dt* is the time step, *V<sub>clR</sub>* is the renal volume cleared, and *V<sub>clH</sub>* is the hepatic volume cleared.

@anchor drugs-pharmacodynamics
### Pharmacodynamics
Pharmacodynamic (PD) models characterize the effect that a drug has on the organism. The current version of %BioGears contains two pharmacodynamic models.
- A simple dose-response model with a response biomarker functionally linked to the plasma concentration of a drug
- A site-of-action model with a local response functionally linked to the local tissue concentration of a drug

#### Plasma Concentration Model
Due to difficulties in measuring drug concentrations at the site of action as well as the varied and complex nature of the chain of events from receptor binding to biological response, drug responses are often quantified indirectly through surrogate endpoints. Development of the %BioGears pharmaocodynamic model began with a characterization of expected results by subject matter experts for a small library of drugs. The expected results were limited to whole-body biomarkers similar to vital signs (e.g. changes in heart rate, respiration rate, blood pressure, etc.). We treated the expected results as surrogate endpoints and used the common E<sub>max</sub> model to characterize the effects. Note that in this initial application, E<sub>max</sub> referred to the expected effect of the drug rather than the maximum effect of the drug. For that reason, overdose is not possible with most of the drugs in the current version of %BioGears. However, the simple E<sub>max</sub> model has been extended to a sigmoidal E<sub>max</sub> model; therefore, it is possible to shape the response curve to better match empirical data, and setting the true maximum effect is as simple as setting the correct value in the drug file. We are beginning to convert the pharmacodynamics of some drugs to the true E<sub>max</sub> model as data becomes available to us (see the [future work](@ref drugs-future) section). The pharmacodynamic effects included in the %BioGears plasma concentration PD model are described in Table 4.

<center>
<i>Table 4. Pharmacodynamic effects modeled in the %BioGears Engine with descriptions and relevant ranges.</i>
</center>

|	Pharmacodynamic Effect	|	Description 	|   Available Values   |
| :---- | :---- | :---- |
|	Bronchodilation	|	Drug effect on the bronchii radii. A maximal effect of 1.0 will reverse the constriction of an asthma attack. | 0 to 1 |
|	Diastolic Pressure	|	Change in the diastolic pressure. Given as a fraction. | -1 to 1 |
|	Heart Rate	|	Change in the heart rate. Given as a fraction. | -1 to 1 |
|   Neuromuscular Block |  Drug&rsquo;s strength as a neuromuscular block, with a 1.0 as the strongest block.  | 0 to 1 |
|   Pupil Size Modifier |  Drug effect on the pupil diameter. Given as a modifier. | -1 to 1 |
|   Pupil Reactivity Modifier |  Drug effect on the pupil reactivity to light. Given as a modifier. | -1 to 1 |
|   Respiration Rate | Change in the respiration rate. Given as a fraction. | -1 to 1 |
|   Sedation  |   Drug&rsquo;s strength as a sedative, with a 1.0 as the strongest sedative.  | 0 to 1 |
|   Systolic Pressure  | Change in the systolic pressure. Given as a fraction. | -1 to 1 |
|   Tidal Volume  |  Change in the tidal volume. Given as a fraction. | -1 to 1 |
|   Tubular Permeability | Drug localized effect on tubulear permeability. Given as a severity, 1.0 complete reabsorption block | 0 to 1 | 

The drug effects are specified for each drug in the substance file. The level of effect is calculated based on the expected effect (or, for some drugs, the maximum effect) of the drug and the current plasma concentration for the drug, as shown in Equation 7 @cite rosenbaum2012basic.  

\f[\Delta E = E_{bl}*\frac{E_{m}*C_{p}^\eta}{EC_{50}^\eta+C_{p}^\eta} \f]
<center>
<i>Equation 7.</i>
</center><br>

Where *E<sub>m</sub>* is the expected (or maximum) effect of the drug, *EC<sub>50</sub>* is the concentration at 50% of the effect, *C<sub>p</sub>* is the drug concentration in plasma, *E<sub>bl</sub>* is the baseline for that effect (i.e., heart rate baseline), <i>&Delta;E</i> is the calculated effect of the drug, and <i>&eta;</i> is the slope factor @cite rosenbaum2012basic. This calculation is repeated for each of the effects in Table 4. 

The drug effect is applied as a fraction of the baseline for the biomarker, which is a patient variable in %BioGears. For example, a person with a resting heart rate of 72 bpm may have a physiological process happening during simulation, perhaps as a condition, which increases his/her baseline heart rate to 80 bpm. If this patient is given a drug with a heart rate effect of 0.2, then at maximum the patient's heart rate will be 96 bpm (80 + 0.2 * 80). If the same drug were given to the same patient but without the condition, the maximum heart rate will be 86.4 bpm (72 + 0.2 * 72).

The *EC<sub>50</sub>* values were unknown for the majority of the drugs, so it was estimated from the maximum concentration of the drug at a standard adult dose, as shown in Equation 8.

\f[EC_{50} = \frac{C_{max}}{32} \f]
<center>
<i>Equation 8.</i>
</center><br>

Where *C<sub>max</sub>* is the maximum plasma concentration for the standard adult dose and *EC<sub>50</sub>* is the concentration at which 50% of the effect should be present.

@anchor drugs-cardiovascular-effects
##### %Cardiovascular Effects
Equation 7 provides a straightforward calculation for the heart rate. However, to be applied in the cardiovascular system, the drug effects need to be translated to the effects on the mean arterial pressure and the pulse pressure. This is accomplished using Equations 9 and 10. These equations were developed using the relationship between diastolic and systolic pressure and the mean arterial pressure @cite guyton2006medical.

\f[\Delta MAP = \left(2* \Delta DBP \right) + \frac{\Delta SBP}{3} \f]
<center>
<i>Equation 9.</i>
</center><br>

\f[\Delta P_{pulse} = \Delta SBP - \Delta DBP \f]
<center>
<i>Equation 10.</i>
</center><br>

Where *MAP* is the mean arterial blood pressure, *DBP* is the diastolic blood pressure, and *SBP* is the systolic blood pressure. These changes to the heart rate, mean arterial pressure, and pulse pressure are then system outputs for the drug system. The changes are then applied in the %Cardiovascular System. For more details on the implementation of the effects see the @ref CardiovascularMethodology.

@anchor drugs-respiratory-effects
##### %Respiratory Effects
As with the %Cardiovascular System, the respiratory and tidal volume effects are relatively straight forward to apply. The neuromuscular block and sedation levels are calculated to have an effect level between zero and one, where zero is no effect and one is a maximal effect. The detail of how these are implemented can be found in the @ref RespiratoryMethodology.

#### Site-of-Action Model
There are currently two drugs which utilize a localized PD effects model: Albuterol and Furosemide.

##### %Respiratory Effects
Aerosolized substances have a direct effect on the respiratory system. There are two direct-effect aerosol substance properties.
- BronchioleModifier
	- A parameter which controls the dilation (positive value) or constriction (negative value) of the bronchioles in the presence of the substance
- InflammationCoefficient
	- A parameter to quantify the propensity of the aerosol to cause inflammation of the respiratory tissues

For example, Albuterol is an aerosolized drug that typically enters the body via nebulizer or metered-dose inhaler. Accordingly, in %BioGears Albuterol enters the body through the respiratory tract and diffuses into the respiratory tissues (see the [aerosol section](@ref environment-aerosol) in the @ref EnvironmentMethodology report). The BronchioleModifier for Albuterol is set to 1 in the substance file, meaning that Albuterol has the capability to maximally dilate the bronchioles. The bronchodilatory effects of Albuterol are applied directly at the site of action, and the actual bronchodilation is a function of the concentration of Albuterol in the respiratory tissues.

##### %Renal Effects
The pharmacodynamic effects of diuretics locally target the renal system's functionality. Local binding of the Na-K-2Cl symporter by Furosemide (Lasix) in the tubular lumen stimulates an increase in urine production and ion excretion. In %BioGears we simulate this effect by adjusting the reabsorption permeability as a function of plasma concentration of Furosemide. This enables simulation of the whole-body drug effects, but the model does not use the local concentration of drug in the tubular lumen as the primary determinant of the reabsorption adjustment. A mechanistic model based on traditional receptor theory which combines the tissue properties of receptor concentration and signal transduction with the drug properties of intrinsic efficacy and affinity to form a model of drug response would use the local tissue concentration as the first link in a causal chain leading to permeabilty changes and the appropriate downstream effects. This type of mechanistic model is recommended as future work. For details on the reabsorption and urine production of the renal system, see the @ref RenalMethodology report. The results of the Lasix administration simulation are compared to data found in literature and presented in the [validation section](@ref drugs-furosemide).

@anchor drugs-substances
### %Substances
The full list of drugs available in the %BioGears library can be found in Table&nbsp;5 in the Validation section. Additional substances, such as oxygen, carbon dioxide, and hemoglobin that are available in the %BioGears Engine can be found in the @ref BloodChemistryMethodology.

@anchor drugs-variability
### Patient Variability
It is possible to customize the body that is simulated by %BioGears. For a detailed discussion of patient variability in %BioGears please see the @ref PatientMethodology report. Variability in body morphology will obviously have an effect on the pharmacokinetics of a drug. For example, a larger body may have a larger plasma volume, and thus the plasma concentration for a specific dose of a drug will be less than the same dose administered to a smaller body. Additionally, the partitioning of drugs is dependent on the relative masses of the physiological compartments, and storage is affected by distribution. Lipophilic drugs may appear to remain longer in the %BioGears plasma in patients who are configured with a higher body fat fraction. Patient configuration will also impact the pharmacodynamics. Maximum drug effects are computed as a fraction of baseline physiology. Changing a patient's baseline parameter (e.g. heart rate baseline) will also change the maximum effect (e.g. maximum heart rate) at a specific concentration of a drug. All drug validation is performed on a %BioGears Standard Male.

@anchor drugs-dependencies
### Dependencies
The substance calculations rely on the flow values calculated by the @ref CircuitMethodology to calculate the movement of substances from compartment to compartment in each circuit. Any limitations and assumptions associated with this methodology will also be associated with the %Drugs Methodology. The pharmocokinetic modeling is reliant on accurate values for the physical chemical properties of drugs. If these parameters are unknown or estimated from animal studies, the calculation for the partition coefficient may become unreliable.  For some drugs, this information may be difficult to determine. The %BioGears model also allows the user to supply partition coefficients directly. Some third party resources, both open source and commercially available, may provide this data for users, allowing incorporation of the data into the %BioGears full body simulation.

While this model is primarily used for drugs, it could be used for any substance in the body. %BioGears uses the clearance methodology for several additional substances. The modular approach to these calculations allows for the use of any combination of the three methodologies, PK, clearance, and PD.

The substance values and calculations are used by a variety of systems to trigger actions and responses, define physiologic set points, scale circuit parameters, and modify driver frequencies. Many of these triggers and responses are discussed in the @ref BloodChemistryMethodology and the @ref EndocrineMethodology. The drug-specific effects are listed and described briefly in Table&nbsp;5. The implementation of these calculated responses can be found in the @ref CardiovascularMethodology and the @ref RespiratoryMethodology.

@anchor drugs-assumptions
### Assumptions and Limitations
The %Drugs Methodology is based on the assumption that all substances are suspended in the fluid (blood or air, depending on the system) and move through the circuits with the flow. While this does allow for renal and hepatic clearance and metabolic elimination of substances, it does not allow for particle deposition. This assumption is valid for the level of fidelity of the model. In the future, particle deposition can be addressed by adding a more detailed substance methodology with factors for deposition within an organ, tissue, or blood vessel. Also, not included is a method for modeling vaporized substances, such as albuterol.  In the future, we will add this methodology to allow a liquid in the respiratory tract and produce a more realistic representation of the behavior.

The drug model addresses many of the earlier limitation of the %BioGears drug model. This includes creating a substance file that uses physical chemical properties to define the pharmacokinetic properties and intuitive modifiers to calculate the pharmacodynamic effects. However, this implementation of a PD model works best with a drug with immediate effects, such as anesthesia medications. This implementation has not been tested for drugs with a later onset due to secondary mechanisms. This is an area for future work. Additionally, no drug interactions or intoxication is modeled.

@anchor drugs-Actions
Actions
-------

@anchor drugs-interventions
### Interventions

#### Bolus Administration

A bolus administration represents an injection of a substance in a single dose. The substance, concentration, and amount are specified by the user. The total mass for the dose is calculated by multiplying the concentration and the amount. The total mass is then incrementally added to the vena cava compartment over the course of two seconds to represent the slow depression of a plunger. Once added to the vena cava, the substance will circulate through the %Cardiovascular System as part of the blood flow. The effects of the substance on the physiologic output will vary with the substance.

#### IV Administration

Intravenous administration represents administration of a compound substance (a single entity with multiple substances, i.e., saline) at a specified rate over time into the venous system. The compound substance, the rate, and the bag volume are specified by the user. At each time step, the mass of the substances are incremented based on the amount of compound substance entering the system. The mass is calculated by taking the flow entering the system at each time step multiplied by the known concentration of each substance within the compound substance. This mass is then added to the vena cava at each time step until the intravenous administration is stopped. The added substances will then circulate through the %Cardiovascular System as part of the blood flow. The effect on the physiologic output will vary based on the compound substance selected.

#### IV Infusion

Titration represents the administration of a single substance at a specified rate and concentration over time into the venous system. The user selects a single substance and specifies the concentration and rate with titration. As with intravenous administration, the mass of the substance is incremented based on the amount of the substance entering the system. The mass is calculated by taking the flow entering the system at each time step multiplied by the known concentration of each substance within the compound substance. This mass is then added to the vena cava at each time step until the intravenous administration is stopped. The added substances then circulate through the %Cardiovascular System as part of the blood flow. The effect on the physiologic output will vary based on the compound substance selected.

@anchor drugs-results
Results and Conclusions
=======================

Validation - Resting Physiologic State
--------------------------------------

The %Drugs Methodology has no resting state validation.

@anchor drugs-validation-actions
Validation - Actions
--------------------

### Bolus Administration

All drugs in the %BioGears library were validated qualitatively or with subject matter expert input. The bolus injection methodology was validated by comparing the PK and PD results to literature. See the sections below for more detail. 

The succinycholine scenario shows a drug impacting the major %BioGears systems. Succinycholine (Figure&nbsp;4) initially drops the heart rate and blood pressure approximately 5&ndash;10%. As expected, the respiration drops to zero within 60&ndash;90 seconds to represent the paralysis associated with the neuromuscular blocker. The oxygen saturation drops slowly as the concentration of oxygen in the bloodstream drops, leading to hypoxia. Epinephrine is released in response to hypoxia, causing an increase in heart rate and blood pressure (@ref EndocrineMethodology). This is an example of the interdependent nature of the %BioGears systems and the chain reaction drug administration can cause.

<center>
<table border="0">
<tr>
    <td><img src="./plots/Drugs/Succinylcholine_HeartRate.jpg" width="550"></td>
    <td><img src="./plots/Drugs/Succinylcholine_MeanArterialPressure.jpg" width="550"></td>
</tr>
<tr>
    <td><img src="./plots/Drugs/Succinylcholine_RespirationRate.jpg" width="550"></td>
    <td><img src="./plots/Drugs/Succinylcholine_OxygenSaturation.jpg" width="550"></td>
</tr>
<tr>
    <td colspan="2"><img src="./plots/Drugs/SuccinylcholineLegend.jpg" width="1100"></td>
</tr>
</table>
</center>
<center>
<i>Figure 2. The neuromuscular blocker, Succinylcholine, causes a cessation of respiration due to its paralytic effects. The heart rate and blood pressure initially decrease due to the system-level drug effects. As the oxygen decreases,  hypoxia occurs, resulting in an increase in heart rate and blood pressure.</i>
</center><br>

#### Intravenous Administration
Validation of intravenous administration of a hypotonic solution and blood products can be found in the @ref CardiovascularMethodology.

@anchor drugs-validation-pharmacokinetic
Validation - Pharmacokinetic
--------------------

The PK model was validated by comparing the plasma concentration calculated by the %BioGears Engine to plasma concentration curves found in the literature. The comparisons are shown in Figures 4&ndash;14. No available data was found for Epinephrine, so this drug was only validated from a PD perspective.

<img src="./plots/Drugs/Albuterol.jpg" width="1100">
<center>
<i>Figure 4. Albuterol is an aerosol, but it is modeled as a gas in %BioGears. Alveolar exchange takes place bidirectionally as long as the "gas" (aerosol) is in the blood or in the environment. For that reason, the concentration of Albuterol in the plasma diminishes much faster in %BioGears than demonstrated in literature @cite anderson1998pharmacokinetics. This is a known issue and an area of future work for %BioGears.</i>
</center><br>

<img src="./plots/Drugs/Fentanyl.jpg" width="1100">
<center>
<i>Figure 5. The physical chemical properties of fentanyl found in the literature were used to produce a good fit for the plasma concentration. The experimental data was found in @cite shankaran2013physiologically.</i>
</center><br>

<img src="./plots/Drugs/Furosemide.jpg" width="1100">
<center>
<i>Figure 5. The physical chemical properties of furosemide found in the literature were used to produce a good fit for the plasma concentration. The experimental data was found in @cite hammarlund1985acute.</i>
</center><br>

<img src="./plots/Drugs/Ketamine.jpg" width="1100">
<center>
<i>Figure 6. The partition coefficients were calculated from initial physical chemical properties found for Ketamine. However, the fit was unsatisfactory, so the partition coefficients were directly estimated for this drug to produce a good fit with the plasma concentration curve found in @cite xie2003analgesic.</i>
</center><br>

<img src="./plots/Drugs/Midazolam.jpg" width="1100">
<center>
<i>Figure 7. The %BioGears curve for midazolam plasma concentration shows a good overall fit with the experimental data found in @cite schwagmeier1998midazolam. However, the clearance dominant (end) portion of the curve shows that %BioGears should be clearing more quickly, while midazolam appears to move into the tissues too quickly during the diffusion dominant portion of the curve (beginning).</i>
</center><br>

<img src="./plots/Drugs/Morphine.jpg" width="1100">
<center>
<i>Figure 8. The physical chemical properties of morphine found in the literature were used to produce a good fit for the plasma concentration. The experimental data was found in @cite lotsch2002pharmacokinetic.</i>
</center><br>

<img src="./plots/Drugs/Naloxone.jpg" width="1100">
<center>
<i>Figure 9.  The partition coefficients were calculated from initial physical chemical properties found for Naloxone. However, the fit was unsatisfactory, so the partition coefficients were directly estimated for this drug to produce a good fit with the plasma concentration curve found in @cite aitkenhead1984pharmacokinetics.</i>
</center><br>

<img src="./plots/Drugs/Pralidoxime.jpg" width="1100">
<center>
<i>Figure 10. The pralidoxime experimental data found in @cite abbara2010pharmacokinetic was collected after an intramuscular injection. This administration method is available in %BioGears, so was used to validate the drug. The overall fit between the %BioGears data and the experimental data was good. A slightly higher concentration throughout was evident and may be attributed to the amount of drug that never exits the muscle when this type of injection occurs. In the future, a loss factor could be added to represent this drug amount.</i>
</center><br>

<img src="./plots/Drugs/Prednisone.jpg" width="1100">
<center>
<i>Figure 11.  The physical chemical properties of prednisone found in the literature were used to produce a good fit for the plasma concentration. The experimental data was found in @cite rose1981dose.</i>
</center><br>

<img src="./plots/Drugs/Propofol.jpg" width="1100">
<center>
<i>Figure 12. The propofol experimental data was collected during and after an infusion of propofol. %BioGears is able to support a rate and concentration input for an infusion; therefore, the infusion methodology was used to adminster propofol in the engine. The infusion explains the initial curve evident in the plasma concentration. The initial diffusion dominant portion of the curve shows a reduced diffusion into the tissues compared to the experimental data; however, the clearance dominant portion of the curve shows good agreement with the data found in @cite ward2002pharmacodynamics.</i>
</center><br>

<img src="./plots/Drugs/Rocuronium.jpg" width="1100">
<center>
<i>Figure 13. The %BioGears calculated plasma concentration curve for Rocuronium shows good agreement with the experimental data found in @cite de2014analysis. This is particularly true for the diffusion dominant portion of the curve, while the %BioGears clearance is less than that shown in the experimental data.</i>
</center><br>

<img src="./plots/Drugs/Succinylcholine.jpg" width="1100">
<center>
<i>Figure 14. The succinycholine pharmacokinetics were initially calculated from the values found in literature for the physical chemical properties. However, this were significantly adjusted to attempt to match the calculated plasma concentration to the experimental data found in @cite roy2002concentration.</i>
</center><br>

The above results show that, in general, the model chosen for %BioGears produces good agreement between experimental and calculated data. However, it also reveals that for some drugs, this model does not appear to be valid. Future work will investigate the incorporation of vaporized substance methodologies, and additional partition coefficient calculations that may prove more accurate for specific drug types. Further statistical analysis will also be undertaken to assess the model performance rather than solely relying on a qualitative analysis.

@anchor drugs-validation-pharmacodynamic
Validation - Pharmacodynamic
--------------------

The pharmacodynamic effects of the drugs were validated by comparing the effects of each drug to a number of clinical parameters. A summary of the drug validation is shown in Table&nbsp;5. More details on the individual scenario validation can be found in the <a href="DrugsValidation.pdf">Drugs Scenario Validation Matrix</a>.

<center>
<i>Table 5. The %BioGears drug library was validated qualitatively with published values and using subject matter expertise. Green indicates good agreement with validation data, yellow indicates agreement with a general trend with some minor disagreement, and red indicates a disagreement with the validation data. The number indicates the number of output parameters for each category of validation success or failure.</i>
</center>

|	Scenario 	|	Description	|	Good	|	Decent	|	Bad	|
|	---	|	---	|	---	|	---	|	---	|
|	Albuterol	|	Administer 90 ug metered dose of Albuterol	|<span class="success">	5	</span>|<span class="warning">	0	</span>|<span class="danger">	1	</span>|
|	Epinephrine	|	Administer 10 ug injection of Epinephrine	|<span class="success">	4	</span>|<span class="warning">	1	</span>|<span class="danger">	0	</span>|
|	Fentanyl	|	Administer 17 mg injection of Fentanyl	|<span class="success">	5	</span>|<span class="warning">	0	</span>|<span class="danger">	0	</span>|
|	Furosemide	|	Administer 40 mg injection of Furosemide	|<span class="success">	4	</span>|<span class="warning">	0	</span>|<span class="danger">	0	</span>|
|	Ketamine	|	Administer 115 mg injection of Ketamine	|<span class="success">	4	</span>|<span class="warning">	1	</span>|<span class="danger">	0	</span>|
|	Midazolam	|	Administer 5 mg injection of Midazolam	|<span class="success">	5	</span>|<span class="warning">	0	</span>|<span class="danger">	0	</span>|
|	Morphine	|	Administer 42 mg injection of Morphine	|<span class="success">	5	</span>|<span class="warning">	0	</span>|<span class="danger">	0	</span>|
|	Naloxone	|	Administer 17 mg injection of Fentanyl Followed by 30 ug injection of Naloxone *Validating only Naloxone	|<span class="success">	5	</span>|<span class="warning">	0	</span>|<span class="danger">	0	</span>|
|	Pralidoxime	|	Administer 700 mg injection of Pralidoxime	|<span class="success">	5	</span>|<span class="warning">	0	</span>|<span class="danger">	0	</span>|
|	Prednisone	|	Administer 20 mg injection of Prednisone	|<span class="success">	5	</span>|<span class="warning">	0	</span>|<span class="danger">	0	</span>|
|	Propofol	|	Administer 135 mg injection of Propofol	|<span class="success">	4	</span>|<span class="warning">	0	</span>|<span class="danger">	1	</span>|
|	Rocuronium	|	Administer 52 mg injection of Rocuronium	|<span class="success">	2	</span>|<span class="warning">	0	</span>|<span class="danger">	3	</span>|
|	Succinylcholine	|	Administer 96 mg injection of Succinylcholine	|<span class="success">	5	</span>|<span class="warning">	0	</span>|<span class="danger">	0	</span>|
|		|	Total	|<span class="success">	54	</span>|<span class="warning">	2	</span>|<span class="danger">	5	</span>|

<center>
<i>Table 6. The validation results for liquid-modeled drugs.</i>
</center>

|	Event	|	Notes	|	Action Occurance Time (s)	|	Sample Scenario Time (s)	|	Heart Rate  (beats/min)	|	Systolic Pressure  (mmHg)	|	Diastolic Pressure  (mmHg)	|	Respiration Rate  (breaths/min)	|	Oxygen Saturation	|
|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|
|	Administer Epinephrine - 10ug	|	Drug Onset < 1 minute	|	30	|	150	|<span class="warning">	25-50% Increase @cite dukeSME	</span>|<span class="success">	25-50% Increase @cite dukeSME 	</span>|<span class="success">	25-50% Increase @cite dukeSME 	</span>|<span class="success">	NC @cite dukeSME	</span>|<span class="success">	NC 	</span>|
|	Administer Fentanyl - 17 mg	|	Drug Onset < two minutes	|	30	|	100	|<span class="success">	Stable @cite Morgan2006Clinical p192-7, @cite PaulGBarash2009 p277; 5-10% Decrease @cite dukeSME  	</span>|<span class="success">	Stable @cite Morgan2006Clinical p192-7, @cite PaulGBarash2009 p277; 5-10% Decrease @cite dukeSME  	</span>|<span class="success">	Stable @cite Morgan2006Clinical p192-7, @cite PaulGBarash2009 p277; 5-10% Decrease @cite dukeSME  	</span>|<span class="success">	Decrease @cite Morgan2006Clinical p192-7, @cite PaulGBarash2009 p277; 15-25% Decrease @cite dukeSME	</span>|<span class="success">	NC 	</span>|
|	Administer Ketamine - 115 mg	|	Drug Onset < 1 minute	|	30	|	200	|<span class="success">	Moderate Increase @cite Morgan2006Clinical p200; 15-25% Increase @cite dukeSME   	</span>|<span class="success">	Moderate Increase @cite Morgan2006Clinical p200; 15-25% Increase @cite dukeSME   	</span>|<span class="warning">	Moderate Increase @cite Morgan2006Clinical p200; 15-25% Increase @cite dukeSME   	</span>|<span class="success">	Mild Decrease @cite Morgan2006Clinical p200; 25-50% Decrease @cite dukeSME     	</span>|<span class="success">	NC 	</span>|
|	Administer Midazolam - 5 mg	|	Drug Onset in 1-3 min and lasts 30-60 minutes	|	30	|	70	|<span class="success">	Mild Increase @cite Morgan2006Clinical p200; 5-10% Decrease @cite dukeSME	</span>|<span class="success">	Moderate Decrease @cite Morgan2006Clinical p200; 15-25% Decrease @cite dukeSME    	</span>|<span class="success">	Moderate Decrease @cite Morgan2006Clinical p200; 15-25% Decrease @cite dukeSME    	</span>|<span class="success">	Moderate Decrease @cite Morgan2006Clinical p200; Marked Decrease To 0 @cite dukeSME    	</span>|<span class="success">	As long as some respiration rate, little change. If RR=0, then begins to drop along O2 curve. 	</span>|
|	Administer Morphine- 42 mg	|	Drug Onset in less than 2 minutes	|	30	|	100	|<span class="success">	Mild Decrease @cite Morgan2006Clinical p200; 5-10% Decrease @cite dukeSME     	</span>|<span class="success">	Decrease - dose dependant @cite Morgan2006Clinical p200; 5-10% Decrease @cite dukeSME    	</span>|<span class="success">	Decrease - dose dependant @cite Morgan2006Clinical p200; 5-10% Decrease @cite dukeSME    	</span>|<span class="success">	Marked Decrease @cite Morgan2006Clinical p200; 15-25% Decrease @cite dukeSME   	</span>|<span class="success">	As long as some respiration rate, little change. If RR=0, then begins to drop along O2 curve. 	</span>|
|	Administer Fentanyl - 17 mg	|	Drug Onset < two minutes	|	30	|	100	|<span class="success">	Stable @cite Morgan2006Clinical p192-7, @cite PaulGBarash2009 p277; 5-10% Decrease @cite dukeSME  	</span>|<span class="success">	Stable @cite Morgan2006Clinical p192-7, @cite PaulGBarash2009 p277; 5-10% Decrease @cite dukeSME  	</span>|<span class="success">	Stable @cite Morgan2006Clinical p192-7, @cite PaulGBarash2009 p277;  5-10% Decrease @cite dukeSME  	</span>|<span class="success">	Decrease @cite Morgan2006Clinical p192-7, @cite PaulGBarash2009 p277; 15-25% Decrease @cite dukeSME	</span>|<span class="success">	NC 	</span>|
|	Administer Naloxone - 30ug	|	Drug Onset in one to two minutes	|	330	|	350	|<span class="success">	NC or Increase @cite Morgan2006Clinical p192-7, @cite PaulGBarash2009 p285; 5-10% Increase @cite dukeSME   	</span>|<span class="success">	NC or Increase @cite Morgan2006Clinical p192-7, @cite PaulGBarash2009 p285; 5-10% Increase @cite dukeSME   	</span>|<span class="success">	NC or Increase @cite Morgan2006Clinical p192-7, @cite PaulGBarash2009 p285; 5-10% Increase @cite dukeSME   	</span>|<span class="success">	Decrease @cite Morgan2006Clinical p192-7, @cite PaulGBarash2009 p285; Return to resting physiology @cite dukeSME   	</span>|<span class="success">	NC or Increase  	</span>|
|	Administer Pralidoxime - 135 mg	|	Drug Onset in less than 1 minute	|	30	|	100	|<span class="success">	Tachycardia @cite rxlist	</span>|<span class="success">	Increased @cite rxlist   	</span>|<span class="success">	Increased @cite rxlist   	</span>|<span class="success">	Increased @cite rxlist	</span>|<span class="success">	NC @cite safety  	</span>|
|	Administer Prednisone - 135 mg	|	Drug Onset in less than 1 minute	|	30	|	100	|<span class="success">	NC @cite safety  	</span>|<span class="success">	NC @cite safety  	</span>|<span class="success">	NC @cite safety  	</span>|<span class="success">	NC @cite safety  	</span>|<span class="success">	NC @cite safety  	</span>|
|	Administer Propofol - 135 mg	|	Drug Onset in less than 1 minute	|	30	|	100	|<span class="danger">	NC @cite Morgan2006Clinical p200; NC @cite dukeSME     	</span>|<span class="success">	Marked Decrease @cite Morgan2006Clinical p200; 25-40% Decrease @cite dukeSME    	</span>|<span class="success">	Marked Decrease @cite Morgan2006Clinical p200; 25-40% Decrease @cite dukeSME    	</span>|<span class="success">	Marked Decrease @cite Morgan2006Clinical p200; 100% Decrease @cite dukeSME    	</span>|<span class="success">	Begins to drop according to O2 curve 	</span>|
|	Administer Rocuronium - 52 mg	|	Drug Onset in 60-90 seconds	|	30	|	100	|<span class="danger">	NC @cite PaulGBarash2009 p299; NC @cite dukeSME     	</span>|<span class="danger">	NC @cite PaulGBarash2009 p299; NC @cite dukeSME     	</span>|<span class="danger">	NC @cite PaulGBarash2009 p299; NC @cite dukeSME     	</span>|<span class="success">	Goes to Zero @cite Morgan2006Clinical p224; Goes to Zero @cite dukeSME     	</span>|<span class="success">	Begins to drop according to O2 curve 	</span>|
|	Administer Succinycholine - 96 mg	|	Drug Onset < 1 minute	|	30	|	100	|<span class="success">	Mild  Increase @cite Morgan2006Clinical pp210-5; 5-10% Decrease @cite dukeSME    	</span>|<span class="success">	Mild  Increase @cite Morgan2006Clinical pp210-5; 5-10% Decrease @cite dukeSME    	</span>|<span class="success">	Mild  Increase @cite Morgan2006Clinical pp210-5; 5-10% Decrease @cite dukeSME    	</span>|<span class="success">	Goes to Zero @cite Morgan2006Clinical p224; Goes to Zero @cite dukeSME     	</span>|<span class="success">	Begins to drop according to O2 curve 	</span>|


<center>
<i>Table 7. The validation results for gas-modeled drugs.</i>
</center>

|	Event	|	Notes	|	Action Occurance Time (s)	|	Sample Scenario Time (s)	|	Heart Rate (beats/min)	|	Systolic Pressure (mmHg)	|	Diastolic Pressure (mmHg)	|	Respiration Rate (breaths/min)	|	Tidal Volume (mL)	|	Oxygen Saturation	|
|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|
|	Administer Albuterol - 10ug	|	Drug Onset < 1 minute	|	30	|	200	|<span class="success">	25-50% Increase @cite gumbhir1998pharmacokinetic 	</span>|<span class="danger">	Slight Increase @cite gumbhir1998pharmacokinetic 	</span>|<span class="success">	Slight Increase @cite gumbhir1998pharmacokinetic 	</span>|<span class="success">	NC @cite gumbhir1998pharmacokinetic	</span>|<span class="success">	NC @cite gumbhir1998pharmacokinetic	</span>|<span class="success">	NC 	</span>|


<center>
<i>Table 8. The validation results for furosemide.</i>
</center>

|	Event	|	Notes	|	Action Occurance Time (s)	|	Sample Scenario Time (min)	|	Urine Production Rate (mL/min)	|	Chloride Excretion (mmol/min)	|	Sodium Excretion (mol/min)	|	Vascular Volume (mL)	|
|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|
|	Administer Furosemide - 40 mg	|	Drug Onset < 1 minute	|	30	|	450	|<span class="success">	300-400% Increase @cite lahav1992intermittent 	</span>|<span class="success">	300-400% Increase @cite lahav1992intermittent 	</span>|<span class="success">	300-400% Increase @cite lahav1992intermittent 	</span>|<span class="success">	Decrease (around 500-1000 mL) @cite hammarlund1985acute	</span>|

<br>

@anchor drugs-furosemide
### Diuretic-Furosemide 
PD effects for the diuretic Furosemide are handled differently than other drugs in the %BioGears patient. Localized effects are implemented via a tubular permeability modifier. This effectively simulates Furosemide's effect on the tubular luminal Na-K-Cl co-transporter, inhibiting reabsorption of fluid and ions into the vasculature, as shown in figure 15. The permeability modifier is a function of the PK effects of the drug concentration in the blood plasma. These concentrations are then mapped to a Hill-type sigmoid to determine appropriate tubular reabsorption inhibition via reducing the permeability of the tubular lumen, see @ref RenalMethodology. This effectively increases the urine production rate and ion excretion, and reduces the patient's total blood volume. To see the effects of the drug on the cardiovascular system during ventricular systolic dysfunction, see @ref cardiovascular-validation-conditions "Cardiovascular System".

<center>
<table border="0">
<tr>
    <td><img src="./plots/Drugs/Furosemide_BloodVolume.jpg" width="550"></td>
    <td><img src="./plots/Drugs/Furosemide_ChlorideClearance.jpg" width="550"></td>
</tr>
<tr>
    <td><img src="./plots/Drugs/Furosemide_SodiumClearance.jpg" width="550"></td>
    <td><img src="./plots/Drugs/Furosemide_UrineProductionRate.jpg" width="550"></td>
</tr>
<tr>
    <td colspan="2"><img src="./plots/Drugs/FurosemideLegend.jpg" width="1100"></td>
</tr>
</table>
</center>
<center>
<i>Figure 15. The diuretic furosemide causes an inhibition of reabsorption due to its effect on the tubular lumen co-transporter. Total blood volume decreases as urine production and ion excretion increase. Eventually, as the body clears the drug, urine production and ion excretion both begin to return to normal.</i>
</center><br>

@anchor drugs-conclusions
Conclusions
-----------

In general, the drugs in the %BioGears library have strong agreement with both the published data and subject matter expertise. The biggest limitation lies in the transient response to drugs. Currently, the system tolerances provide a response within 30&ndash;60 seconds for all drugs, regardless of the physiologic onset time. The drug response also wears off quickly for all drugs. It is difficult to specify the desired pharmacodynamic response without a well thought out set of parameters. These issues will be addressed as part of future work on the %BioGears Engine by validating the pharmacokinetic model and implementing and validating a pharmacodynamic model.

These models and the combination of these models represent a positive step forward for drug simulation. The parameters are intuitive and accurate for each drug and additional drugs can be added for an expanded drug library.

@anchor drugs-future
Future Work
===========

Coming Soon
-----------
- Improved plasma concentration computation
- Intoxication
- Expanded drug library

Recommended Improvements
------------------------
- Efficacy-based, receptor-binding pharmacodynamics
- Combinatory effects of kinetics
- Long-term drug effects, including physiological changes
- Additional drugs 
- Improved kinetic model for aerosols and vapors
- Higher fidelity models of other routes, including epithelial cell (integumentary, gastrointestinal) absorption
- Drug sensitivity variation

@anchor drugs-appendices
# Appendices

## Acronyms

MAP - Mean Arterial Pressure

PK - Pharmacokinetic

PD - Pharmacodynamic

SDK - Software Development Kit

SMEs - Subject Matter Experts

Data Model Implementation
-------------------------
@ref DrugSystemTable "Drug"