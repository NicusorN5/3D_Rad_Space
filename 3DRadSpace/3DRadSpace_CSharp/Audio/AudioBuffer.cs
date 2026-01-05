using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Audio
{
    public class AudioBuffer : NatPtrWrapper
    {
        [DllImport("3DRadSpace.Audio.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_AudioBuffer_Create")]
        private static extern IntPtr create(IntPtr buffer, int numChannels, int sampleRate, int bps, int format, int size);

        [DllImport("3DRadSpace.Audio.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_AudioBuffer_FromWAV")]
        private static extern IntPtr fromWAV(string path);

        [DllImport("3DRadSpace.Audio.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_AudioBuffer_FromOGG")]
        private static extern IntPtr fromOGG(string path);

        [DllImport("3DRadSpace.Audio.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_AudioBuffer_Destroy")]
        private static extern void destroy(IntPtr audioBuffer);


        public AudioBuffer(IntPtr buffer, int numChannels, int sampleRate, int bps, int format, int size) : base(create(buffer, numChannels, sampleRate, bps, format, size), destroy)
        {
        }

        private AudioBuffer(IntPtr handle) : base(handle, destroy)
        {
        }

        public static AudioBuffer FromWAV(string path)
        {
            return new AudioBuffer(fromWAV(path));
        }

        public static AudioBuffer FromOGG(string path)
        {
            return new AudioBuffer(fromOGG(path));
        }
    }
}
