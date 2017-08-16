/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
package mil.tatrc.physiology.datamodel.doxygen;

import java.io.*;

import mil.tatrc.physiology.utilities.Log;

public class DoxygenPreprocessor
{
  public static void main(String[] args)
  {
    Log.setFileName("DoxygenPreprocessor.log");
    try
    {
      if(args.length!=2)
      {
        Log.info("Command arguments are : <Directory of files to process> <Directory to place processed files>");
        return;
      }
      File srcDir = new File(args[0]);
      if(!srcDir.isDirectory())
      {
        Log.info("Cannot find Source Directory : "+args[0]);
        return;
      }
      File sDir = new File(args[0]);
      File dDir = new File(args[1]);
      dDir.mkdir();
      
      for (String fName : srcDir.list())
      {        
        if(new File(fName).isDirectory())
          continue;// Not making this recursive at this point
        processFile(fName, sDir, dDir);
      }      
    }
    catch (Exception ex)
    {
      Log.error("Unable to create single validation table file.",ex);
    }
  }
  
  protected static void processFile(String fName, File sDir, File dDir) throws IOException
  {
  	String line;
	  Log.info("Processing file : "+sDir.getPath()+"/"+fName);
	  FileReader in = new FileReader(sDir.getPath()+"/"+fName);
	  BufferedReader inFile = new BufferedReader(in);
	  PrintWriter writer = new PrintWriter(dDir.getAbsolutePath()+"/"+fName, "UTF-8");
	  while ((line = inFile.readLine()) != null)
	  {
	    if(line.indexOf("@insert")>-1)
	    {  
	      String iName = line.substring(line.indexOf(" ")).trim();
	      File f = new File(iName.trim()); 
	      if(!f.exists())
	      {// Try to process this file so it is in the dst directory
	      	String inserting = iName.substring(iName.lastIndexOf("/")+1);
	      	processFile(inserting,sDir,dDir);
	      }
	      Log.info("inserting "+iName);
	      try
	      {
	        // Read this file
	        FileReader iFile = new FileReader(iName);            
	        BufferedReader insertFile = new BufferedReader(iFile);
	        while ((line = insertFile.readLine()) != null)
	        {
	          writer.println(line);
	        }
	        insertFile.close();
	      }
	      catch(Exception ex)
	      {
	        Log.error("Could not find "+f.getAbsolutePath()+" to insert into this page",ex);
	        writer.println("<img src=\"./images/MissingTable.jpg\"><center><i>Could not find "+f.getName()+"</i></center><br>");
	      }
	    }
	    else
	      writer.println(line);
	  }
	  inFile.close();
	  writer.close(); 
  }

}