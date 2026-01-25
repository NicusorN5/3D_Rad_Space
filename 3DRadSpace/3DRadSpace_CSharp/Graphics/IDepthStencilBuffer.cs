namespace Engine3DRadSpace.Graphics;

public interface IDepthStencilBuffer : IPtrWrapper, IGPUBuffer
{
	public IntPtr GetDepthTextureHandle();
	public ITexture2D GetDepthTexture();

	public ITexture2D CloneDepthTexture();
}
