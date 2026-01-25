using System.Numerics;
using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Math;

[StructLayout(LayoutKind.Sequential)]
public struct BoundingSphere
{
	public Vector3 Position;
	public float Radius;

	public BoundingSphere(Vector3 position, float radius)
	{
		Position = position;
		Radius = radius;
	}
}
