using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Objects
{
	public class Skinmesh : InstIObject3D
	{
		[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_Skinmesh_Create")]
		extern static IntPtr _create();

		[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_Skinmesh_GetModel")]
		extern static uint _getModel(IntPtr skinmesh);

		[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_Skinmesh_SetModel")]
		extern static void _setModel(IntPtr skinmesh, uint id);

		public Skinmesh() : base(_create())
		{
		}

		public uint Model
		{
			get => _getModel(_handle);
			set=> _setModel(_handle, value);
		}
	}
}
