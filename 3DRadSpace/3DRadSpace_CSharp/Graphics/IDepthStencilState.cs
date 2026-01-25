namespace Engine3DRadSpace.Graphics;

public interface IDepthStencilState : IPtrWrapper, IGPUResource
{
	public uint StencilRef();
}
