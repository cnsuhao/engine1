using System;
using System.Threading;

namespace HowToCSharp
{
  class Program
  {
    static void Main(string[] args)
    {
      RealTimePulse pulse = new RealTimePulse("RealTimePulse.log", "./states/StandardMale@0s.pba");

      // Create the thread object, passing in the Alpha.Beta method
      // via a ThreadStart delegate. This does not start the thread.
      Thread oThread = new Thread(new ThreadStart(pulse.run));

      // Start the thread
      oThread.Start();

      // Spin for a while waiting for the started thread to become alive:
      while (!oThread.IsAlive);

      // Put the Main thread to sleep for a while to allow pulse to do some work:
      int seconds = 0;
      while (seconds < 60)
      {
        Thread.Sleep(1000);
        Console.WriteLine("Lung Volume (mL) : " + pulse.GetLungVolume_mL() + "\n" +
                          "Respiratory Rate (1/min) : " + pulse.GetRespiratoryRate_per_min() + "\n" +
                          "Muscle Pressure (cmH2O) : " + pulse.GetMusclePressure_cmH2O() + "\n" +
                          "Maximum Muscle Pressure (cmH2O) : " + pulse.GetMaxMusclePressure_cmH2O() + "\n" +
                          "Minimum Muscle Pressure (cmH2O) : " + pulse.GetMinMusclePressure_cmH2O() + "\n" +
                          "Pulmonary Compliance (mL/cmH2O) : " + pulse.GetPulmonaryCompliance_mL_per_cmH2O() + "\n" +
                          "Pulmonary Resistance (cmH2O s/L) : " + pulse.GetPulmonaryResistance_cmH2O_s_Per_L() + "\n");
        seconds++;
      }

      // Request that oThread be stopped
      oThread.Abort();

      // Wait until oThread finishes. Join also has overloads
      // that take a millisecond interval or a TimeSpan object.
      oThread.Join();

      Console.WriteLine();
      Console.WriteLine("Pulse has finished");
    }

  }
}
