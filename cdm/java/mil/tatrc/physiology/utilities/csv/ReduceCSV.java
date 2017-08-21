/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
package mil.tatrc.physiology.utilities.csv;

import java.io.*;
import mil.tatrc.physiology.utilities.Log;

public class ReduceCSV
{
  public static void main(String[] args) throws IOException
  {    
    Log.setFileName("ReduceHeaders.log");

    String filename = "BasicStandard12hrResults.txt";

    Log.info("Looking at file: " + filename);
    File fIn = new File(filename);
    if(!fIn.exists())
    {
      Log.error("Say what!?, I don't see that file "+filename);
      return;
    }
    FileInputStream fStream = new FileInputStream(filename);
    DataInputStream in = new DataInputStream(fStream);
    BufferedReader bIn = new BufferedReader(new InputStreamReader(in));

    File fOut = new File("Reduced"+fIn.getName());
    FileOutputStream oStream = new FileOutputStream(fOut);
    BufferedWriter bOut = new BufferedWriter(new OutputStreamWriter(oStream));

    String line = bIn.readLine(); 
    bOut.write(line);
    bOut.newLine();

    int i=0;
    String aLine;
    while ((aLine=bIn.readLine()) != null) 
    {       
      if(i++ %90 == 0)
      {        
        bOut.write(aLine);
        bOut.newLine();
      }
    }       
    bIn.close();
    bOut.close();          
  }
}
