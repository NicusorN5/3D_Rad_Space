using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Graphics
{
    [StructLayout(LayoutKind.Sequential, Pack = sizeof(byte), Size = sizeof(byte))]
    public struct ShaderCompilationResult
    {
        byte _succeded;

        public ShaderCompilationResult(bool succeded)
        {
            _succeded = succeded ? (byte)1 : (byte)0;
        }

        public bool Succeded
        {
            get
            {
                return _succeded > 0;
            }
        }
    }
}
