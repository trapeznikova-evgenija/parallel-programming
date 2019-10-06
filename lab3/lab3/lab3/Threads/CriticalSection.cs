using System;
using System.Threading;

namespace lab3.Threads
{
    public class CriticalSection : ICriticalSection
    {
        private Mutex _mutex;
        private int _spinCount;

        public CriticalSection()
        {
            _mutex = new Mutex();
            _spinCount = 1;
        }

        public void Enter()
        {
            int currentSpin = 0;
            while(!_mutex.WaitOne(0, false))
            {
                if (currentSpin == _spinCount)
                {
                    currentSpin = 0;
                    Thread.Sleep( 10 );
                }
                currentSpin++;
            }
            
        }

        public void Leave()
        {
            _mutex.ReleaseMutex();
        }

        public void SetSpinCount( int count )
        {
            _spinCount = count;
        }

        public bool TryEnter( int timeout )
        {
            int currentSpin = 0;
            var firstAttemptTime = DateTime.Now.Millisecond;
            while(!_mutex.WaitOne(0, false))
            {
                if ( currentSpin == _spinCount )
                {
                    currentSpin = 0;
                    Thread.Sleep( 10 );
                }
                currentSpin++;
                if (DateTime.Now.Millisecond - firstAttemptTime >= timeout)
                {
                    return false;
                }
            }
            return true;
        }
    }
}
