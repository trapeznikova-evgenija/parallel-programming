using lab3.Threads;
using System;
using System.Collections.Generic;
using System.Threading;

namespace lab3.Ariphmetic
{
    public class PiCalculator
    {
        public int AmountStep { get; set; }
        public int AmountThread { get; set; }
        
        private double _pi;
        private ICriticalSection _criticalSection;

        public PiCalculator()
        {
            _criticalSection = new CriticalSection();
        }

        public double CalculatePi( int? timeout = null )
        {
            _pi = 0;
            double step = 1 / ( double ) AmountStep;
            int countStepsPerThread = AmountStep / AmountThread;
            var threads = new List<Thread>();
            for ( int idThread = 0; idThread < AmountThread; idThread++ )
            {
                Thread thread = timeout.HasValue ? new Thread( IncreasePiValueByTimeout ) : new Thread( IncreasePiValueBySpin );
                threads.Add( thread );
                thread.Start( new ArgsThread
                {
                    Left = idThread * countStepsPerThread,
                    Right = ( idThread + 1 ) * countStepsPerThread,
                    Step = step
                } );
            }

            foreach ( var thread in threads )
            {
                thread.Join();
            }
            return _pi;
        }

        public void SetSpinCount(int spinCount)
        {
            _criticalSection.SetSpinCount( spinCount );
        }

        private void IncreasePiValueBySpin( object arg )
        {
            var argsThread = ( ArgsThread ) arg;
            for ( int i = argsThread.Left; i < argsThread.Right; i++ )
            {
                var x = ( i + 0.5 ) * argsThread.Step;
                _criticalSection.Enter();
                _pi += 4.0 / ( 1.0 + x * x ) * argsThread.Step;
                _criticalSection.Leave();
            }
        }

        private void IncreasePiValueByTimeout( object arg )
        {
            var argsThread = ( ArgsThread ) arg;
            for ( int i = argsThread.Left; i < argsThread.Right; i++ )
            {
                var x = ( i + 0.5 ) * argsThread.Step;
                while ( !_criticalSection.TryEnter( argsThread.Timeout ) ) ;
                _pi += 4.0 / ( 1.0 + x * x ) * argsThread.Step;
                _criticalSection.Leave();
            }
        }
    }
}
