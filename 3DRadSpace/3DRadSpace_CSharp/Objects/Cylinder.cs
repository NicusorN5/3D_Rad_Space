using Engine3DRadSpace.Math;
using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Objects
{
	public class Cylinder : InstIObject3D
	{
		[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_OCylinder_Create")]
		extern static IntPtr _create();

		[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_OCylinder_GetColor")]
		extern static Color _getColor(IntPtr cylinder);

		[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_OCylinder_SetColor")]
		extern static unsafe void _setColor(IntPtr cylinder, Color* color);

		[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_OCylinder_GetRadius")]
		extern static float _getRadius(IntPtr cylinder);

		[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_OCylinder_SetRadius")]
		extern static void _setRadius(IntPtr cylinder, float radius);

		[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_OCylinder_GetHeight")]
		extern static float _getHeight(IntPtr cylinder);

		[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_OCylinder_SetHeight")]
		extern static void _setHeight(IntPtr cylinder, float height);

		[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_OCylinder_GetResolution")]
		extern static uint _getResolution(IntPtr cylinder);

		[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_OCylinder_SetResolution")]
		extern static void _setResolution(IntPtr cylinder, uint resolution);

		public Cylinder() : base(_create())
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
		public float Height
		{
			get => _getHeight(_handle);
			set => _setHeight(_handle, value);
		}

		public uint Resolution
		{
			get => _getResolution(_handle);
			set => _setResolution(_handle, value);
		}
	}
}
