     

# Latest Release Notes

Our latest deployment is still in a beta phase, and is intended to be an intermediate release to 
showcase the capabilities of the %BioGears&reg; Physiology Engine. 
The current version of the software includes examples of all types
of engine interfaces, but does not include all of the functionality or
physiologic systems that will be present in the final product. This
version of the software is meant to elicit feedback and enhance
community involvement in establishing end product expectations.

- - -

@insert MainPageFAQ.md

## Have more questions?

See the @ref ExtraFAQ for any other questions you may have.

- - -

## Programmatics

%BioGears is being developed under the <a href="http://www.tatrc.org/">TATRC</a> funded project:
W81XWH-13-2-0068.

Disclaimer:

> This work is supported by the US Army Medical Research and Materiel Command. The views, opinions and/or findings contained in this report are those of the author(s) and should not be construed as an official Department of the Army position, policy, or decision unless so designated by other documentation.

%BioGears is released under this @ref License.

%BioGears has @ref published papers and abstracts on several systems and clinical scenarios. 

- - -

## What's New in ver 6.1.0/6.1.1 (March 10, 2017)

The latest deployment includes the following notable updates:
<br>Note: 6.1.1 only contains a few minor bug fixes (no features)
- General bug fixes, system improvements, and tools/solver improvements
- Improved Epinephrine methodology
- Improved Pupillary State for both Drug and %Nervous methodology
- Improved %Renal Tubuloglomerular Feedback
- Added cardiovascular chemoreceptor feedback
- Added Diuretic drug effects (Furosemide)
- Aerosolization of Solids and Liquids
  - Improves administration of Albuterol
  - New Smoke Particulate substance and smoke inhalation modeling
- Carbon Monoxide support
- New data requests and events
- New Conditions
  - Impaired Alveolar Exchange
- New Actions
  - Acute Stress
  - Apnea
  - Brain Injury
  - Intubation now supports Leftmainstem, Rightmainstem, Esopageal, and Tracheal types
  - Mechanical Ventilation

(Interested in a previous @ref version?)

- - -
@anchor known-issues
## Known Issues and Limitations
The following are known issues with the current version of the software:
- Lack of a full sympathetic/parasympathetic nervous system
- Extravascular fluid exchange model is incomplete
- Peripheral resistance currently does not scale with core temperature
- Only tested a simulation up to 12 hours in length (No sleep model)
- Limited Consumption model
	- Limited number of macronutrients available
	- Limited conversion and use within the %BioGears engine

- - -

## Tentative Near-Term Timeline

These are the planned updates:
- Bug fixes
- Intoxications
- Exocrine and secretory functions
- Starvation and dehydration states
- Nerve agents
- Improved modularity

- - -

## Credits
<b>%BioGears @ref version 6.1.0-beta</b>

<b><a href="http://www.ara.com/">Applied Research Associates Inc.</a></b>

*Principal Investigator:* Jeff Webb

*Project Manager:* Jenn Carter

*Software Architect:* Aaron Bray

*Physiology Modeler:* Rodney Metoyer

*Physiology Modeler:* Ausin Baird, PhD

*Physiology Modeler:* Bennett Welch

*Software Developer:* David Byrd

*Website Engineer:* Anthony Hamilton

**Consultants:**

Bryan Bergeron, MD (<b><a href="http://bryanbergeron.com/">Archetype Technologies, Inc.</a></b>)

Nicholas Moss, PhD

Stephen Mangum, PharmD

**Past Contributors:**

Rachel Clipp, PhD

Jerry Heneghan

Yeshitila Gebremichael, PhD

Zack Swarm

Pat Russler

Beth Smith

Paul Rutledge

Federico Menozzi

Alex Somers

Katie Carter

Cassidy Limer

<b><a href="https://pharmacy.unc.edu/">UNC Eshelman School of Pharmacy:</a></b><br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Alexander Tropsha, PhD<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Kimberly Brouwer, PhD<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Denise Rhoney, PharmD<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Eugene Muratove, PhD<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Daniel Gonzalez, PharmD, PhD <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Alexander Golbraikh, PhD<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Vadryn Pierre, PharmD<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Nilay Thakakkar, PhD<br>

**Acknowledgement:**

The %BioGears team would like to thank the following individuals for providing programmatic guidance and oversight for the U.S. Government on this project:  
	
Jan Harris, PhD, RN<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; *Director, Joint Program Committee-1*<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; *U.S. Army Medical Research and Materiel Command (USAMRMC)*<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; *Fort Detrick, Maryland*

Kevin Kunkler, MD<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; *Portfolio Manager, Joint Program Committee-1*<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; *U.S. Army Medical Research and Materiel Command (USAMRMC)*<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; *Fort Detrick, Maryland*<br>

J. Harvey Magee<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; *Manager, Medical Modeling and Simulation Innovation Center (MMSIC)*<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; *Telemedicine & Advanced Technology Research Center (TATRC)*<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; *US Army Medical Research & Materiel Command (USAMRMC)*<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; *Fort Detrick, Maryland*<br>

Geoffrey T. Miller, MS<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; *Assistant Professor, Eastern Virginia Medical School*<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; *Research Scientist, Medical Modeling and Simulation Innovation Center (MMSIC)*<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; *Telemedicine & Advanced Technology Research Center (TATRC)*<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; *US Army Medical Research & Materiel Command (USAMRMC)*<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; *Fort Detrick, Maryland*<br>

Thomas B. Talbot, MD<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; *Principal Medical Expert - USC Institute for Creative Technologies*<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; *Associate Research Professor of Medical Education - Keck School of Medicine, USC*<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; *Playa Vista, CA*<br>

**Software Tools:**

%BioGears leverages the following: @ref Credits.

---

## Dedication

This software is dedicated to **N. Ty Smith, M.D.**, physician, professor, mentor, friend, and founding director of the Pacific Academy of Ecclesiastical Music (PACEM).

Dr. Smith was born in Iowa and graduated from Harvard College and Harvard Medical School. Dr. Smith served on the faculties at Stanford Medical Center and the University of California at San Diego. He was a Visiting Professor at the University of Washington, Institute of Medical Physics in Holland, University of Wisconsin, and University of Otago in New Zealand. Dr. Smith also served at Children's Medical Center in Boston, Massachusetts, Massachusetts General Hospital, U.S. Naval Hospital in Portsmouth, Virginia, U.S. Veterans Administration Hospital in San Diego, and Dunedin Hospital in New Zealand.

Dr. Smith, along with Ken Starko M.Sc., created "Body Simulation" in the 1990s. Body Simulation models and their interfaces were used for pharmacologic experimentation, testing, teaching, and training by device manufacturers, pharmaceutical companies, professional associations, and government agencies. %BioGears builds directly from this vision and legacy.

It was Dr. Smith's fervent wish that his work continue long into the future to advance scientific discovery, improve the safety of healthcare, and ultimately save lives.
 
*The %BioGears Team*<br>
*Raleigh North Carolina, September 2014*


@page errors Errors

@page events Events

