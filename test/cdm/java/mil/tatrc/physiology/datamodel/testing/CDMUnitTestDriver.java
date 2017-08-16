/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
package mil.tatrc.physiology.datamodel.testing;

import mil.tatrc.physiology.utilities.Log;
import mil.tatrc.physiology.testing.SETestDriver;
import mil.tatrc.physiology.testing.SETestDriver.TestJob;

public class CDMUnitTestDriver implements SETestDriver.Executor
{
  protected long nativeObj;
  protected native long nativeAllocate();
  protected native void nativeDelete(long nativeObj);
  protected native void nativeExecute(long nativeObj, String testName, String outputDir);
  
  public CDMUnitTestDriver()
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

}
