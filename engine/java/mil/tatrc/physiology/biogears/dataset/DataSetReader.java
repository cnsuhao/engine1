/**************************************************************************************
Copyright 2017 Kitware, Inc.
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

package mil.tatrc.physiology.biogears.dataset;

import java.io.File;
import java.io.FileInputStream;
import java.util.*;

import org.apache.poi.ss.usermodel.FormulaEvaluator;
import org.apache.poi.xssf.usermodel.XSSFCell;
import org.apache.poi.xssf.usermodel.XSSFRow;
import org.apache.poi.xssf.usermodel.XSSFSheet;
import org.apache.poi.xssf.usermodel.XSSFWorkbook;

import com.kitware.physiology.cdm.Patient.PatientData;
import com.kitware.physiology.cdm.Physiology.eHeartRhythm;
import com.kitware.physiology.cdm.Properties.eCharge;
import com.kitware.physiology.cdm.Substance.SubstanceData;

import mil.tatrc.physiology.datamodel.substance.SESubstanceTissuePharmacokinetics;
import mil.tatrc.physiology.datamodel.engine.PhysiologyEngineDynamicStabilization;
import mil.tatrc.physiology.datamodel.engine.PhysiologyEngineDynamicStabilizationCriteria;
import mil.tatrc.physiology.datamodel.engine.PhysiologyEngineTimedStabilization;
import mil.tatrc.physiology.datamodel.system.environment.SEEnvironmentalConditions;
import mil.tatrc.physiology.datamodel.system.equipment.electrocardiogram.SEElectroCardioGramWaveform;
import mil.tatrc.physiology.datamodel.system.equipment.electrocardiogram.SEElectroCardioGramWaveformInterpolator;
import mil.tatrc.physiology.datamodel.patient.*;
import mil.tatrc.physiology.datamodel.patient.nutrition.SENutrition;
import mil.tatrc.physiology.datamodel.properties.SEScalarTime;
import mil.tatrc.physiology.datamodel.substance.*;
import mil.tatrc.physiology.utilities.FileUtils;
import mil.tatrc.physiology.utilities.Log;
import mil.tatrc.physiology.utilities.RunConfiguration;

public class DataSetReader
{
  private static  FormulaEvaluator evaluator;
  private static  RunConfiguration cfg;

  public static void main(String[] args)
  {
    cfg = new RunConfiguration();
    loadData(cfg.getDataDirectory()+"/data/BioGears.xlsx");
  }

  public static void loadData(String xlsFile)
  {
    try
    {
      // Delete current dir contents
      FileUtils.delete(new File("./substances/"));
      FileUtils.delete(new File("./patients/"));
      FileUtils.delete(new File("./environments/"));
      FileUtils.delete(new File("./nutrition/"));
      FileUtils.delete(new File("./ecg/"));
      FileUtils.delete(new File("./config/"));
      // Ok, let's make them again
      FileUtils.createDirectory("./substances/");
      FileUtils.createDirectory("./patients/");
      FileUtils.createDirectory("./environments/");
      FileUtils.createDirectory("./nutrition/");
      FileUtils.createDirectory("./ecg/");
      FileUtils.createDirectory("./config/");
    }
    catch(Exception ex)
    {
      Log.error("Unable to clean directories");
      return;
    }
    try
    {   
      File xls = new File(xlsFile);
      if(!xls.exists())
      {
        Log.error("Could not find xls file "+xlsFile);
        return;
      }
      Log.info("Generating data from "+xlsFile);
      FileInputStream xlFile = new FileInputStream(xlsFile);    
      XSSFWorkbook xlWBook =  new XSSFWorkbook (xlFile);
      evaluator = xlWBook.getCreationHelper().createFormulaEvaluator();
      
      String contentVersion = "6.2.0";      

      List<SEPatient> patients = readPatients(xlWBook.getSheet("Patients"));
      for(SEPatient p : patients)
      {
        String fileName = "./patients/"+p.getName()+".pba";
        Log.info("Writing : "+fileName);
        p.writeFile(fileName);
        SEPatient check = new SEPatient();
        check.readFile(fileName);
        Log.info("Checking : "+fileName);
        
        if(!SEPatient.unload(p).toString().equals(SEPatient.unload(check).toString()))
          throw new RuntimeException("Serialization is not matching, something is wrong in the load/unload for patients");
      }
      
      Map<String,SESubstance> substances=readSubstances(xlWBook.getSheet("Substances"));
      for(SESubstance s : substances.values())  
      {
        String fileName = "./substances/"+s.getName()+".pba";
        Log.info("Writing : "+fileName);
        s.writeFile(fileName);
        SESubstance check = new SESubstance();
        check.readFile(fileName);
        Log.info("Checking : "+fileName);
        
        if(!SESubstance.unload(s).toString().equals(SESubstance.unload(check).toString()))
          throw new RuntimeException("Serialization is not matching, something is wrong in the load/unload for substances");
      }
      
      SESubstanceManager subMgr = new SESubstanceManager();
      subMgr.loadSubstanceDirectory();// We need a substance manager to check compounds
      List<SESubstanceCompound> compounds = readCompounds(xlWBook.getSheet("Compounds"), substances);
      for(SESubstanceCompound c : compounds)
      {
        String fileName = "./substances/"+c.getName()+".pba";
        Log.info("Writing : "+fileName);
        c.writeFile(fileName);  
        SESubstanceCompound check = new SESubstanceCompound();
        check.readFile(fileName,subMgr);
        Log.info("Checking : "+fileName);        
        if(!SESubstanceCompound.unload(c).toString().equals(SESubstanceCompound.unload(check).toString()))
          throw new RuntimeException("Serialization is not matching, something is wrong in the load/unload for substance compounds");
      }
      // Make sure we can read it back in
      subMgr.loadSubstanceDirectory();
      
      Map<String,SEEnvironmentalConditions> environments = readEnvironments(xlWBook.getSheet("Environment"), substances);
      for(String name : environments.keySet())
      {
        String fileName = "./environments/"+name+".pba";
        Log.info("Writing : "+fileName);
        SEEnvironmentalConditions e = environments.get(name);
        e.writeFile(fileName);  
        SEEnvironmentalConditions check = new SEEnvironmentalConditions();
        check.readFile(fileName,subMgr);
        Log.info("Checking : "+fileName);        
        if(!SEEnvironmentalConditions.unload(e).toString().equals(SEEnvironmentalConditions.unload(check).toString()))
          throw new RuntimeException("Serialization is not matching, something is wrong in the load/unload for environmental conditions");
      }
      
      Map<String,SENutrition> meals = readNutrition(xlWBook.getSheet("Nutrition"));
      for(String name : meals.keySet())
      {
        SENutrition n = meals.get(name);
        String fileName = "./nutrition/"+name+".pba";
        Log.info("Writing : "+fileName);
        n.writeFile(fileName);
        SENutrition check = new SENutrition();
        check.readFile(fileName);
        Log.info("Checking : "+fileName);
        
        if(!SENutrition.unload(n).toString().equals(SENutrition.unload(check).toString()))
          throw new RuntimeException("Serialization is not matching, something is wrong in the load/unload for nutrition");
      }
      
      PhysiologyEngineTimedStabilization timed = new PhysiologyEngineTimedStabilization();
      PhysiologyEngineDynamicStabilization dynamic = new PhysiologyEngineDynamicStabilization();
      if(readStabilization(xlWBook.getSheet("Stabilization"),timed,dynamic))
      {
        String fileName = "./config/TimedStabilization.pba";
        Log.info("Writing : "+fileName);
        timed.writeFile(fileName);
        PhysiologyEngineTimedStabilization checkTimed = new PhysiologyEngineTimedStabilization();
        checkTimed.readFile(fileName);
        Log.info("Checking : "+fileName);
        
        if(!PhysiologyEngineTimedStabilization.unload(timed).toString().equals(PhysiologyEngineTimedStabilization.unload(checkTimed).toString()))
          throw new RuntimeException("Serialization is not matching, something is wrong in the load/unload for timed stabilization");
        
        fileName = "./config/DynamicStabilization.pba";
        Log.info("Writing : "+fileName);
        dynamic.writeFile(fileName);
        PhysiologyEngineDynamicStabilization checkDynamic = new PhysiologyEngineDynamicStabilization();
        checkDynamic.readFile(fileName);
        Log.info("Checking : "+fileName);
        
        if(!PhysiologyEngineDynamicStabilization.unload(dynamic).toString().equals(PhysiologyEngineDynamicStabilization.unload(checkDynamic).toString()))
          throw new RuntimeException("Serialization is not matching, something is wrong in the load/unload for dynamic stabilization");
      }
      
      Map<String,SEElectroCardioGramWaveformInterpolator> ecg = readECG(xlWBook.getSheet("ECG"));
      if(ecg!=null)
      {
        for(String name : ecg.keySet())
        {
          SEElectroCardioGramWaveformInterpolator i = ecg.get(name);
          String fileName = "./ecg/"+name+".pba";
          Log.info("Writing : "+fileName);
          i.writeFile(fileName);
          SEElectroCardioGramWaveformInterpolator check = new SEElectroCardioGramWaveformInterpolator();
          check.readFile(fileName);
          Log.info("Checking : "+fileName);

          if(!SEElectroCardioGramWaveformInterpolator.unload(i).toString().equals(SEElectroCardioGramWaveformInterpolator.unload(check).toString()))
            throw new RuntimeException("Serialization is not matching, something is wrong in the load/unload for ECG Interpolator");
        }
      }
      
      xlWBook.close();
    }
    catch(Exception ex)
    {
      Log.error("Error reading XSSF : "+xlsFile,ex);
      return;
    }
  }

  protected static List<SEPatient> readPatients(XSSFSheet xlSheet)
  {
    String property,value,unit;
    List<SEPatient> patients = new ArrayList<SEPatient>();
    try
    {
      int rows = xlSheet.getPhysicalNumberOfRows();      
      for (int r = 0; r < rows; r++) 
      {
        XSSFRow row = xlSheet.getRow(r);
        if (row == null) 
          continue;
        int cells = row.getPhysicalNumberOfCells();
        if(r==0)
        {// Allocate the number of patients we have
          for(int i=1;i<cells;i++)
            patients.add(new SEPatient());
        }
        property = row.getCell(0).getStringCellValue();
        if(property==null||property.isEmpty())
          continue;
        Log.info("Processing Patient Field : "+property);
        for (int c = 1; c < cells; c++) 
        {
          String cellValue=null;
          XSSFCell cell = row.getCell(c);
          switch(cell.getCellType())
          {
            case XSSFCell.CELL_TYPE_NUMERIC:
              cellValue = Double.toString(cell.getNumericCellValue());
              break;
            case XSSFCell.CELL_TYPE_STRING:
              cellValue = cell.getStringCellValue();
              break;
          }
          if(cellValue==null||cellValue.isEmpty())
            continue;
          int split = cellValue.indexOf(" ");
          // Pull The Value
          if(split==-1)
          {
            value=cellValue;
            unit="";
          }
          else
          {
            value = cellValue.substring(0,split);
            unit  = cellValue.substring(split+1);
          }
          if(value.equals("INF"))
            value = "Infinity";
          if(!setProperty(patients.get(c-1),property,value,unit))
          {
            Log.error("Error pulling"+property+" from "+cellValue);
            break;
          }
        }
      }
    }
    catch(Exception ex)
    {
      Log.error("Error reading XLS",ex);
      return null;
    }
    return patients;
  }

  protected static boolean setProperty(SEPatient patient,
      String property,
      String value,
      String unit)
  {
    if(property.equals("Name"))
    {      
      patient.setName(value);
      return true;
    }
    if(property.equals("Sex"))
    {
      patient.setSex(PatientData.eSex.valueOf(value));
      return true;
    }
    if(property.equals("Age"))
    {
      patient.getAge().setValue(Double.parseDouble(value),unit);
      return true;
    }    
    if(property.equals("Weight"))
    {
      patient.getWeight().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("Height"))
    {
      patient.getHeight().setValue(Double.parseDouble(value),unit);
      return true;
    }

    if(property.equals("BasalMetabolicRate"))
    {
      patient.getBasalMetabolicRate().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("BodyDensity"))
    {
      patient.getBodyDensity().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("BodyFatFraction"))
    {
      patient.getBodyFatFraction().setValue(Double.parseDouble(value),unit);
      return true;
    }  
    if(property.equals("DiastolicArterialPressureBaseline"))
    {
      patient.getDiastolicArterialPressureBaseline().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("ExpiratoryReserveVolume"))
    {
      patient.getExpiratoryReserveVolume().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("FunctionalResidualCapacity"))
    {
      patient.getFunctionalResidualCapacity().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("HeartRateBaseline"))
    {
      if(unit.equals("bpm"))
        unit = "1/min";
      patient.getHeartRateBaseline().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("HeartRateMaximum"))
    {
      if(unit.equals("bpm"))
        unit = "1/min";
      patient.getHeartRateMaximum().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("HeartRateMinimum"))
    {
      if(unit.equals("bpm"))
        unit = "1/min";
      patient.getHeartRateMinimum().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("InspiratoryCapacity"))
    {
      patient.getInspiratoryCapacity().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("InspiratoryReserveVolume"))
    {
      patient.getInspiratoryReserveVolume().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("LeanBodyMass"))
    {
      patient.getLeanBodyMass().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("MeanArterialPressureBaseline"))
    {
      patient.getMeanArterialPressureBaseline().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("ResidualVolume"))
    {
      patient.getResidualVolume().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("RespirationRateBaseline"))
    {
      if(unit.equals("bpm"))
        unit = "1/min";
      patient.getRespirationRateBaseline().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("RightLungRatio"))
    {
      patient.getRightLungRatio().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("SkinSurfaceArea"))
    {
      patient.getSkinSurfaceArea().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("SystolicArterialPressureBaseline"))
    {
      patient.getSystolicArterialPressureBaseline().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("TidalVolumeBaseline"))
    {
      patient.getTidalVolumeBaseline().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("BloodVolumeBaseline"))
    {
      patient.getBloodVolumeBaseline().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("TotalLungCapacity"))
    {
      patient.getTotalLungCapacity().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("VitalCapacity"))
    {
      patient.getVitalCapacity().setValue(Double.parseDouble(value),unit);
      return true;
    }

    throw new RuntimeException("Not a valid patient property " + property);
  }

  protected static Map<String,SESubstance> readSubstances(XSSFSheet xlSheet)
  {
    String currCmpt=null;
    String property,value,unit;
    SESubstance substance=null;
    SESubstanceTissuePharmacokinetics fx=null;
    List<SESubstance> substances = new ArrayList<SESubstance>();
    Set<Integer> skipColumns = new HashSet<Integer>();
    
    try
    {
      int rows = xlSheet.getPhysicalNumberOfRows();      
      for (int r = 0; r < rows; r++) 
      {
        XSSFRow row = xlSheet.getRow(r);
        if (row == null) 
          continue;
        int cells = row.getPhysicalNumberOfCells();
        if(r==0)
        {
          for (int c = 1; c < cells; c++) 
          {
            property = row.getCell(c).getStringCellValue().trim();
            if(property.equals("Reference Value")||property.equals("Reference Source")||property.equals("Notes/Page"))
              skipColumns.add(c);
          }
        }        
        property = row.getCell(0).getStringCellValue().trim();
        if(property==null||property.isEmpty())
          continue;
        Log.info("Processing Substance Field : "+property);
        int idx = property.indexOf(" Pharmacokinetics");
        if(idx>-1)
          currCmpt = property.substring(0,idx);
        int s=-1;
        for (int c = 1; c < cells; c++) 
        {
          if(skipColumns.contains(c))
            continue;
          s++;
          String cellValue=null;
          XSSFCell cell = row.getCell(c);
          switch(cell.getCellType())
          {
            case XSSFCell.CELL_TYPE_NUMERIC:
              cellValue = Double.toString(cell.getNumericCellValue());
              break;
            case XSSFCell.CELL_TYPE_STRING:
              cellValue = cell.getStringCellValue();
              break;
            case XSSFCell.CELL_TYPE_FORMULA:
              switch(evaluator.evaluateFormulaCell(cell))
              {
                case XSSFCell.CELL_TYPE_NUMERIC:
                  cellValue = Double.toString(cell.getNumericCellValue());
                  break;
                case XSSFCell.CELL_TYPE_STRING:
                  cellValue = cell.getStringCellValue();
                  break;
              }               
          }
          if(cellValue==null)
            continue;
          cellValue=cellValue.trim();
          if(cellValue.isEmpty())
            continue;
          if(property.equals("Name"))
          {
            substance = new SESubstance();
            substances.add(substance);
            Log.info("Found "+cellValue+" @ "+c);
          }

          int split = cellValue.indexOf(" ");
          // Pull The Value
          if(split==-1)
          {
            value=cellValue;
            unit="";
          }
          else
          {
            value = cellValue.substring(0,split);
            unit  = cellValue.substring(split+1);
          }
          if(value.equals("INF"))
            value = "Infinity";
          try{
          substance=substances.get(c-(3*s)-1);
          }catch(Exception ex)
          {ex.printStackTrace();}

          if(currCmpt==null)
            fx=null;
          else
            fx=substance.getPK().getTissueKinetics(currCmpt);              
          if(!setProperty(substance,fx,property,value,unit))
          {
            Log.error("Error pulling"+property+" from "+cellValue);
            break;
          }
        }
      }
    }
    catch(Exception ex)
    {
      Log.error("Error reading XLS",ex);
      return null;
    }    
    Map<String,SESubstance> map = new HashMap<String,SESubstance>();
    for(SESubstance sub : substances)
      map.put(sub.getName(), sub);
    return map;
  }

  protected static boolean setProperty(SESubstance substance,
      SESubstanceTissuePharmacokinetics tk,
      String property,
      String value,
      String unit)
  {
    if(property.equals("Name"))
    {
      substance.setName(value);
      return true;
    }
    if(property.equals("State"))
    {
      substance.setState(SubstanceData.eState.valueOf(value));
      return true;
    }
    if(property.equals("Density"))
    {
      substance.getDensity().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("MolarMass"))
    {
      substance.getMolarMass().setValue(Double.parseDouble(value),unit);
      return true;
    }
    // Diffusion-ish
    if(property.equals("MaximumDiffusionFlux"))
    {
      substance.getMaximumDiffusionFlux().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("MichaelisCoefficient"))
    {
      substance.getMichaelisCoefficient().setValue(Double.parseDouble(value),unit);
      return true;
    }
    // Aerosolization
    if(property.equals("BronchioleModifier"))
    {
      substance.getAerosolization().getBronchioleModifier().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("InflammationCoefficient"))
    {
      substance.getAerosolization().getInflammationCoefficient().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("ParticulateSizeDistribution"))
    {          
      int arrayStart = value.indexOf('[', 0);
      int arrayEnd   = value.indexOf(']', 0);
      String fraction = value.substring(arrayStart+1, arrayEnd);
      
      arrayStart = value.indexOf('[', arrayEnd+1);
      arrayEnd   = value.indexOf(']', arrayEnd+1);
      String size = value.substring(arrayStart+1, arrayEnd);

      arrayStart = unit.indexOf('[', 0);
      arrayEnd   = unit.indexOf(']', 0);
      String[] units = unit.substring(arrayStart+1, arrayEnd).split(",");
      
      substance.getAerosolization().getParticulateSizeDistribution().setFraction(fraction);
      substance.getAerosolization().getParticulateSizeDistribution().setLength(size,units[1]);
      return true;
    }    
    // Liquid-ish    
    if(property.equals("MassInBody"))
    {
      substance.getMassInBody().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("PlasmaConcentration"))
    {
      substance.getPlasmaConcentration().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("SystemicMassCleared"))
    {
      substance.getSystemicMassCleared().setValue(Double.parseDouble(value),unit);
      return true;
    }
    
    // Gas-ish
    if(property.equals("AlveolarTransfer"))
    {
      substance.getAlveolarTransfer().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("DiffusingCapacity"))
    {
      substance.getDiffusingCapacity().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("EndTidalFraction"))
    {
      substance.getEndTidalFraction().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("EndTidalPressure"))
    {
      substance.getEndTidalPressure().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("RelativeDiffusionCoefficient"))
    {
      substance.getRelativeDiffusionCoefficient().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("SolubilityCoefficient"))
    {
      substance.getSolubilityCoefficient().setValue(Double.parseDouble(value),unit);
      return true;
    }
    
    // Clearance
    if(property.equals("FractionExcretedInFeces"))
    {
      substance.getClearance().getFractionExcretedInFeces().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("FractionExcretedInUrine"))
    {
      substance.getClearance().getFractionExcretedInUrine().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("FractionMetabolizedInGut"))
    {
      substance.getClearance().getFractionMetabolizedInGut().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("IntrinsicClearance"))
    {
      substance.getClearance().getIntrinsicClearance().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("FractionUnboundInPlasma"))
    {
      double d = Double.parseDouble(value);
      if(substance.hasPK() && substance.getPK().hasPhysicochemicals() && substance.getPK().getPhysicochemicals().hasFractionUnboundInPlasma() && substance.getPK().getPhysicochemicals().getFractionUnboundInPlasma().getValue()!=d)
      {
        Log.fatal("Different values for FractionUnboundInPlasma, values must be consistent");
        System.exit(1);
      }
      substance.getPK().getPhysicochemicals().getFractionUnboundInPlasma().setValue(Double.parseDouble(value),unit);
      
      if(substance.hasClearance() && substance.getClearance().hasFractionUnboundInPlasma() && substance.getClearance().getFractionUnboundInPlasma().getValue()!=d)
      {
        Log.fatal("Different values for FractionUnboundInPlasma, values must be consistent");
        System.exit(1);
      }
      substance.getClearance().getFractionUnboundInPlasma().setValue(Double.parseDouble(value),unit);
      return true; 
    }
    // Renal Dynamics
    if(property.equals("Clearance")||property.equals("RenalClearance"))
    {
      double d = Double.parseDouble(value);
      if(substance.hasClearance() && substance.getClearance().hasRenalClearance() && substance.getClearance().getRenalClearance().getValue(unit)!=d)
      {
        Log.fatal("Different values for RenalClearance, values must be consistent");
        System.exit(1);
      }
      substance.getClearance().getRenalClearance().setValue(d,unit);
      return true;
    }
    if(property.equals("ChargeInBlood"))
    {
      substance.getClearance().setChargeInBlood(eCharge.valueOf(value));
      return true;
    }
    if(property.equals("ReabsorptionRatio"))
    {
      substance.getClearance().getRenalReabsorptionRatio().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("TransportMaximum"))
    {
      substance.getClearance().getRenalTransportMaximum().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("FiltrationRate"))
    {
      substance.getClearance().getRenalFiltrationRate().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("ReabsorptionRate"))
    {
      substance.getClearance().getRenalReabsorptionRate().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("ExcretionRate"))
    {
      substance.getClearance().getRenalExcretionRate().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("GlomerularFilterability"))
    {
      substance.getClearance().getGlomerularFilterability().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("SystemicClearance"))
    {
      substance.getClearance().getSystemicClearance().setValue(Double.parseDouble(value),unit);
      return true;
    }
    
    // Pharmacokinetics
    if(property.equals("AcidDissociationConstant"))
    {
      substance.getPK().getPhysicochemicals().getAcidDissociationConstant().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("BindingProtein"))
    {
      substance.getPK().getPhysicochemicals().setBindingProtein(SubstanceData.eBindingProtein.valueOf(value));
      return true;
    }
    if(property.equals("BloodPlasmaRatio"))
    {
      substance.getPK().getPhysicochemicals().getBloodPlasmaRatio().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("IonicState"))
    {
      substance.getPK().getPhysicochemicals().setIonicState(SubstanceData.eIonicState.valueOf(value));
      return true;
    }
    if(property.equals("LogP"))
    {
      substance.getPK().getPhysicochemicals().getLogP().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("OralAbsorptionRateConstant"))
    {
      substance.getPK().getPhysicochemicals().getOralAbsorptionRateConstant().setValue(Double.parseDouble(value),unit);
      return true;
    }
    // Tissue Effects
    if(property.equals("PartitionCoefficient"))
    {
      tk.getPartitionCoefficient().setValue(Double.parseDouble(value),unit);
      return true;
    }
    
    // Pharmacodynamics
    if(property.equals("Bronchodilation"))
    {
      substance.getPD().getBronchodilation().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("DiastolicPressureModifier"))
    {
      substance.getPD().getDiastolicPressureModifier().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("EC50"))
    {
      substance.getPD().getEC50().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("EMaxShapeParameter"))
    {
      substance.getPD().getEMaxShapeParameter().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("HeartRateModifier"))
    {
      substance.getPD().getHeartRateModifier().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("NeuromuscularBlock"))
    {
      substance.getPD().getNeuromuscularBlock().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("PupilReactivityModifier"))
    {
      substance.getPD().getPupillaryResponse().getReactivityModifier().setValue(Double.parseDouble(value));
      return true;
    }
    if(property.equals("PupilSizeModifier"))
    {
      substance.getPD().getPupillaryResponse().getSizeModifier().setValue(Double.parseDouble(value));
      return true;
    }
    if(property.equals("RespirationRateModifier"))
    {
      substance.getPD().getRespirationRateModifier().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("Sedation"))
    {
      substance.getPD().getSedation().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("SystolicPressureModifier"))
    {
      substance.getPD().getSystolicPressureModifier().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("TidalVolumeModifier"))
    {
      substance.getPD().getTidalVolumeModifier().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("TubularPermeabilityModifier"))
    {
      substance.getPD().getTubularPermeabilityModifier().setValue(Double.parseDouble(value),unit);
      return true;
    }
    
    throw new RuntimeException("Not a valid substance property " + property);
  }

  protected static List<SESubstanceCompound> readCompounds(XSSFSheet xlSheet, Map<String,SESubstance> substances)
  {
    String property,value,unit;
    SESubstance s;
    SESubstanceCompound compound=null;
    List<SESubstanceCompound> compounds = new ArrayList<SESubstanceCompound>();
    List<SESubstanceConcentration> currentComponent = null;
    try
    {
      int rows = xlSheet.getPhysicalNumberOfRows();      
      for (int r = 0; r < rows; r++) 
      {
        XSSFRow row = xlSheet.getRow(r);
        if (row == null) 
          continue;
        int cells = row.getPhysicalNumberOfCells();
        if(r==0)
        {// Allocate the number of compounds we have
          for(int i=1;i<cells;i++)          
            compounds.add(new SESubstanceCompound());
          currentComponent = new ArrayList<SESubstanceConcentration>(cells);
        }
        property = row.getCell(0).getStringCellValue();
        if(property==null||property.isEmpty())
          continue;
        Log.info("Processing Patient Field : "+property);
        if(property.equals("Data Type"))
          continue;// Only one type at this point
        for (int c = 1; c < cells; c++) 
        {
          String cellValue=null;
          XSSFCell cell = row.getCell(c);
          switch(cell.getCellType())
          {
            case XSSFCell.CELL_TYPE_NUMERIC:
              cellValue = Double.toString(cell.getNumericCellValue());
              break;
            case XSSFCell.CELL_TYPE_STRING:
              cellValue = cell.getStringCellValue();
              break;
          }
          if(cellValue==null||cellValue.isEmpty())
            continue;
          int split = cellValue.indexOf(" ");
          // Pull The Value
          if(split==-1)
          {
            value=cellValue;
            unit="";
          }
          else
          {
            value = cellValue.substring(0,split);
            unit  = cellValue.substring(split+1);
          }
          compound=compounds.get(c-1);
          if(property.equals("Compound Name"))
          {
            compound.setName(value);
            continue;
          }
          if(property.equals("Component Name"))
          {
            s = substances.get(value);
            SESubstanceConcentration component = compound.getComponent(s);
            currentComponent.add(c-1, component);
            continue;
          }
          if(!setProperty(currentComponent.get(c-1),property,value,unit))
          {
            Log.error("Error setting property");
            break;
          }
        }
      }
    }
    catch(Exception ex)
    {
      Log.error("Error reading XLS",ex);
      return null;
    }
    return compounds;      
  }

  protected static boolean setProperty(SESubstanceConcentration component,
      String property,
      String value,
      String unit)
  {
    if(property.equals("Concentration"))
    {
      component.getConcentration().setValue(Double.parseDouble(value),unit);
      return true;
    }
    throw new RuntimeException("Not a valid compound component property " + property);
  }

  enum AmbientType {Gas,Aerosol};
  static class AmbientSubstance
  {
    public AmbientSubstance(AmbientType t){type=t;}
    public AmbientType type;
    public SESubstanceFractionAmount subFrac;
    public SESubstanceConcentration subConc;
  }
  protected static Map<String,SEEnvironmentalConditions> readEnvironments(XSSFSheet xlSheet, Map<String,SESubstance> substances)
  {
    String property,value,unit;
    SEEnvironmentalConditions environment;
    Map<String,SEEnvironmentalConditions> map = new HashMap<String,SEEnvironmentalConditions>();    
    Map<Integer,AmbientSubstance> columnSubstances = new HashMap<Integer,AmbientSubstance>();
    List<SEEnvironmentalConditions> environments = new ArrayList<SEEnvironmentalConditions>();
    try
    {
      int rows = xlSheet.getPhysicalNumberOfRows();      
      for (int r = 0; r < rows; r++) 
      {
        XSSFRow row = xlSheet.getRow(r);
        if (row == null) 
          continue;
        int cells = row.getPhysicalNumberOfCells();
        if(r==0)
        {// Allocate the number of environments we have
          for(int i=1;i<cells;i++)
            environments.add(new SEEnvironmentalConditions());
        }
        property = row.getCell(0).getStringCellValue();
        if(property==null||property.isEmpty())
          continue;
        Log.info("Processing Environment Field : "+property);
        for (int c = 1; c < cells; c++) 
        {
          String cellValue=null;
          XSSFCell cell = row.getCell(c);
          switch(cell.getCellType())
          {
            case XSSFCell.CELL_TYPE_NUMERIC:
              cellValue = Double.toString(cell.getNumericCellValue());
              break;
            case XSSFCell.CELL_TYPE_STRING:
              cellValue = cell.getStringCellValue();
              break;
          }
          if(cellValue==null||cellValue.isEmpty())
            continue;
          int split = cellValue.indexOf(" ");
          // Pull The Value
          if(split==-1)
          {
            value=cellValue;
            unit="";
          }
          else
          {
            value = cellValue.substring(0,split);
            unit  = cellValue.substring(split+1);
          }
          environment = environments.get(c-1);
          if(property.equals("Name"))
          {
            map.put(cellValue, environment);
            continue;
          }
          if(property.equals("AmbientGasData"))
          {           
            columnSubstances.put(c, new AmbientSubstance(AmbientType.Gas));
            continue;
          }
          if(property.equals("AmbientAerosolData"))
          {            
            columnSubstances.put(c, new AmbientSubstance(AmbientType.Aerosol));
            continue;
          }
          if(property.equals("Substance"))
          {// NOTE THIS ASSUMES THAT A ROW IS ALL ASSOCIATED WITH THE SAME SUBSTANCE            
            
            AmbientSubstance as = columnSubstances.get(c);
            if(as.type==AmbientType.Gas)
              as.subFrac = environment.createAmbientGas(substances.get(value));
            else if(as.type==AmbientType.Aerosol)
              as.subConc = environment.createAmbientAerosol(substances.get(value));            
            continue;
          }
          if(!setProperty(environment,columnSubstances.get(c),property,value,unit))
          {
            Log.error("Error pulling"+property+" from "+cellValue);
            break;
          }
        }
      }
    }
    catch(Exception ex)
    {
      Log.error("Error reading XLS",ex);
      return null;
    }    
    return map;
  }

  protected static boolean setProperty(SEEnvironmentalConditions env, 
      AmbientSubstance as,
      String property,
      String value,
      String unit)
  {

    if(property.equals("SurroundingType"))
    {
//      env.setSurroundingType(EnumSurroundingType.fromValue(value));
      return true;
    }
    if(property.equals("AirDensity"))
    {
      env.getAirDensity().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("AirVelocity"))
    {
      env.getAirVelocity().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("AmbientTemperature"))
    {

      env.getAmbientTemperature().setValue(Double.parseDouble(value),covTempUnit(unit));
      return true;
    }
    if(property.equals("AtmosphericPressure"))
    {
      env.getAtmosphericPressure().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("ClothingResistance"))
    {
      env.getClothingResistance().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("Emissivity"))
    {
      env.getEmissivity().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("MeanRadiantTemperature"))
    {
      env.getMeanRadiantTemperature().setValue(Double.parseDouble(value),covTempUnit(unit));
      return true;
    }
    if(property.equals("RelativeHumidity"))
    {
      env.getRelativeHumidity().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("RespirationAmbientTemperature"))
    {
      env.getRespirationAmbientTemperature().setValue(Double.parseDouble(value),covTempUnit(unit));
      return true;
    }    
    // Substance Fraction
    if(property.equals("FractionAmount"))
    {
      as.subFrac.getAmount().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("Concentration"))
    {
      as.subConc.getConcentration().setValue(Double.parseDouble(value),unit);
      return true;
    }
    throw new RuntimeException("Not a valid environment property " + property);
  }

  protected static Map<String,SENutrition> readNutrition(XSSFSheet xlSheet)
  {
    String property,value,unit;
    SENutrition meal;
    Map<String,SENutrition> map = new HashMap<String,SENutrition>();    
    List<SENutrition> meals = new ArrayList<SENutrition>();
    int colsPerObject = 1;// 1 columns per object (value, reference, notes)
    try
    {
      int rows = xlSheet.getPhysicalNumberOfRows();      
      for (int r = 0; r < rows; r++) 
      {
        XSSFRow row = xlSheet.getRow(r);
        if (row == null) 
          continue;
        int cells = row.getPhysicalNumberOfCells();
        if(r==0)
        {// Allocate the number of objects we have
          int objects = (cells-1)/colsPerObject;
          for(int i=1;i<=objects;i++)
            meals.add(new SENutrition());
        }
        property = row.getCell(0).getStringCellValue();
        if(property==null||property.isEmpty())
          continue;
        Log.info("Processing Nutrition Field : "+property);
        for (int c = 1; c < cells; c+=colsPerObject)// Note, I am not doing anything with the references and notes here 
        {
          String cellValue=null;
          XSSFCell cell = row.getCell(c);
          switch(cell.getCellType())
          {
            case XSSFCell.CELL_TYPE_NUMERIC:
              cellValue = Double.toString(cell.getNumericCellValue());
              break;
            case XSSFCell.CELL_TYPE_STRING:
              cellValue = cell.getStringCellValue();
              break;
          }
          if(cellValue==null||cellValue.isEmpty())
            continue;
          int split = cellValue.indexOf(" ");
          // Pull The Value
          if(split==-1)
          {
            value=cellValue;
            unit="";
          }
          else
          {
            value = cellValue.substring(0,split);
            unit  = cellValue.substring(split+1);
          }
          meal = meals.get((c-1)/colsPerObject);
          if(property.equals("Name"))
          {
            map.put(cellValue, meal);
            continue;
          }          
          if(!setProperty(meal,property,value,unit))
          {
            Log.error("Error pulling"+property+" from "+cellValue);
            break;
          }
        }
      }
    }
    catch(Exception ex)
    {
      Log.error("Error reading XLS",ex);
      return null;
    }    
    return map;
  }

  protected static boolean setProperty(SENutrition meal,
      String property,
      String value,
      String unit)
  {
    if(property.equals("Carbohydrate"))
    {
      meal.getCarbohydrate().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("CarbohydrateDigestionRate"))
    {
      meal.getCarbohydrateDigestionRate().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("Fat"))
    {
      meal.getFat().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("FatDigestionRate"))
    {
      meal.getFatDigestionRate().setValue(Double.parseDouble(value),unit);
      return true;
    }
    if(property.equals("Protein"))
    {

      meal.getProtein().setValue(Double.parseDouble(value),covTempUnit(unit));
      return true;
    }
    if(property.equals("ProteinDigestionRate"))
    {
      meal.getProteinDigestionRate().setValue(Double.parseDouble(value),covTempUnit(unit));
      return true;
    }
    if(property.equals("Sodium"))
    {
      meal.getSodium().setValue(Double.parseDouble(value),unit);
      return true;
    }    
    if(property.equals("Calcium"))
    {
      meal.getCalcium().setValue(Double.parseDouble(value),unit);
      return true;
    }  
    if(property.equals("Water"))
    {
      meal.getWater().setValue(Double.parseDouble(value),unit);
      return true;
    }       
    throw new RuntimeException("Not a valid environment property " + property);
  }

  protected static boolean readStabilization(XSSFSheet xlSheet, PhysiologyEngineTimedStabilization timed, PhysiologyEngineDynamicStabilization dynamic)
  {
    int split;
    // Fields are expected data we must have
    Set<String> fields = new HashSet<String>();
    fields.add("Criteria");
    fields.add("ConvergenceTime");
    fields.add("MinimumReactionTime");
    fields.add("MinimumReactionTime");
    fields.add("MaxAllowedStabilizationTime");
    fields.add("TimedStabilizationLength");
    String property,value,unit,cellValue;
   
    SEScalarTime time=null;
    PhysiologyEngineDynamicStabilizationCriteria criteria=null;
    try
    {
      int rows = xlSheet.getPhysicalNumberOfRows();     
      for (int r = 0; r < rows; r++) 
      {
        XSSFRow row = xlSheet.getRow(r);
        if (row == null) 
          continue;
        property = row.getCell(0).getStringCellValue();
        if(property==null||property.isEmpty())
          continue;
        if(!fields.contains(property))
        {
          if(property.equals("Resting"))
          {
            criteria=dynamic.getRestingStabilizationCriteria();
            time=timed.getRestingStabilizationTime();
          }
          else if(property.equals("Feedback"))
          {
            criteria=dynamic.getFeedbackStabilizationCriteria();
            time=timed.getFeedbackStabilizationTime();
          }
          else
          {
            criteria=dynamic.createConditionCriteria(property);
            time=timed.createConditionStabilizationTime(property);
          }
          continue;
        }         
        else if(property.equals("Criteria"))
        {
          criteria.createProperty(row.getCell(1).getNumericCellValue(),row.getCell(2).getStringCellValue());
        }
        else if(property.equals("ConvergenceTime"))
        {
          cellValue = row.getCell(1).getStringCellValue();
          split = cellValue.indexOf(" ");           
          value = cellValue.substring(0,split);
          unit  = cellValue.substring(split+1);        
          criteria.getConvergenceTime().setValue(Double.parseDouble(value),unit);
        }
        else if(property.equals("MinimumReactionTime"))
        {
          cellValue = row.getCell(1).getStringCellValue();
          split = cellValue.indexOf(" ");           
          value = cellValue.substring(0,split);
          unit  = cellValue.substring(split+1);        
          criteria.getMinimumReactionTime().setValue(Double.parseDouble(value),unit);
        }
        else if(property.equals("MaxAllowedStabilizationTime"))
        {
          cellValue = row.getCell(1).getStringCellValue();
          split = cellValue.indexOf(" ");           
          value = cellValue.substring(0,split);
          unit  = cellValue.substring(split+1);        
          criteria.getMaximumAllowedStabilizationTime().setValue(Double.parseDouble(value),unit);
        }
        else if(property.equals("TimedStabilizationLength"))
        {
          cellValue = row.getCell(1).getStringCellValue();
          split = cellValue.indexOf(" ");           
          value = cellValue.substring(0,split);
          unit  = cellValue.substring(split+1);        
          time.setValue(Double.parseDouble(value),unit);
        }
      }
    }
    catch(Exception ex)
    {
      Log.error("Error reading XLS",ex);
      return false;
    }   
    return true;
  }
  
  protected static Map<String,SEElectroCardioGramWaveformInterpolator> readECG(XSSFSheet xlSheet)
  {
    int split;
    // Fields are expected data we must have
    Set<String> fields = new HashSet<String>();
    fields.add("Description");
    fields.add("Lead");
    fields.add("Rhythm");
    fields.add("ElectricPotential");
    fields.add("Time");
    String property,value,unit,cellValue;
    int lead=3;
    eHeartRhythm rhythm=eHeartRhythm.NormalSinus;
       
    SEElectroCardioGramWaveformInterpolator ecg=null;
    Map<String,SEElectroCardioGramWaveformInterpolator> map = new HashMap<String,SEElectroCardioGramWaveformInterpolator>();
    try
    {
      int rows = xlSheet.getPhysicalNumberOfRows();     
      for (int r = 0; r < rows; r++) 
      {
        XSSFRow row = xlSheet.getRow(r);
        if (row == null) 
          continue;
        property = row.getCell(0).getStringCellValue();
        if(property==null||property.isEmpty())
          continue;
        if(!fields.contains(property))
        {
          ecg = new SEElectroCardioGramWaveformInterpolator();
          map.put(property, ecg);
          continue;
        }         
        else if(property.equals("Lead"))
        {          
          lead = (int)(row.getCell(1).getNumericCellValue());
        }
        else if(property.equals("Rhythm"))
        {
          rhythm = eHeartRhythm.valueOf((row.getCell(1).getStringCellValue()));
        }
        else if(property.equals("ElectricPotential"))
        {
          cellValue = row.getCell(1).getStringCellValue();
          split = cellValue.indexOf(" ");           
          value = cellValue.substring(0,split);
          unit  = cellValue.substring(split+1);        
          SEElectroCardioGramWaveform waveform = ecg.getWaveform(lead, rhythm);
          waveform.getData().setElectricPotential(value, unit);
        }
        else if(property.equals("Time"))
        {
          cellValue = row.getCell(1).getStringCellValue();
          split = cellValue.indexOf(" ");           
          value = cellValue.substring(0,split);
          unit  = cellValue.substring(split+1);        
          SEElectroCardioGramWaveform waveform = ecg.getWaveform(lead, rhythm);
          waveform.getData().setTime(value, unit);          
        }        
      }
    }
    catch(Exception ex)
    {
      Log.error("Error reading XLS",ex);
      return null;
    }   
    return map;
  }

  private static String covTempUnit(String unit)
  {
    if(unit.equals("C"))
      return "degC";
    if(unit.equals("F"))
      return "degF";
    if(unit.equals("R"))
      return "degR";
    return unit;
  }
}
