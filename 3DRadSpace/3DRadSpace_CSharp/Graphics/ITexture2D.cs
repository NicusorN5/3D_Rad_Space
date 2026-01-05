using System.Drawing;

namespace Engine3DRadSpace.Graphics
{
    public interface ITexture2D : IPtrWrapper
    {
        public Point Size { get; }
        public uint Width { get; }
        public uint Height { get; }
        public IntPtr ViewHandle { get; }
        public ITexture2D CreateStaging();
        public void SaveToFile(string path);
    }
}
