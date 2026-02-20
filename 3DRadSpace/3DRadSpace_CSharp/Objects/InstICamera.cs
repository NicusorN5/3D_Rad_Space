using System.Numerics;
using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Objects;

public class InstICamera : NatPtrWrapper, ICamera
{
	[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_ICamera_GetViewMatrix")]
	extern static Matrix4x4 _view(IntPtr icamera);

	[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_ICamera_GetProjectionMatrix")]
	extern static Matrix4x4 _proj(IntPtr icamera);

	[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_ICamera_Destroy")]
	extern static void _destroy(IntPtr icamera);

	public InstICamera(IntPtr natPtr) : base(natPtr, _destroy)
	{
	}

	public Matrix4x4 GetViewMatrix()
	{
		return _view(_handle);
	}

	public Matrix4x4 GetProjectionMatrix()
	{
		return _proj(_handle);
	}
}
