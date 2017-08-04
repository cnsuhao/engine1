/**************************************************************************************
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