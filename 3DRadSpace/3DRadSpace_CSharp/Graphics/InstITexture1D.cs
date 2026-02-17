using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Graphics
{
	public class InstITexture1D : InstGPUMultiBuffer, ITexture1D 
	{
		[DllImport("3DRadSpace.Graphics.dll", EntryPoint = "E3DRSP_ITexture1D_Size")]
		extern static long _size(IntPtr texture);

		[DllImport("3DRadSpace.Graphics.dll", EntryPoint = "E3DRSP_ITexture1D_GetViewHandle")]
		extern static IntPtr _viewHandle(IntPtr texture);

		[DllImport("3DRadSpace.Graphics.dll", EntryPoint = "E3DRSP_ITexture1D_CreateStaging")]
		extern static IntPtr _createStaging(IntPtr texture);

		public InstITexture1D(IntPtr handle) : base(handle)
		{
		}

		public long Size => _size(Handle);
		public IntPtr ViewHandle => _viewHandle(Handle);

		public ITexture1D CreateStaging()
		{
			return new InstITexture1D(_createStaging(Handle));
		}
	}
}
