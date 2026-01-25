using System.Runtime.InteropServices;

namespace Engine3DRadSpace;

public class InstIInitializable : NatPtrWrapper, IInitializable
{
	[DllImport("3DRadSpace.Core.dll", EntryPoint = "E3DRSP_IInitializable_Initialize")]
	internal extern static void _initialize(IntPtr handle);

	[DllImport("3DRadSpace.Core.dll", EntryPoint = "E3DRSP_IInitializable_Destroy")]
	internal extern static void _destroy(IntPtr handle);

	public InstIInitializable(IntPtr handle) : base(handle, _destroy)
	{
	}

	public void Initialize()
	{
		_initialize(_handle);
	}
}
