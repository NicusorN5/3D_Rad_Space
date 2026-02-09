using System.Drawing;

namespace Engine3DRadSpace.Graphics;

public interface ITextureCube : IGPUResource
{
	public Point Size { get; }
	public uint Width { get; }
	public uint Height { get; }
	public IntPtr ViewHandle { get; }
	public ITexture2D CreateStaging();
}
