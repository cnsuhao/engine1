/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
package mil.tatrc.physiology.utilities.csv.plots;

import mil.tatrc.physiology.datamodel.substance.SESubstanceManager;
import mil.tatrc.physiology.utilities.LogListener;

public interface Plotter 
{
  void plot(LogListener listener, SESubstanceManager subMgr);
}
