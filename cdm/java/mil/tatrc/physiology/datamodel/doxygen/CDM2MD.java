/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
package mil.tatrc.physiology.datamodel.doxygen;

import java.io.PrintWriter;
import java.lang.reflect.Method;
import java.util.*;

import com.kitware.physiology.cdm.AnesthesiaMachine.AnesthesiaMachineData;
import com.kitware.physiology.cdm.Patient.PatientData;

import mil.tatrc.physiology.datamodel.compartment.SECompartment;
import mil.tatrc.physiology.datamodel.patient.SEPatient;
import mil.tatrc.physiology.datamodel.patient.actions.SEConsciousRespirationCommand;
import mil.tatrc.physiology.datamodel.patient.actions.SEPatientAction;
import mil.tatrc.physiology.datamodel.patient.assessments.SEPatientAssessment;
import mil.tatrc.physiology.datamodel.patient.conditions.SEPatientCondition;
import mil.tatrc.physiology.datamodel.properties.SEFunction;
import mil.tatrc.physiology.datamodel.properties.SEScalar;
import mil.tatrc.physiology.datamodel.system.environment.actions.SEEnvironmentAction;
import mil.tatrc.physiology.datamodel.system.environment.conditions.SEEnvironmentCondition;
import mil.tatrc.physiology.datamodel.system.equipment.anesthesia.actions.SEAnesthesiaMachineAction;
import mil.tatrc.physiology.datamodel.system.equipment.inhaler.actions.SEInhalerAction;
import mil.tatrc.physiology.utilities.FileUtils;
import mil.tatrc.physiology.utilities.FindObjects;
import mil.tatrc.physiology.utilities.FindObjects.BagMethod;
import mil.tatrc.physiology.utilities.Log;
import mil.tatrc.physiology.utilities.StringUtils;

/**
 * This class will generate markdown tables
 * for some important cdm data structures
 * for use in our documentation
 */
public class CDM2MD
{

	public static void main(String[] args)
	{
		try
		{
			String destDir = "./docs/markdown";
			if(args.length>0)
				destDir = args[0];
			//FileUtils.delete(destDir);//Caller should delete old contents
			FileUtils.createDirectory(destDir);

			PrintWriter writer=new PrintWriter(destDir+"/CDMTable.md", "UTF-8");

			writer.append("CDM Tables {#CDMTables}\n");
			writer.append("=======================\n");

			List<String> skipProperties = new ArrayList<String>();
			skipProperties.add("Comment");
			skipProperties.add("ScenarioTime");

			// PATIENT
			WriteDoxyTable(SEPatient.class, "", writer, skipProperties);    
			WriteDoxyTable(PatientData.eEvent.class, "PatientData_", writer, skipProperties);  
			Set<Class<? extends SEPatientAction>> pActions = FindObjects.findClassSubTypes("mil.tatrc.physiology.datamodel.patient.actions", SEPatientAction.class);
			for(Class<?> c : pActions)
				WriteDoxyTable(c, "", writer, skipProperties);
			Set<Class<? extends SEConsciousRespirationCommand>> cmds = FindObjects.findClassSubTypes("mil.tatrc.physiology.datamodel.patient.actions", SEConsciousRespirationCommand.class);
			for(Class<?> c : cmds)
				WriteDoxyTable(c, "", writer, skipProperties);
			Set<Class<? extends SEPatientCondition>> pConditions = FindObjects.findClassSubTypes("mil.tatrc.physiology.datamodel.patient.conditions", SEPatientCondition.class);
			for(Class<?> c : pConditions)
				WriteDoxyTable(c, "", writer, skipProperties);
			Set<Class<? extends SEPatientAssessment>> pAsses = FindObjects.findClassSubTypes("mil.tatrc.physiology.datamodel.patient.assessments", SEPatientAssessment.class);
			for(Class<?> c : pAsses)
				WriteDoxyTable(c, "", writer, skipProperties);
			Set<Class<? extends Object>> pNutrition = FindObjects.findAllClasses("mil.tatrc.physiology.datamodel.patient.nutrition");
			for(Class<?> c : pNutrition)
				WriteDoxyTable(c, "", writer, skipProperties);

			// ENVIRONMENT
			Set<Class<? extends Object>> env = FindObjects.findAllClasses("mil.tatrc.physiology.datamodel.system.environment");
			for(Class<?> c : env)
				WriteDoxyTable(c, "", writer, skipProperties);
			Set<Class<? extends SEEnvironmentAction>> eActions = FindObjects.findClassSubTypes("mil.tatrc.physiology.datamodel.system.environment.actions", SEEnvironmentAction.class);
			for(Class<?> c : eActions)
				WriteDoxyTable(c, "", writer, skipProperties);
			Set<Class<? extends SEEnvironmentCondition>> eConditions = FindObjects.findClassSubTypes("mil.tatrc.physiology.datamodel.system.environment.conditions", SEEnvironmentCondition.class);
			for(Class<?> c : eConditions)
				WriteDoxyTable(c, "", writer, skipProperties);

			// ANESTHESIA MACHINE

			WriteDoxyTable(AnesthesiaMachineData.eEvent.class, "Anesthesia", writer, skipProperties);  
			Set<Class<? extends Object>> anes = FindObjects.findAllClasses("mil.tatrc.physiology.datamodel.system.equipment.anesthesia");
			for(Class<?> c : anes)
				WriteDoxyTable(c, "", writer, skipProperties);
			Set<Class<? extends SEAnesthesiaMachineAction>> aActions = FindObjects.findClassSubTypes("mil.tatrc.physiology.datamodel.system.equipment.anesthesia.actions", SEAnesthesiaMachineAction.class);
			for(Class<?> c : aActions)
				WriteDoxyTable(c, "", writer, skipProperties);

			// ECG
			Set<Class<? extends Object>> ecg = FindObjects.findAllClasses("mil.tatrc.physiology.datamodel.system.equipment.electrocardiogram");
			for(Class<?> c : ecg)
				WriteDoxyTable(c, "", writer, skipProperties);

			// INHALER
			Set<Class<? extends Object>> inhaler = FindObjects.findAllClasses("mil.tatrc.physiology.datamodel.system.equipment.inhaler");
			for(Class<?> c : inhaler)
				WriteDoxyTable(c, "", writer, skipProperties);
			Set<Class<? extends SEInhalerAction>> iActions = FindObjects.findClassSubTypes("mil.tatrc.physiology.datamodel.system.equipment.inhaler.actions", SEInhalerAction.class);
			for(Class<?> c : iActions)
				WriteDoxyTable(c, "", writer, skipProperties);

			// PHYSIOLOGY
			Set<Class<? extends Object>> phys = FindObjects.findAllClasses("mil.tatrc.physiology.datamodel.system.physiology");
			for(Class<?> c : phys)
				WriteDoxyTable(c, "", writer, skipProperties);

			// SUBSTSANCE
			Set<Class<? extends Object>> subs = FindObjects.findAllClasses("mil.tatrc.physiology.datamodel.substance");
			for(Class<?> c : subs)
				WriteDoxyTable(c, "", writer, skipProperties);
			Set<Class<? extends Object>> subQs = FindObjects.findAllClasses("mil.tatrc.physiology.datamodel.substance.quantity");
			for(Class<?> c : subQs)
				WriteDoxyTable(c, "", writer, skipProperties);

			// COMPARTMENT
			Set<Class<? extends SECompartment>> cmpts = FindObjects.findClassSubTypes("mil.tatrc.physiology.datamodel.compartment",SECompartment.class);
			for(Class<?> c : cmpts)
				WriteDoxyTable(c, "", writer, skipProperties);

			// SCENARIO
			Set<Class<? extends Object>> sce = FindObjects.findAllClasses("mil.tatrc.physiology.datamodel.scenario");
			for(Class<?> c : sce)
				WriteDoxyTable(c, "", writer, skipProperties);

			writer.close();

		} 
		catch (Exception e)
		{
			Log.error("Could not create directory .markdown",e);
			return;
		}
	}

	protected static void WriteDoxyTable(Class<?> c, String prefix, PrintWriter writer, List<String> skipProperties)
	{    
		String tableName = c.getSimpleName();
		if(tableName.startsWith("SE"))
			tableName = tableName.substring(2);
		if(tableName.startsWith("Enum"))
			tableName = tableName.substring(4);
		String descPrepend;
		if(c.isEnum())
			descPrepend = "@copybrief "+prefix+tableName;
		else
			descPrepend = "@copybrief "+prefix+tableName+"Data";

		String columnHeaders[] = new String[3];
		int maxColumnLength[] = new int[columnHeaders.length];
		columnHeaders[0] = "Property Name";
		columnHeaders[1] = "Type";
		columnHeaders[2] = "Definition";
		for(int i=0; i<maxColumnLength.length; i++)
			maxColumnLength[i] = columnHeaders[i].length();

		List<BagMethod> bagMethods = FindObjects.getBagMethods(c,skipProperties);
		if(c.isEnum())
		{
			for(Object o : c.getEnumConstants())
			{
				Method m;
				//Enum<?> e = (Enum<?>)o;
				try
				{
					BagMethod bag = new BagMethod();
					bag.propertyName = o.toString();
					bag.returnType = c;
					bagMethods.add(bag);
				} 
				catch (Exception ex)
				{
					Log.info("Enum is not happy",ex);
				}
			}
		}

		// Compute all of our header values and sizes
		for(BagMethod bag : bagMethods)
		{
			// Header (was built when we had to pull data out of the results file)
			if(bag.propertyName.length()>maxColumnLength[0])
				maxColumnLength[0] = bag.propertyName.length();
			if(bag.returnType.getSimpleName().length()>maxColumnLength[1])
				maxColumnLength[1] = bag.returnType.getSimpleName().length();           
		}
		maxColumnLength[2] = descPrepend.length()+maxColumnLength[0];

		try
		{
			// Create file and start the table      
			writer.println("");
			writer.println("@anchor "+StringUtils.removeSpaces(tableName)+"Table");
			if(c.isEnum())
				writer.println("## "+prefix+tableName);
			else
			writer.println("## "+StringUtils.spaceCamelCase(tableName));
			writer.println(descPrepend+"");

			if(!bagMethods.isEmpty())
			{
				for(int i=0; i<columnHeaders.length; i++)
					writer.print("|"+pad(columnHeaders[i],maxColumnLength[i]));
				writer.println("|");
				for(int i=0; i<columnHeaders.length; i++)
					writer.print("|"+pad("---",maxColumnLength[i]));
				writer.println("|");
				// Now loop the vData and write out table rows
				for(BagMethod bag : bagMethods)
				{
					writer.print("|"+pad(bag.propertyName,maxColumnLength[0]));
					if(bag.returnType.getSimpleName().equals("List"))
					{
						// If it is a list, I am doing this special code, not generic smart yet
						if(bag.propertyName.equals("AmbientSubstance"))
						{
							writer.print("|"+"List of SubstanceFractions");
							writer.print("|"+"@ref SubstanceFractionTable");
						}
						else if(bag.propertyName.equals("Commands"))
						{
							writer.print("|"+"List of Commands");
							String tables = "@ref BreathHoldTable <br> @ref ForcedExhaleTable <br> @ref ForcedInhaleTable <br> @ref UseInhalerTable";
							writer.print("|"+tables);
						}
						else if(bag.propertyName.equals("SubstanceQuantities") && tableName.startsWith("Gas"))
						{
							writer.print("|"+"List of SEGasSubstanceQuantity");
							writer.print("|"+"@ref GasSubstanceQuantityTable");
						}
						else if(bag.propertyName.equals("SubstanceQuantities") && tableName.startsWith("Liquid"))
						{
							writer.print("|"+"List of SELiquidSubstanceQuantity");
							writer.print("|"+"@ref LiquidSubstanceQuantityTable");
						}
						else if(bag.propertyName.equals("Components"))
						{
							writer.print("|"+"List of SESubstanceCompoundComponent");
							writer.print("|"+"@ref SubstanceCompoundComponentTable");
						}
						else if(bag.propertyName.equals("GasFraction"))
						{
							writer.print("|"+"List of SESubstanceFractionAmount");
							writer.print("|"+"@ref SubstanceFractionAmountTable");
						}
						else if(bag.propertyName.equals("AmbientGas"))
						{
							writer.print("|"+"List of SESubstanceFractionAmount");
							writer.print("|"+"@ref SubstanceFractionAmountTable");
						}
						else if(bag.propertyName.equals("AmbientAerosol"))
						{
							writer.print("|"+"List of SESubstanceConcentration");
							writer.print("|"+"@ref SubstanceConcentrationTable");
						}
						else
							Log.error("Unsupported List type for :"+bag.propertyName+" on table "+tableName);

					}
					else
					{
						writer.print("|"+pad(bag.returnType.getSimpleName(),maxColumnLength[1]));
						if(SEScalar.class.isAssignableFrom(bag.returnType) || 
								Enum.class.isAssignableFrom(bag.returnType) ||
								String.class.isAssignableFrom(bag.returnType) ||
								SEFunction.class.isAssignableFrom(bag.returnType))
							writer.print("|"+pad(descPrepend+"_"+bag.propertyName,maxColumnLength[2]));
						else
						{
							String refTable = bag.returnType.getSimpleName();
							if(refTable.startsWith("SE"))
								refTable = refTable.substring(2);
							writer.print("|"+pad("@ref "+refTable+"Table",maxColumnLength[2]));
						}
					}
					writer.println("|");
				}   
			}
			writer.println("");
		}
		catch(Exception ex)
		{
			Log.error("Error writing cdm table for "+tableName,ex);      
		}
	}
	protected static String pad(String s, int max)
	{
		if(s==null)
			return new String(new char[(max+5)]).replace('\0',' ');
		// Using a pad of 5 between columns
		try
		{
			String ret =  s + new String(new char[(max-s.length())+5]).replace('\0',' ');
			return ret;
		}
		catch(Exception ex)
		{
			Log.error("Could not pad "+s+" with a max of "+max,ex);
			return "";
		}
	}

}
