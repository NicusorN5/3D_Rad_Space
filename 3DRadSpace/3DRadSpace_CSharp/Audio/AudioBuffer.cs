using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Audio
{
    public class AudioBuffer : IDisposable
    {
        [DllImport("3DRadSpace.Audio.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_AudioBuffer_Create")]
        private static extern IntPtr create(IntPtr buffer, int numChannels, int sampleRate, int bps, int format, int size);

        [DllImport("3DRadSpace.Audio.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_AudioBuffer_FromWAV")]
        private static extern IntPtr fromWAV(string path);

        [DllImport("3DRadSpace.Audio.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_AudioBuffer_FromOGG")]
        private static extern IntPtr fromOGG(string path);

        [DllImport("3DRadSpace.Audio.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_AudioBuffer_Destroy")]
        private static extern void destroy(IntPtr audioBuffer);

        IntPtr _audioBuffer;
        bool _disposed;

        public AudioBuffer(IntPtr buffer, int numChannels, int sampleRate, int bps, int format, int size)
        {
            _audioBuffer = create(buffer, numChannels, sampleRate, bps, format, size);
            _disposed = false;
        }

        private AudioBuffer(IntPtr handle)
        {
            _audioBuffer = handle;
            _disposed = false;
        }

        public static AudioBuffer FromWAV(string path)
        {
            return new AudioBuffer(fromWAV(path));
        }

        public static AudioBuffer FromOGG(string path)
        {
            return new AudioBuffer(fromOGG(path));
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);  
        }
        protected virtual void Dispose(bool disposing)
        {
            if (_disposed)
            {
                return;
            }

            if(_audioBuffer != 0)
            {
                destroy(_audioBuffer);
                _audioBuffer = 0;
            }

            _disposed = true;
        }

        public nint Handle
        {
            get => _audioBuffer;
        }

        ~AudioBuffer()
        {
            Dispose(false);
        }
    }
}
