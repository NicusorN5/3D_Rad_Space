namespace Engine3DRadSpace.Graphics;

public interface ITexture1D : IGPUMultiBuffer
{
    public long Size { get; }
    public IntPtr ViewHandle { get; }
    public ITexture1D CreateStaging();
}
