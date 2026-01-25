using System.Runtime.InteropServices;

namespace Engine3DRadSpace;

public abstract class InstIDrawable3D : NatPtrWrapper, IDrawable3D
{
	[DllImport("3DRadSpace.Core.dll", EntryPoint = "E3DRSP_IDrawable3D_Destroy")]
	extern static void _destroy(IntPtr handle);

	[DllImport("3DRadSpace.Core.dll", EntryPoint = "E3DRSP_IDrawable3D_Draw3D")]
	internal extern static void _draw3D(IntPtr handle);

	protected InstIDrawable3D(IntPtr handle) : base(handle, _destroy)
	{
	}

	public void Draw3D()
	{
		_draw3D(_handle);
	}
}
