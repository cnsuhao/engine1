/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

/**
 * 
 */
package mil.tatrc.physiology.testing;

import mil.tatrc.physiology.utilities.LogListener;

/**
 * @author abray
 * Simple class to listen to any status messages
 * from the calculation and add them to the report
 */
public class SETestCaseListener extends LogListener
{
  private SETestCase testCase=null;
  
  public SETestCaseListener()
  {

  }
  
  public void reset()
  {
    this.testCase=null;
  }
  
  public void setTestCase(SETestCase tc)
  {
    this.testCase=tc;
  }

  public void handleError(String msg)
  {
    if (testCase != null)
    {
    	testCase.AddFailure(msg);
    }
  }
  
  public void handleFatal(String msg)
  {
  	if (testCase != null)
    {
    	testCase.AddFailure(msg);
    }
  }
}