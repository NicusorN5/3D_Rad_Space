using System.Runtime.InteropServices;
using System.Numerics;

namespace Engine3DRadSpace.Audio
{
    public class SoundInstance : IDisposable
    {
        IntPtr _soundInstance;
        bool _disposed;


        [DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_Create")]
        private static unsafe extern IntPtr create(IntPtr sound, IntPtr source);

        [DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_Destroy")]
        private static unsafe extern void destroy(IntPtr sound);

        [DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_GetPitch")]
        private static unsafe extern float getPitch(IntPtr sound);

        [DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_SetPitch")]
        private static unsafe extern void setPitch(IntPtr sound, float pitch);

        [DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_GetGain")]
        private static unsafe extern float getGain(IntPtr sound);

        [DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_SetGain")]
        private static unsafe extern void setGain(IntPtr sound, float gain);

        [DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_GetMaxGain")]
        private static unsafe extern float getMaxGain(IntPtr sound);

        [DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_SetMaxGain")]
        private static unsafe extern void setMaxGain(IntPtr sound, float gain);

        [DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_GetMinGain")]
        private static unsafe extern float getMinGain(IntPtr sound);

        [DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_SetMinGain")]
        private static unsafe extern void setMinGain(IntPtr sound, float gain);

        [DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_GetPosition")]
        private static unsafe extern IntPtr getPosition(IntPtr sound);

        [DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_SetPosition")]
        private static unsafe extern void setPostion(IntPtr sound, IntPtr pos);

        [DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_GetVelocity")]
        private static unsafe extern IntPtr getVelocity(IntPtr sound);

        [DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_SetVelocity")]
        private static unsafe extern void setVelocity(IntPtr sound, IntPtr vel);

        [DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_GetDirection")]
        private static unsafe extern IntPtr getDirection(IntPtr sound);

        [DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_SetDirection")]
        private static unsafe extern void setDirection(IntPtr sound, IntPtr dir);

        [DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_GetMaxDistance")]
        private static unsafe extern float getMaxDistance(IntPtr sound);

        [DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_SetMaxDistance")]
        private static unsafe extern void setMaxDistance(IntPtr sound, float dst);


        [DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_GetReferenceDistance")]
        private static unsafe extern float getReferenceDistance(IntPtr sound);

        [DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_SetReferenceDistance")]
        private static unsafe extern void setReferenceDistance(IntPtr sound, float refDst);

        [DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_GetRolloffFactor")]
        private static unsafe extern float getRolloffFactor(IntPtr sound);

        [DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_SetRolloffFactor")]
        private static unsafe extern void setRolloffFactor(IntPtr sound, float rolloff);

        [DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_GetConeOuterGain")]
        private static unsafe extern float getConeOuterGain(IntPtr sound);

        [DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_SetConeOuterGain")]
        private static unsafe extern void setConeOuterGain(IntPtr sound, float gain);

        [DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_GetConeInnerAngle")]
        private static unsafe extern float getConeInnerAngle(IntPtr sound);

        [DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_SetConeInnerAngle")]
        private static unsafe extern void setConeInnerAngle(IntPtr sound, float angle);

        [DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_GetConeOuterAngle")]
        private static unsafe extern float getConeOuterAngle(IntPtr sound);

        [DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_SetConeOuterAngle")]
        private static unsafe extern void setConeOuterAngle(IntPtr sound, float rolloff);

        [DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_IsLooping")]
        private static unsafe extern bool isLooping(IntPtr sound);

        [DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_Play")]
        private static unsafe extern bool play(IntPtr sound);

        [DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_Stop")]
        private static unsafe extern bool stop(IntPtr sound);

        [DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_Pause")]
        private static unsafe extern bool pause(IntPtr sound);

        public unsafe SoundInstance(Sound sound, AudioSource source)
        {
            _soundInstance = create(sound.Handle, (nint)(&source));
        }

        public float Pitch
        {
            get => getPitch(_soundInstance);
            set => setPitch(_soundInstance, value);
        }

        public float Gain
        {
            get => getGain(_soundInstance);
            set => setGain(_soundInstance, value);
        }

        public float MaxGain
        {
            get => getMaxGain(_soundInstance);
            set => setMaxGain(_soundInstance, value);
        }

        public float MinGain
        {
            get => getMinGain(_soundInstance);
            set => setMinGain(_soundInstance, value);
        }

        public unsafe Vector3 Position
        {
            get => *(Vector3*)getPosition(_soundInstance);
            set => setPostion(_soundInstance, (IntPtr)(&value));
        }

        public unsafe Vector3 Velocity
        {
            get => *((Vector3*)getVelocity(_soundInstance));
            set => setVelocity(_soundInstance, (IntPtr)(&value));
        }

        public unsafe Vector3 Direction
        {
            get => *((Vector3*)getDirection(_soundInstance));
            set => setDirection(_soundInstance, (IntPtr)(&value));
        }

        public float MaxDistance
        {
            get => getMaxDistance(_soundInstance);
            set => setMaxDistance(_soundInstance, value);
        }

        public float RerefenceDistance
        {
            get => getReferenceDistance(_soundInstance);
            set => setReferenceDistance(_soundInstance, value);
        }

        public float RolloffFactor
        {
            get => getRolloffFactor(_soundInstance);
            set => setRolloffFactor(_soundInstance, value);
        }

        public float ConeOuterGain
        {
            get => getConeOuterGain(_soundInstance);
            set => setConeOuterGain(_soundInstance, value);
        }

        public float ConeInnerAngle
        {
            get => getConeInnerAngle(_soundInstance);
            set => setConeInnerAngle(_soundInstance, value);
        }

        public float ConeOuterAngle
        {
            get => getConeOuterAngle(_soundInstance);
            set => setConeOuterAngle(_soundInstance, value);
        }

        public bool IsLooping
        {
            get => isLooping(_soundInstance);
        }

        public void Play()
        {
            play(_soundInstance);
        }

        public void Stop()
        {
            stop(_soundInstance);
        }

        public void Pause()
        {
            pause(_soundInstance);
        }

        public void Dispose()
        {
            Dispose(true);
        }

        virtual protected void Dispose(bool disposing)
        {
            if (_disposed) return;

            if (_soundInstance != 0)
            {
                destroy(_soundInstance);
                _soundInstance = 0;
            }

            _disposed = true;
        }
    }
}
