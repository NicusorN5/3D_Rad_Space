using Engine3DRadSpace.Math;
using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Objects
{
	public class Box : InstIObject3D
	{
		[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_OBox_Create")]
		extern static IntPtr _create();

		[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_OBox_GetColor")]
		extern static Color _getColor(IntPtr box);

		[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_OBox_SetColor")]
		extern static unsafe void _setColor(IntPtr box, Color* color);

		public Box() : base(_create())
		{
		}

		public unsafe Color Color
		{
			get => _getColor(_handle);
			set => _setColor(_handle, &value);
		}
	}
}
