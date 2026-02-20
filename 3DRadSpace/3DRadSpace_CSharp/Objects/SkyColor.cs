using Engine3DRadSpace.Math;
using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Objects
{
	public class SkyColor : InstIObject
	{
		[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_SkyColor_Create")]
		extern static IntPtr _create();

		[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_SkyColor_Get")]
		extern static Color _get(IntPtr skinmesh);

		[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_SkyColor_Set")]
		extern static unsafe void _set(IntPtr skinmesh, Color *color);

		public SkyColor() : base(_create())
		{
		}

		public unsafe Color Color
		{
			get => _get(_handle);
			set => _set(_handle, &value);
		}
	}
}
