using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

namespace HowToCSharp
{
  public class test
  {

    private System.Threading.Timer Timer;
    public int smallesttimestep = 200;
    public double e = 0.01;
    private PulseEngineRef pulse;
    public test()
    {
      pulse = new PulseEngineRef("csharp.log");
      pulse.LoadStateFile("./states/StandardMale@0s.pba");

      if (false)
        Timer = new System.Threading.Timer(PULSEGetData, pulse, 0, smallesttimestep);
      else
      {
        while (true)
        {
            pulse.AdvanceModelTime(0.02);
            Console.WriteLine("Lung Volume(mL) : " + pulse.GetLungVolume());
            Console.WriteLine("resp : " + pulse.GetRespiratoryRate());
            Console.WriteLine("press : " + pulse.GetMusclePressure());
            Console.WriteLine("C : " + pulse.GetPulmonaryCompliance());
            Console.WriteLine("R : " + pulse.GetPulmonaryResistance());
            Thread.Sleep(20);
        }
      }

    }

    private void PULSEGetData(object pulseinfo)
    {
      PulseEngineRef pulse = (PulseEngineRef)pulseinfo;
      pulse.AdvanceModelTime(0.02);
      Console.WriteLine("Lung Volume(mL) : " + pulse.GetLungVolume());
      Console.WriteLine("resp : " + pulse.GetRespiratoryRate());
      Console.WriteLine("press : " + pulse.GetMusclePressure());
      Console.WriteLine("C : " + pulse.GetPulmonaryCompliance());
      Console.WriteLine("R : " + pulse.GetPulmonaryResistance());
      Thread.Sleep(20);
    }
  }
}
