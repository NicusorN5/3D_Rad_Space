using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Engine3DRadSpace.Reflection
{
    /// <summary>
    /// Type with the same memory layout as Reflection::UUID.
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    public struct UUID
    {
        public ulong Data1;
        public ushort Data2;
        public ushort Data3;
        public byte Data4_1;
        public byte Data4_2;
        public byte Data4_3;
        public byte Data4_4;
        public byte Data4_5;
        public byte Data4_6;
        public byte Data4_7;
        public byte Data4_8;
    }
}
