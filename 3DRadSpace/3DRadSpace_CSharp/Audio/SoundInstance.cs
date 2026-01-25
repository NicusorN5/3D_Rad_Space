using System.Runtime.InteropServices;
using System.Numerics;

namespace Engine3DRadSpace.Audio;
public class SoundInstance : IDisposable
{
	IntPtr _soundInstance;
	bool _disposed;

	[DllImport("3DRadSpace.Audio.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_Create")]
	private static extern IntPtr create(IntPtr sound, IntPtr source);

	[DllImport("3DRadSpace.Audio.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_Destroy")]
	private static extern void destroy(IntPtr sound);

	[DllImport("3DRadSpace.Audio.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_GetPitch")]
	private static extern float getPitch(IntPtr sound);

	[DllImport("3DRadSpace.Audio.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_SetPitch")]
	private static extern void setPitch(IntPtr sound, float pitch);

	[DllImport("3DRadSpace.Audio.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_GetGain")]
	private static extern float getGain(IntPtr sound);

	[DllImport("3DRadSpace.Audio.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_SetGain")]
	private static extern void setGain(IntPtr sound, float gain);

	[DllImport("3DRadSpace.Audio.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_GetMaxGain")]
	private static extern float getMaxGain(IntPtr sound);

	[DllImport("3DRadSpace.Audio.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_SetMaxGain")]
	private static extern void setMaxGain(IntPtr sound, float gain);

	[DllImport("3DRadSpace.Audio.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_GetMinGain")]
	private static extern float getMinGain(IntPtr sound);

	[DllImport("3DRadSpace.Audio.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_SetMinGain")]
	private static extern void setMinGain(IntPtr sound, float gain);

	[DllImport("3DRadSpace.Audio.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_GetPosition")]
	private static extern IntPtr getPosition(IntPtr sound);

	[DllImport("3DRadSpace.Audio.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_SetPosition")]
	private static extern void setPostion(IntPtr sound, IntPtr pos);

	[DllImport("3DRadSpace.Audio.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_GetVelocity")]
	private static extern IntPtr getVelocity(IntPtr sound);

	[DllImport("3DRadSpace.Audio.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_SetVelocity")]
	private static extern void setVelocity(IntPtr sound, IntPtr vel);

	[DllImport("3DRadSpace.Audio.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_GetDirection")]
	private static extern IntPtr getDirection(IntPtr sound);

	[DllImport("3DRadSpace.Audio.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_SetDirection")]
	private static extern void setDirection(IntPtr sound, IntPtr dir);

	[DllImport("3DRadSpace.Audio.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_GetMaxDistance")]
	private static extern float getMaxDistance(IntPtr sound);

	[DllImport("3DRadSpace.Audio.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_SetMaxDistance")]
	private static extern void setMaxDistance(IntPtr sound, float dst);


	[DllImport("3DRadSpace.Audio.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_GetReferenceDistance")]
	private static extern float getReferenceDistance(IntPtr sound);

	[DllImport("3DRadSpace.Audio.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_SetReferenceDistance")]
	private static extern void setReferenceDistance(IntPtr sound, float refDst);

	[DllImport("3DRadSpace.Audio.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_GetRolloffFactor")]
	private static extern float getRolloffFactor(IntPtr sound);

	[DllImport("3DRadSpace.Audio.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_SetRolloffFactor")]
	private static extern void setRolloffFactor(IntPtr sound, float rolloff);

	[DllImport("3DRadSpace.Audio.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_GetConeOuterGain")]
	private static extern float getConeOuterGain(IntPtr sound);

	[DllImport("3DRadSpace.Audio.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_SetConeOuterGain")]
	private static extern void setConeOuterGain(IntPtr sound, float gain);

	[DllImport("3DRadSpace.Audio.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_GetConeInnerAngle")]
	private static extern float getConeInnerAngle(IntPtr sound);

	[DllImport("3DRadSpace.Audio.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_SetConeInnerAngle")]
	private static extern void setConeInnerAngle(IntPtr sound, float angle);

	[DllImport("3DRadSpace.Audio.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_GetConeOuterAngle")]
	private static extern float getConeOuterAngle(IntPtr sound);

	[DllImport("3DRadSpace.Audio.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_SetConeOuterAngle")]
	private static extern void setConeOuterAngle(IntPtr sound, float rolloff);

	[DllImport("3DRadSpace.Audio.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_IsLooping")]
	private static extern byte isLooping(IntPtr sound);

	[DllImport("3DRadSpace.Audio.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_SetLooping")]
	private static extern void setLooping(IntPtr sound, byte looping);

	[DllImport("3DRadSpace.Audio.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_Play")]
	private static extern void play(IntPtr sound);

	[DllImport("3DRadSpace.Audio.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_Stop")]
	private static extern void stop(IntPtr sound);

	[DllImport("3DRadSpace.Audio.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_SoundInstance_Pause")]
	private static extern void pause(IntPtr sound);

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
		get => isLooping(_soundInstance) > 0;
		set => setLooping(_soundInstance, (byte)(value ? 1 : 0));
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
		if (_disposed)
		{
			return;
		}

		if (_soundInstance != 0)
		{
			destroy(_soundInstance);
			_soundInstance = 0;
		}

		_disposed = true;
	}
}
