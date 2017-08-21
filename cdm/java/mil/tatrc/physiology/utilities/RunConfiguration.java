package mil.tatrc.physiology.utilities;

import java.io.*;
import java.util.Properties;

import org.jfree.util.Log;

/**
 * Simple file to load up a config file and
 * provide access to the variables it contains
 * Pretty much a simple I/O wrapped properties file
 * @author aaron.bray
 *
 */
public class RunConfiguration 
{
  protected String dataDirectory;
  protected String testConfigDirectory;
  protected String validationDirectory;
  protected String verificationDirectory;
  
  public    String getDataDirectory()         { return dataDirectory;         }
  public    String getTestConfigDirectory()   { return testConfigDirectory;   }
  public    String getValidationDirectory()   { return validationDirectory; }
  public    String getVerificationDirectory() { return verificationDirectory; }
  
  
  public RunConfiguration()
  { 
    // Default values
    dataDirectory         = "./";
    testConfigDirectory   = "./";
    validationDirectory   = "./";
    verificationDirectory = "./";
    
    // Now let's look for a config file and
    // use any configuration parameters it has    
    File file = new File("./run.config");
    if(file.exists())
    {
      try
      {
        FileInputStream fileInput = new FileInputStream(file);
        Properties properties = new Properties();
        properties.load(fileInput);
        setProperties(properties);
        fileInput.close();
      }
      catch(Exception ex)
      {
        Log.error("Could not read run.config file");
      }
    }
    
  }
  
  protected void setProperties(Properties properties)
  {
    if(properties.containsKey("data_dir"))
    {  
      String val = properties.get("data_dir").toString();
      if(!val.startsWith("@"))
      {
        File dir = new File(val);
        if(dir.exists() && dir.isDirectory())
          dataDirectory = val;
        else
          Log.error("data_root set to invalid directory "+val+", ignoring and using default ("+this.dataDirectory+")");
      }
    }
    if(properties.containsKey("test_config_dir"))
    {  
      String val = properties.get("test_config_dir").toString();
      if(!val.startsWith("@"))
      {
        File dir = new File(val);
        if(dir.exists() && dir.isDirectory())
        	testConfigDirectory = val;
        else
          Log.error("test_config_dir set to invalid directory "+val+", ignoring and using default ("+this.testConfigDirectory+")");
      }
    }
    if(properties.containsKey("validation_dir"))
    {  
      String val = properties.get("validation_dir").toString();
      if(!val.startsWith("@"))
      {
        File dir = new File(val);
        if(dir.exists() && dir.isDirectory())
        	validationDirectory = val;
        else
          Log.error("validation_dir set to invalid directory "+val+", ignoring and using default ("+this.validationDirectory+")");
      }
    }
    if(properties.containsKey("verification_dir"))
    {  
      String val = properties.get("verification_dir").toString();
      if(!val.startsWith("@"))
      {
        File dir = new File(val);
        if(dir.exists() && dir.isDirectory())
        	verificationDirectory = val;
        else
          Log.error("verification_dir set to invalid directory "+val+", ignoring and using default ("+this.verificationDirectory+")");
      }
    }
  }
  
}
