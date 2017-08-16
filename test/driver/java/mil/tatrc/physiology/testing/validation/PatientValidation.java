/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
package mil.tatrc.physiology.testing.validation;

import java.io.PrintWriter;
import java.util.Arrays;

import mil.tatrc.physiology.datamodel.patient.SEPatient;
import mil.tatrc.physiology.utilities.Log;

public class PatientValidation extends ValidationTool
{
  public PatientValidation()
  {
    DEST_DIRECTORY = "./test_results/tables/";
    DEFAULT_DIRECTORY = cfg.getValidationDirectory();
    DEFAULT_FILE = "PatientValidationData.xlsx";
    TABLE_TYPE = "Patient";
    HEADER_PREPEND = "Patient";
  }
  public static void main(String[] args)
  {
    Log.setFileName("ValidationTool.log");
    Log.info("Running with agrs : "+Arrays.toString(args));
    PatientValidation me = new PatientValidation();
    if(args.length!=3)
    {
      me.loadData("Local","MSVC","x86");
    }
    else
    {      
      me.loadData(args[0], args[1], args[2]);
    }
  }
  
  public void CustomMarkdown(String sheetName, String destinationDirectory)
  {
    PrintWriter writer=null;
    try
    {
      // Create file and start the table
      writer = new PrintWriter(destinationDirectory+"/"+sheetName+"Description.md", "UTF-8");
      
      writer.println("### "+patient.getName());
      writer.println("|Property Name                     |Value     ");
      writer.println("|---                               |---       ");
      writer.println("|Sex                               |"+patient.getSex());
      writer.println("|Age                               |"+patient.getAge());
      writer.println("|Weight                            |"+patient.getWeight());
      writer.println("|Height                            |"+patient.getHeight());
      writer.println("|BodyDensity                       |"+patient.getBodyDensity());
      writer.println("|BodyFatFraction                   |"+patient.getBodyFatFraction());
      writer.println("|LeanBodyMass                      |"+patient.getLeanBodyMass());
      writer.println("|AlveoliSurfaceArea                |"+patient.getAlveoliSurfaceArea());
      writer.println("|RightLungRatio                    |"+patient.getRightLungRatio());
      writer.println("|SkinSurfaceArea                   |"+patient.getSkinSurfaceArea());
      writer.println("|BasalMetabolicRate                |"+patient.getBasalMetabolicRate());
      writer.println("|BloodVolumeBaseline               |"+patient.getBloodVolumeBaseline());
      writer.println("|DiastolicArterialPressureBaseline |"+patient.getDiastolicArterialPressureBaseline());
      writer.println("|HeartRateBaseline                 |"+patient.getHeartRateBaseline());
      writer.println("|MeanArterialPressureBaseline      |"+patient.getMeanArterialPressureBaseline());
      writer.println("|RespirationRateBaseline           |"+patient.getRespirationRateBaseline());
      writer.println("|SystolicArterialPressureBaseline  |"+patient.getSystolicArterialPressureBaseline());
      writer.println("|TidalVolumeBaseline               |"+patient.getTidalVolumeBaseline());
      writer.println("|HeartRateMaximum                  |"+patient.getHeartRateMaximum());
      writer.println("|HeartRateMinimum                  |"+patient.getHeartRateMinimum());
      writer.println("|ExpiratoryReserveVolume           |"+patient.getExpiratoryReserveVolume());
      writer.println("|FunctionalResidualCapacity        |"+patient.getFunctionalResidualCapacity());
      writer.println("|InspiratoryCapacity               |"+patient.getInspiratoryCapacity());
      writer.println("|InspiratoryReserveVolume          |"+patient.getInspiratoryReserveVolume());
      writer.println("|ResidualVolume                    |"+patient.getResidualVolume());
      writer.println("|TotalLungCapacity                 |"+patient.getTotalLungCapacity());
      writer.println("|VitalCapacity                     |"+patient.getVitalCapacity());
      
      writer.close();
    }
    catch(Exception ex)
    {
      Log.error("Error writing validation table for "+sheetName,ex);
      writer.close();
    }
  }

}
