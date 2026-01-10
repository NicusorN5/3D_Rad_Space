using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Logging
{
    [StructLayout(LayoutKind.Sequential)]
    public struct Warning
    {
        [MarshalAs(UnmanagedType.LPStr)]
        public string Details;
        public int Code;
        public int Severity;
        public IntPtr Extra;

        public Warning(string details, int code, int severity, IntPtr extra)
        {
            Details = details;
            Code = code;
            Severity = severity;
            Extra = extra;
        }

        [DllImport("3DRadSpace.Logging.dll", CharSet = CharSet.Ansi, EntryPoint = "E3DRSP_SetLastWarning")]
        public extern static void SetLastWarning(ref Warning wrn);
    }
}
