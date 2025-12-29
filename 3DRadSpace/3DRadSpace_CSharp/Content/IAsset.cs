using Engine3DRadSpace.Reflection;

namespace Engine3DRadSpace.Content
{
    public interface IAsset
    {
        public UUID UUID { get; }
        public string FileExtension { get; }
    }
}
