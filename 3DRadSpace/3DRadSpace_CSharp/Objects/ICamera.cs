using System;
using System.Numerics;

namespace Engine3DRadSpace.Objects;

public interface ICamera
{
	public Matrix4x4 GetViewMatrix();
	public Matrix4x4 GetProjectionMatrix();
}
