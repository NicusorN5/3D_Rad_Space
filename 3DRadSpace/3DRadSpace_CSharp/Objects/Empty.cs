using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Objects
{
	public class Empty : InstIObject3D
	{
		[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_Empty_Create")]
		extern static IntPtr _create();

		public Empty() : base(_create())
		{
		}
	}
}
