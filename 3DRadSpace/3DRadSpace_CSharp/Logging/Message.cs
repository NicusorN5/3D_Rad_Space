using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Logging
{
    [StructLayout(LayoutKind.Sequential)]
    public struct Message
    {
        public string Details;
        public int Code;
        public IntPtr Extra;

        public Message(string details, int code, IntPtr extra)
        {
            Details = details;
            Code = code;
            Extra = extra;
        }

        [DllImport("3DRadSpace.Logging.dll", CharSet = CharSet.Ansi, EntryPoint = "E3DRSP_SetLastMessage")]
        extern unsafe static void _log(string details, int code, IntPtr extra);

        public static void SetLastMessage(Message msg )
        {
            _log(msg.Details, msg.Code, msg.Extra);
        }
    }
}
