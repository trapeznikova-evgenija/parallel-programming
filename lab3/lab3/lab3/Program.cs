using lab3.Ariphmetic;
using lab3.Util;
using System;

namespace lab3
{
    class Program
    {
        static void Main( string [] args )
        {

            try
            {
                var param = Validator.GetArgsIntArrFromSrtArr( args );
                var piCalculator = new PiCalculator
                {
                    AmountStep = param [ 0 ],
                    AmountThread = 4
                };

                piCalculator.SetSpinCount( Convert.ToInt32( param [ 1 ] ) );
                var timer = System.Diagnostics.Stopwatch.StartNew();
                Console.WriteLine( piCalculator.CalculatePi() );
                timer.Stop();
                Console.WriteLine( timer.ElapsedMilliseconds );

                timer = System.Diagnostics.Stopwatch.StartNew();
                Console.WriteLine( piCalculator.CalculatePi( Convert.ToInt32( param [ 2 ] ) ) );
                timer.Stop();
                Console.WriteLine( timer.ElapsedMilliseconds );
            }
            catch (Exception e)
            {
                Console.WriteLine( e.Message );
            }
        }
    }
}
