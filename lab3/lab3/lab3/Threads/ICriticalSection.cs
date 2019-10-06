namespace lab3.Threads
{
    public interface ICriticalSection
    {
        void Enter();
        bool TryEnter( int timeout );
        void SetSpinCount( int count );
        void Leave();
    }
}
