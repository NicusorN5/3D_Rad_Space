namespace Engine3DRadSpace.Internal
{
    [StructLayout(LayoutKind.Sequential, Pack = sizeof(int), Size = 2 * sizeof(int))]
    public struct Point
    {
        public int X;
        public int Y;
    }
}
