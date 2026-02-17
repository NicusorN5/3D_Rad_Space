using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Math
{
    [StructLayout(LayoutKind.Sequential)]
    public struct UPoint3
    {
        public uint X;
        public uint Y;
        public uint Z;
    
        public UPoint3(uint x, uint y, uint z)
        {
            X = x;
            Y = z;
            Z = z;
        }
    }
}
