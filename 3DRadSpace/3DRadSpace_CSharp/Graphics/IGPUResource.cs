namespace Engine3DRadSpace.Graphics
{
    public interface IGPUResource : IPtrWrapper
    {
        IGraphicsDevice GraphicsDevice { get; }
        IntPtr GPUHandle { get; }
    }
}
