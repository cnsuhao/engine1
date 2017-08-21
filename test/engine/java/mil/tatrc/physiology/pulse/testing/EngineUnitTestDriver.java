/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
package mil.tatrc.physiology.pulse.testing;

import mil.tatrc.physiology.utilities.Log;
import mil.tatrc.physiology.utilities.UnitConverter;
import mil.tatrc.physiology.testing.SETestDriver;
import mil.tatrc.physiology.testing.SETestDriver.TestJob;

public class EngineUnitTestDriver implements SETestDriver.Executor
{
  
  static
  {
    UnitConverter.initialize(System.getProperty("user.dir"));
  }
  
  protected long nativeObj;
  protected native long nativeAllocate();
  protected native void nativeDelete(long nativeObj);
  protected native void nativeExecute(long nativeObj, String testName, String outputDir);
  
  public EngineUnitTestDriver()
  {
    this.nativeObj = nativeAllocate();
  }
  
  protected void finalize()
  {
    nativeDelete(this.nativeObj);
  }
  
  public boolean ExecuteTest(TestJob job)
  {
    nativeExecute(this.nativeObj,job.name,job.computedDirectory);
    Log.info("Completed running "+job.name);
    return true;
  }
  
  public static void main(String[] args)
  {
    SETestDriver.main(args);
  }

}

