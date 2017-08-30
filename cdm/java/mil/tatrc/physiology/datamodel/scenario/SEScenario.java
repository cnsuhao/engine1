/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.scenario;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

import com.google.protobuf.TextFormat;
import com.google.protobuf.TextFormat.ParseException;
import com.kitware.physiology.cdm.AnesthesiaMachine.AnesthesiaMachineData.eConnection;
import com.kitware.physiology.cdm.AnesthesiaMachine.AnesthesiaMachineData.eOxygenSource;
import com.kitware.physiology.cdm.AnesthesiaMachine.AnesthesiaMachineData.ePrimaryGas;
import com.kitware.physiology.cdm.PatientAssessments.PatientAssessmentData.eType;
import com.kitware.physiology.cdm.Enums.eSide;
import com.kitware.physiology.cdm.Enums.eSwitch;
import com.kitware.physiology.cdm.Scenario.AnyActionData;
import com.kitware.physiology.cdm.Scenario.ScenarioData;
import com.kitware.physiology.cdm.Scenario.DataRequestData.eCategory;
import com.kitware.physiology.pulse.Engine;

import mil.tatrc.physiology.datamodel.actions.SEAction;
import mil.tatrc.physiology.datamodel.actions.SEAdvanceTime;
import mil.tatrc.physiology.datamodel.datarequests.*;
import mil.tatrc.physiology.datamodel.patient.actions.SEBronchoconstriction;
import mil.tatrc.physiology.datamodel.patient.actions.SENeedleDecompression;
import mil.tatrc.physiology.datamodel.patient.actions.SEPatientAssessmentRequest;
import mil.tatrc.physiology.datamodel.patient.conditions.SEChronicAnemia;
import mil.tatrc.physiology.datamodel.properties.CommonUnits.FrequencyUnit;
import mil.tatrc.physiology.datamodel.properties.CommonUnits.PressureUnit;
import mil.tatrc.physiology.datamodel.properties.CommonUnits.TimeUnit;
import mil.tatrc.physiology.datamodel.properties.CommonUnits.VolumePerTimeUnit;
import mil.tatrc.physiology.datamodel.properties.CommonUnits.VolumeUnit;
import mil.tatrc.physiology.datamodel.substance.SESubstance;
import mil.tatrc.physiology.datamodel.substance.SESubstanceManager;
import mil.tatrc.physiology.datamodel.system.equipment.anesthesia.actions.SEAnesthesiaMachineConfiguration;
import mil.tatrc.physiology.utilities.FileUtils;
import mil.tatrc.physiology.utilities.Log;
import mil.tatrc.physiology.utilities.SimpleEquals;

public class SEScenario 
{
	public static void main(String[] args)
	{
		SESubstanceManager mgr = new SESubstanceManager();
		mgr.loadSubstanceDirectory();

		{
			SEScenario s = new SEScenario(mgr);
			s.setName("Test");
			s.setDescription("Description");
			s.getInitialParameters().setPatientFile("StandardMale.pba");


			SEChronicAnemia cond = new SEChronicAnemia();
			cond.getReductionFactor().setValue(0.5);
			s.getInitialParameters().getConditions().add(cond);

			SEDataRequest dr = new SEDataRequest();
			dr.setCategory(eCategory.Physiology);
			dr.setPropertyName("Weight");
			dr.setUnit("kg");
			dr.setPrecision(1);
			s.getDataRequestManager().getRequestedData().add(dr);
			SEAdvanceTime adv = new SEAdvanceTime();
			adv.getTime().setValue(320,TimeUnit.s);
			s.getActions().add(adv);
			SENeedleDecompression nd = new SENeedleDecompression();

			SEBronchoconstriction bc = new SEBronchoconstriction();
			bc.getSeverity().setValue(0.5);
			s.getActions().add(bc);

			SESubstance sub = mgr.getSubstance("Oxygen");
			SEAnesthesiaMachineConfiguration anes = new SEAnesthesiaMachineConfiguration();
			anes.getConfiguration().setConnection(eConnection.Tube);
			anes.getConfiguration().getInletFlow().setValue(5.0, VolumePerTimeUnit.L_Per_min);
			anes.getConfiguration().getInspiratoryExpiratoryRatio().setValue(0.5);
			anes.getConfiguration().getOxygenFraction().setValue(0.23);
			anes.getConfiguration().setOxygenSource(eOxygenSource.Wall);
			anes.getConfiguration().getPositiveEndExpiredPressure().setValue(1.0, PressureUnit.cmH2O);
			anes.getConfiguration().setPrimaryGas(ePrimaryGas.Nitrogen);
			anes.getConfiguration().getRespiratoryRate().setValue(16.0, FrequencyUnit.Per_min);
			anes.getConfiguration().getVentilatorPressure().setValue(10.5, PressureUnit.cmH2O);      
			anes.getConfiguration().getOxygenBottleOne().getVolume().setValue(660.0, VolumeUnit.L);
			anes.getConfiguration().getOxygenBottleTwo().getVolume().setValue(660.0, VolumeUnit.L);      
			anes.getConfiguration().getRightChamber().setState(eSwitch.On);
			anes.getConfiguration().getRightChamber().setSubstance(sub); 
			anes.getConfiguration().getRightChamber().getSubstanceFraction().setValue(0.5);
			anes.getConfiguration().getLeftChamber().setState(eSwitch.On);
			anes.getConfiguration().getLeftChamber().setSubstance(sub);
			s.getActions().add(anes);

			//SECompleteBloodCount cbc = new SECompleteBloodCount();
			//SEPatientAssessment ass = new SEPatientAssessment();
			//s.getActions().add(cbc);
			SEPatientAssessmentRequest pa = new SEPatientAssessmentRequest();
			pa.setType(eType.ComprehensiveMetabolicPanel);
			s.getActions().add(pa);

			nd.setState(eSwitch.On);
			nd.setSide(eSide.Left);
			s.getActions().add(nd);
			System.out.println(SEScenario.unload(s).toString());
			s.writeFile("TestScenario.pba");

			SEScenario s2 = new SEScenario(mgr);
			try 
			{
				s2.readFile("TestScenario.pba");
			} 
			catch (ParseException e) 
			{
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			for(SEAction a : s2.getActions())
			{
				System.out.println(a.toString());
				System.out.println();
			}
		}

		boolean onlyCheckSchema=true;

		String searchDir;
		if(args.length==0)
			searchDir="./verification/scenarios/";
		else
			searchDir=args[0];
		List<String> files=FileUtils.findFiles(searchDir, ".pba", true);
		for(String file : files)
		{
			if(file.indexOf("@")>-1)
				continue; // An assessment
			
			String pba = FileUtils.readFile(file);
			if(pba==null)
			{
				Log.error("Could not read file : "+file);
				continue;
			}
			Engine.ScenarioData.Builder pBuilder = Engine.ScenarioData.newBuilder();
			try
			{
				TextFormat.getParser().merge(pba, pBuilder);
				Log.info(file+" is a good Pulse scenario");
				continue;
			}
			catch(Exception ex)
			{
				Log.info("Testing scenario file "+file);
				SEScenario sce1 = new SEScenario(mgr);
				try
				{
					sce1.readFile(file);
					continue;
				}
				catch(ParseException ex1)
				{
					Log.error("Unable to read file "+file,ex1);
				}
				continue;
//				
//				// Let's make sure we don't have the same data request more than once
//				Set<Integer> hashes = new HashSet<Integer>();
//				for(SEDataRequest dr : sce1.getDataRequestManager().getRequestedData())
//				{
//					int hash = dr.hashCode();        
//					if(!hashes.contains(hash))
//						hashes.add(hash);
//					else
//						Log.error("Duplicate Data Request");
//				}
//
//				if(!onlyCheckSchema)
//				{
//					ScenarioData sce1Data = SEScenario.unload(sce1);
//					SEScenario sce2 = new SEScenario(mgr);
//					SEScenario.load(sce1Data, sce2);
//					ScenarioData sce2Data = SEScenario.unload(sce2);
//
//					int numActions;
//
//					numActions = sce1Data.getAnyActionList().size();
//					if(numActions != sce2Data.getAnyActionList().size())
//						Log.error("We have a xsd actions problem with : "+file);      
//					for(int i=0; i<numActions; i++)
//					{
//						AnyActionData action1 = sce1Data.getAnyAction(i);
//						AnyActionData action2 = sce2Data.getAnyAction(i);
//
//						//Log.info("Comparing "+action1.getClass().getSimpleName());
//						if(!SimpleEquals.Equals(action1, action2))
//						{
//							Log.error("We have an actions problem with : "+file);
//							Log.error("Scenario 1 action is : "+action1);
//							Log.error("Scenario 2 action is : "+action2);          
//						}
//					}
//
//					// Now let's compare SEActions
//					numActions = sce1.actions.size();
//					if(numActions != sce2.actions.size())
//						Log.error("We have an actions problem with : "+file);
//
//					for(int i=0; i<numActions; i++)
//					{
//						String action1 = sce1.actions.get(i).toString();
//						String action2 = sce2.actions.get(i).toString();
//
//						if(!action1.equals(action2))
//						{
//							Log.error("We have an actions problem with : "+file);
//							Log.error("Scenario 1 action is : "+action1);
//							Log.error("Scenario 2 action is : "+action2);          
//						}
//					}
//				}
			}
		}
	}

	protected String                        name;
	protected String                        description;
	protected SEScenarioInitialParameters   params;
	protected String                        engineStateFile;
	protected SEDataRequestManager          drMgr = new SEDataRequestManager();
	protected List<SEAction>                actions = new ArrayList<SEAction>();

	protected SESubstanceManager            subMgr;

	public SEScenario(SESubstanceManager subMgr)
	{
		this.subMgr = subMgr; 
		reset();
	}

	public void reset() 
	{
		this.name            = "";
		this.description     = "";
		this.params          = null;
		this.engineStateFile = null;
		this.actions.clear();    
		this.drMgr.reset();
	}

	public void readFile(String fileName) throws ParseException
	{
		ScenarioData.Builder builder = ScenarioData.newBuilder();
		TextFormat.getParser().merge(FileUtils.readFile(fileName), builder);
		SEScenario.load(builder.build(), this);
	}
	public void writeFile(String fileName)
	{
		FileUtils.writeFile(fileName, SEScenario.unload(this).toString());
	}

	public static void load(ScenarioData src, SEScenario dst)
	{
		dst.reset();

		dst.name = src.getName();
		dst.description = src.getDescription();

		switch(src.getStartTypeCase())
		{
		case ENGINESTATEFILE:
			dst.engineStateFile = src.getEngineStateFile();
			break;
		case INITIALPARAMETERS:
			SEScenarioInitialParameters.load(src.getInitialParameters(),dst.getInitialParameters(),dst.subMgr);
		}

		if(src.hasDataRequestManager())
			SEDataRequestManager.load(src.getDataRequestManager(), dst.getDataRequestManager());

		for(AnyActionData aData : src.getAnyActionList())
			dst.actions.add(SEAction.ANY2CDM(aData,dst.subMgr)); 
		dst.deriveActionTimes();
	}

	public static ScenarioData unload(SEScenario src)
	{
		ScenarioData.Builder dst = ScenarioData.newBuilder();
		unload(src,dst);
		return dst.build();
	}

	protected static void unload(SEScenario src, ScenarioData.Builder dst)
	{
		if(src.hasName())
			dst.setName(src.name);

		if(src.hasDescription())
			dst.setDescription(src.description);

		if(src.hasInitialParameters())
			dst.setInitialParameters(SEScenarioInitialParameters.unload(src.params));
		else if(src.hasEngineState())
			dst.setEngineStateFile(src.engineStateFile);

		if(!src.drMgr.getRequestedData().isEmpty())
			dst.setDataRequestManager(SEDataRequestManager.unload(src.drMgr));

		for(SEAction a : src.actions)
			dst.addAnyAction(SEAction.CDM2ANY(a));
	}

	public boolean isValid()
	{
		if (actions.size() == 0)
			return false;
		if(!hasInitialParameters() && !hasEngineState())
			return false;
		return true;
	}

	public String getName()
	{
		return name;
	}
	public void setName(String name)
	{
		this.name = name;
	}
	public boolean hasName()
	{
		return name.isEmpty() ? false : true;
	}
	public void invalidateName()
	{
		name = "";
	}

	public String getDescription()
	{
		return description;
	}
	public void setDescription(String description)
	{
		this.description = description;
	}
	public boolean hasDescription()
	{
		return description.isEmpty() ? false : true;
	}
	public void invalidateDescription()
	{
		description = "";
	}

	public boolean hasEngineState()
	{
		if(hasInitialParameters())
			return false;
		return this.engineStateFile != null && !this.engineStateFile.isEmpty();
	}
	public void setEngineState(String stateFile)
	{
		invalidateInitialParameters();
		this.engineStateFile = stateFile;
	}
	public String getEngineState(){ return this.engineStateFile; }
	public void invalidateEngineState()
	{
		this.engineStateFile = null;
	}

	public boolean hasInitialParameters()
	{
		return params!=null && params.isValid();
	}
	public SEScenarioInitialParameters getInitialParameters()
	{
		if(this.params==null)
			this.params=new SEScenarioInitialParameters();
		return this.params;
	}
	public void invalidateInitialParameters()
	{
		this.params = null;
	}

	public List<SEAction> getActions() 
	{
		return actions;
	}

	public SEDataRequestManager getDataRequestManager() 
	{
		return this.drMgr;
	}

	public SESubstanceManager getSubstanceManager()
	{
		return this.subMgr;
	}

	public void deriveActionTimes()
	{
		double time_s=0;
		for(SEAction a : this.actions)
		{
			a.getScenarioTime().setValue(time_s, TimeUnit.s);
			if(a instanceof SEAdvanceTime)
				time_s += ((SEAdvanceTime)a).getTime().getValue(TimeUnit.s);
		}
	}
}
