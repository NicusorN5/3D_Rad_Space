using System.Drawing;
using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Graphics;

public class InstITextureCube : InstGPUResource, ITextureCube
{
	[DllImport("3DRadSpace.Graphics.dll", EntryPoint = "E3DRSP_ITextureCube_Size")]
	extern static Internal.Point _size(IntPtr texture);

	[DllImport("3DRadSpace.Graphics.dll", EntryPoint = "E3DRSP_ITextureCube_Width")]
	extern static uint _w(IntPtr texture);

	[DllImport("3DRadSpace.Graphics.dll", EntryPoint = "E3DRSP_ITextureCube_Height")]
	extern static uint _h(IntPtr texture);

	[DllImport("3DRadSpace.Graphics.dll", EntryPoint = "E3DRSP_ITextureCube_GetViewHandle")]
	extern static IntPtr _viewHandle(IntPtr texture);

	[DllImport("3DRadSpace.Graphics.dll", EntryPoint = "E3DRSP_ITextureCube_CreateStaging")]
	extern static IntPtr _createStaging(IntPtr texture);

	public InstITextureCube(IntPtr handle) : base(handle)
	{
	}

	public Point Size
	{
		get
		{
			var s = _size(_handle);
			return new Point(s.X, s.Y);
		}
	}

	public uint Width
	{
		get => _w(_handle);
	}

	public uint Height
	{
		get => _h(_handle);
	}

	public IntPtr ViewHandle
	{
		get => _viewHandle(_handle);
	}

	public ITexture2D CreateStaging()
	{
		return new InstITexture2D(_createStaging(_handle));
	}
}
