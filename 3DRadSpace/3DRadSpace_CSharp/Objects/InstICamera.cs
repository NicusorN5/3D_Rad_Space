using System.Numerics;
using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Objects;

public class InstICamera : NatPtrWrapper
{
	[DllImport("Engine3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_ICamera_GetViewMatrix")]
	extern static Matrix4x4 _view(IntPtr icamera);

	[DllImport("Engine3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_ICamera_GetProjectionMatrix")]
	extern static Matrix4x4 _proj(IntPtr icamera);

	[DllImport("Engine3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_ICamera_Destroy")]
	extern static void _destroy(IntPtr icamera);

	public InstICamera(IntPtr natPtr) : base(natPtr, _destroy)
	{
	}
}
