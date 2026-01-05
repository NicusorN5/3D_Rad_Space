using System.Numerics;
using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Math
{
    [StructLayout(LayoutKind.Sequential)]
    public struct BoundingBox
    {
        public Vector3 Position;
        public Vector3 Scale;

        public BoundingBox(Vector3 p, Vector3 s)
        {
            Position = p;
            Scale = s;
        }
    }
}
