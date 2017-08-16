/**************************************************************************************
Copyright 2015 Applied Research Associates, Inc.
Licensed under the Apache License, Version 2.0 (the "License"); you may not use
this file except in compliance with the License. You may obtain a copy of the License
at:
http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software distributed under
the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License.
**************************************************************************************/
#define _USE_MATH_DEFINES

#include "EngineTest.h"
#include "Controller/Controller.h"
#include "circuit/fluid/SEFluidCircuit.h"
#include "substance/SESubstanceFraction.h"
#include "compartment/SECompartmentManager.h"
#include "compartment/fluid/SEGasCompartmentGraph.h"
#include "compartment/substances/SEGasSubstanceQuantity.h"
#include "properties/SEScalarPressure.h"
#include "properties/SEScalar0To1.h"
#include "properties/SEScalarVolume.h"
#include "properties/SEScalarVolumePerTime.h"
#include "properties/SEScalarFlowCompliance.h"
#include "properties/SEScalarTime.h"
#include "properties/SEScalarInverseVolume.h"
#include "properties/SEScalarMassPerVolume.h"
#include "patient/SEPatient.h"
#include "utils/DataTrack.h"
#include <math.h>

void PulseEngineTest::RespiratoryCircuitAndTransportTest(RespiratoryConfiguration config, const std::string& sTestDirectory)
{
  TimingProfile tmr;
  tmr.Start("Test");
  //Output files
  DataTrack outTrkCircuit;
  DataTrack outTrkGraph;
  DataTrack aerosolGraphTrk;
  std::ofstream fileCircuit;
  std::ofstream fileGraph;
  std::ofstream fAerosolGraph;

  PulseController pc(sTestDirectory + "/RespiratoryCircuitAndTransportTest.log");
  pc.GetPatient().LoadFile("./patients/StandardMale.pba");
  pc.SetupPatient();
  pc.m_Config->EnableRenal(cdm::eSwitch::Off);
  pc.m_Config->EnableTissue(cdm::eSwitch::Off); 
  pc.CreateCircuitsAndCompartments();
  pc.GetSubstances().InitializeGasCompartments();
  SEEnvironmentalConditions& env = pc.GetEnvironment().GetConditions();

  SEFluidCircuit* rCircuit = nullptr;
  SEGasCompartmentGraph* rGraph = nullptr;
  SELiquidCompartmentGraph* aGraph = nullptr;
  std::string sCircuitFileName;
  std::string sTransportFileName;
  std::string sAerosolTxptFileName;
  if (config == RespiratorySolo)
  {
    rCircuit = &pc.GetCircuits().GetRespiratoryCircuit();
    rGraph = &pc.GetCompartments().GetRespiratoryGraph();
    aGraph = nullptr;
    sCircuitFileName = "/RespiratoryCircuitOutput.txt";
    sTransportFileName = "/RespiratoryTransportOutput.txt";
    sAerosolTxptFileName = "";
  }
  else if (config == RespiratoryWithInhaler)
  {
    rCircuit = &pc.GetCircuits().GetRespiratoryAndInhalerCircuit();
    rGraph = &pc.GetCompartments().GetRespiratoryAndInhalerGraph();
    aGraph = &pc.GetCompartments().GetAerosolAndInhalerGraph();
    sCircuitFileName = "/RespiratoryAndInhalerCircuitOutput.txt";
    sTransportFileName = "/RespiratoryAndInhalerTransportOutput.txt";
    sAerosolTxptFileName = "/AerosolInhalerTransportOutput.txt";

    // Get an aerosolized substance
    SESubstance* albuterol = pc.GetSubstances().GetSubstance("Albuterol");
    if (albuterol == nullptr)
    {
      pc.Error("Could not find the aerosol substance : Albuterol");
    }
    else
    {
      pc.GetSubstances().AddActiveSubstance(*albuterol);
      SELiquidCompartment* mouthpiece = pc.GetCompartments().GetLiquidCompartment(pulse::InhalerCompartment::Mouthpiece);
      mouthpiece->GetSubstanceQuantity(*albuterol)->GetMass().SetValue(90, MassUnit::ug);
      mouthpiece->Balance(BalanceLiquidBy::Mass);
    }
  }
  else if (config == RespiratoryWithMechanicalVentilator)
  {
    rCircuit = &pc.GetCircuits().GetRespiratoryAndMechanicalVentilatorCircuit();
    rGraph = &pc.GetCompartments().GetRespiratoryAndMechanicalVentilatorGraph();
    aGraph = nullptr;
    sCircuitFileName = "/RespiratoryAndMechanicalVentilatorCircuitOutput.txt";
    sTransportFileName = "/RespiratoryAndMechanicalVentilatorTransportOutput.txt";
    sAerosolTxptFileName = "";
  }
  else
  {
    return;
  }

  SEFluidCircuitPath *driverPath = rCircuit->GetPath(pulse::RespiratoryPath::EnvironmentToRespiratoryMuscle);
  SEGasTransporter    gtxpt(VolumePerTimeUnit::L_Per_s, VolumeUnit::L, VolumeUnit::L, NoUnit::unitless, pc.GetLogger());
  SELiquidTransporter ltxpt(VolumePerTimeUnit::mL_Per_s, VolumeUnit::mL, MassUnit::ug, MassPerVolumeUnit::ug_Per_mL, pc.GetLogger());
  SEFluidCircuitCalculator calc(FlowComplianceUnit::L_Per_cmH2O, VolumePerTimeUnit::L_Per_s, FlowInertanceUnit::cmH2O_s2_Per_L, PressureUnit::cmH2O, VolumeUnit::L, FlowResistanceUnit::cmH2O_s_Per_L, pc.GetLogger());
  
  //Set the reference not pressure to the standard environment
  //This is needed because we're not setting the Environment during initialization in this unit test
  rCircuit->GetNode(pulse::EnvironmentNode::Ambient)->GetNextPressure().Set(env.GetAtmosphericPressure());
  rCircuit->GetNode(pulse::EnvironmentNode::Ambient)->GetPressure().Set(env.GetAtmosphericPressure());
  //Precharge the stomach to prevent negative volume
  rCircuit->GetNode(pulse::RespiratoryNode::Stomach)->GetNextPressure().Set(env.GetAtmosphericPressure());
  rCircuit->GetNode(pulse::RespiratoryNode::Stomach)->GetPressure().Set(env.GetAtmosphericPressure());

  //Circuit Analysis Test --------------------------------------------------
  //Execution parameters
  double time = 0;
  double deltaT_s = 1.0 / 90.0;
  double runTime_min = 10.0;
  //Drive waveform parameters
  double period = 5.0;
  double alpha = (2 * M_PI) / (period);
  double driverPressure_cmH2O = 0.0;
  double amplitude_cmH2O = 6.0;
  double yOffset = -12.0;

  for (unsigned int i = 0; i < runTime_min * 60.0 / deltaT_s; i++)
  {
    //PreProcess - Push driver pressure and  variable compliance data into the Circuit
    driverPressure_cmH2O = yOffset + amplitude_cmH2O * sin(alpha * time);   //compute new pressure
    driverPath->GetNextPressureSource().SetValue(driverPressure_cmH2O, PressureUnit::cmH2O);

    //Process - Execute the circuit
    calc.Process(*rCircuit, deltaT_s);
    //Execute the substance transport function
    gtxpt.Transport(*rGraph, deltaT_s);
    // Do it again for aerosols
    if(aGraph!=nullptr)
      ltxpt.Transport(*aGraph, deltaT_s);
    //convert 'Next' values to current
    calc.PostProcess(*rCircuit);

    outTrkCircuit.Track(time, *rCircuit);
    outTrkGraph.Track(time, *rGraph);
    if(aGraph!=nullptr)
      aerosolGraphTrk.Track(time, *aGraph);
    time += deltaT_s;

    if (i == 0)
    {
      outTrkCircuit.CreateFile(std::string(sTestDirectory + sCircuitFileName).c_str(), fileCircuit);
      outTrkGraph.CreateFile(std::string(sTestDirectory + sTransportFileName).c_str(), fileGraph);
      if (aGraph != nullptr)
        aerosolGraphTrk.CreateFile(std::string(sTestDirectory + sAerosolTxptFileName).c_str(), fAerosolGraph);
    }
    outTrkCircuit.StreamTrackToFile(fileCircuit);
    outTrkGraph.StreamTrackToFile(fileGraph);
    if (aGraph != nullptr)
      aerosolGraphTrk.StreamTrackToFile(fAerosolGraph);
  }
  fileCircuit.close();
  fileGraph.close();
  fAerosolGraph.close();
  std::stringstream ss;
  ss << "It took " << tmr.GetElapsedTime_s("Test") << "s to run";
  pc.GetLogger()->Info(ss.str(), "RespiratoryCircuitAndTransportTest");
}

void PulseEngineTest::RespiratoryCircuitAndTransportTest(const std::string& sTestDirectory)
{
  RespiratoryCircuitAndTransportTest(RespiratorySolo, sTestDirectory);
}

void PulseEngineTest::RespiratoryWithInhalerCircuitAndTransportTest(const std::string& sTestDirectory)
{
  RespiratoryCircuitAndTransportTest(RespiratoryWithInhaler, sTestDirectory);
}

void PulseEngineTest::RespiratoryWithMechanicalVentilatorCircuitAndTransportTest(const std::string& sTestDirectory)
{
  RespiratoryCircuitAndTransportTest(RespiratoryWithMechanicalVentilator, sTestDirectory);
}

void PulseEngineTest::RespiratoryDriverTest(const std::string& sTestDirectory)
{
  TimingProfile tmr;
  tmr.Start("Test");
  PulseController pc(sTestDirectory + "/RespiratoryDriverTest.log");
  pc.GetPatient().LoadFile("./patients/StandardMale.pba");
  pc.SetupPatient();
  pc.m_Config->EnableRenal(cdm::eSwitch::Off);
  pc.m_Config->EnableTissue(cdm::eSwitch::Off);
  pc.CreateCircuitsAndCompartments();
  SEEnvironmentalConditions env(pc.GetSubstances());
  env.LoadFile("./environments/Standard.pba");
  SEGasCompartment* cEnv = pc.GetCompartments().GetGasCompartment(pulse::EnvironmentCompartment::Ambient);
  for (SESubstanceFraction* subFrac : env.GetAmbientGases())
  {
    pc.GetSubstances().AddActiveSubstance(subFrac->GetSubstance());
    cEnv->GetSubstanceQuantity(subFrac->GetSubstance())->GetVolumeFraction().Set(subFrac->GetFractionAmount());
  }
  pc.GetSubstances().InitializeGasCompartments();

  DataTrack trk1;  
  SEFluidCircuit& RespCircuit = pc.GetCircuits().GetRespiratoryCircuit();
  SEFluidCircuitCalculator calc(FlowComplianceUnit::L_Per_cmH2O, VolumePerTimeUnit::L_Per_s, FlowInertanceUnit::cmH2O_s2_Per_L, PressureUnit::cmH2O, VolumeUnit::L, FlowResistanceUnit::cmH2O_s_Per_L, pc.GetLogger());

  double deltaT_s = 1.0 / 90.0;

  SEFluidCircuitPath* driverPressurePath = RespCircuit.GetPath(pulse::RespiratoryPath::EnvironmentToRespiratoryMuscle);
  SEFluidCircuitPath* rightPleuralToRespiratoryMuscle = RespCircuit.GetPath(pulse::RespiratoryPath::RightPleuralToRespiratoryMuscle);
  SEFluidCircuitPath* leftPleuralToRespiratoryMuscle = RespCircuit.GetPath(pulse::RespiratoryPath::LeftPleuralToRespiratoryMuscle);

  SEFluidCircuitNode* rightPleuralNode = RespCircuit.GetNode(pulse::RespiratoryNode::RightPleural);
  SEFluidCircuitNode* leftPleuralNode = RespCircuit.GetNode(pulse::RespiratoryNode::LeftPleural);
  SEFluidCircuitNode* rightDeadSpaceNode = RespCircuit.GetNode(pulse::RespiratoryNode::RightAnatomicDeadSpace);
  SEFluidCircuitNode* leftDeadSpaceNode = RespCircuit.GetNode(pulse::RespiratoryNode::LeftAnatomicDeadSpace);
  SEFluidCircuitNode* rightAlveoliNode = RespCircuit.GetNode(pulse::RespiratoryNode::RightAlveoli);
  SEFluidCircuitNode* leftAlveoliNode = RespCircuit.GetNode(pulse::RespiratoryNode::LeftAlveoli);

  RespCircuit.GetNode(pulse::EnvironmentNode::Ambient)->GetNextPressure().SetValue(760, PressureUnit::mmHg);

  driverPressurePath->GetNextPressureSource().SetValue(0.0, PressureUnit::cmH2O);
  double PressureIncrement_cmH2O = 0.1;
  double DriverPressure_cmH2O = 0.0;
  bool bSettled = false;
  bool bIRVReached = false;
  bool bRVReached = false;
  int iTime = 0;

  while (!bIRVReached)
  {
    double TotalVolume_L = 0.0;
    double PreviousTotalVolume_L = 0.0;
    while (!bSettled)
    {
      //Set the driver pressure
      //Note: the driver pressure should be negative
    driverPressurePath->GetNextPressureSource().SetValue(DriverPressure_cmH2O, PressureUnit::cmH2O);

      //Variable compliance feedback
      //TODO: Figure out how to use that actual Respiratory function.  For now we'll just copy and paste it in.
    double dRightPleuralCompliance = rightPleuralToRespiratoryMuscle->GetNextCompliance().GetValue(FlowComplianceUnit::L_Per_cmH2O);
    double dLeftPleuralCompliance = leftPleuralToRespiratoryMuscle->GetNextCompliance().GetValue(FlowComplianceUnit::L_Per_cmH2O);
    double dRightPleuralVolumeBaseline = rightPleuralNode->GetVolumeBaseline().GetValue(VolumeUnit::L);
    double dLeftPleuralVolumeBaseline = leftPleuralNode->GetVolumeBaseline().GetValue(VolumeUnit::L);
    double dRightPleuralVolume = rightPleuralNode->GetNextVolume().GetValue(VolumeUnit::L);
    double dLeftPleuralVolume = leftPleuralNode->GetNextVolume().GetValue(VolumeUnit::L);

    dRightPleuralCompliance = (dRightPleuralVolume - dRightPleuralVolumeBaseline) * 5.0 * dRightPleuralCompliance + dRightPleuralCompliance;
    dLeftPleuralCompliance = (dLeftPleuralVolume - dLeftPleuralVolumeBaseline) * 5.0 * dLeftPleuralCompliance + dLeftPleuralCompliance;

    dRightPleuralCompliance = LIMIT(dRightPleuralCompliance, 1e-6, 0.05);
    dLeftPleuralCompliance = LIMIT(dLeftPleuralCompliance, 1e-6, 0.05);

    rightPleuralToRespiratoryMuscle->GetNextCompliance().SetValue(dRightPleuralCompliance, FlowComplianceUnit::L_Per_cmH2O);
    leftPleuralToRespiratoryMuscle->GetNextCompliance().SetValue(dLeftPleuralCompliance, FlowComplianceUnit::L_Per_cmH2O);


      //Process the circuit
      calc.Process(RespCircuit, deltaT_s);
      //Advance time
      calc.PostProcess(RespCircuit);

      //Calculate the total lung volume
      TotalVolume_L =
        leftDeadSpaceNode->GetNextVolume(VolumeUnit::L) +
        leftAlveoliNode->GetNextVolume(VolumeUnit::L) +
        rightDeadSpaceNode->GetNextVolume(VolumeUnit::L) +
        rightAlveoliNode->GetNextVolume(VolumeUnit::L);

      //Check to see if the circuit has stabilized
      if (std::abs(TotalVolume_L - PreviousTotalVolume_L) < 0.0001)
      {
        //Output values        
        trk1.Track("LungVolume_L", iTime, TotalVolume_L);
        trk1.Track("DriverPressure_cmH2O", iTime, driverPressurePath->GetPressureSource(PressureUnit::cmH2O));
        iTime++;
        bSettled = true;
      }
      PreviousTotalVolume_L = TotalVolume_L;
    }
    bSettled = false;

    //Check to see if we've gone all the way to the max volume
    if (TotalVolume_L >= pc.GetPatient().GetTotalLungCapacity(VolumeUnit::L))
    {
      bIRVReached = true;
    }
    else
    {
      DriverPressure_cmH2O = DriverPressure_cmH2O - PressureIncrement_cmH2O;
    }
  }
  trk1.WriteTrackToFile(std::string(sTestDirectory + "/RespiratoryDriverOutput.txt").c_str());
  std::stringstream ss;
  ss << "It took " << tmr.GetElapsedTime_s("Test") << "s to run";
  pc.GetLogger()->Info(ss.str(), "RespiratoryDriverTest");
}
