using System.Numerics;
using Engine3DRadSpace.Math;

namespace Engine3DRadSpace.Objects;

public interface IObject3D : IObject, IDrawable3D
{
	public Vector3 Position { get; set; }
	public Vector3 RotationCenter { get; set; }
	public Quaternion Rotation { get; set; }
	public Vector3 Scale { get; set; }

	public Matrix4x4 GetModelMatrix();
	public float? Intersects(Ray ray);
}
