Scenario XML Files {#ScenarioXMLFile} 
==================

The engine can be used to simulate various physiological scenarios.
The Common Data Model (CDM) provides a Scenario structure that can contain a set of instructions that can be used to drive the engine. 
Below you can see :
- How a scenario is structured in XSD Schema
- XML examples of all the actions, conditions, assessments supported

A Scenario is a 'canned' instruction set with requested data to be output in a comma delimited file that is executed by the engine and will produce the same results data.
'FATAL' is used below to note boundary cases that will result in a fatal exception, stopping the engine.

If you would like execute scenarios, the CDM contains a class, @ref SEScenarioExec, that can execute any scenario with a physiology engine that implements the PhysiologyEngine interface.
The @ref Toolkit, also provides example scenario files and can also execute scenario files.

An example of a basic scenario file is shown below.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
<?xml version="1.0" encoding="UTF-8"?>
<Scenario xmlns="uri:/mil/tatrc/physiology/datamodel" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsdVersion="v16.12" contentVersion="BioGears_6.0.1-beta" xsi:schemaLocation="">
  <Name>InitialStableState</Name>
  <Description>Start the engine at a state, this is for debugging said state</Description>
  <EngineStateFile>./states/StandardMale@0s.xml</EngineStateFile>
  
  <DataRequests>
      <DataRequest xsi:type="PhysiologySystemDataRequestData" Name="HeartRate" Unit="1/min"/>
      <DataRequest xsi:type="PhysiologySystemDataRequestData" Name="RespirationRate" Unit="1/min"/>
    <DataRequest xsi:type="PhysiologySystemDataRequestData" Name="OxygenSaturation" Unit="unitless"/>

      <DataRequest xsi:type="GasCompartmentDataRequestData" Compartment="Carina"       Substance="Oxygen"        Name="PartialPressure" Unit="cmH2O" Precision="0"/>
      <DataRequest xsi:type="GasCompartmentDataRequestData" Compartment="Carina"       Substance="CarbonDioxide" Name="PartialPressure" Unit="cmH2O" Precision="1"/>
          
      <DataRequest xsi:type="LiquidCompartmentDataRequestData" Compartment="Aorta"     Substance="Oxygen"        Name="PartialPressure" Unit="mmHg" Precision="1"/>
      <DataRequest xsi:type="LiquidCompartmentDataRequestData" Compartment="Aorta"     Substance="CarbonDioxide" Name="PartialPressure" Unit="mmHg" Precision="1"/>
  </DataRequests>
   
  <Action xsi:type="AdvanceTimeData">
    <Time value="2" unit="min"/>		
  </Action>
</Scenario>
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The scenario allows for a name and description, but this is not used in execution.
The scenario contains the following execution information:
- What engine state to use
- A list of values to return from the engine
- A list of actions to execute over the course of the run

- - -

## Patient File and optional conditions

While it is recommened to use an Engine State when running a scenario, you do have the option to initialize the engine with a Patient File and optional conditions.
The specified patient file refers to an XML file containing @ref Patient_PatientData information.
Replace the <EngineStateFile> tag with the <InitialParameters> tag like this:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
<?xml version="1.0" encoding="UTF-8"?>
<Scenario xmlns="uri:/mil/tatrc/physiology/datamodel" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsdVersion="v16.12" contentVersion="BioGears_6.0.1-beta" xsi:schemaLocation="">
    <Name>Anemia30</Name>
    <Description>Anemia onset, leading to 30% reduction in hemoblogin content</Description>
    <InitialParameters>
          <PatientFile>StandardMale.xml</PatientFile>
          <Condition xsi:type="ChronicAnemiaData">
              <ReductionFactor value="0.3"/>
          </Condition>
      </InitialParameters>
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

## Patient Conditions

Conditions give instructions to the engine to apply certian changes to the engine to simulate the specified conditions.
The following are links to the Condition class specification along with XML examples of conditions that can be used in making your own scenarios.

#### Chronic Anemia
@copybrief PatientConditions_ChronicAnemiaData
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
PatientCondition {
  ChronicAnemia {
    ReductionFactor { Scalar0To1 {Value: 0.3} }
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### COPD
@copybrief PatientConditions_ChronicObstructivePulmonaryDiseaseData
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
PatientCondition {
  ChronicObstructivePulmonaryDisease {
    BronchitisSeverity { Scalar0To1 {Value: 0.3} }
    EmphysemaSeverity { Scalar0To1 {Value: 0.3} }
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Chronic Pericardial Effusion
@copybrief PatientConditions_ChronicPericardialEffusionData
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
PatientCondition {
  ChronicPericardialEffusion {
    AccumulatedVolume { ScalarVolume {Value: 500 Unit: "mL"} }
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Chronic %Renal Stenosis
@copybrief PatientConditions_ChronicRenalStenosisData
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
PatientCondition {
  ChronicRenalStenosis {
    LeftKidneySeverity { Scalar0To1 {Value: 0.9} }
    RightKidneySeverity { Scalar0To1 {Value: 0.9} }
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Chronic Ventricular Systolic Dysfunction
@copybrief PatientConditions_ChronicVentricularSystolicDysfunctionData
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
PatientCondition {
  ChronicVentricularSystolicDysfunction {}
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Consume Meal
@copybrief PatientConditions_ConsumeMealData
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
PatientCondition {
  ConsumeMeal {
    Meal {
      Nutrition {
        Carbohydrate { ScalarMass {Value: 390.0 Unit: "g"} }
        CarbohydrateDigestionRate { ScalarMassPerTime {Value: 0.5 Unit: "g/min"} }
        Fat { ScalarMass {Value: 90.0 Unit: "g"} }
        FatDigestionRate { ScalarMassPerTime {Value: 0.055 Unit: "g/min"} }
        Protein { ScalarMass {Value: 56.0 Unit: "g"} }
        ProteinDigestionRate { ScalarMassPerTime {Value: 0.071 Unit: "g/min"} }
        Calcium { ScalarMass {Value: 1.0 Unit: "g"} }
        Sodium { ScalarMass {Value: 1.5 Unit: "g"} }
        Water { ScalarVolume {Value: 3.7 Unit: "L"} }
      }
    }
  }
}

or

<!-- file must be in the ./bin/nutrition directory -->
jbw
PatientCondition {
  ConsumeMeal {
    Meal {
      NutritionFile { "Soylent.pba" }
    }
  }
}

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Impaired Alveolar Exchange
@copybrief PatientConditions_ImpairedAlveolarExchangeData
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
PatientCondition {
  ImpairedAlveolarExchange {
    ImpairedSurfaceArea { ScalarArea {Value: 0.3 Unit: "m^2"} }
  }
}

or

PatientCondition {
  ImpairedAlveolarExchange {
    ImpairedFraction { Scalar0To1 {Value: 0.3} }
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Lobar Pneumonia
@copybrief PatientConditions_LobarPneumoniaData
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
PatientCondition {
  LobarPneumonia {
    Severity  { Scalar0To1 {Value: 0.7} }
    LeftLungAffected  { Scalar0To1 {Value: 0.0} }
    RightLungAffected  { Scalar0To1 {Value: 0.67} }
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Initial %Environment
@copybrief EnvironmentConditions_InitialEnvironmentData
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
EnvironmentCondition {
  InitialEnvironmentConditions {
    Conditions {
      SurroundingType: Air
      AirVelocity { ScalarLengthPerTime {Value: 1.0 Unit: "m/s"} }
      AmbientTemperature { ScalarTemperature {Value: 25.0 Unit: "degC"} }
      AtmosphericPressure { ScalarPressure {Value: 542.0 Unit: "mmHg"} }
      ClothingResistance { ScalarHeatResistanceArea {Value: 2.0 Unit: "clo"} }
      Emissivity { Scalar0To1 {Value: 0.9} }
      MeanRadiantTemperature { ScalarTemperature {Value: 25.0 Unit: "degC"} }
      RelativeHumidity { Scalar0To1 {Value: 0.1} }
      RespirationAmbientTemperature { ScalarTemperature {Value: 25.0 Unit: "degC"} }
      AmbientGas { Name: "Nitrogen" Amount { Scalar0To1 {Value: 0.79008} } }
      AmbientGas { Name: "Oxygen" Amount {Scalar0To1 {Value: 0.2095} } }
      AmbientGas { Name: "CarbonDioxide" Amount {Scalar0To1 {Value: 4.0E-4} } }
      AmbientGas { Name: "CarbonMonoxide" Amount {Scalar0To1 {Value: 2.0E-5} } }
      AmbientAerosol { Name: "ForestFireParticulate" Concentration { ScalarMassPerVolume {Value: 2.9 Unit: "mg/m^3"} } } 
    }
  }
}

or

<!-- file must be in the ./bin/environments directory -->
jbw
EnvironmentCondition {
  InitialEnvironmentConditions {
    Conditions {
      ConditionsFile {"Hypobaric3000m.pba"}
    }
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- - - 

## Data Requests

Currently there are four supported types of data requests:

### Physiology System Data

Physiology System data refers to all the data specified by SystemData and its derived types.

At this time, you do not need to specify the system name.
The Name attribute should be set to a System Property name. (e.g., HeartRate)

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
<DataRequest xsi:type="PhysiologySystemDataRequestData" Name="HeartRate" Unit="1/min" />
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

### Compartment Data

Compartments refer to all the data specified on Compartments.
You can read more about compartments @ref CompartmentsInterface "here".

There are two amin types of Compartments, gas and liquid.

Data on the compartment itself: 
The Compartment attribute can be any of the enumerations defined. 
The Name attribute should be set to a Compartment Property name.
The Substance attribute is optional, and the if used the name will refer to a substance quantity property.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
<DataRequest xsi:type="GasCompartmentDataRequestData" Compartment="LeftAlveoli" Name="Pressure" Unit="cmH2O"/>		
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
<DataRequest xsi:type="GasCompartmentDataRequestData" Compartment="LeftAlveoli" Substance="Oxygen" Name="PartialPressure" Unit="mmHg"/>
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
<DataRequest xsi:type="LiquidCompartmentDataRequestData" Compartment="Aorta" Name="Pressure" Unit="mmHg" />
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
<DataRequest xsi:type="LiquidCompartmentDataRequestData" Compartment="Aorta" Substance="Oxygen" Name="PartialPressure" Unit="mmHg"/>
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

### Environment Data

Environment System data refers to all the data specified by @ref Environment_EnvironmentData and its derived types.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
<DataRequest xsi:type="EnvironmentDataRequestData"  Name="ConvectiveHeatLoss"    Unit="W"          Precision="2"/>
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

### Equipment Data

System level data from a piece of equipment

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
<DataRequest xsi:type="EquipmentDataRequestData"  Type="ECG" Name="Lead3ElectricPotential"    Unit="mV"          Precision="0"/>
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

### Substance Data

Substance data is provided about a substance and its current state in the body and on specific anatomy compartments

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
<DataRequest xsi:type="SubstanceDataRequestData" Substance="Morphine" Name="PlasmaConcentration" Unit="ug/mL"/>
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
<DataRequest xsi:type="SubstanceDataRequestData" Substance="Morphine" Compartment="LeftKidneyTissue" Name="MassCleared" Unit="ug"/>
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- - -

## General Actions

Actions give instructions to the engine to define what happens over the course of a scenario. 
Everything from advancing time, to starting a hemorrhage, to administering a drug is an action of some kind. 
The following are links to the Action class specification along with XML examples of actions that can be used in making your own scenarios.

- - -

#### Advance Time

@copybrief Scenario_AdvanceTimeData
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
AdvanceTime 
{
  Time { ScalarTime {Value: 20.0  Unit: "s"} }
}    
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Serialize State
@copybrief Scenario_SerializeStateData
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
<Action xsi:type="SerializeStateData" Type="Save">
		<Filename></Filename><!-- No Filename, engine is going to auto generate a name, something like : StandardMale@0s.xml -->		
  </Action>
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- - -

Patient Insults
---------------
- - -

#### Acute Stress
@copybrief PatientActions_AcuteStressData <br>
Severity value must be >=0.0 and <=1.0 <br>
A severity of 0 removes the action completely.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
PatientAction {
  AcuteStress {
    Severity { Scalar0To1 {Value: 0.3} }
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- - -

#### Apnea
@copybrief PatientActions_ApneaData <br>
Severity value must be >=0.0 and <=1.0 <br>
A severity of 0 removes the action completely.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
PatientAction {
  Apnea {
    Severity { Scalar0To1 {Value: 0.3} }
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- - -

#### Airway Obstruction 
@copybrief PatientActions_AirwayObstructionData <br>
Severity value must be >=0.0 and <=1.0 <br>
A severity of 0 removes the action completely.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
PatientAction {
  AirwayObstruction {
    Severity { Scalar0To1 {Value: 0.3} }
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- - -

#### Asthma Attack
@copybrief PatientActions_AsthmaAttackData <br>
Severity value must be >=0.0 and <=1.0 <br>
A severity of 0 removes the action completely.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
PatientAction {
  AsthmaAttack {
    Severity { Scalar0To1 {Value: 0.3} }
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- - -

#### Brain Injury
@copybrief PatientActions_BrainInjuryData <br>
Severity value must be >=0.0 and <=1.0 <br>
A severity of 0 removes the action completely.<br>
Types : Diffuse, LeftFocal, RightFocal
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
PatientAction {
  BrainInjury {
    Type: LeftFocal
    Severity { Scalar0To1 {Value: 0.3} }
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- - -
		
#### Bronchoconstriction 
@copybrief PatientActions_BronchoconstrictionData <br>
Severity value must be >=0.0 and <=1.0 <br>
A severity of 0 removes the action completely.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
PatientAction {
  Bronchoconstriction {
    Severity { Scalar0To1 {Value: 0.3} }
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- - -

#### Consume Nutrients 
@copybrief PatientActions_ConsumeNutrientsData
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
PatientAction {
  ConsumeNutrients {
    Nutrition {
      Carbohydrate { ScalarMass {Value: 390.0 Unit: "g"} }
      CarbohydrateDigestionRate { ScalarMassPerTime {Value: 0.5 Unit: "g/min"} }
      Fat { ScalarMass {Value: 90.0 Unit: "g"} }
      FatDigestionRate { ScalarMassPerTime {Value: 0.055 Unit: "g/min"} }
      Protein { ScalarMass {Value: 56.0 Unit: "g"} }
      ProteinDigestionRate { ScalarMassPerTime {Value: 0.071 Unit: "g/min"} }
      Calcium { ScalarMass {Value: 1.0 Unit: "g"} }
      Sodium { ScalarMass {Value: 1.5 Unit: "g"} }
      Water { ScalarVolume {Value: 3.7 Unit: "L"} }
    }
  }
}

or

<!-- file must be in the ./bin/nutrition directory -->
jbw
PatientAction {
  ConsumeNutrients {
    NutritionFile { "Soylent.pba" }
    }
  }
}

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- - -

#### Cardiac Arrest 
@copybrief PatientActions_CardiacArrestData
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
PatientAction {
  CardiacArrest {State: On}
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- - -
	
#### Exercise 
@copybrief PatientActions_ExerciseData <br>
An intensity of 0 removes the action completely.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
PatientAction {
  Exercise {
    Intensity { Scalar0To1 {Value: 0.3} }
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- - -
	
#### Hemorrhage 
@copybrief PatientActions_HemorrhageData <br>
The Compartment attribute can be any of the enumerations defined in the enumAnatomy enumeration.<br>
FATAL: Cannot have bleeding rate greater than cardiac output or less than 0
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
PatientAction {
  Hemorrhage { Compartment: "RightLegVascular"
    Rate { ScalarVolumePerTime {Value: 250.0 Unit: "mL/min"} }
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- - -

#### Pericardial Effusion
@copybrief PatientActions_PericardialEffusionData <br>
EffusionRate of the liquid
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
PatientAction {
  PericardialEffusion {
    EffusionRate { ScalarVolumePerTime {Value: 0.1 Unit: "mL/s"} }
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- - -
	
#### Tension Pneumothorax 
@copybrief PatientActions_TensionPneumothoraxData <br>
The Type attribute can be "Open" or "Closed"<br>
The Side attribute can be "Left" or "Right"<br>
Severity value must be >=0.0 and <=1.0 <br>
A severity of 0 removes the action completely.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
PatientAction {
  TensionPneumothorax {
    Type: Open
    Side: Right
    Severity { Scalar0To1 {Value: 0.3} }
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- - -

Patient Interventions
---------------------

- - -
	
#### Chest Compression Force 
@copybrief PatientActions_ChestCompressionForceData <br>
Force is the specific magnitude to perform a compression with.<br>
Note, that patient should be in Cardiac Arrest before performing CPR
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
PatientAction {
  ChestCompressionForce {
    Force { ScalarForce {Value: 100.0 Unit: "N"} }
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- - -
		
#### Chest Compression Force Scale 
@copybrief PatientActions_ChestCompressionForceScaleData <br>
ForceScale value must be >=0.0 and <=1.0<br>
Note, that patient should be in Cardiac Arrest before performing CPR
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
PatientAction {
  ChestCompressionForceScale {
    ForceScale { Scalar0To1 {Value: 0.73} }
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- - -
		
#### Chest Occlusive Dressing 
@copybrief PatientActions_ChestOcclusiveDressingData <br>
The State attribute can be "On" or "Off" <br>
Side is either Left or Right<br>
FATAL: If the side specified does not have a pnumothorax 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
PatientAction {
  ChestOcclusiveDressing {
    State: On
    Side: Right
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- - -

#### Conscious Respiration 
@copybrief PatientActions_ConsciousRespirationData <br>
This action can contain 1 or more commands :
- @copybrief PatientActions_ForcedInhaleData
- @copybrief PatientActions_ForcedExhaleData
- @copybrief PatientActions_BreathHoldData
- @copybrief PatientActions_UseInhalerData

<br>
Commands will be processed in order.
The first commands will be proceesed instantly
When it has completed (run through it's Period),
the next command will be processed.
Other actions will be processed while these commands
are processed or waiting to be processed.
You may want to advance time for the sum of the 
command periods to ensure the body is doing what you 
expect it to.. Or not, depending on how you want 
the system to react.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
PatientAction {
  ConsciousRespiration {
    Command {
      ForcedExhale {
        ExpiratoryCapacityFraction { Scalar0To1 {Value: 1.0} }
        Period { ScalarTime {Value: 3.0 Unit: "s"} }
      }
    }
    Command {
      ForcedInhale {
        InspiratoryCapacityFraction { Scalar0To1 {Value: 0.5} }
        Period { ScalarTime {Value: 5.0 Unit: "s"} }
      }
    }
    Command {
      UseInhaler {}
    }
    Command {
      BreathHold {
        Period { ScalarTime {Value: 10.0 Unit: "s"} }
      }
    }
  }
}


~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- - -

#### Intubation 
@copybrief PatientActions_IntubationData <br>
Note: In order to 'turn off' an intubation, use'Off' as the Type  <br>
Types : Off, Esophageal, LeftMainstem, RightMainstem, Tracheal
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
PatientAction {
  Intubation {Type: Tracheal}
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- - -

#### Mechanical Ventilation 
@copybrief PatientActions_MechanicalVentilationData <br>
You may provide Pressure and/or Flow. <br>
If you do not provide GasFractions, the environment gas fractions will be used. <br>
If you do provide Gas Fractions, they must add up to 1.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
PatientAction {
  MechanicalVentilation { State: On
    Flow { ScalarVolumePerTime {Value: 1.0 Unit: "mL/s"} }
    Pressure { ScalarPressure {Value: 10.0 Unit: "cmH2O"} }
    GasFraction { Name: "Oxygen"
      Amount { Scalar0To1 {Value: 0.3} } }
    GasFraction { Name: "CarbonDioxide"
      Amount { Scalar0To1 {Value: 0.1} } }
    GasFraction { Name: "Nitrogen"
      Amount { Scalar0To1 {Value: 0.6} } }
  }
}

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- - -
	
#### Needle Decompression 
@copybrief PatientActions_NeedleDecompressionData <br>
The Side attribute can be "Left" or "Right"<br>
The State attribute can be "On" or "Off"
FATAL: If the side specified does not have a pnumothorax 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
PatientAction {
  NeedleDecompression {
    State: On
    Side: Right
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Urinate 
@copybrief PatientActions_UrinateData <br>
Action to empty the bladder. if not emptied, 
it will empty and throw an event.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
PatientAction {
  Urinate {}
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- - -
	
#### Substance Bolus  
@copybrief PatientActions_SubstanceBolusData

The AdminRoute can be one of:
- "Intravenous"
- "Intramuscular"
- "Subcutaneous"
- "Oral"
- "Rectal"
- "Inhaled"

The Substance element should be set to a name of any of the %Substances.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
PatientAction {
  SubstanceBolus { 
    AdministrationRoute: Intravenous
    Substance: "Succinylcholine"
    Concentration { ScalarMassPerVolume {Value: 4820.0 Unit: "ug/mL"} }
    Dose { ScalarVolume {Value: 30.0 Unit: "mL"} }
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- - -
	
#### Substance Compound Infusion Fluids 
@copybrief PatientActions_SubstanceCompoundInfusionData <br>
The Substance Compound element should be set to a name of any of the %Substances Compounds. <br>
Set Rate to 0 to remove Action
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
PatientAction {
  SubstanceCompoundInfusion { 
    SubstanceCompound: "Saline"
    BagVolume { ScalarVolume {Value: 500.0 Unit: "mL"} }
    Rate { ScalarVolumePerTime {Value: 100.0 Unit: "mL/min"} }
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- - -
	
#### Substance Infusion 
@copybrief PatientActions_SubstanceInfusionData <br>
The Substance element should be set to a name of any of the %Substances. <br>
Set Rate to 0 to remove Action
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
PatientAction {
  SubstanceInfusion { 
   Substance: "Succinylcholine"
    Concentration { ScalarMassPerVolume {Value: 5000.0 Unit: "ug/mL"} }
    Rate { ScalarVolumePerTime {Value: 100.0 Unit: "mL/min"} }
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- - -

Anesthesia Machine State
------------------------

- - -
#### Anesthesia Machine Configuration 
@copybrief AnesthesiaActions_AnesthesiaMachineConfigurationData <br>
NOTE: Each field is optional. <br>
Connection can be one of : Off, Mask, Tube <br>
Patient must be intubated to be connected as Tube <br>
Anesthesia machine will be disconneted if intubation is removed. <br>
Patient cannot be intubated to be connected as Mask <br>
Anesthesia machine will be disconneted if patient is then intubated. <br>
Cannot have inhaler and anesthesia machine on at the same time <br>
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
AnesthesiaMachineAction {
  Configuration {
    Configuration {
      Connection: Mask
      InletFlow { ScalarVolumePerTime {Value: 5.0 Unit: "L/min"} }
      InspiratoryExpiratoryRatio { Scalar {Value="0.5"} }
      OxygenFraction { Scalar0To1 {Value="0.25"} }
      OxygenSource: Wall
      PositiveEndExpiredPressure { ScalarPressure { Value: 1.0 Unit: "cmH2O"} }
      PrimaryGas: Nitrogen      
      RespiratoryRate { ScalarFrequency {Value: 16.0 Unit: "1/min"} }
      VentilatorPressure { ScalarPressure { Value: 10.5 Unit: "cmH2O"} }
      OxygenBottleOne {
        Volume { ScalarVolume {Value: 660.0 Unit: "L"} }
      }
      OxygenBottleTwo {
        Volume { ScalarVolume {Value: 700.0 Unit: "L"} }
      }
    }
  }
}

jbw - file?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
AnesthesiaMachineAction {
  Configuration {
    Configuration {
      Connection: Off
    }
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	
AnesthesiaMachineAction {
  Configuration {
    Configuration {
      RightChamber {
        State: On
        SubstanceFraction { Scalar0To1 {Value="0.04"} }
        Substance: "Desflurane"
      }
      LeftChamber {
        State: Off
        SubstanceFraction { Scalar0To1 {Value="0.01"} }
        Substance: "Desflurane"
      }
    }
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	
- - -

Anesthesia Machine Incidents
----------------------------

- - -
	
#### Oxygen TankPressure Loss 
@copybrief AnesthesiaActions_OxygenTankPressureLossData <br>
The State attribute can be "On" or "Off"
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
AnesthesiaMachineAction {
  OxygenTankPressureLoss {State: On}
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- - -
	
#### Oxygen Wall Port Pressure Loss 
@copybrief AnesthesiaActions_OxygenWallPortPressureLossData <br>
The State attribute can be "On" or "Off"
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
AnesthesiaMachineAction {
  OxygenWallPortPressureLoss {State: On}
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- - -

Anesthesia Machine Failures
---------------------------

- - -
	
#### Expiratory Valve Leak 
@copybrief AnesthesiaActions_ExpiratoryValveLeakData <br>
The State attribute can be "On" or "Off"<br>
Severity value must be >=0.0 and <=1.0
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
AnesthesiaMachineAction {
  ExpiratoryValveLeak {
    Severity { Scalar0To1 {Value: 0.5} }
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- - -
	
#### Expiratory Valve Obstruction 
@copybrief AnesthesiaActions_ExpiratoryValveObstructionData <br>
The State attribute can be "On" or "Off"<br>
Severity value must be >=0.0 and <=1.0
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
AnesthesiaMachineAction {
  ExpiratoryValveObstruction {
    Severity { Scalar0To1 {Value: 0.5} }
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- - -
	
#### Inspiratory Valve Leak 
@copybrief AnesthesiaActions_InspiratoryValveLeakData <br>
The State attribute can be "On" or "Off"<br>
Severity value must be >=0.0 and <=1.0
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
AnesthesiaMachineAction {
  InspiratoryValveLeak {
    Severity { Scalar0To1 {Value: 0.5} }
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- - -
	
#### Inspiratory Valve Obstruction 
@copybrief AnesthesiaActions_InspiratoryValveObstructionData <br>
The State attribute can be "On" or "Off"<br>
Severity value must be >=0.0 and <=1.0
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
AnesthesiaMachineAction {
  InspiratoryValveObstruction {
    Severity { Scalar0To1 {Value: 0.5} }
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- - -
	
#### Mask Leak 
@copybrief AnesthesiaActions_MaskLeakData <br>
The State attribute can be "On" or "Off"<br>
Severity value must be >=0.0 and <=1.0
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
AnesthesiaMachineAction {
  MaskLeak {
    Severity { Scalar0To1 {Value: 0.5} }
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- - -
	
#### Soda Lime Failure 
@copybrief AnesthesiaActions_SodaLimeFailureData <br>
The State attribute can be "On" or "Off"<br>
Severity value must be >=0.0 and <=1.0
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
AnesthesiaMachineAction {
  SodaLimeFailure {
    Severity { Scalar0To1 {Value: 0.5} }
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- - -
	
#### Tube Cuff Leak 
@copybrief AnesthesiaActions_TubeCuffLeakData <br>
The State attribute can be "On" or "Off"<br>
Severity value must be >=0.0 and <=1.0
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
AnesthesiaMachineAction {
  TubeCuffLeak {
    Severity { Scalar0To1 {Value: 0.5} }
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- - -
	
#### Vaporizer Failure 
@copybrief AnesthesiaActions_VaporizerFailureData <br>
The State attribute can be "On" or "Off"<br>
Severity value must be >=0.0 and <=1.0
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
AnesthesiaMachineAction {
  VaporizerFailure {
    Severity { Scalar0To1 {Value: 0.5} }
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- - -
	
#### Ventilator Pressure Loss 
@copybrief AnesthesiaActions_VentilatorPressureLossData <br>
The State attribute can be "On" or "Off"<br>
Severity value must be >=0.0 and <=1.0
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
AnesthesiaMachineAction {
  VentilatorPressureLoss {
    Severity { Scalar0To1 {Value: 0.5} }
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- - -
	
#### Y Piece Disconnect 
@copybrief AnesthesiaActions_YPieceDisconnectData <br>
The State attribute can be "On" or "Off"<br>
Severity value must be >=0.0 and <=1.0 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
AnesthesiaMachineAction {
  YPieceDisconnect {
    Severity { Scalar0To1 {Value: 0.5} }
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- - -

%Inhaler State
------------------------

#### %Inhaler Configuration 
@copybrief InhalerActions_InhalerConfigurationData <br>
FATAL: Cannot have inhaler and anesthesia machine on at the same time
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
InhalerAction {
  Configuration {
    Configuration {
      Substance: "Oxygen"
      MeteredDose { ScalarMass {Value: 90.0 Unit: "ug"} }
      NozzleLoss { Scalar0To1 {Value: 0.04} }
      SpacerVolume { ScalarVolume {Value: 0.1 Unit: "L"} }
    }
  }
}

jbw - file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- - -

%Environment 
------------------------

- - -
	
#### %Environment Configuration State <br>
@copybrief EnvironmentActions_EnvironmentChangeData <br>
NOTE: Each field is optional.
jbw - mention CO and particulates (e.g., smoke)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
EnvironmentAction {
  Conditions {
    Conditions {
      SurroundingType: Air
      AirVelocity { ScalarLengthPerTime {Value: 1.0 Unit: "m/s"} }
      AmbientTemperature { ScalarTemperature {Value: 25.0 Unit: "degC"} }
      AtmosphericPressure { ScalarPressure {Value: 542.0 Unit: "mmHg"} }
      ClothingResistance { ScalarHeatResistanceArea {Value: 2.0 Unit: "clo"} }
      Emissivity { Scalar0To1 {Value: 0.9} }
      MeanRadiantTemperature { ScalarTemperature {Value: 25.0 Unit: "degC"} }
      RelativeHumidity { Scalar0To1 {Value: 0.1} }
      RespirationAmbientTemperature { ScalarTemperature {Value: 25.0 Unit: "degC"} }
      AmbientGas { Name: "Nitrogen" Amount { Scalar0To1 {Value: 0.79008} } }
      AmbientGas { Name: "Oxygen" Amount {Scalar0To1 {Value: 0.2095} } }
      AmbientGas { Name: "CarbonDioxide" Amount {Scalar0To1 {Value: 4.0E-4} } }
      AmbientGas { Name: "CarbonMonoxide" Amount {Scalar0To1 {Value: 2.0E-5} } }
      AmbientAerosol { Name: "ForestFireParticulate" Concentration { ScalarMassPerVolume {Value: 2.9 Unit: "mg/m^3"} } } 
    }
  }
}

or

<!-- file must be in the ./bin/environments directory -->
jbw
EnvironmentCondition {
  InitialEnvironmentConditions {
    Conditions {
      ConditionsFile {"Hypobaric3000m.pba"}
    }
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- - -

#### Thermal Application <br>
@copybrief EnvironmentActions_ThermalApplicationData <br>
You must provide at least 1 activity, but up can also 
apply up-to all 3 in one action.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
EnvironmentAction {
  ThermalApplication {
    ActiveHeating {
      Power { ScalarPower {Value: 500.0 Unit: "BTU/hr"} }
      SurfaceAreaFraction { Scalar0To1 {Value: 0.2} }
    }
    ActiveCooling {
      Power { ScalarPower {Value: 500.0 Unit: "BTU/hr"} }
      SurfaceArea { ScalarArea {Value: 0.1 Unit: "m^2"} }
    }
    AppliedTemperature { 
      State: On
      Temperature { ScalarTemperature {Value: 30.0 Unit: "degF"} }
      SurfaceAreaFraction { Scalar0To1 {Value: 1.0} }
    }
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
