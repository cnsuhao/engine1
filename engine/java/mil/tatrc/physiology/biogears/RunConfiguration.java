package mil.tatrc.physiology.biogears;

import java.io.*;
import java.util.Properties;

import org.jfree.util.Log;

public class RunConfiguration 
{
  protected String dataDirectory;
  public    String getDataDirectory() { return dataDirectory; }
  
  public RunConfiguration()
  { 
    // Default values
    dataDirectory = "./";
    
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
    if(properties.containsKey("data_root"))
    {  
      String val = properties.get("data_root").toString();
      if(!val.startsWith("@"))
      {
        File dir = new File(val);
        if(dir.exists() && dir.isDirectory())
          dataDirectory = val;
        else
          Log.error("data_root set to invalid directory "+val+", ignoring and using default ("+this.dataDirectory+")");
      }
    }
  }
  
}
