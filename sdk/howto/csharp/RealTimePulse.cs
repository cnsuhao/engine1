using System;
using System.Threading;
using System.Diagnostics;

// Look at James' email on strings
// fix the CLR install (CLR is not part of all build, so there is nothing to install, so install fails)
// How do we get events into C#
// Make properties and other cdm objects
// units should be an enum on C# side of things

namespace HowToCSharp
{
  // Connect events we get from pulse to csharp methods
  public class PulseEventHandler : PulseEventsRef
  {
    public PulseEventHandler(RealTimePulse pulse) { _pulse = pulse; }
    protected override void OnStartOfInhale() { _pulse.StartBreath(); }
    protected RealTimePulse _pulse;
  }

  public class PulseLogHandler : PulseLoggerRef
  {
    protected override void OnFatal(string msg) { Console.WriteLine("[Fatal] "+ msg); }
    protected override void OnError(string msg) { Console.WriteLine("[Error] " + msg); }
    protected override void OnWarn(string msg) { Console.WriteLine("[Warn] " + msg); }
    protected override void OnInfo(string msg) { Console.WriteLine("[Info] " + msg); }
    protected override void OnDebug(string msg) { Console.WriteLine("[Debug] " + msg); }
  }

  public class RealTimePulse
  {
    protected bool _alive = true;
    protected bool _paused = false;
    protected PulseEngineRef _pulse;
    protected PulseEventHandler _events;
    protected PulseLogHandler _logger;
    private Object _lock = new Object();

    protected double _lung_volume_mL;
    protected double _respiratory_rate_per_min;
    protected double _muscle_pressure_cmH2O;
    protected double _pulmonary_compliance_mL_per_cmH2O;
    protected double _pulmonary_resistance_cmH2O_s_Per_L;
    protected double _max_muscle_pressure_cmH2O;
    protected double _working_max_muscle_pressure_cmH2O;
    protected double _min_muscle_pressure_cmH2O;
    protected double _working_min_muscle_pressure_cmH2O;

    public RealTimePulse() { }
    public RealTimePulse(string log_file, string state_file)
    {
      _pulse = new PulseEngineRef(log_file);
      _pulse.LoadStateFile(state_file);
      _events = new PulseEventHandler(this);
      _events.SetupEventHandler(_pulse);
      _logger = new PulseLogHandler();
      _logger.SetupCallbacks(_pulse);

    }

    public double GetLungVolume_mL() { lock(_lock) { return _lung_volume_mL; } }
    public double GetRespiratoryRate_per_min() { lock (_lock) { return _respiratory_rate_per_min; } }
    public double GetMusclePressure_cmH2O() { lock (_lock) { return _muscle_pressure_cmH2O; } }
    public double GetMaxMusclePressure_cmH2O() { lock (_lock) { return _max_muscle_pressure_cmH2O; } }
    public double GetMinMusclePressure_cmH2O() { lock (_lock) { return _min_muscle_pressure_cmH2O; } }
    public double GetPulmonaryCompliance_mL_per_cmH2O() { lock (_lock) { return _pulmonary_compliance_mL_per_cmH2O; } }
    public double GetPulmonaryResistance_cmH2O_s_Per_L() { lock (_lock) { return _pulmonary_resistance_cmH2O_s_Per_L; } }

    public void StartBreath()
    {
      _max_muscle_pressure_cmH2O = _working_max_muscle_pressure_cmH2O;
      _working_max_muscle_pressure_cmH2O = 0;
      _min_muscle_pressure_cmH2O = _working_min_muscle_pressure_cmH2O;
      _working_min_muscle_pressure_cmH2O = 1000000;
    }

    public void run()
    {
      int duration_ms;
      Console.WriteLine("Pulse is running in its own thread.");
      Stopwatch stopWatch = new Stopwatch();
      while (_alive)
      {
        stopWatch.Reset();
        stopWatch.Start();
        if (!_paused)
        {
          _pulse.AdvanceModelTime(1);// Advance a second
          lock(_lock)
          {
            _lung_volume_mL = _pulse.GetLungVolume();
            _respiratory_rate_per_min = _pulse.GetRespiratoryRate();
            _muscle_pressure_cmH2O = _pulse.GetMusclePressure();
            _pulmonary_compliance_mL_per_cmH2O = _pulse.GetPulmonaryCompliance();
            _pulmonary_resistance_cmH2O_s_Per_L = _pulse.GetPulmonaryResistance();
            if (_muscle_pressure_cmH2O > _working_max_muscle_pressure_cmH2O)
              _working_max_muscle_pressure_cmH2O = _muscle_pressure_cmH2O;
            if (_muscle_pressure_cmH2O < _working_min_muscle_pressure_cmH2O)
              _working_min_muscle_pressure_cmH2O = _muscle_pressure_cmH2O;
          }
        }
        stopWatch.Stop();
        // See how long it took us to run a second, and sleep
        duration_ms = (int)stopWatch.Elapsed.TotalMilliseconds;
        if(duration_ms > 1000)
          Console.WriteLine("Pulse is running slower than real time!!! : "+ duration_ms);
        else
          Thread.Sleep(1000 - duration_ms);
      }
    }
  }
}
