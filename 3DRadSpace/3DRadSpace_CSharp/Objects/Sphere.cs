using Engine3DRadSpace.Math;
using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Objects
{
	public class Sphere : InstIObject3D
	{
		[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_OSphere_Create")]
		extern static IntPtr _create();

		[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_OSphere_GetColor")]
		extern static Color _getColor(IntPtr sphere);

		[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_OSphere_SetColor")]
		extern static unsafe void _setColor(IntPtr sphere, Color* color);

		[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_OSphere_GetRadius")]
		extern static float _getRadius(IntPtr sphere);

		[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_OSphere_SetRadius")]
		extern static void _setRadius(IntPtr sphere, float radius);

		[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_OSphere_GetResolution")]
		extern static uint _getResolution(IntPtr sphere);

		[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_OSphere_SetResolution")]
		extern static void _setResolution(IntPtr sphere, uint resolution);

		public Sphere() : base(_create())
		{
		}

		public unsafe Color Color
		{
			get => _getColor(_handle);
			set => _setColor(_handle, &value);
		}

		public float Radius
		{
			get => _getRadius(_handle);
			set => _setRadius(_handle, value);
		}

		public uint Resolution
		{
			get => _getResolution(_handle);
			set => _setResolution(_handle, value);
		}
	}
}
