using System.Numerics;
using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Math;

[StructLayout(LayoutKind.Sequential)]
public struct Ray
{
	public Vector3 Origin;
	public Vector3 Direction;

	public Ray(Vector3 origin, Vector3 direction)
	{
		Origin = origin;
		Direction = direction;
	}
}
