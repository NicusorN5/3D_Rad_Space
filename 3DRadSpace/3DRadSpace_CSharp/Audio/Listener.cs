using System.Numerics;
using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Audio;

[StructLayout(LayoutKind.Sequential)]
struct Listener
{
	float Volume;
	Vector3 Position;
	Vector3 Velocity;

	Vector3 Direction;
	Vector3 Normal;

	byte Enabled;
}
