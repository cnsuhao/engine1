using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HowToCSharp
{
  class Program
  {
    static void Main(string[] args)
    {
      PulseEngineRef pulse = new PulseEngineRef("csharp.log");
      pulse.LoadStateFile("./states/StandardMale@0s.pba");
      pulse.AdvanceModelTime(5);
      Console.WriteLine("Lung Volume(mL) : " + pulse.GetLungVolume());
      pulse.AdvanceModelTime(1);
      Console.WriteLine("Lung Volume(mL) : " + pulse.GetLungVolume());
      pulse.AdvanceModelTime(1);
      Console.WriteLine("Lung Volume(mL) : " + pulse.GetLungVolume());
      pulse.AdvanceModelTime(1);
      Console.WriteLine("Lung Volume(mL) : " + pulse.GetLungVolume());
    }
  }
}
