using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Objects
{
	public class Skybox : InstIObject3D
	{
		[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_Skybox_Create")]
		extern static IntPtr _create();

		[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_Skybox_Get")]
		extern static uint _getSkyboxID(IntPtr skinmesh);

		[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_Skybox_Set")]
		extern static void _setSkyboxID(IntPtr skinmesh, uint id);

		public Skybox() : base(_create())
		{
		}

		public uint SkyboxID
		{
			get => _getSkyboxID(_handle);
			set => _setSkyboxID(_handle, value);
		}
	}
}
