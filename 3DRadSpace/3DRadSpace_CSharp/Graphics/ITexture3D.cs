using Engine3DRadSpace.Math;

namespace Engine3DRadSpace.Graphics
{
	public interface ITexture3D : IGPUMultiBuffer
	{
		public UPoint3 Size { get; }
		public uint Width { get; }
		public uint Height { get; }
		public uint Depth { get; }

		public IntPtr GetViewHandle();
		public ITexture3D CreateStaging();
	}
}
