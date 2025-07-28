using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Audio
{
    public class AudioEngine : IDisposable
    {
        private IntPtr _audio;
        private bool _disposed;

        [DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_AudioEngine_Create")]
        private static extern IntPtr create();

        [DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_AudioEngine_Create1")]
        private static extern IntPtr create1(string deviceName);

        //E3DRSP_AudioEngine_ListAudioDevices
        [DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_AudioEngine_ListAudioDevices")]
        private static extern IntPtr listAudioDevices();

        [DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_AudioEngine_SwitchAudioDevice")]
        private static extern void switchDevice(IntPtr audio, string name);

        [DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_AudioEngine_Update")]
        private static extern void update(IntPtr audio);

        [DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_AudioEngine_CheckErrors")]
        private static extern int checkErrors(IntPtr audio);

        [DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_AudioEngine_Destroy")]
        private static extern void destroy(IntPtr audio);

        public AudioEngine()
        {
            _audio = create();
            _disposed = false;
        }

        public AudioEngine(string deviceName)
        {
            _audio = create1(deviceName);
            _disposed = false;
        }

        public unsafe static List<string>? ListAudioDevices()
        {
            List<string> result = new();

            IntPtr ptr = listAudioDevices();
            if (ptr == IntPtr.Zero) return null;

            char* currentString = null;
            do
            {
                currentString = *((char**)ptr);

                if (currentString != null)
                {
                    result.Add(Marshal.PtrToStringAnsi((IntPtr)currentString));
                }
                else break;
            }
            while (true);

            return result;
        }

        public void SwitchAudioDevice(string deviceName)
        {
            switchDevice(_audio, deviceName);
        }

        public void Update()
        {
            update(_audio);
        }

        public AudioError CheckErrors()
        {
            return (AudioError)checkErrors(_audio);
        }

        public nint Handle
        {
            get => _audio;
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        protected virtual void Dispose(bool disposing)
        {
            if (_disposed) return;

            if (_audio != 0)
            {
                destroy(_audio);
                _audio = 0;
            }

            _disposed = true;
        }

        ~AudioEngine()
        {
            Dispose(false);
        }
    }
}
