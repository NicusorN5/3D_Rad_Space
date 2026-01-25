namespace Engine3DRadSpace.Graphics;

public interface IRenderTarget : IPtrWrapper
{
	public IntPtr RenderTargetHandle { get; }
}
